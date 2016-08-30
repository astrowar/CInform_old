#pragma once
#ifndef CBLOCKUNDESTAND_H
#define CBLOCKUNDESTAND_H


#include "BlockInterpreter.h"
 
#include "CBlockMatch.h"

class CBlockUnderstand : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(string ident) override;

    HBlockMatch input_n; // Pode ser simples ou com a preposicao
    HBlock output_n;

    CBlockUnderstand(HBlockMatch _input_n, HBlock _output_n) : input_n(_input_n), output_n((_output_n)) {};
};


class CBlockUnderstandStatic : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(string ident) override;

    HBlockMatchList argument_match; // Pode ser simples ou com a preposicao
    HBlock output_n;
	int entryID;
    CBlockUnderstandStatic(int _entryID,HBlockMatchList _argument_match, HBlock _output_n) : argument_match(_argument_match),
                                                                                output_n((_output_n)), entryID(_entryID)
    {};
};

using HBlockUnderstandStatic = std::shared_ptr<CBlockUnderstandStatic>;







class CBlockUnderstandDynamic : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(string ident) override;

	HBlockMatch input_n; // Pode ser simples ou com a preposicao
	HBlockMatch argument_n;
	HBlock output_n;
	CBlockUnderstandDynamic(HBlockMatch _input_n, HBlockMatch _argumentMatchs, HBlock _output_n) : input_n(_input_n), argument_n(_argumentMatchs), output_n(_output_n) {};
};

using HBlockUnderstandDynamic = std::shared_ptr<CBlockUnderstandDynamic>;



#endif