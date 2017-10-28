// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include <algorithm>

using namespace std;
using namespace CBlocking;
 
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;



bool CBlockInterpreter::kind_has_property_called_inner(HBlockKind kind, string propertyNamed , std::list<CBlockKind*> kindsUsed)
{
	for (auto &kvar : kind_named_variables)
	{
		if (kvar->kind.get() == kind.get())
		{
			if (kvar->variableNamed->property_name->named == propertyNamed)
			{
				return true;
			}

		}
	}
	kindsUsed.push_back(kind.get()  );

	list<HBlockKind> kinds = getUpperKinds(kind);
	for(auto &k : kinds)
	{
		if (std::find(kindsUsed.begin(), kindsUsed.end(), k.get() ) != kindsUsed.end()) continue;
		if (kind_has_property_called_inner( k, propertyNamed , kindsUsed))
		{
			return true;
		}
	}

	return false;
}

bool CBlockInterpreter::kind_has_property_called(HBlockKind kind, const string & propertyNamed )
{	
	return kind_has_property_called_inner(kind, propertyNamed, list<CBlockKind*>());
}


bool CBlockInterpreter::assert_property_ForbiddenValue(HBlockProperty prop, CBlocking::HBlock value, HRunLocalScope localsEntry)
{
	if (HBlockNoum prop_obj_noum = asHBlockNoum(prop->obj))
	{
		CBlocking::HBlock nobj = resolve_noum(prop_obj_noum, localsEntry);
		return assert_property_ForbiddenValue(make_shared<CBlockProperty>(prop->prop, nobj), value, localsEntry);
	}
	 

	if (HBlockKind prop_obj_kind = asHBlockKind(prop->obj))
	{
		if (HBlockNoum prop_name_noum = asHBlockNoum(prop->prop))
		{
			if (kind_has_property_called(prop_obj_kind, prop_name_noum->named))
			{
				auto kdef = make_shared<CBlockAssertion_isForbiddenAssign>(prop, value);
				//assignments.push_back(kdef);
				//add_defaultValueVariableToAllinstances(kdef);

				forbiden_assignments.push_back(kdef);
				add_forbidenValueVariableToAllinstances(kdef);

				return true;
			}
			else
			{
				//logError("Kind " + std::itos( uintptr_t(prop_obj_kind.get())) + " Dont have a property called " + prop_name_noum->named);
				logError("Kind  Dont have a property called " + prop_name_noum->named);
			}
		}
	}

	return false;
}


bool CBlockInterpreter::assert_property_ConstantValue(HBlockProperty prop, CBlocking::HBlock value, HRunLocalScope localsEntry)
{
	if (HBlockNoum prop_obj_noum = asHBlockNoum(prop->obj))
	{
		CBlocking::HBlock nobj = resolve_noum(prop_obj_noum, localsEntry);
		return assert_property_ConstantValue(make_shared<CBlockProperty>(prop->prop, nobj), value, localsEntry);
	}


	if (HBlockKind prop_obj_kind = asHBlockKind(prop->obj))
	{
		if (HBlockNoum prop_name_noum = asHBlockNoum(prop->prop))
		{
			if (kind_has_property_called(prop_obj_kind, prop_name_noum->named))
			{
				auto kdef = make_shared<CBlockAssertion_isConstantAssign>(prop, value); 
				constant_assignments.push_back(kdef);
				add_constantValueVariableToAllinstances(kdef); 
				return true;
			}
			else
			{
				logError("Kind   Dont have a property called " + prop_name_noum->named);
			}
		}
	}

	return false;
}




bool CBlockInterpreter::assert_property_defaultValue(HBlockProperty prop, CBlocking::HBlock value,  HRunLocalScope localsEntry)
{
	if (HBlockNoum prop_obj_noum = asHBlockNoum(prop->obj))
	{
		CBlocking::HBlock nobj = resolve_noum(prop_obj_noum,localsEntry);		
		return assert_property_defaultValue(  make_shared<CBlockProperty>(prop->prop, nobj  )   , value,localsEntry);
	}
	if (HBlockInstance prop_obj_inst = asHBlockInstance(prop->obj))
	{
		logError( "cant assign Ususally to Instances");
		return false;
	}

	if (HBlockKind prop_obj_kind = asHBlockKind(prop->obj))
	{
		if (HBlockNoum prop_name_noum = asHBlockNoum(prop->prop))
		{		
			if (kind_has_property_called(prop_obj_kind, prop_name_noum->named))
			{
				auto kdef = make_shared<CBlockAssertion_isDefaultAssign>(prop, value);
				default_assignments.push_back(kdef);
				add_defaultValueVariableToAllinstances(kdef);
				return true;
			}
			else
			{
				logError("Kind   Dont have a property called " + prop_name_noum->named);
			 
			}
		}
	}

	return false;
}


bool  CBlockInterpreter::assert_it_ConstantAssign(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry)
{
	obj->dump(" ");
	 
	if (HBlockNoum nbase = asHBlockNoum(obj))
	{
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) 
		{
			return assert_it_ConstantAssign(nobj, value, localsEntry);
		}
		//podemos definir esse noum como uma constante no codigo
		auto kdef = make_shared<CBlockAssertion_isConstantAssign>(nbase, value);
		constant_assignments.push_back(kdef);
		return true;
	}

	if (HBlockInstance ibase = asHBlockInstance(obj)) {
		auto kdef = make_shared<CBlockAssertion_isConstantAssign>(ibase, value);
		 
		constant_assignments.push_back(kdef);
		add_constantValueVariableToAllinstances(kdef);
		assert_assertation(ibase, value , localsEntry);

		return true;
	} 

	if (HBlockProperty pbase = asHBlockProperty(obj))
	{
		return assert_property_ConstantValue(pbase, value, localsEntry);
	}

	if (HVariableNamed vbase = asHVariableNamed(obj))
	{
		
		auto kdef = make_shared<CBlockAssertion_isConstantAssign>(vbase, value);
		constant_assignments.push_back(kdef); 
		vbase->value = value;
		return true;
	}

	if (HBlockKind kbase = asHBlockKind(obj))
	{ 
		auto kdef = make_shared<CBlockAssertion_isConstantAssign>(kbase, value);
		//kdef == nullptr;
		constant_assignments.push_back(kdef);
		add_constantValueVariableToAllinstances(kdef);
		return true;
	}

	return false;
}

//Forbiden value
bool CBlockInterpreter::assert_it_ForbiddenValue(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
	//default value so eh valudi para Kinds

	obj->dump(" ");
	if (HBlockNoum nbase = asHBlockNoum(obj)) 
	{
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) {
			return assert_it_ForbiddenValue(nobj, value, localsEntry);
		}
		return false;
	}

	if (HBlockInstance ibase = asHBlockInstance(obj)) {
		auto kdef = make_shared<CBlockAssertion_isForbiddenAssign>(ibase, value);
		//kdef == nullptr;
		forbiden_assignments.push_back(kdef);
		add_forbidenValueVariableToAllinstances(kdef);
		return true;
	}


	if (HBlockProperty pbase = asHBlockProperty(obj))
	{
		return assert_property_ForbiddenValue(pbase, value, localsEntry);
	}
	if (HBlockKind kbase = asHBlockKind(obj))
	{
		 
		auto kdef = make_shared<CBlockAssertion_isForbiddenAssign>(kbase, value);
		//kdef == nullptr;
		forbiden_assignments.push_back(kdef);
		add_forbidenValueVariableToAllinstances(kdef);
		return true;
	}

	return false;
}


bool CBlockInterpreter::assert_it_defaultValue(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
    //default value so eh valudi para Kinds
	 
	obj->dump(" ");
    if (HBlockNoum nbase = asHBlockNoum(obj)) {
        CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_defaultValue(nobj, value,localsEntry);
        }
        return false;
    } 
	
	if (HBlockInstance ibase = asHBlockInstance(obj)) {
        logError( "cant assign Ususally to Instances");
		return false;
    } 
	if (HBlockProperty pbase = asHBlockProperty(obj)) 
	{ 
		return assert_property_defaultValue(pbase, value,localsEntry); 
    } 
	if (HBlockKind kbase = asHBlockKind(obj)) 
	{
		if (HBlockNoum nvalue = asHBlockNoum(value)) 
		{
			//default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, nvalue));
		}
		auto kdef = make_shared<CBlockAssertion_isDefaultAssign>(kbase, value);
		//kdef == nullptr;
		default_assignments.push_back(kdef);
		add_defaultValueVariableToAllinstances(kdef);
		return true;
	}

    return false;
}
