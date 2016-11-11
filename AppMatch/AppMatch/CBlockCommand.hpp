//
// Created by eraldo.rangel on 12/09/2016.
//

#ifndef APPMATCH_CBLOCKCOMMAND_H
#define APPMATCH_CBLOCKCOMMAND_H


#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"

class CBlockNow : public CBlock     //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockNow; }

	HBlockAssertion_is assertation;
	CBlockNow(  HBlockAssertion_is _n ) : assertation(_n) {};
}; 

using HBlockNow = std::shared_ptr<CBlockNow>;

class CBlockEvery : public CBlock     //retorna uma declaracao tal qual o comando se aplica a todos do tipo interno
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockEvery; }

	HBlock assertation;
	CBlockEvery(HBlock _n) : assertation(_n) {};
};

using HBlockEvery = std::shared_ptr<CBlockEvery>;

class CBlockComandList : public CBlock     //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockComandList; }

	std::list<HBlock> lista;
	CBlockComandList(std::list<HBlock> _lista) : lista(_lista) {};
};

using HBlockComandList = std::shared_ptr<CBlockComandList>;







// Blocos que definem os Event Handles das acoes

enum EventHandleStage {
	StageBefore,
	StageAfter,
	StageReport
};


class CBlockEventHandle : public CBlock     //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockEventHandle; }
	
	CBlockEventHandle(EventHandleStage _stage, HBlockMatchActionCall  _eventToObserve , HBlockComandList _body ) : eventToObserve(_eventToObserve), body(_body), stage(_stage) {};
	HBlockMatchActionCall  eventToObserve;
	HBlockComandList body;
	EventHandleStage stage;
};

using HBlockEventHandle = std::shared_ptr<CBlockEventHandle>;




#endif //APPMATCH_CBLOCKCOMMAND_H
