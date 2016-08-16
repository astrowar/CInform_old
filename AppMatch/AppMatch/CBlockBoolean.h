#pragma once
#include "BlockInterpreter.h"

class CBlockBooleanAND : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanAND(CBlock* input_a, CBlock* input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	CBlock* input_A;
	CBlock* input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanOR : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanOR(CBlock* input_a, CBlock* input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	CBlock* input_A;
	CBlock* input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanNOT : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanNOT(CBlock* input_a )
		: input_A(input_a) {}

	CBlock* input_A;

	void dump(std::string ident) override;
};






