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

    CBlockUnderstandStatic(HBlockMatchList _argument_match, HBlock _output_n) : argument_match(_argument_match),
                                                                                output_n((_output_n)) {};
};

using HBlockUnderstandStatic = std::shared_ptr<CBlockUnderstandStatic>;

#endif