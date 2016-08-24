#include "CBlockInterpreterRuntime.h"
#include <iostream>

using namespace std;

HBlockInstance CBlockInterpreter::new_Instance(std::string named, HBlockKind kind) {
    // nova instance e inicializa os fields

    HBlockInstance c = std::make_shared<CBlockInstance>(named, kind);

    // inicia os fields CAN_BE

    std::list<HBlockKind> kinds = getUpperKinds(kind);
    std::cout << "Up Kinds  " << std::endl;
    for (auto &k : kinds) {
        std::cout << " ," << k->named;

    }
    std::cout << std::endl;
    std::cout << " ----------------------------- " << std::endl;
    for (auto &k : kinds) {
        for (auto &kvar : kind_variables) {
            if (HBlockKind dkind = dynamic_pointer_cast<CBlockKind>(kvar->get_obj())) {
                if (dkind->named == k->named) {
                    if (HBlockAssertion_canBe kvar_enum = dynamic_pointer_cast<CBlockAssertion_canBe>(kvar)) {
                        if (kvar_enum->definition->values.size() > 1) {
                            c->newEnumVariableSlot(kvar_enum->definition);
                        }
                        if (kvar_enum->definition->values.size() == 1) {
                            c->newBoolVariableSlot(kvar_enum->definition->values.front());
                        }
                    }
                }
            }
        }
    }

    // assign the defaults of kinds

    for (auto &k : kinds) {
        for (auto &kvar : default_assignments) {
            if (HBlockKind dkind = dynamic_pointer_cast<CBlockKind>(kvar->get_obj())) {

                if (dkind->named == k->named) {
                    if (HBlockNoum noumSet = dynamic_pointer_cast<CBlockNoum>(kvar->get_definition())) {
                        c->set(noumSet);
                    }
                }
            }
        }
    }

	//named variables

	for (auto &k : kinds) {
		for (auto &kvar : kind_named_variables) {
			if (kvar->kind->named == k->named)
			{
				HBlockKind_InstanceVariable v = dynamic_pointer_cast<CBlockKind_InstanceVariable>(kvar->variableNamed);
				HBlockKind nkindBase = resolve_kind(v->variableNamed->kind_name->named);
				c->newNamedVariable(v->variableNamed->property_name  , nkindBase);
			}
		}
	}
	

    return c;


}


void CBlockInterpreter::assign_variable_to_instance(HBlockAssertionBase kvar) {
    if (HBlockInstance c = dynamic_pointer_cast<CBlockInstance>(kvar->get_obj())) {
        {
            if (HBlockAssertion_canBe kvar_enum = dynamic_pointer_cast<CBlockAssertion_canBe>(kvar)) {
                if (kvar_enum->definition->values.size() > 1) {
                    c->newEnumVariableSlot(kvar_enum->definition);
                }
                if (kvar_enum->definition->values.size() == 1) {
                    c->newBoolVariableSlot(kvar_enum->definition->values.front());
                }
            }
        }
    }
}