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

class CVariableSlotEnum : public CVariableSlot
{
public:
	CBlockNoum* value;
	CBlockEnums* valueDefinition;
	CVariableSlotEnum(CBlockEnums* enums);
};

class CVariableSlotBool : public CVariableSlot
{
public:
	bool value;
	CBlockNoum* valueDefinition;
	CVariableSlotBool(CBlockNoum* valueDef);
};

class CVariableNamed
{
public:
	CBlock* value;
	CBlockKind* kind;
	CBlockNoum* name;
	 CVariableNamed(CBlockNoum* _name , CBlockKind* _kind , CBlock* _value );
};

class CBlockInstance : public CBlock //retorna um valor generico
{
public:
	virtual void dump( std::string ident) override;
	CBlockInstance(std::string _named , CBlockKind *base );
	void newEnumVariableSlot(CBlockEnums* definition);
	void newBoolVariableSlot(CBlockNoum* value);
	void newNamedVariable(CBlockNoum* called, CBlockKind *kind);

	void set(CBlockNoum* c_block);
	void unset(CBlockNoum* c_block);
	bool has_slot(CBlockNoum* value);
	CVariableNamed* get_property(std::string named);
	void set_property(std::string cs, UBlock value);
	QueryResul is_set(CBlockNoum* value);

	std::string named;
	CBlockKind *baseKind;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

	std::vector<CVariableSlot*> anomimousSlots;
	std::vector<CVariableNamed*> namedSlots;

};



#endif //APPMATCH_BLOCKINSTANCE_H
