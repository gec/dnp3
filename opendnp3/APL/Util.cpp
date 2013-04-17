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
#include <algorithm>
#include <assert.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/TimingTools.h>
#include <opendnp3/APL/Util.h>

#ifdef WIN32
#define sscanf sscanf_s
#endif

using namespace std;
using namespace boost::posix_time;

#ifdef APL_PLATFORM_WIN
#define CLEAR_CMD		"cls"
#else
#define CLEAR_CMD		"clear"
#endif

namespace apl
{

std::string Month(int aMonth)
{
	switch(aMonth) {
	case(1): return	"Jan";
	case(2): return "Feb";
	case(3): return "Mar";
	case(4): return "Apr";
	case(5): return "May";
	case(6): return "Jun";
	case(7): return "Jul";
	case(8): return "Aug";
	case(9): return "Sep";
	case(10): return "Oct";
	case(11): return "Nov";
	case(12): return "Dec";
	default: return "Unknown month";
	}
}

std::string ToNormalizedString(const boost::posix_time::ptime& arTime)
{
	ostringstream oss;
	time_duration tod = arTime.time_of_day();
	int year = arTime.date().year();
	int month = arTime.date().month();
	int day = arTime.date().day();
	millis_t millisec = tod.fractional_seconds() / 1000;
	oss.precision(2);
	oss << year << "-" << Month(month) << "-";
	oss << setw(2) << setfill('0') << day << " ";
	oss << setw(2) << setfill('0') << tod.hours() << ":";
	oss << setw(2) << setfill('0') << tod.minutes() << ":";
	oss << setw(2) << setfill('0') << tod.seconds() << ".";
	oss << setw(3) << setfill('0') << millisec;
	return oss.str();
}

void ClearScreen()
{
	/*
	 * Capture the return value, but ignore it.  This prevents a minor
	 * compiler warning on gcc.
	 */
	int err;
	err = system(CLEAR_CMD);
}

double SafeCastInt64ToDouble(boost::int64_t aInput)
{
#if defined(ARM) || defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB)
	// fix for arm compiler bug
	long upper =  (aInput & 0xFFFFFFFF00000000LL) >> 32;
	unsigned long lower = (aInput & 0x00000000FFFFFFFFLL);

	//Shift the upper portion back into the correct range ( e1<<e2 becomes e1 * pow(2.0, e2), in our case pow(2,32)=4294967296)
	double f1 = upper * 4294967296.0;
	double f2 = lower;
	double dblVar = f1 + f2;

	return dblVar;
#else
	return static_cast<double>(aInput);
#endif
}

void toUpperCase(std::string& apStr)
{
	//from http://gethelp.devx.com/techtips/cpp_pro/10min/2002/Oct/10min1002-2.asp
	std::transform(apStr.begin(), apStr.end(), apStr.begin(), (int(*)(int)) toupper);
}
void toLowerCase(std::string& apStr)
{
	//from http://gethelp.devx.com/techtips/cpp_pro/10min/2002/Oct/10min1002-2.asp
	std::transform(apStr.begin(), apStr.end(), apStr.begin(), (int(*)(int)) tolower);
}

}
