// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Eraldo Rangel on 19/08/16.
//

#include "BlockInstance.hpp"
 
#include "sharedCast.hpp"
#include "BlockInterpreter.hpp"

using  namespace  std   ;
using namespace CBlocking;


CVariableSlotEnum::CVariableSlotEnum(HBlockEnums enums)
{
	this->valueDefinition = enums;
	this->value = enums->values.front();
}

CVariableSlotBool::CVariableSlotBool(CBlocking::HBlockNoum valueDef)
{
	this->valueDefinition = valueDef;
	this->value = true;
}

 

CVariableNamed::CVariableNamed(CBlocking::HBlockNoum _name, HBlockKind _kind, CBlocking::HBlock _value): value(_value), kind(_kind), name(_name)
{
}

 

 

CBlockInstance::CBlockInstance(string _named, int _id, HBlockKind _baseKind) : named(_named), id(_id), baseKind(_baseKind)
{
}

void CBlockInstance::newEnumVariableSlot(HBlockEnums definition  )
{
	this->anomimousSlots.push_back( make_shared<CVariableSlotEnum>(definition));

}

void CBlockInstance::newBoolVariableSlot(CBlocking::HBlockNoum value)
{
	this->anomimousSlots.push_back(make_shared< CVariableSlotBool> (value));
}

void CBlockInstance::newNamedVariable(HBlockNoum called, HBlockKind kind)
{
	//verifica se ja nao existe algo assim
	for(auto s : this->namedSlots)
	{
		if (s->name->named == called->named) return; //ja tem um slot com esse nome 
	}
	this->namedSlots.push_back(make_shared< CVariableNamed>(called, kind, nullptr));
}


void CBlockInstance::set(HBlockNoum c_block)
{
	//Anonymous SET
	for(auto &va :	this->anomimousSlots)
	{
		if (HVariableSlotEnum   venum = DynamicCasting::asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains( c_block->named ))
			{
				venum->value = c_block;
				return;
			}
		}
		if (HVariableSlotBool   vbool = DynamicCasting::asHVariableSlotBool(va))
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

		if (HVariableSlotBool  vbool = DynamicCasting::asHVariableSlotBool(va))
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
		if (HVariableSlotEnum   venum = DynamicCasting::asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				return true ;
			}
		}
		if (HVariableSlotBool   vbool = DynamicCasting::asHVariableSlotBool(va))
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

void CBlockInstance::set_property(string  pnamed, CBlocking::HBlock value)
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
		if (HVariableSlotEnum  venum = DynamicCasting::asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				if (venum->value->named == value->named) return QEquals;
				return QNotEquals;
			}
		}
		if (HVariableSlotBool   vbool = DynamicCasting::asHVariableSlotBool(va))
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







