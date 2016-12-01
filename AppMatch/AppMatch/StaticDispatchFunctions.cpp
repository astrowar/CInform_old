// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Eraldo Rangel on 23/08/16.
//
#include "Parser.hpp"
 
#include <algorithm>


#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"
#include "CblockAssertion.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



NSParser::staticDispatchEntry::staticDispatchEntry(HBlockMatchList _argumentsMatch, HBlock _action) : entryArguments(
        _argumentsMatch), action(_action) {

}

NSParser::staticDispatchEntry::staticDispatchEntry() : entryArguments(nullptr), action(nullptr) {

}

 

NSParser::SentenceDispatchPredicate::SentenceDispatchPredicate(std::vector<HPred> _matchPhase, HBlockMatch _matchPhaseDynamic,
	HBlock _output, int _entryId) : matchPhase(_matchPhase),
	_matchPhaseDynamic(_matchPhaseDynamic),
	output(_output),
	entryId(_entryId) {

}

int NSParser::CParser::registerStaticDispatch(int entry, HBlockMatchList argumentMatch, HBlock body) {
    for (auto it = staticDispatch.begin(); it != staticDispatch.end(); ++it) {
        if (it->entryId == entry) {
            staticDispatchEntry sEntry(argumentMatch, body);
            it->entries.push_back(sEntry);
            return entry;
        }
    }
    //nao achei nenhum que ja existe

    StaticDispatchArgument sdisp(entry);
    sdisp.entries.push_back(staticDispatchEntry(argumentMatch, body));
    staticDispatch.push_back(sdisp);
    return entry;
}


int NSParser::CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry) {

    //Verifica se ja tem a sentenceDispatch
    int maxID = 0;
    for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {
        maxID = std::max(maxID, it->entryId);
        if (isSamePred(it->matchPhase, _matchPhase)) {
            return it->entryId;
        }
    }

    //nao tem nenhum ... Cria um novo
    SentenceDispatchPredicate sdisp(_matchPhase, entry, nullptr, maxID + 1);
    sentenceDispatch.push_back(sdisp);

    sentenceDispatch.sort([](const SentenceDispatchPredicate &a, const SentenceDispatchPredicate &b) -> bool {
        return a.matchPhase.size() > b.matchPhase.size();
    });

   logMessage( "Dynamic Registed " );
    entry->dump("    ");

    return maxID + 1;
}

int NSParser::CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry , HBlock ret) {

	//Verifica se ja tem a sentenceDispatch
	int maxID = 0;
	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {
		maxID = std::max(maxID, it->entryId);
		if (isSamePred(it->matchPhase, _matchPhase)) {
			return it->entryId;
		}
	}

	//nao tem nenhum ... Cria um novo
	SentenceDispatchPredicate sdisp(_matchPhase, entry, ret, maxID + 1);
	sentenceDispatch.push_back(sdisp);

	sentenceDispatch.sort([](const SentenceDispatchPredicate &a, const SentenceDispatchPredicate &b) -> bool {
		return a.matchPhase.size() > b.matchPhase.size();
	});

	logMessage("Dynamic Registed ");
	entry->dump("    ");

	return maxID + 1;
}