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
#ifndef __CONFIGURE_H_
#define __CONFIGURE_H_

//////////////////////////////////////
//	Set the target platform
//
//	OS specific .h includes use these APL_PLATFORM_X tags to
//	include the correct file.
//////////////////////////////////////


#ifdef WIN32
#define APL_PLATFORM_WIN
#else
#define APL_PLATFORM_LINUX
#endif

/*------ Set optional preprocessor defines ---- */


//if defined, the location is information is compiled into the build for each log call.
#define APL_COMPILE_LOG_LOCATION

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef APL_COMPILE_LOG_LOCATION
#define LOCATION __FILE__ "(" TOSTRING(__LINE__) ")"
#else
#define LOCATION ""
#endif

#endif

