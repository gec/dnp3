/* ******************************
	GENERATED CONTENT DO NOT ALTER!
*********************************
*/
#ifndef _APLXML_BASE_H_
#define _APLXML_BASE_H_
#include <APLXML/tinybinding.h>
using namespace std;
namespace APLXML_Base {
enum BaudRateEnum {
	BAUDRATE_1200,
	BAUDRATE_1800,
	BAUDRATE_2400,
	BAUDRATE_4800,
	BAUDRATE_9600,
	BAUDRATE_19200,
	BAUDRATE_38400,
	BAUDRATE_57600,
	BAUDRATE_115200,
	BAUDRATE_230400,
};
	BaudRateEnum FromString_BaudRateEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_BaudRateEnum(BaudRateEnum aValue);

enum DBitsEnum {
	DATABITS_7,
	DATABITS_8,
};
	DBitsEnum FromString_DBitsEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_DBitsEnum(DBitsEnum aValue);

enum FlowControlEnum {
	FLOW_NONE,
	FLOW_HARDWARE,
	FLOW_XONXOFF,
};
	FlowControlEnum FromString_FlowControlEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_FlowControlEnum(FlowControlEnum aValue);

enum LogLevelEnum {
	LOG_DEBUG,
	LOG_COMM,
	LOG_INTERPRET,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_EVENT,
};
	LogLevelEnum FromString_LogLevelEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_LogLevelEnum(LogLevelEnum aValue);

enum ParityEnum {
	PARITY_NONE,
	PARITY_EVEN,
	PARITY_ODD,
};
	ParityEnum FromString_ParityEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_ParityEnum(ParityEnum aValue);

class PhysicalLayerDescriptor_t : public IXMLDataBound {
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Name;
	int OpenRetryMS;
};
enum StopBitsEnum {
	STOPBITS_0,
	STOPBITS_1,
	STOPBITS_2,
};
	StopBitsEnum FromString_StopBitsEnum(TiXmlNode* apParent, const char* aValue);
	string ToString_StopBitsEnum(StopBitsEnum aValue);

class TCPv4Client_t : public APLXML_Base::PhysicalLayerDescriptor_t{
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Address;
	int Port;
};

class TCPv4Server_t : public APLXML_Base::PhysicalLayerDescriptor_t{
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Endpoint;
	int Port;
};

class TCPv6Client_t : public APLXML_Base::PhysicalLayerDescriptor_t{
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Address;
	int Port;
};
class TCPv6Server_t : public APLXML_Base::PhysicalLayerDescriptor_t{
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Endpoint;
	int Port;
};

class Log_t : public IXMLDataBound {
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	LogLevelEnum Filter;
};
class Serial_t : public APLXML_Base::PhysicalLayerDescriptor_t{
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	string Device;
	BaudRateEnum BaudRate;
	ParityEnum Parity;
	DBitsEnum DBits;
	StopBitsEnum StopBits;
	FlowControlEnum FlowControl;
};
#ifdef SWIG
}
%template(Serial_c) std::vector<APLXML_Base::Serial_t*>;
namespace APLXML_Base{
#endif
#ifdef SWIG
}
%template(TCPv4Client_c) std::vector<APLXML_Base::TCPv4Client_t*>;
namespace APLXML_Base{
#endif
#ifdef SWIG
}
%template(TCPv4Server_c) std::vector<APLXML_Base::TCPv4Server_t*>;
namespace APLXML_Base{
#endif
#ifdef SWIG
}
%template(TCPv6Client_c) std::vector<APLXML_Base::TCPv6Client_t*>;
namespace APLXML_Base{
#endif
#ifdef SWIG
}
%template(TCPv6Server_c) std::vector<APLXML_Base::TCPv6Server_t*>;
namespace APLXML_Base{
#endif
class PhysicalLayerList_t : public IXMLDataBound {
public:
	void toXml(TiXmlNode* pParent, bool aCreateNode, bool aIgnoreValid);
	void fromXml(TiXmlNode* pNode);
	PhysicalLayerList_t();

#ifdef SWIG
%immutable TCPv4ServerVector;
#endif
	private: collectedType < TCPv4Server_t > TCPv4Server;
	public: vector < TCPv4Server_t* >& TCPv4ServerVector;
#ifdef SWIG
%immutable TCPv4ClientVector;
#endif
	private: collectedType < TCPv4Client_t > TCPv4Client;
	public: vector < TCPv4Client_t* >& TCPv4ClientVector;

#ifdef SWIG
%immutable TCPv6ServerVector;
#endif
	private: collectedType < TCPv6Server_t > TCPv6Server;
	public: vector < TCPv6Server_t* >& TCPv6ServerVector;
#ifdef SWIG
%immutable TCPv6ClientVector;
#endif
	private: collectedType < TCPv6Client_t > TCPv6Client;
	public: vector < TCPv6Client_t* >& TCPv6ClientVector;

#ifdef SWIG
%immutable SerialVector;
#endif
	private: collectedType < Serial_t > Serial;
	public: vector < Serial_t* >& SerialVector;
};
}
#endif

