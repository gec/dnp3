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

#ifndef __LOG_ENTRY_CIRCULAR_BUFFER_H_
#define __LOG_ENTRY_CIRCULAR_BUFFER_H_

#include <opendnp3/APL/EventLock.h>
#include <opendnp3/APL/LogBase.h>
#include <opendnp3/APL/LogEntry.h>
#include <opendnp3/APL/SubjectBase.h>
#include <opendnp3/APL/Uncopyable.h>

#include <assert.h>
#include <deque>

namespace apl
{

class LogEntryCircularBuffer : public ILogBase, public SubjectBase<SigLock>, private Uncopyable
{
public:
	LogEntryCircularBuffer(size_t aMaxEntries = 100);

	bool ReadLog(LogEntry&, int aTimeout = 0);
	void SetMaxEntries(size_t aMax);
	void Log( const LogEntry& arEntry );
	void SetVar(const std::string& aSource, const std::string& aVarName, int aValue) {}
	size_t Count();
	void AddIgnoreCode(int aCode);

protected:
	void BlockUntilEntry();
	SigLock mLock;

private:
	bool CheckRead(LogEntry& aEntry);
	size_t mMaxEntries;
	std::deque<LogEntry> mItemQueue;
	std::set<int> mIgnoreCodes;
};

}
#endif
