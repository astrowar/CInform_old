#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "QueryStack.h"

using namespace std;

QueryResul CBlockInterpreter::queryVerb_ListedIn(HBlock n1, HBlock n2,   QueryStack stk)
{
	
	if (HBlockNoum   nnoum2 = dynamic_pointer_cast<CBlockNoum>(n2))
	{
		HBlock resolved = resolve_noum(nnoum2);
		
		return queryVerb_ListedIn(n1, resolved, stk);
	}

	if (HVariableNamed   nvar2 = dynamic_pointer_cast<CVariableNamed>(n2))
	{ 
		return queryVerb_ListedIn(n1, nvar2->value, stk);
	}

	if (HBlockList   val_list = dynamic_pointer_cast<CBlockList>(n2))
	{
		 for( auto &hb : val_list->lista )
		 {
			 if (query_is(n1, hb, stk) == QEquals) return QEquals;
		 }
		 return QNotEquals;
	}
	
	return QUndefined;
}