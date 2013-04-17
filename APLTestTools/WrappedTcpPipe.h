#ifndef __WRAPPED_TCP_PIPE_H_
#define __WRAPPED_TCP_PIPE_H_

#include <opendnp3/APL/PhysicalLayerAsyncTCPv4Client.h>
#include <opendnp3/APL/PhysicalLayerAsyncTCPv4Server.h>

#include "PhysicalLayerWrapper.h"

namespace boost {
	namespace asio {
		class io_service;
	}
}

namespace apl
{

class WrappedTcpPipe
{
	public:
		WrappedTcpPipe(Logger*, boost::asio::io_service*, boost::uint16_t aPort);

	private:
		PhysicalLayerAsyncTCPv4Client clientTcp;
		PhysicalLayerAsyncTCPv4Server serverTcp;

	public:
		PhysicalLayerWrapper client;
		PhysicalLayerWrapper server;
};

}

#endif
