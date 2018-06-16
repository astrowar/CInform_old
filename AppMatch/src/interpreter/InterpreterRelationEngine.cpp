// PVS
// PVQ
 
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "BlockInterpreter.hpp"
 

#include "CblockAssertion.hpp"
#include "interpreter/QueryStack.hpp"
#include "CResultMatch.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;

bool CBlockInterpreter::assert_newRelation(HBlockRelationBase rel) {
    // processa uma nova relacao
    string nrel = rel->named;
    if (staticRelation.find(nrel) != staticRelation.end()) {
		logError("relation " + nrel + " alreads exist");
        return false;
    }
    staticRelation[nrel] = rel;

	addSymbol(nrel, rel);
    return true;
}

