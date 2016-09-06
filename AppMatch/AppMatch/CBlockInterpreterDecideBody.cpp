
#include "CBlockMatch.h"
#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <iostream>
#include "QueryStack.h"


HBlock CBlockInterpreter::getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecideWhether dct) {

    return nullptr;

}

HBlock CBlockInterpreter::getDecidedValueOf(HBlock c_block, HBlockToDecideWhat dct , QueryStack stk) {
    HBlockMatch match = std::dynamic_pointer_cast<CBlockMatch>(dct->queryToMatch);

	CResultMatch result = this->Match(match, c_block, stk);
    if (result.hasMatch ) 
	{
        return dct->decideBody;
    }

    return nullptr;
}
