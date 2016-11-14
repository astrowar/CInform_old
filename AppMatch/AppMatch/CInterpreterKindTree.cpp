//
// Created by Eraldo Rangel on 18/08/16.
//



#include "BlockInterpreter.hpp"
#include "sharedCast.hpp"
 #include "CBlockInterpreterRuntime.hpp"

using namespace std;

bool CBlockInterpreter::is_derivadeOf(HBlockKind a, HBlockKind b) {
    if (a->named == "" || b->named == "") return false;
    if (a->named == b->named) return true;

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
            if (HBlockKind nbase = asHBlockKind((*it)->get_obj()))

                if (nbase->named == a->named) {
                    if (HBlockKindOf k = asHBlockKindOf((*it)->get_definition())) {
                        if (k->baseClasse->named == b->named) {
                            return true;
                        } else {
                            bool bnn = is_derivadeOf(k->baseClasse, b);
                            if (bnn) {
                                return true;
                            }

                        }
                    }
                }
        }
    }
    return false;
}

list<HBlockKind> CBlockInterpreter::getUpperKinds(HBlockKind a) {
    list<HBlockKind> upperList;


    for (auto it = assertions.begin(); it != assertions.end(); ++it) {

        if (HBlockKind nbase = asHBlockKind((*it)->get_obj()))
            if ( nbase->named == a->named)  //  A -> X
            {
                if (HBlockKindOf k = asHBlockKindOf((*it)->get_definition())) {

                    list<HBlockKind> ap = getUpperKinds(k->baseClasse);
                    upperList.insert(upperList.end(), ap.begin(), ap.end());


                }
            }

    }

    //upperList.erase(unique(upperList.begin(), upperList.end()), upperList.end());
    upperList.push_back(a);
    return upperList;
}

bool CBlockInterpreter::is_derivadeOf(HBlockInstance a, HBlockKind b,   HRunLocalScope localsEntry) {
    if (a->named == "" || b->named == "") {
        return false;
    }
    if (a->named == b->named) {
        return true;
    }

	// Custom derivades
	if (HBlockText nInstanceText = asHBlockText(a ))
	{
		return  (b->named == "text"); //CBlock Text is instance of of Text
			
	}


    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
            if (HBlockInstance nbase = asHBlockInstance((*it)->get_obj()))

                if (nbase->named == a->named) {
                    if (HBlockKind k = asHBlockKind((*it)->get_definition())) {
                        if (k->named == b->named) {
                            return true;
                        } else {
                            HBlock bnext = resolve_string(k->named,localsEntry);
                            if (HBlockKind baseClasse = asHBlockKind(bnext)) {
                                bool bnn = is_derivadeOf(baseClasse, b);
                                if (bnn) {
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

