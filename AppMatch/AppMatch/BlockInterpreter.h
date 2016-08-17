#pragma once
#include "CBase.h"
#include <cassert>

class CBlockEnums;
using std::string;
class CBlock;
class CBlockKind;

using UBlock = CBlock*;




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

using UBlock = CBlock*;

 
NoumDefinitions single_definitions(string noun, UBlock block);


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






class CBlockKind : public CBlock  //retorna um valor generico porem Abstrado
{
public:
	virtual bool isValue() = 0;
	CBlockKind(string _named) :named(_named) {   };
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};


class CBlockKindOfName : public CBlock  //Define uma classe derivada de outra
{
public:
	void dump(std::string ident) override;
	CBlockKindOfName(string _baseClasseName) :baseClasseName(_baseClasseName) {   };
	string baseClasseName;
};

class CBlockKindOf  : public CBlock  //Define uma classe derivada de outra
{
public:
	void dump(std::string ident) override;
	CBlockKindOf (CBlockKind* _baseClasse) :baseClasse(_baseClasse) {   };
	CBlockKind* baseClasse ;
};

class CBlockKindAction : public CBlock  //Define uma tipo de acao   derivada
{
public:
	void dump(std::string ident) override;
	CBlockKindAction(string _baseActionName , CBlock* _applyTo ) :baseClasseName(_baseActionName), applyTo(_applyTo)
	{   };
	string baseClasseName;
	UBlock applyTo;
};

class CBlockKindValue : public CBlockKind //retorna um valor generico
{
public:
	virtual bool isValue() override { return true; }
	void dump(std::string ident) override;
	CBlockKindValue(string _named) :CBlockKind(_named) {   };
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

class CBlockKindThing : public CBlockKind //retorna um valor generico
{
public:
	virtual bool isValue() override { return true; }
	void dump(std::string ident) override;
	CBlockKindThing(string _named) :CBlockKind(_named) {   };
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};


class CVariableSlot
{
public:
	virtual ~CVariableSlot()
	{
	}
};

 

class CVariableSlotEnum : public CVariableSlot
{
public:
	CBlockNoum* value;
	CBlockEnums* valueDefinition;
	CVariableSlotEnum(CBlockEnums* enums);
};


class CVariableSlotBool : public CVariableSlot
{
public:
	bool value;
	CBlockNoum* valueDefinition;
	CVariableSlotBool(CBlockNoum* valueDef);
};

class CVariableNamed  
{
public:
	CBlock* value;
	CBlockKind* kind;
	CBlockNoum* name;
	 CVariableNamed(CBlockNoum* _name , CBlockKind* _kind , CBlock* _value );
};


class CBlockInstance : public CBlock //retorna um valor generico
{
public:
	virtual void dump(std::string ident) override;
	CBlockInstance(string _named  );
	void newEnumVariableSlot(CBlockEnums* definition);
	void newBoolVariableSlot(CBlockNoum* value);
	void newNamedVariable(CBlockNoum* called, CBlockKind *kind);

	void set(CBlockNoum* c_block);
	void unset(CBlockNoum* c_block);
	bool has_slot(CBlockNoum* value);
	CVariableNamed* get_property(string named);
	void set_property(string cs, UBlock value);
	QueryResul is_set(CBlockNoum* value);
	
	string named;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

	std::vector<CVariableSlot*> anomimousSlots;
	std::vector<CVariableNamed*> namedSlots;

};


class CBlockNamedValue : public CBlock //retorna um valor generico
{
public:
	virtual void dump(std::string ident) override;
	CBlockNamedValue(string _named  );
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
	CBlockInstanceVariable(CBlockNoum* _kind_name, CBlockNoum* _called);
	CBlockNoum* property_name;
	CBlockNoum* kind_name;

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
	bool contains(string cs);
	string value;
};



class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock noum;
	CBlockInstanceVariable *  instance_variable;
	CBlockAssertion_InstanceVariable(UBlock _noum,  CBlockInstanceVariable * _instance_variable) :  noum((_noum)), instance_variable(_instance_variable) {};
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
	CBlockIsVerb(std::string _verb, UBlock  _n1, UBlock  _n2) : verb((_verb)), n1((_n1)), n2((_n2)) {};
};

class CBlockIsNotVerb : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	string verb;
	UBlock  n1;
	UBlock  n2;
	CBlockIsNotVerb(std::string _verb, UBlock  _n1, UBlock  _n2) : verb(_verb), n1((_n1)), n2((_n2)) {};
};

class CBlockVerbRelation : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	UBlock verbNoum; // Pode ser simples ou com a preposicao
	UBlock  relation;
	CBlockVerbRelation(UBlock _noum, UBlock _relation) : verbNoum((_noum)), relation((_relation)) {};
};

class CBlockMatch;

class CBlockUnderstand : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	CBlockMatch * input_n; // Pode ser simples ou com a preposicao
	UBlock output_n;
	CBlockUnderstand(CBlockMatch * _input_n, UBlock _output_n) : input_n(_input_n), output_n((_output_n)) {};
};

class CBlockMatchList;
class CBlockUnderstandStatic : public CBlock    //retorna uma declaracao
{
public:
	virtual void dump(std::string ident) override;

	CBlockMatchList * argument_match; // Pode ser simples ou com a preposicao
	UBlock output_n;
	CBlockUnderstandStatic(CBlockMatchList * _argument_match, UBlock _output_n) : argument_match(_argument_match), output_n((_output_n)) {};
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




class CBlockActionApply: public  CBlock
{
public:
	virtual void dump(std::string ident) override;
	UBlock noum1;
	UBlock noum2;
	CBlockActionApply(UBlock  _noum1, UBlock  _noum2 );
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




