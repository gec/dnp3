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
#ifndef __MOCK_TIMER_SOURCE_H_
#define __MOCK_TIMER_SOURCE_H_


#include <opendnp3/APL/ITimerSource.h>
#include <map>
#include <queue>

namespace apl
{

class MockTimer;

/** @section desc Test class that doles out MockTimer* */
class MockTimerSource : public ITimerSource
{
	friend class MockTimer;

public:
	MockTimerSource();
	~MockTimerSource();

	// Implement ITimerSource
	ITimer* Start(millis_t, const FunctionVoidZero&);
	ITimer* Start(const boost::posix_time::ptime&, const FunctionVoidZero&);
	void Post(const FunctionVoidZero&);
	void PostSync(const FunctionVoidZero&);

	/** Turns the auto-post feature on/off. When Auto post is on, Post() is executed synchronously */
	void SetAutoPost(bool aAutoPost) {
		this->mPostIsSynchronous = aAutoPost;
	}

	/**	Call the next (by expiration time) without caring about the time requirement.
		@returns true if a timer was dispatched */
	bool DispatchOne();

	/** Calls DispatchOne() up to some maximum number of times continuing while
		there are still events to dispatch

		@return the number of events dispatched
	*/
	size_t Dispatch(size_t aMaximum = std::numeric_limits<size_t>::max());

	/** @returns The number of active, pending timers */
	size_t NumActive() {
		return mTimerMap.size() + mPostQueue.size();
	}

private:

	void Cancel(ITimer* apTimer);

	typedef std::deque<FunctionVoidZero> PostQueue;
	typedef std::multimap<boost::posix_time::ptime, MockTimer*> TimerMap;
	typedef std::deque<MockTimer*> TimerQueue;

	bool mPostIsSynchronous;
	PostQueue mPostQueue;
	TimerMap mTimerMap;
	TimerQueue mIdle;
	TimerQueue mAllTimers;

};

/** @section desc Test timer class used in conjunction with MockTimerSource */
class MockTimer : public ITimer
{
	friend class MockTimerSource;

public:
	MockTimer(MockTimerSource*, const boost::posix_time::ptime&, const FunctionVoidZero&);

	//implement ITimer
	void Cancel();
	boost::posix_time::ptime ExpiresAt();

private:
	boost::posix_time::ptime mTime;
	MockTimerSource* mpSource;
	FunctionVoidZero mCallback;
};

}

#endif

