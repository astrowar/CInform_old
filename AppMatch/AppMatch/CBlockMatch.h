#pragma once

#ifndef CBLOCKMATCH_H
#define CBLOCKMATCH_H


#include "BlockInterpreter.h"
#include "CBlockAction.h"

class CBlockMatch
        : public CBlock // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
   // virtual void dump(string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
    

    CBlockMatch()  {};
};

using HBlockMatch = std::shared_ptr<CBlockMatch>;

class CBlockMatchAny
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
   

    CBlockMatchAny() : CBlockMatch( ) {};
};


class CBlockMatchNamed : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(string ident) override;

    
    string named;
    HBlockMatch matchInner;
    CBlockMatchNamed(string _named, HBlockMatch _matchInner) : CBlockMatch( ), named(_named),
                                                                    matchInner(_matchInner) {};
};
using HBlockMatchNamed = std::shared_ptr<CBlockMatchNamed>;



class CBlockMatchNoum : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(string ident) override;
	HBlockNoum  inner;
	CBlockMatchNoum(HBlockNoum _inner) : CBlockMatch(), inner(_inner) {};
};
using HCBlockMatchNoum = std::shared_ptr<CBlockMatchNoum>;



class CBlockMatchKind
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(string ident) override;

    // CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block
    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
  
    HBlockKind kind;

    CBlockMatchKind(HBlockKind _kindInnter) : CBlockMatch( ), kind(_kindInnter) {};
};


class CBlockMatchWith : public CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatchWith(const HBlock& _matchInner, const HBlockMatch& previous_match)
		: CBlockMatch( ),
		  previous_match(previous_match)
	{
	}

	HBlockMatch previous_match;
};


class CBlockMatchList
        : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
    virtual void dump(string ident) override;

    // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
 
    std::list<HBlockMatch> matchList;

    CBlockMatchList(std::list<HBlockMatch> _matchList) : CBlockMatch( ), matchList(_matchList) {};
};

using HBlockMatchList = std::shared_ptr<CBlockMatchList>;

//  eating something in the presence of Lady Bracknell
class CBlockMatchAction : public CBlockMatch // um bloco que serve para dar Match em uma Acao
{
public :
    CBlockMatchAction(HBlockAction _input)
            : CBlockMatch( ), input(_input) {
    }

    HBlockAction input;
};



class CBlockMatchBlock : public CBlockMatch // um bloco que serve para dar Match em um Bloco ... ???
{
public:
	virtual void dump(string ident) override;
	HBlock  inner;
	CBlockMatchBlock(HBlock  _inner) : CBlockMatch(), inner(_inner) {};
};
using HBlockMatchBlock = std::shared_ptr<CBlockMatchBlock>;


 

class CBlockMatchIs  : public CBlockMatch // um bloco que serve para dar Match em um Bloco ... ???
{
public:
 
	HBlock  obj;
	HBlock  value;
	CBlockMatchIs(HBlock  _obj, HBlock _value ) : CBlockMatch(), obj(_obj) , value(_value ) {};
};
using HBlockMatchIs = std::shared_ptr<CBlockMatchIs>;




class CBlockMatchDirectIs : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
{
public:
	virtual void dump(string ident) override;
 
	CBlockMatchDirectIs(HBlock  _obj, HBlock _value) : CBlockMatchIs(_obj , _value )   {};
};
using HBlockMatchDirectIs = std::shared_ptr<CBlockMatchDirectIs>;




class CBlockMatchIsVerb : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
{
public:
	virtual void dump(string ident) override; 
	std::string verb;
	CBlockMatchIsVerb(string _verb , HBlock  _obj, HBlock _value) : CBlockMatchIs(_obj, _value), verb(_verb) {};
};
using HBlockMatchIsVerb = std::shared_ptr<CBlockMatchIsVerb>;


#endif //CBLOCKMATCH_H