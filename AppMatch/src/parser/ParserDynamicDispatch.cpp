// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "parser/Parser.hpp"
#include "CBlockUndestand.hpp"
#include <vector>
#include <algorithm>

using namespace CBlocking;

using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;



CPredSequence  convert_doSequence(HBlockNoum n)
{ 
	 
	if (n->type() == BlockNoumCompose)
	{
		std::vector<HPred> seq;
		CBlockNoumCompose* ncomp = static_cast<CBlockNoumCompose*>(n.get());
		for (auto it = ncomp->noums.begin(); it != ncomp->noums.end();++it)
		{
			seq.push_back(pLiteral((*it)->named()));
		}
		return CPredSequence(seq);
	}	
	return CPredSequence(pLiteral(n->named()));
}


NSParser::DispatchArguments NSParser::DynamicDispatch::parser_user_parser(CParser *p, HTerm termLiteral)
{
	// quando entra um cLiteral para entender como parser
	// determina os brackets
	 
	std::list<string>  termos;
	CLiteral *clit = asCLiteral(termLiteral.get());
	string lit = clit->val;
	if (lit[0] == '"') lit = lit.substr(1, lit.size()-1);
	if (lit.back() == '"') lit = lit.substr(0, lit.size()-1);
	const size_t n = lit.size();

	size_t pivot = 0;
	for (size_t i = 0; i < n; ++i)
	{

		if (lit[i] == '[')
		{
			termos.push_back(lit.substr(pivot, i - pivot));
			pivot = i;
		}
		
		if (lit[i] == ']')
		{
			termos.push_back(lit.substr(pivot, i - pivot+1));
			pivot = i+1;
			
		}
	}
	if ( n>pivot)termos.push_back(lit.substr(pivot, n - pivot));

	//remove os vazios
	termos.erase(std::remove_if(termos.begin(), termos.end(), [](string x) {return x.empty(); }), termos.end());


	//divide as palavras que nao estao dentro do []
	for (auto it = termos.begin(); it != termos.end();++it)
	{
		string s = *it;
		if (s[0] == '[') continue;

		size_t  nq = s.size();

		for (size_t i = 0; i < nq; ++i)
		{
			if (s[i] == ' ')
			{
				//divide
				string s1 = s.substr(0, i);
				string s2 = s.substr(i+1, n - i-1);
				it = termos.erase(it);
				if ((s1 != " ") && (s1.size() > 0))
				{
					termos.insert(it, s1);
				}
				if ((s2 != " ") && (s2.size()>0))
				{
					termos.insert(it, s2);
				}
				it = termos.begin();
				break;
			}			
		}

		//while (s.size()>0 && s.front() == ' ') s = s.substr(1, s.size() - 1);
		//while (s.size()>0 && s.back() == ' ') s = s.substr(0, s.size() - 1);
	}

	//for (auto &s : termos)
	//{
	//	printf("|%s|\n", s.c_str());
	//}


	HBlockMatch arg1 = nullptr;
	HBlockMatch arg2 = nullptr;
	std::list<HBlockMatch> mfull_parseList = std::list<HBlockMatch>();
	std::list<HBlockMatch> margs_parseList = std::list<HBlockMatch>();
	CPredSequence replcList = CPredSequence(std::vector<HPred>()); //  = pLiteral(res.matchs["verb"]->repr()) << pAny("noum1") << pLiteral(res.matchs["with_word"]->repr()) << pAny("noum2");

	for (auto &s : termos)
	{
		//printf("|%s|\n", s.c_str());
		//while (s.size()>0 && s.front() == ' ') s = s.substr(1, s.size() - 1);
		//while (s.size()>0 && s.back() == ' ') s = s.substr(0, s.size() - 1);
	}
	termos.erase(std::remove_if(termos.begin(), termos.end(),[](string x) {return x.empty(); }), termos.end());
	 
	for (auto &s : termos)
	{
		HBlockMatch term = nullptr;

		if (s.front() == '[' && s.back() != ']')
		{
			logError("Undestand text Error\n");			
			return NSParser::DispatchArguments({}, nullptr,nullptr);
		}
		bool is_arg = s.front() == '[';


		if (s.front() == '[')
		{
			s = s.substr(1, s.size() - 1);
		}
		if (s.back() == ']')
		{
			s = s.substr(0, s.size() - 1);
		}
		 
		while (s.size()>0 && s.front() == ' ') s = s.substr(1, s.size() - 1);
		while (s.size()>0 && s.back() == ' ') s = s.substr(0, s.size() - 1);

		if (is_arg)
		{
			//termo de argumento
			//term = NSParser::ExpressionMatch::parser_MatchArgument(p, make_string(s));

			HBlockNoum arg_noum = nullptr;  

			// eh um argumento composto ou simples 
			if (s.find(' ') != string::npos)
			{
			  std::vector<HBlockNoum> _noums;
			  std::vector<string>  vargs  =	split_string(s, " ");
			  for (auto sa : vargs)
			  {
				  _noums.push_back(std::make_shared<CBlockNoumStr>(sa));
			  }			  
			  arg_noum = std::make_shared<CBlockNoumCompose>(_noums);
			}
			else
			{
				arg_noum = std::make_shared<CBlockNoumStr>(s);
			}

			if (arg1 == nullptr)
			{
				term = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
				arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchNoum>(arg_noum));
				replcList = replcList << pAny("noum1");
				margs_parseList.push_back(arg1);
			}
			else if (arg2 == nullptr)
			{
				term = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());
				arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchNoum>(arg_noum));
				replcList = replcList << pAny("noum2");
				margs_parseList.push_back(arg2);
			}
			else
			{
				logError("Only two terms for undestand\n");
				return NSParser::DispatchArguments({}, nullptr, nullptr);
			}
			
			
		}
		else
		{
			//termo normal
			   //term = ExpressionMatch::parse_match_noum(p, { make_string(s) });
			   term = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr >( s ));

			  //term = NSParser::ExpressionMatch::parser_MatchArgument(p, make_string(s));
			  replcList = replcList << pLiteral(s);
		}

		mfull_parseList.push_back(term);
	}





	//printf("%s \n", lit.c_str());

	

	for (auto s : termos)
	{
		//printf("|%s|\n", s.c_str());
	}

	auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>(margs_parseList ));
	auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>(mfull_parseList));
	NSParser::DispatchArguments r =  NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);

	
	return r;
 
	 
}

NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInput(CParser *p, HTerm term) {
    
	if (CLiteral *clit = asCLiteral(term.get()))
	{
		std::vector<HPred> replcList;
		replcList.push_back(pLiteral(term->repr()));
		return parser_user_parser(p, term);		
	}
	if (CList *cterm = asCList(term.get())) {
        std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
        auto kv = parser_buildMatchBlock_actionInputList(p,vterm);
        return kv;
    }
    std::vector<HPred> replcList;
    replcList.push_back(pLiteral(term->repr()));
	std::vector<HTerm> term_vec = { term };
	auto argument_parser_input  = ExpressionMatch::parse_match_noum(p, term_vec);
	return DispatchArguments(replcList, nullptr, argument_parser_input);
}



HBlockStaticDispatch NSParser::DynamicDispatch::getStaticDispatchResolve(CParser *p, HTerm term) //Determina se este termo esta na lista de dispatchs dynamicos
{


    //Verifica se ja tem a matchPhase
    int maxID = 0;
    for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it) {
        MatchResult res = CMatch(term, it->matchPhase);
        if (res.result == Equals) 
		{
            return std::make_shared<CBlockStaticDispatch>(it->entryId,
                                                          std::make_shared<CBlockNoumStr>(res.matchs["noum1"]->repr()),
                                                          std::make_shared<CBlockNoumStr>(res.matchs["noum2"]->repr()));
        }
    }
    return nullptr;


}

 

NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInputList(CParser *p, std::vector<HTerm>&  term) {

	{
		auto tphase = getQuadPartition(term);
		for (auto t : tphase)
		{
			auto term1 = t[0];
			auto var1 = t[1];
			auto term2 = t[2];
			auto var2 = t[3];

			auto term1expr = Expression::parser_noum_expression(p, term1);
			if (term1expr == nullptr) continue;
			 
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(term1expr);
			if (c1 == nullptr) continue;
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument_only(p, var1);
			if (c2 == nullptr) continue;
			if (c2->type() == BlockMatchList) continue;

			HBlockMatch c3 = ExpressionMatch::parse_match_noum(p, { term2 });
			if (c3 == nullptr) continue;
			HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument_only(p, var2);
			if (c4 == nullptr) continue;
			if (c4->type() == BlockMatchList) continue;

			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

			CPredSequence replcList = pLiteral(term1->repr()) << pAny("noum1") << pLiteral(term2->repr()) << pAny("noum2");

			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2, c4 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, arg1, c3, arg2 }));
			return NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);
		}
	}

	{
		auto tphase = getBiPartition(term);
		for (auto t : tphase)
		{
			auto term1 = t.first;			
			auto term2 = t.second;
			

			//auto term1expr = Expression::parser_noum_expression(p, term1);
			//if (term1expr == nullptr) continue;
			//HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(term1expr);
			//if (c1 == nullptr) continue;
			//HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, var1);
			//if (c2 == nullptr) continue;
			//HBlockMatch c3 = ExpressionMatch::parse_match_noum(p, { term2 });
			//if (c3 == nullptr) continue;
			//HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, var2);
			//if (c4 == nullptr) continue;
			//HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			//HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());
			//CPredSequence replcList = pLiteral(term1->repr()) << pAny("noum1") << pLiteral(term2->repr()) << pAny("noum2");
			//auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2, c4 }));
			//auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, arg1, c3, arg2 }));
			//return NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);
		}
	}



	//auto tr = getTriPartition(term);
    //for(auto t : tr)
    if(false){
		CPredSequence predList =  pWord("verb")	<<pAny("kind1")	<<pAny("with_word") <<pAny("kind2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>( Expression::parser_noum_expression(p,res.matchs["verb"]));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
			HBlockMatch c3 = ExpressionMatch::parse_match_noum(p, { res.matchs["with_word"] });
                   
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            CPredSequence replcList =        pLiteral(res.matchs["verb"]->repr()) <<pAny("noum1") <<   pLiteral(res.matchs["with_word"]->repr()) <<       pAny("noum2");

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1, c3, arg2}));
            return NSParser::DispatchArguments(  replcList.data_list.front(), mlist1, mlist2);

        }
    }
    {
		  CPredSequence predList = pWord("verb")<< pAny("kind1")	<<pLiteral("[")	<<pAny("kind2") << pLiteral("]");


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(Expression::parser_noum_expression(p, res.matchs["verb"]));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
          
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            CPredSequence replcList = pLiteral(res.matchs["verb"]->repr())<<   pAny("noum1") << pAny("noum2");

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1,   arg2}));
            return NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);

        }
    }
	{
		  CPredSequence predList = pWord("verb") << pWord("aux")<<pAny("kind1");
	 
		 

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			HBlockNoum nn1 = Expression::parser_noum_expression(p, res.matchs["verb"]);
			HBlockNoum nn2 = Expression::parser_noum_expression(p, res.matchs["aux"]);

			HBlockNoumCompose ncc = std::make_shared<CBlockNoumCompose>(std::vector<HBlockNoum>{ nn1,nn2 });

			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(ncc);
			//HBlockMatch c1a = std::make_shared<CBlockMatchNoum>(Expression::parser_noum_expression(p, res.matchs["aux"]));


		 
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p,res.matchs["kind1"]);
			
			CPredSequence replcList =  pLiteral(res.matchs["verb"]->repr()) <<pLiteral(res.matchs["aux"]->repr())<<	pAny("noum1");

			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1,  arg1 }));
			return NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);
		}
	}


    {
		  CPredSequence predList = pWord("verb")<<pAny("kind1");
  
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
		 
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(Expression::parser_noum_expression(p, res.matchs["verb"]));

			if (c1 != nullptr)
			{
				HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
				if (c2 != nullptr)
				{
					HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>()); //este eh o match estatico .. ie .. aquele usado pelo parser para identificar as chamadas estaticas

					CPredSequence replcList = pLiteral(res.matchs["verb"]->repr()) << pAny("noum1");

					auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
					auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, arg1 }));
					return NSParser::DispatchArguments(replcList.data_list.front(), mlist1, mlist2);
				}
			}
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
		  CPredSequence  predList = pLiteral("understand") << pOptional(pLiteral(":")) << pAny("What") << pLiteral("as") <<pAny("Subst") ;
		   
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {


			 

             

            // existe uma action que Match com o Subst ???
            HBlock output_noum = nullptr;
            HBlockMatch sentence_match = nullptr;
            {

               auto sTerm = res.matchs["Subst"];
                {
                    sTerm = expandBract(sTerm);
                }

				//Rh um action !!
				CPredSequence actionList = CPredSequence(p->actionPredList);

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
			vlist.push_back(std::make_shared<CBlockNoumStr>(vAtom->h->repr()));
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
	while (!remainder.empty())
	{
		HTerm item = remainder.front();
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
				t0.push_back(std::make_shared<CBlockNoumStr>(item->repr()) );
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
		return std::make_shared<CBlockNoumStr>(term->repr());
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
		CPredSequence predList_a =     pWord("Action") << pAny("noum1") <<	 pPreposition("pred") << 	 pOr("pred_aux", pLiteral("to"), pLiteral("of")) <<	 pAny("noum2");
	 

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
		CPredSequence predList_b =   pWord("Action") <<   pAny("noum1") <<  pPreposition("pred") <<   pAny("noum2");
		
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
		CPredSequence predList_a2 =  pWord("Action")	 << pPreposition("pred")	 << pOr("pred_aux", pLiteral("to"), pLiteral("of"))	 << pAny("noum1");

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
		CPredSequence predList_c =  pWord("Action")	 << pAny("noum1") << pPreposition("pred") << pAny("noum2");
	 

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
		CPredSequence predList_a1 =  pWord("Action") <<	  pPreposition("pred")<< 	  pAny("noum1");


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
		CPredSequence predList_d = 	 pWord("Action") <<	 pAny("noum1");
		 

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
		CPredSequence predList_e = pWord("Action");

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


 
HBlock NSParser::DynamicDispatch::Instead_phase(CParser *p, std::vector<HTerm>&  term)
{
	{
		CPredSequence  predList_a = pAny("ActionRemainder") << pLiteral("instead");
		 
		MatchResult res = CMatch(term, predList_a);
		if (res.result == Equals)
		{			 
			auto actionRemainder = Statement::parser_stmt_call(p, { res.matchs["ActionRemainder"] } );
			if (actionRemainder != nullptr)
			{
				auto TryactionCall = std::make_shared<CBlockTryCall>(actionRemainder);
				auto stoping =  std::make_shared<CBlockExecutionResultFlag>(PhaseResultFlag::actionStop, nullptr);
				std::list<HBlock> cmd = { TryactionCall , stoping };
				return  std::make_shared<CBlockComandList>(cmd);
			}
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
	// <<pLiteral("try");
	// <<pAny("sentence");
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


	{
		CPredSequence predList = pLiteral("matches") << pAny("regex") << pLiteral("in") << pAny("Text");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock marg1 = Expression::parser_expression(p, res.matchs["regex"]);
			if (marg1 != nullptr)
			{
				HBlock  marg2 = Expression::parser_expression(p, res.matchs["Text"]);
				if (marg2 != nullptr)
				{
					//std::make_shared<CBlockPhraseHeader>(std::make_shared<CBlockNoumStr>("matches"), nullptr, std::make_shared<CBlockNoumStr>("in"), HBlockMatch _arg1, HBlockMatch _arg2);
					//return   std::make_shared<CBlockPhraseInvoke>("matches", marg1, marg2);
				}
			}
		}
	}

	for (auto ph : p->phrases)
	{
		if (ph->arg1 != nullptr && ph->pred1 != nullptr )
		{ 
			CPredSequence seq = convert_doSequence(ph->pred1);

			CPredSequence  predList = pLiteral(ph->verb->named()) << seq << pAny("Match_arg2");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlock  marg1 = Expression::parser_expression(p, res.matchs["Match_arg2"]);
				if (marg1 != nullptr)
				{
					return   std::make_shared<CBlockPhraseInvoke>(ph, marg1, nullptr);
				}
			} 
		}
	}


	for (auto ph : p->phrases)
	{
		if (ph->arg1 != nullptr && ph->pred1 == nullptr && ph->pred2 != nullptr && ph->arg1 != nullptr && ph->arg2 != nullptr)
		{
			//CPredSequence predList = {};
			//if (predList.empty())
			//{
			//	<<pLiteral(ph->verb->named());
			//	<<pAny("Match_arg1");
			//	<<(pLiteral(ph->pred2->named() ));
			//	<<pAny("Match_arg2");
			//}

			CPredSequence  predList = pLiteral(ph->verb->named()) << pAny("Match_arg1") << pLiteral(ph->pred2->named()) << pAny("Match_arg2");


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

 
