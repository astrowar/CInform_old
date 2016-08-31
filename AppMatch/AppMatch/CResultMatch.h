#pragma once
 
#include <map>
#include "BlockInterpreter.h"

class CResultMatch
{
public:
	std::map<string, HBlock> maptch;
	bool hasMatch;	
	CResultMatch() : hasMatch(false) {};	
	CResultMatch(string s, HBlock b);
	void append(CResultMatch r);
};
