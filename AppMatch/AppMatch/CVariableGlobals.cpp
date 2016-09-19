#include "CBlockInterpreterRuntime.h"
#include <iostream>
#include "sharedCast.h"
using namespace std;


bool CBlockInterpreter::assert_it_variableGlobal(HBlock obj, HBlock baseKind)
{
	if (HBlockNoum  kindname = asHBlockNoum(baseKind))
	{
		HBlockKind kindr = resolve_kind(kindname->named);
		if (kindr != nullptr) 
		{
			return assert_it_variableGlobal(obj, kindr);
		}
	}

	
	if (HBlockProperty  ComposeKind = asHBlockProperty(baseKind))
	{
		if (HBlockNoum  KTemplate = asHBlockNoum(ComposeKind->prop))
			if (HBlockNoum  KTemplateItem = asHBlockNoum(ComposeKind->obj))
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
	 
	
	if (HBlockKind  kind = asHBlockKind(baseKind))
	{
		if (HBlockNoum nameVar = asHBlockNoum(obj)) {
			HVariableNamed newVar = make_shared<CVariableNamed>(nameVar, kind, nullptr);

			cout << "Add VAR " << newVar->name->named <<endl;
		 
			global_variables.push_back(newVar);
			return true;
		}
		else if (HBlockProperty nameProperty = asHBlockProperty(obj))
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