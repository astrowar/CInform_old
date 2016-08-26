#pragma once
#include "BlockInterpreter.h"



class CBlockArgumentInput : public CBlock //retorna um valor generico
{
public:
	virtual void dump(string ident) override;

	CBlockArgumentInput(HBlockKind _kind,string _named): kind(_kind),named(_named){}

	HBlockKind kind;
	string named;

	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};
using HBlockArgumentInput = std::shared_ptr<CBlockArgumentInput>;
 


class CBlockRelation
	: public CBlock  //  define uma relacao .. este bloco eh abstrato
{
public:
	CBlockRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b)
		: named(_named),
		input_A(input_a),
		input_B(input_b) {
	}

	std::string named;
	HBlockArgumentInput input_A;
	HBlockArgumentInput input_B;
};
using HBlockRelation = std::shared_ptr<CBlockRelation>;
 

class CBlockSimetricRelation : public CBlockRelation 
{
public:
	virtual void dump(string ident) override;

	CBlockSimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b) : CBlockRelation(_named, input_a, input_b)
	{
	}
 
};
using HBlockSimetricRelation = std::shared_ptr<CBlockSimetricRelation>;





class CBlockASimetricRelation : public CBlockRelation	 
{
public:
	virtual void dump(string ident) override;
	 CBlockASimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b) : CBlockRelation(_named, input_a, input_b)
	{
	}

};
using HBlockASimetricRelation = std::shared_ptr<CBlockASimetricRelation>;