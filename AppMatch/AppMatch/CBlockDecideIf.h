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
