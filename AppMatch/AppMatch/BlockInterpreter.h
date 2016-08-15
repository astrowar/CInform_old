#pragma once
#include "CBase.h"
#include <cassert>

using std::string;
class CBlock;
class CBlockKind;






class NoumDefinition
{
public:
	string noum;
	CBlock* definition;
	NoumDefinition(string _noum, CBlock* _definition) : noum(_noum), definition(_definition)
	{}
};

using NoumDefinitions = std::vector<NoumDefinition>;

NoumDefinitions noum_nothing();

NoumDefinitions single_definitions(string noun, CBlock* block);

NoumDefinitions join_definitions(NoumDefinitions a, NoumDefinitions b);





class CBlock
{

public:
	virtual void dump(std::string  ident  ) = 0;

	virtual ~CBlock()
	{
	}
	virtual NoumDefinitions noumDefinitions() {return  noum_nothing( );  };
};

class CUnresolved : public CBlock
{
	void dump(std::string ident) override;
	  CUnresolved(string named);
	string contents;
	virtual NoumDefinitions noumDefinitions() override
	{
		return noum_nothing();  // define nada
	};
};


using UBlock = std::unique_ptr<CBlock>;


class CBlockBooleanResult   // um tipo de bloco que retorna true ou false
{
public:
	virtual ~CBlockBooleanResult()
	{
	}

	virtual bool result() = 0;
};



class CBlockNoum : public CBlock //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockNoum(string named);
	string named;
	virtual NoumDefinitions noumDefinitions() override
	{ return single_definitions(named,this); };
};






class CBlockKind : public CBlock  //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockKind(string _named) :named(_named) {   };
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};


class CBlockKindOf : public CBlock  //Define uma classe derivada de outra
{
public:
	void dump(std::string ident) override;
	CBlockKindOf(string _baseClasseName) :baseClasseName(_baseClasseName) {   };
	string baseClasseName;
};


class CBlockActionKind : public CBlock  //Define uma tipo de acao   derivada
{
public:
	void dump(std::string ident) override;
	CBlockActionKind(string _baseActionName , CBlock* _applyTo ) :baseClasseName(_baseActionName), applyTo(_applyTo)
	{   };
	string baseClasseName;
	UBlock applyTo;
};

class CBlockKindValue : public CBlockKind //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockKindValue(string _named) :CBlockKind(_named) {   };
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};



class CBlockInstance : public CBlock //retorna um valor generico
{
public:
	virtual void dump(std::string ident) override;
	CBlockInstance(string _named  );
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};


class CBlockNamedValue : public CBlock //retorna um valor generico
{
public:
	virtual void dump(std::string ident) override;
	CBlockNamedValue(string _named);
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};

class CBlockVariable : public CBlock //retorna um valor generico
{
public:
	virtual void dump(std::string ident) override;
	CBlockVariable(string _named);
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};



class CBlockProperty : public CBlock //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockProperty(UBlock prop, UBlock b);
	UBlock prop;
	UBlock obj;

};


class  CBlockInstanceVariable : public CBlock //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockInstanceVariable(UBlock _kind_name, UBlock _called);
	UBlock property_name;
	UBlock kind_name;

};




class CBlockList : public CBlock //retorna um valor generico
{
public:
	virtual void  dump(std::string  ident) override;
	std::list<UBlock> lista;
	void push_back(UBlock c_block_value);
	virtual NoumDefinitions noumDefinitions() override;

};
class CBlockEnums : public CBlock //retorna um valor generico
{
public:
	std::vector<CBlockNoum*> values;
	virtual void dump(std::string ident) override;
	  CBlockEnums(std::vector<CBlockNoum*>  _values);
	string value;
};


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
	virtual void dump(std::string ident) override;
	CBlockEnums* definition;
	//CBlockAssertion(HTerm obj, HTerm thing){};
	CBlockAssertion_canBe(CBlock* _obj, CBlockEnums* _definition);;
};



class CBlockAssertion_isKindOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	NoumDefinitions noumDefinitions() override;
	void dump(std::string ident) override;

	virtual CBlock* get_definition()   { return baseKind ; };

	CBlockKind * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isKindOf(CBlockKind* _noum, CBlockKind * _baseKind) :  noum(_noum) , baseKind(_baseKind){};
};


class CBlockAssertion_isInstanceOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	CBlockInstance * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isInstanceOf(CBlockInstance* _noum, CBlockKind * _baseKind) :  noum(_noum), baseKind(_baseKind) {};
};


class CBlockAssertion_isNamedValueOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock noum;
	UBlock baseKind;
	CBlockAssertion_isNamedValueOf(UBlock _noum, UBlock _baseKind) : noum(std::move(_noum))  , baseKind(std::move(_baseKind)) {};
};



class CBlockAssertion_isVariable : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock baseKind;
	CBlockAssertion_isVariable(UBlock _variable, UBlock _baseKind) :  variable(std::move(_variable)), baseKind(std::move(_baseKind)) {};
};








class CBlockAssertion_isDefaultAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isDefaultAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};

class CBlockAssertion_isConstantAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock   variable;
	UBlock   value;
	CBlockAssertion_isConstantAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};


class CBlockAssertion_isForbiddenAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isForbiddenAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value))  {};
};

class CBlockAssertion_isDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isDirectAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};

class CBlockAssertion_isNotDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock variable;
	UBlock value;
	CBlockAssertion_isNotDirectAssign(UBlock _variable, UBlock _value) :  variable(std::move(_variable)), value(std::move(_value)) {};
};



class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock noum;
	CBlockInstanceVariable *  instance_variable;
	CBlockAssertion_InstanceVariable(UBlock _noum,  CBlockInstanceVariable * _instance_variable) :  noum(std::move(_noum)), instance_variable(_instance_variable) {};
};


class CBlockAssertionCond: public CBlock // assertion com condicao
{	public:
	CBlockBooleanResult* cond;
};


class CBlockIsVerb : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	string verb;
	UBlock  n1;
	UBlock  n2;
	CBlockIsVerb(std::string _verb, UBlock _n1, UBlock _n2) : verb((_verb)), n1(std::move(_n1)), n2(std::move(_n2)) {};
};

class CBlockIsNotVerb : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	string verb;
	UBlock  n1;
	UBlock  n2;
	CBlockIsNotVerb(std::string _verb, UBlock _n1, UBlock _n2) : verb(_verb), n1(std::move(_n1)), n2(std::move(_n2)) {};
};

class CBlockVerbRelation : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock verbNoum; // Pode ser simples ou com a preposicao
	UBlock  relation;
	CBlockVerbRelation(UBlock _noum, UBlock _relation) : verbNoum(std::move(_noum)), relation(std::move(_relation)) {};
};

class CBlockMatch;

class CBlockUnderstand : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	CBlockMatch * input_n; // Pode ser simples ou com a preposicao
	UBlock output_n;
	CBlockUnderstand(CBlockMatch * _input_n, UBlock _output_n) : input_n(_input_n), output_n(std::move(_output_n)) {};
};

class CBlockMatchList;
class CBlockUnderstandStatic : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	CBlockMatchList * argument_match; // Pode ser simples ou com a preposicao
	UBlock output_n;
	CBlockUnderstandStatic(CBlockMatchList * _argument_match, UBlock _output_n) : argument_match(_argument_match), output_n(std::move(_output_n)) {};
};



//===================================================================
class CBlockFilter: public CBlock   // filtra um valor para outro valor
{
	virtual HTerm  filter() = 0;
};


class CBlockFilterAtom: public  CBlockFilter
{
	explicit CBlockFilterAtom(CBlock* input)
		: input(input)
	{
	}

	CBlock* input;
	virtual bool filter(HTerm input)  ;
};

class CBlockFilterList : public  CBlockFilter
{
	CBlockList* input;
	virtual bool filter(HTerm input)  ;
};



class CBlockMatch : public  CBlock // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() { return false; };
	CBlock* matchInner;
	CBlockMatch(CBlock* _matchInner  ): matchInner(_matchInner)
	{};
};

class CBlockMatchAny : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() { return true; };

	CBlockMatchAny( ) : CBlockMatch(nullptr)
	{};
};



class CBlockMatchNamed : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	virtual bool match() override;;
	std::string named;
	CBlockMatch* matchInner;

	CBlockMatchNamed(std::string _named, CBlockMatch* _matchInner) :  CBlockMatch(nullptr),named(_named), matchInner(_matchInner)
	{};
};



class CBlockMatchKind : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;
	// CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block
	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() override
	{ return false; };
	CBlockKind* kind;
	CBlockMatchKind(CBlockKind* _kindInnter) : CBlockMatch(nullptr), kind(_kindInnter)
	{};
};


class CBlockMatchWith : public  CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatch* previous_match;
};


class CBlockMatchList : public  CBlockMatch // um bloco que serve para dar Match em um value , retorna true ou false se for Aplicavel
{
public:
	virtual void dump(std::string ident) override;

	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() override
	{ return false; };
	std::list<CBlockMatch*>  matchList;
	CBlockMatchList(std::list<CBlockMatch*> _matchList) : CBlockMatch(nullptr), matchList(_matchList)
	{};
};



class CBlockActionApply: public  CBlock
{
public:
	virtual void dump(std::string ident) override;
	CBlock* noum1;
	CBlock* noum2;
	CBlockActionApply(CBlock* _noum1, CBlock* _noum2 );
};


class CBlockAction : public  CBlock  // um bloco que representa uma atividade
{
public:
	virtual void dump(std::string ident) override;

	CBlockAction(CBlock* input)
		: input(input)
	{
	}

	CBlock* input;
};


class CBlockActionCall : public  CBlock
{
public :
	CBlockAction *action;
	CBlock *noum1;
	CBlock *noum2;
	CBlockActionCall(CBlockAction* _action, CBlock* _noum1, CBlock* _noum2):action(_action), noum1(_noum1), noum2(_noum2){}
	void dump(std::string ident) override;
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



//  eating something in the presence of Lady Bracknell
class CBlockMatchAction : public  CBlockMatch // um bloco que serve para dar Match em uma Acao
{
public :
	  CBlockMatchAction(CBlockAction* input)
		: CBlockMatch(input), input(input)
	{
	}

	CBlockAction* input;
};





class CBlockDinamicDispatch : public  CBlockAction
{
public:

	string  command;
	CBlockDinamicDispatch( string _command ) : CBlockAction(  new CBlockNoum(_command) ), command(_command)  {}
	void dump(std::string ident) override;
};


class CBlockStaticDispatch : public  CBlockAction
{
public:
	int staticEntryTable;
	CBlock *noum1;
	CBlock *noum2;
	CBlockStaticDispatch(int _staticEntryTable,   CBlock* _noum1, CBlock* _noum2) : CBlockAction(new CBlockNoum("static "+ std::to_string( _staticEntryTable) )), staticEntryTable(_staticEntryTable),  noum1(_noum1), noum2(_noum2) {}
	void dump(std::string ident) override;
};



class CBlockTransform  : public  CBlock  // um bloco que trasnforma um valor em outro
{
	explicit CBlockTransform(CBlock* input)
		: input(input)
	{
	}

	CBlock* input;
	virtual HTerm transform() = 0 ;
};





class CBlockIF : public  CBlock  // um bloco do tipo if then else
{
	CBlockIF(CBlockBooleanResult* input_if, CBlock* input_then, CBlock* input_else)
		: input_if(input_if),
		  input_then(input_then),
		  input_else(input_else)
	{
	}

	CBlockBooleanResult* input_if; // o if tem que set True ou False
	CBlock* input_then;
	CBlock* input_else;
	virtual HTerm eval() = 0;
};

class CBlockSame : public  CBlock, CBlockBooleanResult  // um bloco do tipo if then else
{
	CBlockSame(CBlock* input_a, CBlock* input_b)
		: input_A(input_a),
		  input_B(input_b)
	{
	}

	CBlock* input_A;
	CBlock* input_B;
};

class CBlockProp : public  CBlock  // um bloco que especifica uma propiedade ( color OF book ) -> ( prop OF what )
{
	CBlockProp(CBlock* what, CBlock* prop)
		: what(what),
		  prop(prop)
	{
	}

	CBlock* what;
	CBlock* prop;
	virtual HTerm eval() = 0;
};

class CBlockToDecide : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockToDecide(  CBlock* _queryToMatch, CBlock* _decideBody)
		:   queryToMatch(_queryToMatch),
		decideBody(_decideBody)
	{
	}
	CBlock* queryToMatch;
	CBlock* decideBody;
	virtual HTerm eval() { return nullptr; }
   void dump(std::string ident) override;
};


class CBlockToDecideIf : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockToDecideIf(CBlock* _queryToMatch, CBlock* _decideBody)
		: queryToMatch(_queryToMatch),
		decideBody(_decideBody)
	{
	}
	CBlock* queryToMatch;
	CBlock* decideBody;
	virtual HTerm eval() { return nullptr; }
	void dump(std::string ident) override;
};


class CBlockBooleanAND : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanAND(CBlock* input_a, CBlock* input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	CBlock* input_A;
	CBlock* input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanOR : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanOR(CBlock* input_a, CBlock* input_b)
		: input_A(input_a),
		input_B(input_b)
	{
	}

	CBlock* input_A;
	CBlock* input_B;
	void dump(std::string ident) override;
};

class CBlockBooleanNOT : public  CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
	CBlockBooleanNOT(CBlock* input_a )
		: input_A(input_a) {}

	CBlock* input_A;

	void dump(std::string ident) override;
};


class CBlockInterpreter
{
	std::vector<CBlockInstance*> instancias;
	std::vector<CBlockInstanceVariable*> instancias_vars;
	std::vector<CBlockAssertionBase*>    assertions_functional; //To define and others


	std::vector<NoumDefinition> nregisters;
	std::vector<CBlockAssertionBase*> assertions;
	std::vector<CBlockAssertionBase*> dynamic_assertions;

public:
	CBlockInterpreter();
	~CBlockInterpreter();


	CBlockKind* getKindOf(CBlockInstance* obj);

	QueryResul query_is_same(CBlock* c_block, CBlock* c_block1);
	QueryResul query_is(CBlock* c_block, CBlock* c_block1);
	QueryResul query(CBlockAssertion_is* base, CBlockAssertion_is* q);
	QueryResul query(CBlockAssertion_is* query);
	HTerm executeAssertion_is(CBlockAssertion_is* b);
	HTerm executeAssertion(CBlockAssertionBase* b);
	HTerm execute(CBlock *b);
	CBlock* resolve(CTerm  *b);
	CBlock* resolve_of(CBlock  *b , CBlock *a);
};



 