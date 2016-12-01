// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CResultMatch.hpp"

using namespace CBlocking;
 

CResultMatch::CResultMatch(string s, HBlock b) : hasMatch(true)
{
	maptch[s] = b;
}

CResultMatch::CResultMatch(bool r) :hasMatch(r)
{

}

void CResultMatch::append(CResultMatch r)
{
	for(auto &kv: r.maptch)
	{
		maptch[kv.first] = kv.second;
	}
};
