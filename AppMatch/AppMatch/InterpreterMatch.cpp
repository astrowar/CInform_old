// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <memory>
#include "CResultMatch.hpp"
 
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;


using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;


//Match engine

CResultMatch  CBlockInterpreter::MatchList(HBlockMatchList M, HBlockList value,HRunLocalScope localsEntry, QueryStack *stk)
{
	if (M->matchList.size() != value->lista.size())
	{
		 
		//(M)->dump("    ");
		//(value)->dump("    ");
		return   CResultMatch(false); //sizes must be equals
	}
	auto mit = M->matchList.begin();
	auto vit = value->lista.begin();
	 
	auto localsEntryNext = std::make_shared< CRunLocalScope >(localsEntry);
	 

	CResultMatch rAccm = CResultMatch(true);
	while (true)
	{
		if (mit == M->matchList.end()) break;

		//cada item da lista, usa os matchs que ja estao resolvidos ate o momento
		localsEntryNext = std::make_shared< CRunLocalScope >(localsEntryNext,  rAccm.maptch); 

		CResultMatch r = Match(*mit, *vit, localsEntryNext, stk);
		if (r.hasMatch == false)
		{ 	 
			//(*vit)->dump("    ");
			//(*mit)->dump("    ");
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

	 

	auto q = make_shared<CBlockList>(noums);
	 
	return q;
 
}

bool is_article(std::string s)
{
	if (s == "a" || s == "an" || s == "the" || s == "some") return true;
	return false;
}


std::list<HBlockMatch> remove_article(std::list<HBlockMatch> lst)
{
	 
	if (lst.empty()) return lst;
	std::list<HBlockMatch>::iterator init_ptr = lst.begin();
	while (init_ptr != lst.end())
	{
		if (auto mnoum = asHBlockMatchNoum(*init_ptr))
		{
			if (is_article(mnoum->inner->named))
			{
				++init_ptr;
				if (init_ptr == lst.end()) break;
			}
			else
			{
				break;
			}
		}
	}
	return 	std::list<HBlockMatch>(init_ptr, lst.end());
}


CResultMatch  CBlockInterpreter::isEquivalenteMatch(HBlockMatch M, HBlockMatch mValue, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	if (auto mnoum = asHBlockMatchNoum(mValue))
	{
		return  Match(M, mnoum->inner, localsEntry, stk);
	}

	if (auto mlist = asHBlockMatchList(mValue))
	{		
		if (auto mbaseList = asHBlockMatchList(M))
		{

			auto it_list1 = remove_article(mlist->matchList);
			auto it_list2 = remove_article(mbaseList->matchList);
			// Confere cada item do match com os item do M
			if (it_list1.size() != it_list2.size())
			{				  
				return CResultMatch(false); // tamanhos diferentes
			}
			auto it1 = it_list1.begin();
			auto it2 = it_list2.begin();

			CResultMatch mAcc = CResultMatch(true); // Matchs acumulados ate o momento
			HRunLocalScope localsNext = localsEntry;

			for(;it1 != it_list1.end();++it1,++it2)
			{
				CResultMatch rit = isEquivalenteMatch(*it2, *it1, localsNext, stk); 
				if (rit.hasMatch == false)
				{
					return CResultMatch(false);
				}

				mAcc.append(rit ); // Adiciona os matchs nomeados ate o momento
				localsNext = std::make_shared< CRunLocalScope >(localsNext, mAcc.maptch);
				  
			}
			 
			return mAcc;


		}
		else
		{
			// uma lista contra uma nao lista ? o que pode ser
			logError("Something unespected");		

			printf("==============================\n");
			mlist->dump("");
			M->dump("");

			return CResultMatch(false);

		}
	}

	return CResultMatch(false);
}


CResultMatch  CBlockInterpreter::Match_DirectIs(HBlockMatch mObject, HBlockMatch mValue, HBlock object, HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
	 
	auto vr1 = resolve_if_noum(object, localsEntry, std::list<std::string>());
	if (vr1 == nullptr) vr1 = object;
	auto vr2 = resolve_if_noum(value, localsEntry, std::list<std::string>());
	if (vr2 == nullptr) vr2 = value;


	CResultMatch mres = Match(mObject, vr1, localsEntry, stk);
	if (mres.hasMatch)
	{
		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, mres.maptch);
	 

		 
		CResultMatch mres_k = Match(mValue, vr2, localsNext, stk);
		if (mres_k.hasMatch)
		{ 
			//auto locals_value = std::make_shared< CRunLocalScope >(mres_k.maptch);
			//auto localsNext2 = newScope(localsNext, locals_value);
			mres.append(mres_k);		 

			auto locals_value = std::make_shared< CRunLocalScope >(localsNext , mres.maptch);
		 
			return mres; 

		}
		else
		{
		/*	printf("Fail ==========================================\n");
			mValue->dump("");
			vr2->dump("");
			printf("............................................\n");*/
		}
	}
	else
	{
		//printf("Fail ==========================================\n");
		//mObject->dump("");
		//vr1->dump(""); 
		//printf("............................................\n"); 
	}

	return CResultMatch(false); 
}
 



CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value, HRunLocalScope localsEntry ,QueryStack *stk)
{
	if (auto vMatch = asHBlockMatch(value))
	{
		// Hummm ... um match contra outro match ...
		CResultMatch mres = isEquivalenteMatch(M, vMatch, localsEntry, stk);
		if (mres.hasMatch)		return 	mres;
		return CResultMatch(false );
		
	}
	 
	// Pois pode ser que um deles seja uma lista de noum e o parser interpretou como um Match List

	if (auto   mAtom = asHBlockMatchNoum(M))
	{
		if (auto inner =  asHBlockNoum(mAtom->inner))
			if (auto cinner =  asHBlockNoum(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				 
				if (isSameString( inner->named , cinner->named))
				{
				  return 	CResultMatch(true );
				}

				QueryResultContext rcc = query_is(cinner, inner, localsEntry, stk);
				 
				return CResultMatch(rcc.result == QEquals);
				 
			}
 
	 
		if (auto inner_2 =  asHBlockNoum(mAtom->inner))
		{
			if (auto vNoumm =  asHBlockNoum(value))
			{
				if (vNoumm->named == inner_2->named)
				{
					return CResultMatch( true );
				}
			}
			if (auto cInst =  asHBlockInstance(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				//return CResultMatch(inner->named == cinner->named);

				QueryResultContext r = query_is(cInst, inner_2, localsEntry, stk);
				return CResultMatch(r.result == QEquals);

			}


			if (auto cAction = asHBlockAction (value))
			{ 
				if (cAction->named == inner_2->named) return CResultMatch( true );
				QueryResultContext r = query_is(cAction, inner_2, localsEntry, stk);
				return CResultMatch(r.result == QEquals); 
			}

			QueryResultContext rcc = query_is(value, inner_2, localsEntry, stk);
			return CResultMatch(rcc.result == QEquals);
		}

	}
	 
	if (auto   mVNamed = asHBlockMatchNamed(M))
	{
		CResultMatch mres = Match(mVNamed->matchInner , value, localsEntry,stk);
		if (mres.hasMatch)
		{
			if (mVNamed->named =="P2")
			{
				return CResultMatch(mVNamed->named, value);
			}
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
			string nnoum = "";
			for (auto m : mList->matchList)
			{
				HBlockMatchNoum cnoum = asHBlockMatchNoum(m);
				if (is_article(cnoum->inner->named)) continue;
				if (nnoum == "")
				    {
						nnoum = cnoum->inner->named; }
				else 
				    {
						nnoum = nnoum + " " + cnoum->inner->named;
				}
			}

			if (HBlockNoum   noumCompound = asHBlockNoum(value))
			{
				if ( isSameString(nnoum , noumCompound->named))
				{
					 return CResultMatch(true);
				}
			}

			auto resolved = resolve_string_noum(   nnoum ,localsEntry ,std::list<std::string>());
			if (resolved)
			{
				QueryResultContext rr = query_is(value, resolved , localsEntry, stk);
				if (rr.result == QEquals)
				{
					return CResultMatch(true);
				}
			}
			 

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
			 
			auto rList =  MatchList(mList, vNoumList, localsEntry, stk);
			return rList;
		}
		return CResultMatch(false);
	}

	 


	if (HBlockMatchAND   mAnnd = asHBlockMatchAND(M))
	{
		auto mAcc = CResultMatch(true);
		for(auto& mItem : mAnnd->matchList)
		{
			auto rAnnd =  Match(mItem, value, localsEntry, stk);
			if (rAnnd.hasMatch == false )
			{
				return CResultMatch(false);
			}
			mAcc.append(rAnnd);
		}		
		return mAcc;
		
	}



	if (HBlockMatchProperty   mProp = asHBlockMatchProperty(M))
	{
		if (HBlockProperty    vProp = asHBlockProperty(value))
		{
			QueryResultContext rProp = query_is( mProp->prop , vProp->prop, nullptr, stk);
			if (rProp.result == QEquals)
			{
				CResultMatch mres =  Match(mProp->obj, vProp->obj, localsEntry, stk);
				return mres;
			}
		}
		else
		{
			// value pode ser o resultado da computacao da propriedade ....
			HBlockList  objList = lookup_value_by_Selector(mProp->obj , localsEntry,stk); // obtem todos os objetos que casam com a descricao
			for(auto &o : objList->lista )
			{
				HBlockProperty propToProbe =  make_shared<CBlockProperty>(mProp->prop, o);

		 
				auto prop_value =  query_is_propertyOf_value(propToProbe, value, localsEntry, stk);
				if (prop_value.result == QEquals)
				{
					return CResultMatch(true);
				}
			}
			
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

			auto vr1 = resolve_if_noum(vDirect->get_obj(), localsEntry, std::list<std::string>());
			if (vr1 == nullptr) vr1 = vDirect->get_obj();
			auto vr2 = resolve_if_noum(vDirect->value, localsEntry, std::list<std::string>());
			if (vr2 == nullptr) vr2 = vDirect->value;


			CResultMatch mres = Match(mDirect->obj, vr1,localsEntry  , stk);
			if (mres.hasMatch)
			{
				auto localsNext = std::make_shared< CRunLocalScope >(localsEntry , mres.maptch);
				 

				CResultMatch mres_k = Match(mDirect->value, vr2 , localsEntry ,stk);
				if (mres_k.hasMatch)
				{
					//auto locals_value = std::make_shared< CRunLocalScope >(localsNext , mres_k.maptch); 
					mres.append(mres_k);
					return mres;

				}
			}	
			else
			{
				//printf("Match Fail =============================\n");

				//mDirect->obj->dump("  ");
				//vDirect->get_obj()->dump("  ");
				//if (localsEntry != nullptr)
				//{
				//	printf("LETs   \n");
				//	localsEntry->dump("");
				//}
				//printf(".........................................\n");

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

					QueryResultContext qverb = query_is(value, mWhich->value, localsEntry, stk);
					if (qverb.result == QEquals)
					{
						return mres;
					}		
					return CResultMatch(false);
				}
				else
				{
					HBlockIsVerb vv = make_shared<CBlockIsVerb>(mWhich->verb, value, mWhich->value);
					QueryResultContext qverb = query_verb(vv, localsEntry, stk);
					if (qverb.result == QEquals)
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
					QueryResultContext qverb = query_is(value, mWhichNot->value, localsEntry, stk);
					if (qverb.result != QEquals)
					{
						return mres;
					}
					 
				}
				else
				{
					HBlockIsVerb vv = make_shared<CBlockIsVerb>(mWhichNot->verb, value, mWhichNot->value);
					QueryResultContext qverb = query_verb(vv, localsEntry, stk);
					if (qverb.result != QEquals)
					{
						return mres;
					}
				}
			} 
		} 
	}
	
	return CResultMatch(false);
}