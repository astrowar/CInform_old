//
// Created by eraldo.rangel on 12/09/2016.
//

#ifndef APPMATCH_CBLOCKCOMMAND_H
#define APPMATCH_CBLOCKCOMMAND_H


#include "BlockInterpreter.hpp"

class CBlockNow : public CBlock     //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockNow; }

	HBlockAssertion_is assertation;
	CBlockNow(  HBlockAssertion_is _n ) : assertation(_n) {};
}; 

using HBlockNow = std::shared_ptr<CBlockNow>;


class CBlockComandList : public CBlock     //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockComandList; }

	std::list<HBlock> lista;
	CBlockComandList(std::list<HBlock> _lista) : lista(_lista) {};
};

using HBlockComandList = std::shared_ptr<CBlockComandList>;


#endif //APPMATCH_CBLOCKCOMMAND_H
