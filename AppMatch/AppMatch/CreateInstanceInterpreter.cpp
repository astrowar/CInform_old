#include "CBlockInterpreterRuntime.h"
#include <iostream>

using namespace std;


void CBlockInterpreter::dump_instance(string str )
{
	return dump_instance(str, nullptr);
}

void CBlockInterpreter::dump_instance(string str,   HRunLocalScope localsEntry) {
    HBlock n = resolve_string(str,localsEntry);
    if (HBlockInstance nn = dynamic_pointer_cast<CBlockInstance>(n)) {
        for (auto &va : nn->anomimousSlots) {
            cout << "====================" << endl;
            if (HVariableSlotEnum venum = dynamic_pointer_cast<CVariableSlotEnum>(va)) {

                venum->valueDefinition->dump("    ");
                venum->value->dump("    ");

            }
            if (HVariableSlotBool vbool = dynamic_pointer_cast<CVariableSlotBool>(va)) {

                vbool->valueDefinition->dump("    ");
                cout << vbool->value << endl;
            }
        }

    }
}






HBlockInstance CBlockInterpreter::new_Instance(string named, HBlockKind kind) {
    // nova instance e inicializa os fields

    HBlockInstance c = make_shared<CBlockInstance>(named, kind);

    // inicia os fields CAN_BE

    list<HBlockKind> kinds = getUpperKinds(kind);
    cout << "Up Kinds  " << endl;
    for (auto &k : kinds) {
        cout << " ," << k->named;

    }
    cout << endl;
    cout << " ----------------------------- " << endl;
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

	//named variables
	for (auto &k : kinds) {
		for (auto &kvar : kind_named_variables) {
			if (kvar->kind->named == k->named)
			{
				HBlockInstanceVariable v = dynamic_pointer_cast<CBlockInstanceVariable>(kvar->variableNamed);
				HBlockKind nkindBase = resolve_kind(v->kind_name->named);
				c->newNamedVariable(v->property_name, nkindBase);
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

			if (HBlockProperty  dproperty = dynamic_pointer_cast<CBlockProperty>(kvar->get_obj())) {

				if (HBlockKind  dp_kind = dynamic_pointer_cast<CBlockKind>(dproperty->obj))
				{
					if (dp_kind->named == k->named)
					{

						if (HBlockNoum   dp_propname = dynamic_pointer_cast<CBlockNoum>(dproperty->prop ))
						{
							c->set_property(dp_propname->named, kvar->get_definition());
						}
					}
				}
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