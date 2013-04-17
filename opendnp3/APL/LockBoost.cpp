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

#include <opendnp3/APL/LockBoost.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace apl
{

SigLock_Boost::SigLock_Boost() : mLockCount(0)
{

}

SigLock_Boost::~SigLock_Boost()
{
#ifdef DEBUG_LOCKS
	//make sure we havn;t missed a lock somewhere
	assert(mLockPtr.get() == NULL);
#endif
	assert(mLockCount == 0);

}

////////////////////////////
// Base class interface functions
////////////////////////////

void SigLock_Boost::Lock()
{
#ifdef DEBUG_LOCKS
	assert(mLockPtr.get() == NULL);
	//we use a thread specific pointer to hold onto our scoped_lock object
	//beyond the life of this functions stack.
	mLockPtr.reset(new boost::mutex::scoped_lock(mMutex, boost::defer_lock));
	mLockPtr.get()->lock();
#endif
	mMutex.lock();
	mLockCount++;
}

void SigLock_Boost::Unlock()
{
#ifdef DEBUG_LOCKS
	//make sure this thread has gotten the lock to the mutex
	assert(mLockPtr.get() != NULL);
#endif

	assert(mLockCount > 0);
	mLockCount--;
	mMutex.unlock();

#ifdef DEBUG_LOCKS
	mLockPtr.get()->unlock();
	delete mLockPtr.release();
#endif

}

void SigLock_Boost::Wait()
{
#ifdef DEBUG_LOCKS
	assert(mLockPtr.get() != NULL);
#endif
	mCondition.wait(mMutex);

}

bool SigLock_Boost::TimedWait(millis_t aMillisec)
{
	boost::posix_time::ptime t(boost::posix_time::microsec_clock::universal_time());
	t += boost::posix_time::milliseconds(aMillisec);

#ifdef DEBUG_LOCKS
	assert(mLockPtr.get() != NULL);
#endif

	return mCondition.timed_wait(mMutex, t);

}

void SigLock_Boost::Signal()
{
#ifdef DEBUG_LOCKS
	assert(mLockPtr.get() != NULL);
#endif
	mCondition.notify_one();
}

void SigLock_Boost::Broadcast()
{
#ifdef DEBUG_LOCKS
	assert(mLockPtr.get() != NULL);
#endif
	mCondition.notify_all();
}


} //end namespace
