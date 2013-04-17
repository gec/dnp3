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

#include "MockPhysicalLayerSource.h"
#include "MockPhysicalLayerAsync.h"

#include <opendnp3/APL/Logger.h>
#include <opendnp3/APL/Exception.h>

namespace apl
{

MockPhysicalLayerSource::MockPhysicalLayerSource(Logger* apLogger, ITimerSource* apTimerSrc) :
	mpLogger(apLogger),
	mpTimerSrc(apTimerSrc)
{

}

MockPhysicalLayerSource::~MockPhysicalLayerSource()
{
	for(MockMap::iterator i = mMockMap.begin(); i != mMockMap.end(); ++i) delete i->second;
}

MockPhysicalLayerAsync* MockPhysicalLayerSource::GetMock(const std::string& arName)
{
	MockMap::iterator i = mMockMap.find(arName);
	return (i == this->mMockMap.end()) ? NULL : i->second;
}

IPhysicalLayerAsync* MockPhysicalLayerSource::AcquireLayer(const std::string& arName)
{
	MockMap::iterator i = mMockMap.find(arName);
	if(i == this->mMockMap.end()) {
		Logger* pLogger = mpLogger->GetSubLogger(arName);
		MockPhysicalLayerAsync* pLayer = new MockPhysicalLayerAsync(pLogger, mpTimerSrc);				
		mMockMap.insert(MockMap::value_type(arName, pLayer));
		return pLayer;
	}
	else throw ArgumentException(LOCATION, "Layer already exists: " + arName);
}

void MockPhysicalLayerSource::ReleaseLayer(const std::string& arName)
{
	MockMap::iterator i = mMockMap.find(arName);
	if(i == this->mMockMap.end()) throw ArgumentException(LOCATION, "Layer does not exist: " + arName);
	else {
		delete i->second;
		this->mMockMap.erase(arName);
	}
}

}


