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
 

bool CBlockInterpreter::assert_it_variableGlobal(HBlock obj, HBlock baseKind , HBlock defaultValue )
{
	if (HBlockKindNamed  kindname = asHBlockKindNamed(baseKind))
	{
		HBlockKind kindr = resolve_kind(kindname->named);
		if (kindr != nullptr)
		{
			return assert_it_variableGlobal(obj, kindr, defaultValue);
		}
		else
		{
			logMessage("Whats is ");
			kindname->dump("      ");
			return false;
		}
	}

	if (HBlockNoum  kindname = asHBlockNoum(baseKind))
	{
		HBlockKind kindr = resolve_kind(kindname->named());
		if (kindr != nullptr) 
		{
			return assert_it_variableGlobal(obj, kindr, defaultValue);
		}
		else
		{
			logMessage("Whats is ");
			kindname->dump("      ");
			return false;
		}
	}

	
	//if (HBlockProperty  ComposeKind = asHBlockProperty(baseKind))
	//{
	//	if (HBlockNoum  KTemplate = asHBlockNoum(ComposeKind->prop))
	//		if (HBlockNoum  KTemplateItem = asHBlockNoum(ComposeKind->obj))
	//		{
	//			if (KTemplate->named == "list")
	//			{
	//				HBlockKind itemKind = resolve_kind(KTemplateItem->named);
	//				if (itemKind != nullptr)
	//				{
	//					HBlockListOfKind kindr = make_shared<CBlockListOfKind>(itemKind);
	//					return assert_it_variableGlobal(obj, kindr);
	//				}
	//				else
	//				{
	//					logMessage("Whats is " + KTemplateItem->named);
	//				}
	//			}
	//		}
	//}
	 
	
	if (HBlockKind  kind = asHBlockKind(baseKind))
	{
		if (HBlockNoum nameVar = asHBlockNoum(obj)) {
			HBlockVariableNamed newVar = make_shared<CBlockVariableNamed>(nameVar, kind, defaultValue);

			logMessage("Add VAR " + newVar->name->named());
		 
			global_variables.push_back(newVar);
			addSymbol(newVar->name->named(), newVar);

			return true;
		}
		else if (HBlockProperty nameProperty = asHBlockProperty(obj))
		{
			return assert_it_variableGlobal(   make_shared<CBlockNoumStr>(HtoString(nameProperty)) ,kind, defaultValue) ;
		}
		else
		{
			logMessage("Whats is ");
			obj->dump("      ");
		}
	}


	return false;
}