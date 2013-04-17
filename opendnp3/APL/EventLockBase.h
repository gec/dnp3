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
#ifndef __EVENT_LOCK_BASE_H_
#define __EVENT_LOCK_BASE_H_

#include <opendnp3/APL/IEventLock.h>
#include <opendnp3/APL/Lock.h>
#include <opendnp3/APL/Notifier.h>

#include <vector>

namespace apl
{

/** Inherited classes are free to define how the event code/mask gets recorded and presented
	to thread receiving the event alert.
*/

template<class T>
class EventLockBase : public IEventLock<T>, public SigLock
{
public:

	EventLockBase();
	virtual ~EventLockBase();

	// Implement the IEventLock<T> interface
	void SignalEvent(const T& arEvent);
	void BroadcastEvent(const T& arEvent);

	INotifier* GetNotifier(const T& arEvent);

protected:

	// Inherited classes must implement the following
	virtual void RecordEventCode(const T& arEvent) = 0;

private:
	std::vector< Notifier<T>* > mNotifiers;
};

template<class T>
EventLockBase<T>::EventLockBase() :
	SigLock()
{}

template<class T>
EventLockBase<T>::~EventLockBase()
{
	for(size_t i = 0; i < mNotifiers.size(); i++) delete mNotifiers[i];
}

template<class T>
void EventLockBase<T>::SignalEvent(const T& arEvent)
{
	CriticalSection cs(this);
	this->RecordEventCode(arEvent);
	SigLock::Signal();
}

template<class T>
void EventLockBase<T>::BroadcastEvent(const T& arEvent)
{
	CriticalSection cs(this);
	this->RecordEventCode(arEvent);
	SigLock::Broadcast();
}

template<class T>
INotifier* EventLockBase<T>::GetNotifier(const T& arEvent)
{
	Notifier<T>* pNotifier = new Notifier<T>(arEvent, this);
	mNotifiers.push_back(pNotifier);
	return pNotifier;
}





}

#endif
