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
#ifndef __EVENT_SET_H_
#define __EVENT_SET_H_

#include <opendnp3/APL/Types.h>

#include <queue>

namespace apl
{

class EventSet
{
public:

	EventSet(boost::int64_t aEventFlags) {
		const int64_t ONE = static_cast<boost::int64_t>(1);

		for(size_t i = 0; i < 64; i++) {
			if( (aEventFlags & (ONE << i)) != 0) mEvents.push(i);
		}
	}

	inline bool HasEvents() {
		return mEvents.size() != 0;
	}

	inline size_t GetNextEvent() {
		assert(HasEvents());

		size_t ret = mEvents.front();
		mEvents.pop();
		return ret;
	}

private:

	std::queue<size_t> mEvents;

};

}

#endif

