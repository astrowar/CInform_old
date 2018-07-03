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



 
QueryResultContext CBlockInterpreter::queryVerb_matches(CBlocking::HBlock value, CBlocking::HBlock mregex, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockText text = DynamicCasting::asHBlockText(value))
	{
		if (HBlockText regex_text = DynamicCasting::asHBlockText(mregex))
		{
			if (std::regex_search(text->contents, std::regex(regex_text->contents)))				
			{
				return QEquals;
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