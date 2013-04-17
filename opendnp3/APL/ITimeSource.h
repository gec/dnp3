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
#ifndef __I_TIME_SOURCE_H_
#define __I_TIME_SOURCE_H_

#include <opendnp3/APL/Types.h>

namespace boost
{
namespace posix_time
{

class ptime;

}
}

namespace apl
{
class ITimeManager
{
public:
	virtual millis_t GetTime() = 0;
	virtual void SetTime(millis_t aTime) = 0;
};
class ITimeSource
{
public:
	virtual boost::posix_time::ptime GetUTC() = 0;
	virtual TimeStamp_t GetTimeStampUTC() = 0;
};
}

#endif

