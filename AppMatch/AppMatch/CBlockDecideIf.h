#pragma once
#include "BlockInterpreter.h" 
#include "CBlockMatch.h"

class CBlockToDecideIf
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecideIf(HBlockMatchIs _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

	HBlockMatchIs queryToMatch;
    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(string ident) override;
};

using HBlockToDecideIf = std::shared_ptr<CBlockToDecideIf>;


class CBlockToDecide
        : public CBlock  // um bloco que especifica um valor Customizado ( color OF book ) -> ( prop OF what )
{
public:
    CBlockToDecide(HBlockMatch _queryToMatch, HBlock _decideBody)
            : queryToMatch(_queryToMatch),
              decideBody(_decideBody) {
    }

	HBlockMatch queryToMatch;
    HBlock decideBody;

    virtual HTerm eval() { return nullptr; }

    void dump(string ident) override;
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

    void dump(string ident) override;
};

using HBlockToDecidewhether = std::shared_ptr<CBlockToDecidewhether>;


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

