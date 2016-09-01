#include "CResultMatch.h"

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
