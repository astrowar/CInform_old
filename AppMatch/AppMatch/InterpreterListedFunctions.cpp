#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "QueryStack.h"
#include "sharedCast.h"

using namespace std;

QueryResul CBlockInterpreter::queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack stk)
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
			 if (query_is(n1, hb, localsEntry, stk) == QEquals) return QEquals;
		 }
		 return QNotEquals;
	}
	
	return QUndefined;
}