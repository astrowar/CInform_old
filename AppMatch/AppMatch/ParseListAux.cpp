// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"

using namespace CBlocking;
 
using namespace NSTerm;
using namespace NSTerm::NSMatch;






HBlockList NSParser::ParseList::parseAssertion_Strict_COMMA_Supl(CParser * p, HTerm term, HPred sep) {

    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(sep);
    predList.push_back(mkHPredAny("N2"));
    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
        cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
        cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
        return cList;
    }
    return nullptr;
}

HBlockList  NSParser::ParseAssertion::parseAssertionFirstTerm_COMMA_Supl( CParser * p, HTerm term, HPred sep, HBlockList cList) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(mkHPredBooleanOr("sep", mk_HPredLiteral(","), sep));
    predList.push_back(mkHPredAny("N2"));

    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        cList = parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
        cList = parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
        return cList;
    }

    HBlock ret = Expression::parser_expression(p,term);
    cList->push_back(ret);
    //cList->push_back(std::make_shared<CBlockNoum>(  term->removeArticle()->repr()));
    return cList;
}

HBlockList NSParser::ParseList::parseAssertionFirstTerm_COMMA_AND(CParser * p, HTerm term, HBlockList CList) {
    return ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,term, mk_HPredLiteral("and"), CList);
}

HBlockList NSParser::ParseList::parseAssertionFirstTerm_COMMA_OR(CParser * p, HTerm term, HBlockList CList) {
    return ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,term, mk_HPredLiteral("or"), CList);
}







HBlock NSParser::ParseList::parse_List_AND(CParser * p, std::vector<HTerm>& term) {
    {
        auto sep = mk_HPredLiteral("and");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
            cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
            cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
            return cList;
        }
    }

    {
        auto sep = mk_HPredLiteral("or");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            return nullptr;
        }
    }
    {
        auto sep = mk_HPredLiteral(",");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
            cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
            cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
            return cList;
        }
    }

    return nullptr;

}


HBlock NSParser::ParseList::parse_List_OR(CParser * p, std::vector<HTerm>& term) {
	{
		auto sep = mk_HPredLiteral("or");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockList  cList = std::make_shared<CBlockList  >(std::list<HBlock>());
			cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
			cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
			HBlockList_OR  or_List = std::make_shared<CBlockList_OR  >(std::list<HBlock>());
			or_List->lista = cList->lista;
			return or_List;
		}
	}

	{
		auto sep = mk_HPredLiteral("and");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			return nullptr;
		}
	}
 

	return nullptr;

}




HBlockList NSParser::ParseList::parse_Strict_COMMA_AND(CParser * p, HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(p,term, mk_HPredLiteral("and"));
}

HBlockList NSParser::ParseList::parse_Strict_COMMA_OR(CParser * p, HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(p,term, mk_HPredLiteral("or"));
}