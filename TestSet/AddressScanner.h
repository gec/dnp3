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

#ifndef __ADDRESS_SCANNER_H_
#define __ADDRESS_SCANNER_H_

#include <APLXML/PhysicalLayerManagerXML.h>
#include <opendnp3/APL/IOServiceThread.h>
#include <opendnp3/APL/TimerSourceASIO.h>
#include <opendnp3/APL/IOService.h>
#include <opendnp3/APL/Loggable.h>

#include <opendnp3/DNP3/LinkLayerRouter.h>
#include <opendnp3/DNP3/ILinkContext.h>
#include <opendnp3/DNP3/LinkFrame.h>

namespace APLXML_MTS
{
class MasterTestSet_t;
}
namespace apl
{
class Logger;
}
namespace boost
{
namespace asio
{
class io_service;
}
}

namespace apl
{
namespace dnp
{

class AddressScanner : private Loggable, public ILinkContext
{
public:
	AddressScanner(Logger* apLogger, const APLXML_MTS::MasterTestSet_t& cfg, boost::uint16_t start, boost::uint16_t stop);

	void Run();

	void OnLowerLayerUp();
	void OnLowerLayerDown();

	void Ack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void Nack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void LinkStatus(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void NotSupported (bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);

	//	Pri to Sec

	void TestLinkStatus(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc);
	void ResetLinkStates(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc);
	void RequestLinkStatus(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc);
	void ConfirmedUserData(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength);
	void UnconfirmedUserData(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength);

private:

	void OnTimeout();

	void NextFrame();

	apl::IOService mService;
	apl::xml::PhysicalLayerManagerXML manager;
	TimerSourceASIO mTimerSrc;
	IOServiceThread mThread;
	dnp::LinkLayerRouter mRouter;
	LinkFrame mFrame;
	ITimer* mpTimer;
	boost::uint16_t mMasterAddr;
	millis_t mScanTimeout;

	boost::uint16_t mCurrent;
	boost::uint16_t mStop;
};

}
}

#endif
