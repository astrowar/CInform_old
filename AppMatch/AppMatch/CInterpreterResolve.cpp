
 
#include "CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"
 
using namespace std;

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

	if (HVariableNamed 	nvar  = asHVariableNamed (qlist))
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


string CBlockInterpreter::BlockNoum(HBlock c_block) {
	if (HBlockKind k0 = asHBlockKind(c_block)) {
		return k0->named;
	}

	if (HBlockInstance k1 = asHBlockInstance(c_block)) {
		return k1->named;
	}

	if (HBlockKindValue k2 = asHBlockKindValue(c_block)) {
		return k2->named;
	}

	if (HBlockNamedValue k3 = asHBlockNamedValue(c_block)) {
		return k3->named;
	}

	if (HBlockVariable k4 = asHBlockVariable(c_block)) {
		return k4->named;
	}

	if (HBlockNoum k5 = asHBlockNoum(c_block)) {
		return k5->named;
	}

	if (HBlockVerb k6 = asHBlockVerb(c_block)) {
		return k6->named ;
	}


	return "";
}



HBlock CBlockInterpreter::resolve(CTerm *b) {
	return make_shared<CBlockNoum>(b->repr());
}

HBlock CBlockInterpreter::resolve_of(HBlock b, HBlock a) {
	//return new CBlockProperty( b , a);
	return nullptr;
}

HBlockKind CBlockInterpreter::resolve_system_kind(string n) 
{
	{
		if (n == "text") {
			return  std::make_shared<CBlockKindValue>("text");
		}

	}

	{
		if (n == "action") {
			return  std::make_shared<CBlockKindValue>("action");
		}

	}
	return nullptr;
}


HBlockKind CBlockInterpreter::resolve_kind(string n) {
	for (auto &defs : assertions) {
		if (HBlockKind nn = asHBlockKind(defs->get_definition())) {
			if (nn->named == n) {
				return nn;
			}
		}
	}
	if (auto kcustom = resolve_system_kind(n))
	{
		return kcustom;
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
HBlock CBlockInterpreter::resolve_noum(HBlockNoum n, HRunLocalScope localsEntry ,std::list<std::string>  noumsToResolve ) 
{
	if (std::find(noumsToResolve.begin(), noumsToResolve.end(), n->named) != noumsToResolve.end())
	{
		return nullptr;
	}
	noumsToResolve.push_front(n->named);

	// eh um kind de alguma coisa ?

	if (localsEntry != nullptr) 
	{
		auto lnoum = localsEntry->resolve(n->named);
		if (lnoum != nullptr)
		{			
			return resolve_if_noum(lnoum,localsEntry, noumsToResolve );
		}
	}

	//eh uma instancia de alguem ??
	for (auto &a_inst : instancias) 
	{
		 
		if (a_inst->named == n->named)
		{
			return a_inst;
		}
	}

	

	for (auto &defs : assertions) {
		if (HBlockNoum nn = asHBlockNoum(defs->get_obj())) {
			//logMessage("assertation named : " + nn->named );
			if (nn->named == n->named) 
			{
				return resolve_if_noum(defs->get_definition(), localsEntry, noumsToResolve);
			}
		}
	}

	for (auto &defs : global_variables) {
		if (HVariableNamed nnvar = asHVariableNamed(defs)) {
			//logMessage( nn->named << std::endl;
			if (nnvar->name->named == n->named) {
				return resolve_if_noum( nnvar, localsEntry, noumsToResolve);
			}
		}
	}

	for (auto &adefs : actions_header) {

		if (adefs->named == n->named) {
			return resolve_if_noum(adefs,localsEntry, noumsToResolve);
		}

	}



	//Custom Resolvers

	if (auto kcustom = resolve_system_kind(n->named)) {
		return resolve_if_noum(kcustom,localsEntry, noumsToResolve);
	}

	//logError("Fail to " + n->named);
	if (n->named == "D")
	{
		return nullptr;
	}
	return nullptr;


}

HBlock CBlockInterpreter::resolve_noum_as_variable(HBlockNoum n) 
{
	for (auto &defs : global_variables) {
		if (HVariableNamed nnvar = asHVariableNamed(defs)) {
			//std::cout << nn->named << std::endl;
			if (nnvar->name->named == n->named)
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

