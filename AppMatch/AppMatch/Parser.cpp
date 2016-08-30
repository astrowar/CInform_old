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




HBlockAssertion_is CParser::parserMatchIsCondition(HTerm term) 
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
                return std::make_shared<CBlockAssertion_isDirectAssign>(body, value);
            }
        }
    }
    return nullptr;

}


HBlockStaticDispatch
CParser::getStaticDispatchResolve(HTerm term) //Determina se este termo esta na lista de dispatchs dynamicos
{


    //Verifica se ja tem a matchPhase
    int maxID = 0;
    for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {
        MatchResult res = CMatch(term, it->matchPhase);
        if (res.result == Equals) {
            return std::make_shared<CBlockStaticDispatch>(it->entryId,
                                                          std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr()),
                                                          std::make_shared<CBlockNoum>(res.matchs["noum2"]->repr()));
        }
    }
    return nullptr;


}


DispatchArguments CParser::parser_buildMatchBlock_actionInput(HTerm term) {
    if (CList *cterm = dynamic_cast<CList *>(term.get())) {
        std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
        auto kv = parser_buildMatchBlock_actionInput(vterm);
        return kv;
    }

    std::vector<HPred> replcList;
    replcList.push_back(mk_HPredLiteral(term->repr()));

    //return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr()));
    return DispatchArguments(replcList, nullptr,
                             std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr())));
}

HBlockMatch CParser::parser_MatchArgument(HTerm term) 
{

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("kind"));
        predList.push_back(mk_HPredLiteral("called"));
        predList.push_back(mkHPredAny("var_named"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatch>(
                    std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
            HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
            return n1;
        } 
    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("kind"));
        predList.push_back(mk_HPredLiteral("-"));
        predList.push_back(mkHPredAny("var_named"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatch>(
                    std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
            HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
            return n1;
        }
    }

	std::cout << "Argument:  " <<  (term)->repr() << std::endl;

    return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->removeArticle()->repr()));
    return nullptr;
}


DispatchArguments CParser::parser_buildMatchBlock_actionInput(std::vector<HTerm> term) {

    std::cout << "what:  " << get_repr(term) << std::endl;
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("verb"));
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("]"));
        predList.push_back(mkHPredAny("with_word"));
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind2"));
        predList.push_back(mk_HPredLiteral("]"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
            HBlockMatch c3 = std::make_shared<CBlockMatch>(
                    std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));
            HBlockMatch c4 = parser_MatchArgument(res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
            replcList.push_back(mkHPredAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1, c3, arg2}));
            return DispatchArguments(replcList, mlist1, mlist2);

        }
    }
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("verb"));
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("]"));
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind2"));
        predList.push_back(mk_HPredLiteral("]"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
            HBlockMatch c3 = std::make_shared<CBlockMatch>(
                    std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));
            HBlockMatch c4 = parser_MatchArgument(res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
            replcList.push_back(mkHPredAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1, c3, arg2}));
            return DispatchArguments(replcList, mlist1, mlist2);

        }
    }
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("verb"));
		predList.push_back(mkHPredAny("aux"));
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind1"));
		predList.push_back(mk_HPredLiteral("]"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			HBlockMatch c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch c1a = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["aux"]->repr()));


			//HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mk_HPredLiteral(res.matchs["aux"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c1a, c2 }));
			return DispatchArguments(replcList, mlist1, mlist2);
		}
	}


    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("verb"));
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("]"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
			HBlockMatch c1 = nullptr;
			c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));


            //HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            //return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, c2}));
            return DispatchArguments(replcList, mlist1, mlist2);
        }
    }

    return DispatchArguments(std::vector<HPred>(), nullptr, nullptr);
}


HBlock CParser::STMT_understand_generic_redirect( HTerm  term, HBlock  output_term) {

	DispatchArguments match_predicate = parser_buildMatchBlock_actionInput( term);
	if (match_predicate.sentenceMatch == nullptr) return nullptr;
	HBlockUnderstandDynamic  retBlock = std::make_shared<CBlockUnderstandDynamic >(  match_predicate.sentenceMatch, match_predicate.staticArgumentMatch, output_term);
	int entryID = registerDynamicDispatch(match_predicate.staticPredicade,	match_predicate.sentenceMatch, output_term);


	return retBlock;
}

HBlock CParser::STMT_understand_Action_Assertion_static(std::vector<HTerm> term) {

    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("understand"));
        predList.push_back(mk_HPredLiteral(":"));
        predList.push_back(mkHPredAny("What"));
        predList.push_back(mk_HPredLiteral("as"));
        predList.push_back(mkHPredAny("Subst"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {


			 

            //auto input_noum =  std::make_shared<CBlockNoum>(res.matchs["What"]->repr());

            // existe uma action que Match com o Subst ???
            HBlock output_noum = nullptr;
            HBlockMatch sentence_match = nullptr;
            {

               auto sTerm = res.matchs["Subst"];
                {
                    sTerm = expandBract(sTerm);
                }

				//Rh um action !!
				std::vector<HPred> actionList;
				actionList.push_back(actionPredList);
				MatchResult res_action = CMatch(sTerm, actionList);
				if (res_action.result == Equals) {

					output_noum = std::make_shared<CBlockAction>(std::make_shared<CBlockNoum>((sTerm)->repr())); //An Action !!!
				}
				else
				{
					output_noum = parser_expression(res.matchs["Subst"]);
				}


				//Nao eh um action               
				//HBlock value = parser_expression( res.matchs["Subst"]);

				if (output_noum == nullptr) return nullptr;
				return STMT_understand_generic_redirect(res.matchs["What"], output_noum);

                //std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

				// Verifica se tem alguma Acao que corresponde ao termo de saida

                //std::vector<HPred> actionList;
               // actionList.push_back(actionPredList);
                //MatchResult res_action = CMatch(sTerm, actionList);
				if (res_action.result == Equals) {
					
					HBlockAction output_action = std::make_shared<CBlockAction>(std::make_shared<CBlockNoum>((sTerm)->repr()));

					output_noum = output_action;
					DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
					sentence_match = match_predicate.sentenceMatch;



					//std::cout << "predicate  " << get_repr( match_predicate.second ) << std::endl;

					actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, output_action));
					int entryID = registerDynamicDispatch(match_predicate.staticPredicade,	match_predicate.sentenceMatch);
					HBlockUnderstandStatic retBlock = std::make_shared<CBlockUnderstandStatic>(entryID,	match_predicate.staticArgumentMatch, output_noum);
					registerStaticDispatch(entryID, match_predicate.staticArgumentMatch, retBlock);

					return retBlock;
				}

                // nao tem acao pre-definida na saida ... tente criar
                {
                    //std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

                    HBlockStaticDispatch s_action = getStaticDispatchResolve(sTerm); // esse termo corresponde a outro undestand ? ..undestand chain
					if (s_action != nullptr) 
					{
						output_noum = s_action;
						auto match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
						sentence_match = match_predicate.sentenceMatch;

						actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, s_action));
						int entryID = registerDynamicDispatch(match_predicate.staticPredicade,
							match_predicate.sentenceMatch);
						HBlockUnderstandStatic retBlock = std::make_shared<CBlockUnderstandStatic>(entryID, match_predicate.staticArgumentMatch, s_action);
						registerStaticDispatch(entryID, match_predicate.staticArgumentMatch, retBlock);

						return retBlock;
					}

                }

				//Ok .. nao tem registro de nada analise o que esta na saida


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

std::list<HBlock> CParser::ToMatchList( std::vector<HPred> pvector, MatchResult result)
{
	std::list<HBlock> vlist;
	for(int j = 0; j< pvector.size();++j)
	{
		if (CPredAtom* vAtom = dynamic_cast < CPredAtom * >(pvector[j].get()))
		{
			vlist.push_back(std::make_shared<CBlockNoum>(vAtom->h->repr()));
		}
		else if (CPredAny * vAny = dynamic_cast < CPredAny* >(pvector[j].get()))
		{
			HBlock n1 = parser_expression(result.matchs[vAny->named]);
			vlist.push_back(n1);
		}
		else
		{
			std::cout << "error" << std::endl;
		}
	}
	return vlist;

}

//Uma das rotinas mais importantes. Ela altera  o proprio parser
HBlock CParser::STMT_understand_Assertion(std::vector<HTerm> term) {

    for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {

        MatchResult res_action = CMatch(term, it->matchPhase);
        if (res_action.result == Equals) 
		{
            HBlock n1 = parser_expression(res_action.matchs["noum1"]);
            HBlock n2 = nullptr;
            if (res_action.matchs.find("noum2") != res_action.matchs.end()) {
                n2 = parser_expression(res_action.matchs["noum2"]);
            } else {
                n2 = std::make_shared<CBlockNoum>("Nothing");
            }
			n1->dump("   ");
			n2->dump("   ");

			
			if (HBlockAction vAction = std::dynamic_pointer_cast<CBlockAction >(it->output))
			{
				return std::make_shared<CBlockActionCall>(vAction, n1,n2);
			}
			std::list<HBlock> resList = ToMatchList(it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockList>(resList);

			

			return 	  std::make_shared<CBlockDinamicDispatch>(clistResults); // it->output;
            return std::make_shared<CBlockStaticDispatch>(it->entryId, n1, n2);


        }

    }
    

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