// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QueryStack.hpp"
#include "CResultMatch.hpp"
#include "sharedCast.hpp"
#include <algorithm>
#include "CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;



std::vector<std::string> split_string_noum(const std::string& str, const std::string& delimiter)
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


std::vector<string> isHBlockMatchNoumList(const std::vector<HBlockMatch>  &mlist)
{
	std::vector<string> ret;
   //retorna empty se nao for uma lista de noums
	for (auto it = mlist.begin(); it != mlist.end(); ++it)
	{
		if (HBlockMatchNoum  nn = DynamicCasting::asHBlockMatchNoum(*it))
		{
			ret.push_back(nn->inner->named);
		}
		else
		{
			return{};
		}
	}

	return ret;
}


string CBlockInterpreter::getStringPrexfedFromList(const std::vector<string>& noumFragmented , std::list<string> allStringNames )
{
	size_t lst_size_t = noumFragmented.size();
	for (auto &ss : allStringNames)
	{
		std::vector<string> kindNameFramented = split_string_noum(ss, " ");
		size_t n_k_size_t = kindNameFramented.size();
		if (lst_size_t != n_k_size_t) continue;

		bool isEquals_b = true;
		for (size_t i = 0; i<lst_size_t; ++i)
		{
			if (isSameString(kindNameFramented[i], noumFragmented[i]) == false)
			{
				isEquals_b = false;
			}
			break;
		}
		if (isEquals_b) return ss;

	}
	return "";
}


 

std::list<HBlock> CBlockInterpreter::getInstancesFromKind(HBlockKind kind, HRunLocalScope localsEntry)
{
	std::list<HBlock> ret;
	//percorre todos os Kinds
	
	if (kind.get() == this->MetaKind.get() )
	{
		for (auto &defs : assertions)
		{
			if (HBlockKind nn = DynamicCasting::asHBlockKind(defs->get_definition())) {
				ret.push_back( nn );
			}
		}
		return ret;
	}

	
	{
		if (kind.get() == this->MetaKindRelation.get())
		{
			for (auto &sRelation : this->staticRelation)
			{
				ret.push_back(sRelation.second);
			}
			return ret;
		}
	}

	for (auto &nInst : instancias)
	{
		if (CBlock::isSame(nInst->baseKind.get() , kind.get() ))
		{
			ret.push_back(nInst);
			continue;
		}

      if (is_derivadeOf(nInst->baseKind, kind))
			{
				ret.push_back(nInst);
			} 
	}

	return ret;
}


std::list<HBlock> CBlockInterpreter::getInstancesFromSelector(HBlockMatch seletor, HRunLocalScope localsEntry)
{
	//Nunca chame Resolve_Selector daqui
	 

	if (HBlockMatchNoum mNoum = DynamicCasting::asHBlockMatchNoum(seletor))
	{
		for (auto &nInst : instancias)
		{
			auto qret = query_is(nInst, mNoum->inner, localsEntry,nullptr);
			if (qret.result == QEquals)
			{
				return{ nInst };
			}
		}
	}

	if (HBlockMatchKind mKind = DynamicCasting::asHBlockMatchKind(seletor))
	{
		return getInstancesFromKind(mKind->kind, localsEntry);
	}

	if (HBlockMatchAND mmAnd = DynamicCasting::asHBlockMatchAND(seletor))
	{ 
			std::list<HBlock> instancias = {};
			for( auto &m : mmAnd->matchList)
			{
				 if (HBlockMatchKind mKindP = DynamicCasting::asHBlockMatchKind(m))
				 {
					  instancias =  getInstancesFromKind(mKindP->kind, localsEntry);
				 }
			}
			if (instancias.empty()) return{};
			std::list<HBlock> nextInstancias = {};
			for (auto &mInst : instancias)
			{
				bool isValid = true;
				for (auto &m : mmAnd->matchList)
				{
					if (DynamicCasting::asHBlockMatchKind(m) == nullptr) //agora os que nao sao Kind
					{
						 

						auto qret = query_is(mInst, m, localsEntry, nullptr);
						if (qret.result != QEquals)
						{
							isValid = false;
							break;
						}
					}
				}
				if (isValid) nextInstancias.push_back(mInst);
			}
			return nextInstancias; 
	}



	return {};
}


CBlocking::HBlockMatch CBlockInterpreter::Resolve_Selector_item(HBlockMatch seletor, std::list<string> &allKindsNames , std::list<string> &allEnumNames ,HRunLocalScope localsEntry)
{
	if (HBlockMatchNoum mNoum = DynamicCasting::asHBlockMatchNoum(seletor))
	{
		for (auto &ss : allKindsNames)
		{
			if (isSameString(ss, mNoum->inner->named))
			{
				return make_shared<CBlockMatchKind>(make_shared<CBlockKindThing>(ss));
			}
		}
	}

	if (HBlockMatchList mList = DynamicCasting::asHBlockMatchList(seletor))
	{
		return Resolve_Selector_List(mList, allKindsNames, allEnumNames , localsEntry);
	}

	return seletor; // i dont know
}

CBlocking::HBlockMatch noum_joined(std::vector<string> strList_in)
{
	printf("Match unfound \n");
	string sret = "";
	bool fir = true;
	for (auto s : strList_in)
	{
		printf("%s ", s.c_str());
		if (fir == false) 
		{
			sret = sret + " " + s;
		}
		else 
		{
			sret = sret + s;
		}
		fir = false;
	}
	printf("\n");
	return make_shared<CBlockMatchNoum>(make_shared<CBlockNoum>(sret));;
}


CBlocking::HBlockMatch  CBlockInterpreter::Resolve_Selector_Noum_fragment(std::vector<string> strList_in, std::list<string> &allKindsNames, std::list<string> &allEnumNames, HRunLocalScope localsEntry)
{
	if (allKindsNames.empty())
	{
		 allKindsNames = this->getAllRegistedKinds();
		 allEnumNames = this->getAllRegistedEnums();
	}

	string kindFound = getStringPrexfedFromList(strList_in, allKindsNames);
	if (!(kindFound.empty()))
	{
		return make_shared<CBlockMatchKind>(make_shared<CBlockKindThing>(kindFound));
	}

	string ennFound = getStringPrexfedFromList(strList_in, allEnumNames);
	if (!(ennFound.empty()))
	{
		return make_shared<CBlockMatchNoum>(make_shared<CBlockNoum>(ennFound));
	}
	return nullptr;
}

CBlocking::HBlockMatch CBlockInterpreter::Resolve_Selector_NoumList(std::vector<string> strList_in, std::list<string> &allKindsNames, std::list<string> &allEnumNames, HRunLocalScope localsEntry)
{

	int pivot_a = 0;
	

	std::list<HBlockMatch> resolve_list;
	while (pivot_a < strList_in.size())
	{
		if (HBlockMatch resolved = Resolve_Selector_Noum_fragment(std::vector<string>(strList_in.begin() + pivot_a, strList_in.end()), allKindsNames, allEnumNames, localsEntry))
		{
			resolve_list.push_front(resolved);
			strList_in = std::vector<string>(strList_in.begin(), strList_in.begin() + pivot_a);
			pivot_a = 0;
			if (strList_in.size() == 0) break;
			continue; //volta ao inicio sem incremento
		}

		pivot_a++;

		if (pivot_a == strList_in.size())
		{
			if (strList_in.size() > 0)
			{
				resolve_list.push_front(noum_joined(strList_in));
			}
			break;
		}
	}
	if (resolve_list.size() == 1) return resolve_list.front();
	return make_shared<CBlockMatchAND>(resolve_list);

	 
}

CBlocking::HBlockMatch CBlockInterpreter::Resolve_Selector_List(HBlockMatchList mList, std::list<string> &allKindsNames  , std::list<string> &allEnumNames  , HRunLocalScope localsEntry)
{

	if (mList->matchList.size() == 1) return Resolve_Selector_item(mList->matchList.front(), allKindsNames , allEnumNames, localsEntry);


	// Aqui temos um problema ... mList pode ser A,B,C ond e A  eh um modificador  e B C formam uma palavra valida

	std::vector<string> strList;
	std::list< HBlockMatch > resolveds;
	// faz a selecao das partes que nao sao List
	auto pivot = mList->matchList.begin(); 

	while(pivot != mList->matchList.end())
	{
		if (HBlockMatchNoum mNoum = DynamicCasting::asHBlockMatchNoum(*pivot))
		{
			strList.push_back(mNoum->inner->named);
		}
		else		
		{
			// processa a lista acumulada ate o momento
			if (strList.size() != 0)
			{
				HBlockMatch resolved = Resolve_Selector_NoumList(strList, allKindsNames, allEnumNames, localsEntry);	
				if (HBlockMatchList resolvedmList = DynamicCasting::asHBlockMatchList(resolved))
				{
					for(auto r : resolvedmList->matchList) resolveds.push_back(r);
				}
				else
				{
					resolveds.push_back(resolved);
				}
				strList.clear();
			}
			{
				HBlockMatch resolved = Resolve_Selector_item(*pivot, allKindsNames, allEnumNames, localsEntry);
				resolveds.push_back(resolved);
			}
		}		


		pivot++;
		if (pivot == mList->matchList.end())
		{
			if (strList.size() != 0)
			{
				HBlockMatch resolved = Resolve_Selector_NoumList(strList, allKindsNames, allEnumNames, localsEntry);
				resolveds.push_back(resolved);
				strList.clear();
			}
			break;
		}
	}
	
	if (resolveds.size() == 1) return resolveds.front();

	return  make_shared<CBlockMatchAND>(resolveds);

	  

}

 

CBlocking::HBlockMatch CBlockInterpreter::Resolve_Selector(HBlockMatch seletor, HRunLocalScope localsEntry)
{
	 
	//resolve seletor ... IE 
	// List( Noum(black) , Noum(Thing) ) -> And(Attribute(black) ,  Kind(Thing)  )

	// best friend is a Person that varies
	// List( Noum(best) , Noum(friend) )  -> Noum( best friend ) 


	// List( Noum(closed) , Noum(magical) ,Noum(item) ) -> And(Attribute(closed) ,  Attribute(magical) ,Kind(item)  )

	// List( Noum(lit) , Noum(eletric) ,Noum(device) ) -> And(Attribute(lit) ,  Kind(eletric device)  )
	 
	std::list<string> allKindsNames = this->getAllRegistedKinds();
	std::list<string> allEnumNames = this->getAllRegistedEnums();
	 

	if (HBlockMatchList mList = DynamicCasting::asHBlockMatchList(seletor))
	{
		return Resolve_Selector_List(mList, allKindsNames, allEnumNames, localsEntry);
	}

	return Resolve_Selector_item(seletor, allKindsNames, allEnumNames, localsEntry); 

	return seletor; // seletor nao resolvido ....
}