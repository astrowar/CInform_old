#pragma once

#include "BlockInterpreter.h"

class CBlockMatch
        : public CBlock // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(std::string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
    virtual bool match() { return false; };
    HBlock matchInner;

    CBlockMatch(HBlock _matchInner) : matchInner(_matchInner) {};
};

using HBlockMatch = std::shared_ptr<CBlockMatch>;

class CBlockMatchAny
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(std::string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
    virtual bool match() override { return true; };

    CBlockMatchAny() : CBlockMatch(nullptr) {};
};


class CBlockMatchNamed
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(std::string ident) override;

    virtual bool match() override;;
    std::string named;
    HBlockMatch matchInner;

    CBlockMatchNamed(std::string _named, HBlockMatch _matchInner) : CBlockMatch(nullptr), named(_named),
                                                                    matchInner(_matchInner) {};
};

using HBlockMatchNamed = std::shared_ptr<CBlockMatchNamed>;

class CBlockMatchKind
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(std::string ident) override;

    // CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block
    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
    virtual bool match() override { return false; };
    HBlockKind kind;

    CBlockMatchKind(HBlockKind _kindInnter) : CBlockMatch(nullptr), kind(_kindInnter) {};
};


class CBlockMatchWith : public CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatchWith(const HBlock& _matchInner, const HBlockMatch& previous_match)
		: CBlockMatch(_matchInner),
		  previous_match(previous_match)
	{
	}

	HBlockMatch previous_match;
};


class CBlockMatchList
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(std::string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
    virtual bool match() override { return false; };
    std::list<HBlockMatch> matchList;

    CBlockMatchList(std::list<HBlockMatch> _matchList) : CBlockMatch(nullptr), matchList(_matchList) {};
};

using HBlockMatchList = std::shared_ptr<CBlockMatchList>;

//  eating something in the presence of Lady Bracknell
class CBlockMatchAction : public CBlockMatch // um bloco que serve para dar Match em uma Acao
{
public :
    CBlockMatchAction(HBlockAction input)
            : CBlockMatch(input), input(input) {
    }

    HBlockAction input;
};


