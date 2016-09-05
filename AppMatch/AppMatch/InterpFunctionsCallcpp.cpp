//Executor de acoes 

#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <memory>
#include <iostream>
#include "CBlockScope.h"
#include "QueryStack.h"
using namespace std;


bool CBlockInterpreter::execute_system_action(HBlockActionCall v_call)
{
	v_call->action->dump(" " );

	if (v_call->action->named == "say_text")
	{
		if (HBlockText  ntext = dynamic_pointer_cast<CBlockText>(v_call->noum1))
		{
			printf("root$ %s \n", ntext->contents.c_str());
			return true;
		}
	}
	return false;
}
 

bool CBlockInterpreter::execute_user_action(HBlockActionCall v_call)
{
	 

	return false;
}