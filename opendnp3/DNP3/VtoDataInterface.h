/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.  Green Enery
 * Corp licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-3.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef __VTO_DATA_INTERFACE_H_
#define __VTO_DATA_INTERFACE_H_

#include <opendnp3/APL/DataTypes.h>
#include <opendnp3/DNP3/EventTypes.h>
#include <opendnp3/DNP3/ObjectInterfaces.h>

#include <assert.h>

namespace apl
{
namespace dnp
{

/**
 * The abstract base class for all VTO interface handlers.
 */
class IVtoChannel
{
public:

	/**
	 * Creates a new IVtoBase instance configured for Virtual
	 * Terminal channel id matching aChannelId.
	 *
	 * @param aChannelId	the DNP3 Virtual Terminal port (channel
	 *						id)
	 *
	 * @return				the new IVtoBase instance
	 */
	IVtoChannel(boost::uint8_t aChannelId) : mChannelId(aChannelId) {}

	/**
	 * Returns the Virtual Terminal channel id for the object.
	 *
	 * @return the DNP3 Virtual Terminal port (channel id)
	 */
	boost::uint8_t GetChannelId() {
		return this->mChannelId;
	}

private:
	/**
	 * A hidden default constructor.
	 *
	 * @deprecated			Use IVtoChannel(boost::uint8_t) instead.
	 */
	IVtoChannel() {}

	/**
	 * The DNP3 Virtual Terminal port (channel id) for this object.
	 */
	boost::uint8_t mChannelId;
};

class IVtoCallbacks : public IVtoChannel
{
public:
	/**
	 * Creates a new IVtoCallbacks instance configured for Virtual
	 * Terminal channel id matching aChannelId.
	 *
	 * @param aChannelId	the DNP3 Virtual Terminal port (channel
	 *						id)
	 *
	 * @return				the new IVtoCallbacks instance
	 */
	IVtoCallbacks(boost::uint8_t aChannelId) : IVtoChannel(aChannelId) {}

	/**
	 * Called when an IVtoWriter has space available for writing.
	 */
	virtual void OnBufferAvailable() {}

	/**
	 * Called when an IVtoReader has received some data.
	 */
	virtual void OnVtoDataReceived(const VtoData& arData) {}
};

/**
 * IVTOWriter is returned by the stack for write operations to a Vto
 * stream.  The Write() function should be used in conjunction with the
 * OnBufferAvailable() callback on the IVTOCallbacks interface provided
 * to the stack.
 */
class IVtoWriter
{
public:

	/**
	 * Writes a stream of data to the remote VTO endpoint.
	 *
	 * @param apData		The data to write to the VTO stream.
	 * @param aLength		The length of the data to write (in
	 *						bytes).
	 * @param aChannelId	The channel id for the vto stream
	 *
	 * @return				The number of bytes that were
	 *                      successfully queued into the VTO
	 *                      transmission queue.  This number may be
	 *                      less than the length request if the
	 *                      buffer has insufficient space.
	 */
	virtual size_t Write(const boost::uint8_t* apData, size_t aLength, boost::uint8_t aChannelId) = 0;

	/**
	 * Sends an indication to the remote vto consumer that the VTO connection
	 * on this side of the dnp3 connection has changed.
	 *
	 * @param aLocalVtoConnectionOpened  Whether the local connection
	 *                                   should be considered to be online
	 * @param aChannelId                 The channel id for the vto stream
	 */
	virtual void SetLocalVtoState(bool aLocalVtoConnectionOpened, boost::uint8_t aChannelId) = 0;

	/**
	 * Returns the number of bytes that the writer can currently accept
	 *
	 * @return				the number of objects in the
	 *						transmission queue
	 */
	virtual size_t NumBytesAvailable() = 0;

	/**
	* Registers an IVtoCallbacks to receive OnBufferAvailable() notifications
	* @param apHandler The interface to invoke when space is made available
	*/
	virtual void AddVtoCallback(IVtoCallbacks* apHandler) = 0;

	/**
	* Stops an IVtoCallbacks from receiving OnBufferAvailable() notifications
	* @param apHandler The interface to stop calling when space is available
	*/
	virtual void RemoveVtoCallback(IVtoCallbacks* apHandler) = 0;
};

class IVtoReader
{
public:

	/**
	 * Register an IVtoCallbacks instance with the VtoReader
	 * instance.  The IVtoCallbacks instance is self-aware of its
	 * channel id.
	 *
	 * @param apCallbacks		The callback handler for the channel
	 *
	 * @throw ArgumentException	if the channel id is already
	 *registered
	 *                          with this reader
	 */
	virtual void AddVtoChannel(IVtoCallbacks* apCallbacks) = 0;

	/**
	 * Unregister an IVtoCallbacks instance with the VtoReader
	 * instance.
	 *
	 * @param apCallbacks		The callback handler to unregister
	 *
	 * @throw ArgumentException	if the channel id is not registered
	 *                          with this reader
	 */
	virtual void RemoveVtoChannel(IVtoCallbacks* apCallbacks) = 0;
};

}
}

/* vim: set ts=4 sw=4 noexpandtab: */

#endif
