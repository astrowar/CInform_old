#include "CObjectDefinitions.h"
#include "CValueDefinitions.h"
#include "CRelations.h"


namespace VM
{

	std::string toString(CGenericValue* val);

	std::string toString(HGenericValue val);


	std::string toString(HValue val)
	{
		return toString(val.get());
	}


	std::string toString_val(CValue* val)
	{
		if (val == nullptr) return "NIL??";
		{
			CValueString* v = dynamic_cast<CValueString*>(val);
			if (v != nullptr) return v->_text;
		}
		{
			CValueText* txt = dynamic_cast<CValueText*>(val);
			if (txt != nullptr) return txt->_text;
		}
		{
			CValueList* lst = dynamic_cast<CValueList*>(val);
			if (lst != nullptr)
			{
				std::string s;
				for (auto it = lst->values.begin(); it != lst->values.end(); ++it)
				{
					//CValue* hit = (*it);
					s += toString(*it) + " ";
				}
				return s;
			}
		}
		{
			CValueBoolean* v = dynamic_cast<CValueBoolean*>(val);
			if (v != nullptr)
			{
				if (v->val)
				{
					return "true";
				}
				else
				{
					return "false";
				}
			}
		}
		{
			CValueNumber* v = dynamic_cast<CValueNumber*>(val);
			if (v != nullptr)
			{
				return std::to_string(v->value);
			}
		}


		return "ERROR";
	}

	std::string toString_inst(CObjectInstance* val)
	{
		return val->name;
	}

	std::string toString(CGenericValue* val)
	{
		{
			CValue* v = dynamic_cast<CValue*>(val);
			if (v != nullptr) return toString_val(v);
		}
		{
			CObjectInstance* h = dynamic_cast<CObjectInstance*>(val);
			if (h != nullptr) return toString_inst(h);
		}
		return "Nil";
	}

	std::string toString(HGenericValue val)
	{
		return toString(val.get());
	}

	std::string toString(CRelationInstance* val)
	{
		return toString(val->item1.get()) + "->" + val->relDesc->named + " ->" + toString(val->item2.get());
	}

}