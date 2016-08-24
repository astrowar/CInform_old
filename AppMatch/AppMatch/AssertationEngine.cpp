
#include "CBlockInterpreterRuntime.h"

#include "CBlockMatch.h"
#include <iostream>

using namespace std;

void CBlockInterpreter::initialize() {
    for (auto &p : program) {
        execute_init(p);
    }

}

bool CBlockInterpreter::assert_it_canBe(HBlock c_block, HBlockEnums value) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(c_block)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_canBe(nobj, value);
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

bool CBlockInterpreter::assert_it_valuesDefinitions(HBlock c_block, HBlock value) {
    // Value Kind , is , list of Noums

    if (HBlockList vlist = dynamic_pointer_cast<CBlockList>(value)) // segundo argumento eh uma lista
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(c_block)) //primeiro eh um noum
        {
            // nn eh um value Kind ??
            HBlock nobj = resolve_noum(nn);
            if (HBlockKind nkind = dynamic_pointer_cast<CBlockKind>(
                    nobj)) //mas na verdade o primeiro eh um kind ja definido
            {
                for (auto &v : vlist->lista) {
                    assert_it_instance(v, nkind);
                }
                return true;
            }

        }
    return false;
}

void CBlockInterpreter::execute_init(HBlock p) {

    if (HBlockAssertion_isNotDirectAssign v = dynamic_pointer_cast<CBlockAssertion_isNotDirectAssign>(p)) {
        HBlock obj = v->get_obj();
        HBlock value = v->get_definition();
        if (assert_it_not_Value(obj, value)) return;
    }

    if (HBlockAssertion_isDefaultAssign v = dynamic_pointer_cast<CBlockAssertion_isDefaultAssign>(p)) {
        HBlock obj = v->get_obj();
        HBlock value = v->get_definition();
        if (assert_it_defaultValue(obj, value)) return;
    } else if (HBlockAssertion_canBe vee = dynamic_pointer_cast<CBlockAssertion_canBe>(p)) {
        HBlock obj = vee->get_obj();
        HBlockEnums evalue = vee->definition;
        if (assert_it_canBe(obj, evalue)) return;
    } else if (HBlockAssertion_is vk = dynamic_pointer_cast<CBlockAssertion_is>(p)) {
        HBlock obj = vk->get_obj();
        HBlock value = vk->get_definition();
        //Static Definition de uma instancia derivado
        if (assert_it_Value(obj, value)) return;
        if (assert_it_kind(obj, value)) return;
        if (assert_it_instance(obj, value)) return;
        if (assert_it_valuesDefinitions(obj, value)) return;

        throw "undefined block";
    } else if (HBlockAssertion_InstanceVariable ivar = dynamic_pointer_cast<CBlockAssertion_InstanceVariable>(p)) {
        HBlock obj = ivar->noum;
        HBlock value = ivar->instance_variable;
        if (assert_has_variable(obj, value)) return;
    } else if (HBlockToDecide dcMatch = dynamic_pointer_cast<CBlockToDecide>(p)) {
        if (assert_decideBlock(dcMatch)) return;

    }

    std::cout << "not found block definition " << endl;
    return;
}


bool CBlockInterpreter::assert_decideBlock(HBlockToDecide dct) {
    if (auto inner = std::dynamic_pointer_cast<CBlockMatch>(dct->queryToMatch)) {
        if (auto if_inner = std::dynamic_pointer_cast<CBlockAssertion_isDirectAssign>(inner->matchInner)) {
            decides_if.push_back(make_shared<CBlockToDecideIf>(if_inner, dct->decideBody));
            return true;
        }
    }
    decides_what.push_back(dct);
    return true;
}


bool CBlockInterpreter::assert_has_variable(HBlock obj, HBlock value) {

    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_has_variable(nobj, value);
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


//Forca value a ser Kind
HBlock CBlockInterpreter::value_can_be_assign_to(HBlock value, HBlockKind kind) {
    if (value == nullptr) return nullptr;

    if (HBlockEnums enumarate = dynamic_pointer_cast<CBlockEnums>(kind)) {
        // Acha todas as instancias

    }

    if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(value)) {
        HBlock resolved = resolve_noum(cnn);
        if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(resolved)) {
            if (is_derivadeOf(cinst, kind)) {
                return cinst;
            }
        }
    }

    return nullptr;

}


bool CBlockInterpreter::assert_it_property(HBlock propname, HBlock obj, HBlock value) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_property(propname, nobj, value);
        }
        return false;
    }
    if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum property_noum = dynamic_pointer_cast<CBlockNoum>(propname)) {
            HVariableNamed vv = cinst->get_property(property_noum->named);
            HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind));
            if (instanceValueRefered) {
                cinst->set_property(property_noum->named, instanceValueRefered);
                return true;
            }
        }
    }
    return false;

}

bool CBlockInterpreter::assert_it_Value(HBlock obj, HBlock value) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_Value(nobj, value);
        }
        return false;
    }

    if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
            HBlock nobj = resolve_noum(nbase);
            if (nobj == nullptr) {
                nInst->set(nbase);
                return true;
            }
        }
    }

    if (HBlockProperty prop_n = dynamic_pointer_cast<CBlockProperty>(obj)) {
        HBlock propNamed = prop_n->prop;
        HBlock destination = prop_n->obj;
        return assert_it_property(propNamed, destination, value);
    }

    return false;

}


bool CBlockInterpreter::assert_it_not_Value(HBlock obj, HBlock value) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_not_Value(nobj, value);
        }
        return false;
    }

    if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
            HBlock nobj = resolve_noum(nbase);
            if (nobj == nullptr) {
                nInst->unset(nbase);
                return true;
            }
        }

    }
    return false;
}
bool CBlockInterpreter::assert_property_defaultValue(HBlockProperty prop, HBlock value)
{
	if (HBlockNoum prop_obj_noum = dynamic_pointer_cast<CBlockNoum>(prop->obj))
	{
		HBlock nobj = resolve_noum(prop_obj_noum);
		
		return assert_property_defaultValue(  make_shared<CBlockProperty>(prop->prop, nobj  )   , value);

	}
	if (HBlockInstance prop_obj_inst = dynamic_pointer_cast<CBlockInstance>(prop->obj))
	{
		throw "cant assign Ususally to Instances";
		return false;
	}

	if (HBlockKind prop_obj_kind = dynamic_pointer_cast<CBlockKind>(prop->obj))
	{
		if (HBlockNoum prop_name_noum = dynamic_pointer_cast<CBlockNoum>(prop->prop))
		{			 
			default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(prop_obj_kind, value));
			return true;
		}
	}

	return false;
}
bool CBlockInterpreter::assert_it_defaultValue(HBlock obj, HBlock value) {
    //default value so eh valudi para Kinds
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_defaultValue(nobj, value);
        }
        return false;
    } else if (HBlockInstance ibase = dynamic_pointer_cast<CBlockInstance>(obj)) {
        throw "cant assign Ususally to Instances";
    } else if (HBlockProperty pbase = dynamic_pointer_cast<CBlockProperty>(obj)) {

		return assert_property_defaultValue(pbase, value);


    } else if (HBlockKind kbase = dynamic_pointer_cast<CBlockKind>(obj)) {
        if (HBlockNoum nvalue = dynamic_pointer_cast<CBlockNoum>(value)) {
            std::cout << kbase->named << "  " << nvalue->named << std::endl;
            //default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, nvalue));
        }

        default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, value));
    }

    return false;
}

std::pair<HBlockKind, HBlockKind>
CBlockInterpreter::create_derivadeKind(std::string called, std::string baseClasseName) {

    HBlockKind b = nullptr;
    HBlockKind bup = nullptr;

    if (baseClasseName == "value") {
        b = make_shared<CBlockKindValue>(called);

    } else if (baseClasseName == "") {
        b = make_shared<CBlockKindThing>(called);  //Default
    } else {
        // o que eh a baseclass ???
        HBlock r = resolve_string(baseClasseName);

        if (HBlockKindThing kt = dynamic_pointer_cast<CBlockKindThing>(r)) {
            b = make_shared<CBlockKindThing>(called);
            bup = kt;
        } else if (HBlockKindValue ktv = dynamic_pointer_cast<CBlockKindValue>(r)) {
            b = make_shared<CBlockKindValue>(called);
            bup = ktv;
        } else {
            std::cout << "What ?? " << baseClasseName << endl;
            throw "Error on derive a kind";
        }

    }
    return std::pair<HBlockKind, HBlockKind>(b, bup);

}

bool CBlockInterpreter::assert_it_kind(HBlock obj, HBlock value) {
    if (HBlockKindOfName k = dynamic_pointer_cast<CBlockKindOfName>(value)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {

            auto b_up = create_derivadeKind(nbase->named, k->baseClasseName);
            HBlockKind b = b_up.first;

            if (b_up.second != nullptr) {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                     make_shared<CBlockKindOf>(
                                                                                                             b_up.second));
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

            {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbase, b);
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

            std::cout << "new Kind add " << nbase->named <<  endl;
            return true;
        }

            //Processa a lista
        else if (HBlockList nList = dynamic_pointer_cast<CBlockList>(obj)) {
            for (auto nObj : nList->lista) {
                if (HBlockNoum nbasei = dynamic_pointer_cast<CBlockNoum>(nObj)) {
                    auto b_up = create_derivadeKind(nbasei->named, k->baseClasseName);
                    HBlockKind b = b_up.first;
                    if (b_up.second != nullptr) {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                             make_shared<CBlockKindOf>(
                                                                                                                     b_up.second));
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }

                    {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbasei, b);
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }
                    std::cout << "new Kind add" << endl;
                }
            }
            return true;

        }

    }
    return false;

}

bool CBlockInterpreter::assert_it_instance(HBlock obj, HBlock value) {
    if (HBlockNoum nvalue = dynamic_pointer_cast<CBlockNoum>(value)) {
        if (HBlockNoum nobj = dynamic_pointer_cast<CBlockNoum>(obj)) {
            HBlock nn = resolve_noum(nvalue);
            if (HBlockKind k = dynamic_pointer_cast<CBlockKind>(nn)) {
                //HBlockInstance binstance = make_shared<CBlockInstance>(nobj->named);

                HBlockInstance binstance = new_Instance(nobj->named, k);

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(obj, binstance);
                HBlockAssertion_isInstanceOf newInst = make_shared<CBlockAssertion_isInstanceOf>(binstance, k);
                assertions.push_back(newDefi);
                assertions.push_back(newInst);
                std::cout << "new Instance add" << endl;
                return true;
            }
            return false;
        }

            //Many instances
        else if (HBlockList nobjList = dynamic_pointer_cast<CBlockList>(obj)) {
            for (auto &e : nobjList->lista) {
                assert_it_instance(e, value);
            }
            return true;
        }

    }

    return false;
}

