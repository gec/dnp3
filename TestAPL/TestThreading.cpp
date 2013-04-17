//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Enery Corp licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
#include <boost/test/unit_test.hpp>
#include <APLTestTools/TestHelpers.h>
#include <opendnp3/APL/Lock.h>
#include <opendnp3/APL/Thread.h>
#include <vector>

using namespace std;

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/Util.h>
#include <opendnp3/APL/Log.h>
using namespace apl;


BOOST_AUTO_TEST_SUITE(OSSpecificTests)
class WaitOnLock : public Threadable
{
public:
	WaitOnLock(SigLock* apCountLock , INotifier* apNotifier, Logger* apLogger, string aName):
		mWaiting(false), mpNotifier(apNotifier), mpCount(apCountLock), mpLogger(apLogger), mThreadName(aName) {
		//auto start the thread.
		mpThread = new Thread(this);

		mpThread->Start();
		//use the startLock to syncronize with the about to start thread.
		mStartLock.Lock();
		//block until the thread has actually started
		if(!mWaiting) {
			mStartLock.Wait();
		}
		mStartLock.Unlock();
	};
	~WaitOnLock() {
		//shut the loop down.
		mpThread->RequestStop();
		mpCount->Lock();
		while(mWaiting) {
			mpCount->Broadcast();
			mpCount->TimedWait(50);
		}
		mpCount->Unlock();
		mpThread->WaitForStop();
		delete mpThread;
	}

	std::string Description() const {
		return "WaitOnLock";
	}

	void Run() {
		//while we aren't quitting wait on the lock and count ticks.
		mpCount->Lock();
		//we use the startlock to make sure that this thread has gotten the count
		//lock so we know that the order the threads make it into the Wait() call is
		//the fifo order we expect
		mStartLock.Lock();
		mWaiting = true;
		mpLogger->Log(LEV_DEBUG, mThreadName, "About to wait");
		//rewake the constuctor
		mStartLock.Signal();
		mStartLock.Unlock();
		while(!this->IsExitRequested()) {
			//wait for notifies from the proxy, count them
			mpCount->Wait();
			//mpLogger->Log(LEV_DEBUG,L_PHYSICAL,mThreadName,"Woken, signaling event");
			mpNotifier->Notify();
		}
		//inform the destructor that the loop has died
		mWaiting = false;

		//do one last notify to handle case where last thread got RequestThread after
		//it had signaled but before it had gotten back to the wait condition.
		mpNotifier->Notify();


		//unlock the main lock so other threads can exit
		mpCount->Unlock();

	};
	bool mWaiting;
	//the event lock we use to notify the main thread that we have been woken
	INotifier* mpNotifier;
	//the "main" lock that we are going to wait on to verify FiFo behavior
	SigLock* mpCount;
	//an internal lock we use to make sure the thread is running before we return from the constuctor.
	SigLock mStartLock;
	Logger* mpLogger;
	string mThreadName;
	Thread* mpThread;
};
void AddCount(boost::int64_t aEvent, int* aCounts, int aSlots)
{
	boost::int64_t m = 1;
	int bit;
	for(bit = 0; bit < aSlots; bit++) {
		if(aEvent == (m << bit))break;
	}
	BOOST_REQUIRE(bit != aSlots);
	aCounts[bit]++;
}
bool CheckCount(int* aCounts, int aSlots, Logger* apLogger, bool aDisplay)
{
	int aMax = -1;
	int aMin = 100;
	for(int i = 0; i < aSlots; i++) {
		if(aMax < aCounts[i]) aMax = aCounts[i];
		if(aMin > aCounts[i]) aMin = aCounts[i];
	}
	if(aMax - aMin > 2 && aDisplay) {
		ostringstream oss;
		oss << "One Thread too far ahead Min = " << aMin << " max =" << aMax;
		apLogger->Log(LEV_EVENT, "AddCount", oss.str());
		return false;
	}
	return true;
}
void TestFifoOrder(int numThreads, EventLog* apLog)
{
	//create a name for the error messages
	ostringstream oss;
	oss << "Fifo:" << numThreads;
	string testName = oss.str();

	bool notFifo = false;
	//create the bit mask which is what the event counter should
	//look like when all the threads have fired
	boost::int64_t allThreadsMask = 1;
	allThreadsMask = (allThreadsMask << numThreads) - 1;

	//"main" lock we are going to be checking the FiFo nature
	SigLock* lock = new SigLock();
	//event counter
	EventLock* ec = new EventLock();

	ec->Lock();
	ec->GetEvents(); //clear the default !0
	ec->Unlock();

	Logger* pLogger = apLog->GetLogger(LEV_EVENT, "TestThreading");

	std::vector<WaitOnLock*> threads;
	int* counts = new int[numThreads];
	for(int i = 0; i < numThreads; i++) {
		//create a name for the thread
		ostringstream oss;
		oss << "Thread:" << i;
		//create and start a new listening thread with the mask 1 << i
		threads.push_back(new WaitOnLock(lock, ec->GetNotifier(EventLock::Get64BitMask(i)), apLog->GetLogger(LEV_WARNING, oss.str()), oss.str()));
		//check that the thread is in the waiting state
		BOOST_REQUIRE_EQUAL(threads[i]->mWaiting, true);
		counts[i] = 0;
	}
	//lock the event counter
	ec->Lock();
	//run through the entire order a few times to make sure the scheduling is fair
	for(int i = 0; i < numThreads * 7; i++) {
		//mod is the thread that should be getting fired this time.
		int mod = i % numThreads;

		//make sure the event counter is empty
		BOOST_REQUIRE_EQUAL(ec->GetEvents(), 0);
		pLogger->Log(LEV_DEBUG, testName, "Master about to Signal");
		//unlcok the event counter (so the other thread can get access)
		ec->Unlock();
		//lock and signal the other thread (which means it will wake up and signal an event)
		lock->Lock();
		lock->Signal();
		lock->Unlock();
		//relock the event counter and then get the ready events
		ec->Lock();
		if(ec->GetEvents(false) == 0) {
			//if there are no ready events wait until the signal happens that an event occured
			ec->Wait();
		}
		pLogger->Log(LEV_DEBUG, testName, "Master got woken");
		//calculate the mask the current thread should have.
		boost::int64_t mask = EventLock::Get64BitMask(mod);
		//get the value of the event counter.
		boost::int64_t count = ec->GetEvents();
		AddCount(count, counts, numThreads);
		//make sure we got what we expected
		if(count != mask) {
			ostringstream oss;
			oss << mask << " Mask != count " << count << " iter =" << (i / numThreads) << " mod = " << mod;
			pLogger->Log(LEV_DEBUG, testName, oss.str());
			notFifo = true;
		}
		if(mod == numThreads - 1) {
			CheckCount(counts, numThreads, pLogger, false);
		}
	}
	//no longer asserting its FIFO since it isn't really FIFO when other things are happening
	CheckCount(counts, numThreads, pLogger, true);
	//unlock the event counter so the threads can shut quickly
	ec->Unlock();

	pLogger->Log(LEV_DEBUG, testName, "StoppingAll");
	for(int i = 0; i < numThreads; i++) {
		//set all the threads to have: Threadable::mIsExitRequested set to true
		threads[i]->mpThread->RequestStop();
	}

	//make sure none of our threads have quit early
	ec->Lock();
	BOOST_REQUIRE_EQUAL( ec->GetEvents(false), 0);
	ec->Unlock();

	pLogger->Log(LEV_DEBUG, testName, "Broadcast");
	//wake up all the threads, they will all signal an event as they terminate
	lock->Lock();
	lock->Broadcast();
	lock->Unlock();
	//delete all the threads (also blocks until they all complete)
	for(size_t i = 0; i < threads.size(); i++) {
		delete (threads)[i];
	}
	//make sure that all the threads have quit
	ec->Lock();
	BOOST_REQUIRE_EQUAL( ec->GetEvents(false), allThreadsMask);
	ec->Unlock();

	//cleanup, if there were any threads waiting on these locks this would fail
	delete lock;
	delete ec;
	delete[] counts;
}

BOOST_AUTO_TEST_CASE(FifoOnLocks5)
{
	EventLog log;
	TestFifoOrder(5, &log);
}
BOOST_AUTO_TEST_CASE(FifoOnLocks15)
{
	EventLog log;
	TestFifoOrder(15, &log);
}
BOOST_AUTO_TEST_CASE(FifoOnLocks63)
{
	EventLog log;
	TestFifoOrder(63, &log);
}

void AssuredSleep(int millis)
{
	StopWatch t;
	Thread::SleepFor(millis, true);
	BOOST_REQUIRE(t.Elapsed() >= millis);
}
BOOST_AUTO_TEST_CASE(EnsuredSleepFor)
{
	AssuredSleep(1);
	AssuredSleep(2);
	AssuredSleep(9);
	AssuredSleep(100); //added this b/c it would have yielded ridiculous results on Linux when there was a bug
}

/*//test is deprecated, proper shutdown will ensure this doesn't happen,
BOOST_AUTO_TEST_CASE(DestructionWhileBeingWaitedOn)
{
	MAKE_LOG();
	Lock* lock = new Lock();
	EventLock* ec = new EventLock();
	WaitOnLock thread(lock,new EventLock(ec,1),apLogger,"test");
	// will cause assertion failure, can't do it!
	// delete lock;
	CLEAN_LOG();

}
*/
BOOST_AUTO_TEST_SUITE_END()
