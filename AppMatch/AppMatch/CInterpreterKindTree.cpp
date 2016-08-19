//
// Created by Eraldo Rangel on 18/08/16.
//

#include "CBlockInterpreterRuntime.h"
#include "CInterpreterKindTree.h"

#include "BlockInterpreter.h"
#include <iostream>
using namespace std;


bool CBlockInterpreter::is_derivadeOf(CBlockKind  *a, CBlockKind *b)
{
    if (a->named == "" || b->named == "") return false;
    if (a->named ==  b->named ) return true;

    for (auto it = assertions.begin(); it != assertions.end(); ++it)
    {
        {
            if (CBlockKind * nbase = dynamic_cast<CBlockKind*>((*it)->get_obj()))

                if (nbase->named == a->named)
                {
                    if (CBlockKindOf * k = dynamic_cast<CBlockKindOf*>((*it)->get_definition()))
                    {
                        if (k->baseClasse->named  == b->named)
                        {
                            return true;
                        }
                        else
                        {
                            bool bnn =  is_derivadeOf(k->baseClasse, b);
                            if (bnn == true)
                            {
                                return true;
                            }

                        }
                    }
                }
        }
    }
    return false;
}

std::list<CBlockKind*> CBlockInterpreter::getUpperKinds(CBlockKind* a  )
{
    std::list<CBlockKind*> upperList;

    std::cout << "U " << a->named << std::endl;
    for (auto it = assertions.begin(); it != assertions.end(); ++it)
    {

        if (CBlockKind * nbase = dynamic_cast<CBlockKind*>((*it)->get_obj()))
            if (nbase->named == a->named)  //  A -> X
            {
                if (CBlockKindOf * k = dynamic_cast<CBlockKindOf*>((*it)->get_definition()))
                {


                    std::list<CBlockKind*> ap = getUpperKinds(k->baseClasse);
                    upperList.insert(upperList.end(), ap.begin(), ap.end());


                }
            }

    }

    //upperList.erase(unique(upperList.begin(), upperList.end()), upperList.end());
    upperList.push_back(a);
    return upperList;
}

bool CBlockInterpreter::is_derivadeOf(CBlockInstance  *a, CBlockKind *b)
{
    if (a->named == "" || b->named == "")
    {
        return false;
    }
    if (a->named == b->named)
    {
        return true;
    }

    for (auto it = assertions.begin(); it != assertions.end(); ++it)
    {
        {if (CBlockInstance * nbase = dynamic_cast<CBlockInstance*>((*it)->get_obj()))

                if (nbase->named == a->named)
                {
                    if (CBlockKind  * k = dynamic_cast<CBlockKind *>((*it)->get_definition()))
                    {
                        if (k->named  == b->named)
                        {
                            return true;
                        }
                        else
                        {
                            UBlock bnext = resolve_string(k->named);
                            if (CBlockKind *baseClasse = dynamic_cast<CBlockKind*>(bnext))
                            {
                                bool bnn = is_derivadeOf(baseClasse, b);
                                if (bnn == true)
                                {
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

