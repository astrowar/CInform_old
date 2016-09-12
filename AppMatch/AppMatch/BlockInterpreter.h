#pragma once
#ifndef BLOCKInterpreter_H
#define BLOCKInterpreter_H

#include "CBase.h"


class CBlockEnums;

using std::string;

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
    virtual void dump(string ident) = 0;

    virtual ~CBlock() {
    }

    virtual NoumDefinitions noumDefinitions() { return noum_nothing(); };

    void *operator new(size_t size);
};

using HBlock = std::shared_ptr<CBlock>;

class CUnresolved : public CBlock {
    void dump(string ident) override;

    CUnresolved(string named);

    string contents;

    virtual NoumDefinitions noumDefinitions() override {
        return noum_nothing();  // define nada
    };
};

using UBlock = CBlock *;

NoumDefinitions single_definitions(string noun, CBlock *block);


class CBlockBooleanResult   // um tipo de bloco que retorna true ou false
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

    CBlockNoum(string named);

    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};

using HBlockNoum = std::shared_ptr<CBlockNoum>;

class CBlockKind : public CBlock  //retorna um valor generico porem Abstrado
{
public:
    virtual bool isValue() = 0;

    CBlockKind(string _named) : named(_named) {};
    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};

using HBlockKind = std::shared_ptr<CBlockKind>;




class CBlockKindOfName : public CBlock  //Define uma classe derivada de outra
{
public:
    void dump(string ident) override;

    CBlockKindOfName(string _baseClasseName) : baseClasseName(_baseClasseName) {};
    string baseClasseName;
};

using HBlockKindOfName = std::shared_ptr<CBlockKindOfName>;

class CBlockKindOf : public CBlock  //Define uma classe derivada de outra
{
public:
    void dump(string ident) override;

    CBlockKindOf(HBlockKind _baseClasse) : baseClasse(_baseClasse) {};
    HBlockKind baseClasse;
};

using HBlockKindOf = std::shared_ptr<CBlockKindOf>;

class CBlockKindAction : public CBlock  //Define uma tipo de acao   derivada
{
public:
    void dump(string ident) override;

    CBlockKindAction(string _baseActionName, HBlock _applyTo) : baseClasseName(_baseActionName), applyTo(_applyTo) {};
    string baseClasseName;
    HBlock applyTo;
};

using HBlockKindAction = std::shared_ptr<CBlockKindAction>;

class CBlockKindValue : public CBlockKind //retorna um valor generico
{
public:
    virtual bool isValue() override { return true; }

    void dump(string ident) override;

    CBlockKindValue(string _named) : CBlockKind(_named) {};

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockKindValue = std::shared_ptr<CBlockKindValue>;

class CBlockKindThing : public CBlockKind //retorna um valor generico
{
public:
    virtual bool isValue() override { return true; }

    void dump(string ident) override;

    CBlockKindThing(string _named) : CBlockKind(_named) {};

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockKindThing = std::shared_ptr<CBlockKindThing>;



class CBlockListOfKind : public CBlockKind // algo como List<Kind> 
{
public:
	virtual bool isValue() override { return true; }

	void dump(string ident) override;

	CBlockListOfKind(HBlockKind _itemKind  ) : CBlockKind("list@"+ _itemKind->named) , itemKind(_itemKind){};
	HBlockKind itemKind;
	virtual NoumDefinitions noumDefinitions() override { return single_definitions("list@" + itemKind->named, this); };

};
using HBlockListOfKind = std::shared_ptr<CBlockListOfKind>;




class CBlockNamedValue : public CBlock //retorna um valor generico
{
public:
    virtual void dump(string ident) override;

    CBlockNamedValue(string _named);

    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};

using HBlockNamedValue = std::shared_ptr<CBlockNamedValue>;

class CBlockVariable : public CBlock //retorna um valor generico
{
public:
    virtual void dump(string ident) override;

    CBlockVariable(string _named);

    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockVariable = std::shared_ptr<CBlockVariable>;

class CBlockProperty : public CBlock //retorna um valor generico
{
public:
    void dump(string ident) override;

    CBlockProperty(HBlock prop, HBlock b);

    HBlock prop;
    HBlock obj;

};

using HBlockProperty = std::shared_ptr<CBlockProperty>;

class CBlockInstanceVariable : public CBlock //retorna um valor generico
{
public:
    void dump(string ident) override;

    CBlockInstanceVariable(HBlockNoum _kind_name, HBlockNoum _called);

    HBlockNoum property_name;
    HBlockNoum kind_name;

};

using HBlockInstanceVariable = std::shared_ptr<CBlockInstanceVariable>;





class CBlockKind_InstanceVariable : public CBlock //retorna um valor generico
{
public:
	void dump(string ident) override;
	CBlockKind_InstanceVariable(HBlockKind  _kind , HBlockInstanceVariable _variableNamed):variableNamed(_variableNamed), kind(_kind){}
	HBlockInstanceVariable variableNamed;
	HBlockKind kind;

};
using HBlockKind_InstanceVariable = std::shared_ptr<CBlockKind_InstanceVariable>;



class CBlockList : public CBlock //retorna um valor generico
{
public:
    virtual void dump(string ident) override;
    std::list<HBlock> lista;
    CBlockList(){}
    CBlockList( std::list<HBlock>  _lista ):lista(_lista) {}
    void push_back(HBlock c_block_value);
    virtual NoumDefinitions noumDefinitions() override;
};
using HBlockList = std::shared_ptr<CBlockList>;

class CBlockList_OR : public CBlockList //retorna um valor generico
{
public:
	virtual void dump(string ident) override;
	 
};
using HBlockList_OR = std::shared_ptr<CBlockList_OR>;




 








class CBlockEnums : public CBlock //retorna um valor generico
{
public:
    std::vector<HBlockNoum> values;

    virtual void dump(string ident) override;

    CBlockEnums(std::vector<HBlockNoum> _values);

    bool contains(string cs);

    string value_x;
};

using HBlockEnums = std::shared_ptr<CBlockEnums>;

class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(string ident) override;

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


 

class CBlockVerbRelation : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(string ident) override;

    HBlock  verbNoum; // Pode ser simples ou com a preposicao
    HBlockNoum relationNoum;

    CBlockVerbRelation(HBlock  _noum, HBlockNoum _relationNoum) : verbNoum((_noum)), relationNoum((_relationNoum)) {};
};
using HBlockVerbRelation = std::shared_ptr<CBlockVerbRelation>;



string HtoString(HBlockList lst);
string HtoString(HBlock value);

 


//===================================================================
class CBlockFilter : public CBlock   // filtra um valor para outro valor
{
    virtual HTerm filter() = 0;
};


class CBlockFilterAtom : public CBlockFilter {
    explicit CBlockFilterAtom(HBlock input)
            : input(input) {
    }

    HBlock input;

    virtual bool filter(HTerm input);
};

class CBlockFilterList : public CBlockFilter {

    HBlockList input;

    virtual bool filter(HTerm input);
};


class CBlockActionApply : public CBlock {
public:
    virtual void dump(string ident) override;

    HBlock noum1;
    HBlock noum2;

    CBlockActionApply(HBlock _noum1, HBlock _noum2);
};

using HBlockActionApply = std::shared_ptr<CBlockActionApply>;


 




//Dynamic Dispatch dispacha para TODOS os undestands possiveis
class CBlockDinamicDispatch : public CBlock {
public:

    HBlockList  commandList;
//    CBlockDinamicDispatch(string _command) : CBlockAction(  std::make_shared<CBlockNoum>(_command)), command(_command) {}
	CBlockDinamicDispatch(HBlockList _command) : commandList(_command) {}
    void dump(string ident) override;
};
using HBlockDinamicDispatch = std::shared_ptr<CBlockDinamicDispatch>;


class CBlockTransform : public CBlock  // um bloco que trasnforma um valor em outro
{
    explicit CBlockTransform(HBlock input)
            : input(input) {
    }

    HBlock input;

    virtual HTerm transform() = 0;
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

    virtual HTerm eval() = 0;
};

class CBlockSame : public CBlock, CBlockBooleanResult  // um bloco do tipo if then else
{
    CBlockSame(HBlock input_a, HBlock input_b)
            : input_A(input_a),
              input_B(input_b) {
    }

    HBlock input_A;
    HBlock input_B;
};

class CBlockProp : public CBlock  // um bloco que especifica uma propiedade ( color OF book ) -> ( prop OF what )
{
    CBlockProp(HBlock what, HBlock prop)
            : what(what),
              prop(prop) {
    }

    HBlock what;
    HBlock prop;

    virtual HTerm eval() = 0;
};

using HBlockProp = std::shared_ptr<CBlockProp>;


 

class CBlockVerb : public CBlock //retorna uma declaracao
{
public:
	void dump(string ident) override;
	string named;
private:
	CBlockVerb(string _named) :named(_named) {};
	 
};
using HBlockVerb = std::shared_ptr<CBlockVerb>;



//===========================================


class CBlockSelector : public CBlock //retorna uma declaracao
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
	CBlockSelector_All(HBlock _what) :CBlockSelector(_what) {}
};
using HBlockSelector_All = std::shared_ptr<CBlockSelector_All>;




class CBlockSelector_Any : public CBlockSelector //retorna uma declaracao
{
public:
	void dump(string ident) override;
	CBlockSelector_Any(HBlock _what) :CBlockSelector(_what) {}
};
using HBlockSelector_Any = std::shared_ptr<CBlockSelector_Any>;



#endif
