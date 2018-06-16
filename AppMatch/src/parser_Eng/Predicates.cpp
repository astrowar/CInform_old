// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


// Language terms to undestand English CInform


#include <match/CMatch.hpp>
#include <Parser/Parser.hpp>
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


using tokenIdent = string;

class LanguageModule
{
	 
};

class LanguageEnglish : public  LanguageModule
{
public :
	NSParser::CParser *p;
public:
	explicit LanguageEnglish(NSParser::CParser* p): p(p)
	{
	}

private:

	CPredSequence parse_AssertionAction_secondPart(tokenIdent ApplyRemainder )
	{
		return undefinedArticle() << pLiteral("action") << pLiteral("applying") << pLiteral("to") << pAny(ApplyRemainder);
	}

	CPredSequence parse_ActionCompositionName(tokenIdent ActionName, tokenIdent pred, tokenIdent pred_aux)
	{
		return pWord(ActionName) << pPreposition(pred) << pOr(pred_aux, pLiteral("to"), pLiteral("of"));
	}

	CPredSequence parse_AssertionAction(tokenIdent ActionName, tokenIdent ApplyRemainder)
	{
		return pAny(ActionName) << verb_IS() << undefinedArticle() << pLiteral("action") << pLiteral("applying") << pLiteral("to") << pAny(ApplyRemainder);

	}
	CPredSequence parse_AssertionIsLocalValue(tokenIdent VarName, tokenIdent VarValue)
	{
			return pLiteral("let") << pAny(VarName) << pLiteral("be") << pAny(VarValue);
	}

	CPredSequence parse_AssertionIsVariable(tokenIdent VariableNoum, tokenIdent KindBase)
	{
		auto L_a_an_kind = pList("kindpart", { verb_IS(), undefinedArticle() });
		auto L_are_kinds = pList("kindpart", { verb_IS() });
		return 	pAny(VariableNoum)<< (pOr("kindpart", L_a_an_kind, L_are_kinds))<< pAny(KindBase)	<< (pList("variable", { pLiteral("that"), pLiteral("varies") }));
	}

	CPredSequence parse_KindOf(tokenIdent kindBase )
	{
		auto a_1 = pList("kindDef", { undefinedArticle(), pLiteral("kind"), pLiteral("of") });;
		auto a_2 = pList("kindDef", { pLiteral("kind"), pLiteral("of") });
		auto a_3 = pList("kindDef", { pLiteral("kinds"), pLiteral("of") });
		return (pOr("kindBase_l", a_1, a_2, a_3)) << pAny(kindBase);
	}


	CPredSequence  parse_CompositionOf(tokenIdent kindBase , tokenIdent kindDst)
	{
		return pLiteral("phrase") << pAny(kindBase) << pLiteral("->") << pAny(kindDst); 
	}
	CPredSequence  parse_CompositionOf_b(tokenIdent kindBase, tokenIdent kindDst)
	{
		return pLiteral("relation") << pLiteral("of") << pAny(kindBase) << pLiteral("to") << pAny(kindDst);

	}

	CPredSequence  parse_CompositionOf_b(tokenIdent kindBase )
	{
		return pLiteral("list") << pLiteral("of") << pAny(kindBase);
	}

	CPredSequence parse_AssertionIsCompositionOf(tokenIdent Noum, tokenIdent CompDef)
	{
		return pAny(Noum) << verb_IS() << pAny(CompDef);
	}

	CPredSequence parse_AssertionIsKindOf(tokenIdent Noum, tokenIdent KindDef)
	{
		return pAny(Noum) << verb_IS() << pAny(KindDef);
	}


	CPredSequence parse_AssertionValuesOf(tokenIdent valueName, tokenIdent valueKind)
	{
		auto L_single = pList("spc", { pLiteral("specifies"), undefinedArticle() });
		auto L_plural = pList("spc", { pLiteral("specifies") });
		return  pAny(valueName) << (pOr("spc_part", L_single, L_plural)) << pAny(valueKind);
	}

	CPredSequence parse_AssertionDefaultAssign(tokenIdent Noum, tokenIdent Value)
	{
	  return 	pAny(Noum) << verb_IS() << pLiteral("usually") << pAny(Value);
	}

	CPredSequence parse_AssertionDefaultAssign_always(tokenIdent Noum, tokenIdent Value)
	{
		return 	pAny(Noum) << verb_IS() << pLiteral("always") << pAny(Value);
	}
	CPredSequence parse_AssertionDefaultAssign_never(tokenIdent Noum, tokenIdent Value)
	{
		return 	pAny(Noum) << verb_IS() << pLiteral("never") << pAny(Value);
	}
 


	CPredSequence parserAssertionDirectAssign_isNot(tokenIdent Noum ,tokenIdent Value)
	{
		return pAny(Noum) << verb_IS_NOT() << pAny(Value);
	}

	CPredSequence parserAssertionDirectAssign_is(tokenIdent Noum, tokenIdent Value)
	{
		return pAny(Noum) << verb_IS() << pAny(Value);
	}

	CPredSequence parse_AssertionVerb_is_not(tokenIdent N1, tokenIdent N2)
	{
		return  pAny(N1) << verb_IS_NOT() << p->verbList << pAny(N2);
	}
	CPredSequence parse_AssertionVerb_not(tokenIdent N1, tokenIdent N2)
	{
		return  pAny(N1) << pLiteral("not") << p->verbList << pAny(N2);
	}
	CPredSequence parse_AssertionVerb_is(tokenIdent N1, tokenIdent N2)
	{
		return pAny(N1) << verb_IS() << p->verbList << pAny(N2);
	}
 
	CPredSequence parse_AssertionVerb(tokenIdent N1, tokenIdent N2)
	{
		return pAny(N1) << p->verbList << pAny(N2);
	}

	CPredSequence parser_MatchIsConditionVerb_is(tokenIdent MatchBody, tokenIdent valueToCheck)
	{
		return pAny(MatchBody) << verb_IS() << p->verbList << pAny(valueToCheck); 
	}
	CPredSequence parser_MatchIsConditionVerb(tokenIdent MatchBody, tokenIdent valueToCheck)
	{
		return pAny(MatchBody) << p->verbList << pAny(valueToCheck);
	}
	CPredSequence STMT_verb_relation(tokenIdent Relation )
	{
	  return 	pOr("reverseLiteral", pLiteral("reverse"), pLiteral("reversed")) << pAny(Relation);
	}


	// the verb V implies a R relation
	// verb V implies a R relation
	CPredSequence STMT_verb_Assertion_N(tokenIdent VerbList, tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");
		auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
			pOr("article", pLiteral("a"),
				pLiteral("an"), pLiteral("the")) });
		 return (pOr("kindpart", L_the_verb, L_verb)) << pAny(VerbList) << L_the_verb_1 << pAny(Relation) << pLiteral("relation");
		  
	}

	// (the verb|verb) V Aux implies (a|an|the) R relation	
	// the verb NEXT TO imples an PROXIMITY relation
	CPredSequence STMT_verb_Assertion(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");
		auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
			pOr("article", pLiteral("a"),pLiteral("an"), pLiteral("the")) });
	return  (pOr("kindpart", L_the_verb, L_verb)) << pAny(Verb) << pAny(Aux) << L_the_verb_1 << pAny(Relation) << pLiteral("relation");
	 
	}
	CPredSequence STMT_verb_Assertion_b(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");
		return  (pOr("kindpart", L_the_verb, L_verb)) << pAny(Verb) << pAny(Aux) << pLiteral("implies") << pAny(Relation) << pLiteral("relation");
		 
	}

	CPredSequence STMT_verb_Assertion_c(tokenIdent Verb,  tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");
		auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
			pOr("article", pLiteral("a"),
				pLiteral("an"), pLiteral("the")) });

		return pOr("kindpart", L_the_verb, L_verb) << pAny(Verb) << L_the_verb_1 << pAny(Relation) << pLiteral("relation");

	}

	CPredSequence STMT_verb_Assertion_d(tokenIdent Verb, tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");

		return  pOr("kindpart", L_the_verb, L_verb) << pAny(Verb) << pLiteral("implies") << pAny(Relation) << pLiteral("relation");
    }

	CPredSequence STMT_verb_Assertion_e(tokenIdent Verb, tokenIdent Relation)
	{
		auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
		auto L_verb = pLiteral("verb");
		auto L_the_verb_4 = pLiteral("implies");
		return  pOr("kindpart", L_the_verb, L_verb) << pAny(Verb) << L_the_verb_4 << pAny(Relation) << pLiteral("relation");
    }





	CPredSequence STMT_canBe_Assertion(tokenIdent Target, tokenIdent EnumValues)
	{
		return pAny(Target) << pLiteral("can") << pLiteral("be") << pAny(EnumValues);
	}

	CPredSequence CProperty_called(tokenIdent kindName , tokenIdent propName)
	{
		return pAny(kindName) << pLiteral("called") << pAny(propName);
	}
	CPredSequence STMT_hasAn_Assertion(tokenIdent Target, tokenIdent KindAndName)
	{
		return pAny(Target) << pLiteral("has") << undefinedArticle() << pAny(KindAndName); 
	}

 







	CPredSequence parserBooleanNot(tokenIdent N ) 
	{
		return  pLiteral("not") << NSTerm::pAny(N);
    };

	CPredSequence parserBooleanAnd(tokenIdent n1, tokenIdent n2)
	{
		return  pAny(n1) << pLiteral("or") << pAny(n2);
	};


};

