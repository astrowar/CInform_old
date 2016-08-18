#pragma once
#include "BlockInterpreter.h"

class CBlockMatch : public  CBlock // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() { return false; };
	CBlock* matchInner;
	CBlockMatch(CBlock* _matchInner  ): matchInner(_matchInner)
	{};
};

class CBlockMatchAny : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() override { return true; };

	CBlockMatchAny( ) : CBlockMatch(nullptr)
	{};
};



class CBlockMatchNamed : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	virtual bool match() override;;
	std::string named;
	CBlockMatch* matchInner;

	CBlockMatchNamed(std::string _named, CBlockMatch* _matchInner) :  CBlockMatch(nullptr),named(_named), matchInner(_matchInner)
	{};
};



class CBlockMatchKind : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;
	// CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block
	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() override
	{ return false; };
	CBlockKind* kind;
	CBlockMatchKind(CBlockKind* _kindInnter) : CBlockMatch(nullptr), kind(_kindInnter)
	{};
};


class CBlockMatchWith : public  CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatch* previous_match;
};


class CBlockMatchList : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() override
	{ return false; };
	std::list<CBlockMatch*>  matchList;
	CBlockMatchList(std::list<CBlockMatch*> _matchList) : CBlockMatch(nullptr), matchList(_matchList)
	{};
};

//  eating something in the presence of Lady Bracknell
class CBlockMatchAction : public  CBlockMatch // um bloco que serve para dar Match em uma Acao
{
public :
	  CBlockMatchAction(CBlockAction* input)
		: CBlockMatch(input), input(input)
	{
	}

	CBlockAction* input;
};


