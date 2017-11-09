// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
        CPredSequence predList;
        <<(pLiteral("not"));
        <<(pAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n2 = parserBoolean(p,res.matchs["N2"]);
            return std::make_shared<CBlockBooleanNOT>(n2);
        }
    }

    {
        CPredSequence predList;
        <<(pAny("N1"));
        <<(pLiteral("and"));
        <<(pAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parserBoolean(p,res.matchs["N1"]);
            HBlock n2 = parserBoolean(p, res.matchs["N2"]);
            return std::make_shared<CBlockBooleanAND>(n1, n2);
        }
    }

    {
        CPredSequence predList;
        <<(pAny("N1"));
        <<(pLiteral("or"));
        <<(pAny("N2"));

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
    CPredSequence predList;
    <<(pAny("Object"));
    <<(mk_HPredLiteral_OR("Verb", {"is", "are"}));
    //<<(pAtom("Verb", make_string("is")));
    <<(pList("kindpart", {pLiteral("a"), pLiteral("kind"), pLiteral("of")}));
    <<(pAny("Kind"));

    MatchResult res = CMatch(lst, predList);
    if (res.result != Equals) {
        return ParserResult(res);
    }
    //HBlock b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
    return std::move(ParserResult(res));
}

 


HBlockActionApply NSParser::ParseAssertion::parse_AssertionAction_ApplyngTo(CParser * p, HTerm term) 
{
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList;		
		<<(pLiteral("nothing"));		
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			//HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			//HBlock n2 = Expression::parser_kind(p, res.matchs["kind2"]);
			return std::make_shared<CBlockActionApply>(nullptr,nullptr);
		}
	}
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList;
		<<(pAny("kind1"));
		<<(pLiteral("and"));
		<<(pAny("kind2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			HBlock n2 = Expression::parser_kind(p, res.matchs["kind2"]);
			return std::make_shared<CBlockActionApply>(n1, n2);
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList;
		<<(pLiteral("two"));
		<<(pAny("kind1"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			return std::make_shared<CBlockActionApply>(n1, n1);
		}
	}


    {
        // and action applying to [one visible thing and requiring light]
        CPredSequence predList;
        //<<(pLiteral("one"));
        <<(pAny("kind1"));
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


