
 
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;

HVariableSlotEnum asHVariableSlotEnum(HVariableSlot c )
{
    if (c != nullptr && c->type() == VarSlotType ::EnumSlot)
        return std::static_pointer_cast<CVariableSlotEnum>(c);
    return nullptr;
}

HVariableSlotBool asHVariableSlotBool(HVariableSlot c )
{
    if (c != nullptr && c->type() == VarSlotType ::BoolSlot)
        return std::static_pointer_cast<CVariableSlotBool>(c);
    return nullptr;
}

 


void CBlockInterpreter::dump_instance(string str )
{
	return dump_instance(str, nullptr);
}

void CBlockInterpreter::dump_instance(string str,   HRunLocalScope localsEntry) {
    HBlock n = resolve_string(str,localsEntry);
    if (HBlockInstance nn = asHBlockInstance(n)) {
        for (auto &va : nn->anomimousSlots) {
            
            if (HVariableSlotEnum venum = asHVariableSlotEnum(va)) {

                venum->valueDefinition->dump("    ");
                venum->value->dump("    ");

            }
            if (HVariableSlotBool vbool = asHVariableSlotBool(va)) {

                vbool->valueDefinition->dump("    ");
                printf("%i ", vbool->value );
            }
        }

    }
}

void CBlockInterpreter::add_defaultValueVariableToAllinstances(HBlockAssertion_isDefaultAssign kvar)
{
	
	for (auto &c : instancias)
	{
		if (HBlockKind dkind = asHBlockKind(kvar->get_obj())) {

			if(is_derivadeOf(c->baseKind , dkind ) )
			{
				if (HBlockNoum noumSet = asHBlockNoum(kvar->get_definition())) 
				{					 
					//c->set(noumSet);
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
						auto kproperty = c->get_property(dp_propname->named);
						if (kproperty != nullptr) 
							if (kproperty->value == nullptr)
							{

								c->set_property(dp_propname->named, kvar->get_definition());
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
			HBlockKind nkindBase = resolve_kind(v->kind_name->named);
			c->newNamedVariable(v->property_name, nkindBase);
		}		 
	}
}


HBlockInstance CBlockInterpreter::new_Instance(string named, HBlockKind kind) {
    // nova instance e inicializa os fields

    HBlockInstance c = make_shared<CBlockInstance>(named, kind);
	 
    // inicia os fields CAN_BE

    list<HBlockKind> kinds = getUpperKinds(kind);
   /* cout << "Up Kinds  " << endl;
    for (auto &k : kinds) {
        cout << " ," << k->named;

    }
    cout << endl;
    cout << " ----------------------------- " << endl;*/
    for (auto &k : kinds) {
        for (auto &kvar : kind_variables) {
            if (HBlockKind dkind = asHBlockKind(kvar->get_obj())) {
                if (dkind->named == k->named) {
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
    }

	//named variables
	for (auto &k : kinds) 
	{
		for (auto &kvar : kind_named_variables) {
			if (kvar->kind->named == k->named)
			{
				HBlockInstanceVariable v = asHBlockInstanceVariable(kvar->variableNamed);
				HBlockKind nkindBase = resolve_kind(v->kind_name->named);
				c->newNamedVariable(v->property_name, nkindBase);
			}
			 
		}
	}


    // assign the defaults of kinds

	for (auto &k : kinds) 
	{
		for (auto &kvar : default_assignments) {
			if (HBlockKind dkind = asHBlockKind(kvar->get_obj())) {

				if (dkind->named == k->named) {
					if (HBlockNoum noumSet = asHBlockNoum(kvar->get_definition())) {
						c->set(noumSet);
					}
				}
			}
			if (HBlockProperty  dproperty = asHBlockProperty(kvar->get_obj())) {

				if (HBlockKind  dp_kind = asHBlockKind(dproperty->obj))
				{
					if (dp_kind->named == k->named)
					{
						if (HBlockNoum   dp_propname = asHBlockNoum(dproperty->prop ))
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