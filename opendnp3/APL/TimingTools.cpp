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

#ifdef max
#undef max
#endif

#include <opendnp3/APL/TimingTools.h>

namespace apl
{

///////////////////////////////////////////////
//	StopWatch
///////////////////////////////////////////////

apl::millis_t StopWatch :: Elapsed(bool aReset)
{
	apl::millis_t ret = mStartTime.GetElapsedMS();
	if(aReset) mStartTime.SetToNow();
	return ret;
}

void StopWatch :: Restart()
{
	mStartTime.SetToNow();
}

///////////////////////////////////////////////
//	TimeStamp
///////////////////////////////////////////////

//millis_t TimeStamp :: mOffset = TimeStamp::UTCUnset;

//StaticSubject TimeStamp :: mTimeNotifier ;

const TimeStamp_t TimeStamp::MAX = std::numeric_limits<TimeStamp_t>::max();
const TimeStamp_t TimeStamp::MIN = std::numeric_limits<TimeStamp_t>::min();

TimeStamp_t TimeStamp :: GetTimeStamp(const millis_t aInFuture)
{
	Time dt; // need faster calls
	return (TimeStamp_t)(dt.GetValueMS() + aInFuture);
}

UTCTimeStamp_t TimeStamp :: GetUTCTimeStamp(const millis_t aInFuture)
{
	Time dt; // need faster calls
	return (UTCTimeStamp_t) (dt.GetValueMS() + aInFuture);
}

std::string TimeStamp :: UTCTimeStampToString(const UTCTimeStamp_t aTime)
{
	Time dt; // need faster calls
	dt.SetTo(aTime);
	return dt.GetTimeString();
}

}
