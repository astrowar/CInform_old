#include "CBlockInterpreterRuntime.h"
#include <iostream>
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

	std::list<HBlockKind> kinds = getUpperKinds(kind);
	for(auto &k : kinds)
	{
		if (kind_has_property_called( k, propertyNamed))
		{
			return true;
		}
	}

	return false;
}

	





bool CBlockInterpreter::assert_property_defaultValue(HBlockProperty prop, HBlock value)
{
	if (HBlockNoum prop_obj_noum = dynamic_pointer_cast<CBlockNoum>(prop->obj))
	{
		HBlock nobj = resolve_noum(prop_obj_noum);
		
		return assert_property_defaultValue(  make_shared<CBlockProperty>(prop->prop, nobj  )   , value);

	}
	if (HBlockInstance prop_obj_inst = dynamic_pointer_cast<CBlockInstance>(prop->obj))
	{
		throw "cant assign Ususally to Instances";
		return false;
	}

	if (HBlockKind prop_obj_kind = dynamic_pointer_cast<CBlockKind>(prop->obj))
	{
		if (HBlockNoum prop_name_noum = dynamic_pointer_cast<CBlockNoum>(prop->prop))
		{		
			if (kind_has_property_called(prop_obj_kind, prop_name_noum->named))
			{
				default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(prop, value));
				return true;
			}
			else
			{
				std::cout << "Kind " << prop_obj_kind->named << " Dont have a property called " << prop_name_noum->named << endl;
			}
		}
	}

	return false;
}
bool CBlockInterpreter::assert_it_defaultValue(HBlock obj, HBlock value) {
    //default value so eh valudi para Kinds
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_defaultValue(nobj, value);
        }
        return false;
    } else if (HBlockInstance ibase = dynamic_pointer_cast<CBlockInstance>(obj)) {
        throw "cant assign Ususally to Instances";
    } else if (HBlockProperty pbase = dynamic_pointer_cast<CBlockProperty>(obj)) {

		return assert_property_defaultValue(pbase, value);


    } else if (HBlockKind kbase = dynamic_pointer_cast<CBlockKind>(obj)) {
        if (HBlockNoum nvalue = dynamic_pointer_cast<CBlockNoum>(value)) {
            std::cout << kbase->named << "  " << nvalue->named << std::endl;
            //default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, nvalue));
        }

        default_assignments.push_back(make_shared<CBlockAssertion_isDefaultAssign>(kbase, value));
    }

    return false;
}
