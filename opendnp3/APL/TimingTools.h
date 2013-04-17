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
#ifndef _TIMINGTOOLS_H__
#define _TIMINGTOOLS_H__

#include <opendnp3/APL/TimeTypes.h>
#include <opendnp3/APL/Timeout.h>
#include <opendnp3/APL/Types.h>

namespace apl
{

/**
	This class is designed to make it easier to do simple timing tests
	and make it easier to replace with better implementation (if one
	presents itself.)
*/
class StopWatch
{
public:

	//get the elapsed time since creation or the last restart
	//by default each call to Elapsed restarts the timer.
	apl::millis_t Elapsed(bool aReset = true);

	//restart or re-zero the StopWatch.
	void Restart();

private:
	apl::Time mStartTime;
};

/** Light-weight alternative to Time class.
*/
class TimeStamp
{
public:
	static TimeStamp_t GetTimeStamp(const millis_t aInFuture = 0);
	static UTCTimeStamp_t GetUTCTimeStamp(const millis_t aInFuture = 0);

	static std::string UTCTimeStampToString(const UTCTimeStamp_t aTime);

	const static TimeStamp_t MAX;
	const static TimeStamp_t MIN;

};
}

#endif
