#include <boost/program_options.hpp>
#include <iostream>
#include "cOptions.h"

using namespace std;

	/**

	Construct and set defaults

	*/
cOptions::cOptions()
		: flagcom(false)
		, flagslave(true)
		, PortName("tcpserver")
		, remote_dnp3(100)
		, local_dnp3(1)
		, ip("127.0.0.1")
		, port( 4999 )
		, meter_reading( 32 )
	{
	serialsets.mBaud = 9600;
	serialsets.mDevice = "COM2";
	serialsets.mDataBits = 8;
	serialsets.mFlowType = apl::FLOW_NONE;
	serialsets.mParity   = apl::PAR_NONE;
	serialsets.mStopBits = 1;

	}
	/**

	Change defaults to appropriate for master

	*/

void cOptions::set_master_defaults()
	{
		flagslave = false;
		remote_dnp3 = 1;
		local_dnp3  = 100;
	}

	/**

	Decode and store

	@return 0 if no error

	*/
int cOptions::decode( int argc, char* argv[] )
	{
		// specify options

		namespace po = boost::program_options;
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("tcp",  "communicate over tcp/ip ( default )")
			("com", "communicate over serial com port")
			("baud", po::value<int>(), "com - baud rate ( default 9600 )")
			("port", po::value<string>(), "port ( e.g. 5 for COM5, or 4999 for tcp )")
			("ip", po::value<string>(), "tcp - ip address (default 127.0.0.1 ( same machine ) )")
			("remote", po::value<int>(), "dnp3 link index for partner( default 100 )")
			("local", po::value<int>(), "dnp3 link index for this( default 1 )")
			("meter", po::value<int>(), "initial meter reading( default 32 )")
			;

		// parse command line
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);    

		// store options changed from defaults

		if (vm.count("help")) {
			cout << desc << "\n";
			return 1;
		}

		if( vm.count("tcp") && vm.count("com") ) {
			cout << "Please choose either TCP or COM, not both" << endl;
			return 1;
		}

		if( vm.count("com") ) {
			// using COM serial port
			flagcom = true;
			PortName = "comserver";
			if( vm.count("port") )
				serialsets.mDevice = "COM" + vm["port"].as<string>();
			if( vm.count("baud") )
				serialsets.mBaud = vm["baud"].as<int>();
		} else {
			// using tcp
			if( vm.count("port") )
				port = atoi( vm["port"].as<string>().c_str() );
			if( vm.count("ip") )
				ip = vm["ip"].as<string>();
		}
		if( vm.count("remote") )
			remote_dnp3 = vm["remote"].as<int>();
		if( vm.count("local") )
			remote_dnp3 = vm["local"].as<int>();

		if( vm.count("meter") )
			meter_reading = vm["meter"].as<int>();


		cout << "Command line parsed OK\n";
		if( flagslave && flagcom ) {
			cout << "Will attempt to connect to master over COM port";
		} else if ( flagslave && ! flagcom ) {
			cout << "Will attempt to connect to master over TCP/IP";
		} else if ( !flagslave && flagcom ) {
			cout << "Will attempt to connect to slave over COM port";
		} else if ( ! flagslave && ! flagcom ) {
			cout << "Will attempt to connect to slave over TCP/IP";
		}

		return 0;

	}

