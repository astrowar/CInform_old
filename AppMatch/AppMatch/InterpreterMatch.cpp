#include "CBlockInterpreterRuntime.h"
#include <memory>
#include "CResultMatch.h"
using namespace std;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value)
{
	if (M->matchList.size() != value->lista.size()) return CResultMatch();
	auto mit = M->matchList.begin();
	auto vit = value->lista.begin();
	while (true)
	{
		CResultMatch r = Match(*mit, *vit);


		if (mit == M->matchList.end()) break;
	}

}
 
CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value)
{

	 
	if (auto   mVNamed = dynamic_pointer_cast<CBlockMatchNamed>(M))
	{
		CResultMatch mres = Match(mVNamed->matchInner , value);
		if (mres.hasMatch)
		{
			return CResultMatch(mVNamed->named, value);
		}
		return mres;
	}

	if (HBlockList   vList = dynamic_pointer_cast<CBlockList>(value))
	{
		if (HBlockMatchList   mList = dynamic_pointer_cast<CBlockMatchList>(M))
		{
			
		}
		else
		{
			return CResultMatch();
		}
	}

	if (HBlockNoum    vNoum = dynamic_pointer_cast<CBlockNoum >(value))
	{
		if (auto    mNoum = dynamic_pointer_cast<CBlockMatchAny>(M))
		{
			return CResultMatch("", vNoum);
		}
		else
		{
			return CResultMatch();
		}
	}
	
	return CResultMatch();
}