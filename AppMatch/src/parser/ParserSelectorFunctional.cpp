// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Parser\Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


//all
//all but
//all except
//almost all
//almost no
//at least
//at most
//each
//every
//exactly
//fewer than
//less than
//more than
//most
//no
//none
//some
//under half
//a number alone, as in "three swans"

HBlockSelector   NSParser::ParseSelector::parser_List_selector(CParser * p, std::vector<HTerm>&  term)
{
	{
		// is a kind definition ??
		  CPredSequence predList = pLiteral("all")	<<pAny("List");

		 
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["List"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockSelector_All>(noum);
		}
	}

	{
		// is a kind definition ??
		  CPredSequence predList =  pLiteral("any")	<<pAny("List");
		 
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["List"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockSelector_Any>(noum);
		}
	}


	return nullptr;
}


 

HBlockSelector NSParser::ParseSelector::parser_List_selector(CParser * p, HTerm  term)
{
	if (CList *vlist = asCList(term.get())) 
	{
		auto v =vlist->asVector();
		auto r = parser_List_selector(p,v);
		return r;
	}
	return nullptr; // isso porque nao vale 1 unico termo como seletor
}

 