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


string CBlockInterpreter::getStringPrexfedFromList(std::vector<string> noumFragmented , std::list<string> allStringNames )
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
	if (kind->named =="kind")
	{
		for (auto &defs : assertions)
		{
			if (HBlockKind nn = DynamicCasting::asHBlockKind(defs->get_definition())) {
				ret.push_back( nn );
			}
		}
		return ret;
	}

	 
	for (auto &nInst : instancias)
	{
		if (isSameString(nInst->baseKind->named, kind->named))
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

	std::list<HBlock> results;

	if (HBlockMatchNoum mNoum = DynamicCasting::asHBlockMatchNoum(seletor))
	{
		for (auto &nInst : instancias)
		{
			auto qret = query_is(nInst, mNoum->inner, localsEntry, QueryStack());
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
						auto qret = query_is(mInst, m, localsEntry, QueryStack());
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


CBlocking::HBlockMatch CBlockInterpreter::Resolve_Selector(HBlockMatch seletor, HRunLocalScope localsEntry)
{
	//resolve seletor ... IE 
	// List( Noum(black) , Noum(Thing) ) -> And(Attribute(black) ,  Kind(Thing)  )

	// best friend is a Person that varies
	// List( Noum(best) , Noum(friend) )  -> Noum( best friend ) 


	// List( Noum(closed) , Noum(magical) ,Noum(item) ) -> And(Attribute(closed) ,  Attribute(magical) ,Kind(item)  )

	
	 

	if (HBlockMatchNoum mNoum = DynamicCasting::asHBlockMatchNoum(seletor))
	{
		std::list<string> allKindsNames = this->getAllRegistedKinds(); //incluindo os kinds do sistema, value Kinds e verbs
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
		  
		// Aqui temos um problema ... mList pode ser A,B,C ond e A  eh um modificador  e B C formam uma palavra valida
		 
		std::list<string> allKindsNames = this->getAllRegistedKinds();

		for(auto pivot = mList->matchList.begin(); pivot != mList->matchList.end();++pivot)
		{
			// ultima parte 
			std::vector<HBlockMatch> lastPart(pivot, mList->matchList.end());
			if (lastPart.empty()) break; //ultimo item da lista 

			std::vector<string> strList = isHBlockMatchNoumList(lastPart);
			if (strList.empty()) break; // nao eh um grupo de Noums continuos

			string kindFound =  getStringPrexfedFromList(strList, allKindsNames);
			if (!(kindFound.empty() ))
			{
			    //a ultima parte  eh o nome de um Kind valido !!
				HBlockMatchList retList = make_shared<CBlockMatchList>(std::list<HBlockMatch>(mList->matchList.begin() , pivot) );
				HBlockMatchKind matchKind = make_shared<CBlockMatchKind>(make_shared<CBlockKindThing>(kindFound));
				auto retValue = make_shared<CBlockMatchAND >(std::list<HBlockMatch> ({ matchKind , retList }) );
				return retValue;
			}

		}

	}

	return seletor; // seletor nao resolvido ....
}