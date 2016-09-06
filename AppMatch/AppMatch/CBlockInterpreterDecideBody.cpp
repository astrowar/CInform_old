
#include "CBlockMatch.h"
#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <iostream>
#include "QueryStack.h"


HBlock CBlockInterpreter::getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecideWhether dct) {

    return nullptr;

}

HBlock CBlockInterpreter::getDecidedValueOf(HBlock c_block, HBlockToDecideWhat dct , HRunLocalScope localsEntry, QueryStack stk) {
    HBlockMatch match = std::dynamic_pointer_cast<CBlockMatch>(dct->queryToMatch);

	CResultMatch result = this->Match(match, c_block, stk);
    if (result.hasMatch ) 
	{
 
		auto localsHeader = std::make_shared< CRunLocalScope >(result.maptch);
		if (localsEntry != nullptr)
		{
			HRunLocalScope localsNext = localsEntry->Union(localsHeader);
		}
		else
		{
			HRunLocalScope localsNext = localsHeader;
		}

		

        return dct->decideBody;
    }

    return nullptr;
}
 

QueryResul CBlockInterpreter::getDecidedIf(HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack stk)
{
	CResultMatch result = this->Match(dct->queryToMatch, c_block, stk);
	if (result.hasMatch)
	{
		auto localsHeader = std::make_shared< CRunLocalScope >(result.maptch);
		HRunLocalScope localsNext = nullptr;
		if (localsEntry != nullptr)
		{
			  localsNext = localsEntry->Union(localsHeader);
		}
		else
		{
			  localsNext = localsHeader;
		}

		auto rr =  query(dct->decideBody, localsNext, stk);
		if (rr == QEquals) return  QEquals;
		return QNotEquals;

	}

	return QUndefined;
}