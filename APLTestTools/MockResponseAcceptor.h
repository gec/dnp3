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
#ifndef __MOCK_RESPONSE_ACCEPTOR_H_
#define __MOCK_RESPONSE_ACCEPTOR_H_


#include <queue>
#include <opendnp3/APL/CommandTypes.h>
#include <opendnp3/APL/CommandInterfaces.h>
#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/Lock.h>

namespace apl
{
struct MockResponse {
	MockResponse(const apl::CommandResponse& aResponse, int aSequence) :
		Response(aResponse),
		Sequence(aSequence)
	{}

	apl::CommandResponse Response;
	int Sequence;
};

class MockResponseAcceptor : public apl::IResponseAcceptor
{
public:

	void AcceptResponse(const apl::CommandResponse& aResponse, int aSequence);

	MockResponse PopResponse();
	size_t NumResponses();

private:
	apl::SigLock mLock;
	std::deque<MockResponse> mResponses;
};
}

#endif
