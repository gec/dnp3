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
#include <opendnp3/APL/TimeSource.h>
#include <opendnp3/APL/TimingTools.h>

using namespace boost::posix_time;

namespace apl
{

//real time source

TimeSource TimeSource::mInstance;

ptime TimeSource::GetUTC()
{
	return microsec_clock::universal_time();
}

TimeStamp_t TimeSource::GetTimeStampUTC()
{
	return TimeStamp::GetTimeStamp();
}

//mock time source
MockTimeSource::MockTimeSource() :
	mTime(min_date_time)
{

}

void MockTimeSource::SetTime(TimeStamp_t aTime)
{
	mTime = TimeBoost::GetPTimeFromMS(aTime);
}

TimeStamp_t MockTimeSource::GetTimeStampUTC()
{
	TimeBoost t(mTime); TimeStamp_t ret(t.GetValueMS()); return ret;
}

void MockTimeSource::Advance(millis_t aDuration)
{
	mTime += milliseconds(aDuration);
}

void MockTimeSource::SetToNow()
{
	mTime = microsec_clock::universal_time();
}


TimeSourceSystemOffset::TimeSourceSystemOffset()
	: mOffset(0)
{
}


millis_t TimeSourceSystemOffset::GetTime()
{
	return TimeStamp::GetTimeStamp() + mOffset;
}
void TimeSourceSystemOffset::SetTime(millis_t aTime)
{
	mOffset = aTime - TimeStamp::GetTimeStamp();
}

}
