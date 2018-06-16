#pragma once

#ifndef CBLOCKBOOLEAN_H
#define CBLOCKBOOLEAN_H

#include "BlockInterpreter.hpp"

namespace CBlocking
{
	class CBlockBooleanValue  : public CBlockValue  // um bloco que especifica um valor Booleano
	{
	public:
		CBlockBooleanValue(bool _state) :state(_state) {}
		bool state;
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockBooleanValue; }
	};
	using HBlockBooleanValue = std::shared_ptr<CBlockBooleanValue>;


	class CBlockBooleanAND  : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
	{
	public:
		CBlockBooleanAND(CBlocking::HBlock input_A, CBlocking::HBlock input_B)
			: input_A(input_A),
			input_B(input_B) {
		}

		CBlocking::HBlock input_A;
		CBlocking::HBlock input_B;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockBooleanAND; }
	};
	using HBlockBooleanAND = std::shared_ptr<CBlockBooleanAND>;




	class CBlockBooleanOR 	: public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
	{
	public:
		CBlockBooleanOR(CBlocking::HBlock input_A, CBlocking::HBlock input_B)
			: input_A(input_A),
			input_B(input_B) {
		}

		CBlocking::HBlock input_A;
		CBlocking::HBlock input_B;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockBooleanOR; }
	};
	using HBlockBooleanOR = std::shared_ptr<CBlockBooleanOR>;




	class CBlockBooleanNOT : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
	{
	public:
		CBlockBooleanNOT(CBlocking::HBlock input_A)
			: input_A(input_A) {}

		CBlocking::HBlock input_A;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockBooleanNOT; }
	};
	using HBlockBooleanNOT = std::shared_ptr<CBlockBooleanNOT>;

}



#endif