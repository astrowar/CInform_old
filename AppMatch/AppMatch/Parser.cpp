#include "Parser.h"
#include <iostream>
#include <algorithm>

#include "CBlockInterpreterRuntime.h"
#include "CBlockMatch.h"
#include "CBlockBoolean.h"
#include "CblockAssertion.h"

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




HBlockAssertion_is CParser::parserMatchIsCondition(HTerm term) {
    // Funcao Complexa ... determina todos os tipos de condicoes, tipo um Regex


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

HBlockMatch CParser::parser_MatchArgument(HTerm term) {

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
        predList.push_back(mk_HPredLiteral("["));
        predList.push_back(mkHPredAny("kind1"));
        predList.push_back(mk_HPredLiteral("]"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
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
                //std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;
                std::vector<HPred> actionList;
                actionList.push_back(actionPredList);
                MatchResult res_action = CMatch(sTerm, actionList);
                if (res_action.result == Equals) {
                    HBlockAction output_action = std::make_shared<CBlockAction>(
                            std::make_shared<CBlockNoum>((sTerm)->repr()));
                    output_noum = output_action;
                    DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
                    sentence_match = match_predicate.sentenceMatch;

                    //std::cout << "predicate  " << get_repr( match_predicate.second ) << std::endl;

                    actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, output_action));

                    HBlockUnderstandStatic retBlock = std::make_shared<CBlockUnderstandStatic>(
                            match_predicate.staticArgumentMatch, output_noum);

                    int entryID = registerDynamicDispatch(match_predicate.staticPredicade,
                                                          match_predicate.sentenceMatch);
                    registerStaticDispatch(entryID, match_predicate.staticArgumentMatch, retBlock);

                    return retBlock;
                }

                //is not a action registed
                {
                    std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

                    HBlockStaticDispatch s_action = getStaticDispatchResolve(sTerm);
                    if (s_action != nullptr) {

                        output_noum = s_action;
                        auto match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
                        sentence_match = match_predicate.sentenceMatch;

                        actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, s_action));

                        HBlockUnderstandStatic retBlock = std::make_shared<CBlockUnderstandStatic>(
                                match_predicate.staticArgumentMatch, s_action);

                        int entryID = registerDynamicDispatch(match_predicate.staticPredicade,
                                                              match_predicate.sentenceMatch);
                        registerStaticDispatch(entryID, match_predicate.staticArgumentMatch, retBlock);

                        return retBlock;
                    }

                }
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

    HBlock verb_decideIn = CParser::parse_toDecide_Entry(term);
    if (verb_decideIn != nullptr) {
        return verb_decideIn;
    }

    HBlock verb_decideRet = CParser::parse_toDecide_Ret(term);
    if (verb_decideRet != nullptr) {
        return verb_decideRet;
    }

    return nullptr;


}

//Uma das rotinas mais importantes. Ela altera  o proprio parser
HBlock CParser::STMT_understand_Assertion(std::vector<HTerm> term) {

    for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {

        MatchResult res_action = CMatch(term, it->matchPhase);
        if (res_action.result == Equals) {
            HBlock n1 = parser_expression(res_action.matchs["noum1"]);
            HBlock n2 = nullptr;
            if (res_action.matchs.find("noum2") != res_action.matchs.end()) {
                n2 = parser_expression(res_action.matchs["noum2"]);
            } else {
                n2 = std::make_shared<CBlockNoum>("Nothing");
            }
            return std::make_shared<CBlockStaticDispatch>(it->entryId, n1, n2);


        }

    }
    

    auto p_action = STMT_understand_Action_Assertion_static(term);
    if (p_action != nullptr) return p_action;

    return nullptr;
}

 
HBlock CParser::STMT_verb_Assertion_N(std::vector<HTerm> term) {
    auto L_the_verb = mkHPredList("vinitial", {mk_HPredLiteral("the"), mk_HPredLiteral("verb")});
    auto L_verb = mk_HPredLiteral("verb");
    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("VerbList"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});
        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HPred verbMatch;
            HBlock a_verb;
            HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            if (CList *plist = dynamic_cast<CList *>(res.matchs["VerbList"].get())) {
                //eh uma lista

                HBlockList clist = std::make_shared<CBlockList>();

                verbMatch = mkHPredList("VerbMatch", {});
                CPredList *cpList = reinterpret_cast<CPredList *>(verbMatch.get());

                for (auto ip : plist->lst) {
                    clist->push_back(std::make_shared<CBlockNoum>(ip->repr()));
                    cpList->plist.push_back(mk_HPredLiteral(ip->repr()));
                }
                a_verb = clist;

                verbList->blist.push_back(verbMatch);
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

            } else {
                //nao eh uma lista :-(
                return nullptr;
            }
        }

    }
    return nullptr;

}

HBlock CParser::STMT_verb_Assertion(std::vector<HTerm> term) {

    auto L_the_verb = mkHPredList("vinitial", {mk_HPredLiteral("the"), mk_HPredLiteral("verb")});
    auto L_verb = mk_HPredLiteral("verb");
    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mkHPredAny("Aux"));

        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});
        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>();
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
        }

    }

    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mkHPredAny("Aux"));
        predList.push_back(mk_HPredLiteral("implies"));
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>();
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
        }

    }

    {
        //Teste de carga

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});

        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;
            HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

        }

    }

    {
        //Teste de carga

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mk_HPredLiteral("implies"));
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;
            HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

        }

    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});

        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = dynamic_cast<CList *>(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>();
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                int nv = inList.size();

                //std::cout << res.matchs["Verb"]->repr() << std::endl;
                if (a_verb != nullptr) {

                    HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    verbList->blist.push_back(verbMatch);
                    return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                }
            } else {

                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
                HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            }
        }

    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_4 = mk_HPredLiteral("implies");
        predList.push_back(L_the_verb_4);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = dynamic_cast<CList *>(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>();
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                if (a_verb != nullptr) {
                    HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    verbList->blist.push_back(verbMatch);
                    return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                }
            } else {
                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
                HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            }
        }

    }

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

HBlock CParser::parse_List_AND(std::vector<HTerm> term) {
    {
        auto sep = mk_HPredLiteral("and");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList cList = std::make_shared<CBlockList>();
            cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
            cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
            return cList;
        }
    }

    {
        auto sep = mk_HPredLiteral("or");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            return nullptr;
        }
    }
    {
        auto sep = mk_HPredLiteral(",");
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(sep);
        predList.push_back(mkHPredAny("N2"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList cList = std::make_shared<CBlockList>();
            cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
            cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
            return cList;
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
        return std::make_shared<CBlockNoum>(res.matchs["Noum"]->removeArticle()->repr());
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


HBlockList CParser::parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep) {

    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(sep);
    predList.push_back(mkHPredAny("N2"));
    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        HBlockList cList = std::make_shared<CBlockList>();
        cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
        cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
        return cList;
    }
    return nullptr;
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, HBlockList cList) {
    std::vector<HPred> predList;
    predList.push_back(mkHPredAny("N1"));
    predList.push_back(mkHPredBooleanOr("sep", mk_HPredLiteral(","), sep));
    predList.push_back(mkHPredAny("N2"));

    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
        cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
        return cList;
    }

    HBlock ret = parser_expression(term);
    cList->push_back(ret);
    //cList->push_back(std::make_shared<CBlockNoum>(  term->removeArticle()->repr()));
    return cList;
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, HBlockList CList) {
    return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("and"), CList);
}

HBlockList CParser::parseAssertionFirstTerm_COMMA_OR(HTerm term, HBlockList CList) {
    return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("or"), CList);
}

HBlockList CParser::parse_Strict_COMMA_AND(HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("and"));
}

HBlockList CParser::parse_Strict_COMMA_OR(HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("or"));
}


HBlock CParser::parseAssertionFirstTerm_Compose(HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>();
    c_list = CParser::parseAssertionFirstTerm_COMMA_AND(term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        std::swap(rt, c_list->lista.front());
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
    c_list = CParser::parseAssertionFirstTerm_COMMA_OR(term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        std::swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}

HBlock CParser::STMT_Decide_Assertion(std::vector<HTerm> lst) {
    HBlock assert_decide = CParser::parseAssertion_isDecide(lst);
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


HBlock CParser::parser_stmt(std::string str) {
    str = decompose_bracket(str, "(");
    str = decompose_bracket(str, ")");
    str = decompose_bracket(str, ",");

    std::vector<HTerm> lst = decompose(str);
    return parser_stmt(lst);


}
