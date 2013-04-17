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
#ifndef __SYNC_VAR_H_
#define __SYNC_VAR_H_

#include <opendnp3/APL/Lock.h>
#include <opendnp3/APL/SubjectBase.h>
#include <opendnp3/APL/Timeout.h>

namespace apl
{
/** Simple single synchronized value that provides notification capabilities.
*/
template <class T>
class SyncVar : public SubjectBase<SigLock>
{
public:

	SyncVar(const T& arInitial) :
		mChange(false),
		mValue(arInitial)
	{}

	SyncVar() :
		mChange(false)
	{}

	virtual ~SyncVar() {}

	bool ChangeSinceRead() {
		return mChange;
	}

	// sets the value to arVal and returns whether the new value == the previous value.
	bool Set(const T& arVal) {
		bool changed;
		{
			CriticalSection cs(&mLock);
			changed = !(mValue == arVal);
			if(changed) {
				mChange = true;
				mLock.Broadcast();
			}
			mValue = arVal;
		}
		if(changed) this->NotifyAll();
		return changed;
	}

	T Get() {
		CriticalSection cs(&mLock);
		mChange = false;
		return mValue;
	}

	bool WaitUntil(const T& arVal, millis_t aTimeout) {
		CriticalSection cs(&mLock);
		if(mValue == arVal) return true;

		if(aTimeout >= 0) {
			Timeout dt(aTimeout);
			while(!dt.IsExpired() && !(mValue == arVal)) mLock.TimedWait(dt.Remaining());
		}
		else {
			while(!(mValue == arVal)) mLock.Wait();
		}

		return (mValue == arVal);
	}

	bool WaitWhile(const T& arVal, millis_t aTimeout) {
		CriticalSection cs(&mLock);
		if(!(mValue == arVal)) return true;

		if(aTimeout >= 0) {
			Timeout dt(aTimeout);
			while(!dt.IsExpired() && (mValue == arVal)) mLock.TimedWait(dt.Remaining());
		}
		else {
			while(mValue == arVal) mLock.Wait();
		}

		return !(mValue == arVal);
	}
protected:
	SigLock mLock;

	bool mChange;
	// protects the variable. The variable may be something may not be atomically writable.
	T mValue;

};


}

#endif
