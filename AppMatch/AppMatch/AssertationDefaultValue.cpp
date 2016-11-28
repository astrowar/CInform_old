
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp" 
using namespace std;
using namespace CBlocking;
 
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;



bool CBlockInterpreter::kind_has_property_called_inner(HBlockKind kind, string propertyNamed , list<string> kindsUsed)
{
	for (auto &kvar : kind_named_variables)
	{
		if (kvar->kind->named == kind->named)
		{
			if (kvar->variableNamed->property_name->named == propertyNamed)
			{
				return true;
			}

		}
	}
	kindsUsed.push_back(kind->named );

	list<HBlockKind> kinds = getUpperKinds(kind);
	for(auto &k : kinds)
	{
		if (std::find(kindsUsed.begin(), kindsUsed.end(), k->named) != kindsUsed.end()) continue;
		if (kind_has_property_called_inner( k, propertyNamed , kindsUsed))
		{
			return true;
		}
	}

	return false;
}

bool CBlockInterpreter::kind_has_property_called(HBlockKind kind, string propertyNamed )
{	
	return kind_has_property_called_inner(kind, propertyNamed, list<string>());
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
				logError("Kind " + prop_obj_kind->named + " Dont have a property called " + prop_name_noum->named);
			 
			}
		}
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
		if (HBlockNoum nvalue = asHBlockNoum(value)) {


			//default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, nvalue));
		}

		auto kdef = make_shared<CBlockAssertion_isDefaultAssign>(kbase, value);
		default_assignments.push_back(kdef);
		add_defaultValueVariableToAllinstances(kdef);
		return true;
	}

    return false;
}
