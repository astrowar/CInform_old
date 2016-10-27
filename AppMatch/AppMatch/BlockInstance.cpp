//
// Created by Eraldo Rangel on 19/08/16.
//

#include "BlockInstance.hpp"
 
#include "sharedCast.hpp"

using  namespace  std   ;

CVariableSlotEnum::CVariableSlotEnum(HBlockEnums enums)
{
	this->valueDefinition = enums;
	this->value = enums->values.front();
}

CVariableSlotBool::CVariableSlotBool(HBlockNoum valueDef)
{
	this->valueDefinition = valueDef;
	this->value = true;
}

 

CVariableNamed::CVariableNamed(HBlockNoum _name, HBlockKind _kind, HBlock _value): value(_value), kind(_kind), name(_name)
{
}

 

CBlockInstance::CBlockInstance( string _named, HBlockKind _baseKind) : named(_named), baseKind(_baseKind)
{
	//assert(_named[0] != '[');
}

void CBlockInstance::newEnumVariableSlot(HBlockEnums definition  )
{
	this->anomimousSlots.push_back( make_shared<CVariableSlotEnum>(definition));

}

void CBlockInstance::newBoolVariableSlot(HBlockNoum value)
{
	this->anomimousSlots.push_back(make_shared< CVariableSlotBool> (value));
}

void CBlockInstance::newNamedVariable(HBlockNoum called, HBlockKind kind)
{
	this->namedSlots.push_back(make_shared< CVariableNamed>(called, kind, nullptr));
}


void CBlockInstance::set(HBlockNoum c_block)
{
	//Anonymous SET
	for(auto &va :	this->anomimousSlots)
	{
		if (HVariableSlotEnum   venum = asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains( c_block->named ))
			{
				venum->value = c_block;
				return;
			}
		}
		if (HVariableSlotBool   vbool = asHVariableSlotBool(va))
		{
			if (vbool->valueDefinition->named == c_block->named )
			{
				vbool->value = true;
				return;
			}
		}
	}
}

void CBlockInstance::unset(HBlockNoum c_block)
{
	//Anonymous SET
	for (auto &va : this->anomimousSlots)
	{

		if (HVariableSlotBool  vbool = asHVariableSlotBool(va))
		{
			if (vbool->valueDefinition->named == c_block->named)
			{
				vbool->value = false;
				return;
			}
		}
	}
}

bool CBlockInstance::has_slot(HBlockNoum value)
{

	for (auto &va : this->anomimousSlots)
	{
		if (HVariableSlotEnum   venum = asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				return true ;
			}
		}
		if (HVariableSlotBool   vbool = asHVariableSlotBool(va))
		{
			if (vbool->valueDefinition->named == value->named)
			{
				return true ;
			}
		}
	}
	return false;
}

HVariableNamed  CBlockInstance::get_property( string  pnamed)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{
			//logMessage(pnamed + " has? " + va->name->named);
			return va;
		}
	}
	return nullptr;
}

void CBlockInstance::set_property(string  pnamed, HBlock value)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{
			//logMessage(pnamed + " has? " + va->name->named);			 
			va->value = value;
		}
	}
	return;
}

QueryResul CBlockInstance::is_set(HBlockNoum  value)
{
	for (auto &va : this->anomimousSlots)
	{
		if (HVariableSlotEnum  venum = asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				if (venum->value->named == value->named) return QEquals;
				return QNotEquals;
			}
		}
		if (HVariableSlotBool   vbool = asHVariableSlotBool(va))
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







