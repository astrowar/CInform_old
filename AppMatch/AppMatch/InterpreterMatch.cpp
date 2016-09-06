#include "CBlockInterpreterRuntime.h"
#include <memory>
#include "CResultMatch.h"
#include <iostream>
#include "QueryStack.h"
using namespace std;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value, QueryStack stk)
{
	if (M->matchList.size() != value->lista.size())
	{
		std::cout << "FAIL  size  " << std::endl;
		(M)->dump("    ");
		(value)->dump("    ");
		return   CResultMatch(false); //sizes must be equals
	}
	auto mit = M->matchList.begin();
	auto vit = value->lista.begin();
	CResultMatch rAccm = CResultMatch(true);
	while (true)
	{
		if (mit == M->matchList.end()) break;
		CResultMatch r = Match(*mit, *vit,stk);
		if (r.hasMatch == false)
		{
			std::cout << "FAIL  item   " << std::endl;
			(*vit)->dump("    ");
			(*mit)->dump("    ");
			return   CResultMatch(false);
		}
		rAccm.append(r);
		++mit;
		++vit;
	}
	return rAccm;

}
 
CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value, QueryStack stk)
{
	if (auto   mAtom = dynamic_pointer_cast<CBlockMatchNoum>(M))
	{
		if (auto inner = std::dynamic_pointer_cast<CBlockNoum>(mAtom->inner))
			if (auto cinner = std::dynamic_pointer_cast<CBlockNoum>(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				cout << inner->named << " == " << cinner->named << endl;
				if (inner->named == cinner->named)
				{
				  return 	CResultMatch(true );
				}

				auto rcc = query_is(cinner, inner, nullptr, stk);
				return CResultMatch(rcc == QEquals);
				 
			}
	}

	if (auto  mAtom = dynamic_pointer_cast<CBlockMatchNoum>(M))
	{
		if (auto inner = std::dynamic_pointer_cast<CBlockNoum>(mAtom->inner))
		{
			if (auto vNoumm = std::dynamic_pointer_cast<CBlockNoum>(value))
			{
				if (vNoumm->named == inner->named)
				{
					return CResultMatch( true );
				}
			}
			if (auto cInst = std::dynamic_pointer_cast<CBlockInstance>(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				//return CResultMatch(inner->named == cinner->named);

				auto r = query_is(cInst, inner, nullptr, stk);
				return CResultMatch(r == QEquals);

			}

			auto rcc = query_is(value, inner, nullptr, stk);
			return CResultMatch(rcc == QEquals);
		}

	}
	 
	if (auto   mVNamed = dynamic_pointer_cast<CBlockMatchNamed>(M))
	{
		CResultMatch mres = Match(mVNamed->matchInner , value,stk);
		if (mres.hasMatch)
		{
			return CResultMatch(mVNamed->named, value);
		}
		return mres;
	}

	if (HBlockMatchList   mList = dynamic_pointer_cast<CBlockMatchList>(M))	 
	{
		if (HBlockList   vList = dynamic_pointer_cast<CBlockList>(value))
		{
			return MatchList(mList, vList,stk);
		}
		else
		{
			return CResultMatch(false);
		}
	}

	if (HBlockMatchAND   mAnnd = dynamic_pointer_cast<CBlockMatchAND>(M))
	{
		for(auto& mItem : mAnnd->matchList)
		{
			auto rAnnd =  Match(mItem, value, stk);
			if (rAnnd.hasMatch == false )
			{
				return CResultMatch(false);
			}
		}		
		return CResultMatch(true);
		
	}



	if (HBlockMatchProperty   mProp = dynamic_pointer_cast<CBlockMatchProperty>(M))
	{
		if (HBlockProperty    vProp = dynamic_pointer_cast<CBlockProperty>(value))
		{

			auto rProp = query_is( mProp->prop , vProp->prop, nullptr, stk);
			if (rProp == QEquals)
			{
				CResultMatch mres =  Match(mProp->obj, vProp->obj, stk);
				return mres;
			}
		}
		else
		{
			return CResultMatch(false);
		}
	}
	

	if (HBlockMatchDirectIs   mDirect = dynamic_pointer_cast<CBlockMatchDirectIs>(M))
	{
		if (HBlockAssertion_isDirectAssign   vDirect = dynamic_pointer_cast<CBlockAssertion_isDirectAssign>(value))
		{
			CResultMatch mres = Match(mDirect->obj, vDirect->get_obj()  , stk);
			if (mres.hasMatch)
			{
				CResultMatch mres_k = Match(mDirect->value, vDirect->value , stk);
				if (mres_k.hasMatch)
				{
					mres.append(mres_k);
					return mres;

				}
			}	
			else
			{
				return CResultMatch(false);
			}
		}
	}


	if (auto    mNoum = dynamic_pointer_cast<CBlockMatchAny>(M))
		{
			return CResultMatch( true );
		}
		 
	 
	
	return CResultMatch(false);
}