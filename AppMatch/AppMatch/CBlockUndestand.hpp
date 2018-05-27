#pragma once
#ifndef CBLOCKUNDESTAND_H
#define CBLOCKUNDESTAND_H


#include "BlockInterpreter.hpp"
 
#include "CBlockMatch.hpp"
namespace CBlocking
{
	class CBlockUnderstand : public CBlock    //retorna uma declaracao
	{
	public:
		virtual void dump(string ident) override;

		HBlockMatch input_n; // Pode ser simples ou com a preposicao
		CBlocking::HBlock output_n;

		CBlockUnderstand(HBlockMatch _input_n, CBlocking::HBlock _output_n) : input_n(_input_n), output_n((_output_n)) {};
		 
	};
	using HBlockUnderstand = std::shared_ptr<CBlockUnderstand>;




	class CBlockUnderstandStatic : public CBlock    //retorna uma declaracao
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockUnderstandStatic; }

		HBlockMatchList argument_match; // Pode ser simples ou com a preposicao
		CBlocking::HBlock output_n;
		int entryID;
		CBlockUnderstandStatic(int _entryID, HBlockMatchList _argument_match, CBlocking::HBlock _output_n) : argument_match(_argument_match),
			output_n((_output_n)), entryID(_entryID)
		{};
		 
	};

	using HBlockUnderstandStatic = std::shared_ptr<CBlockUnderstandStatic>;







	class CBlockUnderstandDynamic : public CBlock    //retorna uma declaracao
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockUnderstandDynamic; }

		HBlockMatch input_n; // Pode ser simples ou com a preposicao
		HBlockMatchList argument_n;
		CBlocking::HBlock output_n;
		CBlockUnderstandDynamic(HBlockMatch _input_n, HBlockMatchList _argumentMatchs, CBlocking::HBlock _output_n) : input_n(_input_n), argument_n(_argumentMatchs), output_n(_output_n) {};
	};

	using HBlockUnderstandDynamic = std::shared_ptr<CBlockUnderstandDynamic>;

}

#endif