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

#ifndef __KEY_KEYS_H_
#define __KEY_KEYS_H_

#include <vector>

namespace apl
{

template <class T, class U>
static std::vector<U> GetKeys(const T& arMap)
{
	std::vector<U> ret;
	for(typename T::const_iterator i = arMap.begin(); i != arMap.end(); ++i) {
		ret.push_back(i->first);
	}
	return ret;
}

}

#endif

