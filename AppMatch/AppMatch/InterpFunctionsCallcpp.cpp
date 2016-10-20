//Executor de acoes 

#include "CBlockInterpreterRuntime.hpp"
#include "CResultMatch.hpp"
#include <memory>
 
#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
using namespace std;


bool CBlockInterpreter::execute_system_action(HBlockActionCall v_call)
{
	v_call->action->dump(" " );

	if (v_call->action->named == "say_text")
	{
		if (HBlockText  ntext = asHBlockText(v_call->noum1))
		{
			printf("root$ %s \n", ntext->contents.c_str());
			return true;
		}
	}
	if (v_call->action->named == "say")
	{
		if (HBlockText  ntext = asHBlockText(v_call->noum1))
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