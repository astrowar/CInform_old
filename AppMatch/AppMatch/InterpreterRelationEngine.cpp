//
// Created by eraldo.rangel on 12/09/2016.
//


#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "QueryStack.h"
#include "CResultMatch.h"

using namespace std;

bool CBlockInterpreter::assert_newRelation(HBlockRelationBase rel) {
    // processa uma nova relacao
    string nrel = rel->named;
    if (staticRelation.find(nrel) != staticRelation.end()) {
        cout << "relation " << nrel << " alreads exist" << endl;
        return false;
    }
    staticRelation[nrel] = rel;

    return true;
}

