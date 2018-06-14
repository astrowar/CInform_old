// PVS
// PVQ
 
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "sharedCast.hpp"
 #include "CBlockInterpreterRuntime.hpp"
#include <algorithm>
#include <cstring>
#include <locale>
#include "CBlockNumber.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
 

HBlockNoum  CBlockInterpreter::get_plural_of( string s )
{
	for(auto v : plural_assertations)
	{
		
		if (isSameString(v.first->named, s))
		{
			return v.second ;
		}
	}
	return nullptr;
}



bool CBlockInterpreter::isSameString(string s1 , string s2)
{
	if (s1 == s2) return true;
	if (( s1.size() ==  s2.size()) && (tolower( s1[0]) == tolower(s2[0])))
	{
		int n = s1.size();
		for(int j = 0 ; j< n ;++j )
		{
			if (tolower(s1[j]) != tolower(s2[j])) return false;
		}
		return true;
	}
	return false;
}




 



std::list<HBlock>  CBlockInterpreter::resolve_as_list(HBlock qlist, HRunLocalScope localsEntry)
{
	return resolve_as_list(qlist, localsEntry, std::list<std::string>());
}
std::list<HBlock>  CBlockInterpreter::resolve_as_list(HBlock qlist, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve)
{
	if (HBlockNoum	nn = asHBlockNoum(qlist))
	{
		HBlock resolved =  resolve_noum(nn,localsEntry, noumsToResolve);
		if (resolved != nullptr)
		{
			return resolve_as_list(resolved,localsEntry, noumsToResolve);
		}
	}

	if (HBlockVariableNamed 	nvar  = asHBlockVariableNamed (qlist))
	{
		return resolve_as_list(nvar->value,localsEntry, noumsToResolve);
	}

	if (HBlockProperty 	nprop = asHBlockProperty (qlist))
	{
		auto olist =  resolve_as_list( nprop->obj ,localsEntry, noumsToResolve);
		// applica as propiedades a cada objeto
		std::list<HBlock> po_list;
		for(auto e: olist)
		{
			po_list.push_back(make_shared<CBlockProperty>(nprop->prop, e));
		}
		return po_list;

	}

	if (HBlockList nlist = asHBlockList (qlist) )
	{
		return nlist->lista;
	}

	return std::list<HBlock>();
}


HBlockKind CBlockInterpreter::getKindOf(HBlockInstance obj) {
	for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		if (HBlockAssertion_is v = asHBlockAssertion_is(*it)) {
			if (v->get_obj() == obj) {
				if (HBlockKind k = asHBlockKind(v->get_definition())) {
					return k;
				}
			}
		}
	}
	return nullptr;
}


string CBlockInterpreter::asBlockNoum(HBlock c_block) 
{

	//if (HBlockKind k0 = asHBlockKind(c_block)) 
	//{
	//	return k0->named;
	//}

	//if (HBlockInstance k1 = asHBlockInstance(c_block)) {
	//	return k1->named;
	//}

	//if (HBlockAction   kaa = asHBlockAction (c_block)) {
	//	return   kaa->named;
	//}

	if (HBlockKindValue k2 = asHBlockKindValue(c_block)) 
	{
		return k2->named;
	}

	if (HBlockNamedValue k3 = asHBlockNamedValue(c_block)) {
		return k3->named;
	}

 

	if (HBlockNoum k5 = asHBlockNoum(c_block)) {
		return k5->named;
	}

	if (HBlockVerb k6 = asHBlockVerb(c_block)) {
		return   k6->named ;
	}

	for (auto s : symbols)
	{
		if (s.second.get() == c_block.get())
		{
			return s.first;
		}
	}

	return "";
}



//HBlock CBlockInterpreter::resolve(NSTerm::CTerm *b) {
//	return make_shared<CBlockNoumStr>(b->repr());
//}

HBlock CBlockInterpreter::resolve_of(HBlock b, HBlock a) {
	//return new CBlockProperty( b , a);
	return nullptr;
}

HBlockKind CBlockInterpreter::resolve_system_kind(string n) 
{
	{
		if (isSameString( n , "text")) {
			return  std::make_shared<CBlockKindValue>("text");
		}
	}
	{
		if (isSameString(n, "number")) {
			return  std::make_shared<CBlockKindValue>("number");
		}

	} 
	{
		if (isSameString(n, "action"))
		{
			return  std::make_shared<CBlockKindEntity>("action");
		}

		if (isSameString(n, "relation"))
		{
			return  std::make_shared<CBlockKindEntity>("relation");
		}


		
	}
	return nullptr;
}

HBlockKind CBlockInterpreter::resolve_user_kind(string n)
{
	
	for (auto s : symbols)
	{
		if (s.first == n)
		{
			if (HBlockKind nn = asHBlockKind(s.second ))
			{
				return nn;
			}
		}
	}

	//for (auto &defs : assertions)
	//{ 
	//	if (HBlockKind nn = asHBlockKind(defs->get_definition())) {
	//		if ( isSameString( nn->named , n)) 
	//		{
	//			return nn;
	//		}
	//	}
	//}

	return nullptr;
}


HBlockKind CBlockInterpreter::resolve_kind(string n) 
{


	//for (auto &defs : assertions) 
	//{
	//	if (HBlockKind nn = asHBlockKind(defs->get_definition())) 
	//	{
	//		if (isSameString(nn->named, n)) 
	//		{
	//			return nn;
	//		}
	//	}
	//	if (HBlockKindValue nn = asHBlockKindValue(defs->get_definition()))
	//	{
	//		if (isSameString(nn->named, n))
	//		{
	//			return nn;
	//		}
	//	}
	//}



	if (auto kcustom = resolve_system_kind(n))
	{
		return kcustom;
	}
	 
	if (auto k = resolve_user_kind(n))
	{
		return k;
	}

	return nullptr;

}

HBlock CBlockInterpreter::resolve_if_noum(HBlock  n, HRunLocalScope localsEntry,std::list<std::string>  noumsToResolve)
{
	if (auto anoum = asHBlockNoum(n))
	{		 
		 return resolve_noum(anoum, localsEntry, noumsToResolve );	 
	}
	return n;
}

 

HBlock CBlockInterpreter::resolve_noum(HBlockNoum n, HRunLocalScope localsEntry)
{
	return resolve_noum(n, localsEntry, std::list<std::string>());
}
HBlock CBlockInterpreter::has_resolve_noum(HBlockNoum n, HRunLocalScope localsEntry)
{
	return has_resolve_noum(n, localsEntry, std::list<std::string>());
}
 

HBlock CBlockInterpreter::resolve_noum(HBlockNoum n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve)
{
	return resolve_string_noum(n->named, localsEntry, noumsToResolve);
}

HBlock CBlockInterpreter::has_resolve_noum(HBlockNoum n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve)
{
	return has_resolve_string_noum(n->named, localsEntry, noumsToResolve);
}

bool  is_number(const std::string  s)
{
	auto start = s.begin() + (s[0] == '-');
	return
		!s.empty() &&
		s.end() == std::find_if(start, s.end(), [](char c) 
	{
		return (isdigit(c)==false ) && (c != '.');
	}) && 
		std::count(start, s.end(), '.') <= 1;

}

HBlock CBlockInterpreter::resolve_string_noum(string named, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve)
{
	auto h = has_resolve_string_noum(named, localsEntry, noumsToResolve);
	if (h==nullptr)
	{
		//printf("* Unable to resolve %s \n", named.c_str());
	}
	return h;
}

HBlock CBlockInterpreter::has_resolve_string_noum(string named, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve)
{
	if (isSameString(named , "true")) return std::make_shared<CBlockBooleanValue>(true);
	if (isSameString(named , "false")) return std::make_shared<CBlockBooleanValue>(false);
	if (isSameString(named, "yes")) return std::make_shared<CBlockBooleanValue>(true);
	if (isSameString(named , "no")) return std::make_shared<CBlockBooleanValue>(false);
	if (isSameString(named, "nothing")) return Nothing;

	if (std::find(noumsToResolve.begin(), noumsToResolve.end(), named) != noumsToResolve.end())
	{
		return nullptr;
	}
	noumsToResolve.push_front(named);

	// eh um kind de alguma coisa ?

	if (localsEntry != nullptr)
	{
		auto lnoum = localsEntry->resolve(named);
		if (lnoum != nullptr)
		{
			return resolve_if_noum(lnoum, localsEntry, noumsToResolve);
		}
	}


	for (auto s : symbols)
	{
		if (s.first == named)
		{
			return s.second;
		}
	}  
	
	return nullptr;








	////eh uma instancia de alguem ??
	//for (auto &a_inst : instancias)
	//{
	//	if (a_inst->named == named)
	//	{
	//		return a_inst;
	//	}
	//}

	//for (auto &a_action : actions_header)
	//{
	//	if (isSameString( a_action->named , named ))
	//	{
	//		return a_action;
	//	}
	//}


	//for (auto &defs : assertions) {
	//	if (HBlockNoum nn = asHBlockNoum(defs->get_obj())) {
	//		//logMessage("assertation named : " + nnamed );
	//		if (isSameString(nn->named ,named))
	//		{
	//			return resolve_if_noum(defs->get_definition(), localsEntry, noumsToResolve);
	//		}
	//	}
	//}

	//for (auto &defs : global_variables) {
	//	if (HBlockVariableNamed nnvar = asHBlockVariableNamed(defs)) {
	//		//logMessage( nnamed << std::endl;
	//		if (isSameString(nnvar->name->named , named)) {
	//			return resolve_if_noum(nnvar, localsEntry, noumsToResolve);
	//		}
	//	}
	//}

	//for (auto &adefs : actions_header) {

	//	if (isSameString(adefs->named , named)) {
	//		return resolve_if_noum(adefs, localsEntry, noumsToResolve);
	//	}

	//}

	//{
	//	auto rel_find = this->staticRelation.find(named);
	//	if (rel_find != this->staticRelation.end())
	//	{
	//		return rel_find->second;
	//	}
	//}
	//



	////Custom Resolvers

	//if (auto kcustom = resolve_system_kind(named)) {
	//	return resolve_if_noum(kcustom, localsEntry, noumsToResolve);
	//}

	//if (auto ukcustom = resolve_user_kind(named)) {
	//	return resolve_if_noum(ukcustom, localsEntry, noumsToResolve);
	//}


	//if (strncmp(named.c_str(), "verb ", 5) == 0)
	//{
	//	int np = named.size();
	//	std::string vremaind = named.substr(5, np);
	//	logMessage(vremaind);
	//	for (auto &v : verbs)
	//	{
	//		if (isSameString(v->named , vremaind))
	//		{
	//			logMessage(" verb " + vremaind);
	//			return v;
	//		}
	//	}
	//	logError(" verb " + vremaind+" not registed");
	//	return nullptr;
	//}



	//if (is_number( named ) )
	//{
	//	int jValue = atoi(named.c_str());
	//	return  make_shared<CBlockIntegerNumber>(jValue);

	//}

	// 
	//return nullptr;


}



HBlock CBlockInterpreter::resolve_noum_as_variable(HBlockNoum n) 
{
	for (auto &defs : global_variables) {
		if (HBlockVariableNamed nnvar = asHBlockVariableNamed(defs)) {
			//std::cout << nn->named << std::endl;
			if (isSameString(nnvar->name->named, n->named))
			{
				return nnvar;
			}
		}
	}
	return nullptr;

}

 

HBlock CBlockInterpreter::resolve_string(string n, HRunLocalScope localsEntry)
{
	if (localsEntry != nullptr)
	{
		auto lnoum = localsEntry->resolve(n );
		if (lnoum != nullptr) return lnoum;
	}

	for (auto &defs : assertions) {
		if (HBlockNoum nn = asHBlockNoum(defs->get_obj())) {
			//std::cout << nn->named << std::endl;
			if (nn->named == n) {
				return defs->get_definition();
			}
		}
	}
	return nullptr;
}


std::list<string>  CBlockInterpreter::getAllRegistedEnums()
{
	std::list<string> ret;

	for (auto n : registred_adjetives) ret.push_back(n->named);
 
	return ret;
}
std::list<string>  CBlockInterpreter::getAllRegistedKinds()
{
	std::list<string> ret;

	//add todos os tipos do sistema que geram INSTANCIAS
	ret.push_back("kind");
	ret.push_back("action");
	ret.push_back("verb");
	ret.push_back("relation");

	for (auto &s : symbols)
	{
		if (HBlockKind nn = asHBlockKind(s.second)) 
		{
			ret.push_back(s.first);
		}
	} 
	return ret;
}
