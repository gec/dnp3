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
#ifndef _TIME_BOOST_H_
#define _TIME_BOOST_H_

#include <opendnp3/APL/Configure.h>
#include <opendnp3/APL/Types.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <string>

//undef some of the evil macros brought in by windows
#undef GetMessage
#undef max
#undef min

using namespace boost::posix_time;
namespace apl
{

class TimeBoost
{
public:

	TimeBoost();
	TimeBoost(apl::millis_t aTime);
	TimeBoost(ptime aTime);
	~TimeBoost();

	void SetToNow();

	apl::millis_t GetElapsedMS() const;

	void SetTo(millis_t aTimeMS);

	void AddMS(millis_t aAddMS);
	boost::int64_t GetValueMS() const;

	static millis_t CalcDeltaMS(const TimeBoost& now, const TimeBoost& start);
	static ptime GetPTimeFromMS(millis_t aTimeMS);

	static const TimeBoost Max;
	static const TimeBoost Min;

	friend class TimeStamp;

	bool operator <(const TimeBoost& arRHS) {
		return mTime < arRHS.mTime;
	}
	bool operator <=(const TimeBoost& arRHS) {
		return mTime <= arRHS.mTime;
	}
	bool operator >(const TimeBoost& arRHS) {
		return mTime > arRHS.mTime;
	}
	bool operator >=(const TimeBoost& arRHS) {
		return mTime >= arRHS.mTime;
	}
	bool operator ==(const TimeBoost& arRHS) {
		return mTime == arRHS.mTime;
	}

	std::string GetTimeString() const;

private:

	ptime mTime;

	static boost::gregorian::date msEpochDate;
	static ptime msEpoch;
};

/*
bool operator <(const TimeBoost& arLHS, const TimeBoost& arRHS);
bool operator <=(const TimeBoost& arLHS, const TimeBoost& arRHS);
bool operator >(const TimeBoost& arLHS, const TimeBoost& arRHS);
bool operator >=(const TimeBoost& arLHS, const TimeBoost& arRHS);
bool operator ==(const TimeBoost& arLHS, const TimeBoost& arRHS);
*/

}

#endif
