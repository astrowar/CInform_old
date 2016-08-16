#pragma once
#include "BlockInterpreter.h"








class CBlockAssertionBase : public CBlock //retorna uma declaracao
{
public:
	virtual CBlock* get_obj() = 0;
	//CBlockAssertion(HTerm obj, HTerm thing){};
	CBlockAssertionBase( ){}
	//virtual NoumDefinitions noumDefinitions() override { return obj->noumDefinitions(); };
};


class CBlockAssertion_is : public CBlockAssertionBase //retorna uma declaracao
{
public:
	void dump(std::string ident) override;


	virtual CBlock* get_definition() = 0;
	//CBlockAssertion(HTerm obj, HTerm thing){};
	CBlockAssertion_is(  )    {};

};


//class CBlockAssertion_property_canBe : public CBlockAssertionBase //retorna uma declaracao
//{
//public:
//	void dump(std::string ident) override;
//
//	CBlockEnums* definition;
//	//CBlockAssertion(HTerm obj, HTerm thing){};
//	CBlockAssertion_property_canBe(CBlockProperty* _obj, CBlockEnums* _definition) :CBlockAssertionBase(_obj), definition(_definition) {};
//	virtual NoumDefinitions noumDefinitions() override { return obj->noumDefinitions(); };
//};


class CBlockAssertion_canBe : public CBlockAssertionBase //retorna uma declaracao
{
public:
	virtual CBlock* get_obj() override;
	virtual void dump(std::string ident) override;
	CBlockEnums* definition;
	CBlock* obj;
	//CBlockAssertion(HTerm obj, HTerm thing){};
	CBlockAssertion_canBe(UBlock  _obj, CBlockEnums* _definition);;
};






class CBlockAssertion_isKindOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	NoumDefinitions noumDefinitions() override;
	void dump(std::string ident) override;

	virtual CBlock* get_definition() override;;

	CBlockKind * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isKindOf(CBlockKind* _noum, CBlockKind * _baseKind) :  noum(_noum) , baseKind(_baseKind){};
};


class CBlockAssertion_isInstanceOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	CBlockInstance * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isInstanceOf(CBlockInstance* _noum, CBlockKind * _baseKind) :  noum(_noum), baseKind(_baseKind) {};
};


class CBlockAssertion_isNamedValueOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override ;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock noum;
	UBlock baseKind;
	CBlockAssertion_isNamedValueOf(UBlock _noum, UBlock _baseKind) : noum(std::move(_noum))  , baseKind(std::move(_baseKind)) {};
};



class CBlockAssertion_isVariable : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock baseKind;
	CBlockAssertion_isVariable(UBlock _variable, UBlock _baseKind) :  variable(std::move(_variable)), baseKind(std::move(_baseKind)) {};
};








class CBlockAssertion_isDefaultAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isDefaultAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};





class CBlockAssertion_isConstantAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock   variable;
	UBlock   value;
	CBlockAssertion_isConstantAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};


class CBlockAssertion_isForbiddenAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isForbiddenAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value))  {};
};

class CBlockAssertion_isDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isDirectAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};

class CBlockAssertion_isNotDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	CBlock* get_obj() override;
	CBlock* get_definition() override;
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isNotDirectAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};


class CBlockAssertion_isActionOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	void dump(std::string ident) override;

	CBlockNoum* noum;
	CBlockAction* action;
	CBlockActionApply* application;
	CBlockAssertion_isActionOf(CBlockNoum* _noum, CBlockAction * _action , CBlockActionApply* _application) :  noum(_noum), action(_action), application(_application) {};
};

