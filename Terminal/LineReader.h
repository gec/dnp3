#ifndef __LINE_READER_H_
#define __LINE_READER_H_

#include <opendnp3/APL/Uncopyable.h>
#include <opendnp3/APL/PhysicalLayerMonitor.h>
#include <opendnp3/APL/CopyableBuffer.h>
#include <string>

namespace apl
{

class IPhysicalLayerAsync;
class ITimerSource;

/** Abstracts the process of reading line from a physical layer.
*/
class LineReader : public PhysicalLayerMonitor, private Uncopyable
{
public:
	LineReader(Logger* apLogger, IPhysicalLayerAsync* apPhysical, ITimerSource* apTimerSrc, size_t aBuffSize);

	virtual void AcceptLine(const std::string&) = 0;
	virtual void _Up() = 0;
	virtual void _Down() = 0;

private:
	CopyableBuffer mBuffer;
	size_t mNumBytes;
	bool mHasCR;

	void Read();
	void OnPhysicalLayerOpenSuccessCallback();
	void OnPhysicalLayerOpenFailureCallback() {}
	void OnPhysicalLayerCloseCallback();
	void Reset();

	void _OnReceive(const boost::uint8_t*, size_t aNum);
	void ReadBuffer();
};


}

#endif
