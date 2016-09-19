#pragma once
#ifndef APPMATCH_BLOCKACTION_H
#define APPMATCH_BLOCKACTION_H


#include "BlockInterpreter.h"
#include "CBlockNamedVariable.h"
#include <string>


class CBlockAction : public CBlock  // um bloco que representa uma atividade
{
public:
    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAction; }

    CBlockAction(string _named)

            : named(_named) {
    }

	void newNamedVariable(HBlockNoum called, HBlockKind kind);

	HVariableNamed get_property(string pnamed);

	void set_property(string pnamed, HBlock value);

	string named;
	std::vector<HVariableNamed> namedSlots;
};
using HBlockAction = std::shared_ptr<CBlockAction>;


class CBlockActionCall : public CBlock {
public :
    HBlockAction action;
    HBlock noum1;
    HBlock noum2;

    CBlockActionCall(HBlockAction _action, HBlock _noum1, HBlock _noum2) : action(_action), noum1(_noum1),
                                                                           noum2(_noum2) {}

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockActionCall; }
};

using HBlockActionCall = std::shared_ptr<CBlockActionCall>;






class CBlockStaticDispatch : public CBlockAction {
public:
    int staticEntryTable;
    HBlock noum1;
    HBlock noum2;

    CBlockStaticDispatch(int _staticEntryTable, HBlock _noum1, HBlock _noum2) : 
		CBlockAction(  ("static " + std::to_string(_staticEntryTable))),

            staticEntryTable(_staticEntryTable),
		    noum1(_noum1), noum2(_noum2) {}

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockStaticDispatch; }

 
};

using HBlockStaticDispatch = std::shared_ptr<CBlockStaticDispatch>;







#endif
