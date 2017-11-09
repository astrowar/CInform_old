// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <vector>
#include "Parser.hpp"
#include "CBlockUndestand.hpp"
using namespace CBlocking;

using namespace NSTerm;
using namespace NSTerm::NSMatch;




NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInput(CParser *p, HTerm term) {
    if (CList *cterm = asCList(term.get())) {
        std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
        auto kv = parser_buildMatchBlock_actionInputList(p,vterm);
        return kv;
    }

    std::vector<HPred> replcList;
    replcList.push_back(pLiteral(term->repr()));

    //return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr()));
    return DispatchArguments(replcList, nullptr,
                             std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(term->repr())));
}



HBlockStaticDispatch NSParser::DynamicDispatch::getStaticDispatchResolve(CParser *p, HTerm term) //Determina se este termo esta na lista de dispatchs dynamicos
{


    //Verifica se ja tem a matchPhase
    int maxID = 0;
    for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it) {
        MatchResult res = CMatch(term, it->matchPhase);
        if (res.result == Equals) {
            return std::make_shared<CBlockStaticDispatch>(it->entryId,
                                                          std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr()),
                                                          std::make_shared<CBlockNoum>(res.matchs["noum2"]->repr()));
        }
    }
    return nullptr;


}

 

NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInputList(CParser *p, std::vector<HTerm>&  term) {

   // std::cout << "what:  " << get_repr(term) << std::endl;
    {
		static CPredSequence predList = {};
		if (predList.empty())
		{

			<<(pAny("verb"));
			//<<(pLiteral("["));
			<<(pAny("kind1"));
			//<<(pLiteral("]"));
			<<(pAny("with_word"));
			//<<(pLiteral("["));
			<<(pAny("kind2"));
			//<<(pLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
            HBlockMatch c3 = std::make_shared<CBlockMatchNoum>(
                    std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            CPredSequence replcList;
            replcList.push_back(pLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(pAny("noum1"));
            replcList.push_back(pLiteral(res.matchs["with_word"]->repr()));
            replcList.push_back(pAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1, c3, arg2}));
            return NSParser::DispatchArguments(  replcList, mlist1, mlist2);

        }
    }
    {
		static CPredSequence predList = {};
		if (predList.empty())
		{
			<<(pAny("verb"));
			//<<(pLiteral("["));
			<<(pAny("kind1"));
		//	<<(pLiteral("]"));
			<<(pLiteral("["));
			<<(pAny("kind2"));
			//<<(pLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
          
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            CPredSequence replcList;
            replcList.push_back(pLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(pAny("noum1"));
            
            replcList.push_back(pAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1,   arg2}));
            return NSParser::DispatchArguments(replcList, mlist1, mlist2);

        }
    }
	{
		static CPredSequence predList = {};
		if (predList.empty())
		{
			<<(pAny("verb"));
			<<(pAny("aux"));
		//	<<(pLiteral("["));
			<<(pAny("kind1"));
		//	<<(pLiteral("]"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch c1a = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["aux"]->repr()));


			//HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p,res.matchs["kind1"]);
			
			CPredSequence replcList;
			replcList.push_back(pLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(pLiteral(res.matchs["aux"]->repr()));
			replcList.push_back(pAny("noum1"));
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c1a, arg1 }));
			return NSParser::DispatchArguments(replcList, mlist1, mlist2);
		}
	}


    {
		static CPredSequence predList = {};
		if (predList.empty())
		{
			<<(pAny("verb"));
	//		<<(pLiteral("["));
			<<(pAny("kind1"));
	//		<<(pLiteral("]"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
		 
			HBlockMatch  c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));


            //HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p,res.matchs["kind1"]);
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>()); //este eh o match estatico .. ie .. aquele usado pelo parser para identificar as chamadas estaticas
						

            CPredSequence replcList;
            replcList.push_back(pLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(pAny("noum1"));
            //return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1 }));
            return NSParser::DispatchArguments(replcList, mlist1, mlist2);
        }
    }

    return NSParser::DispatchArguments(std::vector<HPred>(), nullptr, nullptr);
}


HBlock NSParser::DynamicDispatch::STMT_understand_generic_redirect(CParser *p, HTerm  term, HBlock  output_term) {

	DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(p, term);
	if (match_predicate.sentenceMatch == nullptr) return nullptr;



	HBlockUnderstandDynamic  retBlock = std::make_shared<CBlockUnderstandDynamic >(  match_predicate.sentenceMatch, match_predicate.staticArgumentMatch, output_term);
	int entryID = p->registerDynamicDispatch(match_predicate.staticPredicade,	match_predicate.sentenceMatch, output_term);


	return retBlock;
}





HBlock NSParser::DynamicDispatch::STMT_understand_Action_Assertion_static(CParser *p, std::vector<HTerm>&  term) {

    {
		static CPredSequence predList = {};
		if (predList.empty())
		{
			predList = { pLiteral("understand") , pLiteral(":") ,pAny("What") ,pLiteral("as") ,pAny("Subst") };

		/*	<<(pLiteral("understand"));
			<<(pLiteral(":"));
			<<(pAny("What"));
			<<(pLiteral("as"));
			<<(pAny("Subst"));*/
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
				CPredSequence actionList;
				actionList.push_back(p->actionPredList);
				MatchResult res_action = CMatch(sTerm, actionList);
				if (res_action.result == Equals) {

					output_noum = std::make_shared<CBlockActionNamed>( ((sTerm)->repr())); //An Action !!!
				}
				else
				{
					output_noum = Expression::parser_expression(p,res.matchs["Subst"]);

					//Interpretei 
					logMessage("Interpretei " + sTerm->repr());
					logMessage("Como ");
					output_noum->dump("          ");
					logMessage("---");

				}


				//Nao eh um action               
				//HBlock value = parser_expression( res.matchs["Subst"]);

				if (output_noum == nullptr) return nullptr;
				 
				return STMT_understand_generic_redirect(p,res.matchs["What"], output_noum);

                //std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

				// Verifica se tem alguma Acao que corresponde ao termo de saida

                //std::vector<HPred> actionList;
               // actionList.push_back(actionPredList);
                //MatchResult res_action = CMatch(sTerm, actionList);
				 

				//Ok .. nao tem registro de nada analise o que esta na saida


            }
        }
    }
    return nullptr;
}

std::list<HBlock> NSParser::DynamicDispatch::ToMatchList(CParser *p, std::vector<HPred> pvector, MatchResult result)
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
			HBlock n1 = Expression::parser_expression(p,result.matchs[vAny->named]);
			vlist.push_back(n1);
		}
		else
		{
			logError("error" );
		}
	}
	return vlist;
}


std::pair<HBlockList, std::list<HTerm> >  pack_terms(std::list<HTerm> terms )
{		
	std::list<HBlock> t0 ;
	//vai adicionando ate achar o end list
	
	std::list<HTerm> remainder = terms;
	while ( remainder.size() > 0 )
	{
		auto item = remainder.front();
		remainder.pop_front();
		if (item->is_openBracket())
		{
		 
			auto i_remainder = pack_terms(remainder);
			auto h_item = i_remainder.first;
			remainder = i_remainder.second;
			t0.push_back(h_item);
			continue;
		}
		else if (item->is_closeBracket() )
		{		
		 		 
			auto head = std::make_shared<CBlockList>(t0);
			return make_pair(head, remainder);
		}
		else
		{
			if (CString *cs = asCString(item.get()))
			{ 
				t0.push_back(std::make_shared<CBlockNoum>(item->repr()) );
			}
		}
	}
	auto head = std::make_shared<CBlockList>(t0);
	return make_pair(head, remainder);
}

HBlockList getNoumListing(std::vector<HTerm>  term);
HBlock  getNoumListing(HTerm   term)
{
	if (CList *clist = asCList(term.get()))
	{
		return getNoumListing(clist->asVector());
	}
	if (CString *cs = asCString(term.get()))
	{ 
		return std::make_shared<CBlockNoum>(term->repr());
	}
	return nullptr;
}
HBlockList getNoumListing(std::vector<HTerm>  term)
{
	auto clist = std::make_shared<CBlockList>(std::list<HBlock>());
	for (auto k : term)
	{		 
		clist->push_back(getNoumListing(k));
	}
	return clist;
}

HBlock NSParser::DynamicDispatch::Dispatch_action_call(CParser *p, HTerm  term)
{
	{
		CPredSequence predList_a = {};
		if (predList_a.empty())
		{
			 
			predList_a.push_back(pWord("Action"));
			predList_a.push_back(pAny("noum1"));
			predList_a.push_back(pPreposition("pred"));
			predList_a.push_back(pOr("pred_aux", pLiteral("to"), pLiteral("of")));
			predList_a.push_back(pAny("noum2"));
		}

		MatchResult res = CMatch(term, predList_a);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr() + " " + res.matchs["pred_aux"]->repr();
			auto actionDesc = std::make_shared<CBlockActionNamed>(anamed); //An Action !!!			
			auto nn1 = Expression::parser_expression(p, res.matchs["noum1"]);
			auto nn2 = Expression::parser_expression(p, res.matchs["noum2"]);

			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nn2); //An Action !!!
			return actionCall;
		}
	}

	{
		CPredSequence predList_b = {};
		if (predList_b.empty())
		{

			predList_b.push_back(pWord("Action"));
			predList_b.push_back(pAny("noum1"));
			predList_b.push_back(pPreposition("pred")); 
			predList_b.push_back(pAny("noum2"));
		}

		MatchResult res = CMatch(term, predList_b);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr();
			auto actionDesc = std::make_shared<CBlockActionNamed>( anamed); //An Action !!!			
			auto nn1 = Expression::parser_expression(p, res.matchs["noum1"]);
			auto nn2 = Expression::parser_expression(p, res.matchs["noum2"]);

			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nn2); //An Action !!!
			return actionCall;
		}
	}



	{
		CPredSequence predList_a2 = {};
		if (predList_a2.empty())
		{
		 
			predList_a2.push_back(pWord("Action"));
			predList_a2.push_back(pPreposition("pred"));
			predList_a2.push_back(pOr("pred_aux", pLiteral("to"), pLiteral("of")));
			predList_a2.push_back(pAny("noum1"));
		}

		MatchResult res = CMatch(term, predList_a2);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr() + " " + res.matchs["pred_aux"]->repr();
			auto actionDesc = std::make_shared<CBlockActionNamed>(anamed); //An Action !!!			
			auto nn1 = Expression::parser_expression(p, res.matchs["noum1"]);

			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nullptr); //An Action !!!
			return actionCall;
		}
	}
	 
	{
		CPredSequence predList_c = {};
		if (predList_c.empty())
		{
		 
			predList_c.push_back(pWord("Action"));
			predList_c.push_back(pAny("noum1"));
			predList_c.push_back(pPreposition("pred"));	 
			predList_c.push_back(pAny("noum2"));
		}

		auto s = term->repr();
		printf("* %s \n",s.c_str());
		MatchResult res = CMatch(term, predList_c);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr();
			auto actionDesc = std::make_shared<CBlockActionNamed>(anamed); //An Action !!!			
			auto nn1 = Expression::parser_expression(p, res.matchs["noum1"]);
			auto nn2 = Expression::parser_expression(p, res.matchs["noum2"]);

			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nn2); //An Action !!!
			return actionCall;
		}
	}


	{
		CPredSequence predList_a1 = {};
		if (predList_a1.empty())
		{

			predList_a1.push_back(pWord("Action"));
			predList_a1.push_back(pPreposition("pred"));
			predList_a1.push_back(pAny("noum1"));
		}

		MatchResult res = CMatch(term, predList_a1);

		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr();
			auto actionDesc = std::make_shared<CBlockActionNamed>(anamed); //An Action !!!			
			auto nn1 = Expression::parser_expression(p, res.matchs["noum1"]);

			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nullptr); //An Action !!!
			return actionCall;
		}
	}

	{
		CPredSequence predList_d = {};
		if (predList_d.empty())
		{
		 
			predList_d.push_back(pWord("Action"));
			predList_d.push_back(pAny("noum1"));
		}

		MatchResult res = CMatch(term, predList_d);
		if (res.result == Equals)
		{
			auto actionDesc = std::make_shared<CBlockActionNamed>((res.matchs["Action"]->repr())); //An Action !!!			
			auto nn1 = Expression::parser_expression( p,res.matchs["noum1"] );
			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nn1, nullptr); //An Action !!!
			return actionCall;
		}
	}
	{
		CPredSequence predList_e = {};
		if (predList_e.empty())
		{
			 
			predList_e.push_back(pWord("Action"));
		}

		MatchResult res = CMatch(term, predList_e);
		if (res.result == Equals)
		{
			auto actionDesc = std::make_shared<CBlockActionNamed>((res.matchs["Action"]->repr())); //An Action !!!		 
			auto actionCall = std::make_shared<CBlockActionCallNamed>(actionDesc, nullptr, nullptr); //An Action !!!
			return actionCall;
		}
	}
	return nullptr;


}


HBlock NSParser::DynamicDispatch::TryDispatch_action(CParser *p, std::vector<HTerm>&  term)
{
	//{
	//	static CPredSequence predList = {};
	//	if (predList.empty())
	//	{
	//		<<(pLiteral("try"));
	//		<<(pAny("sentence"));
	//	}

	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals)
	//	{
	//		std::pair<HBlockList, std::list<HTerm> >    clist_ia = pack_terms(std::list<HTerm>(term.begin(), term.end()));
	//		HBlockList clist = clist_ia.first;
	//		if (!clist_ia.second.empty())
	//		{
	//			return nullptr;
	//		}
	//		clist->lista.pop_front();
	//		clist->dump("");
	//		auto tryCall = std::make_shared<CBlockTryCall>(clist); //An Action !!!
	//		return tryCall;
	//	}
	//}
	//return nullptr;
  

	{
		CPredSequence  predList_a = pLiteral("try") << pAny("ActionRemainder") ;
		//if (predList_a.empty())
		//{
		//	predList_a.push_back(pLiteral("try"));
		//	predList_a.push_back(pAny("ActionRemainder"));
 
		//}

		MatchResult res = CMatch(term, predList_a);
		if (res.result == Equals)
		{
			auto actionRemainder = Dispatch_action_call(p,res.matchs["ActionRemainder"]);  
			if (actionRemainder != nullptr)
			{
				auto TryactionCall = std::make_shared<CBlockTryCall>(actionRemainder);
				return TryactionCall;
			}
		}
	}

	 
	return nullptr;
}


 
HBlock NSParser::DynamicDispatch::parser_PhraseInvoke(CParser *p, std::vector<HTerm>&  term)
{
	for (auto ph : p->phrases)
	{
		if (ph->arg1 != nullptr && ph->pred1 == nullptr && ph->pred2 != nullptr && ph->arg1 != nullptr && ph->arg2 != nullptr)
		{
			//CPredSequence predList = {};
			//if (predList.empty())
			//{
			//	<<(pLiteral(ph->verb->named));
			//	<<(pAny("Match_arg1"));
			//	<<(pLiteral(ph->pred2->named ));
			//	<<(pAny("Match_arg2"));
			//}

			CPredSequence  predList = pLiteral(ph->verb->named) << pAny("Match_arg1") << pLiteral(ph->pred2->named) << pAny("Match_arg2");


			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{				
				HBlock marg1 = Expression::parser_expression(p, res.matchs["Match_arg1"]);			
				if (marg1 != nullptr)
				{
					HBlock  marg2 = Expression::parser_expression(p, res.matchs["Match_arg2"]);
					if (marg2 != nullptr)
					{
						return   std::make_shared<CBlockPhraseInvoke>(ph, marg1, marg2);
					}
				}
			}
		}
	}
	return nullptr;

}

HBlock NSParser::DynamicDispatch::DynamicDispatch_action(CParser *p, std::vector<HTerm>&  term) {

	for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it)
	{

		MatchResult res_action = CMatch(term, it->matchPhase);
		if (res_action.result == Equals)
		{
			HBlock n1 = Expression::parser_expression(p,res_action.matchs["noum1"]);
			HBlock n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end()) {
				n2 = Expression::parser_expression(p, res_action.matchs["noum2"]);
			}
			else {
				n2 = std::make_shared<CBlockNothing>("nothing");
			}
			n1->dump("   ");
			n2->dump("   ");


			//if (HBlockAction vAction = std::asHBlockAction(it->output))
			//{
			//	return std::make_shared<CBlockActionCall>(vAction, n1, n2);
			//}
			std::list<HBlock> resList = ToMatchList(p, it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockList>(resList);

			return 	  std::make_shared<CBlockDinamicDispatch>(clistResults); // it->output;
			return std::make_shared<CBlockStaticDispatch>(it->entryId, n1, n2);
		}

	}
	return nullptr;
}
