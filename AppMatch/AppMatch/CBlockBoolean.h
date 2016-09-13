#pragma once

#ifndef CBLOCKBOOLEAN_H
#define CBLOCKBOOLEAN_H

#include "BlockInterpreter.h"

class CBlockBooleanAND
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockBooleanAND(HBlock input_a, HBlock input_b)
            : input_A(input_a),
              input_B(input_b) {
    }

    HBlock input_A;
    HBlock input_B;

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockBooleanAND; }
};

class CBlockBooleanOR
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockBooleanOR(HBlock input_a, HBlock input_b)
            : input_A(input_a),
              input_B(input_b) {
    }

    HBlock input_A;
    HBlock input_B;

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockBooleanOR; }
};

class CBlockBooleanNOT
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockBooleanNOT(HBlock input_a)
            : input_A(input_a) {}

    HBlock input_A;

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockBooleanNOT; }
};






#endif