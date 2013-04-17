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
#ifndef _PHYSICAL_LAYER_FACTORY_H_
#define _PHYSICAL_LAYER_FACTORY_H_

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/PhysicalLayerFunctors.h>
#include <opendnp3/APL/SerialTypes.h>

#include <boost/cstdint.hpp>
#include <map>

namespace apl
{

class PhysicalLayerFactory
{
public:

	static IPhysicalLayerAsyncFactory GetSerialAsync(SerialSettings s);
	static IPhysicalLayerAsyncFactory GetTCPv4ClientAsync(std::string aAddress, boost::uint16_t aPort);
	static IPhysicalLayerAsyncFactory GetTCPv4ServerAsync(std::string aEndpoint, boost::uint16_t aPort);
	static IPhysicalLayerAsyncFactory GetTCPv6ClientAsync(std::string aAddress, boost::uint16_t aPort);
	static IPhysicalLayerAsyncFactory GetTCPv6ServerAsync(std::string aEndpoint, boost::uint16_t aPort);

	//normal factory functions
	static IPhysicalLayerAsync* FGetSerialAsync(SerialSettings s, boost::asio::io_service* apSrv, Logger* apLogger);
	static IPhysicalLayerAsync* FGetTCPv4ClientAsync(std::string aAddress, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger);
	static IPhysicalLayerAsync* FGetTCPv4ServerAsync(std::string aEndpoint, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger);
	static IPhysicalLayerAsync* FGetTCPv6ClientAsync(std::string aAddress, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger);
	static IPhysicalLayerAsync* FGetTCPv6ServerAsync(std::string aEndpoint, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger);
};

}

#endif
