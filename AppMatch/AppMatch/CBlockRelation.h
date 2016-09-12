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
 


class CBlockRelationBase
	: public CBlock  //  define uma relacao .. este bloco eh abstrato
{
public:
	CBlockRelationBase(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b, bool _various_1 , bool _various_2)
		: named(_named),
		input_A(input_a),
		input_B(input_b), various_noum1(_various_1), various_noum2(_various_2)
	{
	}

	virtual bool is_various_noum1() { return various_noum1; };
	virtual bool is_various_noum2() { return various_noum2;  }
	virtual bool is_symetric() = 0;
	std::string named;
	HBlockArgumentInput input_A;
	HBlockArgumentInput input_B;
	bool various_noum1;
	bool various_noum2;
};
using HBlockRelationBase = std::shared_ptr<CBlockRelationBase>;
 






class CBlockSimetricRelation : public CBlockRelationBase 
{
public:
	virtual void dump(string ident) override;

	CBlockSimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b,bool _various_1, bool _various_2) : CBlockRelationBase(_named, input_a, input_b ,_various_1,_various_2)
	{
	}
	virtual bool is_symetric()override { return true ; }
};
using HBlockSimetricRelation = std::shared_ptr<CBlockSimetricRelation>;

 


class CBlockASimetricRelation : public CBlockRelationBase	 
{
public:
	virtual void dump(string ident) override;
	 CBlockASimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b, bool _various_1, bool _various_2) : CBlockRelationBase(_named, input_a, input_b,_various_1, _various_2)
	{
	}

	 virtual bool is_symetric()override { return false; }
};

 
using HBlockASimetricRelation = std::shared_ptr<CBlockASimetricRelation>;




//Relation Connection Per Se
class CBlockRelationInstance : public CBlock
{
public:
	virtual void dump(string ident) override;
	HBlockRelationBase relation;
	HBlock value1 ;
	HBlock value2 ;

	CBlockRelationInstance(HBlockRelationBase _relation, HBlock _value1 , HBlock  _value2) : relation( _relation), value1(_value1), value2(_value2)
	{
	}

};
using HBlockRelationInstance = std::shared_ptr<CBlockRelationInstance>;

