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