//
// Created by Eraldo Rangel on 19/08/16.
//

#ifndef APPMATCH_BLOCKINSTANCE_H
#define APPMATCH_BLOCKINSTANCE_H

#include "BlockInterpreter.h"
#include <string>


class CVariableSlot
{
public:
	virtual ~CVariableSlot()
	{
	}
};

using HVariableSlot = std::shared_ptr<CVariableSlot>;

class CVariableSlotEnum : public CVariableSlot
{
public:
	HBlockNoum value;
	HBlockEnums valueDefinition;
	CVariableSlotEnum(HBlockEnums enums);
};

class CVariableSlotBool : public CVariableSlot
{
public:
	bool value;
	HBlockNoum valueDefinition;
	CVariableSlotBool(HBlockNoum valueDef);
};

class CVariableNamed
{
public:
	HBlock value;
	HBlockKind kind;
	HBlockNoum name;
	 CVariableNamed(HBlockNoum _name , HBlockKind _kind , HBlock _value );
};


using HVariableNamed = std::shared_ptr<CVariableNamed>;

class CBlockInstance : public CBlock //retorna um valor generico
{
public:
	virtual void dump( std::string ident) override;
	CBlockInstance(std::string _named , HBlockKind base );
	void newEnumVariableSlot(HBlockEnums definition);
	void newBoolVariableSlot(HBlockNoum value);
	void newNamedVariable(HBlockNoum called, HBlockKind kind);

	void set(HBlockNoum c_block);
	void unset(HBlockNoum c_block);
	bool has_slot(HBlockNoum value);
	HVariableNamed get_property(std::string named);
	void set_property(std::string cs, UBlock value);
	QueryResul is_set(HBlockNoum value);

	std::string named;
	HBlockKind baseKind;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

	std::vector<HVariableSlot> anomimousSlots;
	std::vector<HVariableNamed> namedSlots;

};

using HBlockInstance = std::shared_ptr<CBlockInstance>;


#endif //APPMATCH_BLOCKINSTANCE_H
