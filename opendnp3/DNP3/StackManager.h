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
#ifndef __STACK_MANAGER_H_
#define __STACK_MANAGER_H_

#include <opendnp3/APL/CommandInterfaces.h>
#include <opendnp3/APL/DataInterfaces.h>
#include <opendnp3/APL/LogBase.h>
#include <opendnp3/APL/PhysLayerSettings.h>
#include <opendnp3/APL/SerialTypes.h>
#include <opendnp3/DNP3/MasterStackConfig.h>
#include <opendnp3/DNP3/SlaveStackConfig.h>
#include <opendnp3/DNP3/VtoDataInterface.h>

#include <vector>

namespace apl
{
class EventLog;
class ILogBase;
}

namespace apl
{
namespace dnp
{

class AsyncStackManager;

/**
 * Wraps the AyncStackManger using the impl pattern. This makes it
 * suiteable for wrapping with swig or for creating a header-only
 * distribution.  The functions do the exact same thing as their impl
 * counterparts.
 */
class StackManager
{
public:
	StackManager();
	~StackManager();

	void AddTCPClient(const std::string& arName,
	                  PhysLayerSettings aPhys,
	                  const std::string& arAddr,
	                  boost::uint16_t aPort);

	void AddTCPv4Client(const std::string& arName,
	                    PhysLayerSettings aPhys,
	                    const std::string& arAddr,
	                    boost::uint16_t aPort);

	void AddTCPServer(const std::string& arName,
	                  PhysLayerSettings aPhys,
	                  const std::string& arEndpoint,
	                  boost::uint16_t aPort);

	void AddTCPv4Server(const std::string& arName,
	                    PhysLayerSettings aPhys,
	                    const std::string& arEndpoint,
	                    boost::uint16_t aPort);

	void AddTCPv6Client(const std::string& arName,
	                    PhysLayerSettings aPhys,
	                    const std::string& arAddr,
	                    boost::uint16_t aPort);

	void AddTCPv6Server(const std::string& arName,
	                    PhysLayerSettings aPhys,
	                    const std::string& arEndpoint,
	                    boost::uint16_t aPort);

	void AddSerial(const std::string& arName,
	               PhysLayerSettings aPhys,
	               SerialSettings aSerial);

	ICommandAcceptor* AddMaster(const std::string& arPortName,
	                            const std::string& arStackName,
	                            FilterLevel aLevel,
	                            IDataObserver* apPublisher,
	                            const MasterStackConfig& arCfg);

	IDataObserver* AddSlave(const std::string& arPortName,
	                        const std::string& arStackName,
	                        FilterLevel aLevel,
	                        ICommandAcceptor* apCmdAcceptor,
	                        const SlaveStackConfig& arCfg);

	void AddVtoChannel(const std::string& arStackName,
	                   IVtoCallbacks* apOnDataCallback);

	void RemoveVtoChannel(const std::string& arStackName,
	                      IVtoCallbacks* apOnDataCallback);

	void StartVtoRouter(const std::string& arPortName,
	                    const std::string& arStackName,
	                    const VtoRouterSettings& arSettings);

	void StopVtoRouter(const std::string& arStackName,
	                   boost::uint8_t aVtoChannelId);

	void StopAllRoutersOnStack(const std::string& arStackName);

	IVtoWriter* GetVtoWriter(const std::string& arStackName);

	void RemovePort(const std::string& arPortName);

	void RemoveStack(const std::string& arStackName);

	void AddLogHook(ILogBase*);

	std::vector<std::string> GetStackNames();

	std::vector<std::string> GetPortNames();

	void Shutdown();

private:
	EventLog* mpLog;
	AsyncStackManager* mpImpl;
};

}
}

/* vim: set ts=4 sw=4 noexpandtab: */

#endif

