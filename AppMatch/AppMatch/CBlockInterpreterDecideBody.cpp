
#include "CBlockMatch.h"
#include "CBlockInterpreterRuntime.h"
#include <iostream>

bool CBlockInterpreter::Match(HBlock c_block, HBlockMatch m) {
    {
        if (auto inner = std::dynamic_pointer_cast<CBlockNoum>(m->matchInner))
            if (auto cinner = std::dynamic_pointer_cast<CBlockNoum>(c_block)) {
                std::cout << inner->named << " == " << cinner->named << std::endl;
                return (inner->named == cinner->named);
            }
    }

    {
        if (auto inner = std::dynamic_pointer_cast<CBlockInstance>(m->matchInner))
            if (auto cinner = std::dynamic_pointer_cast<CBlockInstance>(c_block)) {
                return (inner->named == cinner->named);
            }
    }

    {
        if (auto akind = std::dynamic_pointer_cast<CBlockKind>(m->matchInner))
            if (auto cinner = std::dynamic_pointer_cast<CBlockInstance>(c_block)) {
                return is_derivadeOf(cinner, akind);
            }
    }

    {
        if (auto akind = std::dynamic_pointer_cast<CBlockMatchAny>(m->matchInner)) {
            return true;
        }
    }

    return false;
}

HBlock CBlockInterpreter::getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecidewhether dct) {

    return nullptr;

}

HBlock CBlockInterpreter::getDecidedValueOf(HBlock c_block, HBlockToDecide dct) {
    HBlockMatch match = std::dynamic_pointer_cast<CBlockMatch>(dct->queryToMatch);

    if (this->Match(c_block, match)) {

        return dct->decideBody;
    }

    return nullptr;
}
