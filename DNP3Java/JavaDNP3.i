%module(directors="1") javadnp3
%{
/* Includes the header in the wrapper code */

#include <opendnp3/APL/IPhysicalLayerObserver.h>
#include <opendnp3/DNP3/StackManager.h>

using namespace apl;
using namespace apl::dnp;

%}

%pragma(java) jniclasscode=%{
  static {
    if(System.getProperty("org.totalgrid.reef.protocol.dnp3.nostaticload") == null) System.loadLibrary("dnp3java");    
  }
%}

%include <std_string.i>
%include <std_vector.i>

%feature("director"); //generate directors for all classes that have virtual methods

%apply short     { boost::uint8_t  };
%apply char      { boost::int8_t   };
%apply int       { boost::uint16_t };
%apply short     { boost::int16_t  };
%apply long long { boost::uint32_t };
%apply int       { boost::int32_t  };
%apply long long { boost::uint64_t };
%apply long long { boost::int64_t  };

%template(VectorOfString) std::vector<std::string>;

namespace apl{
%rename(boEqual) BinaryOutput::operator==(const BinaryOutput& arRHS) const;
%rename(stEqual) Setpoint::operator==(const Setpoint& arRHS) const;

%rename(bdpEqual) BoolDataPoint::operator==(const BoolDataPoint& rhs);
%rename(tdpEqual) TypedDataPoint::operator==(const TypedDataPoint<T>& rhs);

%rename(get_binary) Binary::operator ValueType() const;
%rename(set_binary) Binary::operator=(ValueType aValue);

%rename(get_controlstatus) ControlStatus::operator ValueType() const;
%rename(set_controlstatus) ControlStatus::operator=(ValueType aValue);

%rename(get_analog) Analog::operator ValueType() const;
%rename(set_analog) Analog::operator=(ValueType aValue);

%rename(get_counter) Counter::operator ValueType() const;
%rename(set_counter) Counter::operator=(ValueType aValue);

%rename(get_setpointstatus) SetpointStatus::operator ValueType() const;
%rename(set_setpointstatus) SetpointStatus::operator=(ValueType aValue);

%rename(PhysLayerStateToString) operator<<(std::ostream& output, PhysicalLayerState aState);

%ignore Transaction::Transaction(ITransactable* apTransactable);
}

%include <opendnp3/APL/Types.h>
%include <opendnp3/APL/INotifier.h>
%include <opendnp3/APL/LogTypes.h>
%include <opendnp3/APL/LogEntry.h>
%include <opendnp3/APL/LogBase.h>
%include <opendnp3/APL/PhysicalLayerStates.h>
%include <opendnp3/APL/IPhysicalLayerObserver.h>
%include <opendnp3/APL/PhysLayerSettings.h>
%include <opendnp3/APL/SerialTypes.h>
%include <opendnp3/APL/QualityMasks.h>
%include <opendnp3/APL/CommandTypes.h>

%include <opendnp3/APL/BaseDataTypes.h>
%template(DoublePoint) apl::TypedDataPoint<double>;
%template(UnsignedPoint) apl::TypedDataPoint<boost::uint32_t>;
%include <opendnp3/APL/DataTypes.h>

%include <opendnp3/APL/ITransactable.h>
%include <opendnp3/APL/DataInterfaces.h>
%include <opendnp3/APL/CommandInterfaces.h>

%include <opendnp3/DNP3/VtoRouterSettings.h>
%include <opendnp3/DNP3/VtoConfig.h>
%template(VectorOfVtoRouterConfig) std::vector<apl::dnp::VtoRouterConfig>;
%include <opendnp3/DNP3/VtoData.h>
%include <opendnp3/DNP3/VtoDataInterface.h>

%include <opendnp3/DNP3/PointClass.h>
%include <opendnp3/DNP3/LinkConfig.h>
%include <opendnp3/DNP3/AppConfig.h>
%include <opendnp3/DNP3/MasterConfigTypes.h>
%include <opendnp3/DNP3/IStackObserver.h>
%include <opendnp3/DNP3/ClassMask.h>

%template(VectorOfExceptionScan) std::vector<apl::dnp::ExceptionScan>;
%include <opendnp3/DNP3/MasterConfig.h>
%include <opendnp3/DNP3/SlaveConfig.h>

%include <opendnp3/DNP3/DeviceTemplateTypes.h>
%template(VectorOfEventPointRecord) std::vector<apl::dnp::EventPointRecord>;
%template(VectorOfDeadbandPointRecord) std::vector<apl::dnp::DeadbandPointRecord>;
%template(VectorOfControlRecord) std::vector<apl::dnp::ControlRecord>;
%template(VectorOfPointRecord) std::vector<apl::dnp::PointRecord>;
%include <opendnp3/DNP3/DeviceTemplate.h>

%include <opendnp3/DNP3/MasterStackConfig.h>
%include <opendnp3/DNP3/SlaveStackConfig.h>


%include <exception.i>
// provide an exception handler for the stack manager
%exception {
	try {
		$action
	}
	catch (apl::Exception ex) {
		SWIG_exception(SWIG_ValueError, ex.what());
	}
	catch (std::exception ex) {
		SWIG_exception(SWIG_ValueError, ex.what());
	}
}


%include <opendnp3/DNP3/StackManager.h>

