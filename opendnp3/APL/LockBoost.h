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

#ifndef _LOCK_BOOST_H_
#define _LOCK_BOOST_H_

#include <opendnp3/APL/Configure.h>
#include <opendnp3/APL/LockBase.h>
#include <opendnp3/APL/Uncopyable.h>

#ifdef APL_PLATFORM_WIN
#pragma warning( disable : 4996 )
#ifndef _CRT_SECURE_NO_WARNING
#define _CRT_SECURE_NO_WARNING
#endif
#endif
#include <boost/thread/condition.hpp>
#include <boost/thread/shared_mutex.hpp>

//leave this off
#undef DEBUG_LOCKS

#ifdef DEBUG_LOCKS
#include <boost/thread/tss.hpp>
#endif

namespace apl
{
class SigLock_Boost : public ILockBase, private Uncopyable
{
public:

	SigLock_Boost();
	virtual ~SigLock_Boost();

	////////////////////////////
	// Base class interface functions
	////////////////////////////

	void Lock();
	void Unlock();
	void Wait();
	bool TimedWait(millis_t aMillisec);
	void Signal();
	void Broadcast();

private:

	int mLockCount;
	boost::condition_variable_any mCondition;
	boost::shared_mutex mMutex;
#ifdef DEBUG_LOCKS
	boost::thread_specific_ptr< boost::mutex::scoped_lock > mLockPtr;
#endif
};
};
#endif
