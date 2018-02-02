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
using namespace VariableSloting;
 

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
	if (_kind == nullptr)
	{
		logError("variable named must have a type");
	}
}

 

 

CBlockInstance::CBlockInstance(  int _id, HBlockKind _baseKind) :  id(_id), baseKind(_baseKind)
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
				printf("unset !");
				this->dump(""); 
				return;
			}
		}

		if (HVariableSlotEnum  vEnn = DynamicCasting::asHVariableSlotEnum(va))
		{
			if (vEnn->valueDefinition->contains(c_block->named))
			{
				if (vEnn->valueDefinition->values.size() == 2)
				{
					if (vEnn->valueDefinition->values[0]->named == c_block->named)
					{
						vEnn->value = vEnn->valueDefinition->values[1];
					}
					else
					{
						vEnn->value = vEnn->valueDefinition->values[0];
					}
				}
				else
				{
					logError("Value Slot is not a binary Set \n");
					return;
				}

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
			if (va->value == nullptr)
			{
				//retorna o valor como nothing ...
				return std::make_shared< CVariableNamed>(va->name, va->kind, std::make_shared<CBlockNothing>("nothing"));
				//return va;
			}
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


bool NNisSameString(const string &s1, const string &s2)
{
	if (s1 == s2) return true;
	if ((s1.size() == s2.size()) && (tolower(s1[0]) == tolower(s2[0])))
	{
		int n = s1.size();
		for (int j = 0; j< n; ++j)
		{
			if (tolower(s1[j]) != tolower(s2[j])) return false;
		}
		return true;
	}
	return false;
}


 

bool CBlockInstance::is_set(HBlockNoum  valueName, bool &value)
{
	 
	for (auto &va : this->anomimousSlots)
	{
		if (HVariableSlotEnum  venum = DynamicCasting::asHVariableSlotEnum(va))
		{
			if (venum->valueDefinition->contains(valueName->named))
			{
				if (NNisSameString(venum->value->named, valueName->named))
				{
					value = true;
					return true;
				}
				value = false;
				return true;
			}
		}
		if (const HVariableSlotBool   vbool = DynamicCasting::asHVariableSlotBool(va))
		{
			if (vbool->valueDefinition->named == valueName->named)
			{
				if (vbool->value == true)
				{
					value = true;
					return true;
				}
				value = false;
				return true;
			}
		}
	}
	return false; //nao ha esse valor
}







