// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Eraldo Rangel on 18/08/16.
//



#include "BlockInterpreter.hpp"
#include "sharedCast.hpp"
 #include "CBlockInterpreterRuntime.hpp"

using namespace std;


using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;


bool CBlockInterpreter::is_derivadeOf(HBlockKind aDerivade, HBlockKind Base) {
	if (aDerivade.get() == nullptr || Base.get() == nullptr)
	{
		return false;
	}
    if (aDerivade.get() == Base.get()) return true;

	aDerivade->dump("");
	Base->dump("");

	if (HBlockCompositionList nderiv = asHBlockCompositionList(aDerivade))
		if (HBlockCompositionList nbase = asHBlockCompositionList(Base))
		{
			auto b = is_derivadeOf(nderiv->itemKind, nbase->itemKind);
			return b;
		}

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
 


            if (HBlockKind nbase = asHBlockKind((*it)->get_obj()))

                if (nbase.get() == aDerivade.get()) 
				{
                    if (HBlockKindOf k = asHBlockKindOf((*it)->get_definition())) {
                        if (k->baseClasse.get() == Base.get()) 
						{
                            return true;
                        } 
						else 
						{
                            bool bnn = is_derivadeOf(k->baseClasse, Base);
                            if (bnn) 
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

list<HBlockKind> CBlockInterpreter::getUpperKinds(HBlockKind a) {
    list<HBlockKind> upperList;


    for (auto it = assertions.begin(); it != assertions.end(); ++it) {

        if (HBlockKind nbase = asHBlockKind((*it)->get_obj()))
            if ( nbase.get() == a.get())  //  A -> X
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
    if (a  == nullptr || b ==nullptr) {
        return false;
    }
 

	//// Custom derivades
	//if (HBlockText nInstanceText = asHBlockText(a ))
	//{
	//	return  (b->named == "text"); //CBlock Text is instance of of Text 
	//}

	return is_derivadeOf(a->baseKind, b );


    //for (auto it = assertions.begin(); it != assertions.end(); ++it) {
    //    {
    //        if (HBlockInstance nbase = asHBlockInstance((*it)->get_obj()))

    //            if (nbase->named == a->named) {
    //                if (HBlockKind k = asHBlockKind((*it)->get_definition())) {
    //                    if (k->named == b->named) {
    //                        return true;
    //                    } else {
    //                        CBlocking::HBlock bnext = resolve_string(k->named,localsEntry);
    //                        if (HBlockKind baseClasse = asHBlockKind(bnext)) {
    //                            bool bnn = is_derivadeOf(baseClasse, b);
    //                            if (bnn) {
    //                                return true;
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //    }
    //}
    return false;
}

