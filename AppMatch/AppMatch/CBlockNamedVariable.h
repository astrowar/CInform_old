#pragma once
#ifndef APPMATCH_BLOCKNAMEDVAR_H
#define APPMATCH_BLOCKNAMEDVAR_H

#include "BlockInterpreter.h"
#include <string>


enum VarSlotType
{
	EnumSlot,
	BoolSlot
};

class CVariableSlot {
public:
    virtual ~CVariableSlot() {
    }
	virtual VarSlotType  type() = 0;
};

using HVariableSlot = std::shared_ptr<CVariableSlot>;

class CVariableSlotEnum : public CVariableSlot {
public:
    HBlockNoum value;
    HBlockEnums valueDefinition;

    CVariableSlotEnum(HBlockEnums enums);
	virtual VarSlotType  type() override  { return VarSlotType ::EnumSlot ; };
};

using HVariableSlotEnum = std::shared_ptr<CVariableSlotEnum>;

class CVariableSlotBool : public CVariableSlot {
public:
    bool value;
    HBlockNoum valueDefinition;

    CVariableSlotBool(HBlockNoum valueDef);
	virtual VarSlotType  type() override  { return VarSlotType ::BoolSlot ; };
};

using HVariableSlotBool = std::shared_ptr<CVariableSlotBool>;

class CVariableNamed :public CBlock {
public:
	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::VariableNamed; }
	HBlock value;
    HBlockKind kind;
    HBlockNoum name;

    CVariableNamed(HBlockNoum _name, HBlockKind _kind, HBlock _value);
};

using HVariableNamed = std::shared_ptr<CVariableNamed>;

#endif
