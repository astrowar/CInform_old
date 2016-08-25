
 
#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;



HBlockKind CBlockInterpreter::getKindOf(HBlockInstance obj) {
    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        if (HBlockAssertion_is v = dynamic_pointer_cast<CBlockAssertion_is>(*it)) {
            if (v->get_obj() == obj) {
                if (HBlockKind k = dynamic_pointer_cast<CBlockKind>(v->get_definition())) {
                    return k;
                }
            }
        }
    }
    return nullptr;
}


std::string CBlockInterpreter::BlockNoum(HBlock c_block) {
    if (HBlockKind k0 = dynamic_pointer_cast<CBlockKind>(c_block)) {
        return k0->named;
    }

    if (HBlockInstance k0 = dynamic_pointer_cast<CBlockInstance>(c_block)) {
        return k0->named;
    }

    if (HBlockKindValue k0 = dynamic_pointer_cast<CBlockKindValue>(c_block)) {
        return k0->named;
    }

    if (HBlockNamedValue k0 = dynamic_pointer_cast<CBlockNamedValue>(c_block)) {
        return k0->named;
    }

    if (HBlockVariable k0 = dynamic_pointer_cast<CBlockVariable>(c_block)) {
        return k0->named;
    }

    if (HBlockNoum k0 = dynamic_pointer_cast<CBlockNoum>(c_block)) {
        return k0->named;
    }
    return "";
}



HBlock CBlockInterpreter::resolve(CTerm *b) {
    return make_shared<CBlockNoum>(b->repr());
}

HBlock CBlockInterpreter::resolve_of(HBlock b, HBlock a) {
    //return new CBlockProperty( b , a);
    return nullptr;
}

HBlockKind CBlockInterpreter::resolve_kind(std::string n) {
    for (auto &defs : assertions) {
        if (HBlockKind nn = dynamic_pointer_cast<CBlockKind>(defs->get_definition())) {
            if (nn->named == n) {
                return nn;
            }
        }
    }
    return nullptr;

}

HBlock CBlockInterpreter::resolve_noum(HBlockNoum n) {
    // eh um kind de alguma coisa ?
    for (auto &defs : assertions) {
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(defs->get_obj())) {
            //std::cout << nn->named << std::endl;
            if (nn->named == n->named) {
                return defs->get_definition();
            }
        }
    }
    std::cout << "Fail to " << n->named << std::endl;
    return nullptr;


}

HBlock CBlockInterpreter::resolve_string(std::string n) {
    for (auto &defs : assertions) {
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(defs->get_obj())) {
            //std::cout << nn->named << std::endl;
            if (nn->named == n) {
                return defs->get_definition();
            }
        }
    }
    return nullptr;
}
