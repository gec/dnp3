/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.  Green Enery
 * Corp licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/IPhysicalLayerAsync.h>
#include <opendnp3/APL/IPhysicalLayerSource.h>
#include <opendnp3/APL/Logger.h>
#include <opendnp3/DNP3/AlwaysOpeningVtoRouter.h>
#include <opendnp3/DNP3/EnhancedVtoRouter.h>
#include <opendnp3/DNP3/VtoRouterManager.h>
#include <opendnp3/DNP3/VtoRouterSettings.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <sstream>

namespace apl
{
namespace dnp
{

RouterRecord::RouterRecord(const std::string& arPortName, boost::shared_ptr<VtoRouter> apRouter, IVtoWriter* apWriter, boost::uint8_t aVtoChannelId) :
	mPortName(arPortName),
	mpRouter(apRouter),
	mpWriter(apWriter),
	mVtoChannelId(aVtoChannelId)
{

}

VtoRouterManager::VtoRouterManager(Logger* apLogger, ITimerSource* apTimerSrc, IPhysicalLayerSource* apPhysSrc) :
	Loggable(apLogger),
	mpTimerSrc(apTimerSrc),
	mpPhysSource(apPhysSrc),
	mSuspendTimerSource(apTimerSrc)
{
	assert(apTimerSrc != NULL);
	assert(apPhysSrc != NULL);
}

VtoRouter* VtoRouterManager::StartRouter(
    const std::string& arPortName,
    const VtoRouterSettings& arSettings,
    IVtoWriter* apWriter)
{
	IPhysicalLayerAsync* pPhys = mpPhysSource->AcquireLayer(arPortName);
	Logger* pLogger = this->GetSubLogger(arPortName, arSettings.CHANNEL_ID);

	boost::shared_ptr<VtoRouter> pRouter;
	if(arSettings.DISABLE_EXTENSIONS) {
		pRouter.reset(new AlwaysOpeningVtoRouter(arSettings, pLogger, apWriter, pPhys, mpTimerSrc));
	}
	else {
		if(arSettings.START_LOCAL) {
			pRouter.reset(new ServerSocketVtoRouter(arSettings, pLogger, apWriter, pPhys, mpTimerSrc));
		}
		else {
			pRouter.reset(new ClientSocketVtoRouter(arSettings, pLogger, apWriter, pPhys, mpTimerSrc));
		}
	}

	RouterRecord record(arPortName, pRouter, apWriter, arSettings.CHANNEL_ID);

	this->mRecords.push_back(record);

	return pRouter.get();
}

std::vector<RouterRecord> VtoRouterManager::GetAllRouters()
{
	std::vector<RouterRecord> ret;
	for(size_t i = 0; i < mRecords.size(); ++i) ret.push_back(mRecords[i]);
	return ret;
}

void VtoRouterManager::StopRouter(IVtoWriter* apWriter, boost::uint8_t aVtoChannelId)
{
	VtoRouter* pRouter = this->GetRouterOnWriter(apWriter, aVtoChannelId).mpRouter.get();
	this->StopRouter(pRouter, apWriter);
}

void VtoRouterManager::StopAllRoutersOnWriter(IVtoWriter* apWriter)
{
	RouterRecordVector recs = this->GetAllRoutersOnWriter(apWriter);

	for(RouterRecordVector::iterator i = recs.begin(); i != recs.end(); ++i) {
		this->StopRouter(i->mpRouter.get(), apWriter);
	}
}

std::vector<RouterRecord> VtoRouterManager::GetAllRoutersOnWriter(IVtoWriter* apWriter)
{
	std::vector< RouterRecord > ret;

	for(RouterRecordVector::iterator i = this->mRecords.begin(); i != mRecords.end(); ++i) {
		if(i->mpWriter == apWriter) ret.push_back(*i);
	}

	return ret;
}

RouterRecord VtoRouterManager::GetRouterOnWriter(IVtoWriter* apWriter, boost::uint8_t aVtoChannelId)
{
	for(RouterRecordVector::iterator i = this->mRecords.begin(); i != mRecords.end(); ++i) {
		if(i->mpWriter == apWriter && i->mVtoChannelId == aVtoChannelId) return *i;
	}

	throw ArgumentException(LOCATION, "Router not found for writer on channel");
}


RouterRecordVector::iterator VtoRouterManager::Find(IVtoWriter* apWriter, boost::uint8_t aVtoChannelId)
{
	RouterRecordVector::iterator i = this->mRecords.begin();

	for(; i != mRecords.end(); ++i) {
		if(i->mpWriter == apWriter && i->mVtoChannelId == aVtoChannelId) return i;
	}

	return i;
}

RouterRecordVector::iterator VtoRouterManager::Find(IVtoWriter* apWriter)
{
	RouterRecordVector::iterator i = this->mRecords.begin();

	for(; i != mRecords.end(); ++i) {
		if(i->mpWriter == apWriter) return i;
	}

	return i;
}

void VtoRouterManager::StopRouter(VtoRouter* apRouter, IVtoWriter* apWriter)
{
	for(RouterRecordVector::iterator i = mRecords.begin(); i != mRecords.end(); ++i) {
		if(i->mpRouter.get() == apRouter) {

			{
				Transaction tr(&mSuspendTimerSource);
				apWriter->RemoveVtoCallback(apRouter);
				i->mpRouter->Shutdown();
			}

			i->mpRouter->WaitForShutdown();			  // blocking, when it returns we're done for good
			mpPhysSource->ReleaseLayer(i->mPortName); // release the physical layer
			mRecords.erase(i);						  // erasing from the vector will cause the shared_ptr to delete the VtoRouter*
			return;
		}
	}

	throw ArgumentException(LOCATION, "Router could not be found in vector");
}

Logger* VtoRouterManager::GetSubLogger(const std::string& arId, boost::uint8_t aVtoChannelId)
{
	std::ostringstream oss;
	oss << arId << "-VtoRouterChannel-" << ((int)aVtoChannelId);
	return mpLogger->GetSubLogger(oss.str());
}

}
}
