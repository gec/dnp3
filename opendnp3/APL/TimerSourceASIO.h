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
#ifndef __TIMER_SOURCE_ASIO_H_
#define __TIMER_SOURCE_ASIO_H_

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/ITimerSource.h>
#include <opendnp3/APL/Lock.h>

#include <queue>

namespace boost
{

namespace asio
{
class io_service;
}
namespace system
{
class error_code;
}

}

namespace apl
{

class TimerASIO;
class AsyncResult;

class TimerSourceASIO : public ITimerSource
{

public:
	TimerSourceASIO(boost::asio::io_service*);
	~TimerSourceASIO();

	ITimer* Start(millis_t, const FunctionVoidZero&);
	ITimer* Start(const boost::posix_time::ptime&, const FunctionVoidZero&);
	void Post(const FunctionVoidZero&);
	void PostSync(const FunctionVoidZero&);

private:

	static void SafeExecute(const FunctionVoidZero&, AsyncResult* apResult);
	static void Rethrow(const Exception& arException);

	TimerASIO* GetTimer();
	void StartTimer(TimerASIO*, const FunctionVoidZero&);

	boost::asio::io_service* mpService;

	typedef std::deque<TimerASIO*> TimerQueue;

	TimerQueue mAllTimers;
	TimerQueue mIdleTimers;

	void OnTimerCallback(const boost::system::error_code&, TimerASIO*, FunctionVoidZero);
};
}

#endif

