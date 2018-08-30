// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include <memory>
#include "parser/Parser.hpp"
#include "CBlockDecideIf.hpp"
#include <sharedCast.hpp>
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


HBlockNoum convert_to_noum(NSParser::CParser* p, HTerm term)
{
	auto *clist = asCList(term.get());
	if (clist != nullptr)
	{		
		std::vector<HBlockNoum> lst;
		auto term_vec = clist->asVector();
		for (auto c : term_vec)
		{
			//if (c->repr() == "the" || c->repr() == "an" || c->repr() == "a")
			//{
				//auto ndet =  std::make_shared<CBlockNoumStrDet>(c->repr() , convert_to_noum(p,c));
				//lst.push_back(ndet);				
			//}
			//else
			{
				auto nitem = convert_to_noum(p, c);
				lst.push_back(nitem);
			}
		}
		return std::make_shared<CBlockNoumCompose>(lst);
	}
	return std::make_shared<CBlockNoumStr>(term->repr());
}





HBlockMatchList NSParser::ParseDecide::parser_match_body(CParser * p, HTerm term)
{


	//particiona e so aceita noums ou arguments inputs

	return parseDecidePhaseMatchEntry(p, term);






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

			return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c2,c3,c4 }));
		}
	}

	{
		auto tphase = getTriPartition(term);
		for (auto t : tphase)
		{
			auto term1 = t[0];
			auto var1 = t[1];
			auto term2 = t[2]; 
			auto term1expr = Expression::parser_noum_expression(p, term1);
			if (term1expr == nullptr) continue;

			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(term1expr);
			if (c1 == nullptr) continue;
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument_only(p, var1);
			if (c2 == nullptr) continue;
			if (c2->type() == BlockMatchList) continue;

			HBlockMatch c3 = ExpressionMatch::parse_match_noum(p, { term2 });
			if (c3 == nullptr) continue; 
			return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c2,c3  }));
		}
	}


	{
		auto tphase = getBiPartition(term);
		for (auto t : tphase)
		{
			auto term1 = t.first;
			auto var1 = t.second;
		  

			printf("%s ", term1->repr().c_str());
			printf(" -  %s \n", var1->repr().c_str());
			auto term1expr = Expression::parser_noum_expression(p, term1);
			if (term1expr == nullptr) continue;

			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(term1expr);
			if (c1 == nullptr) continue;
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument_only(p, var1);
			if (c2 == nullptr) continue;
			if (c2->type() == BlockMatchList) continue;
			 
			return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c2  }));
		}
	}



	return nullptr;


}


HBlockPhraseHeader  NSParser::ParseDecide::parser_What_Which_Assertion(CParser * p, HTerm term)
{

	{
		// what text is the kind name for (parseme - S) with plural flag(truth state - F) :
		CPredSequence predList = mk_What_Which() << pAny("kindReturn") << verb_IS() << pAny("RemainderQuery") << pLiteral("for") << pAny("argument") << pLiteral("with")<<pAny("options");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["kindReturn"]);
			HBlockNoum noum = convert_to_noum(p, res.matchs["RemainderQuery"]);
			HBlockMatch  AdjetiveMatch = std::make_shared<CBlockMatchNoum>(noum);
			if (AdjetiveMatch != nullptr)
			{
				logError("nao implementado");
				return std::make_shared<CBlockPhraseHeader>(nullptr, nullptr);
				//return AdjetiveMatch;
			}
		}
	}


	{
		// what text is the kind name for (parseme - S)  :
		CPredSequence predList = mk_What_Which() << pAny("kindReturn") << verb_IS() << pAny("RemainderQuery") <<pLiteral("for") << pAny("argument");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["kindReturn"]);
			if (c1 != nullptr)
			{

				HTerm tem_part1 = res.matchs["RemainderQuery"];
				std::list<HTerm>  t1 = (asCList(tem_part1.get()))->lst ; 
				t1.push_back(make_string("for"));
				t1.push_back(res.matchs["argument"]);

				HTerm next_term = make_list(t1);

				std::pair<HBlockMatchList, HBlockMatchList>  AdjetiveMatch_p = parser_match_phraseHeader(p, next_term, 1);
				return std::make_shared<CBlockPhraseHeader>(p->get_next_headerName() ,AdjetiveMatch_p.first, AdjetiveMatch_p.second);
				  

				//HBlockMatch  arg2 = ExpressionMatch::parser_MatchArgument_only(p, res.matchs["argument"]);
				//if (arg2 != nullptr)
				//{
				//	//HBlockNoum noum = convert_to_noum(p,res.matchs["RemainderQuery"]);

				//	//HBlockMatch  AdjetiveMatch =  std::make_shared<CBlockMatchNoum>(  noum);
				//	HBlockMatchList  AdjetiveMatch = parser_match_body(p, res.matchs["RemainderQuery"]);
				//	if (AdjetiveMatch != nullptr)
				//	{
				//		auto mlist = AdjetiveMatch->matchList;
				//		mlist.push_back(std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr>("for")));
				//		mlist.push_back(arg2);
				//		return std::make_shared<CBlockMatchList>(mlist);
				//	}
				//}
			}
		}
	}


	{
		// which (Person) is (the targert) -> Enforce (Return Value) as Person
		CPredSequence predList = mk_What_Which()	<<pAny("kindReturn") <<verb_IS()<<pAny("RemainderQuery");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);
			if (c1 != nullptr)
			{
				std::pair<HBlockMatchList, HBlockMatchList>  AdjetiveMatch_p = parser_match_phraseHeader(p, res.matchs["RemainderQuery"], 1);

				return std::make_shared<CBlockPhraseHeader>(p->get_next_headerName(), AdjetiveMatch_p.first, AdjetiveMatch_p.second);

				//HBlockMatchList  AdjetiveMatch = parser_match_body(p, res.matchs["RemainderQuery"]);
				//if (AdjetiveMatch != nullptr)
				//{
				//	return AdjetiveMatch;					
				//}
			}
		}
	}
	return nullptr;
}

HBlockMatch  NSParser::ParseDecide::parseDecidePhaseMatchEntry(CParser * p, std::list<std::vector<HTerm > > terms)
{
	for (auto t : terms)
	{
		std::list<HBlockMatch> mtermos;
		bool has_err = false;
		for (auto ts : t)
		{
			HBlockMatch  componente = ExpressionMatch::parser_MatchComponentePhase(p, ts);
			//printf("%s %x\n", ts->repr().c_str(), componente);
			 
			if (componente == nullptr)
			{
				has_err = true;
				break;
			}
			else
			{
				mtermos.push_back(componente);
			}
		}
		if (has_err == false) return std::make_shared<CBlockMatchList >(mtermos);
	}
	return nullptr;
}


HBlockMatchList  NSParser::ParseDecide::parseDecidePhaseMatchEntry(CParser * p, HTerm term)
{
	{
		std::vector<HTerm> term_in = { term };
		HBlockMatchList  mlist = NSParser::ParseDecide::parseDecidePhaseMatchEntry(p, term_in);
		if (mlist->matchList.size() == 1)
		{
			if (auto mmlist = DynamicCasting::asHBlockMatchList(mlist->matchList.front()))
			{
				return mmlist;
			}
		}
		return mlist;
	}


	std::function<HBlock(HTerm)> func_MatchComponentePhase = [&](HTerm ts) { return ExpressionMatch::parser_MatchComponentePhase(p, ts); };
	
	auto r6 =  getHexPartition_fn(term, func_MatchComponentePhase);
	if (r6.empty() == false)
	{
		std::list<HBlockMatch> mtermos;
		for (auto bb : r6.front())
		{
			mtermos.push_back(std::static_pointer_cast<CBlockMatch>(bb));
		}
		return std::make_shared<CBlockMatchList >(mtermos);
	}


	auto r5 = getQuiPartition_fn(term, func_MatchComponentePhase);
	if (r5.empty() == false)
	{
		std::list<HBlockMatch> mtermos;
		for (auto bb : r5.front())
		{
			mtermos.push_back(std::static_pointer_cast<CBlockMatch>(bb));
		}
		return std::make_shared<CBlockMatchList >(mtermos);
	}


	auto r4 = getQuadPartition_fn(term, func_MatchComponentePhase);
	if (r4.empty() == false)
	{
		std::list<HBlockMatch> mtermos;
		for (auto bb : r4.front())
		{
			mtermos.push_back(std::static_pointer_cast<CBlockMatch>(bb));
		}
		return std::make_shared<CBlockMatchList >(mtermos);
	}

	auto r3 = getTriPartition_fn(term, func_MatchComponentePhase);
	if (r3.empty() == false)
	{
		std::list<HBlockMatch> mtermos;
		for (auto bb : r3.front())
		{
			mtermos.push_back(std::static_pointer_cast<CBlockMatch>(bb));
		}
		return std::make_shared<CBlockMatchList >(mtermos);
	}


	auto r2 = getBiPartition_fn(term, func_MatchComponentePhase);
	if (r2.empty() == false)
	{
		std::list<HBlockMatch> mtermos;
		for (auto bb : r2.front())
		{
			mtermos.push_back(std::static_pointer_cast<CBlockMatch>(bb));
		}
		return std::make_shared<CBlockMatchList >(mtermos);
	}




	//auto mphase5 =  parseDecidePhaseMatchEntry(p, getQuiPartition(term));
	//if (mphase5 != nullptr) return mphase5;

	//auto  mphase4 = parseDecidePhaseMatchEntry(p, getQuadPartition(term));
	//if (mphase4 != nullptr) return mphase4;


	//auto mphase3 = parseDecidePhaseMatchEntry(p, getTriPartition(term));
	//if (mphase3 != nullptr) return mphase3;

	//auto bip = getBiPartition_v(term);

	//auto mphase2 = parseDecidePhaseMatchEntry(p, bip);
	//if (mphase2 != nullptr) return mphase2;

	return nullptr;
}


void add_item(std::list<HBlockMatch > &plist, HBlockMatch h)
{
	if (auto nn = DynamicCasting::asHBlockMatchList(h))
	{
		plist.insert(plist.end(), nn->matchList.begin(), nn->matchList.end());

	}
	else
	{
		plist.push_back(h);
	}
}


 


HBlockMatch   NSParser::ParseDecide::parseDecidePhaseMatchEntry_i(CParser * p, HTerm  term_in)
{
	if (CList* listterm = asCList(term_in.get()))
	{
		auto r = parseDecidePhaseMatchEntry(p, listterm->asVector());
		if (r == nullptr)
		{
			return nullptr;
		}
		return r;
	}


	auto ri =  ExpressionMatch::parser_MatchComponentePhase(p, term_in);
	if (ri == nullptr)
	{
		return nullptr;
	}
	return ri;
}
bool is_backet_balanced(std::vector<HTerm> terms);
HBlockMatchList  NSParser::ParseDecide::parseDecidePhaseMatchEntry(CParser * p, std::vector<HTerm> term_in)
{

	if (term_in.size() == 1)
	{
		HBlockMatch r = parseDecidePhaseMatchEntry_i(p, term_in.front());
		if (r == nullptr) return nullptr;
		auto plist = std::list<HBlockMatch >();
		plist.push_back(r);
		return  std::make_shared<CBlockMatchList>(plist);
	}


	if (is_backet_balanced(term_in) == false)
		return nullptr;

	//if (term_in.front()->is_openBracket() && (term_in.back()->is_closeBracket()))
	//{
	//	if (is_backet_balanced(term_in))
	//	{
	//		auto res = std::vector<HTerm>(std::next(term_in.begin()), std::prev(term_in.end()));
	//		auto mlist = parseDecidePhaseMatchEntry(p, res);
	//		if (mlist != nullptr)
	//		{
	//		 
	//			auto plist = std::list<HBlockMatch >();
	//			plist.push_back(mlist);
	//			return  std::make_shared<CBlockMatchList>(plist);
	//		}
	//	}
	//	else
	//	{
	//		return nullptr;
	//	}
	//}



	{
		auto plist = std::list<HBlockMatch  >();
		CPredSequence predList = pWord("N1") << pWord("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlockMatch  n1 = parseDecidePhaseMatchEntry_i(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				add_item(plist, n1);
				HBlockMatch  n2 = parseDecidePhaseMatchEntry_i(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					add_item(plist, n2);
					return  std::make_shared<CBlockMatchList>(plist);
				}
			}
		}
	}









	{
		auto plist = std::list<HBlockMatch >();
		CPredSequence predList = pWord("N1") << pAny("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlockMatch  n1 = parseDecidePhaseMatchEntry_i(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				add_item(plist, n1);
				HBlockMatch  n2 = parseDecidePhaseMatchEntry_i(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					add_item(plist, n2);
					return  std::make_shared<CBlockMatchList>(plist);
				}
			}
		}
	}



	{
		auto plist = std::list<HBlockMatch >();
		CPredSequence predList = pAny("N1") << pWord("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlockMatch  n2 = parseDecidePhaseMatchEntry_i(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				HBlockMatch  n1 = parseDecidePhaseMatchEntry_i(p, res.matchs["N1"]);
				if (n1 != nullptr)
				{
					add_item(plist, n1);

					{
						add_item(plist, n2);
						return  std::make_shared<CBlockMatchList>(plist);
					}
				}
			}
		}
	}


	{
		auto plist = std::list<HBlockMatch >();
		CPredSequence predList = pAny("N1") << pAny("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlockMatch  n1 = parseDecidePhaseMatchEntry_i(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				add_item(plist, n1);
				HBlockMatch  n2 = parseDecidePhaseMatchEntry_i(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					add_item(plist, n2);
					return  std::make_shared<CBlockMatchList>(plist);
				}
			}
		}
	}

	{
		auto cls = make_list(term_in);
	auto ri = ExpressionMatch::parser_MatchComponentePhase(p, cls);
	if (ri != nullptr)
	{
		auto plist = std::list<HBlockMatch >();
		add_item(plist, ri);
		return  std::make_shared<CBlockMatchList>(plist);
	}
	}

	return nullptr;

}




HBlockMatchIs NSParser::ParseDecide::parser_What_Which_Verb_Assertion(CParser * p, HTerm term)
{

	{// which (Person) is (the targert) -> Enforce (Return Value) as Person
		CPredSequence predList = mk_What_Which() << pWord("kindReturn") <<  pLiteral("is") << pAny("RemainderQuery");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{


			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["kindReturn"]);
			if (c1 != nullptr)
			{
				HBlockMatch  AdjetiveMatch = parseDecidePhaseMatchEntry(p, res.matchs["RemainderQuery"]);
				if (AdjetiveMatch != nullptr)
				{
					return std::make_shared<CBlockMatchDirectIs>(c1, AdjetiveMatch);
				}
			}

			return nullptr;		
		}
	}



	{// which (Person) is (the targert) -> Enforce (Return Value) as Person
		CPredSequence predList = mk_What_Which() <<pAny("kindReturn")	<<p->verbList	<<pAny("RemainderQuery");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));


			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);			
			if (c1 != nullptr)
			{
				HBlockMatch  AdjetiveMatch = ExpressionMatch::parser_expression_match(p, res.matchs["RemainderQuery"]);

				if (AdjetiveMatch != nullptr)
				{
					return std::make_shared<CBlockMatchIsVerb>(vrepr, c1, AdjetiveMatch);
				}
			}
		}
	}
	return nullptr;
}


HBlockMatchIs NSParser::ParseDecide::parser_Match_IF_Assertion(CParser * p, HTerm term )
{
    

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << verb_IS() << pAny("ADV") << pLiteral("than") << pAny("BValue");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			auto vrepr = CtoString(expandBract(res.matchs["ADV"]));

			return std::make_shared<CBlockMatchIsAdverbialComparasion>(vrepr, AValue, BValue);
		}
	}
	{
		CPredSequence predList = pLiteral("if")	<<pAny("AValue")<< p->verbList	<<pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchIsVerb >(vrepr, AValue, BValue);
		}
	}

	{
		CPredSequence predList = pLiteral("if")	<<pAny("AValue")	<<verb_IS()	<<pAny("BValue");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchDirectIs>(AValue, BValue);
		}
	}

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1") << pWord("C2") << pWord("C3") << pWord("C4") << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					HBlockMatch NC3 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C3"]);
					HBlockMatch NC4 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C4"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) && (NC3 != nullptr) && (NC4 != nullptr))
					{
						std::list<HBlockMatch> _matchList = { NC1,NC2,NC3,NC4 };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}



	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1")<< pWord("C2")<< pWord("C3") << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					HBlockMatch NC3 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C3"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) && (NC3 != nullptr))
					{
						std::list<HBlockMatch> _matchList = {NC1,NC2,NC3};
						HBlockMatchList mlist =  std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}					
				}
			}
		}
	}

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1") << pWord("C2")   << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) )
					{
						std::list<HBlockMatch> _matchList = { NC1,NC2  };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}


	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1")   << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);	
					if ((NC1 != nullptr)  )
					{
						std::list<HBlockMatch> _matchList = { NC1  };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}


    {
        CPredSequence predList = pLiteral("if") << pAny("AValue")  ;
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;
            auto r =  res.matchs["AValue"].get();
			
			//return std::make_shared<CBlockMatchIs>(AValue );
			logError(r->repr());
			return nullptr;
        }
    }

    return nullptr;

}



HBlockToDecide NSParser::ParseDecide::parseAssertion_isDecide_inLine(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{

	 

 

   
	if (inner == nullptr)
	{
		{
			  CPredSequence predList = pLiteral("to") <<pLiteral("decide")<<pAny("Match")	<<pLiteral(":")	<<pAny("RemainBody");
		 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"] );
				if (a_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


				HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat>(w_match, body);
				}


				logError("Decide mal formado");
				return nullptr;

			}
		}
	}

	if (inner != nullptr)
	{
		//Com bloco inner 
		{

			CPredSequence predList = pLiteral("to") << pLiteral("decide") << pAny("Match") << pLiteral(":");

			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"]);
				if (a_match != nullptr)
				{
					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

	            HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match != nullptr)
				{
					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					auto h =  std::make_shared<CBlockToDecideWhat>(w_match, body);
					return h;
				}


				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match != nullptr)
				{
					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


			

				logError("Decide mal formado");
				return nullptr;
			}
		}




 
	}


    return nullptr;
}



std::pair<HBlockMatchList, HBlockMatchList>  NSParser::ParseDecide::parser_match_phraseHeader(CParser * p, HTerm  term, int args_i_item)
{
	std::list<HBlockMatch> phase_i;
	std::list<HBlockMatch> args_i;


 


	{// uma palavra apenas
		CPredSequence predList = pWord("H");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{   
			
			//HBlockNoum n = NSParser::ParseAssertion::parse_noum(p, res.matchs["H"]);

			HBlockMatch tem_h = NSParser::ExpressionMatch::parser_MatchComponentePhase(p, res.matchs["H"]);			
			if (HBlockMatchNamed arg = DynamicCasting::asHBlockMatchNamed(tem_h))
			{
				args_i.push_back(arg);
				phase_i.push_back(std::make_shared<CBlockMatchNamed>("A" + std::to_string(args_i_item), std::make_shared<CBlockMatchAny>()));
			}
			else
			{
				phase_i.push_back(tem_h);
			}
			return std::pair<HBlockMatchList, HBlockMatchList>(std::make_shared<CBlockMatchList >(phase_i), std::make_shared<CBlockMatchList >(args_i));
		}
	}


	{// uma palavra e o resto
		CPredSequence predList = pWord("H") << pAny("Rem");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch tem_h = NSParser::ExpressionMatch::parser_MatchComponentePhase(p, res.matchs["H"]);
			if (tem_h != nullptr)
			{
				if (HBlockMatchNamed arg = DynamicCasting::asHBlockMatchNamed(tem_h))
				{
					args_i.push_back(arg);
					phase_i.push_back(std::make_shared<CBlockMatchNamed>("A" + std::to_string(args_i_item), std::make_shared<CBlockMatchAny>()));
					args_i_item++;
				}
				else
				{
					phase_i.push_back(tem_h);
				}

				std::pair<HBlockMatchList, HBlockMatchList> p12 = parser_match_phraseHeader(p, res.matchs["Rem"], args_i_item);
				phase_i.insert(phase_i.end(), p12.first->matchList.begin(), p12.first->matchList.end());
				args_i.insert(args_i.end(), p12.second->matchList.begin(), p12.second->matchList.end());
				return std::pair<HBlockMatchList, HBlockMatchList>(std::make_shared<CBlockMatchList >(phase_i), std::make_shared<CBlockMatchList >(args_i));
			}
			 
		}
	}



	 

	{// uma palavra e o resto
		CPredSequence predList = pAny("arg") << pAny("Rem");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch tem_h =  NSParser::ExpressionMatch::parser_MatchComponentePhase(p, res.matchs["arg"]);

			if (tem_h != nullptr)
			{
				if (HBlockMatchNamed arg = DynamicCasting::asHBlockMatchNamed(tem_h))
				{
					args_i.push_back(arg);
					phase_i.push_back(std::make_shared<CBlockMatchNamed>("A" + std::to_string(args_i_item), std::make_shared<CBlockMatchAny>()));
					args_i_item++;
				}
				else
				{
					phase_i.push_back(tem_h);
				}

				std::pair<HBlockMatchList, HBlockMatchList> p12 = parser_match_phraseHeader(p, res.matchs["Rem"], args_i_item);
				phase_i.insert(phase_i.end(), p12.first->matchList.begin(), p12.first->matchList.end());
				args_i.insert(args_i.end(), p12.second->matchList.begin(), p12.second->matchList.end());
				return std::pair<HBlockMatchList, HBlockMatchList>(std::make_shared<CBlockMatchList >(phase_i), std::make_shared<CBlockMatchList >(args_i));
			}
		}
	}


	{// uma variavel apenas
		CPredSequence predList = pAny("arg");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch arg = NSParser::ExpressionMatch::parser_MatchComponentePhase(p, res.matchs["arg"]);

			if (arg != nullptr)
			{
				args_i.push_back(arg);
				phase_i.push_back(std::make_shared<CBlockMatchNamed>("A" + std::to_string(args_i_item), std::make_shared<CBlockMatchAny>()));
				args_i_item++;
				return std::pair<HBlockMatchList, HBlockMatchList>(std::make_shared<CBlockMatchList >(phase_i), std::make_shared<CBlockMatchList >(args_i));
			}
		}
	}



	HBlockMatchList mphase_i = std::make_shared<CBlockMatchList >(phase_i);
	HBlockMatchList margs_i = std::make_shared<CBlockMatchList >(args_i);
	return std::pair<HBlockMatchList, HBlockMatchList>(mphase_i, margs_i);
}


HBlock NSParser::ParseDecide::parseAssertion_isDecide (CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{ 

	{
		CPredSequence predList = pLiteral("to") << pLiteral("decide") << pAny("KindReturn") << mk_What_Which() << verb_IS() << pAny("PhaseHeader") << pLiteral(":");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			std::pair<HBlockMatchList, HBlockMatchList>  AdjetiveMatch = parser_match_phraseHeader(p, res.matchs["PhaseHeader"],1);
			if (AdjetiveMatch.first != nullptr)
			{
				HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
				if (body != nullptr)
				{
					HBlockNoum name = p->get_next_headerName();
					auto header = std::make_shared<CBlockPhraseHeader>(name, AdjetiveMatch.first , AdjetiveMatch.second);
					return std::make_shared<CBlockPhraseDefine>(header, body);
				}
			}

			logError("Decide mal formado");
		}
	}


	auto hdecide =  parseAssertion_isDecide_inLine(p, term, inner, err);
	if (hdecide != nullptr)
	{
		return hdecide;
		//return std::make_shared<CBlockPhraseDefine>(name, hdecide->, body);
	}






	//{
	//	// to doing somethig with another thing
	//	CPredSequence predList = pLiteral("to") << pWord("Verb") << pAny("Match_arg1") << pPreposition("pred") << pAny("Match_arg2") << pLiteral(":");
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals)
	//	{
	//		HBlockMatch  marg1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["Match_arg1"]);
	//		if (marg1 != nullptr)
	//		{
	//			HBlockMatch  marg2 = ExpressionMatch::parser_MatchArgument(p, res.matchs["Match_arg2"]);
	//			if (marg2 != nullptr)
	//			{

	//				HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
	//				if (body != nullptr)
	//				{
	//					HBlockNoum nVerb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
	//					HBlockNoum nPred = std::make_shared<CBlockNoumStr>(res.matchs["pred"]->repr());
	//					HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(nVerb, nullptr, nPred, marg1, marg2);
	//					p->phrases.push_back(nheader);
	//					return std::make_shared<CBlockPhraseDefine>(nheader, body);
	//				}
	//			}
	//		}
	//	}
	//}


	////isso aqui é phase definition
	//{
	//	CPredSequence predList = pLiteral("to") << pWord("Verb") << pAny("terms") << pLiteral(":");
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals)
	//	{
	//		HBlockNoum nVerb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
	//		auto term_q = res.matchs["terms"];
	//		HBlockPhraseHeader nheader = nullptr;
	//		for (auto term12 : getBiPartition(term_q))
	//		{
	//			HBlockMatch  marg2 = ExpressionMatch::parser_MatchVariableDeclare(p, term12.second);
	//			if (marg2 != nullptr)
	//			{
	//				//processa o inico  N VAR N
	//				for (auto mterm123 : getTriPartition(term12.first))
	//				{
	//					HBlockMatchNoum  mnoum1 = ExpressionMatch::parser_expression_match_noum(p, mterm123[0]);
	//					if (mnoum1 == nullptr) continue;
	//					HBlockMatch  marg1 = ExpressionMatch::parser_MatchVariableDeclare(p, mterm123[1]);
	//					if (marg1 == nullptr) continue;
	//					HBlockMatchNoum  mnoum3 = ExpressionMatch::parser_expression_match_noum(p, mterm123[2]);
	//					if (mnoum3 == nullptr) continue;
	//					nheader = std::make_shared<CBlockPhraseHeader>(nVerb, mnoum1->inner, mnoum3->inner, marg1, marg2);
	//					break;
	//				}

	//				if (nheader == nullptr)
	//				{
	//					for (auto mterm12 : getBiPartition(term12.first))
	//					{

	//						HBlockMatch  marg1 = ExpressionMatch::parser_MatchVariableDeclare(p, mterm12.first);
	//						if (marg1 == nullptr) continue;


	//						HBlockNoum  mnoum3 = convert_to_noum(p, mterm12.second);
	//						if (mnoum3 == nullptr) continue;
	//						nheader = std::make_shared<CBlockPhraseHeader>(nVerb, mnoum3, nullptr, marg1, marg2);
	//						break;
	//					}
	//				}
	//				if (nheader == nullptr)
	//				{
	//					HBlockNoum  mnoum_pred = convert_to_noum(p, term12.first);
	//					if (mnoum_pred != nullptr)
	//					{
	//						nheader = std::make_shared<CBlockPhraseHeader>(nVerb, mnoum_pred, nullptr, marg2, nullptr);
	//					}
	//				}

	//				if (nheader != nullptr)
	//				{
	//					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
	//					if (body != nullptr)
	//					{
	//						//HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(nVerb, nullptr, nullptr, marg2, nullptr);
	//						p->phrases.push_back(nheader);
	//						return std::make_shared<CBlockPhraseDefine>(nheader, body);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


return nullptr;
}


HBlock NSParser::ParseDecide::parseAssertion_DecideOn(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{
		{
			  CPredSequence predList =  			pLiteral("decide") <<pLiteral("on")	<<pAny("ExpressionBody");
			 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
					logMessage((res.matchs["ExpressionBody"]->repr()));
					HBlock body = Expression::parser_expression(p, res.matchs["ExpressionBody"]);
					return std::make_shared<CBlockToDecideOn>( body);
			}
		}
	}
	 
		return nullptr;
	 


}

HBlock NSParser::ParseDecide::STMT_Definition_Assertion(CParser * p, std::vector<HTerm>&  term)
{

    {
		  auto c1 = pList({ pLiteral("definition"), pLiteral(":") });
		  auto c2 = pLiteral("definition:");

		  CPredSequence predList  = (pOr("kindpart", c1, c2))	<<pAny("Match") <<pLiteral("if")	<<pAny("LogicalBody");
		 

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			HBlockMatchIsVerb  v_match = ExpressionMatch::parserMatchIsConditionVerb (p,res.matchs["Match"]);
			if (v_match != nullptr)
			{
				HBlock body = Statement::parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(v_match, body);
			}

			HBlockMatchIs a_match = ExpressionMatch::parserMatchIsCondition(p,res.matchs["Match"]);
			if (a_match != nullptr)
			{
				HBlock body = Statement::parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}
			return nullptr;
        }
    }
    return nullptr;
}






HBlock NSParser::ParseDecide::parse_toDecide_Entry(CParser * p, std::vector<HTerm>&  term) 
{
    {
        CPredSequence predList = pLiteral("to") <<pLiteral("decide") <<pLiteral(":");
        return nullptr;
    }
}

HBlock NSParser::ParseDecide::parse_toDecide_Ret(CParser * p, std::vector<HTerm>&  term) {
    {
        CPredSequence predList = pLiteral("decide") <<pLiteral("on") <<pAny("Subst");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_expression(p,res.matchs["Subst"]);
            if (n1 == nullptr) return nullptr;
            return std::make_shared<CBlockToDecideOn>(n1);
        }
    }
    return nullptr;
}

HBlock NSParser::ParseDecide::parser_decides_Assertion(CParser * p, std::vector<HTerm>&  term) 
{

    HBlock verb_decideIn = parse_toDecide_Entry(p,term);
    if (verb_decideIn != nullptr) {
        return verb_decideIn;
    }

    HBlock verb_decideRet = parse_toDecide_Ret(p,term);
    if (verb_decideRet != nullptr) {
        return verb_decideRet;
    }

    return nullptr;


}





