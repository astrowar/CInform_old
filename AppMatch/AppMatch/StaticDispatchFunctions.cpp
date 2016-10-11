//
// Created by Eraldo Rangel on 23/08/16.
//
#include "Parser.hpp"
#include <iostream>
#include <algorithm>

#include "CBlockInterpreterRuntime.hpp"
#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"
#include "CblockAssertion.hpp"

staticDispatchEntry::staticDispatchEntry(HBlockMatchList _argumentsMatch, HBlock _action) : entryArguments(
        _argumentsMatch), action(_action) {

}

staticDispatchEntry::staticDispatchEntry() : entryArguments(nullptr), action(nullptr) {

}

 

SentenceDispatchPredicate::SentenceDispatchPredicate(std::vector<HPred> _matchPhase, HBlockMatch _matchPhaseDynamic,
	HBlock _output, int _entryId) : matchPhase(_matchPhase),
	_matchPhaseDynamic(_matchPhaseDynamic),
	output(_output),
	entryId(_entryId) {

}

int CParser::registerStaticDispatch(int entry, HBlockMatchList argumentMatch, HBlock body) {
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


int CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry) {

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

    std::cout << "Dynamic Registed " << std::endl;
    entry->dump("    ");

    return maxID + 1;
}

int CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry , HBlock ret) {

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

	std::cout << "Dynamic Registed " << std::endl;
	entry->dump("    ");

	return maxID + 1;
}