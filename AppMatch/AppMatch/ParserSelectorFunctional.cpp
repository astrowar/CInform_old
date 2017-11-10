// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



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

 