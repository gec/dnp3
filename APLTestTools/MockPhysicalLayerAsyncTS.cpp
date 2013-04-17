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
#include "MockPhysicalLayerAsyncTS.h"

#include <APLTestTools/MockTimerSource.h>
#include <boost/bind.hpp>
#include <opendnp3/APL/Logger.h>

using namespace boost::system;

namespace apl
{

MockPhysicalLayerAsyncTS::MockPhysicalLayerAsyncTS(Logger* apLogger, MockTimerSource* apTimerSrc) :
	PhysicalLayerAsyncBase(apLogger),
	mpTimerSrc(apTimerSrc),
	mpOpenTimer(NULL),
	mErrorCode(errc::permission_denied, get_generic_category()),
	mWriteBuffer(1024)
{
	this->Reset();
}

void MockPhysicalLayerAsyncTS::WriteToLayer(const boost::uint8_t* apData, size_t aNumBytes)
{
	memcpy(mWriteBuffer.WriteBuff(), apData, aNumBytes);
	mWriteBuffer.AdvanceWrite(aNumBytes);
	this->CheckForRead();
}

void MockPhysicalLayerAsyncTS::Advance()
{
	while(mpTimerSrc->DispatchOne());
}

void MockPhysicalLayerAsyncTS::Reset()
{
	mpBuff = NULL;
	mNumBytes = 0;
}

void MockPhysicalLayerAsyncTS::DoOpen()
{
	mpOpenTimer = mpTimerSrc->Start(2000, boost::bind(&MockPhysicalLayerAsyncTS::OnOpenCallback, this, mSuccessCode));
}

//we might have outstanding
void MockPhysicalLayerAsyncTS::DoClose()
{
	this->Reset();

	if(mState.mReading) {
		mpTimerSrc->Post(boost::bind(&MockPhysicalLayerAsyncTS::OnReadCallback, this, mErrorCode, mpBuff, 0));
	}

	if(mState.mWriting) {
		mpTimerSrc->Post(boost::bind(&MockPhysicalLayerAsyncTS::OnWriteCallback, this, mErrorCode, 0));
	}
}

void MockPhysicalLayerAsyncTS::DoOpeningClose()
{
	mpOpenTimer->Cancel();
	mpTimerSrc->Post(boost::bind(&MockPhysicalLayerAsyncTS::OnOpenCallback, this, mErrorCode));
}


void MockPhysicalLayerAsyncTS::DoOpenSuccess()
{
	LOG_BLOCK(LEV_INFO, "Open success");
}

void MockPhysicalLayerAsyncTS::DoOpenFailure() {}

void MockPhysicalLayerAsyncTS::DoAsyncRead(boost::uint8_t* apBuff, size_t aNumBytes)
{
	mpBuff = apBuff;
	mNumBytes = aNumBytes;
	mpTimerSrc->Post(boost::bind(&MockPhysicalLayerAsyncTS::CheckForRead, this));
}

void MockPhysicalLayerAsyncTS::DoAsyncWrite(const boost::uint8_t* apData, size_t aNumBytes)
{
	this->WriteToBuffer(apData, aNumBytes); //record to BufferTestObject
	mpTimerSrc->Post(boost::bind(&MockPhysicalLayerAsyncTS::OnWriteCallback, this, mSuccessCode, aNumBytes));
}

void MockPhysicalLayerAsyncTS::CheckForRead()
{
	if(mNumBytes > 0 && mWriteBuffer.NumReadBytes() > 0) {
		size_t min = mNumBytes > mWriteBuffer.NumReadBytes() ? mWriteBuffer.NumReadBytes() : mNumBytes;
		memcpy(mpBuff, mWriteBuffer.ReadBuff(), min);
		mNumBytes = 0;
		this->OnReadCallback(mSuccessCode, mpBuff, min);
		mWriteBuffer.AdvanceRead(min);
		mWriteBuffer.Shift();
	}
}

} //end namespace
