#include "apl/serialtypes.h"

/**

  Decode and store command line options for master/slave demo

*/
class cOptions
{
public:
	bool			flagcom;				///< true if using COM serial port
	bool			flagslave;				///< true if slave
	apl::SerialSettings	serialsets;				///< COM serial port settings
	std::string		PortName;				///< DNP3 name for partner
	unsigned		remote_dnp3;			///< DNP3 index for partner
	unsigned		local_dnp3;				///< DNP3 index for this
	std::string		ip;						///< ip address
	unsigned		port;					///< ip port
	int				meter_reading;			///

	/**

	Construct and set defaults

	*/
	cOptions();
;	/**

	Change defaults to appropriate for master

	*/

	void set_master_defaults();
;
	/**

	Decode and store

	@return 0 if no error

	*/
	int decode( int argc, char* argv[] );


};		// end of cOptions