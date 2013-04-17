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
#include <iostream>

#include <opendnp3/APL/Configure.h>
#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/TimeTypes.h>
#include <opendnp3/APL/TimingTools.h>
#include <opendnp3/APL/Thread.h>
#include <opendnp3/APL/EventLock.h>
#include <opendnp3/APL/TimeSource.h>



#include <opendnp3/APL/Util.h>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>

using namespace std;
using namespace apl;


BOOST_AUTO_TEST_SUITE(TimeTest)
BOOST_AUTO_TEST_CASE(CustomPTimeToString)
{
	ptime t = time_from_string("2008-07-01 12:00:00.100");
	string out = ToNormalizedString(t);
	string expected("2008-Jul-01 12:00:00.100");

	BOOST_REQUIRE_EQUAL(out, expected);

	t = time_from_string("2008-07-01 2:01:27.000");
	out = ToNormalizedString(t);
	expected = "2008-Jul-01 02:01:27.000";

	BOOST_REQUIRE_EQUAL(out, expected);
}

BOOST_AUTO_TEST_CASE(Sleep)
{
	int sleeps[4] = {25, 50, 75, 100};

	for(int i = 0; i < 4; i++) {
		Time start;
		Thread::SleepFor(sleeps[i] + 10, true);
		Time end;

		millis_t interval = Time::CalcDeltaMS(end, start);

		//std::cout << "Start: " << start.GetTimeString() << endl;
		//std::cout << "End: " << end.GetTimeString() << endl;
		//std::cout << interval << std::endl;
		BOOST_REQUIRE(interval >= sleeps[i]);
	}
}

BOOST_AUTO_TEST_CASE(TimeConstruction)
{
	for(int i = 0; i < 1000; i++)
		Time t;
}

BOOST_AUTO_TEST_CASE(ReadSystemTime)
{
	Time t; //default value is NOW
	int sleepTime = 2000;
	Thread::SleepFor(sleepTime, true); 	//let's sleep for a few seconds
	boost::int64_t elapsed = t.GetElapsedMS(); //now let's verify that close to this amount of time has elapsed

	BOOST_REQUIRE(elapsed >= sleepTime);
}
BOOST_AUTO_TEST_CASE(CheckInstantElapsed)
{
	Time t;

	boost::int64_t diff = t.GetElapsedMS();

	BOOST_REQUIRE_EQUAL( diff , 0 );
}
BOOST_AUTO_TEST_CASE(CheckMonotononicallyIncreasing)
{
	//check that subsequent calls to GetElapsed() allways return increasing numbers
	Time t;
	boost::int64_t lastElapsed = t.GetElapsedMS();
	boost::int64_t elapsed;

	for(int i = 0; i < 200; i++) {
		for(int j = 0; j < 1000; j++) {
			elapsed = t.GetElapsedMS();
			if(elapsed < lastElapsed) {
				ostringstream oss;
				oss << "Time Elapsed didn't increase " << elapsed << " < " << lastElapsed;
				std::cout << oss.str() << std::endl;
				BOOST_REQUIRE(elapsed >= lastElapsed);
			}
			else {
				lastElapsed = elapsed;
			}
		}
	}
}

BOOST_AUTO_TEST_CASE(SetTime)
{
	Time t;
	boost::int64_t time = t.GetValueMS();
	t.SetTo(t.GetValueMS() + 5000); //set to five seconds in the future

	time = t.GetValueMS() - time;

	BOOST_REQUIRE_EQUAL(time, 5000);
}

BOOST_AUTO_TEST_CASE(AddTime)
{
	Time t;
	boost::int64_t time = t.GetValueMS();
	t.AddMS(5000);

	time = t.GetValueMS() - time;

	BOOST_REQUIRE_EQUAL(time, 5000);
}

BOOST_AUTO_TEST_CASE(Operators)
{
	Time t1(1000);
	Time t2(900);

	BOOST_REQUIRE(t2 < t1);
	BOOST_REQUIRE( !(t1 < t2) );
	BOOST_REQUIRE( t2 <= t1 );
	BOOST_REQUIRE( t1 >= t2 );

	BOOST_REQUIRE(t1 == t1);
	BOOST_REQUIRE(t2 == t2);
	BOOST_REQUIRE(t1 <= t1);
	BOOST_REQUIRE(t2 <= t2);
	BOOST_REQUIRE(t1 >= t1);
	BOOST_REQUIRE(t2 >= t2);

}

BOOST_AUTO_TEST_CASE(MaxMin)
{
	Time tmin = Time::Min;
	Time tmax = Time::Max;

	BOOST_REQUIRE(tmin < tmax);
	BOOST_REQUIRE(tmax > tmin);
	BOOST_REQUIRE(tmin <= tmax);
	BOOST_REQUIRE(tmax >= tmin);
	BOOST_REQUIRE( !(tmin == tmax) );
	BOOST_REQUIRE(tmin == tmin);
	BOOST_REQUIRE(tmax == tmax);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TimeoutTests)
BOOST_AUTO_TEST_CASE(AllParams)
{
	//create a timeout of 1 millisecond
	Timeout to(1);

	//check that the timeout starts out unexpired
	BOOST_REQUIRE_EQUAL(to.IsExpired(false), false);
	BOOST_REQUIRE_EQUAL(to.Remaining(false), 1);

	//sleep for atleast 1 milli
	Thread::SleepFor(1, true);

	//make sure that it is still unexpired since we have overridden
	//the "UpdateTimeout" to false which means it won't believe it
	//has expired even though enough time has passed
	BOOST_REQUIRE_EQUAL(to.IsExpired(false), false);
	BOOST_REQUIRE_EQUAL(to.Remaining(false), 1);

	//once we call IsExpired(true) it will update its remaining time
	//and therefore think it is expired
	BOOST_REQUIRE_EQUAL(to.IsExpired(true), true);
	BOOST_REQUIRE_EQUAL(to.Remaining(false), 0);

	//we will reset the timeout to another millisecond
	to.Reset(1);

	//check that the reset worked and its unexpired
	BOOST_REQUIRE_EQUAL(to.IsExpired(false), false);
	BOOST_REQUIRE_EQUAL(to.Remaining(false), 1);

	//sleep long enough to trip the state
	Thread::SleepFor(1, true);

	//check that its symettric if we call to.Remaing(true) it
	//will return 0 and isexpired will return true
	BOOST_REQUIRE_EQUAL(to.Remaining(true), 0);
	BOOST_REQUIRE_EQUAL(to.IsExpired(false), true);
}

BOOST_AUTO_TEST_CASE(DefaultArguments)
{
	//create a timeout of 1 millisecond
	Timeout to(1);

	//check that its not expired
	BOOST_REQUIRE_EQUAL(to.IsExpired(false), false);
	BOOST_REQUIRE_EQUAL(to.Remaining(false), 1);

	//sleep for a mill
	Thread::SleepFor(1, true);

	//check that the remaining still says 1
	BOOST_REQUIRE_EQUAL(to.Remaining(), 1);

	//check that once we ask if it is expired it tells us we are and have no time remaining.
	BOOST_REQUIRE_EQUAL(to.IsExpired(), true);
	BOOST_REQUIRE_EQUAL(to.Remaining(), 0);
}

BOOST_AUTO_TEST_CASE(ExampleLoop)
{
	StopWatch t;
	Timeout to(250);

	do {
		Thread::SleepFor(rand() % to.Remaining());
	}
	while(!to.IsExpired());

	BOOST_REQUIRE(t.Elapsed() >= 250);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(StopWatchTests)

BOOST_AUTO_TEST_CASE(BasicTest)
{
	StopWatch sw;

	//show that the stopwatch start at 0 (may be 1 almost instantly in current implementation)
	BOOST_REQUIRE(sw.Elapsed(false) <= 1);

	//sleep for 5 millis
	Thread::SleepFor(5, true);

	//make sure the stopwatch recorded atleast 5 millis elapsed (override default bool)
	BOOST_REQUIRE(sw.Elapsed(false) >= 5);

	//check that the value wasn't reset and that if aReset==true the next call restarts
	//the stopwatch
	BOOST_REQUIRE(sw.Elapsed(true) >= 5);
	BOOST_REQUIRE(sw.Elapsed(false) <= 1);

	//sleep again
	Thread::SleepFor(5, true);

	//check that the elapsed time is correct
	BOOST_REQUIRE(sw.Elapsed(false) >= 5);

	//restart the stopwatch and make sure that the elapsed time gets back to 0
	sw.Restart();
	BOOST_REQUIRE(sw.Elapsed(false) <= 1);
}

BOOST_AUTO_TEST_CASE(ExampleUsage)
{
	StopWatch sw;
	Thread::SleepFor(5);  //should take 5 mills but may take less
	millis_t sleep1 = sw.Elapsed(); //automatic restart of stopwatch (like a split)
	Thread::SleepFor(5, true); //will take atleast 5 mills
	millis_t sleep2 = sw.Elapsed(); //should be around 5 millis
	BOOST_REQUIRE(sleep1 >= 0);
	BOOST_REQUIRE(sleep2 >= 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TimeStampTests)
BOOST_AUTO_TEST_CASE(TimeStampOperations)
{
	//get current time stamp
	TimeStamp_t now = TimeStamp::GetTimeStamp();

	//get a timestamp for 2 milliseconds in the future
	TimeStamp_t laterGuess = TimeStamp::GetTimeStamp(2);

	//actually sleep for 2 milliseconds
	Thread::SleepFor(2, true);

	//get another timestamp
	TimeStamp_t later = TimeStamp::GetTimeStamp();

	//check that it is a difference of 2 milliseconds from our original stamp
	millis_t difference = later - now;
	BOOST_REQUIRE(difference >= 2);

	//check that is equal to our "future" stamp
	millis_t difference2 = laterGuess - later;
	BOOST_REQUIRE(difference > difference2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TimeManagerTests)
BOOST_AUTO_TEST_CASE(TimeSourceSystemOffsetTest)
{

	TimeSourceSystemOffset time;
	millis_t base = time.GetTime();
	time.SetTime(base + 5000);
	BOOST_REQUIRE(time.GetTime() >= base + 5000);
}
BOOST_AUTO_TEST_CASE(TimeSourceSystemOffsetTestNeg)
{

	TimeSourceSystemOffset time;
	millis_t base = time.GetTime();
	time.SetTime(base - 5000);
	BOOST_REQUIRE(time.GetTime() >= base - 5000);
}
BOOST_AUTO_TEST_SUITE_END()
