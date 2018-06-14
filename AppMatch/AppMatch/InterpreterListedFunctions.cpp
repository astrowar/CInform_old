// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "BlockInterpreter.hpp"
 

#include "CblockAssertion.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
 


QueryResultContext CBlockInterpreter::queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	if (HBlockNoum   nnoum2 = asHBlockNoum(n2))
	{
		HBlock resolved = resolve_noum(nnoum2,localsEntry);
		
		return queryVerb_ListedIn(n1, resolved, localsEntry, stk);
	}

	if (HBlockVariableNamed   nvar2 = asHBlockVariableNamed(n2))
	{ 
		return queryVerb_ListedIn(n1, nvar2->value, localsEntry,  stk);
	}

	if (HBlockList   val_list = asHBlockList(n2))
	{
		 for( auto &hb : val_list->lista )
		 {
			 QueryResultContext qcc = query_is(n1, hb, localsEntry, stk);
			 if ( qcc.result == QEquals) return qcc;
		 }
		 return QNotEquals;
	}
	
	return QUndefined;
}