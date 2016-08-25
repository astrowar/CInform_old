//
// Created by Eraldo Rangel on 18/08/16.
//

#include "CBlockInterpreterRuntime.h"

#include "BlockInterpreter.h"
#include <iostream>

using namespace std;

bool CBlockInterpreter::is_derivadeOf(HBlockKind a, HBlockKind b) {
    if (a->named == "" || b->named == "") return false;
    if (a->named == b->named) return true;

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
            if (HBlockKind nbase = dynamic_pointer_cast<CBlockKind>((*it)->get_obj()))

                if (nbase->named == a->named) {
                    if (HBlockKindOf k = dynamic_pointer_cast<CBlockKindOf>((*it)->get_definition())) {
                        if (k->baseClasse->named == b->named) {
                            return true;
                        } else {
                            bool bnn = is_derivadeOf(k->baseClasse, b);
                            if (bnn == true) {
                                return true;
                            }

                        }
                    }
                }
        }
    }
    return false;
}

std::list<HBlockKind> CBlockInterpreter::getUpperKinds(HBlockKind a) {
    std::list<HBlockKind> upperList;

    std::cout << "U " << a->named << std::endl;
    for (auto it = assertions.begin(); it != assertions.end(); ++it) {

        if (HBlockKind nbase = dynamic_pointer_cast<CBlockKind>((*it)->get_obj()))
            if (nbase->named == a->named)  //  A -> X
            {
                if (HBlockKindOf k = dynamic_pointer_cast<CBlockKindOf>((*it)->get_definition())) {

                    std::list<HBlockKind> ap = getUpperKinds(k->baseClasse);
                    upperList.insert(upperList.end(), ap.begin(), ap.end());


                }
            }

    }

    //upperList.erase(unique(upperList.begin(), upperList.end()), upperList.end());
    upperList.push_back(a);
    return upperList;
}

bool CBlockInterpreter::is_derivadeOf(HBlockInstance a, HBlockKind b) {
    if (a->named == "" || b->named == "") {
        return false;
    }
    if (a->named == b->named) {
        return true;
    }

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
            if (HBlockInstance nbase = dynamic_pointer_cast<CBlockInstance>((*it)->get_obj()))

                if (nbase->named == a->named) {
                    if (HBlockKind k = dynamic_pointer_cast<CBlockKind>((*it)->get_definition())) {
                        if (k->named == b->named) {
                            return true;
                        } else {
                            HBlock bnext = resolve_string(k->named);
                            if (HBlockKind baseClasse = dynamic_pointer_cast<CBlockKind>(bnext)) {
                                bool bnn = is_derivadeOf(baseClasse, b);
                                if (bnn == true) {
                                    return true;
                                }
                            }
                        }
                    }
                }
        }
    }
    return false;
}

