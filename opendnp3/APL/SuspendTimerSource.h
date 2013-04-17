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

#ifndef __SUSPEND_TIMER_SOURCE_H_
#define __SUSPEND_TIMER_SOURCE_H_

#include <opendnp3/APL/ITransactable.h>
#include <opendnp3/APL/Lock.h>

namespace apl
{

class ITimerSource;

/**
*  Pauses execution of the thread driving a TimerSource. Uses the ITransactable RAII
*  pattern to guarantee that that the resource is released if an uncaught
*  exception is thrown
*
*/
class SuspendTimerSource : public ITransactable
{
public:
	SuspendTimerSource(ITimerSource* apTimerSource);

private:

	void Pause();
	void _Start();
	void _End();

	ITimerSource* mpTimerSource;
	bool mPausing;
	bool mIsPaused;
	SigLock mLock;
};


}
/* vim: set ts=4 sw=4: */

#endif
