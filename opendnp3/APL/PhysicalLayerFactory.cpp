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

#include <opendnp3/APL/Log.h>
#include <opendnp3/APL/PhysicalLayerAsyncSerial.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPv4Client.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPv4Server.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPv6Client.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPv6Server.h>
#include <opendnp3/APL/PhysicalLayerFactory.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace apl
{

IPhysicalLayerAsyncFactory PhysicalLayerFactory :: GetSerialAsync(SerialSettings s)
{
	return boost::bind(&PhysicalLayerFactory::FGetSerialAsync, s, _2, _1);
}

IPhysicalLayerAsyncFactory PhysicalLayerFactory :: GetTCPv4ClientAsync(std::string aAddress, boost::uint16_t aPort)
{
	return boost::bind(&PhysicalLayerFactory::FGetTCPv4ClientAsync, aAddress, aPort, _2, _1);
}

IPhysicalLayerAsyncFactory PhysicalLayerFactory :: GetTCPv4ServerAsync(std::string aEndpoint, boost::uint16_t aPort)
{
	return boost::bind(&PhysicalLayerFactory::FGetTCPv4ServerAsync, aEndpoint, aPort, _2, _1);
}

IPhysicalLayerAsyncFactory PhysicalLayerFactory :: GetTCPv6ClientAsync(std::string aAddress, boost::uint16_t aPort)
{
	return boost::bind(&PhysicalLayerFactory::FGetTCPv6ClientAsync, aAddress, aPort, _2, _1);
}

IPhysicalLayerAsyncFactory PhysicalLayerFactory :: GetTCPv6ServerAsync(std::string aEndpoint, boost::uint16_t aPort)
{
	return boost::bind(&PhysicalLayerFactory::FGetTCPv6ServerAsync, aEndpoint, aPort, _2, _1);
}

IPhysicalLayerAsync* PhysicalLayerFactory :: FGetSerialAsync(SerialSettings s, boost::asio::io_service* apSrv, Logger* apLogger)
{
	return new PhysicalLayerAsyncSerial(apLogger, apSrv, s);
}

IPhysicalLayerAsync* PhysicalLayerFactory :: FGetTCPv4ClientAsync(std::string aAddress, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger)
{
	return new PhysicalLayerAsyncTCPv4Client(apLogger, apSrv, aAddress, aPort);
}

IPhysicalLayerAsync* PhysicalLayerFactory :: FGetTCPv4ServerAsync(std::string aEndpoint, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger)
{
	return new PhysicalLayerAsyncTCPv4Server(apLogger, apSrv, aEndpoint, aPort);
}

IPhysicalLayerAsync* PhysicalLayerFactory :: FGetTCPv6ClientAsync(std::string aAddress, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger)
{
	return new PhysicalLayerAsyncTCPv6Client(apLogger, apSrv, aAddress, aPort);
}

IPhysicalLayerAsync* PhysicalLayerFactory :: FGetTCPv6ServerAsync(std::string aEndpoint, boost::uint16_t aPort, boost::asio::io_service* apSrv, Logger* apLogger)
{
	return new PhysicalLayerAsyncTCPv6Server(apLogger, apSrv, aEndpoint, aPort);
}

}
