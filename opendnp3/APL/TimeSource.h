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
#ifndef __TIME_SOURCE_H_
#define __TIME_SOURCE_H_

#include <opendnp3/APL/ITimeSource.h>
#include <opendnp3/APL/Singleton.h>
#include <opendnp3/APL/Types.h>

#include <boost/date_time/posix_time/ptime.hpp>

namespace apl
{
class TimeSource : public ITimeSource
{
	MACRO_SINGLETON_INSTANCE(TimeSource)

	// Implement ITimeSource
	boost::posix_time::ptime GetUTC();
	TimeStamp_t GetTimeStampUTC();
};

class MockTimeSource : public ITimeSource
{
public:

	MockTimeSource();

	// Implement ITimeSource
	boost::posix_time::ptime GetUTC() {
		return mTime;
	}
	TimeStamp_t GetTimeStampUTC();

	void SetTime(const boost::posix_time::ptime& arTime) {
		mTime = arTime;
	}
	void SetTime(TimeStamp_t aTime);
	void Advance(millis_t aDuration);
	void SetToNow();

private:

	boost::posix_time::ptime mTime;
};

/** Maintains an external time by keeping an offset from system time.
*/
class TimeSourceSystemOffset : public  ITimeManager
{
public:
	TimeSourceSystemOffset();

	millis_t GetTime();
	void SetTime(millis_t aTime);
private:
	boost::int64_t mOffset;
};

class MockTimeManager : public ITimeManager
{
public:
	MockTimeManager() : mTime(0) {}
	millis_t GetTime() {
		return mTime;
	}
	void SetTime(millis_t aTime) {
		mTime = aTime;
	}
private:
	millis_t mTime;
};
}

#endif

