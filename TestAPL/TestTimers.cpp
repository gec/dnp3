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


#include <opendnp3/APL/TimerSourceASIO.h>
#include <opendnp3/APL/Threadable.h>
#include <opendnp3/APL/Thread.h>
#include <opendnp3/APL/Exception.h>

#include <map>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace std;
using namespace apl;

class MockTimerHandler
{
public:
	MockTimerHandler() : mCount(0)
	{}

	void OnExpiration() {
		++mCount;
	}
	size_t GetCount() {
		return mCount;
	}

private:
	size_t mCount;
};

class MonotonicReceiver : private Threadable
{
public:
	MonotonicReceiver(boost::asio::io_service* apSrv, TimerSourceASIO* apTimerSrc) :
		mLast(-1),
		mNum(0),
		mMonotonic(true),
		mpSrv(apSrv),
		mpTimerSrc(apTimerSrc),
		mpInfinite(apTimerSrc->StartInfinite()),
		mThread(this)
	{
		mThread.Start();	
	}

	~MonotonicReceiver()
	{
		mpInfinite->Cancel();
	}

	void Receive(int aVal) {
		if(aVal <= mLast) mMonotonic = false;
		++mNum;
		mLast = aVal;
	}

	bool IsMonotonic() {
		return mMonotonic;
	}

	int Num() {
		return mNum;
	}	

private:

	int mLast;
	int mNum;
	bool mMonotonic;

	boost::asio::io_service* mpSrv;
	TimerSourceASIO* mpTimerSrc;
	ITimer* mpInfinite;

	void Run() {
		mpSrv->run();
	}

	Thread mThread;
};

BOOST_AUTO_TEST_SUITE(Timers)

void ThrowInvalidStateException()
{
	throw InvalidStateException(LOCATION, "some bad state");
}

BOOST_AUTO_TEST_CASE(SyncRethrowsExceptions)
{
	boost::asio::io_service srv;
	TimerSourceASIO ts(&srv);
	MonotonicReceiver rcv(&srv, &ts);	

	BOOST_REQUIRE_THROW(ts.PostSync(boost::bind(&ThrowInvalidStateException)), Exception);

}

BOOST_AUTO_TEST_CASE(TestOrderedDispatch)
{
	const int NUM = 10000;

	boost::asio::io_service srv;
	TimerSourceASIO ts(&srv);
	MonotonicReceiver rcv(&srv, &ts);

	for(int i = 0; i < NUM; ++i) {
		ts.Post(boost::bind(&MonotonicReceiver::Receive, &rcv, i));
	}

	ts.Sync();

	BOOST_REQUIRE_EQUAL(NUM, rcv.Num());
	BOOST_REQUIRE(rcv.IsMonotonic());
}


BOOST_AUTO_TEST_CASE(ExpirationAndReuse)
{
	MockTimerHandler mth;
	boost::asio::io_service srv;
	TimerSourceASIO ts(&srv);
	ITimer* pT1 = ts.Start(1, boost::bind(&MockTimerHandler::OnExpiration, &mth));
	BOOST_REQUIRE_EQUAL(srv.run_one(), 1);
	BOOST_REQUIRE_EQUAL(1, mth.GetCount());
	ITimer* pT2 = ts.Start(1, boost::bind(&MockTimerHandler::OnExpiration, &mth));
	BOOST_REQUIRE_EQUAL(pT1, pT2); //The ASIO implementation should reuse timers
}

BOOST_AUTO_TEST_CASE(Cancelation)
{
	MockTimerHandler mth;
	boost::asio::io_service srv;
	TimerSourceASIO ts(&srv);
	ITimer* pT1 = ts.Start(1, boost::bind(&MockTimerHandler::OnExpiration, &mth));
	pT1->Cancel();
	BOOST_REQUIRE_EQUAL(1, srv.run_one());
	BOOST_REQUIRE_EQUAL(0, mth.GetCount());
	ITimer* pT2 = ts.Start(1, boost::bind(&MockTimerHandler::OnExpiration, &mth));
	BOOST_REQUIRE_EQUAL(pT1, pT2);
}


BOOST_AUTO_TEST_CASE(MultipleOutstanding)
{
	MockTimerHandler mth1;
	MockTimerHandler mth2;
	boost::asio::io_service srv;
	TimerSourceASIO ts(&srv);
	ITimer* pT1 = ts.Start(0, boost::bind(&MockTimerHandler::OnExpiration, &mth1));
	ITimer* pT2 = ts.Start(100, boost::bind(&MockTimerHandler::OnExpiration, &mth2));

	BOOST_REQUIRE_NOT_EQUAL(pT1, pT2);

	BOOST_REQUIRE_EQUAL(1, srv.run_one());
	BOOST_REQUIRE_EQUAL(1, mth1.GetCount());
	BOOST_REQUIRE_EQUAL(0, mth2.GetCount());

	BOOST_REQUIRE_EQUAL(1, srv.run_one());
	BOOST_REQUIRE_EQUAL(1, mth1.GetCount());
	BOOST_REQUIRE_EQUAL(1, mth2.GetCount());
}

BOOST_AUTO_TEST_SUITE_END()
