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
#ifndef __TIMEOUT_H_
#define __TIMEOUT_H_

#include <opendnp3/APL/TimeTypes.h>
#include <opendnp3/APL/Types.h>

namespace apl
{

// Use this class to simplify writing do loops with a timeout
// it minimizes the number of calls to get datetime and allows
// us to easily replace the implementation later if we find an
// even more effecient way to implement the timeout checking.
//
// Intended Usage:
//
// Timeout to(5000);
// do{
//	  //call some subordinate slow function
//	  bool success = WaitForInput(to.Remaining());
//
//		//do something on success
//		if(success) return or break;
//
//		//or go back around the loop, the next call to
//		//remaining will be guarnteed to be > 0
// }while(!to.IsExpired());
class Timeout
{
public:
	// constuctor, timeout will expire this many mills in the future
	Timeout(apl::millis_t aTimeout);

	// updates the remaing time (by default) and returns whether its expired
	bool IsExpired(bool aUpdateRemaining = true);

	// returns how much time is left (by default since the last IsExpired() call)
	apl::millis_t Remaining(bool aUpdateRemaining = false);

	// reset the Timeout to a new timeout value.
	void Reset(apl::millis_t aTimeout);

	apl::Time ExpiryTime();
	apl::TimeStamp_t ExpiryTimeStamp();

private:

	void UpdateRemaining(); //actually reread the clock.

	apl::millis_t mTimeout;
	apl::millis_t mRemaining;

	apl::Time mExpireTime;

};

}

#endif
