#include <vector>
#include "Parser.h"
#include <iostream>




DispatchArguments CParser::parser_buildMatchBlock_actionInput(HTerm term) {
    if (CList *cterm = asCList(term.get())) {
        std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
        auto kv = parser_buildMatchBlock_actionInput(vterm);
        return kv;
    }

    std::vector<HPred> replcList;
    replcList.push_back(mk_HPredLiteral(term->repr()));

    //return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr()));
    return DispatchArguments(replcList, nullptr,
                             std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(term->repr())));
}



HBlockStaticDispatch CParser::getStaticDispatchResolve(HTerm term) //Determina se este termo esta na lista de dispatchs dynamicos
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

HBlockMatch CParser::parser_MatchArgument(std::vector<HTerm> term )
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("kind"));
			predList.push_back(mk_HPredLiteral("called"));
			predList.push_back(mkHPredAny("var_named"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(
				std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("kind"));
			predList.push_back(mk_HPredLiteral("-"));
			predList.push_back(mkHPredAny("var_named"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(
				std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}
	}
	 
 
	return nullptr;
}

HBlockMatch CParser::parser_MatchArgument(HTerm term) 
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("ListKind"));
			predList.push_back(mk_HPredLiteral("called"));
			predList.push_back(mkHPredAny("var_named"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			CTerm* cterm = res.matchs["ListKind"]->removeArticle();
			//cterm eh uma lista ??
			if (CList* clist = asCList(cterm))
			{
				HBlockMatchAND mmlist = std::make_shared<CBlockMatchAND>(std::list<HBlockMatch>());
				for(auto &ci : clist->lst  )
				{
					auto  str_i =  ci->removeArticle()->repr();
					HBlockMatch mi = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(str_i));
					mmlist->matchList.push_back(mi);
				}
				//HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["ListKind"]->removeArticle()->repr()));
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), mmlist);
				return n1;
			}
		}
	}
    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("kind"));
			predList.push_back(mk_HPredLiteral("called"));
			predList.push_back(mkHPredAny("var_named"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(
                    std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
            HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
            return n1;
        } 
    }

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("kind"));
			predList.push_back(mk_HPredLiteral("-"));
			predList.push_back(mkHPredAny("var_named"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(
                    std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
            HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
            return n1;
        }
    }
	std::cout << "Argument:  " <<  (term)->repr() << std::endl;
    return std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(CtoString(expandBract(term)->removeArticle())));
    return nullptr;
}



DispatchArguments CParser::parser_buildMatchBlock_actionInput(std::vector<HTerm> term) {

    std::cout << "what:  " << get_repr(term) << std::endl;
    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{

			predList.push_back(mkHPredAny("verb"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
			predList.push_back(mk_HPredLiteral("]"));
			predList.push_back(mkHPredAny("with_word"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind2"));
			predList.push_back(mk_HPredLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
            HBlockMatch c3 = std::make_shared<CBlockMatchNoum>(
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
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
			predList.push_back(mk_HPredLiteral("]"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind2"));
			predList.push_back(mk_HPredLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
          
            HBlockMatch c4 = parser_MatchArgument(res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            
            replcList.push_back(mkHPredAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1,   arg2}));
            return DispatchArguments(replcList, mlist1, mlist2);

        }
    }
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
			predList.push_back(mkHPredAny("aux"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
			predList.push_back(mk_HPredLiteral("]"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch c1a = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["aux"]->repr()));


			//HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
			
			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mk_HPredLiteral(res.matchs["aux"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c1a, arg1 }));
			return DispatchArguments(replcList, mlist1, mlist2);
		}
	}


    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
			predList.push_back(mk_HPredLiteral("]"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
			HBlockMatch c1 = nullptr;
			c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));


            //HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = parser_MatchArgument(res.matchs["kind1"]);
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            //return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1 }));
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
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("understand"));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("What"));
			predList.push_back(mk_HPredLiteral("as"));
			predList.push_back(mkHPredAny("Subst"));
		}

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

					output_noum = std::make_shared<CBlockAction>( ((sTerm)->repr())); //An Action !!!
				}
				else
				{
					output_noum = parser_expression(res.matchs["Subst"]);

					//Interpretei 
					std::cout << "Interpretei " << sTerm->repr()   << std::endl;
					std::cout << "Como "   << std::endl;
					output_noum->dump("          ");
					std::cout << "---" << std::endl;

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
					
					HBlockAction output_action = std::make_shared<CBlockAction>(((sTerm)->repr()));

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

std::list<HBlock> CParser::ToMatchList( std::vector<HPred> pvector, MatchResult result)
{
	std::list<HBlock> vlist;
	for(size_t j = 0; j< pvector.size();++j)
	{
		if (CPredAtom* vAtom = asPredAtom(pvector[j].get()))
		{
			vlist.push_back(std::make_shared<CBlockNoum>(vAtom->h->repr()));
		}
		else if (CPredAny * vAny =asPredAny(pvector[j].get()))
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


HBlock CParser::DynamicDispatch_action(std::vector<HTerm> term) {

	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it)
	{

		MatchResult res_action = CMatch(term, it->matchPhase);
		if (res_action.result == Equals)
		{
			HBlock n1 = parser_expression(res_action.matchs["noum1"]);
			HBlock n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end()) {
				n2 = parser_expression(res_action.matchs["noum2"]);
			}
			else {
				n2 = std::make_shared<CBlockNoum>("Nothing");
			}
			n1->dump("   ");
			n2->dump("   ");


			//if (HBlockAction vAction = std::asHBlockAction(it->output))
			//{
			//	return std::make_shared<CBlockActionCall>(vAction, n1, n2);
			//}
			std::list<HBlock> resList = ToMatchList(it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockList>(resList);

			return 	  std::make_shared<CBlockDinamicDispatch>(clistResults); // it->output;
			return std::make_shared<CBlockStaticDispatch>(it->entryId, n1, n2);
		}

	}
	return nullptr;
}
