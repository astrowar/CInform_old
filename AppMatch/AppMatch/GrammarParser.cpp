#include "GrammarParser.h"
// ReSharper disable All 


GrammarParser::GrammarParser()
{
}


GrammarParser::~GrammarParser()
{
}

std::string GrammarParserEn::pluralOf(std::string s)
{
	for(auto kv = noum_map.begin() ; kv != noum_map.end();++kv)
	{
		if ((kv->second.modificador == NNS) && (kv->second.base == s))
		{
			return kv->second.noum;
		}
	}
	return std::string();
}

std::string GrammarParserEn::singularOf(std::string s)
{

	return std::string();
}
