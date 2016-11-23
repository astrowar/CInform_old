//
// Created by Eraldo Rangel on 19/08/16.
//

#ifndef APPMATCH_BLOCKINSTANCE_H
#define APPMATCH_BLOCKINSTANCE_H

#include "BlockInterpreter.hpp"
#include <string>
#include "CBlockNamedVariable.hpp"

class CBlockInstance : public CBlock //retorna um valor generico
{
public:
    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockInstance; }

    CBlockInstance(string _named, int id, HBlockKind base);

    void newEnumVariableSlot(HBlockEnums definition);

    void newBoolVariableSlot(HBlockNoum value);

    void newNamedVariable(HBlockNoum called, HBlockKind kind);

    void set(HBlockNoum c_block);

    void unset(HBlockNoum c_block);

    bool has_slot(HBlockNoum value);

    HVariableNamed get_property(string named);

    void set_property(string cs, HBlock value);

    QueryResul is_set(HBlockNoum value);

    string named; // nome public
	int id;  // id unico para cada instancia .. serve para saber se estamos a falar da mesma instancia
    HBlockKind baseKind;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

    std::vector<HVariableSlot> anomimousSlots;
    std::vector<HVariableNamed> namedSlots;

};

using HBlockInstance = std::shared_ptr<CBlockInstance>;








//Values Instances .. Text , Number , DateTime 




class CBlockText : public CBlock //retorna um valor generico
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockText; }
	std::string contents;
	CBlockText(std::string _contents   )  :  contents(_contents) {}
};
using HBlockText = std::shared_ptr<CBlockText>;





#endif //APPMATCH_BLOCKINSTANCE_H
