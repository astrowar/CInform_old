//
// Created by Eraldo Rangel on 12/10/16.
//
#include "Parser.hpp"
#include "CBlockControlFlux.hpp"

HBlock   CParser::parser_if_condition(HTerm term)
{
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("or"));
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_if_condition(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_if_condition(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }


    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_expression(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }

    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_expression(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }


    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = parser_expression(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }


    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = parser_expression(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }

    return parser_expression( term); //default ...

    return nullptr;

}

HBlockList  CParser::parser_control_else(std::vector<HTerm> term) {
    {
        static std::vector<HPred> predList = {};
        if (predList.empty()) {
            predList.push_back(mk_HPredLiteral("else"));
 
        }
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
           
			auto token_else = std::make_shared<CBlockControlToken >("else");
            return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
        }
    }
    return nullptr;
}


HBlockList  CParser::parser_control_end(std::vector<HTerm> term)  
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("end"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			auto token_else = std::make_shared<CBlockControlToken >("end");
			return std::make_shared<CBlockList  >(std::list<HBlock>({ token_else }));
		}
	}
	return nullptr;
}


HBlockList  CParser::parser_control_if(std::vector<HTerm> term) {
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral("then"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock ACondition = parser_if_condition(res.matchs["Condition"]);
			auto token_if = std::make_shared<CBlockControlToken >("if");
			auto token_then = std::make_shared<CBlockControlToken >("then");
			return std::make_shared<CBlockList  >(std::list<HBlock>({ token_if,ACondition ,token_then  }));
		}
	}
	return nullptr;
}

HBlockList  CParser::STMT_control_flux(std::vector<HTerm> term) {

//identifica os IF, then ,else, while ,case , select da vida

	HBlockList rblock_if = (parser_control_if(term));
    if (rblock_if != nullptr) return rblock_if; 

	//HBlockList rblock_then = (parser_control_then(term));
 //   if (rblock_then != nullptr) return rblock_then;

	HBlockList rblock_else = (parser_control_else(term));
    if (rblock_else != nullptr) return rblock_else;

	HBlockList rblock_end = (parser_control_end(term));
    if (rblock_end != nullptr) return rblock_end;



    return nullptr;
}