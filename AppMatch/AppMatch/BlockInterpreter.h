#pragma once

#include "CBase.h"
#include <cassert>
 

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
    virtual void dump(std::string ident) = 0;

    virtual ~CBlock() {
    }

    virtual NoumDefinitions noumDefinitions() { return noum_nothing(); };

    void *operator new(size_t size);
};

using HBlock = std::shared_ptr<CBlock>;

class CUnresolved : public CBlock {
    void dump(std::string ident) override;

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
    void dump(std::string ident) override;

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
    void dump(std::string ident) override;

    CBlockKindOfName(string _baseClasseName) : baseClasseName(_baseClasseName) {};
    string baseClasseName;
};

using HBlockKindOfName = std::shared_ptr<CBlockKindOfName>;

class CBlockKindOf : public CBlock  //Define uma classe derivada de outra
{
public:
    void dump(std::string ident) override;

    CBlockKindOf(HBlockKind _baseClasse) : baseClasse(_baseClasse) {};
    HBlockKind baseClasse;
};

using HBlockKindOf = std::shared_ptr<CBlockKindOf>;

class CBlockKindAction : public CBlock  //Define uma tipo de acao   derivada
{
public:
    void dump(std::string ident) override;

    CBlockKindAction(string _baseActionName, HBlock _applyTo) : baseClasseName(_baseActionName), applyTo(_applyTo) {};
    string baseClasseName;
    HBlock applyTo;
};

using HBlockKindAction = std::shared_ptr<CBlockKindAction>;

class CBlockKindValue : public CBlockKind //retorna um valor generico
{
public:
    virtual bool isValue() override { return true; }

    void dump(std::string ident) override;

    CBlockKindValue(string _named) : CBlockKind(_named) {};

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockKindValue = std::shared_ptr<CBlockKindValue>;

class CBlockKindThing : public CBlockKind //retorna um valor generico
{
public:
    virtual bool isValue() override { return true; }

    void dump(std::string ident) override;

    CBlockKindThing(string _named) : CBlockKind(_named) {};

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockKindThing = std::shared_ptr<CBlockKindThing>;

class CBlockNamedValue : public CBlock //retorna um valor generico
{
public:
    virtual void dump(std::string ident) override;

    CBlockNamedValue(string _named);

    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };
};

using HBlockNamedValue = std::shared_ptr<CBlockNamedValue>;

class CBlockVariable : public CBlock //retorna um valor generico
{
public:
    virtual void dump(std::string ident) override;

    CBlockVariable(string _named);

    string named;

    virtual NoumDefinitions noumDefinitions() override { return single_definitions(named, this); };

};

using HBlockVariable = std::shared_ptr<CBlockVariable>;

class CBlockProperty : public CBlock //retorna um valor generico
{
public:
    void dump(std::string ident) override;

    CBlockProperty(HBlock prop, HBlock b);

    HBlock prop;
    HBlock obj;

};

using HBlockProperty = std::shared_ptr<CBlockProperty>;

class CBlockInstanceVariable : public CBlock //retorna um valor generico
{
public:
    void dump(std::string ident) override;

    CBlockInstanceVariable(HBlockNoum _kind_name, HBlockNoum _called);

    HBlockNoum property_name;
    HBlockNoum kind_name;

};

using HBlockInstanceVariable = std::shared_ptr<CBlockInstanceVariable>;





class CBlockKind_InstanceVariable : public CBlock //retorna um valor generico
{
public:
	void dump(std::string ident) override;
	CBlockKind_InstanceVariable(HBlockKind  _kind , HBlockInstanceVariable _variableNamed):variableNamed(_variableNamed), kind(_kind){}
	HBlockInstanceVariable variableNamed;
	HBlockKind kind;

};
using HBlockKind_InstanceVariable = std::shared_ptr<CBlockKind_InstanceVariable>;



class CBlockList : public CBlock //retorna um valor generico
{
public:
    virtual void dump(std::string ident) override;

    std::list<HBlock> lista;

    void push_back(HBlock c_block_value);

    virtual NoumDefinitions noumDefinitions() override;

};

using HBlockList = std::shared_ptr<CBlockList>;

class CBlockEnums : public CBlock //retorna um valor generico
{
public:
    std::vector<HBlockNoum> values;

    virtual void dump(std::string ident) override;

    CBlockEnums(std::vector<HBlockNoum> _values);

    bool contains(string cs);

    string value_x;
};

using HBlockEnums = std::shared_ptr<CBlockEnums>;

class CBlockAssertion_InstanceVariable : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(std::string ident) override;

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
    virtual void dump(std::string ident) override;

    HBlock verbNoum; // Pode ser simples ou com a preposicao
    HBlock relation;

    CBlockVerbRelation(HBlock _noum, HBlock _relation) : verbNoum((_noum)), relation((_relation)) {};
};

class CBlockMatch;

using HBlockMatch = std::shared_ptr<CBlockMatch>;

class CBlockUnderstand : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(std::string ident) override;

    HBlockMatch input_n; // Pode ser simples ou com a preposicao
    HBlock output_n;

    CBlockUnderstand(HBlockMatch _input_n, HBlock _output_n) : input_n(_input_n), output_n((_output_n)) {};
};

class CBlockMatchList;

using HBlockMatchList = std::shared_ptr<CBlockMatchList>;

class CBlockUnderstandStatic : public CBlock    //retorna uma declaracao
{
public:
    virtual void dump(std::string ident) override;

    HBlockMatchList argument_match; // Pode ser simples ou com a preposicao
    HBlock output_n;

    CBlockUnderstandStatic(HBlockMatchList _argument_match, HBlock _output_n) : argument_match(_argument_match),
                                                                                output_n((_output_n)) {};
};

using HBlockUnderstandStatic = std::shared_ptr<CBlockUnderstandStatic>;

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
    virtual void dump(std::string ident) override;

    HBlock noum1;
    HBlock noum2;

    CBlockActionApply(HBlock _noum1, HBlock _noum2);
};

using HBlockActionApply = std::shared_ptr<CBlockActionApply>;

class CBlockAction : public CBlock  // um bloco que representa uma atividade
{
public:
    virtual void dump(std::string ident) override;

    CBlockAction(HBlock input)
            : input(input) {
    }

    HBlock input;
};

using HBlockAction = std::shared_ptr<CBlockAction>;

class CBlockActionCall : public CBlock {
public :
    HBlockAction action;
    HBlock noum1;
    HBlock noum2;

    CBlockActionCall(HBlockAction _action, HBlock _noum1, HBlock _noum2) : action(_action), noum1(_noum1),
                                                                           noum2(_noum2) {}

    void dump(std::string ident) override;
};

using HBlockActionCall = std::shared_ptr<CBlockActionCall>;

class CBlockDinamicDispatch : public CBlockAction {
public:

    string command;

    CBlockDinamicDispatch(string _command) : CBlockAction(std::make_shared<CBlockNoum>(_command)), command(_command) {}

    void dump(std::string ident) override;
};

using HBlockDinamicDispatch = std::shared_ptr<CBlockDinamicDispatch>;

class CBlockStaticDispatch : public CBlockAction {
public:
    int staticEntryTable;
    HBlock noum1;
    HBlock noum2;

    CBlockStaticDispatch(int _staticEntryTable, HBlock _noum1, HBlock _noum2) : CBlockAction(
            std::make_shared<CBlockNoum>("static " + std::to_string(_staticEntryTable))),
                                                                                staticEntryTable(_staticEntryTable),
                                                                                noum1(_noum1), noum2(_noum2) {}

    void dump(std::string ident) override;
};

using HBlockStaticDispatch = std::shared_ptr<CBlockStaticDispatch>;

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

class CBlockToDecide
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecide(HBlock _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

    HBlock queryToMatch;
    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(std::string ident) override;
};

using HBlockToDecide = std::shared_ptr<CBlockToDecide>;

class CBlockToDecidewhether
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecidewhether
            (HBlock _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

    HBlock queryToMatch;
    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(std::string ident) override;
};

using HBlockToDecidewhether = std::shared_ptr<CBlockToDecidewhether>;

class CBlockToDecideIf
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecideIf(HBlockAssertion_is _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

    HBlockAssertion_is queryToMatch;
    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(std::string ident) override;
};

using HBlockToDecideIf = std::shared_ptr<CBlockToDecideIf>;

class CBlockToDecideOn : public CBlock  // bloco que equivale a um return no decide
{
public:
    CBlockToDecideOn(HBlock _decideBody) : decideBody(_decideBody) {
    }

    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(std::string ident) override;
};

using HBlockToDecideOn = std::shared_ptr<CBlockToDecideOn>;

