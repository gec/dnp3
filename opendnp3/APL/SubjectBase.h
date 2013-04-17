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
#ifndef __SUBJECT_BASE_H_
#define __SUBJECT_BASE_H_

#include <opendnp3/APL/INotifier.h>
#include <opendnp3/APL/ISubject.h>
#include <opendnp3/APL/LockBase.h>

#include <set>

namespace apl
{

template <class LockType>
class SubjectBase : public ISubject
{
	typedef std::set<INotifier*> NotifierSet;

public:
	virtual ~SubjectBase() {}

	// implement the ISubject interface
	void AddObserver(INotifier* apNotifier) {
		CriticalSection cs(&mSubjectLock);
		mNotifiers.insert(apNotifier);
	}

	void RemoveObserver(INotifier* apNotifier) {
		CriticalSection cs(&mSubjectLock);
		mNotifiers.erase(apNotifier);
	}

protected:

	void NotifyAll() {
		CriticalSection cs(&mSubjectLock);
		for(NotifierSet::iterator i = mNotifiers.begin(); i != mNotifiers.end(); ++i) {
			(*i)->Notify();
		}
	}

private:
	LockType mSubjectLock;
	NotifierSet mNotifiers;
};

}

#endif
