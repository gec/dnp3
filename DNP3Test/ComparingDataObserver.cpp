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
#include "ComparingDataObserver.h"

namespace apl
{

namespace dnp
{

ComparingDataObserver::ComparingDataObserver(Logger* apLogger, FlexibleDataObserver* apObserver) :
	Loggable(apLogger),
	mSameData(false),
	mpObserver(apObserver)
{

}

void ComparingDataObserver::Reset()
{
	CriticalSection cs(&mLock);
	mBinaryMap.clear();
	mAnalogMap.clear();
	mCounterMap.clear();
	mControlStatusMap.clear();
	mSetpointStatusMap.clear();
	mSameData = false;
}

bool ComparingDataObserver::IsSameData()
{
	size_t required = mpObserver->mBinaryMap.size() +
	                  mpObserver->mAnalogMap.size() +
	                  mpObserver->mCounterMap.size();

	size_t actual = mBinaryMap.size() +
	                mAnalogMap.size() +
	                mCounterMap.size();

	LOG_BLOCK(LEV_EVENT, actual << " of " << required);

	return (required == actual);

}

bool ComparingDataObserver::WaitForSameData(millis_t aWaitMs)
{
	CriticalSection cs(&mLock);
	if(!mSameData) cs.TimedWait(aWaitMs);
	return mSameData;
}

void ComparingDataObserver::DescribeMissingData()
{
	this->DescribeAny<Binary>(mpObserver->mBinaryMap, mBinaryMap);
	this->DescribeAny<Analog>(mpObserver->mAnalogMap, mAnalogMap);
	this->DescribeAny<Counter>(mpObserver->mCounterMap, mCounterMap);
}

void ComparingDataObserver::_Start()
{
	mLock.Lock();
}

void ComparingDataObserver::_End()
{
	if(this->IsSameData()) {
		mSameData = true;
		mLock.Broadcast();
	}
	mLock.Unlock();

}

void ComparingDataObserver::_Update(const Binary& arPoint, size_t aIndex)
{
	this->UpdateAny<Binary>(arPoint, aIndex, mpObserver->mBinaryMap, mBinaryMap);
}

void ComparingDataObserver::_Update(const Analog& arPoint, size_t aIndex)
{
	this->UpdateAny<Analog>(arPoint, aIndex, mpObserver->mAnalogMap, mAnalogMap);
}

void ComparingDataObserver::_Update(const Counter& arPoint, size_t aIndex)
{
	this->UpdateAny<Counter>(arPoint, aIndex, mpObserver->mCounterMap, mCounterMap);
}

void ComparingDataObserver::_Update(const ControlStatus& arPoint, size_t aIndex)
{
	this->UpdateAny<ControlStatus>(arPoint, aIndex, mpObserver->mControlStatusMap, mControlStatusMap);
}

void ComparingDataObserver::_Update(const SetpointStatus& arPoint, size_t aIndex)
{
	this->UpdateAny<SetpointStatus>(arPoint, aIndex, mpObserver->mSetpointStatusMap, mSetpointStatusMap);
}

}

}

