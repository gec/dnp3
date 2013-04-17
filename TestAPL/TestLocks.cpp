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
#include <opendnp3/APL/Threadable.h>
#include <opendnp3/APL/Thread.h>
#include <opendnp3/APL/EventLock.h>

using namespace apl;




class MockThreadable : public Threadable
{
public:
	MockThreadable(SigLock* apLock) : mpLock(apLock) {}
private:
	SigLock* mpLock;
	void Run() {
		//just acquire and signal
		mpLock->Lock();
		mpLock->Signal();
		mpLock->Unlock();
	}

	std::string Description() const {
		return "MockThreadable";
	}
};

class DoubleLocker : public Threadable
{
public:
	DoubleLocker (SigLock* apLock) : mpLock(apLock) {}
private:
	SigLock* mpLock;
	void Run() {
		//just acquire and signal
		mpLock->Lock();
		mpLock->Lock();
		mpLock->Unlock();
	}
};

BOOST_AUTO_TEST_SUITE(OSSpecificTests)

BOOST_AUTO_TEST_CASE(CriticalSection)
{
	SigLock lock;
	apl::CriticalSection cs(&lock);
}

BOOST_AUTO_TEST_CASE(CriticalSectionEarlyEnd)
{
	SigLock lock;

	apl::CriticalSection cs(&lock);
	cs.End();
}

BOOST_AUTO_TEST_CASE(TimedWaitFailure)
{
	SigLock lock;

	lock.Lock();
	bool wake = lock.TimedWait(0);
	lock.Unlock();

	BOOST_REQUIRE(!wake);
}

BOOST_AUTO_TEST_CASE(TimedWaitSuccess)
{
	SigLock lock;
	MockThreadable threadable(&lock);
	Thread thread(&threadable);
	lock.Lock();
	thread.Start();
	bool wake = lock.TimedWait(10000);
	lock.Unlock();
	thread.WaitForStop();

	BOOST_REQUIRE(wake);
}

/*
BOOST_AUTO_TEST_CASE(DoubleLocking)
{
	Lock lock;
	DoubleLocker dl(&lock);
	Thread thread(&dl);
	thread.Start();
	thread.WaitForStop();

	lock.Lock();
	lock.Unlock();
}
*/

/* Deprecated - This test will fail an assertion in ~Lock() now.
BOOST_AUTO_TEST_CASE(DestructionWhileLocked){
	//create a lock
	Lock* plock = new Lock();
	// get the lock on it
	plock->Lock();
	//make sure that it doesn't explode if that lock is deleted while locked.
	delete plock;
}
*/

BOOST_AUTO_TEST_CASE(EventLockTests)
{
	EventLock ec;
	// Signal(), Broadcast() and GetEvents() all require being locked so we lock over the whole test
	ec.Lock();
	// test that before any events have been signaled the value is all bits set
	// this forces client code to check all sources at least once
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), static_cast<boost::int64_t>(~0));
	ec.Unlock();

	//test that a signal registers the correct event
	ec.SignalEvent(1);

	ec.Lock();
	// test that the evnt was recived (non destructivley)
	BOOST_REQUIRE_EQUAL(ec.GetEvents(false), 1);
	// make sure the non-destructive GetEvents left the event with the same value
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), 1);
	// make sure the regular destructive GetEvents() call cleared the event buffer.
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), 0);
	ec.Unlock();

	//make sure that a brodcast works like a signal
	ec.BroadcastEvent(1);

	ec.Lock();
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), 1);
	ec.Unlock();

	// make sure that multiple events are all stored and reported correctly.
	ec.SignalEvent(1);
	ec.SignalEvent(1 << 1);
	ec.SignalEvent(1 << 2);
	ec.SignalEvent(1 << 3);

	ec.Lock();
	//should be the OR of the 4 lowest bits = 0xf
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), 0xf);
	ec.Unlock();
}

BOOST_AUTO_TEST_CASE(Notifier)
{
	EventLock ec;
	ec.Lock();
	ec.GetEvents(); //when an event lock is initialized it is set to  !0
	ec.Unlock();


	int m1 = 1 << 2;
	int m2 = 1 << 4;
	//create a pair of EventLocks that use the same event counter
	INotifier* pNot1 = ec.GetNotifier(m1);
	INotifier* pNot2 = ec.GetNotifier(m2);

	pNot1->Notify();

	ec.Lock();
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), m1);
	ec.Unlock();

	pNot2->Notify();

	ec.Lock();
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), m2);
	ec.Unlock();

	pNot1->Notify();
	pNot2->Notify();

	ec.Lock();
	BOOST_REQUIRE_EQUAL(ec.GetEvents(), m1 | m2);
	ec.Unlock();
}
BOOST_AUTO_TEST_CASE(MaxLocks)
{
	std::vector<SigLock*> locks;
	for(int i = 0; i < 1000; i++) {
		locks.push_back(new SigLock());
	}
	for(int i = 1000 - 1; i >= 0; i--) {
		delete (locks)[i];
		locks.pop_back();
	}
}

BOOST_AUTO_TEST_SUITE_END()


