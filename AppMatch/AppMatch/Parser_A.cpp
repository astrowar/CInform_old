//
// Created by Eraldo Rangel on 23/08/16.
//

#include "Parser.hpp"
 
 

 
#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"
#include "CblockAssertion.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



HBlock NSParser::Statement::parserBoolean(CParser * p, HTerm term) {
    if (CList *vlist = asCList(term.get())) {
        auto v = vlist->asVector();
        auto r = parserBoolean(p,v);
        if (r != nullptr) {
            return r;
        } else {
            //	std::cout << term->repr() << std::endl;
        }

    }
    return Expression::parser_expression(p,term);
}


HBlock NSParser::Statement::parserBoolean(CParser * p, std::vector<HTerm>& term)
{
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n2 = parserBoolean(p,res.matchs["N2"]);
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
            HBlock n1 = parserBoolean(p,res.matchs["N1"]);
            HBlock n2 = parserBoolean(p, res.matchs["N2"]);
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
            HBlock n1 = parserBoolean(p, res.matchs["N1"]);
            HBlock n2 = parserBoolean(p, res.matchs["N2"]);
            return std::make_shared<CBlockBooleanOR>(n1, n2);
        }
    }

    return nullptr;
}


NSParser::ParserResult NSParser::ParseAssertion::parser_AssertionKind(CParser * p, std::vector<HTerm>& lst) {
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

HBlockActionApply NSParser::ParseAssertion::parse_AssertionAction_ApplyngTo(CParser * p, HTerm term) {
    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("and"));
        predList.push_back(mkHPredAny("kind2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_kind(p,res.matchs["kind1"]);
            HBlock n2 = Expression::parser_kind(p,res.matchs["kind2"]);
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
            HBlock n1 = Expression::parser_kind(p,res.matchs["kind1"]);
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
            HBlock n1 = Expression::parser_kind(p,res.matchs["kind1"]);
            return std::make_shared<CBlockActionApply>(n1, nullptr );
        }
    }

    return nullptr;
}


//HBlock NSParser::CParser::parseAssertion_DecideWhat(HTerm term) {
//    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
//}


