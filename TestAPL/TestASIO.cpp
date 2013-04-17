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
#include <opendnp3/APL/Configure.h>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <opendnp3/APL/Types.h>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::system;
using namespace apl;


void AssertCanceled(bool* apFlag, const boost::system::error_code& ec)
{
	if(ec) *apFlag = true;
}

void Cancel(deadline_timer* aptimer)
{
	aptimer->cancel();
}

BOOST_AUTO_TEST_SUITE(TestBoostASIO)

BOOST_AUTO_TEST_CASE(TimerCancel)
{
	bool flag = false;

	io_service io;
	deadline_timer t1(io, posix_time::seconds(0));
	deadline_timer t2(io, posix_time::seconds(1000));

	t1.async_wait(boost::bind(Cancel, &t2));
	t2.async_wait(boost::bind(AssertCanceled, &flag, _1));

	io.run();

	BOOST_REQUIRE(flag);
}

BOOST_AUTO_TEST_SUITE_END()

