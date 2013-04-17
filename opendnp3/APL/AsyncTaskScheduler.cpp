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
#include <opendnp3/APL/AsyncTaskBase.h>
#include <opendnp3/APL/AsyncTaskGroup.h>
#include <opendnp3/APL/AsyncTaskScheduler.h>
#include <opendnp3/APL/Exception.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <vector>

using namespace std;
using namespace boost;
using namespace boost::posix_time;

namespace apl
{

AsyncTaskScheduler::AsyncTaskScheduler(ITimerSource* apTimerSrc, ITimeSource* apTimeSrc) :
	mpTimerSrc(apTimerSrc),
	mpTimeSrc(apTimeSrc)
{

}

AsyncTaskScheduler::~AsyncTaskScheduler()
{
	BOOST_FOREACH(AsyncTaskGroup * p, mGroupSet) {
		delete p;
	}
}

AsyncTaskGroup* AsyncTaskScheduler::CreateNewGroup()
{
	CriticalSection cs(&mLock);
	AsyncTaskGroup* pGroup = new AsyncTaskGroup(mpTimerSrc, mpTimeSrc);
	mGroupSet.insert(pGroup);
	return pGroup;
}

void AsyncTaskScheduler::ReleaseGroup(AsyncTaskGroup* apGroup)
{
	CriticalSection cs(&mLock);
	GroupSet::iterator i = mGroupSet.find(apGroup);
	if( i != mGroupSet.end() ) {
		delete *i;
		mGroupSet.erase(i);
	}
	else throw ArgumentException(LOCATION, "Group not associated with this scheduler");
}

} //end ns
