#include "Parser.hpp"
 


HBlockMatch CParser::parser_What_Which_Assertion(HTerm term) {
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which());
		predList.push_back(mkHPredAny("kindReturn"));  // which (Person) is (the targert) -> Enforce (Return Value) as Person
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch  c1 = parser_MatchArgument(res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = parser_expression_match(res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				return AdjetiveMatch;
				//return std::make_shared<CBlockMatchDirectIs>(c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);
				throw "un Implmeneted";
				return nullptr;
			}
		}
	}
	return nullptr;
}

HBlockMatchIs CParser::parser_What_Which_Verb_Assertion(HTerm term) {
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which());
		predList.push_back(mkHPredAny("kindReturn"));  // which (Person) is (the targert) -> Enforce (Return Value) as Person
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));


			HBlockMatch  c1 = parser_MatchArgument(res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = parser_expression_match(res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				//return AdjetiveMatch;
				return std::make_shared<CBlockMatchIsVerb>(vrepr, c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);
				throw "un Implmeneted";
				return nullptr;
			}
		}
	}
	return nullptr;
}


HBlockMatchIs CParser::parser_Match_IF_Assertion(HTerm term)
{
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("if"));
        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
			HBlockMatch AValue = parser_expression_match(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = parser_expression_match(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockMatchDirectIs>(AValue, BValue);
        }
    }


	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("if"));
		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

			HBlockMatch AValue = parser_expression_match(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = parser_expression_match(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchIsVerb >(vrepr, AValue, BValue);
		}
	}

    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("if"));
        predList.push_back(mkHPredAny("AValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock AValue = parser_expression_match(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;
            auto r =  res.matchs["AValue"].get();
			logError(r->repr());
           // return std::make_shared<CBlockMatch>(AValue);
			throw "un Implmeneted";
			return nullptr;
        }
    }

    return nullptr;

}



HBlock CParser::parseAssertion_isDecide(std::vector<HTerm> term) {

   

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral("decide"));
			predList.push_back(mkHPredAny("Match"));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("RemainBody"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatchIs a_match = parser_Match_IF_Assertion(res.matchs["Match"]);
			if (a_match)
			{
				logMessage((res.matchs["RemainBody"]->repr()));
				HBlock body = parser_expression(res.matchs["RemainBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}

			HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(res.matchs["Match"]);
			if (vb_match)
			{
				logMessage((res.matchs["RemainBody"]->repr()));
				HBlock body = parser_expression(res.matchs["RemainBody"]);
				return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
			}


			HBlockMatch w_match = parser_What_Which_Assertion(res.matchs["Match"]);
			if (w_match)
			{
				logMessage((res.matchs["RemainBody"]->repr()));
				HBlock body = parser_expression(res.matchs["RemainBody"]);
				return std::make_shared<CBlockToDecideWhat>(w_match, body);
			}


        }
    }

    return nullptr;
}

HBlock CParser::STMT_Definition_Assertion(std::vector<HTerm> term) {

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto c1 = mkHPredList("def_A", { mk_HPredLiteral("definition"), mk_HPredLiteral(":") });
			auto c2 = mk_HPredLiteral("definition:");
			predList.push_back(mkHPredBooleanOr("kindpart", c1, c2));
			predList.push_back(mkHPredAny("Match"));
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("LogicalBody"));
		}

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			HBlockMatchIsVerb  v_match = parserMatchIsConditionVerb (res.matchs["Match"]);
			if (v_match != nullptr)
			{
				HBlock body = parserBoolean(res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(v_match, body);
			}

			HBlockMatchIs a_match = parserMatchIsCondition(res.matchs["Match"]);
			if (a_match != nullptr)
			{
				HBlock body = parserBoolean(res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}
			return nullptr;
        }
    }
    return nullptr;
}



