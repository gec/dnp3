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
#ifndef __ASYNC_TASK_GROUP_H_
#define __ASYNC_TASK_GROUP_H_

#include <opendnp3/APL/AsyncTaskInterfaces.h>
#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/Uncopyable.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <queue>
#include <set>

namespace apl
{

class AsyncTaskBase;
class AsyncTaskPeriodic;
class AsyncTaskNonPeriodic;
class AsyncTaskContinuous;
class AsyncTaskScheduler;
class ITimerSource;
class ITimeSource;
class ITimer;

/**
 A collection of related tasks with optional dependencies
*/
class AsyncTaskGroup : private Uncopyable
{
	friend class AsyncTaskBase;
	friend class AsyncTaskContinuous;
	friend class AsyncTaskScheduler;

public:

	~AsyncTaskGroup();

	AsyncTaskBase* Add(millis_t aPeriod, millis_t aRetryDelay, int aPriority, const TaskHandler& arCallback, const std::string& arName = "");
	AsyncTaskContinuous* AddContinuous(int aPriority, const TaskHandler& arCallback, const std::string& arName = "");
	void Remove(AsyncTaskBase* apTask);

	void Shutdown();

	void Enable();
	void Disable();

	void Enable(int aMask);
	void Disable(int aMask);

	void ResetTasks(int aMask);

	void CheckState();

	bool IsRunning() {
		return mIsRunning;
	}

	boost::posix_time::ptime GetUTC() const;

private:

	void OnCompletion();
	void RestartTimer(const boost::posix_time::ptime& arTime);
	void OnTimerExpiration();
	void Update(const boost::posix_time::ptime& arTime);
	AsyncTaskBase* GetNext(const boost::posix_time::ptime& arTime);

	bool mIsRunning;
	bool mShutdown;
	ITimerSource* mpTimerSrc;
	ITimeSource* mpTimeSrc;
	ITimer* mpTimer;

	AsyncTaskGroup(ITimerSource*, ITimeSource*);

	typedef std::vector< AsyncTaskBase* > TaskVec;
	TaskVec mTaskVec;
};

}

#endif
