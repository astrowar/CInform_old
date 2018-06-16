// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.



#include "BlockInterpreter.hpp"
#include "sharedCast.hpp"
 #include "interpreter/CBlockInterpreterRuntime.hpp"

using namespace std;


using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;


bool CBlockInterpreter::is_derivadeOf(HBlockKind aDerivade, HBlockKind Base) {
	if (aDerivade.get() == nullptr || Base.get() == nullptr)
	{
		return false;
	}
	if (CBlock::isSame(aDerivade.get(), Base.get()))
	{
		return true;
	}

 
	if (CBlock::isSame(MetaKindAny.get(), Base.get()))
	{
		//Todos sao instancias de ANY
		return true;
	}

	if (CBlock::isSame(MetaKindAny.get(), aDerivade.get()))
	{
		//  ANY eh derivado de todo mundo
		return true;
	}


	if (HBlockCompositionList nderiv = asHBlockCompositionList(aDerivade))
		if (HBlockCompositionList nbase = asHBlockCompositionList(Base))
		{
			auto b = is_derivadeOf(nderiv->itemKind, nbase->itemKind);
			return b;
		}

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        {
            if (HBlockKind nbase = asHBlockKind((*it)->get_obj()))

                if (CBlock::isSame(nbase.get() , aDerivade.get())) 
				{
                    if (HBlockKindOf k = asHBlockKindOf((*it)->get_definition())) {
                        if (CBlock::isSame(k->baseClasse.get() , Base.get()))
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

bool CBlockInterpreter::is_derivadeOf(HBlockInstance a, HBlockKind b,   HRunLocalScope localsEntry) 
{
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


bool CBlockInterpreter::is_InstanceOf(HBlock  a, HBlockKind b )
{


	//if (asHBlockNothing(c)) return true;
	//if (asHBlockBooleanValue(c)) return true;
	//if (asHBlockList(c)) return true;
	//if (asHBlockInstance(c)) return true;
	//if (asHBlockRelationBase(c)) return true;
	//if (asHBlockAction(c)) return true;
	//if (asHBlockNamedValue(c)) return true;


	if (HBlockKindNamed kNamed = asHBlockKindNamed(b))
	{
		auto bnext = resolve_kind(kNamed->named);
		if (CBlock::isSame(bnext.get(),b.get()) ==false )
		{
			return is_InstanceOf(a, bnext);
		}
	}

	if (CBlock::isSame(a.get(), Nothing.get() ))
	{
		if (CBlock::isSame(b.get(), MetaKindEntity.get())) //nothing is a thing !
		{
			return true;
		}
	}


	if (CBlock::isSame(MetaKindAny.get(), b.get()))
	{
		//Todos sao instancias de ANY
		return true;
	}
	if (CBlock::isSame(a.get(), Anything.get())) //anything is istance of all !
	{
		return true;
	}
	 

	
	if (HBlockText nInstanceText = asHBlockText(a))
	{
		if (CBlock::isSame(b.get(), MetaKindText.get()))
		{
			return true;
		}
	}

	if (HBlockInstance nInstance = asHBlockInstance(a))
	{
 
		return is_derivadeOf(nInstance, b, nullptr);
	}


	if (HBlockList iList = asHBlockList(a))
	{
		if (HBlockCompositionList kList = asHBlockCompositionList(b))
		{
			return true;
		}

	}
 
	if (HBlockCompositionPhrase kPhase = asHBlockCompositionPhrase(b))		
	{
	
		
	}
	if (HBlockActionInstance nAction = asHBlockActionInstance(a))
	{
		return is_derivadeOf(nAction->base_kind, b);		
	}

	if (HBlockNamedValue nValue = asHBlockNamedValue(a))
		if (HBlockEnums kEnums = asHBlockEnums(b))
		{
		 
		}
	 
	if (HBlockBooleanValue nBool = asHBlockBooleanValue(a))
	{
		return  (b == MetaKindBoolean);
	}

	
	return false;
}

