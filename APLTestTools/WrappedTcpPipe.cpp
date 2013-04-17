#include "WrappedTcpPipe.h"

#include <opendnp3/APL/Logger.h>

namespace apl
{

WrappedTcpPipe::WrappedTcpPipe(Logger* apLogger, boost::asio::io_service* apService, boost::uint16_t aPort) :
	clientTcp(apLogger->GetSubLogger("clientTcp"), apService, "127.0.0.1", aPort),
	serverTcp(apLogger->GetSubLogger("serverTcp"), apService, "127.0.0.1", aPort),
	client(apLogger->GetSubLogger("clientWrapper"), &clientTcp),
	server(apLogger->GetSubLogger("serverWrapper"), &serverTcp)
{

}




}

