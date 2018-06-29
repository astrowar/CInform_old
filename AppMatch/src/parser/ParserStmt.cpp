// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Parser\Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;


HBlockKind NSParser::Expression::parser_kind_specification(CParser *p, HTerm term)
{

	HBlockKind p_comp =    NSParser::Expression::parse_CompositionOf( p, term);
	if (p_comp != nullptr) return p_comp;

    HBlockNoum rx  = ParseAssertion::parse_noum(p, term);
    if (rx != nullptr)
    {
        return  std::make_shared<CBlockKindNamed>( rx->named ) ;
    }

	if (CList *vlist = asCList(term.get())) 
	{
		auto rvector = vlist->asVector();	 
		HBlockNoum r  = ParseAssertion::parse_noumVec(p, rvector);
		if (r != nullptr)
		{
			return  std::make_shared<CBlockKindNamed>( r->named ) ;
		}
        return nullptr;
	}

    

 
	return nullptr;
}



HBlock NSParser::Expression::parser_kind(CParser *p, HTerm term)
{
 
	return Expression::parser_expression(p,term);
}

 


HBlock NSParser::Expression::parser_kind_or_instance(CParser *p, HTerm term) { return Expression::parser_expression(p,term); }
HBlock NSParser::Expression::parser_valueReference(CParser *p, HTerm term) { return Expression::parser_expression(p,term); }
HBlock NSParser::Expression::parser_assertionTarger(CParser *p, HTerm term)
{
	HBlock pdet = ParseSelector::parser_List_selector(p,term);
	if (pdet != nullptr) return pdet;
	return Expression::parser_expression(p,term);
}
 


 
 

HBlock   NSParser::ParseAssertion::parser_VerbAssign(CParser * p, std::vector<HTerm>& term)
{

	HBlock adVerb = parse_AssertionAdverb(p, term);
	if (adVerb != nullptr)
	{
		return adVerb;
	}

	HBlock aVerb = parse_AssertionVerb(p,term);
	if (aVerb != nullptr)
	{
		return aVerb;
	}

	HBlock aDirect = parse_AssertionDirectAssign(p,term);
	if (aDirect != nullptr)
	{
		return aDirect;
	}

	return nullptr;
}


HBlock NSParser::Expression::parser_noumList(CParser *p, HTerm term)
{
	{
		CPredSequence predList = pAny("N1") << pAny("N2") << pAny("N3") << pAny("N4");
		MatchResult res = CMatch(term, predList);
		if (res.result == EqualResulting::Equals)
		{
			HBlockNoum  n1 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockNoum n2 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					HBlockNoum n3 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N3"]);
					if (n3 != nullptr)
					{
						HBlockNoum n4 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N4"]);
						if (n4 != nullptr)
						{
							return  std::make_shared<CBlockList>(std::list<HBlock >{n1,n2,n3,n4});
						}
					}
				}
			}
		}
	}




	{
		CPredSequence predList = pAny("N1") << pAny("N2") << pAny("N3")  ;
		MatchResult res = CMatch(term, predList);
		if (res.result == EqualResulting::Equals)
		{
			HBlockNoum  n1 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockNoum n2 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					HBlockNoum n3 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N3"]);
					if (n3 != nullptr)
					{ 
							return  std::make_shared<CBlockList>(std::list<HBlock >{n1, n2, n3 });						 
					}
				}
			}
		}
	}





	{
		CPredSequence predList = pAny("N1") << pAny("N2");
		MatchResult res = CMatch(term, predList);
		if (res.result == EqualResulting::Equals)
		{
			HBlockNoum  n1 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockNoum n2 = NSParser::ParseAssertion::parse_noum(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{ 
					return  std::make_shared<CBlockList>(std::list<HBlock >{n1, n2});						 
				}
			}
		}
	}



	return nullptr;

}




HBlock NSParser::Expression::parser_expression(CParser *p, HTerm  term)
{
	if (CList *vlist = asCList(term.get())) {
		auto rvector = vlist->asVector();
		auto r = parser_expression_lst(p,rvector);
		if (r == nullptr)
		{
			//auto ss = term->repr();
			//printf("@36  %s \n", ss.c_str());
		}

		return r;
	}
	//return std::make_shared<CBlockNoumStr>(term->removeArticle()->repr());
	//std::cout << term->repr() << std::endl; 
	{
		//auto ss = term->repr();
		//printf("@35  %s \n", ss.c_str());
	}
	std::string hString = CtoString(term->removeArticle());

	while (hString.back() == '\t')
	{
		hString = hString.substr(0, hString.size() - 1);
	}
	while (hString.front() == '\t')
	{
		hString = hString.substr(1, hString.size() - 1);
	}

	return std::make_shared<CBlockNoumStr>(hString);
}

HBlock  NSParser::Expression::parser_expression_lst(CParser *p, std::vector<HTerm>&   lst)
{

	HBlock rblock_literalEntry = (Statement::text_literal(p, lst));
	if (rblock_literalEntry != nullptr) return rblock_literalEntry;

	HBlock rblock_textEntry = (Statement::text_entry(p,lst));
	if (rblock_textEntry != nullptr) return rblock_textEntry;

	 

	HBlock adapt_verb = ParseGrammar::expression_adapt_verb(p,lst);
	if (adapt_verb != nullptr) {
		return adapt_verb;
	}

	HBlock rblock_dynamicEntry_1 = (DynamicDispatch::DynamicDispatch_action(p,lst));
	if (rblock_dynamicEntry_1 != nullptr) return rblock_dynamicEntry_1;

	 


	HBlock rblock_Lookup = (ParseRelation::DynamicLookup_Seletor(p,lst));
	if (rblock_Lookup != nullptr) return rblock_Lookup;

	HBlock rblock_phrase_1 = (DynamicDispatch::parser_PhraseInvoke(p, lst));
	if (rblock_phrase_1 != nullptr) return rblock_phrase_1;
	 

	HBlock rblock_assert_1 = (ParseAssertion::parser_VerbAssign(p,lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;


	HBlock noumListAND_Assign = ParseList::parse_List_AND(p,lst);
    if (noumListAND_Assign != nullptr) {
        return noumListAND_Assign;
    }

	HBlock noumListOR_Assign = ParseList::parse_List_OR(p,lst);
	if (noumListOR_Assign != nullptr) {
		return noumListOR_Assign;
	}

	HBlock noumListNeutral_Assign = ParseList::parse_List_Neutral(p, lst);
	if (noumListNeutral_Assign != nullptr) {
		return noumListNeutral_Assign;
	}


    HBlock detnoum_Assign = ParseAssertion::parse_removeArticle(p,lst);
    if (detnoum_Assign != nullptr) {
        return detnoum_Assign;
    }

	HBlock noum_propOF = ParseAssertion::parse_PropertyOf(p,lst);
	if (noum_propOF != nullptr) {
		return noum_propOF;
	}

	HBlock relation_argument = ParseAssertion::parse_RelationArgument(p, lst);
	if (relation_argument != nullptr) {
		return relation_argument;
	}
	 
	HBlock noum_decide = ParseAssertion::parse_decide_on(p, lst);
	if (noum_decide != nullptr) {
		return noum_decide;
	}
 
    HBlock noum_Assign = ParseAssertion::parse_noumVec(p,lst);
    if (noum_Assign != nullptr) {
        return noum_Assign;
    }

 


	// fail back !
	HBlock match_Assign = ExpressionMatch::parser_expression_match(p, lst);
	if (match_Assign != nullptr) {
		return match_Assign;
	}

	return nullptr;
}
HBlock NSParser::Statement::parser_stmt_inner(CParser * p, std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err)
{


	HBlock rblock_unit = (ControlFlux::STMT_unit_test(p, lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_unit != nullptr) return rblock_unit;



	HBlock rblock_system_control = (ControlFlux::STMT_control_flux(p,lst,inner , err));
	if (err->hasError) return nullptr;
	if (rblock_system_control != nullptr) return rblock_system_control;
 
	if (err->hasError) return nullptr;
	//Apenas os termos que iniciam uma sentenca completa

	HBlock rblock_tryEntry_1 = (DynamicDispatch::TryDispatch_action(p,lst));
 
	if (rblock_tryEntry_1 != nullptr) return rblock_tryEntry_1;

   /* HBlock rblock_decide_blc = (parser_decides_Assertion(lst));
    if (rblock_decide_blc != nullptr) return rblock_decide_blc;*/

	HBlock rblock_system_stmt = (ParseAssertion::STMT_system_Assertion(p,lst  ));
	if (err->hasError) return nullptr;
	if (rblock_system_stmt != nullptr) return rblock_system_stmt;

    HBlock rblock_understand_1 = (ParseAssertion::STMT_understand_Assertion(p,lst  ));
 
    if (rblock_understand_1 != nullptr) return rblock_understand_1;

	HBlock rblock_action_controls = (ParseAction::STMT_Action_Controls(p,lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_action_controls != nullptr) return rblock_action_controls;

	HBlock rblock_phraseInvoke = (ParseAction::STMT_phrase_Invoken(p, lst));
	if (rblock_phraseInvoke != nullptr) return rblock_phraseInvoke;

 

	HBlock rblock_relatesTo = (ParseRelation::STMT_relates_Assertion(p,lst ));
	if (rblock_relatesTo != nullptr) return rblock_relatesTo;

	HBlock rblock_decide_1 = (ParseAssertion::STMT_Decide_Assertion(p,lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_decide_1 != nullptr) return rblock_decide_1;

	HBlock rblock_phrase_1 = (ParseAssertion::STMT_Declare_Phrase(p, lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_phrase_1 != nullptr) return rblock_phrase_1;


    HBlock rblock_verb_1n = (Verbal::STMT_verb_Assertion_N(p,lst,err ));
	if (err->hasError) return nullptr;
    if (rblock_verb_1n != nullptr) return rblock_verb_1n;

    HBlock rblock_verb_1 = (Verbal::STMT_verb_Assertion(p,lst ,err));
	if (err->hasError) return nullptr;
    if (rblock_verb_1 != nullptr) return rblock_verb_1;

    HBlock rblock_definition_1 = (ParseDecide::STMT_Definition_Assertion(p,lst)); //To define ...
    if (rblock_definition_1 != nullptr) return rblock_definition_1;

   // HBlock rblock_decide_1 = (STMT_Decide_Assertion(lst,inner, err));
   // if (rblock_decide_1 != nullptr) return rblock_decide_1;
  

    HBlock rblock_assert_1 = (ParseAssertion::parser_Declaration_Assertion(p,lst));
    if (rblock_assert_1 != nullptr) return rblock_assert_1;

    HBlock rblock_assert_hasA = (ParseAssertion::STMT_hasAn_Assertion(p,lst));
    if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

    HBlock rblock_assert_2 = (ParseAssertion::STMT_canBe_Assertion(p,lst));
    if (rblock_assert_2 != nullptr) return rblock_assert_2;

	HBlock rblock_register_verb = (ParseGrammar::STMT_register_verb(p,lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_register_verb != nullptr) return rblock_register_verb;
    
	HBlock rblock_pass = (ControlFlux::STMT_pass(p, lst, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_pass != nullptr) return rblock_pass;



	//logError(get_repr(lst));

    return nullptr;

}
