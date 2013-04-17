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
#ifndef __EVENT_LOCK_H_
#define __EVENT_LOCK_H_

#include <opendnp3/APL/EventLockBase.h>
#include <opendnp3/APL/Types.h>

namespace apl
{

/** Uses a 64-bit mask implementation of EventLockBase
*/
class EventLock : public EventLockBase<boost::int64_t>
{
public:
	EventLock();

	//needs to be used only when we are allready locked on the object
	boost::int64_t GetEvents(bool aClearSentEvents = true);

	static boost::int64_t Get64BitMask(size_t aShift);

protected:

	boost::int64_t mEvents; //the bitfield that holds the events.

private:

	void RecordEventCode(const boost::int64_t& arEvent);
};


}

#endif
