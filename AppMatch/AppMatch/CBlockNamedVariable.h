#pragma once
#ifndef APPMATCH_BLOCKNAMEDVAR_H
#define APPMATCH_BLOCKNAMEDVAR_H

#include "BlockInterpreter.h"
#include <string>

class CVariableSlot {
public:
    virtual ~CVariableSlot() {
    }
};

using HVariableSlot = std::shared_ptr<CVariableSlot>;

class CVariableSlotEnum : public CVariableSlot {
public:
    HBlockNoum value;
    HBlockEnums valueDefinition;

    CVariableSlotEnum(HBlockEnums enums);
};

using HVariableSlotEnum = std::shared_ptr<CVariableSlotEnum>;

class CVariableSlotBool : public CVariableSlot {
public:
    bool value;
    HBlockNoum valueDefinition;

    CVariableSlotBool(HBlockNoum valueDef);
};

using HVariableSlotBool = std::shared_ptr<CVariableSlotBool>;

class CVariableNamed :public CBlock {
public:
	void dump(string ident) override;
	HBlock value;
    HBlockKind kind;
    HBlockNoum name;

    CVariableNamed(HBlockNoum _name, HBlockKind _kind, HBlock _value);
};

using HVariableNamed = std::shared_ptr<CVariableNamed>;

#endif
