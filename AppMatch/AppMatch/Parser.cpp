#include "Parser.h"
#include <iostream>
#include <algorithm>

#include "CBlockInterpreterRuntime.h"
#include "CBlockMatch.h"
 
#include "CblockAssertion.h"
#include "CBlockUndestand.h"

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
            HBlock body = parser_MatchArgument(res.matchs["MatchBody"]);
            HBlock value = parser_MatchArgument(res.matchs["valueToCheck"]);
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
    HBlockList c_list = std::make_shared<CBlockList>();
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
    HBlockList c_list = std::make_shared<CBlockList>();
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

    HBlockList elist = std::make_shared<CBlockList>();
    elist = parseAssertionFirstTerm_COMMA_OR(enumList, elist);
    if (elist->lista.empty()) {
        return nullptr;
    }

    std::vector<HBlockNoum> nlist;
    std::for_each(elist->lista.begin(), elist->lista.end(),
                  [&nlist](HBlock c) { nlist.push_back(std::dynamic_pointer_cast<CBlockNoum>(c)); });
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



HBlock CParser::parser_stmt(HTerm term) {
    if (CList *vlist = dynamic_cast<CList *>(term.get())) {
        auto r = parser_stmt(vlist->asVector());
        /*if (r == nullptr)
            std::cout << term->repr() << std::endl;*/

        return r;
    }
    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
}


HBlock CParser::parserBoolean(HTerm term) {
    if (CList *vlist = dynamic_cast<CList *>(term.get())) {
        auto r = parserBoolean(vlist->asVector());
        if (r != nullptr) {
            return r;
        } else {
            //	std::cout << term->repr() << std::endl;
        }

    }
    return parser_expression(term);
}


HBlock CParser::parser_stmt(string str) {
    str = decompose_bracket(str, "(");
    str = decompose_bracket(str, ")");
    str = decompose_bracket(str, ",");

    std::vector<HTerm> lst = decompose(str);
    return parser_stmt(lst);


}
HBlock CParser::parser_stmt(string str,bool dump)
{
	HBlock b =  parser_stmt(str);
	if (dump)
	{		
		b->dump(""); std::cout << std::endl;
	}
	return b;
}