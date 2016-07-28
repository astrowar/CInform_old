
#include "EqualsResult.h"
#include "CValueDefinitions.h"
#include "CRelations.h"
#include "CObjectDefinitions.h"
EqualsResul isEqual_val(CValue* c1, CValue* c2);
EqualsResul isEqual(CGenericValue* c1, CGenericValue* c2);

EqualsResul isEqual(CValueString* c1, CValueString* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueInstance * c1, CValueInstance* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->vkind->name != c2->vkind->name) return NotEquals;
	if (c1->named  == c2->named ) return Equals;
	return NotEquals;
}


EqualsResul isEqual(CValueBoolean* c1, CValueBoolean* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->val == c2->val) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CRelationInstance * c1, CRelationInstance* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if ((c1->relDesc->named == c2->relDesc->named))
	{
		if (isEqual(c1->item1.get(), c2->item1.get()) == Equals)
			if (isEqual(c1->item2.get(), c2->item2.get()) == Equals)
			{
				return Equals;
			}
	}
	return NotEquals;
}


EqualsResul isEqual(CValueText* c1, CValueText* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueList* c1, CValueList* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->values.size() != c2->values.size()) return NotEquals;
	if (c1->values.empty()) return Equals;
	auto it1 = c1->values.begin();
	auto it2 = c2->values.begin();
	while (it1 != c1->values.end())
	{
		EqualsResul q = isEqual((*it1).get(), (*it2).get());
		if (q != Equals) return NotEquals;
		++it1;
		++it2;
	}
	return Equals;
}
 

EqualsResul isEqual_val(CValue* c1, CValue* c2)
{
	if (c1 == c2) return Equals; //obvious
	EqualsResul q;
	{
		q = isEqual(dynamic_cast<CValueString*>(c1), dynamic_cast<CValueString*>(c2));
		if (q != Undefined) return q;
		q = isEqual(dynamic_cast<CValueText *>(c1), dynamic_cast<CValueText*>(c2));
		if (q != Undefined) return q;
		q = isEqual(dynamic_cast<CValueList*>(c1), dynamic_cast<CValueList*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueList*>(c1), dynamic_cast<CValueList*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueInstance*>(c1), dynamic_cast<CValueInstance*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueBoolean *>(c1), dynamic_cast<CValueBoolean*>(c2));
		if (q != Undefined) return q;

		 

		return Undefined;
	}
}

EqualsResul isEqual_inst(CObjectInstance * c1, CObjectInstance* c2)
{	
	if( c1->kind->name == c2->kind->name)
	{
		if (c1->name == c2->name) return Equals;
	}
	return NotEquals;
}


EqualsResul isEqual_valkind(CValueKind * c1, CValueKind* c2)
{
	 
 if (c1->name == c2->name) return Equals;
	 
	return NotEquals;
}

EqualsResul isEqual_instkind(CObjectKind * c1, CObjectKind * c2)
{
 if (c1->name == c2->name) return Equals;
	 
	return NotEquals;
}

EqualsResul isEqual(CGenericValue * c1, CGenericValue* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	{
		CValue * v1 = dynamic_cast<CValue*>(c1);
		if (v1 != nullptr)
		{
			CValue * v2 = dynamic_cast<CValue*>(c2);
			if (v2 != nullptr)
				return isEqual_val(v1, v2);
			return NotEquals;
		}
	}
	{
		CObjectInstance * h1 = dynamic_cast<CObjectInstance*>(c1);
		if (h1 != nullptr)
		{
			CObjectInstance * h2 = dynamic_cast<CObjectInstance*>(c2);
			if (h2 != nullptr)
				return isEqual_inst(h1, h2);
			return NotEquals;
		}
	} 
	return Undefined;
}


EqualsResul isEqual(CGenericKind * c1, CGenericKind* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	{
		CValueKind * v1 = dynamic_cast<CValueKind*>(c1);
		if (v1 != nullptr)
		{
			CValueKind * v2 = dynamic_cast<CValueKind*>(c2);
			if (v2 != nullptr)
				return isEqual_valkind(v1, v2);
			return NotEquals;
		}
	}
	{
		CObjectKind  * h1 = dynamic_cast<CObjectKind*>(c1);
		if (h1 != nullptr)
		{
			CObjectKind * h2 = dynamic_cast<CObjectKind*>(c2);
			if (h2 != nullptr)
				return isEqual_instkind(h1, h2);
			return NotEquals;
		}
	}
	return Undefined;
}


EqualsResul isEqual(HValue c1, HValue  c2)
{
	return isEqual(c1.get(), c2.get());
}