#include "Parser.hpp"






HBlockList CParser::parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep) {

    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(sep);
    predList.push_back(mkHPredAny("N2"));
    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
        cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
        cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
        return cList;
    }
    return nullptr;
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, HBlockList cList) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(mkHPredBooleanOr("sep", mk_HPredLiteral(","), sep));
    predList.push_back(mkHPredAny("N2"));

    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
        cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
        return cList;
    }

    HBlock ret = parser_expression(term);
    cList->push_back(ret);
    //cList->push_back(std::make_shared<CBlockNoum>(  term->removeArticle()->repr()));
    return cList;
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, HBlockList CList) {
    return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("and"), CList);
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_OR(HTerm term, HBlockList CList) {
    return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("or"), CList);
}







HBlock CParser::parse_List_AND(std::vector<HTerm> term) {
    {
        auto sep = mk_HPredLiteral("and");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
            cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
            cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
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
            cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
            cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
            return cList;
        }
    }

    return nullptr;

}


HBlock CParser::parse_List_OR(std::vector<HTerm> term) {
	{
		auto sep = mk_HPredLiteral("or");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockList  cList = std::make_shared<CBlockList  >(std::list<HBlock>());
			cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
			cList = parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
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




HBlockList CParser::parse_Strict_COMMA_AND(HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("and"));
}

HBlockList CParser::parse_Strict_COMMA_OR(HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("or"));
}