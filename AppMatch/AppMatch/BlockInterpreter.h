#pragma once
#include "CBase.h"

using std::string;
class CBlock;

class CBlock
{

public:
	virtual void dump(std::string  ident  ) = 0;

	virtual ~CBlock()
	{
	}

 
};

class CBlockBooleanResult   // um tipo de bloco que retorna true ou false 
{
public:
	virtual ~CBlockBooleanResult()
	{
	}

	virtual bool result() = 0;
};



class CBlockValue : public CBlock //retorna um valor generico 
{
public:
	void dump(std::string ident) override;
	CBlockValue(string value);
	string value;
};

class CBlockList : public CBlock //retorna um valor generico 
{
public:
	virtual void  dump(std::string  ident) override;
	std::list<CBlock*> lista;
	void push_back(CBlockValue* c_block_value);
};

class CBlockAssertion : public CBlock //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock* obj;  CBlock* definition;

	//CBlockAssertion(HTerm obj, HTerm thing){};
	CBlockAssertion(CBlock* _obj, CBlock* _definition): obj(_obj),definition(_definition)	{};

};

class CBlockAssertionCond: public CBlock // assertion com condicao 
{	
	CBlockBooleanResult* cond;
};


class CBlockFilter: public CBlock   // filtra um valor para outro valor 
{
	virtual HTerm  filter() = 0;
};


class CBlockFilterAtom: public  CBlockFilter 
{
	CBlock* input;
	virtual bool filter(HTerm input)  ;
};

class CBlockFilterList : public  CBlockFilter
{
	CBlockList* input;
	virtual bool filter(HTerm input)  ;
};


class CBlockMatch : public  CBlock // um bloco que serve para dar Match em um value , retorna true ou false 
{
	virtual bool  match() = 0;
};



class CBlockMatchWith : public  CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatch* previous_match; 
};


class CBlockAction : public  CBlock  // um bloco que representa uma atividade
{
	explicit CBlockAction(CBlock* input)
		: input(input)
	{
	}

	CBlock* input;
};

class CBlockActionApply: public  CBlock
{
public:
	void dump(std::string ident) override;
	CBlock* noum1;
	CBlock* noum2;
	CBlockActionApply(CBlock* _noum1, CBlock* _noum2 );


};

//  eating something in the presence of Lady Bracknell
class CBlockMatchAction : public  CBlockMatch // um bloco que serve para dar Match em uma Acao
{
	CBlockAction* input;
};


class CBlockTransform  : public  CBlock  // um bloco que trasnforma um valor em outro
{
	CBlock* input;
	virtual HTerm transform() = 0 ;
};


 


class CBlockIF : public  CBlock  // um bloco do tipo if then else
{
	CBlockBooleanResult* input_if; // o if tem que set True ou False 
	CBlock* input_then;
	CBlock* input_else;
	virtual HTerm eval() = 0;
};

class CBlockSame : public  CBlock, CBlockBooleanResult  // um bloco do tipo if then else
{	 
	CBlock* input_A;
	CBlock* input_B;	 
};

class CBlockProp : public  CBlock  // um bloco que especifica uma propiedade ( color OF book ) -> ( prop OF what )
{	 
	CBlock* what;
	CBlock* prop;
	virtual HTerm eval() = 0;
};



class CBlockInterpreter
{
public:
	CBlockInterpreter();
	~CBlockInterpreter();
};

 