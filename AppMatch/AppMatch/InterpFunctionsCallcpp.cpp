//Executor de acoes 


#include "CResultMatch.hpp"
#include <memory>
 
#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;


bool CBlockInterpreter::execute_phase_before(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{
	// busca por algum before que eh compativel com esta regra e aplica ela


	return true;
}





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
 

bool CBlockInterpreter::execute_user_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{
	 
	logMessage("EXEC CALL ! ");
	v_call->dump("");

	//verifica se os objetos da acao estao condicentes com os requeimentos
	for (auto &ah : actions_header)
	{
		if (ah->named == v_call->action->named)
		{
			ah->dump(" ");
		}
	}
	printf("===============================\n");
	HBlockKindAction kaction = nullptr;
	for (auto &ap : actions_parameters)
	{
		if (ap.first == v_call->action->named)
		{
			if (v_call->noum1 == nullptr  && ap.second->applyTo->noum1 != nullptr) continue;
			if (v_call->noum2 == nullptr  && ap.second->applyTo->noum2 != nullptr) continue;
			if (v_call->noum1 != nullptr  && ap.second->applyTo->noum1 == nullptr) continue;
			if (v_call->noum2 != nullptr  && ap.second->applyTo->noum2 == nullptr) continue;


			//verifica se os argumentos sao compativeis

			if (v_call->noum1 != nullptr)
			{
				auto qarg1 = query_is(v_call->noum1, ap.second->applyTo->noum1, localsEntry, stk);
				if (qarg1 != QEquals) continue; 
			}


			if (v_call->noum2 != nullptr)
			{
				auto qarg2 = query_is(v_call->noum2, ap.second->applyTo->noum2, localsEntry, stk);
				if (qarg2 != QEquals) continue;
			}


			kaction = ap.second;
			break;
		}

	}
	if (kaction == nullptr) {
		return false;
	}
	
	


	kaction->dump(" ");
	//Para executar a acao devo ir  na ordem

	//Before
	execute_phase_before(v_call, localsEntry, stk);
	//Instead

	//Check

	//Daqui para  frente a acao eh sucesso 

	//CarryOut

	//After

	//Report

	return true;
}