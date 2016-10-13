#pragma once
 

#ifndef CBLOCKCONTROLFLUX_H
#define CBLOCKCONTROLFLUX_H

#include "BlockInterpreter.hpp"



class CBlockControlToken //classe que diz que aqui tem um TOKEN especifico de controle
	: public CBlock   
{
public:
	CBlockControlToken(string _token  )
		: token(_token)  {}

	string token;
 

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



#endif