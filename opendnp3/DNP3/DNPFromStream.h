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
#ifndef __DNP_FROM_STREAM_H_
#define __DNP_FROM_STREAM_H_

#include <opendnp3/APL/CommandTypes.h>
#include <opendnp3/APL/Configure.h>

#include <iostream>

#ifdef APL_PLATFORM_WIN
//disable the type converstion warnings
#pragma warning ( push )
#pragma warning ( disable : 4244 )
#endif

namespace apl
{
namespace dnp
{

/** Templates for read dnp3 data types from stream.
	Used in the dnp3 object definitions to define how
	they deserialize themeselves.
*/
class DNPFromStream
{
public:

	template <typename T, typename PayloadType, SetpointEncodingType EncodingType>
	static Setpoint ReadSetpoint(const boost::uint8_t*, const T*);

	//templated conversion functions
	template <typename T>
	static typename T::DataType ReadQ(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadQT(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadV(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadQV(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadBinaryQV(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadBinaryQVT(const boost::uint8_t* apPos, const T* apObj);

	template <typename T>
	static typename T::DataType ReadQVT(const boost::uint8_t* apPos, const T* apObj);
};

template <typename T, typename PayloadType, apl::SetpointEncodingType EncodingType>
inline Setpoint DNPFromStream::ReadSetpoint(const boost::uint8_t* apPos, const T* apObj)
{
	Setpoint sp(static_cast<PayloadType>(apObj->mValue.Get(apPos)));
	sp.mStatus = ByteToCommandStatus(apObj->mStatus.Get(apPos));
	sp.SetEncodingType(EncodingType);
	return sp;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadQ(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQuality(apObj->mFlag.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadBinaryQV(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQualityValue(apObj->mFlag.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadBinaryQVT(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQualityValue(apObj->mFlag.Get(apPos));
	ret.SetTime((TimeStamp_t)apObj->mTime.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadQT(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQuality(apObj->mFlag.Get(apPos));
	ret.SetTime((TimeStamp_t)apObj->mTime.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadV(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetValue(apObj->mValue.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadQV(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQuality(apObj->mFlag.Get(apPos));
	ret.SetValue(apObj->mValue.Get(apPos));
	return ret;
}

template <typename T>
inline typename T::DataType DNPFromStream::ReadQVT(const boost::uint8_t* apPos, const T* apObj)
{
	typename T::DataType ret;
	ret.SetQuality(apObj->mFlag.Get(apPos));
	ret.SetValue(apObj->mValue.Get(apPos));
	ret.SetTime((TimeStamp_t)apObj->mTime.Get(apPos));
	return ret;
}
}
}

#ifdef APL_PLATFORM_WIN
//disable thes type converstion warnings
#pragma warning ( pop )
#endif

#endif

