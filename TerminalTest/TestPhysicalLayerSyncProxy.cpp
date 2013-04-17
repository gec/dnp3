
#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>
#include <APLTestTools/TestHelpers.h>

#include <opendnp3/APL/Lock.h>
#include <APLTestTools/AsyncTestObjectASIO.h>
#include <APLTestTools/LogTester.h>
#include <opendnp3/APL/LowerLayerToPhysAdapter.h>
#include <APLTestTools/MockUpperLayer.h>

#include <Terminal/PhysicalLayerSyncProxy.h>

#include <boost/bind.hpp>
#include <queue>

using namespace apl;
using namespace boost;

class SyncProxyTestObject : public LogTester, public AsyncTestObjectASIO, public PhysicalLayerSyncProxy
{
public:
	SyncProxyTestObject(FilterLevel aLevel, bool aImmediate = false) :
		LogTester(aImmediate),
		AsyncTestObjectASIO(),
		PhysicalLayerSyncProxy(mLog.GetLogger(aLevel, "SyncProxy"), this->GetService()),
		adapter(mLog.GetLogger(aLevel, "Adapter"), this, false),
		upper(mLog.GetLogger(aLevel, "Upper")) {
		adapter.SetUpperLayer(&upper);
	}

	std::string Read() {
		CriticalSection cs(&mQueueLock);
		while(mReadQueue.size() == 0) cs.Wait();
		std::string ret = mReadQueue.front();
		mReadQueue.pop_front();
		return ret;
	}

	void Write(const std::string&) {

	}

	void Push(const std::string& s) {
		CriticalSection cs(&mQueueLock);
		mReadQueue.push_back(s);
		cs.Signal();
	}

	apl::LowerLayerToPhysAdapter adapter;
	apl::MockUpperLayer upper;

private:

	SigLock mQueueLock;
	std::deque<std::string> mReadQueue;
};

BOOST_AUTO_TEST_SUITE(PhysicalLayerSyncProxy)


BOOST_AUTO_TEST_CASE(Init)
{
	SyncProxyTestObject t(LEV_INFO);
}

BOOST_AUTO_TEST_CASE(OpenReadWrite)
{
	SyncProxyTestObject t(LEV_INFO);
	MockUpperLayer::State s;
	BOOST_REQUIRE(t.upper.StateEquals(s));
	t.AsyncOpen(); ++s.mNumLayerUp;
	t.ProceedUntil(boost::bind(&MockUpperLayer::StateEquals, &t.upper, s));

	t.adapter.StartRead();
	t.Push("foo");
	BOOST_REQUIRE(t.ProceedUntil(boost::bind(&MockUpperLayer::BufferEqualsString, &t.upper, "foo")));

	t.Push("bar");
	t.adapter.StartRead();
	BOOST_REQUIRE(t.ProceedUntil(boost::bind(&MockUpperLayer::BufferEqualsString, &t.upper, "foobar")));

	t.upper.SendDown("00"); ++s.mSuccessCnt;
	t.ProceedUntil(boost::bind(&MockUpperLayer::StateEquals, &t.upper, s));

	t.AsyncClose(); ++s.mNumLayerDown;
	t.ProceedUntil(boost::bind(&MockUpperLayer::StateEquals, &t.upper, s));
}



BOOST_AUTO_TEST_SUITE_END()

