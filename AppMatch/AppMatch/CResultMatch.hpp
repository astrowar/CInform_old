#pragma once
 
#include <map>
#include "BlockInterpreter.hpp"

class CResultMatch
{
public:
	std::map<string, CBlocking::HBlock> maptch;
	bool hasMatch;	
	CResultMatch() : hasMatch(false) {};	
	CResultMatch(string s, CBlocking::HBlock b);
	CResultMatch(bool r);
	void append(const CResultMatch & r);
};
