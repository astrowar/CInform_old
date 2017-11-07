#pragma once
#ifndef BLOCKInterpreter_H
#define BLOCKInterpreter_H

#include "CBase.hpp"




#include "BlockTypeEnum.hpp"

void logMessage(std::string str);
void logError(std::string str);
void logWarring(std::string str);
using std::string;


namespace CBlocking
{

	class CBlockEnums;

	class CBlock;

	class CBlockKind;

	class CBlockAssertion_is;

	using UBlock = CBlock *;

	//All CBlocks are constant in memory ... ALL ... because this is can be a ROM data 

	using HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;

	class NoumDefinition {
	public:
		string noum;
		CBlock *definition;
		NoumDefinition(string _noum, UBlock _definition) : noum(_noum), definition(_definition) {}
	};

	using NoumDefinitions = std::vector<NoumDefinition>;

	NoumDefinitions noum_nothing();


	NoumDefinitions join_definitions(NoumDefinitions a, NoumDefinitions b);





	class CBlock {

	public:
		virtual void dump(string ident)
		{
			printf("");
		};


		virtual BlockType type() = 0;
		virtual ~CBlock() {
		}

		 

		void *operator new(size_t size);

		 
		static bool isSame(CBlock* b1, CBlock* b2)  ;


		//template <class HArchive> static void load_and_construct(HArchive& ar, cereal::construct<CBlock>& construct);
	};

	using  HBlock = std::shared_ptr<CBlock>;



	class CUnresolved : public CBlock {
		void dump(string ident) override;

		CUnresolved(string _contents);

		virtual BlockType type() override { return BlockType::Unresolved; }

		string contents;

		 
	};
	using HUnresolved = std::shared_ptr<CUnresolved>;

	using UBlock = CBlock *;

	NoumDefinitions single_definitions(string noun, CBlock *block);



	class CBlockKind : public CBlock  //retorna um valor generico porem Abstrado
	{
	public:
		virtual bool isValue() = 0;
		//virtual BlockType type() override { return BlockType::BlockKind; }
		//CBlockKind( )  { }; // tipos agora nao tem nome de forma intrinsica
		//const string named; 
	};

	using HBlockKind = std::shared_ptr<CBlockKind>;



	// Representa toda as subclasses que sao valores
	class CBlockValue : public CBlock  //retorna um valor generico porem Abstrado
	{
	public:
		virtual bool isValue() { return true; }
		//virtual BlockType type() override { return BlockType::BlockKind; }
		CBlockValue( )   {};
		 
	};
	using HBlockValue = std::shared_ptr<CBlockValue>;



	class CBlockKindReference : public CBlockValue //retorna um valor generico uso apenas no interpreter
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockKindReference; }
		CBlockKindReference( HBlockKind k) :kind(k) {};
		const HBlockKind kind;
	};
	using HBlockKindReference = std::shared_ptr<CBlockKindReference>;




	class CBlockBooleanResult  : public CBlockValue  // um tipo de bloco que retorna true ou false
	{
	public:
		virtual ~CBlockBooleanResult() {
		}

		virtual bool result() = 0;
	};

	using HBlockBooleanResult = std::shared_ptr<CBlockBooleanResult>;

	class CBlockNoum : public CBlock //retorna um valor generico
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockNoum; }

		CBlockNoum() {};
		CBlockNoum(string _named);

		const string named;

		 
	};

	using HBlockNoum = std::shared_ptr<CBlockNoum>;

	 



    class CBlockKindNamed : public CBlockKind  //retorna um tipo que deve ser resolvido em runtime
    {
    public:
      virtual  void dump(string ident) override;
      virtual bool isValue() override { return false; }

        BlockType type() override { return BlockType::BlockKindNamed; }
		string named;
        explicit CBlockKindNamed(string _named) : named(std::move(_named)) {};
    };

    using HBlockKindNamed = std::shared_ptr<CBlockKindNamed>;

	class CBlockNothing : public CBlock  //retorna um valor generico porem Abstrado
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockNothing; }
		CBlockNothing(string _named) : named(_named) {};
		const string named;
	};

	using HBlockNothing = std::shared_ptr<CBlockNothing>;


	class CBlockAnything : public CBlock  //retorna um valor generico porem Abstrado
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAnything; }
		CBlockAnything(string _named) : named(_named) {};
		const string named;
	};

	using HBlockAnything = std::shared_ptr<CBlockAnything>;
	



	class CBlockKindOfName : public CBlock  //Define uma classe derivada de outra
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockKindOfName; }

		CBlockKindOfName(string _baseClasseName) : baseClasseName(_baseClasseName) {};
		string baseClasseName;
	};

	using HBlockKindOfName = std::shared_ptr<CBlockKindOfName>;

	class CBlockKindOf : public CBlock  //Define uma classe derivada de outra
	{
	public:
		void dump(string ident) override;

		virtual BlockType type() override { return BlockType::BlockKindOf; }
		CBlockKindOf(HBlockKind _baseClasse) : baseClasse(_baseClasse) {} 

		HBlockKind baseClasse;
	};

	using HBlockKindOf = std::shared_ptr<CBlockKindOf>;


	 

	class CBlockActionApply : public CBlock {
	public:
		virtual void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockActionApply; }
		 HBlock noum1;
		 HBlock noum2;

		CBlockActionApply(HBlock _noum1, HBlock _noum2);
	};

	using HBlockActionApply = std::shared_ptr<CBlockActionApply>;


	class CBlockKindAction : public CBlockKind  //Define uma tipo de acao derivada
	{
	public:
		void dump(string ident) override;
		virtual bool isValue() override { return true; }
		virtual BlockType type() override { return BlockType::BlockKindAction; }
		CBlockKindAction(  HBlockActionApply _applyTo) :   applyTo(_applyTo) {} 
		 
		HBlockActionApply applyTo;
	};

	using HBlockKindAction = std::shared_ptr<CBlockKindAction>;

	class CBlockKindValue : public CBlockKind // retorna um valor generico que pertence a uma classe de valor
	{
	public:
		virtual bool isValue() override { return true; } 
		void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockKindValue; } 
		string named;
		CBlockKindValue(string _named);
	};

	using HBlockKindValue = std::shared_ptr<CBlockKindValue>;

	class CBlockKindEntity : public CBlockKind //retorna um valor generico
	{
	public:
		virtual bool isValue() override { return true; }
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockKindEntity; }
		string named;
		CBlockKindEntity(string _named) : named(_named) {}
	 
	};
	using HBlockKindEntity = std::shared_ptr<CBlockKindEntity>;


	// Obsoleto , Use Composite
	//class CBlockListOfKind : public CBlockKind // algo como List<Kind> 
	//{
	//public:
	//	virtual bool isValue() override { return true; }
	//	void dump(string ident) override;
	//	virtual BlockType type() override { return BlockType::BlockListOfKind; }
	//	CBlockListOfKind(HBlockKind _itemKind) : CBlockKind("list@" + _itemKind->named), itemKind(_itemKind) {}
	//	HBlockKind itemKind;
	//	virtual NoumDefinitions noumDefinitions() override { return single_definitions("list@" + itemKind->named, this); };
	//};
	//using HBlockListOfKind = std::shared_ptr<CBlockListOfKind>;




	class CBlockNamedValue : public CBlockValue //named value eh um noum que eh representa seu proprio valor ... red, blue, opaque ...
	{
	public:
		virtual void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockNamedValue; } 
		CBlockNamedValue(string _named); 
		string named; 
	}; 
	using HBlockNamedValue = std::shared_ptr<CBlockNamedValue>;



 



	class  CBlockProperty : public CBlock //referencia de uma propriedade de algum objeto
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockProperty; }
		CBlockProperty(HBlock _prop, HBlock _obj);
		HBlock prop;
		HBlock obj;
	};
	using HBlockProperty = std::shared_ptr<CBlockProperty>;


	//?????
	class CBlockInstanceVariable : public CBlock //retorna um valor generico
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockInstanceVariable; }
		CBlockInstanceVariable(HBlockNoum _kind_name, HBlockNoum _property_name);
		HBlockNoum property_name;
		HBlockNoum kind_name;
	};
	using HBlockInstanceVariable = std::shared_ptr<CBlockInstanceVariable>;




	class CBlockKind_InstanceVariable : public CBlock 
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockKind_InstanceVariable; }
		CBlockKind_InstanceVariable(HBlockKind  _kind, HBlockInstanceVariable _variableNamed) :kind(_kind), variableNamed(_variableNamed) {}
		HBlockKind kind;
		HBlockInstanceVariable variableNamed;
	};
	using HBlockKind_InstanceVariable = std::shared_ptr<CBlockKind_InstanceVariable>;






	class CBlockList : public CBlock //Lista generica, sem tipo associado
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockList; }
		std::list<HBlock> lista;
		CBlockList(std::list<HBlock>  _lista) :lista(_lista) {}
		void push_back(HBlock c_block_value);
		 
	};
	using HBlockList = std::shared_ptr<CBlockList>;



	class CBlockList_OR : public CBlockList // lista de termos OU
	{ 
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockList_OR; }
		CBlockList_OR(std::list<HBlock>  _lista)
			: CBlockList(_lista)
		{
		}
	};
	using HBlockList_OR = std::shared_ptr<CBlockList_OR>;


	class CBlockList_AND : public CBlockList //Lista de termos AND
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockList_AND ; }
		CBlockList_AND(std::list<HBlock>  _lista)
			: CBlockList(_lista)
		{
		}
	};
	using HBlockList_AND = std::shared_ptr<CBlockList_AND>;




	class CBlockEnums : public CBlock // definicao de valores enumerados
	{
	public:
		std::vector<HBlockNoum> values;
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockEnums; }
		CBlockEnums(std::vector<HBlockNoum> _values);
		bool contains(string cs);
		string value_x;
	};
	using HBlockEnums = std::shared_ptr<CBlockEnums>;

	 

	class CBlockVerbRelation : public CBlock    // Abstract , define uma relacao
	{
	public:
		HBlock  verbNoum; // Pode ser simples ou com a preposicao
		HBlockNoum relationNoum;
		CBlockVerbRelation(HBlock  _noum, HBlockNoum _relationNoum) : verbNoum((_noum)), relationNoum((_relationNoum)) {};
	};
	using HBlockVerbRelation = std::shared_ptr<CBlockVerbRelation>;



	class CBlockVerbDirectRelation : public CBlockVerbRelation    //retorna uma declaracao
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerbDirectRelation; }
		CBlockVerbDirectRelation(HBlock  _noum, HBlockNoum _relationNoum) : CBlockVerbRelation(_noum, _relationNoum) {};
	};
	using HBlockVerbDirectRelation = std::shared_ptr<CBlockVerbDirectRelation>;




	class CBlockVerbReverseRelation : public CBlockVerbRelation    //retorna uma declaracao
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerbReverseRelation; }
		CBlockVerbReverseRelation(HBlock  _noum, HBlockNoum _relationNoum) : CBlockVerbRelation(_noum, _relationNoum) {};
	};
	using HBlockVerbReverseRelation = std::shared_ptr<CBlockVerbReverseRelation>;







	string HtoStringList(HBlockList lst);
	string HtoString(HBlock value);




	//===================================================================
	class CBlockFilter : public CBlock   // filtra um valor para outro valor
	{
		 
	};


	class CBlockFilterAtom : public CBlockFilter {
		explicit CBlockFilterAtom(HBlock input)
			: input(input) {
		}
		HBlock input;	 
	};

	class CBlockFilterList : public CBlockFilter 
	{
		HBlockList input;	 
	};










	//Dynamic Dispatch dispacha para TODOS os undestands possiveis
	class CBlockDinamicDispatch : public CBlock {
	public:

		HBlockList  commandList;
		//    CBlockDinamicDispatch(string _command) : CBlockAction(  std::make_shared<CBlockNoum>(_command)), command(_command) {}
		CBlockDinamicDispatch(HBlockList _command) : commandList(_command) {}
		void dump(string ident) override;

		virtual BlockType type() override { return BlockType::BlockDinamicDispatch; }
	};
	using HBlockDinamicDispatch = std::shared_ptr<CBlockDinamicDispatch>;


	class CBlockTransform : public CBlock  // um bloco que trasnforma um valor em outro
	{
		explicit CBlockTransform(HBlock input)
			: input(input) {
		}
		HBlock input;
	};


	class CBlockIF : public CBlock  // um bloco do tipo if then else
	{
		CBlockIF(HBlockBooleanResult input_if, HBlock input_then, HBlock input_else)
			: input_if(input_if),
			input_then(input_then),
			input_else(input_else) {
		}

		HBlockBooleanResult input_if; // o if tem que set True ou False
		HBlock input_then;
		HBlock input_else;
	};

	class CBlockSame : public   CBlockBooleanResult  // um bloco do tipo if then else
	{
		CBlockSame(HBlock input_a, HBlock input_b)
			: input_A(input_a),
			input_B(input_b) {
		}
		HBlock input_A;
		HBlock input_B;
	};


	//class CBlockProp : public CBlock  // um bloco que especifica uma propiedade ( color OF book ) -> ( prop OF what )
	//{
	//	CBlockProp(HBlock what, HBlock prop)
	//		: what(what),
	//		prop(prop) {
	//	}
	//	HBlock what;
	//	HBlock prop;
	//};
	//using HBlockProp = std::shared_ptr<CBlockProp>;



	//===========================================
	// Verbos e suas conjugacoes 

	class CBlockVerbConjugation : public CBlock //retorna uma declaracao
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerbConjugation; }
		string word;
		string tense; //tense string based on language

		CBlockVerbConjugation(string _word, string _tense) :word(_word), tense(_tense) {};
	};
	using HBlockVerbConjugation = std::shared_ptr<CBlockVerbConjugation>;


	class CBlockVerb : public CBlock //retorna uma declaracao
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerb; }
		string named;
		std::list<HBlockVerbConjugation> conjugations;
		CBlockVerb(string _named, std::list<HBlockVerbConjugation> _conjugations) :named(_named), conjugations(_conjugations) {};
	};
	using HBlockVerb = std::shared_ptr<CBlockVerb>;



	class CBlockVerbAdapt : public CBlock //retorna uma declaracao
	{
	public:
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockVerbAdapt; }
		string verb;
		string tense;
		string viewPoint;
		CBlockVerbAdapt(string _verb, string _tense, string _viewPoint) :verb(_verb), tense(_tense), viewPoint(_viewPoint) {};
	};
	using HBlockVerbAdapt = std::shared_ptr<CBlockVerbAdapt>;



	//===========================================


	class CBlockSelector : public CBlock // Grmatical 
	{
	public:
		HBlock what;
		CBlockSelector(HBlock _what) :what(_what) {};
	};
	using HBlockSelector = std::shared_ptr<CBlockSelector>;



	class CBlockSelector_All : public CBlockSelector //retorna uma declaracao
	{
	public:
		void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockSelector_All; }
		CBlockSelector_All(HBlock _what) :CBlockSelector(_what) {}
	};
	using HBlockSelector_All = std::shared_ptr<CBlockSelector_All>;




	class CBlockSelector_Any : public CBlockSelector //retorna uma declaracao
	{
	public:
		void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockSelector_Any; }
		CBlockSelector_Any(HBlock _what) :CBlockSelector(_what) {}
	};
	using HBlockSelector_Any = std::shared_ptr<CBlockSelector_Any>;






	class CBlockSelector_Where : public CBlockSelector //retorna uma declaracao
	{
	public:
		void dump(string ident) override; 
		virtual BlockType type() override { return BlockType::BlockSelector_Where; }
		CBlockSelector_Where(HBlock _what) :CBlockSelector(_what) {}
	};
	using HBlockSelector_Where = std::shared_ptr<CBlockSelector_Where>;


}

#endif
