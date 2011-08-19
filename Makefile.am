#
# Copyright (c) 2010, 2011 Green Energy Corp.
# All rights reserved.
#

ACLOCAL_AMFLAGS = -I config/autotools/m4

AM_CXXFLAGS = $(BOOST_CPPFLAGS) -DBOOST_TEST_DYN_LINK -DBOOST_ASIO_ENABLE_CANCELIO -DBOOST_REGEX_NO_LIB
AM_LDFLAGS = $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) $(BOOST_THREAD_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_UNIT_TEST_FRAMEWORK_LIB)

lib_LTLIBRARIES = libopendnp3_apl.la libopendnp3_dnp3.la libopendnp3_java.la

libopendnp3_apl_la_LDFLAGS = -version-info 0:0:0
libopendnp3_apl_la_SOURCES = \
	APL/ASIOSerialHelpers.cpp \
	APL/AsyncLayerInterfaces.cpp \
	APL/AsyncResult.cpp \
	APL/AsyncTaskBase.cpp \
	APL/AsyncTaskContinuous.cpp \
	APL/AsyncTaskGroup.cpp \
	APL/AsyncTaskNonPeriodic.cpp \
	APL/AsyncTaskPeriodic.cpp \
	APL/AsyncTaskScheduler.cpp \
	APL/BaseDataTypes.cpp \
	APL/CommandManager.cpp \
	APL/CommandQueue.cpp \
	APL/CommandResponseQueue.cpp \
	APL/CommandTypes.cpp \
	APL/CopyableBuffer.cpp \
	APL/CRC.cpp \
	APL/EventLock.cpp \
	APL/Exception.cpp \
	APL/FlexibleDataObserver.cpp \
	APL/IHandlerAsync.cpp \
	APL/ITimerSource.cpp \
	APL/IOService.cpp \
	APL/IOServiceThread.cpp \
	APL/LockBase.cpp \
	APL/LockBoost.cpp \
	APL/Log.cpp \
	APL/LogEntryCircularBuffer.cpp \
	APL/LogEntry.cpp \
	APL/Loggable.cpp \
	APL/Logger.cpp \
	APL/LogToFile.cpp \
	APL/LogToStdio.cpp \
	APL/LogTypes.cpp \
	APL/LowerLayerToPhysAdapter.cpp \
	APL/MetricBuffer.cpp \
	APL/MultiplexingDataObserver.cpp \
	APL/PackingUnpacking.cpp \
	APL/Parsing.cpp \
	APL/PhysicalLayerAsyncBase.cpp \
	APL/PhysicalLayerAsyncBaseTCP.cpp \
	APL/PhysicalLayerAsyncSerial.cpp \
	APL/PhysicalLayerAsyncTCPClient.cpp \
	APL/PhysicalLayerAsyncTCPServer.cpp \
	APL/PhysicalLayerFactory.cpp \
	APL/PhysicalLayerInstance.cpp \
	APL/PhysicalLayerManager.cpp \
	APL/PhysicalLayerMap.cpp \
	APL/PhysicalLayerMonitor.cpp \
	APL/PhysicalLayerMonitorStates.cpp \
	APL/PhysicalLayerStates.cpp \
	APL/PhysLoopback.cpp \
	APL/PostingNotifier.cpp \
	APL/PostingNotifierSource.cpp \
	APL/ProtocolUtil.cpp \
	APL/QualityConverter.cpp \
	APL/RandomizedBuffer.cpp \
	APL/ShiftableBuffer.cpp \
	APL/SuspendTimerSource.cpp \
	APL/Threadable.cpp \
	APL/ThreadBase.cpp \
	APL/ThreadBoost.cpp \
	APL/TimeBase.cpp \
	APL/TimeBoost.cpp \
	APL/Timeout.cpp \
	APL/TimerASIO.cpp \
	APL/TimerSourceASIO.cpp \
	APL/TimeSource.cpp \
	APL/TimingTools.cpp \
	APL/ToHex.cpp \
	APL/TrackingTaskGroup.cpp \
	APL/Util.cpp

libopendnp3_dnp3_la_LDFLAGS = -version-info 0:0:0
libopendnp3_dnp3_la_LIBADD = libopendnp3_apl.la
libopendnp3_dnp3_la_SOURCES = \
	DNP3/AlwaysOpeningVtoRouter.cpp \
	DNP3/APDUConstants.cpp \
	DNP3/APDU.cpp \
	DNP3/AppChannelStates.cpp \
	DNP3/AppHeader.cpp \
	DNP3/AppInterfaces.cpp \
	DNP3/AppLayerChannel.cpp \
	DNP3/AppLayer.cpp \
	DNP3/AsyncStackManager.cpp \
	DNP3/BufferTypes.cpp \
	DNP3/ClassCounter.cpp \
	DNP3/ControlTasks.cpp \
	DNP3/Database.cpp \
	DNP3/DataPoll.cpp \
	DNP3/DeviceTemplate.cpp \
	DNP3/DNPCommandMaster.cpp \
	DNP3/DNPCrc.cpp \
	DNP3/EnhancedVto.cpp \
	DNP3/EnhancedVtoRouter.cpp \
	DNP3/HeaderReadIterator.cpp \
	DNP3/IndexedWriteIterator.cpp \
	DNP3/IStackObserver.cpp \
	DNP3/LinkChannel.cpp \
	DNP3/LinkFrame.cpp \
	DNP3/LinkHeader.cpp \
	DNP3/LinkLayerConstants.cpp \
	DNP3/LinkLayer.cpp \
	DNP3/LinkLayerReceiver.cpp \
	DNP3/LinkLayerRouter.cpp \
	DNP3/LinkReceiverStates.cpp \
	DNP3/LinkRoute.cpp \
	DNP3/Master.cpp \
	DNP3/MasterSchedule.cpp \
	DNP3/MasterStack.cpp \
	DNP3/MasterStates.cpp \
	DNP3/MasterTaskBase.cpp \
	DNP3/ObjectHeader.cpp \
	DNP3/ObjectInterfaces.cpp \
	DNP3/ObjectReadIterator.cpp \
	DNP3/Objects.cpp \
	DNP3/ObjectWriteIterator.cpp \
	DNP3/PointClass.cpp \
	DNP3/PriLinkLayerStates.cpp \
	DNP3/ResponseContext.cpp \
	DNP3/ResponseLoader.cpp \
	DNP3/SecLinkLayerStates.cpp \
	DNP3/SlaveConfig.cpp \
	DNP3/Slave.cpp \
	DNP3/SlaveEventBuffer.cpp \
	DNP3/SlaveResponseTypes.cpp \
	DNP3/SlaveStack.cpp \
	DNP3/SlaveStates.cpp \
	DNP3/SolicitedChannel.cpp \
	DNP3/Stack.cpp \
	DNP3/StackManager.cpp \
	DNP3/StartupTasks.cpp \
	DNP3/TLS_Base.cpp \
	DNP3/TransportLayer.cpp \
	DNP3/TransportRx.cpp \
	DNP3/TransportStates.cpp \
	DNP3/TransportTx.cpp \
	DNP3/UnsolicitedChannel.cpp \
	DNP3/VtoData.cpp \
	DNP3/VtoReader.cpp \
	DNP3/VtoRouter.cpp \
	DNP3/VtoRouterManager.cpp \
	DNP3/VtoRouterSettings.cpp \
	DNP3/VtoTransmitTask.cpp \
	DNP3/VtoWriter.cpp

libopendnp3_java_la_LDFLAGS = -version-info 0:0:0
libopendnp3_java_la_SOURCES = DNP3Java/JavaDNP3.i

nobase_pkginclude_HEADERS= \
	version.hpp \
	APL/ASIOSerialHelpers.h \
	APL/AsyncLayerInterfaces.h \
	APL/AsyncTaskBase.h \
	APL/AsyncTaskContinuous.h \
	APL/AsyncTaskGroup.h \
	APL/AsyncTaskInterfaces.h \
	APL/AsyncTaskNonPeriodic.h \
	APL/AsyncTaskPeriodic.h \
	APL/AsyncTaskScheduler.h \
	APL/BaseDataTypes.h \
	APL/BoundNotifier.h \
	APL/CachedLogVariable.h \
	APL/ChangeBuffer.h \
	APL/CommandInterfaces.h \
	APL/CommandManager.h \
	APL/CommandQueue.h \
	APL/CommandResponseQueue.h \
	APL/CommandTypes.h \
	APL/Configure.h \
	APL/CopyableBuffer.h \
	APL/CRC.h \
	APL/DataInterfaces.h \
	APL/DataTypes.h \
	APL/DeleteAny.h \
	APL/EventLockBase.h \
	APL/EventLock.h \
	APL/EventSet.h \
	APL/Exception.h \
	APL/FlexibleDataObserver.h \
	APL/GetKeys.h \
	APL/IEventLock.h \
	APL/IHandlerAsync.h \
	APL/INotifier.h \
	APL/IOService.h \
	APL/IOServiceThread.h \
	APL/IPhysicalLayerAsync.h \
	APL/IPhysicalLayerObserver.h \
	APL/IPhysicalLayerSource.h \
	APL/ISubject.h \
	APL/ITimer.h \
	APL/ITimerSource.h \
	APL/ITimeSource.h \
	APL/ITransactable.h \
	APL/LockBase.h \
	APL/LockBoost.h \
	APL/Lock.h \
	APL/LogBase.h \
	APL/LogEntryCircularBuffer.h \
	APL/LogEntry.h \
	APL/Loggable.h \
	APL/Logger.h \
	APL/Log.h \
	APL/LogToFile.h \
	APL/LogToStdio.h \
	APL/LogTypes.h \
	APL/LogVar.h \
	APL/LowerLayerToPhysAdapter.h \
	APL/MetricBuffer.h \
	APL/MultiplexingDataObserver.h \
	APL/Notifier.h \
	APL/PackingTemplates.h \
	APL/PackingUnpacking.h \
	APL/Parsing.h \
	APL/PhysicalLayerAsyncASIO.h \
	APL/PhysicalLayerAsyncBase.h \
	APL/PhysicalLayerAsyncBaseTCP.h \
	APL/PhysicalLayerAsyncSerial.h \
	APL/PhysicalLayerAsyncTCPClient.h \
	APL/PhysicalLayerAsyncTCPServer.h \
	APL/PhysicalLayerFactory.h \
	APL/PhysicalLayerFunctors.h \
	APL/PhysicalLayerInstance.h \
	APL/PhysicalLayerManager.h \
	APL/PhysicalLayerMap.h \
	APL/PhysicalLayerMonitor.h \
	APL/PhysicalLayerMonitorStates.h \
	APL/PhysicalLayerStates.h \
	APL/PhysLayerSettings.h \
	APL/PhysLoopback.h \
	APL/PostingNotifier.h \
	APL/PostingNotifierSource.h \
	APL/ProtocolUtil.h \
	APL/QualityConverter.h \
	APL/QualityMasks.h \
	APL/QueueingFDO.h \
	APL/Random.h \
	APL/RandomizedBuffer.h \
	APL/SerialTypes.h \
	APL/ShiftableBuffer.h \
	APL/Singleton.h \
	APL/SubjectBase.h \
	APL/SuspendTimerSource.h \
	APL/SyncVar.h \
	APL/Threadable.h \
	APL/ThreadBase.h \
	APL/ThreadBoost.h \
	APL/Thread.h \
	APL/TimeBase.h \
	APL/TimeBoost.h \
	APL/Timeout.h \
	APL/TimerASIO.h \
	APL/TimerSourceASIO.h \
	APL/TimeSource.h \
	APL/TimeTypes.h \
	APL/TimingTools.h \
	APL/ToHex.h \
	APL/TrackingTaskGroup.h \
	APL/Types.h \
	APL/Uncopyable.h \
	APL/Util.h \
	DNP3/AlwaysOpeningVtoRouter.h \
	DNP3/APDUConstants.h \
	DNP3/APDU.h \
	DNP3/AppChannelStates.h \
	DNP3/AppConfig.h \
	DNP3/AppHeader.h \
	DNP3/AppInterfaces.h \
	DNP3/AppLayerChannel.h \
	DNP3/AppLayer.h \
	DNP3/AsyncStackManager.h \
	DNP3/BufferSetTypes.h \
	DNP3/BufferTypes.h \
	DNP3/ClassCounter.h \
	DNP3/ClassMask.h \
	DNP3/ControlTasks.h \
	DNP3/CTOHistory.h \
	DNP3/Database.h \
	DNP3/DatabaseInterfaces.h \
	DNP3/DataPoll.h \
	DNP3/DeviceTemplate.h \
	DNP3/DeviceTemplateTypes.h \
	DNP3/DNPCommandMaster.h \
	DNP3/DNPConstants.h \
	DNP3/DNPCrc.h \
	DNP3/DNPDatabaseTypes.h \
	DNP3/DNPExceptions.h \
	DNP3/DNPFromStream.h \
	DNP3/DNPToStream.h \
	DNP3/EnhancedVto.h \
	DNP3/EnhancedVtoRouter.h \
	DNP3/EventBufferBase.h \
	DNP3/EventBuffers.h \
	DNP3/EventTypes.h \
	DNP3/HeaderReadIterator.h \
	DNP3/IFrameSink.h \
	DNP3/ILinkContext.h \
	DNP3/ILinkRouter.h \
	DNP3/IndexedWriteIterator.h \
	DNP3/IStackObserver.h \
	DNP3/IVtoEventAcceptor.h \
	DNP3/LinkChannel.h \
	DNP3/LinkConfig.h \
	DNP3/LinkFrame.h \
	DNP3/LinkHeader.h \
	DNP3/LinkLayerConstants.h \
	DNP3/LinkLayer.h \
	DNP3/LinkLayerReceiver.h \
	DNP3/LinkLayerRouter.h \
	DNP3/LinkReceiverStates.h \
	DNP3/LinkRoute.h \
	DNP3/MasterConfig.h \
	DNP3/MasterConfigTypes.h \
	DNP3/Master.h \
	DNP3/MasterSchedule.h \
	DNP3/MasterStackConfig.h \
	DNP3/MasterStack.h \
	DNP3/MasterStates.h \
	DNP3/MasterTaskBase.h \
	DNP3/ObjectHeader.h \
	DNP3/ObjectInterfaces.h \
	DNP3/ObjectReadIterator.h \
	DNP3/Objects.h \
	DNP3/ObjectWriteIterator.h \
	DNP3/PointClass.h \
	DNP3/PriLinkLayerStates.h \
	DNP3/ResponseContext.h \
	DNP3/ResponseLoader.h \
	DNP3/SecLinkLayerStates.h \
	DNP3/SlaveConfig.h \
	DNP3/SlaveEventBuffer.h \
	DNP3/Slave.h \
	DNP3/SlaveResponseTypes.h \
	DNP3/SlaveStackConfig.h \
	DNP3/SlaveStack.h \
	DNP3/SlaveStates.h \
	DNP3/SolicitedChannel.h \
	DNP3/Stack.h \
	DNP3/StackManager.h \
	DNP3/StartupTasks.h \
	DNP3/TLS_Base.h \
	DNP3/TransportConstants.h \
	DNP3/TransportLayer.h \
	DNP3/TransportRx.h \
	DNP3/TransportStates.h \
	DNP3/TransportTx.h \
	DNP3/UnsolicitedChannel.h \
	DNP3/VtoConfig.h \
	DNP3/VtoData.h \
	DNP3/VtoDataInterface.h \
	DNP3/VtoEventBufferAdapter.h \
	DNP3/VtoReader.h \
	DNP3/VtoRouter.h \
	DNP3/VtoRouterManager.h \
	DNP3/VtoRouterSettings.h \
	DNP3/VtoTransmitTask.h \
	DNP3/VtoWriter.h

bin_PROGRAMS = testset

testset_LDADD = libopendnp3_apl.la libopendnp3_dnp3.la
testset_CFLAGS = -Itinyxml
testset_SOURCES = \
	APLXML/PhysicalLayerManagerXML.cpp \
	APLXML/PhysicalLayerXMLFactory.cpp \
	APLXML/tinybinding.cpp \
	APLXML/XML_APL.cpp \
	APLXML/XMLConversion.cpp \
	DNP3XML/XML_DNP3.cpp \
	DNP3XML/XML_TestSet.cpp \
	DNP3XML/XmlToConfig.cpp \
	Terminal/ControlResponseTE.cpp \
	Terminal/ControlTerminalExtension.cpp \
	Terminal/DOTerminalExtension.cpp \
	Terminal/FlexibleObserverTerminalExtension.cpp \
	Terminal/LineReader.cpp \
	Terminal/LogTerminalExtension.cpp \
	Terminal/PhysicalLayerIOStreamAsync.cpp \
	Terminal/PhysicalLayerSyncProxy.cpp \
	Terminal/Terminal.cpp \
	Terminal/TerminalInterfaces.cpp \
	TestSet/AddressScanner.cpp \
	TestSet/main.cpp \
	TestSet/StackHelpers.cpp \
	XMLBindings/APLXML_Base.cpp \
	XMLBindings/APLXML_DNP.cpp \
	XMLBindings/APLXML_MTS.cpp \
	XMLBindings/APLXML_STS.cpp \
	tinyxml/tinyxml.cpp \
	tinyxml/tinyxmlerror.cpp \
	tinyxml/tinyxmlparser.cpp

noinst_PROGRAMS = dnp3test

dnp3test_LDADD = libopendnp3_apl.la libopendnp3_dnp3.la
dnp3test_SOURCES = \
	APLTestTools/AsyncPhysTestObject.cpp \
	APLTestTools/AsyncTestObjectASIO.cpp \
	APLTestTools/AsyncTestObject.cpp \
	APLTestTools/BufferHelpers.cpp \
	APLTestTools/BufferTestObject.cpp \
	APLTestTools/LogTester.cpp \
	APLTestTools/LoopbackPhysicalLayerAsync.cpp \
	APLTestTools/MockLowerLayer.cpp \
	APLTestTools/MockPhysicalLayerAsync.cpp \
	APLTestTools/MockPhysicalLayerAsyncTS.cpp \
	APLTestTools/MockPhysicalLayerMonitor.cpp \
	APLTestTools/MockPhysicalLayerSource.cpp \
	APLTestTools/MockResponseAcceptor.cpp \
	APLTestTools/MockTimerSource.cpp \
	APLTestTools/MockUpperLayer.cpp \
	DNP3Test/AppLayerTest.cpp \
	DNP3Test/ComparingDataObserver.cpp \
	DNP3Test/DNPHelpers.cpp \
	DNP3Test/IntegrationTest.cpp \
	DNP3Test/LinkLayerRouterTest.cpp \
	DNP3Test/LinkLayerTest.cpp \
	DNP3Test/MasterTestObject.cpp \
	DNP3Test/MockAppLayer.cpp \
	DNP3Test/MockAppUser.cpp \
	DNP3Test/MockFrameSink.cpp \
	DNP3Test/ResponseLoaderTestObject.cpp \
	DNP3Test/SlaveTestObject.cpp \
	DNP3Test/StartupTeardownTest.cpp \
	DNP3Test/TestAPDU.cpp \
	DNP3Test/TestAPDUWriting.cpp \
	DNP3Test/TestAppLayer.cpp \
	DNP3Test/TestCRC.cpp \
	DNP3Test/TestDatabase.cpp \
	DNP3Test/TestEnhancedVtoRouter.cpp \
	DNP3Test/TestEventBufferBase.cpp \
	DNP3Test/TestEventBuffers.cpp \
	DNP3Test/TestIntegration.cpp \
	DNP3Test/TestLinkFrameDNP.cpp \
	DNP3Test/TestLinkLayer.cpp \
	DNP3Test/TestLinkLayerRouter.cpp \
	DNP3Test/TestLinkReceiver.cpp \
	DNP3Test/TestLinkRoute.cpp \
	DNP3Test/TestMaster.cpp \
	DNP3Test/TestObjects.cpp \
	DNP3Test/TestResponseLoader.cpp \
	DNP3Test/TestSlave.cpp \
	DNP3Test/TestSlaveEventBuffer.cpp \
	DNP3Test/TestStartBoostUTF.cpp \
	DNP3Test/TestStartupTeardown.cpp \
	DNP3Test/TestTransportLayer.cpp \
	DNP3Test/TestTransportLoopback.cpp \
	DNP3Test/TestTransportScalability.cpp \
	DNP3Test/TestVtoInterface.cpp \
	DNP3Test/TestVtoLoopbackIntegration.cpp \
	DNP3Test/TestVtoOnewayIntegration.cpp \
	DNP3Test/TestVtoRouter.cpp \
	DNP3Test/TestVtoRouterManager.cpp \
	DNP3Test/TestVtoWriter.cpp \
	DNP3Test/TransportIntegrationStack.cpp \
	DNP3Test/TransportLoopbackTestObject.cpp \
	DNP3Test/TransportScalabilityTestObject.cpp \
	DNP3Test/TransportStackPair.cpp \
	DNP3Test/TransportTestObject.cpp \
	DNP3Test/VtoIntegrationTestBase.cpp

ASTYLE=astyle --options=config/astyle.cfg

DOCBOOK2HTML=docbook2html
DOCBOOK2PDF=docbook2pdf

astyle:
	${ASTYLE}   ${srcdir}/APL/*.cpp            ${srcdir}/APL/*.h
	${ASTYLE}   ${srcdir}/APLTestTools/*.cpp   ${srcdir}/APLTestTools/*.h
	${ASTYLE}   ${srcdir}/DNP3/*.cpp           ${srcdir}/DNP3/*.h
	${ASTYLE}   ${srcdir}/DNP3Test/*.cpp       ${srcdir}/DNP3Test/*.h

docs: docs-html docs-pdf

docs-html:
	${DOCBOOK2HTML} -o docs/html/ docs/main.xml

docs-pdf:
	${DOCBOOK2PDF} -o docs/pdf/ docs/main.xml

include config/autotools/mk/doxygen.mak
include config/autotools/mk/lcov.mak

.PHONY : astyle docs docs-html docs-pdf lcov lcov-report lcov-reset doxygen-run doxygen-doc $(DX_PS_GOAL) $(DX_PDF_GOAL)

