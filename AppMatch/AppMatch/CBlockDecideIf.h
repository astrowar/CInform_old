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
};

using HBlockToDecideWhat = std::shared_ptr<CBlockToDecideWhat>;






class CBlockToDecideOn : public CBlock  // bloco que equivale a um return no decide
{
public:
    CBlockToDecideOn(HBlock _decideBody) : decideBody(_decideBody) {
    }

    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(string ident) override;
};

using HBlockToDecideOn = std::shared_ptr<CBlockToDecideOn>;

