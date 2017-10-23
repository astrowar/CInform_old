// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"
#include "CBlockComposition.hpp"
#include "sharedCast.hpp"
 
using namespace CBlocking;
using namespace Interpreter;
using namespace NSTerm;
using namespace NSTerm::NSMatch;


HBlockKindAction NSParser::ParseAssertionSecondary::parse_AssertionAction_secondPart(CParser * p,  HTerm  term)
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
			HBlockActionApply applyTO = ParseAssertion::parse_AssertionAction_ApplyngTo(p,res.matchs["ApplyRemainder"]);
			//return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			return std::make_shared<CBlockKindAction>("", applyTO);

		}
	}


	{
		// and action applying to [one visible thing and requiring light]

		//std::cout << term->repr() << std::endl;
		std::vector<HPred> predList;
		predList.push_back(undefinedArticle());
		predList.push_back(mk_HPredLiteral("action"));
		predList.push_back(mk_HPredLiteral("applying"));
		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mk_HPredLiteral("nothing"));
		

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			//HBlockActionApply applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			
			HBlockActionApply applyTO =  std::make_shared<CBlockActionApply>( nullptr , nullptr );
			return std::make_shared<CBlockKindAction>("", applyTO);

		}
	}
	{
		// and action applying to [one visible thing and requiring light]

		//std::cout << term->repr() << std::endl;
		std::vector<HPred> predList;
		predList.push_back(undefinedArticle());
		predList.push_back(mk_HPredLiteral("action"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			//HBlockActionApply applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));

			HBlockActionApply applyTO = std::make_shared<CBlockActionApply>(nullptr, nullptr);
			return std::make_shared<CBlockKindAction>("", applyTO);

		}
	}

	return nullptr;
}
HBlock NSParser::ParseAssertion::parse_AssertionAction(CParser * p, std::vector<HTerm> term) {

    {
        // and action applying to [one visible thing and requiring light]

	    //std::cout << get_repr(term) << std::endl;
        std::vector<HPred> predList;

		predList.push_back(mkHPredAny("ActionName"));
		predList.push_back(verb_IS()); 
        predList.push_back(mkHPredAny("ApplyRemainder"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
	 
			HBlockKindAction applyTO = ParseAssertionSecondary::parse_AssertionAction_secondPart(p,res.matchs["ApplyRemainder"]);
			if (applyTO == nullptr) return nullptr;
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["ActionName"]);
			if (noum == nullptr) return nullptr;

			{
				
				HBlockKindAction action = applyTO;
				auto sActionName = CtoString(res.matchs["ActionName"]);
				//HBlock _naction = std::make_shared<CBlockAction>( (sActionName));
				//HBlock _naction = std::make_shared<CBlockAction>();
				
				HBlock _naction = std::make_shared<CBlockNoum>(sActionName);

				HPred actionMatch = mk_HPredLiteral(sActionName);


				//	std::cout << "found " << actionMatch->repr()  << std::endl;

				p->actionPredList->blist.push_back( actionMatch);
				return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, applyTO);

			}

            //return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			//return std::make_shared<CBlockAssertion_isDirectAssign>(noum, applyTO);

        }
    }

    return nullptr;

}



 
HBlock NSParser::ParseAssertion::parse_AssertionIsLocalValue(CParser * p, std::vector<HTerm>& term)
{
	// is a default ??
	std::vector<HPred> predList;
	predList.push_back(mk_HPredLiteral("let")); 
	predList.push_back(mkHPredAny("VarName"));
	predList.push_back(mk_HPredLiteral("be"));
	predList.push_back(mkHPredAny("VarValue"));

	MatchResult res = CMatch(term, predList);

	if (res.result == Equals)
	{ 
		auto varName = Expression::parser_expression(p, res.matchs["VarName"]);
		if (HBlockNoum varNameNoum = DynamicCasting::asHBlockNoum(varName))
		{
			//auto varName = std::make_shared<CBlockNoum>(res.matchs["VarName"]->removeArticle()->repr());
			auto varValue = Expression::parser_expression(p, res.matchs["VarValue"]);
			return std::make_shared<CBlockAssertion_isLocalVariable>(varNameNoum, varValue);
		}
	}


return nullptr;

}


HBlock NSParser::ParseAssertion::parse_AssertionIsVariable(CParser * p, std::vector<HTerm>& term) {
	 


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

            HBlock noumVariable = Expression::parser_expression(p,res.matchs["VariableNoum"]);
            HBlock baseKind = Expression::parser_kind(p,res.matchs["KindBase"]);
            return std::make_shared<CBlockAssertion_isVariable>(noumVariable, baseKind);
        }
    }
    return nullptr;

}

HBlockKindOfName NSParser::ParseAssertion::parse_KindOf(CParser * p, HTerm  term)
{
	{
		 
		std::vector<HPred> predList;
		auto a_1 = mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind"), mk_HPredLiteral("of") });;
		auto a_2 = mkHPredList("kindDef", { mk_HPredLiteral("kind"), mk_HPredLiteral("of") });
		auto a_3 = mkHPredList("kindDef", { mk_HPredLiteral("kinds"), mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindBase_l", a_1, a_2, a_3));

		predList.push_back(mkHPredAny("kindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{	 
			auto nn =   CtoString(res.matchs["kindBase"]->removeArticle());			 
			return std::make_shared<CBlockKindOfName>(nn);
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
 


 
 

HBlockKind   NSParser::Expression::parse_CompositionOf(CParser * p, HTerm  term)
{
  
	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("phrase"));		 
		predList.push_back(mkHPredAny("kindBase"));
		predList.push_back(mk_HPredLiteral("->"));
		predList.push_back(mkHPredAny("kindDst"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind =  parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				HBlockKind dkind = Expression::parser_kind_specification(p, res.matchs["kindDst"]);
				if (dkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionPhrase>(nkind, dkind);
				}
			} 
		}
	}



	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("relation"));
		predList.push_back(mk_HPredLiteral("of"));
		predList.push_back(mkHPredAny("kindBase"));
		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mkHPredAny("kindDst"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto nkind = parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				auto dkind = Expression::parser_kind_specification(p, res.matchs["kindDst"]);
				if (dkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionRelation>(  nkind, dkind);
				}
			}
		}
	}

	 



	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("list"));
		predList.push_back(mk_HPredLiteral("of"));
		predList.push_back(mkHPredAny("kindBase"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind = parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				return  std::make_shared<CBlockCompositionList>(  nkind);
			}
		}
	}

	 
	return nullptr;
}



HBlock NSParser::ParseAssertion::parse_AssertionIsCompositionOf(CParser * p, std::vector<HTerm>& term) {
	{
		// is a default ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("CompDef"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			auto value = Expression::parse_CompositionOf(p, res.matchs["CompDef"]);
			if (value == nullptr) return nullptr;
			HBlock noum = Expression::parser_assertionTarger(p, res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
		}
	}
	return nullptr;
}


HBlock NSParser::ParseAssertion::parse_AssertionIsKindOf(CParser * p, std::vector<HTerm>& term) {
	{
		// is a default ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS()); 
		predList.push_back(mkHPredAny("KindDef"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlock value = parse_KindOf(p,res.matchs["KindDef"]);
			if (value == nullptr) return nullptr;
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
		}
	}
    return nullptr;
}

HBlock NSParser::ParseAssertion::parse_AssertionValuesOf(CParser * p, std::vector<HTerm>& term) {

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

            HBlock valueName = Expression::parser_expression(p,res.matchs["valueName"]);
            HBlock valueKind = Expression::parser_kind(p,res.matchs["valueKind"]);
            return std::make_shared<CBlockAssertion_isNamedValueOf>(valueName, valueKind);


        }
    }
    return nullptr;
}


HBlock NSParser::ParseAssertion::parse_AssertionDefaultAssign(CParser *p, std::vector<HTerm>& term) {

    {
        // is a default ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));
        predList.push_back(verb_IS());
        predList.push_back(mk_HPredLiteral("usually"));
        predList.push_back(mkHPredAny("Value"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
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
            HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
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
            HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isForbiddenAssign>(noum, value);
        }
    }

    return nullptr;

}



HBlockAssertion_is NSParser::ParseAssertion::parse_AssertionDirectAssign(CParser * p, std::vector<HTerm>& term) {
    {
        // is a kind definition ??
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("Noum"));
			predList.push_back(verb_IS_NOT());
			predList.push_back(mkHPredAny("Value"));
		}

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
            if (noum == nullptr) return nullptr;
            HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
            if (value == nullptr) return nullptr;
            return std::make_shared<CBlockAssertion_isNotDirectAssign>(noum, value);
        }
    }
    {
        // is a kind definition ??
         
		static std::vector<HPred> predList ={};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("Noum"));
			predList.push_back(verb_IS());
			predList.push_back(mkHPredAny("Value"));
		}

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
            if (value == nullptr) return nullptr;

            if (HBlockKindAction action = DynamicCasting::asHBlockKindAction(value)) {
                auto sterm = expandBract(res.matchs["Noum"]);
				//HBlock _naction = std::make_shared<CBlockActionNamed>( (sterm->repr()));
				HBlock _naction = std::make_shared<CBlockNoum>((sterm->repr()));

                HPred actionMatch = convert_to_predicate(sterm.get());
                //	std::cout << "found " << actionMatch->repr()  << std::endl;
                p->actionPredList->blist.push_back(actionMatch);

                return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, value);

            } else {
                HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
                if (noum == nullptr) return nullptr;
                return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
            }

        }
    }

    return nullptr;

}




HBlock NSParser::ParseAssertion::parser_Declaration_Assertion(CParser * p, std::vector<HTerm>& lst)
{

    HBlock verb_Assign = parse_AssertionVerb(p,lst);
    if (verb_Assign != nullptr) {
        return verb_Assign;
    }

    HBlock action_Assign = parse_AssertionAction(p,lst);
    if (action_Assign != nullptr) {
        return action_Assign;
    }

    HBlock assert_variable = parse_AssertionIsVariable(p,lst);
    if (assert_variable != nullptr) {
        return assert_variable;
    }

	HBlock assert_local_value = parse_AssertionIsLocalValue(p, lst);
	if (assert_local_value != nullptr) {
		return assert_local_value;
	}

	HBlock assert_compostionOf = parse_AssertionIsCompositionOf(p, lst);
	if (assert_compostionOf != nullptr) {
		return assert_compostionOf;
	}

    HBlock assert_kindof = parse_AssertionIsKindOf(p,lst);
    if (assert_kindof != nullptr) {
        return assert_kindof;
    }

    HBlock assert_values = parse_AssertionValuesOf(p,lst);
    if (assert_values != nullptr) {
        return assert_values;
    }

    HBlock assert_DefaultAssign = parse_AssertionDefaultAssign(p,lst);
    if (assert_DefaultAssign != nullptr) {
        return assert_DefaultAssign;
    }

    HBlock assert_Assign = parse_AssertionDirectAssign(p,lst);
    if (assert_Assign != nullptr) {
        return assert_Assign;
    }

    return nullptr;

}
