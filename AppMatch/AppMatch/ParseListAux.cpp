// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "Parser.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;
 
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;





HBlockList NSParser::ParseList::parseAssertion_Strict_COMMA_Supl(CParser * p, HTerm term, HPred sep) {

    CPredSequence predList = pAny("N1")  <<sep <<pAny("N2");
    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
        cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
        cList = ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
        return cList;
    }
    return nullptr;
}

HBlockList  NSParser::ParseAssertion::parseAssertionFirstTerm_COMMA_Supl( CParser * p, HTerm term, HPred sep, HBlockList cList) {
    CPredSequence predList =pAny("N1")   <<(pOr("sep", pLiteral(","), sep)) <<pAny("N2");

    MatchResult res = CMatch(term, predList);
    if (res.result == Equals) {
        cList = parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N1"], sep, cList);
        cList = parseAssertionFirstTerm_COMMA_Supl(p,res.matchs["N2"], sep, cList);
        return cList;
    }

    HBlock ret = Expression::parser_expression(p,term);
    cList->push_back(ret);
    //cList->push_back(std::make_shared<CBlockNoumStr>(  term->removeArticle()->repr()));
    return cList;
}

std::list<HBlock>  concat_terms(CBlocking::HBlock c1, CBlocking::HBlock c2)
{
	std::list<HBlock> cList;

	if ((c1->type() != BlockType::BlockList_OR) && (c1->type() != BlockType::BlockList_AND)) // apenas lista neutras 
	{
		if (HBlockList s1 = DynamicCasting::asHBlockList(c1))
		{
			for (auto c : s1->lista) cList.push_back(c);
		}
		else
		{
			cList.push_back(c1);
		}
	}
	else
	{
		cList.push_back(c1);
	}
	
	if ((c2->type() != BlockType::BlockList_OR) && (c2->type() != BlockType::BlockList_AND))// apenas lista neutras 
	{
		if (HBlockList s2 = DynamicCasting::asHBlockList(c2))
		{
			for (auto c : s2->lista) cList.push_back(c);
		}
		else
		{
			cList.push_back(c2);
		}
	}
	else
	{
		cList.push_back(c2);
	}

	return cList;

}

HBlockList  NSParser::ParseAssertion::parseAssertionList_COMMA_neutral(CParser * p, HTerm term ) 
{
	// obtem uma lista que esta separada apenas por virgula
	CPredSequence predList = pAny("N1")<<pLiteral(",")<<pAny("N2");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) {
		CBlocking::HBlock t1 = Expression::parser_expression(p, res.matchs["N1"]);
		CBlocking::HBlock t2  = Expression::parser_expression(p, res.matchs["N2"]);
		HBlockList cList = std::make_shared<CBlockList>( concat_terms(t1, t2));
	}
	return nullptr;

}





HBlockList NSParser::ParseList::parseAssertionFirstTerm_COMMA_AND(CParser * p, HTerm term, HBlockList CList) {
    return ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,term, pLiteral("and"), CList);
}

HBlockList NSParser::ParseList::parseAssertionFirstTerm_COMMA_OR(CParser * p, HTerm term, HBlockList CList) {
    return ParseAssertion::parseAssertionFirstTerm_COMMA_Supl(p,term, pLiteral("or"), CList);
}


HBlock NSParser::ParseList::parse_List_Neutral(CParser * p, std::vector<HTerm>& term)
{
	// obtem uma lista que esta separada apenas por virgula
	CPredSequence predList = pAny("N1") <<pLiteral(",")	<<pAny("N2");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) 
	{
		CBlocking::HBlock t1 = Expression::parser_expression(p, res.matchs["N1"]);
		if (t1 != nullptr)
		{
			auto pterm2 = res.matchs["N2"];
			auto ss2 = pterm2->repr();

			 

			CBlocking::HBlock t2 = Expression::parser_expression(p, res.matchs["N2"]);
			if(t2 ==nullptr)
			{
				CBlocking::HBlock t3 = Expression::parser_expression(p, res.matchs["N2"]);
			}
			if (t2 != nullptr)
			{
				return   std::make_shared<CBlockList>(concat_terms(t1, t2));
			}
		}
	}
	return nullptr;
}




HBlock NSParser::ParseList::parse_List_AND(CParser * p, std::vector<HTerm>& term) 
{
    {
        auto sep = pLiteral("and");
        CPredSequence predList = pAny("N1")      <<sep <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{ 
			//printf("%s  AND %s  \n", ss1.c_str(), ss2.c_str());

            HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>()); 
			HBlock ret_1 = Expression::parser_expression(p, res.matchs["N1"]);
			if (ret_1 != nullptr)
			{
				HBlock ret_2 = Expression::parser_expression(p, res.matchs["N2"]);
				if (ret_2 != nullptr)
				{
					HBlockList_AND  and_List = std::make_shared<CBlockList_AND  >(concat_terms(ret_1, ret_2));					
					return and_List;
				}
			}
        }
    }
	 
    return nullptr;

}


HBlock NSParser::ParseList::parse_List_OR(CParser * p, std::vector<HTerm>& term) {
	{
		auto sep = pLiteral("or");
		CPredSequence predList = pAny("N1")	<<sep	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockList cList = std::make_shared<CBlockList>(std::list<HBlock>());
			HBlock ret_1 = Expression::parser_expression(p, res.matchs["N1"]);
			if (ret_1 != nullptr)
			{
				HBlock ret_2 = Expression::parser_expression(p, res.matchs["N2"]);
				if (ret_2 != nullptr)
				{
					HBlockList_OR  or_List = std::make_shared<CBlockList_OR  >(concat_terms(ret_1, ret_2));
					return or_List;
				}
			}
		}
	}

 
 

	return nullptr;

}




HBlockList NSParser::ParseList::parse_Strict_COMMA_AND(CParser * p, HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(p,term, pLiteral("and"));
}

HBlockList NSParser::ParseList::parse_Strict_COMMA_OR(CParser * p, HTerm term) {
    return parseAssertion_Strict_COMMA_Supl(p,term, pLiteral("or"));
}