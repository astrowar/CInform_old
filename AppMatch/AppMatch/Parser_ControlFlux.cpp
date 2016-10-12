//
// Created by Eraldo Rangel on 12/10/16.
//
#include "Parser.hpp"

HBlock  CParser::parser_if_condition(HTerm term)
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

HBlock  CParser::parser_control_if(HTerm term) {
    {
        static std::vector<HPred> predList = {};
        if (predList.empty()) {
            predList.push_back(mk_HPredLiteral("if"));
            predList.push_back(mkHPredAny("Condition"));
            predList.push_back(mk_HPredLiteral("then"));
        }
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock AValue = parser_if_condition(res.matchs["Condition"]);

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }

    return nullptr;

}

HBlock  CParser::STMT_control_flux(HTerm term) {

//identifica os IF, then ,else, while ,case , select da vida

    HBlock rblock_if = (parser_control_if(term));
    if (rblock_if != nullptr) return rblock_if;


    HBlock rblock_then = (parser_control_then(term));
    if (rblock_then != nullptr) return rblock_then;

    HBlock rblock_else = (parser_control_else(term));
    if (rblock_else != nullptr) return rblock_else;

    HBlock rblock_end = (parser_control_end(term));
    if (rblock_end != nullptr) return rblock_end;



    return nullptr;
}