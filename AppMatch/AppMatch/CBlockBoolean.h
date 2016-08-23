#pragma once
#include "BlockInterpreter.h"

class CBlockBooleanAND : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanAND(HBlock input_a, HBlock input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	HBlock input_A;
	HBlock input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanOR : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanOR(HBlock input_a, HBlock input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	HBlock input_A;
	HBlock input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanNOT : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanNOT(HBlock input_a )
		: input_A(input_a) {}

	HBlock input_A;

	void dump(std::string ident) override;
};






