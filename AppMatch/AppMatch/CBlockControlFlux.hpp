#pragma once
 

#ifndef CBLOCKCONTROLFLUX_H
#define CBLOCKCONTROLFLUX_H

#include "BlockInterpreter.hpp"



class CBlockControlToken //classe que diz que aqui tem um TOKEN especifico de controle
	: public CBlock   
{
public:
	CBlockControlToken(string _token , HBlock _contents )
		: token(_token) , contents(_contents)  {}

	string token;
	HBlock contents;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockControlToken; }
};
using HBlockControlToken = std::shared_ptr<CBlockControlToken>;


class CBlockControlIF
	: public CBlock  
{
public:
	CBlockControlIF(HBlock _block_if , HBlock _block_then, HBlock _block_else )
		: block_if(_block_if) , block_then(_block_then) , block_else(_block_else){}

	HBlock block_if;
	HBlock block_then;
	HBlock block_else;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockControlIF ; }
};
 
using HBlockControlIF = std::shared_ptr<CBlockControlIF>;



class CBlockControlUnless
	: public CBlock
{
public:
	CBlockControlUnless(HBlock _block_if, HBlock _block_then, HBlock _block_else)
		: block_if(_block_if), block_then(_block_then), block_else(_block_else) {}

	HBlock block_if;
	HBlock block_then;
	HBlock block_else;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockControlIF; }
};

using HBlockControlUnless = std::shared_ptr<CBlockControlUnless>;



class CBlockControlSelectItem
	: public CBlock
{
public:
	CBlockControlSelectItem(HBlock _block_seletor, HBlock _block_execute)
		: block_seletor(_block_seletor), block_execute(_block_execute) {}

	HBlock block_seletor;
	HBlock block_execute;


	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockControlSelectItem; }
};
using HBlockControlSelectItem = std::shared_ptr<CBlockControlSelectItem>;




class CBlockControlSelect
	: public CBlock
{
public:
	CBlockControlSelect(HBlock _block_seletor, std::list<HBlockControlSelectItem> _block_selectList, HBlock _block_else)
		: block_seletor(_block_seletor), block_selectList(_block_selectList), block_else(_block_else) {}

	HBlock block_seletor;
	std::list<HBlockControlSelectItem> block_selectList;
	HBlock block_else;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockControlSelect; }
};
using HBlockControlSelect = std::shared_ptr<CBlockControlSelect>;



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
	CBlockExecutionResultFlag(PhaseResultFlag _flag, HBlock _contents)
		: flag(_flag), contents(_contents) {}

	PhaseResultFlag flag;
	HBlock contents;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockExecutionResultFlag; }
};
using HBlockExecutionResultFlag = std::shared_ptr<CBlockExecutionResultFlag>;

 


#endif