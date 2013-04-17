#
# Copyright (c) 2010, 2011 Green Energy Corp.
# All rights reserved.
#

ACLOCAL_AMFLAGS = -I config/autotools/m4

CORE_BOOST_LIBS  = $(BOOST_DATE_TIME_LIB) $(BOOST_THREAD_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SYSTEM_LIB)
TEST_BOOST_LIBS  = $(CORE_BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB)

AM_CXXFLAGS = $(BOOST_CPPFLAGS) -DBOOST_TEST_DYN_LINK -DBOOST_ASIO_ENABLE_CANCELIO -DBOOST_REGEX_NO_LIB
AM_LDFLAGS  = $(BOOST_LDFLAGS)

# Dummy placeholder to allow for expansion later
BUILT_SOURCES =

lib_LTLIBRARIES = libopendnp3.la

libopendnp3_la_LDFLAGS = -version-info 0:0:0
libopendnp3_la_LIBADD = $(BOOST_LDFLAGS) $(CORE_BOOST_LIBS)
libopendnp3_la_DEPENDENCIES =
libopendnp3_la_SOURCES = \
	opendnp3/APL/ASIOSerialHelpers.cpp \
	opendnp3/APL/AsyncLayerInterfaces.cpp \
	opendnp3/APL/AsyncResult.cpp \
	opendnp3/APL/AsyncTaskBase.cpp \
	opendnp3/APL/AsyncTaskContinuous.cpp \
	opendnp3/APL/AsyncTaskGroup.cpp \
	opendnp3/APL/AsyncTaskNonPeriodic.cpp \
	opendnp3/APL/AsyncTaskPeriodic.cpp \
	opendnp3/APL/AsyncTaskScheduler.cpp \
	opendnp3/APL/BaseDataTypes.cpp \
	opendnp3/APL/CommandManager.cpp \
	opendnp3/APL/CommandQueue.cpp \
	opendnp3/APL/CommandResponseQueue.cpp \
	opendnp3/APL/CommandTypes.cpp \
	opendnp3/APL/CopyableBuffer.cpp \
	opendnp3/APL/CRC.cpp \
	opendnp3/APL/EventLock.cpp \
	opendnp3/APL/Exception.cpp \
	opendnp3/APL/FlexibleDataObserver.cpp \
	opendnp3/APL/IHandlerAsync.cpp \
	opendnp3/APL/ITimerSource.cpp \
	opendnp3/APL/IOService.cpp \
	opendnp3/APL/IOServiceThread.cpp \
	opendnp3/APL/LockBase.cpp \
	opendnp3/APL/LockBoost.cpp \
	opendnp3/APL/Log.cpp \
	opendnp3/APL/LogEntryCircularBuffer.cpp \
	opendnp3/APL/LogEntry.cpp \
	opendnp3/APL/Loggable.cpp \
	opendnp3/APL/Logger.cpp \
	opendnp3/APL/LogToFile.cpp \
	opendnp3/APL/LogToStdio.cpp \
	opendnp3/APL/LogTypes.cpp \
	opendnp3/APL/LowerLayerToPhysAdapter.cpp \
	opendnp3/APL/MetricBuffer.cpp \
	opendnp3/APL/MultiplexingDataObserver.cpp \
	opendnp3/APL/PackingUnpacking.cpp \
	opendnp3/APL/Parsing.cpp \
	opendnp3/APL/PhysicalLayerAsyncBase.cpp \
	opendnp3/APL/PhysicalLayerAsyncBaseTCP.cpp \
	opendnp3/APL/PhysicalLayerAsyncSerial.cpp \
	opendnp3/APL/PhysicalLayerAsyncTCPClient.cpp \
	opendnp3/APL/PhysicalLayerAsyncTCPServer.cpp \
	opendnp3/APL/PhysicalLayerFactory.cpp \
	opendnp3/APL/PhysicalLayerInstance.cpp \
	opendnp3/APL/PhysicalLayerManager.cpp \
	opendnp3/APL/PhysicalLayerMap.cpp \
	opendnp3/APL/PhysicalLayerMonitor.cpp \
	opendnp3/APL/PhysicalLayerMonitorStates.cpp \
	opendnp3/APL/PhysicalLayerStates.cpp \
	opendnp3/APL/PhysLoopback.cpp \
	opendnp3/APL/PostingNotifier.cpp \
	opendnp3/APL/PostingNotifierSource.cpp \
	opendnp3/APL/ProtocolUtil.cpp \
	opendnp3/APL/QualityConverter.cpp \
	opendnp3/APL/RandomizedBuffer.cpp \
	opendnp3/APL/ShiftableBuffer.cpp \
	opendnp3/APL/SuspendTimerSource.cpp \
	opendnp3/APL/Threadable.cpp \
	opendnp3/APL/ThreadBase.cpp \
	opendnp3/APL/ThreadBoost.cpp \
	opendnp3/APL/TimeBase.cpp \
	opendnp3/APL/TimeBoost.cpp \
	opendnp3/APL/Timeout.cpp \
	opendnp3/APL/TimerASIO.cpp \
	opendnp3/APL/TimerSourceASIO.cpp \
	opendnp3/APL/TimeSource.cpp \
	opendnp3/APL/TimingTools.cpp \
	opendnp3/APL/ToHex.cpp \
	opendnp3/APL/TrackingTaskGroup.cpp \
	opendnp3/APL/Util.cpp \
	opendnp3/DNP3/AlwaysOpeningVtoRouter.cpp \
	opendnp3/DNP3/APDUConstants.cpp \
	opendnp3/DNP3/APDU.cpp \
	opendnp3/DNP3/AppChannelStates.cpp \
	opendnp3/DNP3/AppHeader.cpp \
	opendnp3/DNP3/AppInterfaces.cpp \
	opendnp3/DNP3/AppLayerChannel.cpp \
	opendnp3/DNP3/AppLayer.cpp \
	opendnp3/DNP3/AsyncStackManager.cpp \
	opendnp3/DNP3/BufferTypes.cpp \
	opendnp3/DNP3/ClassCounter.cpp \
	opendnp3/DNP3/ControlTasks.cpp \
	opendnp3/DNP3/Database.cpp \
	opendnp3/DNP3/DataPoll.cpp \
	opendnp3/DNP3/DeviceTemplate.cpp \
	opendnp3/DNP3/DNPCommandMaster.cpp \
	opendnp3/DNP3/DNPCrc.cpp \
	opendnp3/DNP3/EnhancedVto.cpp \
	opendnp3/DNP3/EnhancedVtoRouter.cpp \
	opendnp3/DNP3/HeaderReadIterator.cpp \
	opendnp3/DNP3/IndexedWriteIterator.cpp \
	opendnp3/DNP3/IStackObserver.cpp \
	opendnp3/DNP3/LinkChannel.cpp \
	opendnp3/DNP3/LinkFrame.cpp \
	opendnp3/DNP3/LinkHeader.cpp \
	opendnp3/DNP3/LinkLayerConstants.cpp \
	opendnp3/DNP3/LinkLayer.cpp \
	opendnp3/DNP3/LinkLayerReceiver.cpp \
	opendnp3/DNP3/LinkLayerRouter.cpp \
	opendnp3/DNP3/LinkReceiverStates.cpp \
	opendnp3/DNP3/LinkRoute.cpp \
	opendnp3/DNP3/Master.cpp \
	opendnp3/DNP3/MasterSchedule.cpp \
	opendnp3/DNP3/MasterStack.cpp \
	opendnp3/DNP3/MasterStates.cpp \
	opendnp3/DNP3/MasterTaskBase.cpp \
	opendnp3/DNP3/ObjectHeader.cpp \
	opendnp3/DNP3/ObjectInterfaces.cpp \
	opendnp3/DNP3/ObjectReadIterator.cpp \
	opendnp3/DNP3/Objects.cpp \
	opendnp3/DNP3/ObjectWriteIterator.cpp \
	opendnp3/DNP3/PointClass.cpp \
	opendnp3/DNP3/PriLinkLayerStates.cpp \
	opendnp3/DNP3/ResponseContext.cpp \
	opendnp3/DNP3/ResponseLoader.cpp \
	opendnp3/DNP3/SecLinkLayerStates.cpp \
	opendnp3/DNP3/SlaveConfig.cpp \
	opendnp3/DNP3/Slave.cpp \
	opendnp3/DNP3/SlaveEventBuffer.cpp \
	opendnp3/DNP3/SlaveResponseTypes.cpp \
	opendnp3/DNP3/SlaveStack.cpp \
	opendnp3/DNP3/SlaveStates.cpp \
	opendnp3/DNP3/SolicitedChannel.cpp \
	opendnp3/DNP3/Stack.cpp \
	opendnp3/DNP3/StackManager.cpp \
	opendnp3/DNP3/StartupTasks.cpp \
	opendnp3/DNP3/TLS_Base.cpp \
	opendnp3/DNP3/TransportLayer.cpp \
	opendnp3/DNP3/TransportRx.cpp \
	opendnp3/DNP3/TransportStates.cpp \
	opendnp3/DNP3/TransportTx.cpp \
	opendnp3/DNP3/UnsolicitedChannel.cpp \
	opendnp3/DNP3/VtoData.cpp \
	opendnp3/DNP3/VtoReader.cpp \
	opendnp3/DNP3/VtoRouter.cpp \
	opendnp3/DNP3/VtoRouterManager.cpp \
	opendnp3/DNP3/VtoRouterSettings.cpp \
	opendnp3/DNP3/VtoTransmitTask.cpp \
	opendnp3/DNP3/VtoWriter.cpp

if WANT_JAVA
JAVA_DIR=$(top_srcdir)/java
JAVA_PACKAGE_DIR=org/totalgrid/reef/protocol/dnp3
JAVA_SOURCE_DIR=$(JAVA_DIR)/src
JAVA_CLASS_DIR=$(JAVA_DIR)/bin

JAVA_SRC_FILES =
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/Analog.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/AnalogQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/AppConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/Binary.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/BinaryOutput.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/BinaryQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/BoolDataPoint.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ClassMask.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CommandModes.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CommandRequest.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CommandResponse.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CommandStatus.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CommandTypes.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ControlCode.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ControlQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ControlRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ControlStatus.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/Counter.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/CounterQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/DataPoint.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/DataTypes.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/DeadbandPointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/DeviceTemplate.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/DoublePoint.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/EventMaxConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/EventPointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ExceptionScan.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/FilterAssoc.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/FilterLevel.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/FixedCommandHandler.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/FlowType.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/GrpVar.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ICommandAcceptor.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ICommandHandler.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ICommandSource.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/IDataObserver.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ILogBase.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/INotifier.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/IPhysicalLayerObserver.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/IResponseAcceptor.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/IStackObserver.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ITransactable.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/LinkConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/LogEntry.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/LogTypes.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/MasterConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/MasterStackConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/ParityType.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/PhysLayerSettings.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/PhysicalLayerState.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/PointClass.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/PointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SWIGTYPE_p_boost__int64_t.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SWIGTYPE_p_boost__uint8_t.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SWIGTYPE_p_int.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SWIGTYPE_p_std__ostream.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SWIGTYPE_p_std__string.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SerialSettings.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/Setpoint.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SetpointEncodingType.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SetpointQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SetpointStatus.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SlaveConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/SlaveStackConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/StackManager.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/StackStates.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/Transaction.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/UnsignedPoint.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfControlRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfDeadbandPointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfEventPointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfExceptionScan.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfPointRecord.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfString.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VectorOfVtoRouterConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoData.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoDataType.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoQuality.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoRouterConfig.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/VtoRouterSettings.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/javadnp3.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/javadnp3Constants.java
JAVA_SRC_FILES += $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)/javadnp3JNI.java

DNP3Java/.java-built: DNP3Java/JavaDNP3.i
	-@mkdir -p $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR)
	swig -c++ -java \
		-package org.totalgrid.reef.protocol.dnp3 \
		-I$(top_srcdir) -I$(top_srcdir)/APL -I$(top_srcdir)/DNP3 \
		-outdir $(JAVA_SOURCE_DIR)/$(JAVA_PACKAGE_DIR) \
		-o DNP3Java/JavaDNP3.cpp $^
	touch $@

DNP3Java/JavaDNP3.cpp: DNP3Java/.java-built
$(JAVA_SRC_FILES): DNP3Java/.java-built

opendnp3.jar: DNP3Java/.java-built
	-@mkdir -p $(JAVA_CLASS_DIR)/$(JAVA_PACKAGE_DIR)
	cd $(JAVA_SOURCE_DIR) && javac -d $(JAVA_CLASS_DIR) -cp . $(JAVA_SRC_FILES)
	cd $(JAVA_CLASS_DIR) && jar cvf $@ org
	mv $(JAVA_CLASS_DIR)/$@ $@

opendnp3_jardir = $(datadir)/java
opendnp3_jar_DATA = opendnp3.jar

BUILT_SOURCES += DNP3Java/.java-built DNP3Java/JavaDNP3.cpp opendnp3.jar $(JAVA_SRC_FILES)
libopendnp3_la_DEPENDENCIES += DNP3Java/JavaDNP3.cpp
libopendnp3_la_SOURCES += DNP3Java/JavaDNP3.cpp
endif

if WANT_PYTHON
pkgpython_PYTHON = pyopendnp3.py __init__.py
pkgpyexec_LTLIBRARIES = _pyopendnp3.la
_pyopendnp3_la_SOURCES = DNP3Java/PythonDNP3.cpp
_pyopendnp3_la_CPPFLAGS = $(SWIG_PYTHON_CPPFLAGS) $(PYTHON_CPPFLAGS)
_pyopendnp3_la_LDFLAGS = -module $(PYTHON_LDFLAGS)
_pyopendnp3_la_LIBADD = libopendnp3.la

__init__.py:
	echo "from pyopendnp3 import *" > $@

DNP3Java/PythonDNP3.cpp: DNP3Java/JavaDNP3.i
	swig -c++ -python -threads \
		-module pyopendnp3 \
		-I$(top_srcdir) -I$(top_srcdir)/APL -I$(top_srcdir)/DNP3 \
		-outdir $(top_srcdir) \
		-o DNP3Java/PythonDNP3.cpp $^

BUILT_SOURCES += DNP3Java/PythonDNP3.cpp
endif

aplheadersdir = $(pkgincludedir)/APL
dnpheadersdir = $(pkgincludedir)/DNP3

pkginclude_HEADERS = opendnp3/version.hpp

aplheaders_HEADERS = \
	opendnp3/APL/ASIOSerialHelpers.h \
	opendnp3/APL/AsyncLayerInterfaces.h \
	opendnp3/APL/AsyncResult.h \
	opendnp3/APL/AsyncTaskBase.h \
	opendnp3/APL/AsyncTaskContinuous.h \
	opendnp3/APL/AsyncTaskGroup.h \
	opendnp3/APL/AsyncTaskInterfaces.h \
	opendnp3/APL/AsyncTaskNonPeriodic.h \
	opendnp3/APL/AsyncTaskPeriodic.h \
	opendnp3/APL/AsyncTaskScheduler.h \
	opendnp3/APL/BaseDataTypes.h \
	opendnp3/APL/BoundNotifier.h \
	opendnp3/APL/CachedLogVariable.h \
	opendnp3/APL/ChangeBuffer.h \
	opendnp3/APL/CommandInterfaces.h \
	opendnp3/APL/CommandManager.h \
	opendnp3/APL/CommandQueue.h \
	opendnp3/APL/CommandResponseQueue.h \
	opendnp3/APL/CommandTypes.h \
	opendnp3/APL/Configure.h \
	opendnp3/APL/CopyableBuffer.h \
	opendnp3/APL/CRC.h \
	opendnp3/APL/DataInterfaces.h \
	opendnp3/APL/DataTypes.h \
	opendnp3/APL/DeleteAny.h \
	opendnp3/APL/EventLockBase.h \
	opendnp3/APL/EventLock.h \
	opendnp3/APL/EventSet.h \
	opendnp3/APL/Exception.h \
	opendnp3/APL/FlexibleDataObserver.h \
	opendnp3/APL/Function.h \
	opendnp3/APL/GetKeys.h \
	opendnp3/APL/IEventLock.h \
	opendnp3/APL/IHandlerAsync.h \
	opendnp3/APL/INotifier.h \
	opendnp3/APL/IOService.h \
	opendnp3/APL/IOServiceThread.h \
	opendnp3/APL/IPhysicalLayerAsync.h \
	opendnp3/APL/IPhysicalLayerObserver.h \
	opendnp3/APL/IPhysicalLayerSource.h \
	opendnp3/APL/ISubject.h \
	opendnp3/APL/ITimer.h \
	opendnp3/APL/ITimerSource.h \
	opendnp3/APL/ITimeSource.h \
	opendnp3/APL/ITransactable.h \
	opendnp3/APL/LockBase.h \
	opendnp3/APL/LockBoost.h \
	opendnp3/APL/Lock.h \
	opendnp3/APL/LogBase.h \
	opendnp3/APL/LogEntryCircularBuffer.h \
	opendnp3/APL/LogEntry.h \
	opendnp3/APL/Loggable.h \
	opendnp3/APL/Logger.h \
	opendnp3/APL/Log.h \
	opendnp3/APL/LogToFile.h \
	opendnp3/APL/LogToStdio.h \
	opendnp3/APL/LogTypes.h \
	opendnp3/APL/LogVar.h \
	opendnp3/APL/LowerLayerToPhysAdapter.h \
	opendnp3/APL/MetricBuffer.h \
	opendnp3/APL/MultiplexingDataObserver.h \
	opendnp3/APL/Notifier.h \
	opendnp3/APL/PackingTemplates.h \
	opendnp3/APL/PackingUnpacking.h \
	opendnp3/APL/Parsing.h \
	opendnp3/APL/PhysicalLayerAsyncASIO.h \
	opendnp3/APL/PhysicalLayerAsyncBase.h \
	opendnp3/APL/PhysicalLayerAsyncBaseTCP.h \
	opendnp3/APL/PhysicalLayerAsyncSerial.h \
	opendnp3/APL/PhysicalLayerAsyncTCPClient.h \
	opendnp3/APL/PhysicalLayerAsyncTCPServer.h \
	opendnp3/APL/PhysicalLayerAsyncTCPv4Client.h \
	opendnp3/APL/PhysicalLayerAsyncTCPv4Server.h \
	opendnp3/APL/PhysicalLayerAsyncTCPv6Client.h \
	opendnp3/APL/PhysicalLayerAsyncTCPv6Server.h \
	opendnp3/APL/PhysicalLayerFactory.h \
	opendnp3/APL/PhysicalLayerFunctors.h \
	opendnp3/APL/PhysicalLayerInstance.h \
	opendnp3/APL/PhysicalLayerManager.h \
	opendnp3/APL/PhysicalLayerMap.h \
	opendnp3/APL/PhysicalLayerMonitor.h \
	opendnp3/APL/PhysicalLayerMonitorStates.h \
	opendnp3/APL/PhysicalLayerStates.h \
	opendnp3/APL/PhysLayerSettings.h \
	opendnp3/APL/PhysLoopback.h \
	opendnp3/APL/PostingNotifier.h \
	opendnp3/APL/PostingNotifierSource.h \
	opendnp3/APL/ProtocolUtil.h \
	opendnp3/APL/QualityConverter.h \
	opendnp3/APL/QualityMasks.h \
	opendnp3/APL/QueueingFDO.h \
	opendnp3/APL/Random.h \
	opendnp3/APL/RandomDouble.h \
	opendnp3/APL/RandomizedBuffer.h \
	opendnp3/APL/SerialTypes.h \
	opendnp3/APL/ShiftableBuffer.h \
	opendnp3/APL/Singleton.h \
	opendnp3/APL/SubjectBase.h \
	opendnp3/APL/SuspendTimerSource.h \
	opendnp3/APL/SyncVar.h \
	opendnp3/APL/Threadable.h \
	opendnp3/APL/ThreadBase.h \
	opendnp3/APL/ThreadBoost.h \
	opendnp3/APL/Thread.h \
	opendnp3/APL/TimeBase.h \
	opendnp3/APL/TimeBoost.h \
	opendnp3/APL/Timeout.h \
	opendnp3/APL/TimerASIO.h \
	opendnp3/APL/TimerSourceASIO.h \
	opendnp3/APL/TimeSource.h \
	opendnp3/APL/TimeTypes.h \
	opendnp3/APL/TimingTools.h \
	opendnp3/APL/ToHex.h \
	opendnp3/APL/TrackingTaskGroup.h \
	opendnp3/APL/Types.h \
	opendnp3/APL/Uncopyable.h \
	opendnp3/APL/Util.h

dnpheaders_HEADERS = \
	opendnp3/DNP3/AlwaysOpeningVtoRouter.h \
	opendnp3/DNP3/APDUConstants.h \
	opendnp3/DNP3/APDU.h \
	opendnp3/DNP3/AppChannelStates.h \
	opendnp3/DNP3/AppConfig.h \
	opendnp3/DNP3/AppHeader.h \
	opendnp3/DNP3/AppInterfaces.h \
	opendnp3/DNP3/AppLayerChannel.h \
	opendnp3/DNP3/AppLayer.h \
	opendnp3/DNP3/AsyncStackManager.h \
	opendnp3/DNP3/BufferSetTypes.h \
	opendnp3/DNP3/BufferTypes.h \
	opendnp3/DNP3/ClassCounter.h \
	opendnp3/DNP3/ClassMask.h \
	opendnp3/DNP3/ControlTasks.h \
	opendnp3/DNP3/CTOHistory.h \
	opendnp3/DNP3/Database.h \
	opendnp3/DNP3/DatabaseInterfaces.h \
	opendnp3/DNP3/DataPoll.h \
	opendnp3/DNP3/DeviceTemplate.h \
	opendnp3/DNP3/DeviceTemplateTypes.h \
	opendnp3/DNP3/DNPCommandMaster.h \
	opendnp3/DNP3/DNPConstants.h \
	opendnp3/DNP3/DNPCrc.h \
	opendnp3/DNP3/DNPDatabaseTypes.h \
	opendnp3/DNP3/DNPExceptions.h \
	opendnp3/DNP3/DNPFromStream.h \
	opendnp3/DNP3/DNPToStream.h \
	opendnp3/DNP3/EnhancedVto.h \
	opendnp3/DNP3/EnhancedVtoRouter.h \
	opendnp3/DNP3/EventBufferBase.h \
	opendnp3/DNP3/EventBuffers.h \
	opendnp3/DNP3/EventTypes.h \
	opendnp3/DNP3/HeaderReadIterator.h \
	opendnp3/DNP3/IFrameSink.h \
	opendnp3/DNP3/ILinkContext.h \
	opendnp3/DNP3/ILinkRouter.h \
	opendnp3/DNP3/IndexedWriteIterator.h \
	opendnp3/DNP3/IStackObserver.h \
	opendnp3/DNP3/IVtoEventAcceptor.h \
	opendnp3/DNP3/LinkChannel.h \
	opendnp3/DNP3/LinkConfig.h \
	opendnp3/DNP3/LinkFrame.h \
	opendnp3/DNP3/LinkHeader.h \
	opendnp3/DNP3/LinkLayerConstants.h \
	opendnp3/DNP3/LinkLayer.h \
	opendnp3/DNP3/LinkLayerReceiver.h \
	opendnp3/DNP3/LinkLayerRouter.h \
	opendnp3/DNP3/LinkReceiverStates.h \
	opendnp3/DNP3/LinkRoute.h \
	opendnp3/DNP3/MasterConfig.h \
	opendnp3/DNP3/MasterConfigTypes.h \
	opendnp3/DNP3/Master.h \
	opendnp3/DNP3/MasterSchedule.h \
	opendnp3/DNP3/MasterStackConfig.h \
	opendnp3/DNP3/MasterStack.h \
	opendnp3/DNP3/MasterStates.h \
	opendnp3/DNP3/MasterTaskBase.h \
	opendnp3/DNP3/ObjectHeader.h \
	opendnp3/DNP3/ObjectInterfaces.h \
	opendnp3/DNP3/ObjectReadIterator.h \
	opendnp3/DNP3/Objects.h \
	opendnp3/DNP3/ObjectWriteIterator.h \
	opendnp3/DNP3/PointClass.h \
	opendnp3/DNP3/PriLinkLayerStates.h \
	opendnp3/DNP3/ResponseContext.h \
	opendnp3/DNP3/ResponseLoader.h \
	opendnp3/DNP3/SecLinkLayerStates.h \
	opendnp3/DNP3/SlaveConfig.h \
	opendnp3/DNP3/SlaveEventBuffer.h \
	opendnp3/DNP3/Slave.h \
	opendnp3/DNP3/SlaveResponseTypes.h \
	opendnp3/DNP3/SlaveStackConfig.h \
	opendnp3/DNP3/SlaveStack.h \
	opendnp3/DNP3/SlaveStates.h \
	opendnp3/DNP3/SolicitedChannel.h \
	opendnp3/DNP3/Stack.h \
	opendnp3/DNP3/StackManager.h \
	opendnp3/DNP3/StartupTasks.h \
	opendnp3/DNP3/TLS_Base.h \
	opendnp3/DNP3/TransportConstants.h \
	opendnp3/DNP3/TransportLayer.h \
	opendnp3/DNP3/TransportRx.h \
	opendnp3/DNP3/TransportStates.h \
	opendnp3/DNP3/TransportTx.h \
	opendnp3/DNP3/UnsolicitedChannel.h \
	opendnp3/DNP3/VtoConfig.h \
	opendnp3/DNP3/VtoData.h \
	opendnp3/DNP3/VtoDataInterface.h \
	opendnp3/DNP3/VtoEventBufferAdapter.h \
	opendnp3/DNP3/VtoReader.h \
	opendnp3/DNP3/VtoRouter.h \
	opendnp3/DNP3/VtoRouterManager.h \
	opendnp3/DNP3/VtoRouterSettings.h \
	opendnp3/DNP3/VtoTransmitTask.h \
	opendnp3/DNP3/VtoWriter.h

bin_PROGRAMS = testset

testset_LDADD = libopendnp3.la $(CORE_BOOST_LIBS)
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

noinst_PROGRAMS = dnp3test demo-master-cpp demo-slave-cpp

dnp3test_LDADD = libopendnp3.la $(TEST_BOOST_LIBS)
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
	APLTestTools/PhysicalLayerWrapper.cpp \
	APLTestTools/WrappedTcpPipe.cpp \
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

demo_master_cpp_LDADD = libopendnp3.la
demo_master_cpp_SOURCES = \
	demos/master-cpp/DemoMain.cpp \
	demos/master-cpp/MasterDemo.cpp

demo_slave_cpp_LDADD = libopendnp3.la
demo_slave_cpp_SOURCES = \
	demos/slave-cpp/DemoMain.cpp \
	demos/slave-cpp/SlaveDemo.cpp

ASTYLE=astyle --options=config/astyle.cfg

DOCBOOK2HTML=docbook2html
DOCBOOK2PDF=docbook2pdf

astyle:
	${ASTYLE}   ${srcdir}/opendnp3/APL/*.cpp   ${srcdir}/opendnp3/APL/*.h
	${ASTYLE}   ${srcdir}/APLTestTools/*.cpp   ${srcdir}/APLTestTools/*.h
	${ASTYLE}   ${srcdir}/opendnp3/DNP3/*.cpp  ${srcdir}/opendnp3/DNP3/*.h
	${ASTYLE}   ${srcdir}/DNP3Test/*.cpp       ${srcdir}/DNP3Test/*.h

docs: docs-html docs-pdf

docs-html:
	${DOCBOOK2HTML} -o docs/html/ docs/main.xml

docs-pdf:
	${DOCBOOK2PDF} -o docs/pdf/ docs/main.xml

include config/autotools/mk/doxygen.mak
include config/autotools/mk/lcov.mak

clean-swig:
	-rm -rf DNP3Java/JavaDNP3.cpp DNP3Java/JavaDNP3.h DNP3Java/.java-built
	-rm -rf DNP3Java/PythonDNP3.cpp DNP3Java/PythonDNP3.h
	-rm -rf pyopendnp3.py pyopendnp3.pyc __init__.py
	-rm -rf $(top_srcdir)/java
	-rm -rf opendnp3.jar

clean-local: clean-swig clean-lcov

.PHONY : astyle docs docs-html docs-pdf lcov lcov-report lcov-reset doxygen-run doxygen-doc $(DX_PS_GOAL) $(DX_PDF_GOAL)

