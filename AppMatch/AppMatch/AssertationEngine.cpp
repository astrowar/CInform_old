
#include "CBlockInterpreterRuntime.h"

#include "CBlockMatch.h"
#include <iostream>
#include "CBlockUndestand.h"
#include "CBlockDecideIf.h"

using namespace std;

void CBlockInterpreter::initialize() {
    for (auto &p : program) {
        execute_init(p);
    }

}

bool CBlockInterpreter::assert_it_canBe(HBlock c_block, HBlockEnums value, HRunLocalScope localsEntry) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(c_block)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_canBe(nobj, value,localsEntry);
        }
        return false;
    } else if (HBlockKind nkind = dynamic_pointer_cast<CBlockKind>(c_block)) {
        kind_variables.push_back(make_shared<CBlockAssertion_canBe>(nkind, value));
        return true;
    } else if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(c_block)) {
        auto p = make_shared<CBlockAssertion_canBe>(nInst, value);
        assign_variable_to_instance(make_shared<CBlockAssertion_canBe>(nInst, value));

        return true;
    }

    return true;
}




bool CBlockInterpreter::assert_decideBlock(HBlockToDecide dct) {
    if (auto inner = dynamic_pointer_cast<CBlockMatchIs>(dct->queryToMatch)) 
	{
        
            decides_if.push_back(make_shared<CBlockToDecideIf>(inner, dct->decideBody));
            return true;
        
    }
    decides_what.push_back(dct);
    return true;
}


 
bool CBlockInterpreter::assert_has_variable(HBlock obj, HBlock value,   HRunLocalScope localsEntry) {

    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_has_variable(nobj, value, localsEntry);
        }
        return false;
    }

    if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        //name da variavel
        if (HBlockInstanceVariable variable_ = dynamic_pointer_cast<CBlockInstanceVariable>(value)) {
            HBlockKind nkindBase = resolve_kind(variable_->kind_name->named);
            nInst->newNamedVariable(variable_->property_name, nkindBase);
            return true;
        }

    } else if (HBlockKind nKind = dynamic_pointer_cast<CBlockKind>(obj)) 	{
		
		if (HBlockInstanceVariable iVariableNamed = dynamic_pointer_cast<CBlockInstanceVariable>(value)) {
			if (HBlockKind_InstanceVariable variable_ = make_shared<CBlockKind_InstanceVariable>(nKind, iVariableNamed))
			{
			 
				kind_named_variables.push_back(variable_);
				return true;
			}
		}
		 
    }
    return false;
}

bool CBlockInterpreter::is_all_items_of_kind(HBlockList listvalues, HBlockKind kind , HRunLocalScope localsEntry)
{
    for( auto &v : listvalues->lista )
    {
        if (value_can_be_assign_to(v,kind,localsEntry) == nullptr  ) return false ;

    }
    return true;


}

//Forca value a ser Kind
HBlock CBlockInterpreter::value_can_be_assign_to(HBlock value, HBlockKind kind, HRunLocalScope localsEntry) {
	if (value == nullptr) return nullptr;

	if (HBlockEnums enumarate = dynamic_pointer_cast<CBlockEnums>(kind)) {
		// Acha todas as instancias
		if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(value))
		{
			for (auto &ee : enumarate->values)
			{
				if (ee->named == cnn->named) return ee;
			}
			return nullptr;
		}
	}

	
	if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(value)) {
		if (is_derivadeOf(cinst, kind ,localsEntry )) {
			return cinst;
		}
	}

	if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(value)) {
		HBlock resolved = resolve_noum(cnn,localsEntry);
		if (resolved != nullptr)
		{
			return value_can_be_assign_to(resolved, kind,localsEntry);
		}
	}

    if (HBlockList clist = dynamic_pointer_cast<CBlockList>(value))
    {
        //Kind precisa ser uma lista tambem
        if (HBlockListOfKind klist = dynamic_pointer_cast<CBlockListOfKind>(kind)) {
            //tem algum tipo que nao corresponde ?
            if (is_all_items_of_kind(clist, klist->itemKind,localsEntry) == false)
            {
                return nullptr;
            }
            return value;

        }
    }


	return nullptr;

}


bool CBlockInterpreter::assert_it_property(HBlock propname, HBlock obj, HBlock value,   HRunLocalScope localsEntry) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_property(propname, nobj, value,localsEntry);
        }
        return false;
    }
    if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum property_noum = dynamic_pointer_cast<CBlockNoum>(propname)) {
            HVariableNamed vv = cinst->get_property(property_noum->named);
			if (vv == nullptr)
			{
				cout << "Obje dont have " << property_noum->named << "property " <<  endl;
			}
            HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind,localsEntry));
            if (instanceValueRefered) {
                cinst->set_property(property_noum->named, instanceValueRefered);
                return true;
            }
        }
    }
    return false;

}



bool CBlockInterpreter::assert_it_not_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_not_Value(nobj, value,localsEntry);
        }
        return false;
    }

    if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
            HBlock nobj = resolve_noum(nbase,localsEntry);
            if (nobj == nullptr) {
                nInst->unset(nbase);
                return true;
            }
        }

    }
    return false;
}



void CBlockInterpreter::execute_init(HBlock p) {


	  HRunLocalScope localsEntry = nullptr;
	if (HBlockAssertion_isNotDirectAssign v = dynamic_pointer_cast<CBlockAssertion_isNotDirectAssign>(p)) {
		HBlock obj = v->get_obj();
		HBlock value = v->get_definition();
		if (assert_it_not_Value(obj, value, localsEntry)) return;
	}

	if (HBlockAssertion_isDefaultAssign v = dynamic_pointer_cast<CBlockAssertion_isDefaultAssign>(p)) {
		HBlock obj = v->get_obj();
		HBlock value = v->get_definition();
		if (assert_it_defaultValue(obj, value, localsEntry)) return;
	}
	else if (HBlockAssertion_canBe vee = dynamic_pointer_cast<CBlockAssertion_canBe>(p)) {
		HBlock obj = vee->get_obj();
		HBlockEnums evalue = vee->definition;
		if (assert_it_canBe(obj, evalue, localsEntry)) return;
	}
	else if (HBlockIsVerb  vRelation = dynamic_pointer_cast<CBlockIsVerb>(p)){

		HBlock obj = vRelation->get_obj();
		HBlock value = vRelation->get_definition();
		if (assert_it_verbRelation(vRelation->verb , obj, value,localsEntry)) return;
    }
	else if (HBlockAssertion_isVariable  vGlobal  = dynamic_pointer_cast<CBlockAssertion_isVariable>(p)) {


		if (assert_it_variableGlobal(vGlobal->variable, vGlobal->baseKind )) return;
	}

	else if (HBlockAssertion_is vk = dynamic_pointer_cast<CBlockAssertion_is>(p)) {
        HBlock obj = vk->get_obj();
        HBlock value = vk->get_definition();
        //Static Definition de uma instancia derivado
        if (assert_it_Value(obj, value,localsEntry)) return;
        if (assert_it_kind(obj, value,localsEntry)) return;
        if (assert_it_instance(obj, value,localsEntry)) return;
        if (assert_it_valuesDefinitions(obj, value,localsEntry)) return;
		if (assert_it_action(obj, value)) return;
		 

        throw "undefined block";
    } else if (HBlockAssertion_InstanceVariable ivar = dynamic_pointer_cast<CBlockAssertion_InstanceVariable>(p)) {
        HBlock obj = ivar->noum;
        HBlock value = ivar->instance_variable;
        if (assert_has_variable(obj, value,localsEntry)) return;
    } else if (HBlockToDecide dcMatch = dynamic_pointer_cast<CBlockToDecide>(p)) {
        if (assert_decideBlock(dcMatch)) return;

    }
	if (HBlockVerbRelation dcverbImpl = dynamic_pointer_cast<CBlockVerbRelation>(p)) 	
	{ 

		if (assert_newVerb(dcverbImpl)) return; 
	}
	  

	if (HBlockUnderstandDynamic    dn_dispatch = dynamic_pointer_cast<CBlockUnderstandDynamic >(p))
	{
		if (assert_newUnderstand(dn_dispatch)) return;
		
	}



    cout << "not found block definition " << endl;
    return;
}
