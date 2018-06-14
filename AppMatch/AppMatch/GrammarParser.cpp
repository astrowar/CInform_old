// PVS
// PVQ
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


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
