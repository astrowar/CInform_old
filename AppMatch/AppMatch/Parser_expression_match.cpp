#include "Parser.h"
#include <iostream>



HBlockMatchProperty  CParser::parse_PropertyOf_Match(std::vector<HTerm> term) 
{
	{

		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("property"));
			predList.push_back(mk_HPredLiteral("of"));
			predList.push_back(mkHPredAny("obj"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock a = parser_expression(res.matchs["property"]);
			if (a != nullptr) {
				HBlockMatch b = parser_expression_match(res.matchs["obj"]);
				if (b != nullptr) {					 
					return std::make_shared<CBlockMatchProperty>(a, b);
				}
			}
		}
	}
	return nullptr;
}

HBlockMatch CParser::parse_match_noum(std::vector<HTerm> term) {
	std::vector<HPred> predList;
 
	predList.push_back(mkHPredAny("Noum"));
	MatchResult res = CMatch(term, predList);

	if (res.result == Equals) {
		string nstr = CtoString(res.matchs["Noum"]->removeArticle());
		return std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(nstr));
	}
	return nullptr;
}


HBlockMatch CParser::parse_AssertionVerb_Match(std::vector<HTerm> term) {
	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(verb_IS_NOT());
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
			return std::make_shared<CBlockMatchIsNotVerb>(vrepr, n1, n2);
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(mk_HPredLiteral("not"));
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
			return std::make_shared<CBlockMatchIsNotVerb>(vrepr, n1, n2);

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(verb_IS());
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

			return std::make_shared<CBlockMatchIsVerb>(vrepr, n1, n2);

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
			return std::make_shared<CBlockMatchIsVerb>(vrepr, n1, n2);

		}
	}

	return nullptr;
}


HBlockMatchIs  CParser::parse_AssertionDirectAssign_Match(std::vector<HTerm> term) {
	{
		// is a kind definition ??
	 
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("Noum"));
			predList.push_back(verb_IS_NOT());
			predList.push_back(mkHPredAny("Value"));
		}

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlockMatch noum = parser_expression_match(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlockMatch value = parser_expression_match(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return std::make_shared<CBlockMatchDirectIsNot>(noum, value);
		}
	}
	{
		// is a kind definition ??
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("Noum"));
			predList.push_back(verb_IS());
			predList.push_back(mkHPredAny("Value"));
		}

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlockMatch value = parser_expression_match(res.matchs["Value"]);
			if (value == nullptr) return nullptr;

			{
				HBlockMatch noum = parser_expression_match(res.matchs["Noum"]);
				if (noum == nullptr) return nullptr;
				return std::make_shared<CBlockMatchDirectIs>(noum, value);
			}

		}
	}

	return nullptr;

}




HBlockMatch   CParser::parser_Verb_Match(std::vector<HTerm> term)
{

	HBlockMatch aVerb = parse_AssertionVerb_Match(term);
	if (aVerb != nullptr)
	{
		return aVerb;
	}

	HBlockMatch aDirect = parse_AssertionDirectAssign_Match(term);
	if (aDirect != nullptr)
	{
		return aDirect;
	}

	return nullptr;
}



HBlockMatch CParser::parser_expression_match(HTerm  term)
{
	if (CList *vlist = asCList(term.get())) {
		auto r = parser_expression_match(vlist->asVector());
		/*if (r == nullptr)
		std::cout << term->repr() << std::endl;*/
		return r;
	}
	auto nn =  std::make_shared<CBlockNoum>(CtoString(term));
	return std::make_shared<CBlockMatchNoum>(nn);
}

std::list<HBlockMatch> CParser::ToMatchListMatc(std::vector<HPred> pvector, MatchResult result)
{
	std::list<HBlockMatch> vlist;
	for (size_t j = 0; j< pvector.size(); ++j)
	{
		if (CPredAtom* vAtom = asPredAtom(pvector[j].get()))
		{
			vlist.push_back(std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(vAtom->h->repr())));
		}
		else if (CPredAny * vAny = asPredAny(pvector[j].get()))
		{
			HBlockMatch n1 = parser_expression_match(result.matchs[vAny->named]);
			vlist.push_back(n1);
		}
		else
		{
			std::cout << "error" << std::endl;
		}
	}
	return vlist;
}


HBlockMatch CParser::DynamicDispatch_action_match(std::vector<HTerm> term) {

	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it)
	{

		MatchResult res_action = CMatch(term, it->matchPhase);
		if (res_action.result == Equals)
		{			 
			std::list<HBlockMatch> resList = ToMatchListMatc(it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockMatchList>(resList);
			return 	clistResults;
		}

	}
	return nullptr;
}



HBlockMatch CParser::parse_match_list(std::vector<HTerm>    term)
{

	{

		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("N1"));
			predList.push_back(mkHPredAny("N2"));
			predList.push_back(mkHPredAny("N3"));
			predList.push_back(mkHPredAny("N4"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
				if (n2 != nullptr)
				{
					HBlockMatch n3 = parser_expression_match(res.matchs["N3"]);
					if (n3 != nullptr)
					{
						HBlockMatch n4 = parser_expression_match(res.matchs["N4"]);
						if (n4 != nullptr)
						return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2, n3 , n4});
					}

					
				}
			}

		}
	}


	{

		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("N1"));
			predList.push_back(mkHPredAny("N2"));
			predList.push_back(mkHPredAny("N3"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
				if (n2 != nullptr)
				{
					HBlockMatch n3 = parser_expression_match(res.matchs["N3"]);
					return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2 ,n3 });
				}
			}

		}
	}


	{
		 
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("N1"));
			predList.push_back(mkHPredAny("N2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			
			HBlockMatch n1 = parser_expression_match(res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(res.matchs["N2"]);
				if (n2 != nullptr)
					return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2 });
			}
		
		}
	}
	return nullptr;
}



HBlockMatch CParser::parser_expression_match(std::vector<HTerm>   lst)
{

	HBlockMatch  rblock_dynamicEntry_1 = (DynamicDispatch_action_match(lst));
	if (rblock_dynamicEntry_1 != nullptr) return rblock_dynamicEntry_1;

	HBlockMatch rblock_assert_1 = (parser_Verb_Match(lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;



	HBlockMatch noum_propOF = parse_PropertyOf_Match(lst);
	if (noum_propOF != nullptr) {
		return noum_propOF;
	}

	 

	HBlockMatch arg_Assign = parser_MatchArgument(lst);
	if (arg_Assign != nullptr) {
		return arg_Assign;
	}

	HBlockMatch list_Assign = parse_match_list(lst);
	if (list_Assign != nullptr) {
		return list_Assign;
	}

	HBlockMatch noum_Assign = parse_match_noum(lst);
	if (noum_Assign != nullptr) {
		return noum_Assign;
	}

	return nullptr;

}