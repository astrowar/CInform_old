 
#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;


std::pair<HBlockKind, HBlockKind>
CBlockInterpreter::create_derivadeKind(std::string called, std::string baseClasseName) {

    HBlockKind b = nullptr;
    HBlockKind bup = nullptr;

    if (baseClasseName == "value") {
        b = make_shared<CBlockKindValue>(called);

    } else if (baseClasseName == "") {
        b = make_shared<CBlockKindThing>(called);  //Default
    } else {
        // o que eh a baseclass ???
        HBlock r = resolve_string(baseClasseName);

        if (HBlockKindThing kt = dynamic_pointer_cast<CBlockKindThing>(r)) {
            b = make_shared<CBlockKindThing>(called);
            bup = kt;
        } else if (HBlockKindValue ktv = dynamic_pointer_cast<CBlockKindValue>(r)) {
            b = make_shared<CBlockKindValue>(called);
            bup = ktv;
        } else {
            std::cout << "What ?? " << baseClasseName << endl;
            throw "Error on derive a kind";
        }

    }
    return std::pair<HBlockKind, HBlockKind>(b, bup);

}






bool CBlockInterpreter::assert_it_Value(HBlock obj, HBlock value) {
    if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
        HBlock nobj = resolve_noum(nbase);
        if (nobj != nullptr) {
            return assert_it_Value(nobj, value);
        }
        return false;
    }

    if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
            HBlock nobj = resolve_noum(nbase);
            if (nobj == nullptr) {
                nInst->set(nbase);
                return true;
            }
        }
    }

    if (HBlockProperty prop_n = dynamic_pointer_cast<CBlockProperty>(obj)) {
        HBlock propNamed = prop_n->prop;
        HBlock destination = prop_n->obj;
        return assert_it_property(propNamed, destination, value);
    }

    return false;

}



bool CBlockInterpreter::assert_it_kind(HBlock obj, HBlock value) {
    if (HBlockKindOfName k = dynamic_pointer_cast<CBlockKindOfName>(value)) {
        if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {

            auto b_up = create_derivadeKind(nbase->named, k->baseClasseName);
            HBlockKind b = b_up.first;

            if (b_up.second != nullptr) {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                     make_shared<CBlockKindOf>(
                                                                                                             b_up.second));
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

            {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbase, b);
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

            std::cout << "new Kind add " << nbase->named <<  endl;
            return true;
        }

            //Processa a lista
        else if (HBlockList nList = dynamic_pointer_cast<CBlockList>(obj)) {
            for (auto nObj : nList->lista) {
                if (HBlockNoum nbasei = dynamic_pointer_cast<CBlockNoum>(nObj)) {
                    auto b_up = create_derivadeKind(nbasei->named, k->baseClasseName);
                    HBlockKind b = b_up.first;
                    if (b_up.second != nullptr) {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                             make_shared<CBlockKindOf>(
                                                                                                                     b_up.second));
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }

                    {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbasei, b);
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }
                    std::cout << "new Kind add" << endl;
                }
            }
            return true;

        }

    }
    return false;

}



bool CBlockInterpreter::assert_it_instance(HBlock obj, HBlock value) {
    if (HBlockNoum nvalue = dynamic_pointer_cast<CBlockNoum>(value)) {
        if (HBlockNoum nobj = dynamic_pointer_cast<CBlockNoum>(obj)) {
            HBlock nn = resolve_noum(nvalue);
            if (HBlockKind k = dynamic_pointer_cast<CBlockKind>(nn)) {
                //HBlockInstance binstance = make_shared<CBlockInstance>(nobj->named);

                HBlockInstance binstance = new_Instance(nobj->named, k);

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(obj, binstance);
                HBlockAssertion_isInstanceOf newInst = make_shared<CBlockAssertion_isInstanceOf>(binstance, k);
                assertions.push_back(newDefi);
                assertions.push_back(newInst);
                std::cout << "new Instance add" << endl;
                return true;
            }
            return false;
        }

            //Many instances
        else if (HBlockList nobjList = dynamic_pointer_cast<CBlockList>(obj)) {
            for (auto &e : nobjList->lista) {
                assert_it_instance(e, value);
            }
            return true;
        }

    }

    return false;
}



bool CBlockInterpreter::assert_it_valuesDefinitions(HBlock c_block, HBlock value) {
    // Value Kind , is , list of Noums

    if (HBlockList vlist = dynamic_pointer_cast<CBlockList>(value)) // segundo argumento eh uma lista
        if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(c_block)) //primeiro eh um noum
        {
            // nn eh um value Kind ??
            HBlock nobj = resolve_noum(nn);
            if (HBlockKind nkind = dynamic_pointer_cast<CBlockKind>(
                    nobj)) //mas na verdade o primeiro eh um kind ja definido
            {
                for (auto &v : vlist->lista) {
                    assert_it_instance(v, nkind);
                }
                return true;
            }

        }
    return false;
}
