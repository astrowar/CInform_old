#include "CBlockInterpreterRuntime.h"
#include <memory>
#include "CResultMatch.h"
using namespace std;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value)
{
	if (M->matchList.size() != value->lista.size())
	{
		return   CResultMatch(false); //sizes must be equals
	}
	auto mit = M->matchList.begin();
	auto vit = value->lista.begin();
	CResultMatch rAccm = CResultMatch(true);
	while (true)
	{
		if (mit == M->matchList.end()) break;
		CResultMatch r = Match(*mit, *vit);
		if (r.hasMatch ==false ) return   CResultMatch(false);		
		rAccm.append(r);
		++mit;
		++vit;
	}
	return rAccm;

}
 
CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value)
{
	if (auto   mAtom = dynamic_pointer_cast<CBlockMatchNoum>(M))
	{
		if (auto inner = std::dynamic_pointer_cast<CBlockNoum>(mAtom->inner))
			if (auto cinner = std::dynamic_pointer_cast<CBlockNoum>(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				return CResultMatch(inner->named == cinner->named);
			}
	}
	 
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
			return MatchList(mList, vList);
		}
		else
		{
			return CResultMatch(false);
		}
	}

	 
	 
	if (auto    mNoum = dynamic_pointer_cast<CBlockMatchAny>(M))
		{
			return CResultMatch( true );
		}
		 
	 
	
	return CResultMatch(false);
}