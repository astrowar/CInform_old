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
using namespace QueryStacking;



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
			noums.push_back(make_shared<CBlockNoumStr>(ssi));
			prev = pos + 1;
		}

		// To get the last substring (or only, if delimiter is not found)
		string sss = str.substr(prev);
		noums.push_back(make_shared<CBlockNoumStr>(sss));

	 
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


CResultMatch  CBlockInterpreter::Match_DirectIs(HBlockMatch mObject_in, HBlockMatch mValue_in, HBlock object, HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
	 
	auto vr1 = resolve_if_noum(object, localsEntry, std::list<std::string>());
	if (vr1 == nullptr) vr1 = object;
	auto vr2 = resolve_if_noum(value, localsEntry, std::list<std::string>());
	if (vr2 == nullptr) vr2 = value;


	auto mObject = resolve_argument_match(mObject_in, localsEntry, stk);
	auto mValue = resolve_argument_match(mValue_in, localsEntry, stk);

	printf("==============================================\nMatched ? \n");
	
	vr1->dump("");
	mObject->dump("");

	printf("\n");
	vr2->dump("");
	mValue->dump("");
	printf("\n");




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
		 printf("Fail ==========================================\n");
			mValue->dump("");
			vr2->dump("");
			printf("............................................\n"); 
		}
	}
	else
	{
		printf("Fail ==========================================\n");
		mObject->dump("");
		vr1->dump(""); 
		printf("............................................\n"); 
	}

	return CResultMatch(false); 
}
 
std::vector<std::string> split_string_comb(const std::string& str, const std::string& delimiter)
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(str.substr(prev));

	return strings;
}

std::string joint_terms(const std::vector<std::string>&  x, int i1, int i2)
{
	std::string acc = "";
	for (int i = i1; i < i2; ++i)
	{
		if (i != i1) acc = acc + " ";
		acc = acc + x[i];
	}
	return acc;
}

CResultMatch  apply_string_combinatoria_4(const std::vector<std::string>&  x, std::function<CResultMatch(std::vector<std::string>)> f_combinatoria)
{
	int xn = x.size();
	for (int i1 = 0; i1 < xn - 3; ++i1)
		for (int i2 = i1 + 1; i2 < xn - 2; ++i2)
			for (int i3 = i2 + 1; i3 < xn-1; ++i3)
				for (int i4= i3 + 1; i4 < xn; ++i4)
			{
				std::vector<std::string> args = { joint_terms(x, i1, i2) , joint_terms(x, i2, i3) , joint_terms(x, i3, i4) , joint_terms(x, i4, xn) };
				CResultMatch r = f_combinatoria(args);
				if (r.hasMatch) return r;
			}
	return   CResultMatch(false);
}


CResultMatch  apply_string_combinatoria_3(const std::vector<std::string>&  x, std::function<CResultMatch(std::vector<std::string>)> f_combinatoria)
{
	int xn = x.size();
	for (int i1 = 0; i1 < xn - 2; ++i1)
		for (int i2 = i1 + 1; i2 < xn-1; ++i2)
			for (int i3 = i2 + 1; i3 < xn; ++i3)
		{
			std::vector<std::string> args = { joint_terms(x, i1, i2) , joint_terms(x, i2, i3) , joint_terms(x, i3, xn) };
			CResultMatch r = f_combinatoria(args);
			if (r.hasMatch) return r;
		}
	return   CResultMatch(false);
}


CResultMatch  apply_string_combinatoria_2(const std::vector<std::string>&  x,   std::function<CResultMatch(std::vector<std::string>)> f_combinatoria)
{
	int xn = x.size();
	for (int i1 = 0; i1 < xn - 1; ++i1)
		for (int i2 = i1+1; i2 < xn ; ++i2)
		{
			std::vector<std::string> args = { joint_terms(x, i1, i2) , joint_terms(x, i2, xn) };
			CResultMatch r =  f_combinatoria(args);
			if (r.hasMatch) return r;
		}
	return   CResultMatch(false);
}

CResultMatch  apply_string_combinatoria(string str, int n, std::function<CResultMatch(std::vector<std::string>)> f_combinatoria)
{
	if (n == 1) return f_combinatoria({ str });
	std::vector<std::string>  x = split_string_comb(str, " ");

	if (static_cast<int>(x.size()) < n) return   CResultMatch(false);
	if (static_cast<int>(x.size()) == n) return   f_combinatoria(x);
	 
	
	if (n == 2) return apply_string_combinatoria_2(x,f_combinatoria);
	if (n == 3) return apply_string_combinatoria_3(x, f_combinatoria);
	if (n == 4) return apply_string_combinatoria_4(x, f_combinatoria);
 
	return   CResultMatch(false);
}

CResultMatch  CBlockInterpreter::MatchListCombinaria(HBlockMatchList Ms, HBlockNoum n, HRunLocalScope localsEntry, QueryStack *stk)
{
	//de alguma forma n eh uma combinacao de termos que dao match em Ms
	if (Ms->matchList.size() == 0) return CResultMatch(false);
	if (Ms->matchList.size() == 1) return Match(Ms->matchList.front(), n, localsEntry, stk);

	std::vector<HBlockMatch > mvec = std::vector<HBlockMatch >(Ms->matchList.begin(), Ms->matchList.end());

	std::function<CResultMatch(std::vector<std::string> )> f_combinatoria = [&](std::vector<std::string> a)
	{ 
		//compara os noums primeiro

		printf("> ");
		for (size_t i = 0; i < mvec.size(); ++i)
		{
			printf("|%s", a[i].c_str());
		}
		printf("\n");

		for (size_t i = 0; i < mvec.size(); ++i)
		{
			if (HBlockMatchNoum vn = asHBlockMatchNoum(mvec[i]))
			{
				if (isSameString(a[i], vn->inner->named ) ==false ) return CResultMatch(false);
			}
		}

		auto locals_value = localsEntry;
		std::map<string, CBlocking::HBlock> accum_vars;

		CResultMatch acc_result  =   CResultMatch(true);
		for (size_t i = 0; i < mvec.size(); ++i)
		{
			if ( asHBlockMatchNoum(mvec[i]) ==nullptr)			 
			{
				auto mres = Match(mvec[i], std::make_shared<CBlockNoumStr>(a[i]), locals_value, stk);
				if (mres.hasMatch == false)
				{
					return CResultMatch(false);
				}
//				for (auto x : mres.maptch) accum_vars[x.first] = x.second;
				acc_result.append(mres);
				locals_value = std::make_shared< CRunLocalScope >(locals_value, mres.maptch); // ajusta para o proximo 
			}
		}
		return acc_result;
	};

	return apply_string_combinatoria(n->named, Ms->matchList.size(), f_combinatoria);


	return CResultMatch(false);
}


bool CBlockInterpreter::is_kind_match(HBlockMatch M )
{
	if (auto   mVNamed = asHBlockMatchNamed(M))
	{
		return  is_kind_match(mVNamed->matchInner);
	}
	if (auto   mn = asHBlockMatchNoum(M))
	{
		const auto knamed = this->resolve_kind(mn->inner->named);
		if (knamed != nullptr) return true;
	}
	return false;
}


CResultMatch CBlockInterpreter::adjetive_match( std::list<HBlockMatch>  mlist , HBlockInstance value, HRunLocalScope localsEntry, QueryStack *stk)
{
	std::list<HBlockMatch>  nlist;
	
	bool has_all_match = true;
	
	std::list<HBlockMatch > mnoumlist;
	string acc = "";

	// agrupa os noum 
	while(mlist.empty() ==false )
	{		 
		HBlockMatch item = mlist.front();
		mlist.pop_front(); 

		const HBlockMatchNoum cnoum = asHBlockMatchNoum(item);
		if (cnoum != nullptr)
		{
			QueryResultContext rr = query_is( cnoum->inner, value, localsEntry, stk);
			if (rr.result != QEquals)
			{
				has_all_match = false;
				break;
			}
		}
		 
	}





	for (auto mi : mlist)
		{
			HBlockMatchNoum cnoum = asHBlockMatchNoum(mi);
			if (cnoum ==nullptr)
			{
				QueryResultContext rr = query_is(value, value, localsEntry, stk);
				if (rr.result != QEquals)
				{
					has_all_match = false;
					break;
				}
			}
			else if (HBlockMatchList cnoumList = asHBlockMatchList(mi))
			{
				CResultMatch cr = CBlockInterpreter::adjetive_match(cnoumList->matchList, value, localsEntry, stk);
				if (cr.hasMatch ==false )
				{
					has_all_match = false;
					break;
				}
			}
		}

	//cheguei aqui e agora ???
	if (has_all_match) return CResultMatch(true);

     
}

HBlockMatchNoum concatenate_MatchNoum(HBlockMatchNoum a, HBlockMatchNoum b)
{
  return 	make_shared<CBlockMatchNoum>(make_shared<CBlockNoumStr>(a->inner->named + " "+b->inner->named));
}


  std::list<HBlockMatch> concatenate_MatchNoum(std::list<HBlockMatch> mList)
{
	//if (mList.size() < 2) return mList;

    for(auto it = mList.begin() ; it!= mList.end() ;++it )
    {
	    if (HBlockMatchNoum anoum = asHBlockMatchNoum(*it))
	    {
			auto x = std::next(it);
			if (x != mList.end() )
			{
				if (HBlockMatchNoum bnoum = asHBlockMatchNoum(*x))  //tem dois noum em sequencia  !
				{
					*it = concatenate_MatchNoum(anoum, bnoum);
					mList.erase(x);		
					it = mList.begin();
				}
			}
	    } 
		if (HBlockMatchList aList= asHBlockMatchList(*it))
		{
			auto nList = concatenate_MatchNoum(aList->matchList);				
			*it = make_shared<CBlockMatchList>(nList);
		}
    }

	return mList;
}

//tenta descobrir os advetivos utilizados
CResultMatch  CBlockInterpreter::Match_list_adjetivos_instance(HBlockMatchList mList, HBlockInstance value, HRunLocalScope localsEntry, QueryStack *stk)
{
	//adjetive Ordem
	std::list<HBlockMatch> lst = mList->matchList;
	auto ret =  CResultMatch(true);

	auto m = lst.back();
	lst.pop_back();

	if ( is_kind_match(m))
	{
		CResultMatch r = Match(m, value, localsEntry, stk);
		if (r.hasMatch == false) return CResultMatch(false);
		ret.append(r);
	}

	auto mfront = concatenate_MatchNoum(lst);
	for(auto it = mfront.begin();it!= mfront.end();++it)
	{
		CResultMatch r = Match(*it, value, localsEntry, stk);
		if (r.hasMatch == false) return CResultMatch(false);
		ret.append(r);
	}

	 
	return ret;
}

CResultMatch  CBlockInterpreter::Match_list_adjetivos(HBlockMatchList mList, HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
 
	if (mList->matchList.size() == 1)
	{
		return Match(mList->matchList.front(), value, localsEntry, stk);
	}

		bool is_compound_noum = true;
		for (auto m : mList->matchList) { if (m->type() != BlockMatchNoum)is_compound_noum = false; }
		if (is_compound_noum)
		{
			string nnoum = "";
			for (auto m : mList->matchList)
			{
				HBlockMatchNoum cnoum = asHBlockMatchNoum(m);
				if (is_article(cnoum->inner->named)) continue;
				if (nnoum.empty())
				{
					nnoum = cnoum->inner->named;
				}
				else
				{
					nnoum = nnoum + " " + cnoum->inner->named;
				}
			}

			if (HBlockNoum   noumCompound = asHBlockNoum(value))
			{
				if (isSameString(nnoum, noumCompound->named))
				{
					return CResultMatch(true);
				}
			}

			auto resolved = resolve_string_noum(nnoum, localsEntry, std::list<std::string>());
			if (resolved)
			{
				QueryResultContext rr = query_is(value, resolved, localsEntry, stk);
				if (rr.result == QEquals)
				{
					return CResultMatch(true);
				}
			}
		}
		else
		{
			if (HBlockNoum   noumCompound = asHBlockNoum(value))
			{
				return MatchListCombinaria(mList, noumCompound, localsEntry, stk);
			}
			if (HBlockInstance   nInst = asHBlockInstance(value))
			{
				return Match_list_adjetivos_instance(mList, nInst, localsEntry, stk);
			}
		}
		return CResultMatch(false);
	}




CResultMatch  CBlockInterpreter::Match(HBlockMatch M, HBlock value, HRunLocalScope localsEntry ,QueryStack *stk)
{
 
	//printf("Is Match ?\n");
	//value->dump("   ");
	//M->dump("   ");	
	//printf("\n\n");

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

				//Elimino esta linha pois aqui nada deve entrar sem estar resolvido


				//QueryResultContext rcc = query_is(cinner, inner, localsEntry, stk);
				 
				//return CResultMatch(rcc.result == QEquals);
				return 	CResultMatch(false);
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
			if (auto cnInstance = asHBlockInstanceNamed(value))
			{
				if (cnInstance->named == inner_2->named) return CResultMatch(true);
				//	QueryResultContext r = query_is(cAction, inner_2, localsEntry, stk);
				//	return CResultMatch(r.result == QEquals); 
			}

			if (auto cInst =  asHBlockInstance(value))
			{
				//Substitua essa igualdade Statica por uma Dynamica
				//return CResultMatch(inner->named == cinner->named);


				// Never Recall Query again over a Noum
				bool actual_value = false;
				
				if (cInst->is_set(inner_2, actual_value))
				{
                  return CResultMatch(actual_value);					 
				} 
				return 	CResultMatch(false);

				QueryResultContext r = query_is(cInst, inner_2, localsEntry, stk);
				return CResultMatch(r.result == QEquals); 
			}
			 

			if (auto cAction = asHBlockActionNamed (value))
			{ 
				if (cAction->named == inner_2->named) return CResultMatch( true );				 
			//	QueryResultContext r = query_is(cAction, inner_2, localsEntry, stk);
			//	return CResultMatch(r.result == QEquals); 
			}

			return CResultMatch(false);
			//Never call query again over a Noum
			QueryResultContext rcc = query_is(value, inner_2, localsEntry, stk);
			return CResultMatch(rcc.result == QEquals);
		}
		return CResultMatch(false);
	}
	 
	if (auto   mVNamed = asHBlockMatchNamed(M))
	{
		auto m_inner = resolve_argument_match(mVNamed->matchInner, localsEntry, stk);

		
		//if (HBlockMatchKind   mkind = asHBlockMatchKind (m_inner))
		//{
		//	if (asHBlockKind(value) !=nullptr)
		//	{
		//		return CResultMatch(false);
		//	} 
		//}

		CResultMatch mres = Match(m_inner, value, localsEntry,stk);
		if (mres.hasMatch)
		{			 
			return CResultMatch(mVNamed->named, value);
		}
		return mres;
	}

	//Noum composto que forma um noum conecido no sistema
	
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
		return Match_list_adjetivos(mList, value, localsEntry, stk);

		//return CResultMatch(false);
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
			if (HBlockMatch    mmmProp = asHBlockMatch(mProp->prop))
			{
				CResultMatch mres = Match(mmmProp, vProp->prop, localsEntry, stk);
				if (mres.hasMatch)
				{
					auto locals_value = std::make_shared< CRunLocalScope >(localsEntry, mres.maptch);
					CResultMatch mres_obj = Match(mProp->obj, vProp->obj, locals_value, stk);					
					mres_obj.append(mres); 
					return mres_obj;
				}
			}
			else
			{
				QueryResultContext rProp = query_is(mProp->prop, vProp->prop, nullptr, stk);
				if (rProp.result == QEquals)
				{
					CResultMatch mres = Match(mProp->obj, vProp->obj, localsEntry, stk);
					return mres;
				}
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
		return CResultMatch(false);
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
		return CResultMatch(false);
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
		return CResultMatch(false);
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
		return CResultMatch(false);
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
		return CResultMatch(false);
	}

	if (HBlockMatchKind  mKind = asHBlockMatchKind(M))
	{
		if (asHBlockNoum(value) != nullptr) return CResultMatch(false);
		
			QueryResultContext qkind = query_is(value, mKind->kind, localsEntry, stk);
			return CResultMatch(qkind.result == QEquals);
		
	}

	if (HBlockMatchValue  mVal = asHBlockMatchValue(M))
	{
		if (asHBlockNoum(value) != nullptr) return CResultMatch(false);
		
			QueryResultContext qkind = query_is(value, mVal->inner, localsEntry, stk);
			return CResultMatch(qkind.result == QEquals);
		
	}



	logError("Match not handled ");
	return CResultMatch(false);
}