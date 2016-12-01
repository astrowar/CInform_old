// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BlockInterpreter.hpp"
 

#include "CblockAssertion.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;

QueryResultContext CBlockInterpreter::queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack stk)
{
	
	if (HBlockNoum   nnoum2 = asHBlockNoum(n2))
	{
		HBlock resolved = resolve_noum(nnoum2,localsEntry);
		
		return queryVerb_ListedIn(n1, resolved, localsEntry, stk);
	}

	if (HVariableNamed   nvar2 = asHVariableNamed(n2))
	{ 
		return queryVerb_ListedIn(n1, nvar2->value, localsEntry,  stk);
	}

	if (HBlockList   val_list = asHBlockList(n2))
	{
		 for( auto &hb : val_list->lista )
		 {
			 QueryResultContext qcc = query_is(n1, hb, localsEntry, stk);
			 if ( qcc.result == QEquals) return QEquals;
		 }
		 return QNotEquals;
	}
	
	return QUndefined;
}