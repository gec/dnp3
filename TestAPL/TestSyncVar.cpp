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
#include <string>

#include <opendnp3/APL/SyncVar.h>
#include <opendnp3/APL/EventLock.h>
#include <opendnp3/APL/Notifier.h>

using namespace std;
using namespace apl;



BOOST_AUTO_TEST_SUITE(SyncVarSuite)
BOOST_AUTO_TEST_CASE(TestStartupNoChange)
{
	SyncVar<int> val(0);
	BOOST_REQUIRE_FALSE(val.ChangeSinceRead());
}

BOOST_AUTO_TEST_CASE(TestChange)
{
	SyncVar<int> val(0);

	val.Set(0);
	BOOST_REQUIRE_FALSE(val.ChangeSinceRead());

	val.Set(1);
	BOOST_REQUIRE(val.ChangeSinceRead());

	BOOST_REQUIRE_EQUAL(1, val.Get());
	BOOST_REQUIRE_FALSE(val.ChangeSinceRead());
}

BOOST_AUTO_TEST_CASE(TestNotification)
{
	EventLock el;
	Notifier<boost::int64_t> n(4, &el);
	SyncVar<int> val(0);
	val.AddObserver(&n);

	{
		CriticalSection cs(&el);
		el.GetEvents();
	}

	{
		//This should not cause a deadlock b/c the SynvVar should not try to notify b/c the value doesn't change
		CriticalSection cs(&el);
		val.Set(0);
		BOOST_REQUIRE_EQUAL(0, el.GetEvents());
	}

	val.Set(1);

	{
		CriticalSection cs(&el);
		BOOST_REQUIRE_EQUAL(4, el.GetEvents());
		BOOST_REQUIRE_EQUAL(0, el.GetEvents());
	}
}

BOOST_AUTO_TEST_SUITE_END()//end suite

