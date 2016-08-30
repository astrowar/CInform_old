#include "Parser.h"
#include <iostream>

HBlockKindAction CParser::parse_AssertionAction_secondPart( HTerm  term)
{
	
	{
		// and action applying to [one visible thing and requiring light]

		//std::cout << term->repr() << std::endl;
		std::vector<HPred> predList; 
		predList.push_back(undefinedArticle());
		predList.push_back(mk_HPredLiteral("action"));
		predList.push_back(mk_HPredLiteral("applying"));
		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mkHPredAny("ApplyRemainder"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			return std::make_shared<CBlockKindAction>("", applyTO);

		}
	}
	return nullptr;
}
HBlock CParser::parse_AssertionAction(std::vector<HTerm> term) {

    {
        // and action applying to [one visible thing and requiring light]

	    //std::cout << get_repr(term) << std::endl;
        std::vector<HPred> predList;

		predList.push_back(mkHPredAny("ActionName"));
		predList.push_back(verb_IS()); 
        predList.push_back(mkHPredAny("ApplyRemainder"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
	 
			HBlockKindAction applyTO = parse_AssertionAction_secondPart(res.matchs["ApplyRemainder"]);
			if (applyTO == nullptr) return nullptr;
			HBlock noum = parser_assertionTarger(res.matchs["ActionName"]);
			if (noum == nullptr) return nullptr;

			{
				
				HBlockKindAction action = applyTO;
				auto sActionName = CtoString(res.matchs["ActionName"]);
				HBlock _naction = std::make_shared<CBlockAction>(std::make_shared<CBlockNoum>(sActionName));
				HPred actionMatch = mk_HPredLiteral(sActionName);


				//	std::cout << "found " << actionMatch->repr()  << std::endl;

				actionPredList->blist.push_back(actionMatch);
				return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, applyTO);

			}

            //return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			//return std::make_shared<CBlockAssertion_isDirectAssign>(noum, applyTO);

        }
    }

    return nullptr;

}


HBlock CParser::parse_AssertionIsVariable(std::vector<HTerm> term) {
	 


    {
        // is a kind definition ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("VariableNoum"));

        auto L_a_an_kind = mkHPredList("kindpart", {verb_IS(), undefinedArticle()});
        auto L_are_kinds = mkHPredList("kindpart", {verb_IS()});

        predList.push_back(mkHPredBooleanOr("kindpart", L_a_an_kind, L_are_kinds));

        predList.push_back(mkHPredAny("KindBase"));
        predList.push_back(mkHPredList("variable", {mk_HPredLiteral("that"), mk_HPredLiteral("varies")}));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlock noumVariable = parser_expression(res.matchs["VariableNoum"]);
            HBlock baseKind = parser_kind(res.matchs["KindBase"]);
            return std::make_shared<CBlockAssertion_isVariable>(noumVariable, baseKind);
        }
    }
    return nullptr;

}

HBlockKindOfName CParser::parse_KindOf( HTerm  term)
{
	{
		 
		std::vector<HPred> predList;
		auto a_1 = mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind"), mk_HPredLiteral("of") });;
		auto a_2 = mkHPredList("kindDef", { mk_HPredLiteral("kind"), mk_HPredLiteral("of") });
		auto a_3 = mkHPredList("kindDef", { mk_HPredLiteral("kinds"), mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindBase_l", a_1, a_2, a_3));

		predList.push_back(mkHPredAny("kindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			return std::make_shared<CBlockKindOfName>(res.matchs["kindBase"]->removeArticle()->repr());
		}
	}

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind") }));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			return std::make_shared<CBlockKindOfName>(""); // no Base

		}
	}

	return nullptr;


}

HBlock CParser::parse_AssertionIsKindOf(std::vector<HTerm> term) {
	{
		// is a default ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS()); 
		predList.push_back(mkHPredAny("KindDef"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlock value = parse_KindOf(res.matchs["KindDef"]);
			if (value == nullptr) return nullptr;
			HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
		}
	}

    return nullptr;

}

HBlock CParser::parse_AssertionValuesOf(std::vector<HTerm> term) {

    // The colors are blue, green, yellow, and red.
    // The textures are rough, stubbly and smooth.
    // Price is a kind of value.  $1.99 specifies a price.
    {

    }


    // $1.99 specifies a price.
    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("valueName"));

        auto L_single = mkHPredList("spc", {mk_HPredLiteral("specifies"), undefinedArticle()});
        auto L_plural = mkHPredList("spc", {mk_HPredLiteral("specifies")});

        predList.push_back(mkHPredBooleanOr("spc_part", L_single, L_plural));

        predList.push_back(mkHPredAny("valueKind"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            //KindValue must exist 

            HBlock valueName = parser_expression(res.matchs["valueName"]);
            HBlock valueKind = parser_kind(res.matchs["valueKind"]);
            return std::make_shared<CBlockAssertion_isNamedValueOf>(valueName, valueKind);


        }
    }
    return nullptr;
}


HBlock CParser::parse_AssertionDefaultAssign(std::vector<HTerm> term) {

    {
        // is a default ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS());
        predList.push_back(mk_HPredLiteral("usually"));
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = parser_expression(res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isDefaultAssign>(noum, value);
        }
    }

    {
        // is a always ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS());
        predList.push_back(mk_HPredLiteral("always"));
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = parser_expression(res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isConstantAssign>(noum, value);
        }
    }

    {
        // is never  ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS());
        predList.push_back(mk_HPredLiteral("never"));
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = parser_expression(res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isForbiddenAssign>(noum, value);
        }
    }

    return nullptr;

}



HBlockAssertion_is CParser::parse_AssertionDirectAssign(std::vector<HTerm> term) {
    {
        // is a kind definition ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS_NOT());
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = parser_expression(res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isNotDirectAssign>(noum, value);
        }
    }
    {
        // is a kind definition ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlock value = parser_expression(res.matchs["Value"]);
            if (value == nullptr) return nullptr;

            if (HBlockKindAction action = std::dynamic_pointer_cast<CBlockKindAction>(value)) {
                auto sterm = expandBract(res.matchs["Noum"]);
                HBlock _naction = std::make_shared<CBlockAction>(std::make_shared<CBlockNoum>(sterm->repr()));


                HPred actionMatch = convert_to_predicate(sterm.get());
                //	std::cout << "found " << actionMatch->repr()  << std::endl;
                actionPredList->blist.push_back(actionMatch);

                return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, value);

            } else {
                HBlock noum = parser_assertionTarger(res.matchs["Noum"]);
                if (noum == nullptr) return nullptr;
                return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
            }

        }
    }

    return nullptr;

}




HBlock CParser::parser_Declaration_Assertion(std::vector<HTerm> lst)
{

    HBlock verb_Assign = parse_AssertionVerb(lst);
    if (verb_Assign != nullptr) {
        return verb_Assign;
    }

    HBlock action_Assign = parse_AssertionAction(lst);
    if (action_Assign != nullptr) {
        return action_Assign;
    }

    HBlock assert_variable = parse_AssertionIsVariable(lst);
    if (assert_variable != nullptr) {
        return assert_variable;
    }

    HBlock assert_kindof = parse_AssertionIsKindOf(lst);
    if (assert_kindof != nullptr) {
        return assert_kindof;
    }

    HBlock assert_values = parse_AssertionValuesOf(lst);
    if (assert_values != nullptr) {
        return assert_values;
    }

    HBlock assert_DefaultAssign = parse_AssertionDefaultAssign(lst);
    if (assert_DefaultAssign != nullptr) {
        return assert_DefaultAssign;
    }

    HBlock assert_Assign = parse_AssertionDirectAssign(lst);
    if (assert_Assign != nullptr) {
        return assert_Assign;
    }

    return nullptr;

}
