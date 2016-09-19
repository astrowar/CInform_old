#pragma once
#include "BlockInterpreter.h" 
#include "CBlockMatch.h"



class CBlockToDecide
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecide( )
             {
    }

    virtual HTerm eval() { return nullptr; }
    
};



class CBlockToDecideIf
        : public CBlockToDecide  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecideIf(HBlockMatchIs _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

	HBlockMatchIs queryToMatch;
    HBlock decideBody;

     

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockToDecideIf; }
};

using HBlockToDecideIf = std::shared_ptr<CBlockToDecideIf>;
using HBlockToDecide = std::shared_ptr<CBlockToDecide>;



class CBlockToDecideWhether
        : public CBlockToDecide   
{
public:
	CBlockToDecideWhether
            (HBlockMatch _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

	HBlockMatch queryToMatch;
    HBlock decideBody;    

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockToDecideWhether; }
};

using HBlockToDecideWhether = std::shared_ptr<CBlockToDecideWhether>;




class CBlockToDecideWhat
	: public CBlockToDecide   
{
public:
	CBlockToDecideWhat
	(HBlockMatch _queryToMatch, HBlock _decideBody)
		: queryToMatch(_queryToMatch),
		decideBody(_decideBody) {
	}

	HBlockMatch queryToMatch;
	HBlock decideBody;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockToDecideWhat; }
};

using HBlockToDecideWhat = std::shared_ptr<CBlockToDecideWhat>;


//First Noum .... Serve para identificar o primeiro Noum de uma sentenca com verbo no meio



class CBlockToDecideWhat_FirstNoum
	: public CBlockToDecide
{
public:
	CBlockToDecideWhat_FirstNoum
	(HBlockMatchIs _queryToMatch, HBlock _decideBody)
		: queryToMatch(_queryToMatch),
		decideBody(_decideBody) {
	}

	HBlockMatchIs queryToMatch;  //Obrigatorio ser um Query IS
	HBlock decideBody;

	void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockToDecideWhat_FirstNoum; }
};

using HBlockToDecideWhat_FirstNoum = std::shared_ptr<CBlockToDecideWhat_FirstNoum>;






class CBlockToDecideOn : public CBlock  // bloco que equivale a um return no decide
{
public:
    CBlockToDecideOn(HBlock _decideBody) : decideBody(_decideBody) {
    }

    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockToDecideOn; }
};

using HBlockToDecideOn = std::shared_ptr<CBlockToDecideOn>;

