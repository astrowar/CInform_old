// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by eraldo.rangel on 12/09/2016.
//


#include "BlockInterpreter.hpp"
 

#include "CblockAssertion.hpp"
#include "QueryStack.hpp"
#include "CResultMatch.hpp"
#include "CBlockInterpreterRuntime.hpp"
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

