#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;


CBlockInstance* CBlockInterpreter::new_Instance( std::string named, CBlockKind* kind)
{	
	// nova instance e inicializa os fields

	CBlockInstance* c = new CBlockInstance(named);

	// inicia os fields CAN_BE

	std::list<CBlockKind*> kinds = getUpperKinds(kind);
	for (auto &k : kinds)
	{
		std::cout << "Kind  " << k->named << std::endl;

	}
	std::cout << " ----------------------------- " << std::endl;
	for(auto &k : kinds)
	{
		for (auto& kvar : kind_variables )
		{
			if (CBlockKind * dkind = dynamic_cast<CBlockKind*>(kvar->get_obj()))
			{
				if (dkind->named == k->named)
				{
					if (CBlockAssertion_canBe * kvar_enum = dynamic_cast<CBlockAssertion_canBe*>(kvar))
					{
						if (kvar_enum->definition->values.size() > 1)
						{
							c->newEnumVariableSlot(kvar_enum->definition);
						}
						if (kvar_enum->definition->values.size() == 1)
						{
							c->newBoolVariableSlot(kvar_enum->definition->values.front());
						}
					}
				}
			}
		}
	}

	// assign the defaults of kinds

	for (auto &k : kinds)
	{ 
		for (auto& kvar : default_assignments )
		{
			if (CBlockKind * dkind = dynamic_cast<CBlockKind*>(kvar->get_obj()))
			{
				 
				if (dkind->named == k->named)
				{
					if (CBlockNoum* noumSet = dynamic_cast<CBlockNoum*>(kvar->get_definition()))
					{
						c->set(noumSet);
					}
				}
			}
		}
	}

	 
	return c;



}



void CBlockInterpreter::assign_variable_to_instance(CBlockAssertionBase *kvar)
{
	if (CBlockInstance  * c = dynamic_cast<CBlockInstance*>(kvar->get_obj()))
	{		 
		{
			if (CBlockAssertion_canBe * kvar_enum = dynamic_cast<CBlockAssertion_canBe*>(kvar))
			{
				if (kvar_enum->definition->values.size() > 1)
				{
					c->newEnumVariableSlot(kvar_enum->definition);
				}
				if (kvar_enum->definition->values.size() == 1)
				{
					c->newBoolVariableSlot(kvar_enum->definition->values.front());
				}
			}
		}
	}
}