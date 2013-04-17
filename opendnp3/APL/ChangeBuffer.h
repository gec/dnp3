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
#ifndef __CHANGE_BUFFER_H_
#define __CHANGE_BUFFER_H_

#include <opendnp3/APL/DataInterfaces.h>
#include <opendnp3/APL/DataTypes.h>
#include <opendnp3/APL/INotifier.h>
#include <opendnp3/APL/SubjectBase.h>
#include <opendnp3/APL/TimingTools.h>

#include <queue>

namespace apl
{

/** Moves measurement data across thread boundaries.
*/
template <class LockType>
class ChangeBuffer : public IDataObserver, public SubjectBase<NullLock>
{

	typedef std::deque< Change<Binary> > BinaryQueue;
	typedef std::deque< Change<Analog> > AnalogQueue;
	typedef std::deque< Change<Counter> > CounterQueue;
	typedef std::deque< Change<ControlStatus> > ControlStatusQueue;
	typedef std::deque< Change<SetpointStatus> > SetpointStatusQueue;

public:

	ChangeBuffer() : mMidFlush(false) {}

	void _Start() {
		mLock.Lock();
	}
	void _End() {

		if ( mMidFlush ) {
			_Clear();
			mMidFlush = false;
		}

		bool notify = this->HasChanges();
		mLock.Unlock();
		if(notify) this->NotifyAll();
	}

	void _Update(const Binary& arPoint, size_t aIndex) {
		mBinaryQueue.push_back(Change<Binary>(arPoint, aIndex));
	}
	void _Update(const Analog& arPoint, size_t aIndex) {
		mAnalogQueue.push_back(Change<Analog>(arPoint, aIndex));
	}
	void _Update(const Counter& arPoint, size_t aIndex) {
		mCounterQueue.push_back(Change<Counter>(arPoint, aIndex));
	}
	void _Update(const ControlStatus& arPoint, size_t aIndex) {
		mControlStatusQueue.push_back(Change<ControlStatus>(arPoint, aIndex));
	}
	void _Update(const SetpointStatus& arPoint, size_t aIndex) {
		mSetpointStatusQueue.push_back(Change<SetpointStatus>(arPoint, aIndex));
	}


	size_t FlushUpdates(apl::IDataObserver* apObserver, bool aClear = true);

	void Clear() {
		assert(this->InProgress());
		_Clear();
	}

private:

	void _Clear() {
		mBinaryQueue.clear();
		mAnalogQueue.clear();
		mCounterQueue.clear();
		mControlStatusQueue.clear();
		mSetpointStatusQueue.clear();
	}

	bool HasChanges() {
		return mBinaryQueue.size() > 0 ||
		       mAnalogQueue.size() > 0 ||
		       mCounterQueue.size() > 0 ||
		       mControlStatusQueue.size() > 0 ||
		       mSetpointStatusQueue.size() > 0;
	}

	template<class T>
	size_t FlushUpdates(const T& arContainer, IDataObserver* apObserver);

	bool mMidFlush;
	BinaryQueue mBinaryQueue;
	AnalogQueue mAnalogQueue;
	CounterQueue mCounterQueue;
	ControlStatusQueue mControlStatusQueue;
	SetpointStatusQueue mSetpointStatusQueue;

	LockType mLock;
};

template <class LockType>
size_t ChangeBuffer<LockType>::FlushUpdates(apl::IDataObserver* apObserver, bool aClear)
{
	Transaction tr(this);
	size_t count = 0;
	if(!this->HasChanges()) return count;

	{
		Transaction t(apObserver);
		mMidFlush = true;	// Will clear on transaction end if an observer call blows up
		count += this->FlushUpdates(mBinaryQueue, apObserver);
		count += this->FlushUpdates(mAnalogQueue, apObserver);
		count += this->FlushUpdates(mCounterQueue, apObserver);
		count += this->FlushUpdates(mControlStatusQueue, apObserver);
		count += this->FlushUpdates(mSetpointStatusQueue, apObserver);
		mMidFlush = false;
	}

	if(aClear) this->Clear();

	return count;
}

template <class LockType>
template <class T>
size_t ChangeBuffer<LockType>::FlushUpdates(const T& arContainer, IDataObserver* apObserver)
{
	size_t count = 0;
	for(typename T::const_iterator i = arContainer.begin(); i != arContainer.end(); ++i) {
		apObserver->Update(i->mValue, i->mIndex);
		++count;
	}
	return count;
}

}

#endif
