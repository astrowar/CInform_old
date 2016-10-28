#include "Parser.hpp"
 


HBlock CParser::parser_kind(HTerm term)
{

	return parser_expression(term);
}
HBlock CParser::parser_kind_or_instance(HTerm term) { return parser_expression(term); }
HBlock CParser::parser_valueReference(HTerm term) { return parser_expression(term); }
HBlock CParser::parser_assertionTarger(HTerm term)
{
	HBlock pdet =  parser_List_selector(term);
	if (pdet != nullptr) return pdet;
	return parser_expression(term);
}
 


HBlock   CParser::parser_VerbAssign(std::vector<HTerm>& term)
{

	HBlock aVerb = parse_AssertionVerb(term);
	if (aVerb != nullptr)
	{
		return aVerb;
	}

	HBlock aDirect = parse_AssertionDirectAssign(term);
	if (aDirect != nullptr)
	{
		return aDirect;
	}

	return nullptr;
}


HBlock CParser::parser_expression(HTerm  term)
{
	if (CList *vlist = asCList(term.get())) {
		auto r = parser_expression(vlist->asVector());
		/*if (r == nullptr)
		std::cout << term->repr() << std::endl;*/
		return r;
	}
	//return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
	//std::cout << term->repr() << std::endl; 
	return std::make_shared<CBlockNoum>(CtoString( term->removeArticle()) );
}

HBlock CParser::parser_expression(std::vector<HTerm>&   lst)
{

	HBlock rblock_textEntry = (text_entry(lst));
	if (rblock_textEntry != nullptr) return rblock_textEntry;


	HBlock rblock_dynamicEntry_1 = (DynamicDispatch_action(lst));
	if (rblock_dynamicEntry_1 != nullptr) return rblock_dynamicEntry_1;

	HBlock rblock_assert_1 = (parser_VerbAssign(lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;


	HBlock noumListAND_Assign = parse_List_AND(lst);
    if (noumListAND_Assign != nullptr) {
        return noumListAND_Assign;
    }

	HBlock noumListOR_Assign = parse_List_OR(lst);
	if (noumListOR_Assign != nullptr) {
		return noumListOR_Assign;
	}

    HBlock detnoum_Assign = parse_removeArticle(lst);
    if (detnoum_Assign != nullptr) {
        return detnoum_Assign;
    }

	HBlock noum_propOF = parse_PropertyOf(lst);
	if (noum_propOF != nullptr) {
		return noum_propOF;
	}

 

    HBlock noum_Assign = parse_noum(lst);
    if (noum_Assign != nullptr) {
        return noum_Assign;
    }

	return nullptr;
}
HBlock CParser::parser_stmt_inner(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err)
{

	HBlock rblock_system_control = (STMT_control_flux(lst,inner , err));
	if (rblock_system_control != nullptr) return rblock_system_control;
 
	if (err->hasError) return nullptr;
	//Apenas os termos que iniciam uma sentenca completa



   /* HBlock rblock_decide_blc = (parser_decides_Assertion(lst));
    if (rblock_decide_blc != nullptr) return rblock_decide_blc;*/

	HBlock rblock_system_stmt = (STMT_system_Assertion(lst  ));
	if (rblock_system_stmt != nullptr) return rblock_system_stmt;

    HBlock rblock_understand_1 = (STMT_understand_Assertion(lst  ));
    if (rblock_understand_1 != nullptr) return rblock_understand_1;

	HBlock rblock_relatesTo = (STMT_relates_Assertion(lst ));
	if (rblock_relatesTo != nullptr) return rblock_relatesTo;

	HBlock rblock_decide_1 = (STMT_Decide_Assertion(lst, inner, err));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;

    HBlock rblock_verb_1n = (STMT_verb_Assertion_N(lst ));
    if (rblock_verb_1n != nullptr) return rblock_verb_1n;

    HBlock rblock_verb_1 = (STMT_verb_Assertion(lst ));
    if (rblock_verb_1 != nullptr) return rblock_verb_1;

    HBlock rblock_definition_1 = (STMT_Definition_Assertion(lst)); //To define ...
    if (rblock_definition_1 != nullptr) return rblock_definition_1;

   // HBlock rblock_decide_1 = (STMT_Decide_Assertion(lst,inner, err));
   // if (rblock_decide_1 != nullptr) return rblock_decide_1;
  

    HBlock rblock_assert_1 = (parser_Declaration_Assertion(lst));
    if (rblock_assert_1 != nullptr) return rblock_assert_1;

    HBlock rblock_assert_hasA = (STMT_hasAn_Assertion(lst));
    if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

    HBlock rblock_assert_2 = (STMT_canBe_Assertion(lst));
    if (rblock_assert_2 != nullptr) return rblock_assert_2;

    
	logError(get_repr(lst));

    return nullptr;

}
