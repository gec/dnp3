// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Energy Corp licenses this file
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

#include "AddressScanner.h"

#include <opendnp3/APL/Logger.h>
#include <APLXML/XMLConversion.h>
#include <XMLBindings/APLXML_MTS.h>

#include <boost/bind.hpp>

namespace apl
{
namespace dnp
{

AddressScanner::AddressScanner(Logger* apLogger, const APLXML_MTS::MasterTestSet_t& cfg, boost::uint16_t start, boost::uint16_t stop) :
	Loggable(apLogger),
	mService(),
	manager(apLogger, mService.Get(), &cfg.PhysicalLayerList, xml::Convert(cfg.Log.Filter)),
	mTimerSrc(mService.Get()),
	mThread(apLogger->GetSubLogger("ioservice"), mService.Get()),
	mRouter(apLogger, manager.AcquireLayer(cfg.PhysicalLayer), &mTimerSrc, 1000),
	mpTimer(NULL),
	mMasterAddr(cfg.Master.Stack.LinkLayer.LocalAddress),
	mScanTimeout(cfg.Master.Stack.LinkLayer.AckTimeoutMS),
	mCurrent(start),
	mStop(stop)
{
	LinkRoute route(cfg.Master.Stack.LinkLayer.RemoteAddress, cfg.Master.Stack.LinkLayer.LocalAddress);
	mRouter.AddContext(this, route);
}

void AddressScanner::OnLowerLayerUp()
{
	this->NextFrame();
}

void AddressScanner::OnLowerLayerDown()
{

}

void AddressScanner::OnTimeout()
{
	LOG_BLOCK(LEV_INFO, "Scan timed out for address: " << mFrame.GetDest());
	mpTimer = NULL;
	this->NextFrame();
}

void AddressScanner::NextFrame()
{
	if(mCurrent >= mStop) mRouter.Shutdown();
	else {
		mpTimer = mTimerSrc.Start(mScanTimeout, boost::bind(&AddressScanner::OnTimeout, this));
		mFrame.FormatResetLinkStates(true, mCurrent, mMasterAddr);
		++mCurrent;
		mRouter.Transmit(mFrame);
	}
}

void AddressScanner::Ack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	LOG_BLOCK(LEV_EVENT, "Received acknowledgement from address: " << aSrc);
	mRouter.Shutdown();
	if(mpTimer != NULL) mpTimer->Cancel();
}

void AddressScanner::Nack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) {}
void AddressScanner::LinkStatus(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) {}
void AddressScanner::NotSupported (bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) {}

void AddressScanner::TestLinkStatus(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc) {}
void AddressScanner::ResetLinkStates(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc) {}
void AddressScanner::RequestLinkStatus(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc) {}
void AddressScanner::ConfirmedUserData(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength) {}
void AddressScanner::UnconfirmedUserData(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength) {}

void AddressScanner::Run()
{
	mRouter.Start();

	LOG_BLOCK(LEV_INFO, "Scanning from " << mCurrent << " to " << mStop);
	mThread.Run();
	LOG_BLOCK(LEV_INFO, "Scan complete...");
}

}
}

