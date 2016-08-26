#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;


bool CBlockInterpreter::assert_it_variableGlobal(HBlock obj, HBlock baseKind)
{
	if (HBlockNoum  kindname = dynamic_pointer_cast<CBlockNoum>(baseKind))
	{
		HBlockKind kindr = resolve_kind(kindname->named);
		if (kindr != nullptr) 
		{
			return assert_it_variableGlobal(obj, kindr);
		}
	}

	
	if (HBlockProperty  ComposeKind = dynamic_pointer_cast<CBlockProperty>(baseKind))
	{
		if (HBlockNoum  KTemplate = dynamic_pointer_cast<CBlockNoum>(ComposeKind->prop))
			if (HBlockNoum  KTemplateItem = dynamic_pointer_cast<CBlockNoum>(ComposeKind->obj))
			{
				if (KTemplate->named == "list")
				{
					HBlockKind itemKind = resolve_kind(KTemplateItem->named);
					if (itemKind != nullptr)
					{
						HBlockListOfKind kindr = make_shared<CBlockListOfKind>(itemKind);
						return assert_it_variableGlobal(obj, kindr);
					}
					else
					{
						cout << "Whats is " << KTemplateItem->named << std::endl;
					}
				}
			}
	}
	 
	
	if (HBlockKind  kind = dynamic_pointer_cast<CBlockKind>(baseKind))
	{
		if (HBlockNoum nameVar = dynamic_pointer_cast<CBlockNoum>(obj)) {
			HVariableNamed newVar = make_shared<CVariableNamed>(nameVar, kind, nullptr);

			cout << "Add VAR " << newVar->name->named <<endl;
		 
			global_variables.push_back(newVar);
			return true;
		}
		else if (HBlockProperty nameProperty = dynamic_pointer_cast<CBlockProperty>(obj)) 
		{
			return assert_it_variableGlobal(   make_shared<CBlockNoum>(HtoString(nameProperty)) ,kind) ;
		}
		else
		{
			cout << "Whats is ";
			obj->dump("      ");
		}
	}

	return false;
}