#include "Parser.hpp"
 
#include <algorithm>

#include "CBlockInterpreterRuntime.hpp"
#include "CBlockMatch.hpp"
 
#include "CblockAssertion.hpp"
#include "CBlockUndestand.hpp"
#include "CBlockCommand.hpp"
#include "sharedCast.hpp"


CParser::CParser(HBlockInterpreter _interpreter) {
    interpreter = _interpreter;
    {
        std::list<HPred> alist;
        verbList = std::make_shared<CPredBooleanOr>("verbList", alist);
        verbList->blist.push_back(mk_HPredLiteral("contains"));
    }

    {
        std::list<HPred> alist;
        actionPredList = std::make_shared<CPredBooleanOr>("actionList", alist);
        actionPredList->blist.push_back(mk_HPredLiteral("getting"));
    }

    {
        std::list<HPred> alist;
        //actionDinamicDispatch = std::make_shared<CPredBooleanOr>("actionList", alist);
        //actionDinamicDispatch->blist.push_back(mk_HPredLiteral("getting"));
    }
}

CParser::~CParser() {
}


// 
//HBlock CParser::get_Noum(string named) const
//{
//	auto kv =  std::find_if(nregisters.begin(), nregisters.end(), [&](const NoumDefinition &a) {return   a.noum == named; });
// 
//	if (kv == nregisters.end()) return nullptr;
//	return kv->definition ;
//}

void CParser::set_Noum(NoumDefinition ndef) {
    nregisters.push_back(ndef);
}

void CParser::set_Noum(NoumDefinitions ndef) {
    nregisters.insert(nregisters.end(), ndef.begin(), ndef.end());
}




HBlockMatchIs CParser::parserMatchIsCondition(HTerm term)
{
    // Funcao Complexa ... determina todos os tipos de condicoes, tipo um Regex 
    //Default is a direct Asign
    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("MatchBody"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("valueToCheck"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch body = parser_MatchArgument(res.matchs["MatchBody"]);
            HBlockMatch value = parser_MatchArgument(res.matchs["valueToCheck"]);
            if (body != nullptr && value != nullptr) {
                return std::make_shared<CBlockMatchDirectIs>(body, value);
            }
        }
    }
    return nullptr;

}
 


HBlock CParser::parse_toDecide_Entry(std::vector<HTerm> term) {
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("to"));
        predList.push_back(mk_HPredLiteral("decide"));
        predList.push_back(mk_HPredLiteral(":"));
        return nullptr;
    }
}

HBlock CParser::parse_toDecide_Ret(std::vector<HTerm> term) {
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("decide"));
        predList.push_back(mk_HPredLiteral("on"));
        predList.push_back(mkHPredAny("Subst"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_expression(res.matchs["Subst"]);
            if (n1 == nullptr) return nullptr;
            return std::make_shared<CBlockToDecideOn>(n1);
        }
    }
    return nullptr;
}

HBlock CParser::parser_decides_Assertion(std::vector<HTerm> term) {

    HBlock verb_decideIn = parse_toDecide_Entry(term);
    if (verb_decideIn != nullptr) {
        return verb_decideIn;
    }

    HBlock verb_decideRet = parse_toDecide_Ret(term);
    if (verb_decideRet != nullptr) {
        return verb_decideRet;
    }

    return nullptr;


}

std::vector<HTerm> expandTerm( HTerm term)
{
    if (CList* clist =  asCList( term.get() ) )
    {
          return clist->asVector();
    }
    return {term};
}

HBlock CParser::sys_now_action(std::vector<HTerm> term) {
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("now"));
        predList.push_back(mkHPredAny("Assertion"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto nterms = expandTerm(res.matchs["Assertion"]);
            //parse_AssertionVerb
            //parse_AssertionDirectAssign

            {
                HBlockAssertion_is now_verb = parse_AssertionVerb(nterms);
                if (now_verb != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_verb);
                }
            }


            {
                HBlockAssertion_is now_is = parse_AssertionDirectAssign(nterms);
                if (now_is != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_is);
                }
            }
        }
    }
    return nullptr;
}



//Processa os smtm que sao do sistema
HBlock CParser::STMT_system_Assertion(std::vector<HTerm> term)
{

            auto d_now = (sys_now_action(term));
            if (d_now != nullptr) return d_now;

    return nullptr;
}

//Uma das rotinas mais importantes. Ela altera  o proprio parser
HBlock CParser::STMT_understand_Assertion(std::vector<HTerm> term) {

    auto d_action = (DynamicDispatch_action(term));
    if (d_action != nullptr) return d_action;
    

    auto p_action = STMT_understand_Action_Assertion_static(term);
    if (p_action != nullptr) return p_action;

    return nullptr;
}


HBlock CParser::parse_removeArticle(std::vector<HTerm> term) {
    if (term.size() > 1) {

        if (mk_HPredLiteral("the")->match(term.front()) == Equals) {
            return parser_expression(get_tail(term));
        }
    }
    return nullptr;
}


HBlock CParser::parse_noum(std::vector<HTerm> term) {
    std::vector<HPred> predList;
     
    //predList.push_back(undefinedArticle());
    predList.push_back(mkHPredAny("Noum"));
    MatchResult res = CMatch(term, predList);

    if (res.result == Equals) {
        string nstr = CtoString(res.matchs["Noum"]->removeArticle() );
        return std::make_shared<CBlockNoum>(nstr);
    }
    return nullptr;
}

HBlockAssertion_isInstanceOf CParser::parseAssertion_isInstanceOf(std::vector<HTerm> term) {
    //Injstance is Alwares derivadefrom a Kind
    {
        // is a kind definition ??
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Noum"));

        auto L_a_an_kind = mkHPredList("kindpart", {verb_IS(), undefinedArticle()});
        auto L_are_kinds = mkHPredList("kindpart", {verb_IS()});

        //predList.push_back(mkHPredBooleanOr("kindpart", L_a_an_kind, L_are_kinds));
        predList.push_back(L_a_an_kind);

        predList.push_back(mkHPredAny("KindBase"));

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            /*if (get_Noum(res.matchs["Noum"]->repr()) != nullptr)
            {
                throw res.matchs["Noum"]->repr() + " ja existe ";
                return nullptr;
            }
            */
            //HBlockInstance  noumInstance = std::make_shared<CBlockInstance> (res.matchs["Noum"]->removeArticle()->repr());
            //HBlockNoum           baseKind = std::make_shared<CBlockNoum>(res.matchs["KindBase"]->removeArticle()->repr());

            //return  std::make_shared<CBlockAssertion_isInstanceOf>(noumInstance, baseKind);
        }
    }
    return nullptr;

}




HBlock CParser::parseAssertionFirstTerm_Compose(HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = parseAssertionFirstTerm_COMMA_AND(term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}


HBlock CParser::parseAssertionFirstTerm(HTerm term) {
    return parseAssertionFirstTerm_Compose(term);
}


HBlock CParser::parseAssertionEnumSecondTerm(HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = parseAssertionFirstTerm_COMMA_OR(term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}

HBlock CParser::STMT_Decide_Assertion(std::vector<HTerm> lst) {
    HBlock assert_decide = parseAssertion_isDecide(lst);
    if (assert_decide != nullptr) {
        return assert_decide;
    }
    return nullptr;

}



HBlockProperty CParser::parse_PropertyOf(std::vector<HTerm> term) {
    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("property"));
        predList.push_back(mk_HPredLiteral("of"));
        predList.push_back(mkHPredAny("obj"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock a = parser_expression(res.matchs["property"]);
            if (a != nullptr) {
                HBlock b = parser_expression(res.matchs["obj"]);
                if (b != nullptr) {
                    //HBlockNoum  object_Name = std::make_shared<CBlockNoum>(res.matchs["obj"]->removeArticle()->repr());
                    return std::make_shared<CBlockProperty>(a, b);
                }
            }
        }
    }




    //{
    //	std::cout << get_repr(term) << std::endl;
    //	std::vector<HPred> predList;
    //	predList.push_back(mk_HPredLiteral("the"));
    //	predList.push_back(mkHPredAny("property"));
    //	predList.push_back(mk_HPredLiteral("of"));
    //	predList.push_back(mkHPredAny("obj"));
    //	MatchResult res = CMatch(term, predList);
    //	if (res.result == Equals)
    //	{
    //		HBlock a = parser(res.matchs["property"]);
    //		if (a != nullptr)
    //		{
    //			HBlock b = parser(res.matchs["obj"]);
    //			if (b != nullptr)
    //			{
    //				//HBlockNoum  object_Name = std::make_shared<CBlockNoum>(res.matchs["obj"]->removeArticle()->repr());
    //				return std::make_shared<CBlockProperty>(a, b);
    //			}
    //		}
    //	}
    //}
    return nullptr;
}


HBlockEnums CParser::parseAssertion_EnumTerms(HTerm enumList) {

    HBlockList elist = std::make_shared<CBlockList>(std::list<HBlock>());
    elist = parseAssertionFirstTerm_COMMA_OR(enumList, elist);
    if (elist->lista.empty()) {
        return nullptr;
    }

    std::vector<HBlockNoum> nlist;
    std::for_each(elist->lista.begin(), elist->lista.end(),
                  [&nlist](HBlock c) { nlist.push_back(asHBlockNoum(c)); });
    return std::make_shared<CBlockEnums>(nlist);

}


HBlock CParser::STMT_canBe_Assertion(std::vector<HTerm> lst) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("Target"));
    predList.push_back(mk_HPredLiteral("can"));
    predList.push_back(mk_HPredLiteral("be"));
    predList.push_back(mkHPredAny("EnumValues"));
    MatchResult res = CMatch(lst, predList);

    if (res.result != Equals) return nullptr;

    HBlockEnums definitionSecond = parseAssertion_EnumTerms(res.matchs["EnumValues"]);
    if (definitionSecond == nullptr) {
        return nullptr;
    }

    

    HBlock defintionFirst_Noum = parser_assertionTarger(res.matchs["Target"]);
    if (defintionFirst_Noum != nullptr) {
        return std::make_shared<CBlockAssertion_canBe>(defintionFirst_Noum, definitionSecond);
    }

    return nullptr;
}

HBlockInstanceVariable CParser::CProperty_called(HTerm term) {
    {
        // the torch has a brightness called brightnessLevel ;
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("kindName"));
        predList.push_back(mk_HPredLiteral("called"));
        predList.push_back(mkHPredAny("propName"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockNoum a = std::make_shared<CBlockNoum>(res.matchs["kindName"]->repr());
            HBlockNoum b = std::make_shared<CBlockNoum>(res.matchs["propName"]->repr());
            return std::make_shared<CBlockInstanceVariable>(a, b);
        }

    }

    {
        // the torch has a brightness   ;  -> called brightness
        HBlockNoum a = std::make_shared<CBlockNoum>(term->repr());
        HBlockNoum b = std::make_shared<CBlockNoum>(term->repr());
        return std::make_shared<CBlockInstanceVariable>(a, b);
    }

}


HBlock CParser::STMT_hasAn_Assertion(std::vector<HTerm> lst) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("Target"));
    predList.push_back(mk_HPredLiteral("has"));
    predList.push_back(undefinedArticle());
    predList.push_back(mkHPredAny("KindAndName"));
    MatchResult res = CMatch(lst, predList);

    if (res.result != Equals) {
        return nullptr;
    }

    HBlockInstanceVariable definitionProperty_kindAndName = CProperty_called(res.matchs["KindAndName"]);
    if (definitionProperty_kindAndName == nullptr) {
        return nullptr;
    }

    //HBlockNoum  defintionFirst_KindOrInstance = std::make_shared<CBlockNoum>( res.matchs["Target"]->removeArticle()->repr());
    HBlock defintionFirst_KindOrInstance = parser_kind_or_instance(res.matchs["Target"]);

    return std::make_shared<CBlockAssertion_InstanceVariable>(defintionFirst_KindOrInstance,
                                                              definitionProperty_kindAndName);
}



HBlock CParser::parser_stmt(HTerm term, HGroupLines inner, ErrorInfo *err) {
    if (CList *vlist = asCList(term.get())) {
        auto r = parser_stmt_inner(vlist->asVector(),inner,err);
        /*if (r == nullptr)
            std::cout << term->repr() << std::endl;*/

        return r;
    }
    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
}


HBlock CParser::parserBoolean(HTerm term) {
    if (CList *vlist = asCList(term.get())) {
        auto r = parserBoolean(vlist->asVector());
        if (r != nullptr) {
            return r;
        } else {
            //	std::cout << term->repr() << std::endl;
        }

    }
    return parser_expression(term);
}


HBlock CParser::parser_stmt_str(string str, HGroupLines inner, ErrorInfo *err) {
    str = decompose_bracket(str, "(");
    str = decompose_bracket(str, ")");
    str = decompose_bracket(str, ",");
    std::vector<HTerm> lst = decompose(str);
    return parser_stmt_inner(lst,inner,err);
}


HBlock CParser::Parser_Stmt(string str, bool dump )
{
	ErrorInfo err;
		return parser_stmt(str, dump, &err);
}
HBlock CParser::parser_stmt(string str,bool dump,ErrorInfo *err)
{
    HBlock b = parser_stmt_str(str,nullptr, err); //nao tem inner
    if (dump)
    {		
        b->dump("");  
        printf("\n");
    }
    return b;
}

std::vector<string>  split_new_lines(const string &str)   {
    auto p1 = str.begin();
    auto p2 = str.begin();
    std::vector<string> sentences;
    while (p2 != str.end())
    {
        if (*p2 =='\n')
        {
            sentences.push_back( string(p1,p2));
            printf("%s\n", sentences.back().c_str());
            p1 = p2;
            ++p1;
            p2 = p1;
            if (p2 == str.end()) break;
        }
        ++p2;
    }
    if(p1 != p2 )
    {
        sentences.push_back( string(p1,p2));
        printf("%s\n", sentences.back().c_str());
    }
   return sentences;
}
 
 HBlock  CParser::parser_GroupLine( std::string v , HGroupLines inner, ErrorInfo *err)
{
	auto vstr = decompose_bracket(v, "(");
	vstr = decompose_bracket(v, ")");
	vstr = decompose_bracket(v, ",");
	vstr = decompose_bracket(v, ":");
	std::vector<HTerm> lst = decompose(vstr);
	HBlock  rblock_stmt = parser_stmt_inner (lst, inner , err);
	if (err->hasError) return nullptr; 
	return rblock_stmt;
}

 HBlockComandList CParser::parser_stmt_inner(HGroupLines inner, ErrorInfo *err)
{
	std::list<HBlock> retBlocks;
	if (inner == nullptr)
	{
		return nullptr;
	}

	while (inner != nullptr)
	{
		for (auto it = inner->lines.begin(); it != inner->lines.end(); ++it)
		{
			HBlock blk;
			std::string rawLine = it->line;
			auto inext = std::next(it);
			HGroupLines _inner = nullptr;
			if (inext == inner->lines.end()) _inner = inner->inner;
			blk = parser_GroupLine(rawLine, _inner, err);
			if (err->hasError)
			{
				logError(err->msg+ " at line "+ std::to_string(inner->lines.front().linenumber)); 
				return nullptr;
			}

			if (blk == nullptr)
			{
			
				logError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				err->setError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				return nullptr;
			}
			retBlocks.push_back(blk);

		}
		inner = inner->next;
		if (inner == nullptr) break;
	}

	retBlocks = post_process_tokens(retBlocks ,  err );
	if (err->hasError)
	{
		err->msg = err->msg + "at line " + std::to_string(inner->lines.front().linenumber);
	}


	return  std::make_shared< CBlockComandList >(retBlocks);

}
std::list<HBlock> CParser::parser_GroupLines(HGroupLines pivot, ErrorInfo *err)
{

	auto r = parser_stmt_inner(pivot, err);
	if (r!=nullptr)
	{
		logError(err->msg);
		return r->lista;
	}

	return std::list<HBlock>();


	 
/*
	std::list<HBlock> retBlocks;
	if (pivot == nullptr)
	{
		return retBlocks;
	}

	while (pivot != nullptr)
	{
		for (auto it = pivot->lines.begin(); it != pivot->lines.end(); ++it)
		{
			HBlock blk;
			std::string rawLine = it->line;
			auto inext = std::next(it);
			HGroupLines _inner = nullptr;
			if (inext == pivot->lines.end()) _inner = pivot->inner;
			blk = parser_GroupLine(rawLine, _inner, err);
			if (err->hasError)   return std::list<HBlock>();
			if (blk == nullptr)
			{
				logError("Parser Error at " + std::to_string(pivot->lines.front().linenumber));
				err->setError("Parser Error at " + std::to_string(pivot->lines.front().linenumber));
				return std::list<HBlock>();
			}
			retBlocks.push_back(blk);

		}
		pivot = pivot->next;
		if (pivot == nullptr) break;
	}
	return retBlocks;
*/
}

HBlock CParser::parser_text(string str , ErrorInfo *err)
{
	 
    // quebra o text  em linhas e processa as linhas separadamente
    auto vlist = split_new_lines(str);
	HGroupLines pivot =  get_identation_groups("__FILE__",vlist,err);
	if (err->hasError) return nullptr;
	if (pivot == nullptr)
	{
		return nullptr;
	}
	 
    auto blist  = parser_stmt_inner(pivot,err); 
	if (err->hasError) return nullptr;
	return  blist;



   /* for(auto &v : vlist)
    {
		auto vstr = decompose_bracket(v, "(");
        vstr = decompose_bracket(v, ")");
        vstr = decompose_bracket(v, ",");
		std::vector<HTerm> lst = decompose(vstr);

		

		HBlockList rblock_control_flux = STMT_control_flux(lst);
		if (rblock_control_flux != nullptr)
		{
			blist.insert(blist.end(), rblock_control_flux->lista.begin(), rblock_control_flux->lista.end());
			continue;
		}
		
		HBlock  rblock_stmt = parser_stmt(lst);
		if (rblock_stmt != nullptr)
		{
			blist.push_back(rblock_stmt);
		}
    }

	std::list< HBlock > blist_next = group_tokens(blist);

    return  std::make_shared< CBlockList > (blist_next);*/


}


//interprete varias linhas de texto
HBlock CParser::parser_text(string str, bool dump )
{
	ErrorInfo err;
    HBlock b =  parser_text(str,&err);
    if (b) {
        if (dump) {
            b->dump("");
            printf("\n");
        }
    }
    else
    {
        printf("Parser Error\n");
    }
    return b;
}