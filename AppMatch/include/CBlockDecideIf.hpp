#pragma once
#include "BlockInterpreter.hpp" 
#include "CBlockMatch.hpp"

#include <cassert>

namespace CBlocking
{
	class CBlockToDecide  : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
	{
	public:
		CBlockToDecide()
		{
		}

		 

	};



	class CBlockToDecideIf  : public CBlockToDecide  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
	{
	public:
		CBlockToDecideIf(HBlockMatchIs _queryToMatch, CBlocking::HBlock _decideBody)
			: queryToMatch(_queryToMatch),
			decideBody(_decideBody) 
		{
			assert(_queryToMatch != nullptr);
		}

		HBlockMatchIs queryToMatch;
		CBlocking::HBlock decideBody;



		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockToDecideIf; }
	};

	using HBlockToDecideIf = std::shared_ptr<CBlockToDecideIf>;
	using HBlockToDecide = std::shared_ptr<CBlockToDecide>;



	class CBlockToDecideWhether  : public CBlockToDecide
	{
	public:
		CBlockToDecideWhether(HBlockMatch _queryToMatch, CBlocking::HBlock _decideBody)
			: queryToMatch(_queryToMatch),
			decideBody(_decideBody) {
		}

		HBlockMatch queryToMatch;
		CBlocking::HBlock decideBody;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockToDecideWhether; }
	};

	using HBlockToDecideWhether = std::shared_ptr<CBlockToDecideWhether>;




	class CBlockToDecideWhat  : public CBlockToDecide
	{
	public:
		CBlockToDecideWhat(HBlockMatch _queryToMatch, CBlocking::HBlock _decideBody)			: queryToMatch(_queryToMatch),
			decideBody(_decideBody) {
		}

		HBlockMatch queryToMatch;
		CBlocking::HBlock decideBody;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockToDecideWhat; }
	};

	using HBlockToDecideWhat = std::shared_ptr<CBlockToDecideWhat>;


	//First Noum .... Serve para identificar o primeiro Noum de uma sentenca com verbo no meio



	class CBlockToDecideWhat_FirstNoum  : public CBlockToDecide
	{
	public:
		CBlockToDecideWhat_FirstNoum(HBlockMatchIs _queryToMatch, CBlocking::HBlock _decideBody)
			: queryToMatch(_queryToMatch),
			decideBody(_decideBody) {
		}

		HBlockMatchIs queryToMatch;  //Obrigatorio ser um Query IS
		CBlocking::HBlock decideBody;

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockToDecideWhat_FirstNoum; }
	};

	using HBlockToDecideWhat_FirstNoum = std::shared_ptr<CBlockToDecideWhat_FirstNoum>;






	class CBlockToDecideOn : public CBlock  // bloco que equivale a um return no decide
	{
	public:
		CBlockToDecideOn(CBlocking::HBlock _decideBody) : decideBody(_decideBody) {
		}

		CBlocking::HBlock decideBody;

	 

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockToDecideOn; }
	};

	using HBlockToDecideOn = std::shared_ptr<CBlockToDecideOn>;








	//Pharses


	class CBlockPhraseHeader : public CBlock  // bloco que define o header de uma funcao .. nome e match dos argumentos
	{
	public:
		CBlockPhraseHeader(CBlocking::HBlockNoum _name , CBlocking::HBlockMatchList _matchPhase, CBlocking::HBlockMatchList _matchArguments) : name(_name), matchPhase(_matchPhase), matchArguments(_matchArguments)
		{
		}
		 
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockPhraseHeader; }

		CBlocking::HBlockNoum name;
		CBlocking::HBlockMatchList matchPhase;
		CBlocking::HBlockMatchList matchArguments;

	};

	using HBlockPhraseHeader = std::shared_ptr<CBlockPhraseHeader>;



	class CBlockPhraseDefine : public CBlock  // bloco que declara ao interpreter uma phase
	{
	public:
		CBlockPhraseDefine(CBlocking::HBlockPhraseHeader _header,   CBlocking::HBlock  _body) :  header(_header), body(_body){		}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockPhraseDefine; }

		 
		CBlocking::HBlockPhraseHeader  header;
		CBlocking::HBlock  body;

	};

	using HBlockPhraseDefine = std::shared_ptr<CBlockPhraseDefine>;


 

	class CBlockPhraseInvoke : public CBlock  // bloco que equivae a um routine call .. observe que name pode ser compount name para uma listagem de possiveis predicados
	{
	public:
		CBlockPhraseInvoke(CBlocking::HBlockNoum _name, CBlocking::HBlockList  _arguments ) : name(_name), arguments(_arguments)  {		}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockPhraseInvoke; }

		CBlocking::HBlockNoum name;
		CBlocking::HBlockList arguments;

	};

	using HBlockPhraseInvoke = std::shared_ptr<CBlockPhraseInvoke>;



	class CBlockRule : public CBlock  // bloco especifica uma regra
	{
	public:
		CBlockRule(CBlocking::HBlockNoum _rulename, CBlocking::HBlockNoum _rulebook, CBlocking::HBlockMatch _target, CBlocking::HBlock  _body) : rulename(_rulename), rulebook(_rulebook), target(_target), body(_body) {		}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockRule; }

		CBlocking::HBlockNoum rulename;
		CBlocking::HBlockNoum rulebook;
		CBlocking::HBlockMatch target;
		CBlocking::HBlock body;

	};

	using HBlockRule = std::shared_ptr<CBlockRule>;



	class CBlockRuleCall : public CBlock  // bloco especifica uma chamada de regra
	{
	public:
		CBlockRuleCall(CBlocking::HBlock _rulename,  CBlocking::HBlock  _argument) : rulename(_rulename), argument(_argument)  {		}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockRuleCall; }

		CBlocking::HBlock rulename;		
		CBlocking::HBlock argument;

	};

	using HBlockRuleCall = std::shared_ptr<CBlockRuleCall>;



}
