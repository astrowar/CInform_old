
 
#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;


std::list<HBlock>  CBlockInterpreter::resolve_as_list(HBlock qlist)
{
	if (HBlockNoum	nn = dynamic_pointer_cast<CBlockNoum >(qlist))
	{
		HBlock resolved =  resolve_noum(nn);
		if (resolved != nullptr)
		{
			return resolve_as_list(resolved);
		}
	}

	if (HVariableNamed 	nvar  = dynamic_pointer_cast<CVariableNamed >(qlist))
	{
		return resolve_as_list(nvar->value);
	}

	if (HBlockProperty 	nprop = dynamic_pointer_cast<CBlockProperty >(qlist))
	{
		auto olist =  resolve_as_list( nprop->obj );
		// applica as propiedades a cada objeto
		std::list<HBlock> po_list;
		for(auto e: olist)
		{
			po_list.push_back(make_shared<CBlockProperty>(nprop->prop, e));
		}
		return po_list;

	}

	if (HBlockList nlist = dynamic_pointer_cast<CBlockList >(qlist) )
	{
		return nlist->lista;
	}

	return std::list<HBlock>();
}


HBlockKind CBlockInterpreter::getKindOf(HBlockInstance obj) {
    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        if (HBlockAssertion_is v = dynamic_pointer_cast<CBlockAssertion_is>(*it)) {
            if (v->get_obj() == obj) {
                if (HBlockKind k = dynamic_pointer_cast<CBlockKind>(v->get_definition())) {
                    return k;
                }
            }
        }
    }
    return nullptr;
}


string CBlockInterpreter::BlockNoum(HBlock c_block) {
    if (HBlockKind k0 = dynamic_pointer_cast<CBlockKind>(c_block)) {
        return k0->named;
    }

    if (HBlockInstance k1 = dynamic_pointer_cast<CBlockInstance>(c_block)) {
        return k1->named;
    }

    if (HBlockKindValue k2 = dynamic_pointer_cast<CBlockKindValue>(c_block)) {
        return k2->named;
    }

    if (HBlockNamedValue k3 = dynamic_pointer_cast<CBlockNamedValue>(c_block)) {
        return k3->named;
    }

    if (HBlockVariable k4 = dynamic_pointer_cast<CBlockVariable>(c_block)) {
        return k4->named;
    }

    if (HBlockNoum k5 = dynamic_pointer_cast<CBlockNoum>(c_block)) {
        return k5->named;
    }

	if (HBlockVerb k6 = dynamic_pointer_cast<CBlockVerb>(c_block)) {
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

HBlockKind CBlockInterpreter::resolve_kind(string n) {
    for (auto &defs : assertions) {
        if (HBlockKind nn = dynamic_pointer_cast<CBlockKind>(defs->get_definition())) {
            if (nn->named == n) {
                return nn;
            }
        }
    }
    return nullptr;

}

HBlock CBlockInterpreter::resolve_noum(HBlockNoum n) {
    // eh um kind de alguma coisa ?
    for (auto &defs : assertions) {
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(defs->get_obj())) {
            //std::cout << nn->named << std::endl;
            if (nn->named == n->named) {
                return defs->get_definition();
            }
        } 
    }

	for (auto &defs : global_variables) {
		if (HVariableNamed nnvar = dynamic_pointer_cast<CVariableNamed>(defs )) {
			//std::cout << nn->named << std::endl;
			if (nnvar->name->named  == n->named)
			{
				return nnvar ;
			}
		}
	}


    cout << "Fail to " << n->named << endl;
    return nullptr;


}

HBlock CBlockInterpreter::resolve_noum_as_variable(HBlockNoum n) {
	for (auto &defs : global_variables) {
		if (HVariableNamed nnvar = dynamic_pointer_cast<CVariableNamed>(defs)) {
			//std::cout << nn->named << std::endl;
			if (nnvar->name->named == n->named)
			{
				return nnvar;
			}
		}
	}
	return nullptr;

}

HBlock CBlockInterpreter::resolve_value(HBlock  c_block)
{
	if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(c_block))
	{
		auto  obj = resolve_noum(nn);
		return  resolve_value(obj);
	}

	if (HBlockInstance nIns = dynamic_pointer_cast<CBlockInstance>(c_block))
	{
		return nIns;
	}
	dçjfkçlsdjlkj
	return nullptr;

}

HBlock CBlockInterpreter::resolve_string(string n) {
    for (auto &defs : assertions) {
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(defs->get_obj())) {
            //std::cout << nn->named << std::endl;
            if (nn->named == n) {
                return defs->get_definition();
            }
        }
    }
    return nullptr;
}

