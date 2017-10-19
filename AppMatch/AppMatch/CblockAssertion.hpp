#pragma once
#ifndef CBLOCKASSERTATION_H
#define CBLOCKASSERTATION_H

#include "BlockInterpreter.hpp"
#include "BlockInstance.hpp"
#include "CBlockAction.hpp"

namespace CBlocking
{
	class CBlockAssertionBase : public CBlock //retorna uma declaracao
	{
	public:
		virtual CBlocking::HBlock get_obj() = 0;
		CBlockAssertionBase() {}

	};

	using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;

	class CBlockAssertion_is : public CBlockAssertionBase //retorna uma declaracao
	{
	public:
		void dump(string ident) override;


		virtual CBlocking::HBlock get_definition() = 0;

		//CBlockAssertion(HTerm obj, HTerm thing){};
		CBlockAssertion_is() {};

	};

	using HCBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;

	//class CBlockAssertion_property_canBe : public CBlockAssertionBase //retorna uma declaracao
	//{
	//public:
	//	void dump(std::string ident) override;
	//
	//	HBlockEnums definition;
	//	//CBlockAssertion(HTerm obj, HTerm thing){};
	//	CBlockAssertion_property_canBe(HBlockProperty _obj, HBlockEnums _definition) :CBlockAssertionBase(_obj), definition(_definition) {};
	//	virtual NoumDefinitions noumDefinitions() override { return obj->noumDefinitions(); };
	//};


	class CBlockAssertion_canBe : public CBlockAssertionBase //retorna uma declaracao
	{
	public:
		virtual CBlocking::HBlock get_obj() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_canBe; }
		HBlockEnums definition;
		CBlocking::HBlock obj;

		//CBlockAssertion(HTerm obj, HTerm thing){};
		CBlockAssertion_canBe(CBlocking::HBlock _obj, HBlockEnums _definition);;
	};

	using HBlockAssertion_canBe = std::shared_ptr<CBlockAssertion_canBe>;

	class CBlockAssertion_isKindOf : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;
	 
		void dump(string ident) override;
		virtual CBlocking::HBlock get_definition() override;;
		HBlockKind noum;
		HBlockKind baseKind;
		CBlockAssertion_isKindOf(HBlockKind _noum, HBlockKind _baseKind) : noum(_noum), baseKind(_baseKind) {};
	};

	using HBlockAssertion_isKindOf = std::shared_ptr<CBlockAssertion_isKindOf>;

	class CBlockAssertion_isInstanceOf : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;
		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isInstanceOf; }

		HBlockInstance noum;
		HBlockKind baseKind;

		CBlockAssertion_isInstanceOf(HBlockInstance _noum, HBlockKind _baseKind) : noum(_noum), baseKind(_baseKind) {};
	};

	using HBlockAssertion_isInstanceOf = std::shared_ptr<CBlockAssertion_isInstanceOf>;


	class CBlockAssertion_isNamedValueOf : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isNamedValueOf; }

		CBlocking::HBlock noum;
		CBlocking::HBlock baseKind;

		CBlockAssertion_isNamedValueOf(CBlocking::HBlock _noum, CBlocking::HBlock _baseKind) : noum((_noum)),
			baseKind((_baseKind)) {};
	};

	using HBlockAssertion_isNamedValueOf = std::shared_ptr<CBlockAssertion_isNamedValueOf>;

	class CBlockAssertion_isVariable : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isVariable; }

		CBlocking::HBlock variable;
		CBlocking::HBlock baseKind;

		CBlockAssertion_isVariable(CBlocking::HBlock _variable, CBlocking::HBlock _baseKind) : variable((_variable)),
			baseKind((_baseKind)) {};
	};
	using HBlockAssertion_isVariable = std::shared_ptr<CBlockAssertion_isVariable>;




 

		class CBlockAssertion_isLocalVariable : public CBlockAssertion_is //retorna uma declaracao

		{
		public:
			CBlocking::HBlock get_obj() override;

			CBlocking::HBlock get_definition() override;

			virtual void dump(string ident) override;
			virtual BlockType type() override { return BlockType::BlockAssertion_isLocalVariable; }

			CBlocking::HBlockNoum variableName;
			CBlocking::HBlock valueExpression;

			CBlockAssertion_isLocalVariable(CBlocking::HBlockNoum _variableName, CBlocking::HBlock _valueExpression) : variableName((_variableName)),
				valueExpression((_valueExpression)) {};
		};
		using HBlockAssertion_isLocalVariable = std::shared_ptr<CBlockAssertion_isLocalVariable>;



	class CBlockAssertion_isDefaultAssign : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isDefaultAssign; }
		CBlocking::HBlock variable;
		CBlocking::HBlock value;

		CBlockAssertion_isDefaultAssign(CBlocking::HBlock _variable, CBlocking::HBlock _value) : variable((_variable)),
			value((_value)) {};
	};

	using HBlockAssertion_isDefaultAssign = std::shared_ptr<CBlockAssertion_isDefaultAssign>;

	class CBlockAssertion_isConstantAssign : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isConstantAssign; }

		CBlocking::HBlock variable;
		CBlocking::HBlock value;

		CBlockAssertion_isConstantAssign(CBlocking::HBlock _variable, CBlocking::HBlock _value) : variable((_variable)),
			value((_value)) {};
	};

	using HBlockAssertion_isConstantAssign = std::shared_ptr<CBlockAssertion_isConstantAssign>;

	class CBlockAssertion_isForbiddenAssign : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isForbiddenAssign; }

		CBlocking::HBlock variable;
		CBlocking::HBlock value;

		CBlockAssertion_isForbiddenAssign(CBlocking::HBlock _variable, CBlocking::HBlock _value) : variable((_variable)),
			value((_value)) {};
	};
	using HBlockAssertion_isForbiddenAssign = std::shared_ptr<CBlockAssertion_isForbiddenAssign>;



	class CBlockAssertion_isDirectAssign : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;

		CBlocking::HBlock get_definition() override;

		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isDirectAssign; }


		CBlocking::HBlock variable;
		CBlocking::HBlock value;

		CBlockAssertion_isDirectAssign(CBlocking::HBlock _variable, CBlocking::HBlock _value) : variable((_variable)),
			value((_value)) {};
	};

	using HBlockAssertion_isDirectAssign = std::shared_ptr<CBlockAssertion_isDirectAssign>;

	class CBlockAssertion_isNotDirectAssign : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;
		CBlocking::HBlock get_definition() override;
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isNotDirectAssign; }
		CBlocking::HBlock variable;
		CBlocking::HBlock value;
		CBlockAssertion_isNotDirectAssign(CBlocking::HBlock _variable, CBlocking::HBlock _value) : variable((_variable)),
			value((_value)) {};
	};

	using HBlockAssertion_isNotDirectAssign = std::shared_ptr<CBlockAssertion_isNotDirectAssign>;

	class CBlockAssertion_isActionOf : public CBlockAssertion_is //retorna uma declaracao
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssertion_isActionOf; }
		HBlockNoum noum;
		HBlockAction action;
		HBlockActionApply application;

		CBlockAssertion_isActionOf(HBlockNoum _noum, HBlockAction _action, HBlockActionApply _application) : noum(_noum),
			action(_action),
			application(
				_application) {};
	};

	using HBlockAssertion_isActionOf = std::shared_ptr<CBlockAssertion_isActionOf>;

	class CBlockIsVerb : public CBlockAssertion_is    //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;
		CBlocking::HBlock get_definition() override;
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockIsVerb; }

		string verb;
		CBlocking::HBlock n1;
		CBlocking::HBlock n2;

		CBlockIsVerb(string _verb, CBlocking::HBlock _n1, CBlocking::HBlock _n2) : verb((_verb)), n1((_n1)), n2((_n2))
		{
			
		};
	};
	using HBlockIsVerb = std::shared_ptr<CBlockIsVerb>;


	class CBlockIsNotVerb : public CBlockAssertion_is    //retorna uma declaracao
	{
	public:
		CBlocking::HBlock get_obj() override;
		CBlocking::HBlock get_definition() override;
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockIsNotVerb; }

		string verb;
		CBlocking::HBlock n1;
		CBlocking::HBlock n2;

		CBlockIsNotVerb(string _verb, CBlocking::HBlock _n1, CBlocking::HBlock _n2) : verb(_verb), n1((_n1)), n2((_n2)) {};
	};
	using HBlockIsNotVerb = std::shared_ptr<CBlockIsNotVerb>;


	class CBlockAssert : CBlock    //retorna uma declaracao
	{
	public:
 
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAssert; }
		CBlocking::HBlock expression;
		CBlocking::HBlock result;
		CBlockAssert( CBlocking::HBlock _expression, CBlocking::HBlock _result) : expression(_expression),result(_result) {};

	};
	 
		using HBlockAssert = std::shared_ptr<CBlockAssert>;














		class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao
		{
		public:
			virtual void dump(string ident) override;
			virtual BlockType type() override { return BlockType::BlockAssertion_InstanceVariable; }
			HBlock noum;
			HBlockInstanceVariable instance_variable;
			CBlockAssertion_InstanceVariable(HBlock _noum, HBlockInstanceVariable _instance_variable) : noum((_noum)),
				instance_variable(
					_instance_variable) {};
		};
		using HBlockAssertion_InstanceVariable = std::shared_ptr<CBlockAssertion_InstanceVariable>;


		class CBlockAssertionCond : public CBlock // assertion com condicao
		{
		public:
			HBlockBooleanResult cond;
		};
}
#endif //CBLOCKMATCH_H