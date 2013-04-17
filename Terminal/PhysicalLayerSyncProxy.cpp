#include "PhysicalLayerSyncProxy.h"

#include <boost/asio.hpp>
#include <iostream>

//using namespace boost::system;
using namespace std;

namespace apl
{

const boost::system::error_code PhysicalLayerSyncProxy::mSuccessCode(boost::system::errc::success, boost::system::get_generic_category());
const boost::system::error_code PhysicalLayerSyncProxy::mErrorCode(boost::system::errc::permission_denied, boost::system::get_generic_category());

PhysicalLayerSyncProxy::PhysicalLayerSyncProxy(Logger* apLogger, boost::asio::io_service* apService) :
	PhysicalLayerAsyncBase(apLogger),
	mpService(apService),
	mThread(this)
{
	this->Reset();
	mThread.Start();
}

void PhysicalLayerSyncProxy::SignalStop()
{
	CriticalSection cs(&mWaitLock);
	cs.Signal();
}

void PhysicalLayerSyncProxy::Reset()
{
	mReading = false;
	mpBuffer = NULL;
	mNumToRead = 0;
	mLineQueue.clear();
}

void PhysicalLayerSyncProxy::CheckForRead()
{
	if(mReading && mLineQueue.size() > 0) {
		std::string copy(mLineQueue.front());
		mLineQueue.pop_front();
		size_t len = copy.size();
		size_t min = len > mNumToRead ? mNumToRead : len;
		size_t remainder = len - min;
		memcpy(mpBuffer, copy.c_str(), min);
		if(remainder > 0) {
			std::string r(copy.c_str() + mNumToRead, remainder);
			mLineQueue.push_front(r);
		}
		mReading = false;
		mpService->post(boost::bind(&PhysicalLayerSyncProxy::OnReadCallback, this, mSuccessCode, mpBuffer, min));
	}
}

void PhysicalLayerSyncProxy::DoOpen()
{
	this->Reset();
	mpService->post(boost::bind(&PhysicalLayerSyncProxy::OnOpenCallback, this, mSuccessCode));
}

void PhysicalLayerSyncProxy::DoClose()
{

}

void PhysicalLayerSyncProxy::DoAsyncRead(boost::uint8_t* apData, size_t aLength)
{
	CriticalSection cs(&mWaitLock);
	mpBuffer = apData;
	mNumToRead = aLength;
	mReading = true;
	this->CheckForRead();
	if(mReading) cs.Signal(); //wake up the thread to go and get more data from stdin
}

void PhysicalLayerSyncProxy::DoAsyncWrite(const boost::uint8_t* apData, size_t aLength)
{
	const char* pBuff = reinterpret_cast<const char*>(apData);
	string s(pBuff, aLength);
	this->Write(s);
	mpService->post(boost::bind(&PhysicalLayerSyncProxy::OnWriteCallback, this, mSuccessCode, aLength));
}

void PhysicalLayerSyncProxy::Run()
{
	while(!IsExitRequested()) {
		CriticalSection cs(&mWaitLock);
		if( !mReading ) cs.Wait();
		if( mReading ) {
			mLineQueue.push_back(this->Read());
			this->CheckForRead();
		}
	}
}
}
