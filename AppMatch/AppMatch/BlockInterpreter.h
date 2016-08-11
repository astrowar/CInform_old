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
	  CBlock* applyTo;
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
	CBlockProperty(CBlock *prop, CBlock *b);
	CBlock* prop;
	CBlock* obj;
	 
}; 


class  CBlockInstanceVariable : public CBlock //retorna um valor generico 
{
public:
	void dump(std::string ident) override;
	CBlockInstanceVariable(CBlock* _kind_name, CBlock* _called);
	CBlock* property_name;
	CBlock* kind_name;
	 
};




class CBlockList : public CBlock //retorna um valor generico 
{
public:
	virtual void  dump(std::string  ident) override;
	std::list<CBlock*> lista;
	void push_back(CBlock* c_block_value);
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
	CBlock* obj;
	//CBlockAssertion(HTerm obj, HTerm thing){};	
	CBlockAssertionBase(CBlock* _obj): obj(_obj) {};
	virtual NoumDefinitions noumDefinitions() override { return obj->noumDefinitions(); };
};


class CBlockAssertion_is : public CBlockAssertionBase //retorna uma declaracao 
{
public:
	void dump(std::string ident) override;

	CBlock* definition;
	//CBlockAssertion(HTerm obj, HTerm thing){};	
	CBlockAssertion_is(CBlock* _obj,   CBlock * _definition ) :CBlockAssertionBase(_obj), definition(_definition) {};
 
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

	CBlockKind * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isKindOf(CBlockKind* _noum, CBlockKind * _baseKind) :CBlockAssertion_is(_noum, _baseKind), noum(_noum) , baseKind(_baseKind){};
};


class CBlockAssertion_isInstanceOf : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlockInstance * noum;
	CBlockKind * baseKind;
	CBlockAssertion_isInstanceOf(CBlockInstance* _noum, CBlockKind * _baseKind) :CBlockAssertion_is(_noum, _baseKind), noum(_noum), baseKind(_baseKind) {};
};


class CBlockAssertion_isNamedValueOf : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock * noum;
	CBlock * baseKind;
	CBlockAssertion_isNamedValueOf(CBlock * _noum, CBlock * _baseKind) :CBlockAssertion_is(_noum, _baseKind), noum(_noum), baseKind(_baseKind) {};
};


 
class CBlockAssertion_isVariable : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * baseKind;
	CBlockAssertion_isVariable(CBlock  * _variable, CBlock  * _baseKind) :CBlockAssertion_is(_variable, _baseKind), variable(_variable), baseKind(_baseKind) {};
};







 
class CBlockAssertion_isDefaultAssign : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * value;
	CBlockAssertion_isDefaultAssign(CBlock * _variable, CBlock * _value) :CBlockAssertion_is(_variable, _value), variable(_variable), value(_value) {};
};

class CBlockAssertion_isConstantAssign : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * value;
	CBlockAssertion_isConstantAssign(CBlock * _variable, CBlock * _value) :CBlockAssertion_is(_variable, _value), variable(_variable), value(_value) {};
};


class CBlockAssertion_isForbiddenAssign : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * value;
	CBlockAssertion_isForbiddenAssign(CBlock * _variable, CBlock * _value) :CBlockAssertion_is(_variable, _value), variable(_variable), value(_value) {};
};

class CBlockAssertion_isDirectAssign : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * value;
	CBlockAssertion_isDirectAssign(CBlock * _variable, CBlock * _value) :CBlockAssertion_is(_variable, _value), variable(_variable), value(_value) {};
};

class CBlockAssertion_isNotDirectAssign : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * variable;
	CBlock  * value;
	CBlockAssertion_isNotDirectAssign(CBlock * _variable, CBlock * _value) :CBlockAssertion_is(_variable, _value), variable(_variable), value(_value) {};
};



class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock  * noum;
	CBlockInstanceVariable *  instance_variable;
	CBlockAssertion_InstanceVariable(CBlock* _noum,  CBlockInstanceVariable * _instance_variable) :  noum(_noum), instance_variable(_instance_variable) {};
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
	CBlock*  n1;
	CBlock*  n2;
	CBlockIsVerb(std::string _verb, CBlock* _n1, CBlock * _n2) : verb(_verb), n1(_n1), n2(_n2) {};
};

class CBlockIsNotVerb : public CBlock    //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	string verb;
	CBlock*  n1;
	CBlock*  n2;
	CBlockIsNotVerb(std::string _verb, CBlock* _n1, CBlock * _n2) : verb(_verb), n1(_n1), n2(_n2) {};
};
 
class CBlockVerbRelation : public CBlock    //retorna uma declaracao 
{
public:
	virtual void dump(std::string ident) override;

	CBlock* verbNoum; // Pode ser simples ou com a preposicao
	CBlock*  relation;
	CBlockVerbRelation(CBlock* _noum, CBlock * _relation) : verbNoum(_noum), relation(_relation) {};
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
	void dump(std::string ident) override;
	// CBlockMatc(CBlockKind("book")) -> filtra kinds do tipo block 
	// CBlockMatc("reward for (victim - a person)") -> filtra aquery reward of XXX, sendo XXX uma instancia de Person, tageado como "victim"
	virtual bool  match() { return false; };
	CBlock* matchInner;
	CBlockMatch(CBlock* _matchInner  ): matchInner(_matchInner)
	{};
};


 



class CBlockMatchWith : public  CBlockMatch // um bloco que serve para dar Match  no match anterior
{
	CBlockMatch* previous_match; 
};




class CBlockActionApply: public  CBlock
{
public:
	void dump(std::string ident) override;
	CBlock* noum1;
	CBlock* noum2;
	CBlockActionApply(CBlock* _noum1, CBlock* _noum2 ); 
};


class CBlockAction : public  CBlock  // um bloco que representa uma atividade
{
public:
	void dump(std::string ident) override;

	CBlockAction(CBlock* input)
		: input(input)
	{
	}

	CBlock* input;
};


class CBlockAssertion_isActionOf : public CBlockAssertion_is //retorna uma declaracao 
{
public:
	void dump(std::string ident) override;

	CBlockNoum* noum;
	CBlockAction* action;
	CBlockActionApply* application;
	CBlockAssertion_isActionOf(CBlockNoum* _noum, CBlockAction * _action , CBlockActionApply* _application) :CBlockAssertion_is(_noum, _action), noum(_noum), action(_action), application(_application) {};
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

 