#pragma once

#ifndef CBLOCKMATCH_H
#define CBLOCKMATCH_H

 
#include "BlockInterpreter.hpp"
#include "CBlockAction.hpp"

namespace CBlocking
{


	class CBlockMatch : public CBlock // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		// virtual void dump(string ident) override;

		 // CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"


		CBlockMatch() {};
	};

	using HBlockMatch = std::shared_ptr<CBlockMatch>;

	class CBlockMatchAny : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchAny; }

		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"


		CBlockMatchAny() : CBlockMatch() {};
	};
	using HBlockMatchAny = std::shared_ptr<CBlockMatchAny>;

	class CBlockMatchNamed : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchNamed; }


		string named;
		HBlockMatch matchInner;
		CBlockMatchNamed(string _named, HBlockMatch _matchInner);

	};
	using HBlockMatchNamed = std::shared_ptr<CBlockMatchNamed>;



	class CBlockMatchNoum : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchNoum; }
		HBlockNoum  inner;
		CBlockMatchNoum(HBlockNoum _inner);
	};
	using HBlockMatchNoum = std::shared_ptr<CBlockMatchNoum>;



	class CBlockMatchValue : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchValue; }
		HBlock   inner;
		CBlockMatchValue(HBlock  _inner) : CBlockMatch(), inner(_inner) {};
	};
	using HBlockMatchValue = std::shared_ptr<CBlockMatchValue>;





	class CBlockMatchKind : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchKind; }

		// CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block
		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"

		HBlockKind kind;

		CBlockMatchKind(HBlockKind _kindInnter) : CBlockMatch(), kind(_kindInnter) {};
	};
	using HBlockMatchKind = std::shared_ptr<CBlockMatchKind>;


	class CBlockMatchWith : public CBlockMatch // um bloco que serve para dar Match  no match anterior
	{
		CBlockMatchWith(const CBlocking::HBlock& _matchInner, const HBlockMatch& previous_match)
			: CBlockMatch(),
			previous_match(previous_match)
		{
		}

		HBlockMatch previous_match;
	};
	using HBlockMatchWith = std::shared_ptr<CBlockMatchWith>;



	class CBlockMatchList : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchList; }
		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
		std::list<HBlockMatch> matchList;

		CBlockMatchList(std::list<HBlockMatch> _matchList);;
	};
	using HBlockMatchList = std::shared_ptr<CBlockMatchList>;


	//And Block

	class CBlockMatchAND : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchAND; }

		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"

		std::list<HBlockMatch> matchList;

		CBlockMatchAND(std::list<HBlockMatch> _matchList) : CBlockMatch(), matchList(_matchList) {};
	};

	using HBlockMatchAND = std::shared_ptr<CBlockMatchAND>;

	// NOT 
	class CBlockMatchNOT : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchNOT; }

		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"

		HBlockMatch  input;

		CBlockMatchNOT(HBlockMatch  _input) : CBlockMatch(), input(_input) {};
	};

	using HBlockMatchNOT = std::shared_ptr<CBlockMatchNOT>;



	//OR  Block

	class CBlockMatchOR : public CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchOR; }

		// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"

		std::list<HBlockMatch> matchList;

		CBlockMatchOR(std::list<HBlockMatch> _matchList) : CBlockMatch(), matchList(_matchList) {};
	};

	using HBlockMatchOR = std::shared_ptr<CBlockMatchOR>;







	//  eating something in the presence of Lady Bracknell
	//cls CBlockMatchAction : public CBlockMatch // um bloco que serve para dar Match em uma Acao
	//{
	//public:
	//	CBlockMatchAction(HBlockAction _input): CBlockMatch(), input(_input) 
	//	{		}

	//	HBlockAction input;
	//};
	//using HBlockMatchAction = std::shared_ptr<CBlockMatchAction>;

	class CBlockMatchActionCall : public CBlockMatch // um bloco que serve para dar Match em uma Acao
	{
	public:
		CBlockMatchActionCall(HBlockMatch _action, HBlockMatch _argument1, HBlockMatch _argument2)
			: CBlockMatch(), action(_action), argument1(_argument1), argument2(_argument2) {	}

		HBlockMatch action; //action name or ... etc ... ex: before ( geting or puting) an thing intro portal
		HBlockMatch argument1;
		HBlockMatch argument2;


		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchActionCall; }


	};
	using HBlockMatchActionCall = std::shared_ptr<CBlockMatchActionCall>;





	class CBlockMatchBlock : public CBlockMatch // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchBlock; }
		CBlocking::HBlock  inner;
		CBlockMatchBlock(CBlocking::HBlock  _inner) : CBlockMatch(), inner(_inner) {};
	};
	using HBlockMatchBlock = std::shared_ptr<CBlockMatchBlock>;




	class CBlockMatchIs : public CBlockMatch // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:

		HBlockMatch  obj;
		HBlockMatch  value;
		CBlockMatchIs(HBlockMatch  _obj, HBlockMatch _value) : CBlockMatch(), obj(_obj), value(_value) {};
	};
	using HBlockMatchIs = std::shared_ptr<CBlockMatchIs>;




	class CBlockMatchDirectIs : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchDirectIs; }

		CBlockMatchDirectIs(HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value) {};
	};
	using HBlockMatchDirectIs = std::shared_ptr<CBlockMatchDirectIs>;



	class CBlockMatchDirectIsNot : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchDirectIsNot; }

		CBlockMatchDirectIsNot(HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value) {};
	};
	using HBlockMatchDirectIsNot = std::shared_ptr<CBlockMatchDirectIsNot>;



	class CBlockMatchIsVerb : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchIsVerb; }
		std::string verb;


		CBlockMatchIsVerb(string _verb, HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value), verb(_verb) {
			if (_verb == "from")
			{
				logError("wrong");
			}

		};
	};
	using HBlockMatchIsVerb = std::shared_ptr<CBlockMatchIsVerb>;


	class CBlockMatchIsNotVerb : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchIsNotVerb; }
		std::string verb;
		CBlockMatchIsNotVerb(string _verb, HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value), verb(_verb) {};
	};
	using HBlockMatchIsNotVerb = std::shared_ptr<CBlockMatchIsNotVerb>;



	 
	class CBlockMatchIsAdverbialComparasion : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchIsAdverbialComparasion; }
		std::string adverb;


		CBlockMatchIsAdverbialComparasion(string _adverb, HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value), adverb(_adverb) {
			if (_adverb == "from")
			{
				logError("wrong");
			}

		};
	};
	using HBlockMatchIsAdverbialComparasion = std::shared_ptr<CBlockMatchIsAdverbialComparasion>;


	class CBlockMatchProperty : public CBlockMatch //retorna um valor generico
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchProperty; }
		CBlockMatchProperty(CBlocking::HBlock _prop, HBlockMatch b) : prop(_prop), obj(b) {}
		CBlocking::HBlock prop;
		HBlockMatch obj;

	};
	using HBlockMatchProperty = std::shared_ptr<CBlockMatchProperty>;


	class CBlockMatchWhich : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchWhich; }
		std::string verb;
		CBlockMatchWhich(string _verb, HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value), verb(_verb) {};
	};
	using HBlockMatchWhich = std::shared_ptr<CBlockMatchWhich>;

	class CBlockMatchWhichNot : public CBlockMatchIs // um bloco que serve para dar Match em um Bloco ... ???
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockMatchWhichNot; }
		std::string verb;
		CBlockMatchWhichNot(string _verb, HBlockMatch  _obj, HBlockMatch _value) : CBlockMatchIs(_obj, _value), verb(_verb) {};
	};
	using HBlockMatchWhichNot = std::shared_ptr<CBlockMatchWhichNot>;


}
#endif //CBLOCKMATCH_H