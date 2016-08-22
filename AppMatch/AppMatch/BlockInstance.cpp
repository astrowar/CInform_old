//
// Created by Eraldo Rangel on 19/08/16.
//

#include "BlockInstance.h"
#include <iostream>
using  namespace  std   ;

CVariableSlotEnum::CVariableSlotEnum(CBlockEnums* enums)
{
	this->valueDefinition = enums;
	this->value = enums->values.front();
}

CVariableSlotBool::CVariableSlotBool(CBlockNoum* valueDef)
{
	this->valueDefinition = valueDef;
	this->value = true;
}

CVariableNamed::CVariableNamed(CBlockNoum* _name, CBlockKind* _kind, CBlock* _value): value(_value), kind(_kind), name(_name)
{
}

void CBlockInstance::dump(std::string ident)
{
	cout << ident << "Instance: " << named << endl;
}

CBlockInstance::CBlockInstance( std::string _named, CBlockKind *_baseKind) : named(_named), baseKind(_baseKind)
{
	//assert(_named[0] != '[');
}

void CBlockInstance::newEnumVariableSlot(CBlockEnums* definition  )
{
	this->anomimousSlots.push_back( new  CVariableSlotEnum(definition));

}

void CBlockInstance::newBoolVariableSlot(CBlockNoum * value)
{
	this->anomimousSlots.push_back(new CVariableSlotBool (value));
}

void CBlockInstance::newNamedVariable(CBlockNoum* called, CBlockKind* kind)
{
	this->namedSlots.push_back(new CVariableNamed(called, kind, nullptr));

}

void CBlockInstance::set(CBlockNoum* c_block)
{
	//Anonymous SET
	for(auto &va :	this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains( c_block->named ))
			{
				venum->value = c_block;
				return;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == c_block->named )
			{
				vbool->value = true;
				return;
			}
		}
	}
}

void CBlockInstance::unset(CBlockNoum* c_block)
{
	//Anonymous SET
	for (auto &va : this->anomimousSlots)
	{

		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == c_block->named)
			{
				vbool->value = false;
				return;
			}
		}
	}
}

bool CBlockInstance::has_slot(CBlockNoum* value)
{

	for (auto &va : this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				return true ;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == value->named)
			{
				return true ;
			}
		}
	}
	return false;
}

CVariableNamed* CBlockInstance::get_property( std::string  pnamed)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{
			cout << pnamed << " has? " << va->name->named << endl;
			return va;
		}
	}
	return nullptr;
}

void CBlockInstance::set_property(std::string  pnamed, UBlock value)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{
			cout << named << " has? " << va->name->named << endl;
			va->value = value;
		}
	}
	return;
}

QueryResul CBlockInstance::is_set(CBlockNoum * value)
{
	for (auto &va : this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				if (venum->value->named == value->named) return QEquals;
				return QNotEquals;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == value->named)
			{

				if (vbool->value) return QEquals;
				return QNotEquals;
			}
		}
	}
	return QUndefined;
}