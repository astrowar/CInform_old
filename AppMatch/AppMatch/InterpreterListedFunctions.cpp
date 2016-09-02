#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "QueryStack.h"

using namespace std;

QueryResul CBlockInterpreter::queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack stk)
{
	
	if (HBlockNoum   nnoum2 = dynamic_pointer_cast<CBlockNoum>(n2))
	{
		HBlock resolved = resolve_noum(nnoum2,localsEntry);
		
		return queryVerb_ListedIn(n1, resolved, localsEntry, stk);
	}

	if (HVariableNamed   nvar2 = dynamic_pointer_cast<CVariableNamed>(n2))
	{ 
		return queryVerb_ListedIn(n1, nvar2->value, localsEntry,  stk);
	}

	if (HBlockList   val_list = dynamic_pointer_cast<CBlockList>(n2))
	{
		 for( auto &hb : val_list->lista )
		 {
			 if (query_is(n1, hb, localsEntry, stk) == QEquals) return QEquals;
		 }
		 return QNotEquals;
	}
	
	return QUndefined;
}