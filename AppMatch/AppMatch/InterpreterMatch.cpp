#include "CBlockInterpreterRuntime.hpp"
#include <memory>
#include "CResultMatch.hpp"
#include <iostream>
#include "QueryStack.hpp"
#include "sharedCast.hpp"
using namespace std;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value,HRunLocalScope localsEntry, QueryStack stk)
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
		CResultMatch r = Match(*mit, *vit,localsEntry, stk);
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
 
CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value, HRunLocalScope localsEntry ,QueryStack stk)
{
	if (auto   mAtom = asHBlockMatchNoum(M))
	{
		if (auto inner =  asHBlockNoum(mAtom->inner))
			if (auto cinner =  asHBlockNoum(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				cout << cinner->named << " == " <<  inner->named << endl;
				if (inner->named == cinner->named)
				{
				  return 	CResultMatch(true );
				}

				auto rcc = query_is(cinner, inner, localsEntry, stk);
				return CResultMatch(rcc == QEquals);
				 
			}
	}

	if (auto  mAtom = asHBlockMatchNoum(M))
	{
		if (auto inner =  asHBlockNoum(mAtom->inner))
		{
			if (auto vNoumm =  asHBlockNoum(value))
			{
				if (vNoumm->named == inner->named)
				{
					return CResultMatch( true );
				}
			}
			if (auto cInst =  asHBlockInstance(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				//return CResultMatch(inner->named == cinner->named);

				auto r = query_is(cInst, inner, localsEntry, stk);
				return CResultMatch(r == QEquals);

			}

			auto rcc = query_is(value, inner, localsEntry, stk);
			return CResultMatch(rcc == QEquals);
		}

	}
	 
	if (auto   mVNamed = asHBlockMatchNamed(M))
	{
		CResultMatch mres = Match(mVNamed->matchInner , value, localsEntry,stk);
		if (mres.hasMatch)
		{
			return CResultMatch(mVNamed->named, value);
		}
		return mres;
	}

	if (HBlockMatchList   mList = asHBlockMatchList(M))
	{
		if (HBlockList   vList = asHBlockList(value))
		{
			return MatchList(mList, vList,localsEntry ,stk);
		}
		else
		{
			return CResultMatch(false);
		}
	}

	if (HBlockMatchAND   mAnnd = asHBlockMatchAND(M))
	{
		for(auto& mItem : mAnnd->matchList)
		{
			auto rAnnd =  Match(mItem, value, localsEntry, stk);
			if (rAnnd.hasMatch == false )
			{
				return CResultMatch(false);
			}
		}		
		return CResultMatch(true);
		
	}



	if (HBlockMatchProperty   mProp = asHBlockMatchProperty(M))
	{
		if (HBlockProperty    vProp = asHBlockProperty(value))
		{

			auto rProp = query_is( mProp->prop , vProp->prop, nullptr, stk);
			if (rProp == QEquals)
			{
				CResultMatch mres =  Match(mProp->obj, vProp->obj, localsEntry, stk);
				return mres;
			}
		}
		else
		{
			return CResultMatch(false);
		}
	}
	
	// Customized verb
	if (HBlockMatchIsVerb    mVerb = asHBlockMatchIsVerb(M))
	{
		if (HBlockIsVerb    vVerb = asHBlockIsVerb(value))
		{
			CResultMatch mres = Match(mVerb->obj, vVerb->n1, localsEntry, stk);
			if (mres.hasMatch)
			{
				CResultMatch mres_k = Match(mVerb->value, vVerb->n2 , localsEntry,stk);
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


	if (HBlockMatchDirectIs   mDirect = asHBlockMatchDirectIs(M))
	{
		if (HBlockAssertion_isDirectAssign   vDirect = asHBlockAssertion_isDirectAssign(value))
		{
			CResultMatch mres = Match(mDirect->obj, vDirect->get_obj(),localsEntry  , stk);
			if (mres.hasMatch)
			{
				CResultMatch mres_k = Match(mDirect->value, vDirect->value , localsEntry ,stk);
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


	if (auto    mNoum = asHBlockMatchAny(M))
		{
			return CResultMatch( true );
		}
		 
	 
	
	return CResultMatch(false);
}