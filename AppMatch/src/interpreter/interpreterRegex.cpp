// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "interpreter/QueryStack.hpp"
#include "CResultMatch.hpp"

#include <algorithm>

#include "sharedCast.hpp"
#include "dynamicCast.hpp"
#include <cstring>
#include <regex>
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace QueryStacking;


std::map<std::string, HBlock> CBlockInterpreter::get_matches_cases(std::vector<string> matches)
{  
	std::map<std::string, HBlock> matchs_cases;
	int j = 0;
	for (auto mi : matches )
	{	
		if (j == 10) break;
		printf("%s \n", mi.c_str());
		string sub_expression = this->language->text_matching_subexpression(j);
		matchs_cases[sub_expression] = std::make_shared<CBlockText>(mi);
		j++;
		
	}
	for (int k = j ; k<= 9;++k) matchs_cases[this->language->text_matching_subexpression(k)] = Nothing; //Zera os demais
	return matchs_cases;
}
 
QueryResultContext CBlockInterpreter::queryVerb_matches(CBlocking::HBlock value, CBlocking::HBlock mregex, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockText text = DynamicCasting::asHBlockText(value))
	{
		if (HBlockText regex_text = DynamicCasting::asHBlockText(mregex))
		{
			std::smatch m;
			if (std::regex_search(text->contents, m , std::regex(regex_text->contents)))				
			{
				 
				std::vector<string> matches;
				for (auto mi : m) { matches.push_back(mi.str());}

				//"text matching"
				std::map<std::string, HBlock> matchs_cases = get_matches_cases(matches);

				return QueryResultContext(QEquals,matchs_cases) ;
			}
			return QNotEquals;
		}
	}
	else
	{
		CBlocking::HBlock  next_value = exec_eval(value, localsEntry, stk);
		if (CBlock::isSame(next_value.get(), value.get()) == false)
		{
			return queryVerb_matches(next_value, mregex, localsEntry, stk);
		}
	}

	return QUndefined;
}

// Regex nao tem haver com match
// Regex opera apenas com textos, matchs operam com objetos completos

QueryResultContext CBlockInterpreter::queryVerb_exactly_matches(CBlocking::HBlock value, CBlocking::HBlock mregex , HRunLocalScope localsEntry, QueryStack *stk)
{
 
	

	if (HBlockText text = DynamicCasting::asHBlockText(value))
	{
		if (HBlockText regex_text = DynamicCasting::asHBlockText(mregex))
		{
			if (std::regex_match(text->contents, std::regex(regex_text->contents)))			
			{
				return QEquals;
			}
			return QNotEquals;
		}
	}
	else
	{
		CBlocking::HBlock  next_value = exec_eval(value, localsEntry, stk);
		if (CBlock::isSame(next_value.get(), value.get()) ==false )
		{
			return queryVerb_matches(next_value, mregex, localsEntry, stk);
		}
	}

	return QUndefined;
}