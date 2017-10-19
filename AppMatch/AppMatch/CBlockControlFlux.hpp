#pragma once
 

#ifndef CBLOCKCONTROLFLUX_H
#define CBLOCKCONTROLFLUX_H

#include "BlockInterpreter.hpp"


namespace CBlocking
{
	class CBlockControlToken //classe que diz que aqui tem um TOKEN especifico de controle
		: public CBlock
	{
	public:
		CBlockControlToken(string _token, CBlocking::HBlock _contents)
			: token(_token), contents(_contents) {}

		string token;
		CBlocking::HBlock contents;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlToken; }
	};
	using HBlockControlToken = std::shared_ptr<CBlockControlToken>;


	class CBlockControlIF
		: public CBlock
	{
	public:
		CBlockControlIF(CBlocking::HBlock _block_if, CBlocking::HBlock _block_then, CBlocking::HBlock _block_else)
			: block_if(_block_if), block_then(_block_then), block_else(_block_else) {}

		CBlocking::HBlock block_if;
		CBlocking::HBlock block_then;
		CBlocking::HBlock block_else;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlIF; }
	};

	using HBlockControlIF = std::shared_ptr<CBlockControlIF>;



	class CBlockControlUnless
		: public CBlock
	{
	public:
		CBlockControlUnless(CBlocking::HBlock _block_if, CBlocking::HBlock _block_then, CBlocking::HBlock _block_else)
			: block_if(_block_if), block_then(_block_then), block_else(_block_else) {}

		CBlocking::HBlock block_if;
		CBlocking::HBlock block_then;
		CBlocking::HBlock block_else;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlIF; }
	};

	using HBlockControlUnless = std::shared_ptr<CBlockControlUnless>;



	class CBlockControlSelectItem
		: public CBlock
	{
	public:
		CBlockControlSelectItem(CBlocking::HBlock _block_seletor, CBlocking::HBlock _block_execute)
			: block_seletor(_block_seletor), block_execute(_block_execute) {} 
		CBlocking::HBlock block_seletor;
		CBlocking::HBlock block_execute; 
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlSelectItem; }
	};
	using HBlockControlSelectItem = std::shared_ptr<CBlockControlSelectItem>;




	class CBlockControlSelect
		: public CBlock
	{
	public:
		CBlockControlSelect(CBlocking::HBlock _block_seletor, std::list<HBlockControlSelectItem> _block_selectList, CBlocking::HBlock _block_else)
			: block_seletor(_block_seletor), block_selectList(_block_selectList), block_else(_block_else) {}

		CBlocking::HBlock block_seletor;
		std::list<HBlockControlSelectItem> block_selectList;
		CBlocking::HBlock block_else;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlSelect; }
	};
	using HBlockControlSelect = std::shared_ptr<CBlockControlSelect>;



	// For Loop 


 

class CBlockControlForEach
		: public CBlock
	{
	public:
		CBlockControlForEach(CBlocking::HBlock _block_variable, CBlocking::HBlock _block_body )
			: block_variable(_block_variable), block_body(_block_body)  {}

		CBlocking::HBlock block_variable;
		CBlocking::HBlock block_body;
		 

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockControlForEach; }
	};

	using HBlockControlForEach = std::shared_ptr<CBlockControlForEach>;





	//=================== Stop continue action

	enum PhaseResultFlag {
		actionContinue,
		actionStop,
		ruleSucess,
		ruleFail

	};

	class CBlockExecutionResultFlag //classe que diz que aqui tem um TOKEN especifico de controle
		: public CBlock
	{
	public:
		CBlockExecutionResultFlag(PhaseResultFlag _flag, CBlocking::HBlock _contents)
			: flag(_flag), contents(_contents) {}

		PhaseResultFlag flag;
		CBlocking::HBlock contents;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockExecutionResultFlag; }
	};
	using HBlockExecutionResultFlag = std::shared_ptr<CBlockExecutionResultFlag>;


}

#endif