#include "CBlockInterpreterRuntime.hpp"
#include <memory>
#include "CResultMatch.hpp"
 
#include "QueryStack.hpp"
#include "sharedCast.hpp"
using namespace std;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value,HRunLocalScope localsEntry, QueryStack stk)
{
	if (M->matchList.size() != value->lista.size())
	{
		logMessage("FAIL  size  ");
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
			logMessage("FAIL  item   ");
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


HBlockList getCompoundNoumAsList(HBlockNoum noum)
{
	std::list<HBlock> noums;
	auto str = noum->named;
	const std::string delimiter = " ";
	//std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
	{
		 

		std::string::size_type pos = 0;
		std::string::size_type prev = 0;
		while ((pos = str.find(delimiter, prev)) != std::string::npos)
		{
			string ssi = str.substr(prev, pos - prev);
			noums.push_back(make_shared<CBlockNoum>(ssi));
			prev = pos + 1;
		}

		// To get the last substring (or only, if delimiter is not found)
		string sss = str.substr(prev);
		noums.push_back(make_shared<CBlockNoum>(sss));

	 
	}

	return  make_shared<CBlockList>(noums);
 
}

bool is_article(std::string s)
{
	if (s == "a" || s == "an" || s == "the" || s == "some") return true;
	return false;
}
CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value, HRunLocalScope localsEntry ,QueryStack stk)
{
	if (auto   mAtom = asHBlockMatchNoum(M))
	{
		if (auto inner =  asHBlockNoum(mAtom->inner))
			if (auto cinner =  asHBlockNoum(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				logMessage(cinner->named + " == "+inner->named);
				if (inner->named == cinner->named)
				{
				  return 	CResultMatch(true );
				}

				auto rcc = query_is(cinner, inner, localsEntry, stk);
				return CResultMatch(rcc == QEquals);
				 
			}
 
	 
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

	//Noum composto que forma um noum conecido no sistema
	if (HBlockMatchList   mList = asHBlockMatchList(M))
	{
		bool is_compound_noum = true ;
		for (auto m : mList->matchList) {if (m->type() != BlockMatchNoum)is_compound_noum = false;}
		if (is_compound_noum)
		{			
			HBlockNoum noum  = make_shared<CBlockNoum>("");
			for (auto m : mList->matchList)
			{
				HBlockMatchNoum cnoum = asHBlockMatchNoum(m);
				if (is_article(cnoum->inner->named)) continue;
				if (noum->named == "") 
				    { noum->named = cnoum->inner->named; }
				else 
				    { noum->named = noum->named + " " + cnoum->inner->named; }
			}

			auto rr = query_is(value, noum, localsEntry, stk);
			if (rr == QEquals)   return CResultMatch( true );
		}
	}

	if (HBlockMatchList   mList = asHBlockMatchList(M))
	{
		if (HBlockList   vList = asHBlockList(value))
		{
			return MatchList(mList, vList,localsEntry ,stk);
		}
		if (HBlockNoum   noumCompound = asHBlockNoum(value))
		{
			HBlockList   vNoumList = getCompoundNoumAsList(noumCompound);
			return MatchList(mList, vNoumList, localsEntry, stk);
		}
		return CResultMatch(false);
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
		{
			if (HBlockIsVerb    vVerb = asHBlockIsVerb(value))
			{
				CResultMatch mres = Match(mVerb->obj, vVerb->n1, localsEntry, stk);
				if (mres.hasMatch)
				{
					CResultMatch mres_k = Match(mVerb->value, vVerb->n2, localsEntry, stk);
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
		 
	 

	if (HBlockMatchWhich   mWhich = asHBlockMatchWhich(M))
	{
		{
			CResultMatch mres = Match(mWhich->obj, value, localsEntry, stk);
			if (mres.hasMatch)
			{
				if (mWhich->verb == "is")
				{
					//auto vv = make_shared<CBlockAssertion_isDirectAssign>( value, mWhich->value);
					auto qverb = query_is(value, mWhich->value, localsEntry, stk);
					if (qverb == QEquals)
					{
						return mres;
					}
				}
				else
				{
					HBlockIsVerb vv = make_shared<CBlockIsVerb>(mWhich->verb, value, mWhich->value);
					auto qverb = query_verb(vv, localsEntry, stk);
					if (qverb == QEquals)
					{
						return mres;
					}
				}
			} 
		} 
	}

	if (HBlockMatchWhichNot   mWhichNot = asHBlockMatchWhichNot(M))
	{
		{
			CResultMatch mres = Match(mWhichNot->obj, value, localsEntry, stk);
			if (mres.hasMatch)
			{
				if (mWhichNot->verb == "is")
				{
					auto qverb = query_is(value, mWhichNot->value, localsEntry, stk);
					if (qverb != QEquals)
					{
						return mres;
					}
				}
				else
				{
					HBlockIsVerb vv = make_shared<CBlockIsVerb>(mWhichNot->verb, value, mWhichNot->value);
					auto qverb = query_verb(vv, localsEntry, stk);
					if (qverb != QEquals)
					{
						return mres;
					}
				}
			} 
		} 
	}
	
	return CResultMatch(false);
}