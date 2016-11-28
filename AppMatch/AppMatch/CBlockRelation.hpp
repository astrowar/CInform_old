#pragma once
#include "BlockInterpreter.hpp"


namespace CBlocking
{
	class CBlockArgumentInput : public CBlock //retorna um valor generico
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockArgumentInput; }
		CBlockArgumentInput(HBlockKind _kind, string _named) : kind(_kind), named(_named) {}

		HBlockKind kind;
		string named;

		virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

	};
	using HBlockArgumentInput = std::shared_ptr<CBlockArgumentInput>;



	class CBlockRelationBase
		: public CBlock  //  define uma relacao .. este bloco eh abstrato
	{
	public:
		CBlockRelationBase(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b, bool _various_1, bool _various_2)
			: named(_named),
			input_A(input_a),
			input_B(input_b), various_noum1(_various_1), various_noum2(_various_2)
		{
		}

		virtual bool is_various_noum1() { return various_noum1; };
		virtual bool is_various_noum2() { return various_noum2; }
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
		virtual BlockType type() override { return BlockType::BlockSimetricRelation; }

		CBlockSimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b, bool _various_1, bool _various_2) : CBlockRelationBase(_named, input_a, input_b, _various_1, _various_2)
		{
		}
		virtual bool is_symetric()override { return true; }
	};
	using HBlockSimetricRelation = std::shared_ptr<CBlockSimetricRelation>;




	class CBlockASimetricRelation : public CBlockRelationBase
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockASimetricRelation; }
		CBlockASimetricRelation(std::string _named, HBlockArgumentInput input_a, HBlockArgumentInput input_b, bool _various_1, bool _various_2) : CBlockRelationBase(_named, input_a, input_b, _various_1, _various_2)
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
		virtual BlockType type() override { return BlockType::BlockRelationInstance; }
		HBlockRelationBase relation;
		CBlocking::HBlock value1;
		CBlocking::HBlock value2;

		CBlockRelationInstance(HBlockRelationBase _relation, CBlocking::HBlock _value1, CBlocking::HBlock  _value2) : relation(_relation), value1(_value1), value2(_value2)
		{

		}

	};
	using HBlockRelationInstance = std::shared_ptr<CBlockRelationInstance>;



	class CBlockConditionalRelation : public CBlockRelationBase
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockConditionalRelation; }
		CBlockConditionalRelation(HBlockRelationBase  _relation, CBlocking::HBlock  _coditional) : CBlockRelationBase(_relation->named, _relation->input_A, _relation->input_B, false, false)
		{

		}

		HBlockRelationBase  relation;
		CBlocking::HBlock coditional;
		virtual bool is_symetric()override { return false; } // is never simetric

	};
	using HBlockConditionalRelation = std::shared_ptr<CBlockConditionalRelation>;



	enum NoumLocation {
		FirstNoum,
		SecondNoum
	};

	class CBlockRelationLookup : public CBlock
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockRelationLookup; }
		string relation;
		HBlockMatch value1;
		HBlockMatch value2;
		NoumLocation term_to_query;

		CBlockRelationLookup(string _relation, HBlockMatch _value1, HBlockMatch  _value2, NoumLocation _term_to_query) : relation(_relation), value1(_value1), value2(_value2), term_to_query(_term_to_query)
		{

		}

	};
	using HBlockRelationLookup = std::shared_ptr<CBlockRelationLookup>;





	class CBlockVerbLookup : public CBlock
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerbLookup; }
		string verb;
		HBlockMatch value1;
		HBlockMatch value2;
		NoumLocation term_to_query;

		CBlockVerbLookup(string _verb, HBlockMatch _value1, HBlockMatch  _value2, NoumLocation _term_to_query) : verb(_verb), value1(_value1), value2(_value2), term_to_query(_term_to_query)
		{

		}

	};
	using HBlockVerbLookup = std::shared_ptr<CBlockVerbLookup>;

}

