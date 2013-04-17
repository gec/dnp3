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

#include <opendnp3/APL/TimeBoost.h>
#include <opendnp3/APL/Util.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace apl
{

boost::gregorian::date TimeBoost::msEpochDate = boost::gregorian::date(1970, 1, 1);
ptime TimeBoost::msEpoch = ptime(msEpochDate);
const TimeBoost TimeBoost::Max = ptime(boost::date_time::max_date_time);
const TimeBoost TimeBoost::Min = ptime(boost::date_time::min_date_time);

TimeBoost::TimeBoost()
{
	SetToNow();
}

TimeBoost::TimeBoost(millis_t aTimeMS)
{
	this->SetTo(aTimeMS);
}

TimeBoost::TimeBoost(ptime aTime) :
	mTime(aTime)
{

}

TimeBoost::~TimeBoost()
{

}

void TimeBoost::SetToNow()
{
	ptime t(microsec_clock::universal_time());
	mTime = t;
}

millis_t TimeBoost::GetElapsedMS() const
{
	TimeBoost now;
	return static_cast<millis_t>(((now.mTime - mTime).total_milliseconds()));
}

std::string TimeBoost::GetTimeString() const
{
	return apl::ToNormalizedString(mTime);
}
void TimeBoost::SetTo(millis_t aTimeMS)
{
	mTime = GetPTimeFromMS(aTimeMS);
}

void TimeBoost::AddMS(millis_t aAddMS)
{
	mTime += milliseconds(aAddMS);
}

millis_t TimeBoost::GetValueMS() const
{
	return (mTime - msEpoch).total_milliseconds();
}

millis_t TimeBoost::CalcDeltaMS(const TimeBoost& now, const TimeBoost& start)
{
	return static_cast<millis_t>(((now.mTime - start.mTime).total_milliseconds()));
}

ptime TimeBoost::GetPTimeFromMS(millis_t aTimeMS)
{
	ptime t(msEpochDate, milliseconds(aTimeMS));
	return t;
}
}
