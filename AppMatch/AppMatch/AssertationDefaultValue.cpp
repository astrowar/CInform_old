#include "CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"
 
using namespace std;





bool CBlockInterpreter::kind_has_property_called(HBlockKind kind, string propertyNamed)
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

	list<HBlockKind> kinds = getUpperKinds(kind);
	for(auto &k : kinds)
	{
		if (kind_has_property_called( k, propertyNamed))
		{
			return true;
		}
	}

	return false;
}

	





bool CBlockInterpreter::assert_property_defaultValue(HBlockProperty prop, HBlock value,  HRunLocalScope localsEntry)
{
	if (HBlockNoum prop_obj_noum = asHBlockNoum(prop->obj))
	{
		HBlock nobj = resolve_noum(prop_obj_noum,localsEntry);
		
		return assert_property_defaultValue(  make_shared<CBlockProperty>(prop->prop, nobj  )   , value,localsEntry);

	}
	if (HBlockInstance prop_obj_inst = asHBlockInstance(prop->obj))
	{
		throw "cant assign Ususally to Instances";
		return false;
	}

	if (HBlockKind prop_obj_kind = asHBlockKind(prop->obj))
	{
		if (HBlockNoum prop_name_noum = asHBlockNoum(prop->prop))
		{		
			if (kind_has_property_called(prop_obj_kind, prop_name_noum->named))
			{
				default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(prop, value));
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
bool CBlockInterpreter::assert_it_defaultValue(HBlock obj, HBlock value, HRunLocalScope localsEntry) {
    //default value so eh valudi para Kinds
    if (HBlockNoum nbase = asHBlockNoum(obj)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_defaultValue(nobj, value,localsEntry);
        }
        return false;
    } else if (HBlockInstance ibase = asHBlockInstance(obj)) {
        throw "cant assign Ususally to Instances";
    } else if (HBlockProperty pbase = asHBlockProperty(obj)) {

		return assert_property_defaultValue(pbase, value,localsEntry);


    } else if (HBlockKind kbase = asHBlockKind(obj)) {
        if (HBlockNoum nvalue = asHBlockNoum(value)) {
             
			logMessage(kbase->named + "  " + nvalue->named);
            //default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, nvalue));
        }

        default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, value));
    }

    return false;
}
