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
#ifndef __I_LOCK_BASE_H_
#define __I_LOCK_BASE_H_

#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/Uncopyable.h>

#include <assert.h>
#include <stddef.h>

namespace apl
{

/** Defines an interface for a thread-safe lock
	The lock implements both Mutex and Condition functionality
*/
class ILockBase
{
public:
	virtual ~ILockBase() {}
	virtual void Lock() = 0;	// gain exclusivity to the lock
	virtual void Unlock() = 0;	// release exclusivity
	virtual void Wait() = 0;	//wait forever for condition to be satisfied
	virtual bool TimedWait(apl::millis_t aMillisec) = 0; //wait for a number of milliseconds
	virtual void Signal() = 0;	  //wakes a single thread waiting on the lock
	virtual void Broadcast() = 0; //wakes all threads waiting on the lock
};

// this class is for templating purposes for when you want
// to provide the option to use a lock or not in a templated class.
class NullLock : public ILockBase
{
public:
	void Lock() {}
	void Unlock() {}
	void Wait() {}
	bool TimedWait(apl::millis_t /*aMillisec*/) {
		return true;
	}
	void Signal() {}
	void Broadcast() {}
};


/** Lock managing class to make unlock implicit. When using
his construct, exceptions can even be thrown from within critical section. */
class CriticalSection : private Uncopyable
{
public:
	CriticalSection(ILockBase* apLock);
	~CriticalSection();
	void Wait();
	bool TimedWait(apl::millis_t aMillisec);
	void Signal();
	void Broadcast();
	void End();

private:
	bool mIsLocked;
	CriticalSection();
	ILockBase* mpLock;
};

inline void CriticalSection::Wait()
{
	mpLock->Wait();
}
inline bool CriticalSection::TimedWait(apl::millis_t aMillisec)
{
	return mpLock->TimedWait(aMillisec);
}
inline void CriticalSection::Signal()
{
	mpLock->Signal();
}
inline void CriticalSection::Broadcast()
{
	mpLock->Broadcast();
}
inline void CriticalSection::End()
{
	assert(mIsLocked);
	mIsLocked = false;
	mpLock->Unlock();
}

} //end namespace

#endif
