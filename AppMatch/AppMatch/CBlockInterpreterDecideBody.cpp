
#include "CBlockMatch.h"
#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <iostream>

 

HBlock CBlockInterpreter::getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecidewhether dct) {

    return nullptr;

}

HBlock CBlockInterpreter::getDecidedValueOf(HBlock c_block, HBlockToDecide dct) {
    HBlockMatch match = std::dynamic_pointer_cast<CBlockMatch>(dct->queryToMatch);

	CResultMatch result = this->Match(match, c_block);
    if (result.hasMatch ) 
	{
        return dct->decideBody;
    }

    return nullptr;
}
