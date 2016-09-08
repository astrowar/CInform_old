//
// Created by Eraldo Rangel on 23/08/16.
//

#include "Parser.h"
#include <iostream>
 

 
#include "CBlockMatch.h"
#include "CBlockBoolean.h"
#include "CblockAssertion.h"



HBlock CParser::parserBoolean(std::vector<HTerm> term) {
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n2 = parserBoolean(res.matchs["N2"]);
            return std::make_shared<CBlockBooleanNOT>(n2);
        }
    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(mk_HPredLiteral("and"));
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parserBoolean(res.matchs["N1"]);
            HBlock n2 = parserBoolean(res.matchs["N2"]);
            return std::make_shared<CBlockBooleanAND>(n1, n2);
        }
    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(mk_HPredLiteral("or"));
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parserBoolean(res.matchs["N1"]);
            HBlock n2 = parserBoolean(res.matchs["N2"]);
            return std::make_shared<CBlockBooleanOR>(n1, n2);
        }
    }

    return nullptr;
}




ParserResult CParser::parser_AssertionKind(std::vector<HTerm> lst) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("Object"));
    predList.push_back(mk_HPredLiteral_OR("Verb", {"is", "are"}));
    //predList.push_back(mkHPredAtom("Verb", make_string("is")));
    predList.push_back(mkHPredList("kindpart", {mk_HPredLiteral("a"), mk_HPredLiteral("kind"), mk_HPredLiteral("of")}));
    predList.push_back(mkHPredAny("Kind"));

    MatchResult res = CMatch(lst, predList);
    if (res.result != Equals) {
        return ParserResult(res);
    }
    //HBlock b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
    return std::move(ParserResult(res));
}

HBlock CParser::parse_AssertionAction_ApplyngTo(HTerm term) {
    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("and"));
        predList.push_back(mkHPredAny("kind2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_kind(res.matchs["kind1"]);
            HBlock n2 = parser_kind(res.matchs["kind2"]);
            return std::make_shared<CBlockActionApply>(n1, n2);
        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("two"));
        predList.push_back(mkHPredAny("kind1"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_kind(res.matchs["kind1"]);
            return std::make_shared<CBlockActionApply>(n1, n1);
        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        //predList.push_back(mk_HPredLiteral("one"));
        predList.push_back(mkHPredAny("kind1"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_kind(res.matchs["kind1"]);
            return std::make_shared<CBlockActionApply>(n1, std::make_shared<CBlockNoum>("Nothing"));
        }
    }

    return nullptr;
}


//HBlock CParser::parseAssertion_DecideWhat(HTerm term) {
//    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
//}


