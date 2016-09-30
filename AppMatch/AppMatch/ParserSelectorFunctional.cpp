#include "Parser.h"



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

HBlockSelector   CParser::parser_List_selector(std::vector<HTerm> term)
{
	{
		// is a kind definition ??
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("all"));
			predList.push_back(mkHPredAny("List"));
		}
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			HBlock noum = parser_assertionTarger(res.matchs["List"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockSelector_All>(noum);
		}
	}

	{
		// is a kind definition ??
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("any"));
			predList.push_back(mkHPredAny("List"));
		}
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			HBlock noum = parser_assertionTarger(res.matchs["List"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockSelector_Any>(noum);
		}
	}


	return nullptr;
}


 

HBlockSelector CParser::parser_List_selector(HTerm  term)
{
	if (CList *vlist = asCList(term.get())) {
		auto r = parser_List_selector(vlist->asVector());		 
		return r;
	}
	return nullptr; // isso porque nao vale 1 unico termo como seletor
}

 