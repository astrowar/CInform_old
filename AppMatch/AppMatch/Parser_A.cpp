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

HBlockMatch CParser::parser_What_Which_Assertion(HTerm term) {
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which());
		predList.push_back(mkHPredAny("kindReturn"));  // which (Person) is (the targert)
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch c1 = parser_MatchArgument(res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = parser_MatchArgument(res.matchs["RemainderQuery"]);

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
            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

           // return std::make_shared<CBlockMatch>(AValue);
			throw "un Implmeneted";
			return nullptr;
        }
    }

    return nullptr;

}

HBlock CParser::parseAssertion_DecideWhat(HTerm term) {
    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
}

HBlock CParser::parseAssertion_isDecide(std::vector<HTerm> term) {

   

    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("to"));
        predList.push_back(mk_HPredLiteral("decide"));
        predList.push_back(mkHPredAny("Match"));
        predList.push_back(mk_HPredLiteral(":"));
        predList.push_back(mkHPredAny("RemainBody"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatchIs a_match = parser_Match_IF_Assertion(res.matchs["Match"]);
			if (a_match)
			{
				std::cout << (res.matchs["RemainBody"]->repr()) << std::endl;
				HBlock body = parser_expression(res.matchs["RemainBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}


			HBlockMatch w_match = parser_What_Which_Assertion(res.matchs["Match"]);
			if (w_match)
			{
				std::cout << (res.matchs["RemainBody"]->repr()) << std::endl;
				HBlock body = parser_expression(res.matchs["RemainBody"]);
				return std::make_shared<CBlockToDecideWhat>(w_match, body);
			}

        }
    }

    return nullptr;
}

HBlock CParser::STMT_Definition_Assertion(std::vector<HTerm> term) {

    {
        std::vector<HPred> predList;


        auto c1 = mkHPredList("def_A", {mk_HPredLiteral("definition"), mk_HPredLiteral(":")});
        auto c2 = mk_HPredLiteral("definition:");
        predList.push_back(mkHPredBooleanOr("kindpart", c1, c2));

        predList.push_back(mkHPredAny("Match"));
        predList.push_back(mk_HPredLiteral("if"));
        predList.push_back(mkHPredAny("LogicalBody"));

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





