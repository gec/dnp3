#ifndef __TOKEN_NODE_H_
#define __TOKEN_NODE_H_

#include <map>
#include <vector>
#include <string>
#include <deque>
#include <assert.h>
#include <sstream>

namespace apl
{
template <class T>
class TokenNode
{
	typedef std::map<std::string, TokenNode<T>*> TokenMap;

public:

	TokenNode(T aValue)
		:
		mHasDefault(true),
		mValue(aValue) {

	}

	TokenNode()
		:
		mHasDefault(false) {

	}

	~TokenNode() {
		typename TokenMap::iterator i = mMap.begin();
		for(; i != mMap.end(); i++) delete (i->second);
	}

	T* GetValue() {
		return &mValue;
	}


	// returns the correct handler for the tokens
	// and modifies the Tokens vector appropriately for the call
	TokenNode* FindNode(std::vector<std::string>& arTokens) {
		if(arTokens.size() == 0) return this;

		typename TokenMap::iterator i = mMap.find(arTokens[0]);

		if(i == mMap.end()) return this; // this node with arguments

		//strip and argument and call the next node
		arTokens.erase(arTokens.begin());
		return (i->second)->FindNode(arTokens);
	}


	TokenNode* AddToken(const std::string& arToken, T aValue) {
		assert(mMap.find(arToken) == mMap.end());
		TokenNode<T>* pToken = new TokenNode<T>(aValue);
		mMap[arToken] = pToken;
		return pToken;
	}


	void SetValue(T aValue) {
		mHasDefault = true;
		mValue = aValue;
	}

	void GetSubNodeNames(std::vector<std::string>& arNames) {
		typename TokenMap::iterator i = mMap.begin();
		for(; i != mMap.end(); i++) arNames.push_back(i->first);
	}

	void GetSubNodesWithOptions(std::vector<std::string>& arNames) {
		typename TokenMap::iterator i = mMap.begin();
		for(; i != mMap.end(); i++) {
			std::vector<std::string> subs;
			i->second->GetSubNodeNames(subs);

			std::ostringstream oss;
			oss << i->first;
			if ( subs.size() > 0 ) {
				oss << " [";
				bool first = true;
				for ( std::vector<std::string>::const_iterator itr = subs.begin(); itr != subs.end(); itr++ ) {
					if ( !first ) oss << "|";
					first = false;
					oss << *itr;
				}
				oss << "]";
			}
			arNames.push_back(oss.str());
		}
	}


private:

	bool mHasDefault;

	T mValue;

	TokenMap mMap;


};
}

#endif
