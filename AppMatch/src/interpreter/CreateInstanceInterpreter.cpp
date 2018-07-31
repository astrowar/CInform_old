// PVS
// PVQ
 
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "sharedCast.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;


 

 


void CBlockInterpreter::dump_instance(string str )
{
	return dump_instance(str, nullptr);
}

void CBlockInterpreter::dump_instance(string str,   HRunLocalScope localsEntry) {
    HBlock n = resolve_string(str,localsEntry);
	if (HBlockInstance nn = asHBlockInstance(n))
	{
		for (auto &va : nn->anomimousSlots) {

			if (HVariableSlotEnum venum = asHVariableSlotEnum(va)) {

				venum->valueDefinition->dump("    ");
				venum->value->dump("    ");

			}
			if (HVariableSlotBool vbool = asHVariableSlotBool(va)) {

				vbool->valueDefinition->dump("    ");
				printf("%i ", vbool->value);
			}
		}
	}
}

void CBlockInterpreter::add_constantValueVariableToAllinstances(HBlockAssertion_isConstantAssign kvar)
{
	// TODO

}

void CBlockInterpreter::add_forbidenValueVariableToAllinstances(HBlockAssertion_isForbiddenAssign kvar)
{
	// TODO
}

void CBlockInterpreter::add_defaultValueVariableToAllinstances(HBlockAssertion_isDefaultAssign kvar)
{
	
	for (auto &c : instancias)
	{
		if (HBlockKind dkind = asHBlockKind(kvar->get_obj()))
		{
			if (is_derivadeOf(c->baseKind, dkind))
			{
				if (HBlockNoum noumSet = asHBlockNoum(kvar->get_definition()))
				{
					for (auto &va : c->anomimousSlots)
					{
						if (HVariableSlotEnum   venum = DynamicCasting::asHVariableSlotEnum(va))
						{
							if (venum->valueDefinition->contains(noumSet->named()))
							{
								if (venum->value->named() == "DEFAULT")
								{
									venum->value = noumSet;
								}
							}
						}
					}
				}
			}
		}

		if (HBlockProperty  dproperty = asHBlockProperty(kvar->get_obj())) {

			if (HBlockKind  dp_kind = asHBlockKind(dproperty->obj))
			{
				 
				if (is_derivadeOf(c->baseKind, dp_kind))
				{
					if (HBlockNoum   dp_propname = asHBlockNoum(dproperty->prop))
					{
						auto kproperty = c->get_property(dp_propname->named());
						if (kproperty != nullptr) 
							if (kproperty->value == nullptr)
							{
								c->set_property(dp_propname->named(), kvar->get_definition());
							}
					}
				}
			}
		}
	}

}

void CBlockInterpreter::add_namedVariableToAllinstances(HBlockKind_InstanceVariable kvar)
{
	for (auto &c : instancias)
	{
		if (is_derivadeOf(c, kvar->kind, nullptr))
		{
			HBlockInstanceVariable v = asHBlockInstanceVariable(kvar->variableNamed);
			HBlockKind nkindBase = resolve_kind(v->kind_name);
			c->newNamedVariable(v->property_name, nkindBase);
		}		 
	}
}


HBlockInstance CBlockInterpreter::new_Instance(string named, HBlockKind kind) {
    // nova instance e inicializa os fields

    HBlockInstanceNamed c = make_shared<CBlockInstanceNamed>(named, instancia_id, kind);

	instancia_id++;
	 
    // inicia os fields CAN_BE

    list<HBlockKind> kinds = getUpperKinds(kind);
   /* cout << "Up Kinds  " << endl;
    for (auto &k : kinds) {
        cout << " ," << k->named;

    }
    cout << endl;
    cout << " ----------------------------- " << endl;*/

    for (auto &k : kinds) 
	{
        for (auto &kvar : kind_variables ) 
		{
            if (HBlockKind dkind = asHBlockKind(kvar->get_obj())) 
			{
                if (dkind.get() == k.get()) 
				{
                    if (HBlockAssertion_canBe kvar_enum = asHBlockAssertion_canBe(kvar)) 
					{
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
	for (auto &k : kinds) 
	{
		for (auto &kvar : kind_named_variables) {
			if (kvar->kind.get() == k.get())
			{
				HBlockInstanceVariable v = asHBlockInstanceVariable(kvar->variableNamed);
				HBlockKind nkindBase = resolve_kind(v->kind_name);
				c->newNamedVariable(v->property_name, nkindBase);
			}
			 
		}
	}


    // assign the defaults of kinds

	for (auto &k : kinds) 
	{
		for (auto &kvar : default_assignments) {
			if (HBlockKind dkind = asHBlockKind(kvar->get_obj())) {

				if (dkind.get() == k.get()) 
				{
					if (HBlockNoum noumSet = asHBlockNoum(kvar->get_definition())) {
						c->set(noumSet);
					}
				}
			}
			if (HBlockProperty  dproperty = asHBlockProperty(kvar->get_obj())) {

				if (HBlockKind  dp_kind = asHBlockKind(dproperty->obj))
				{
					if (dp_kind.get() == k.get())
					{
						if (HBlockNoum   dp_propname = asHBlockNoum(dproperty->prop ))
						{
							c->set_property(dp_propname->named(), kvar->get_definition());
						}
					}
				}
			}
		}
	}

	 



	 

    return c;


}


void CBlockInterpreter::assign_variable_to_instance(HBlockAssertionBase kvar) {
    if (HBlockInstance c = asHBlockInstance(kvar->get_obj())) {
        {
            if (HBlockAssertion_canBe kvar_enum = asHBlockAssertion_canBe(kvar)) {
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