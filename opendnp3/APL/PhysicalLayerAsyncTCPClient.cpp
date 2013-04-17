//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
// more contributor license agreements. See the NOTICE file distributed
// with this work for additional information regarding copyright
// ownership.  Green Enery Corp licenses this file to you under the
// Apache License, Version 2.0 (the "License"); you may not use this
// file except in compliance with the License.  You may obtain a copy of
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied.  See the License for the specific language governing
// permissions and limitations under the License.
//

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/IHandlerAsync.h>
#include <opendnp3/APL/Logger.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPClient.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

using namespace boost;
using namespace boost::asio;
using namespace std;

namespace apl
{

PhysicalLayerAsyncTCPClient::PhysicalLayerAsyncTCPClient(Logger* apLogger, boost::asio::io_service* apIOService, const boost::asio::ip::tcp::endpoint& arEndpoint, const std::string& arAddress)
	: PhysicalLayerAsyncBaseTCP(apLogger, apIOService)
	, mRemoteEndpoint(arEndpoint)
{
	mRemoteEndpoint.address( ResolveAddress(arAddress) );
}

/* Implement the actions */
void PhysicalLayerAsyncTCPClient::DoOpen()
{
	mSocket.async_connect(mRemoteEndpoint,
	                      boost::bind(&PhysicalLayerAsyncTCPClient::OnOpenCallback,
	                                  this,
	                                  boost::asio::placeholders::error));
}

void PhysicalLayerAsyncTCPClient::DoOpeningClose()
{
	this->CloseSocket();
}

void PhysicalLayerAsyncTCPClient::DoOpenSuccess()
{
	LOG_BLOCK(LEV_INFO, "Connected to: " << mRemoteEndpoint);
}

}

/* vim: set ts=4 sw=4: */
