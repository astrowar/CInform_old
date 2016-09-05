//
// Created by Eraldo Rangel on 19/08/16.
//

#ifndef APPMATCH_BLOCKINSTANCE_H
#define APPMATCH_BLOCKINSTANCE_H

#include "BlockInterpreter.h"
#include <string>
#include "CBlockNamedVariable.h"

class CBlockInstance : public CBlock //retorna um valor generico
{
public:
    virtual void dump(string ident) override;

    CBlockInstance(string _named, HBlockKind base);

    void newEnumVariableSlot(HBlockEnums definition);

    void newBoolVariableSlot(HBlockNoum value);

    void newNamedVariable(HBlockNoum called, HBlockKind kind);

    void set(HBlockNoum c_block);

    void unset(HBlockNoum c_block);

    bool has_slot(HBlockNoum value);

    HVariableNamed get_property(string named);

    void set_property(string cs, HBlock value);

    QueryResul is_set(HBlockNoum value);

    string named;
    HBlockKind baseKind;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

    std::vector<HVariableSlot> anomimousSlots;
    std::vector<HVariableNamed> namedSlots;

};

using HBlockInstance = std::shared_ptr<CBlockInstance>;








//Values Instances .. Text , Number , DateTime 




class CBlockText : public CBlockInstance //retorna um valor generico
{
public:
	virtual void dump(string ident) override;
	std::string contents;
	CBlockText(std::string _contents) :CBlockInstance( "text", std::make_shared<CBlockKindValue>("text") ), contents(_contents) {}
};
using HBlockText = std::shared_ptr<CBlockText>;





#endif //APPMATCH_BLOCKINSTANCE_H
