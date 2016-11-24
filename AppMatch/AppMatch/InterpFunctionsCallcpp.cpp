//Executor de acoes 


#include "CResultMatch.hpp"
#include <memory>
 
#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;


PhaseResult CBlockInterpreter::execute_phase_any(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{



	QueryResultContext qAction = query_is(v_call->action, evh->eventToObserve->action, localsEntry, stk);
	if (qAction.result == QEquals)
	{
		QueryResul qarg1 = QEquals;
		QueryResul qarg2 = QEquals;

		if (evh->eventToObserve->argument1 == nullptr &&  v_call->noum1 != nullptr) return PhaseResult(false); ;
		if (evh->eventToObserve->argument1 != nullptr &&  v_call->noum1 == nullptr) return PhaseResult(false);
		if (evh->eventToObserve->argument2 == nullptr &&  v_call->noum2 != nullptr) return PhaseResult(false); ;
		if (evh->eventToObserve->argument2 != nullptr &&  v_call->noum2 == nullptr) return PhaseResult(false); ;

		HRunLocalScope next_vars = nullptr;
		if (evh->eventToObserve->argument1 != nullptr)
		{
			auto r1 = Match(evh->eventToObserve->argument1, v_call->noum1, localsEntry, stk);
			if (r1.hasMatch == false) return PhaseResult(false); ;
			next_vars = std::make_shared< CRunLocalScope >(r1.maptch);
			HRunLocalScope tmp_vars = newScope(localsEntry, next_vars);
			next_vars = tmp_vars;
		}


		if (evh->eventToObserve->argument2 != nullptr)
		{
			auto r2 = Match(evh->eventToObserve->argument2, v_call->noum2, next_vars, stk); //observe que os valores ja estao sendo usados
			if (r2.hasMatch == false) return PhaseResult(false); ;
			auto next_vars_2 = std::make_shared< CRunLocalScope >(r2.maptch);
			HRunLocalScope tmp_vars = newScope(next_vars, next_vars_2);
			next_vars = tmp_vars;
		}

		//next vars contem as variaveis 
		PhaseResult  rx = this->execute_now(evh->body, next_vars, stk);

		if (rx.hasExecuted)
		{
			return rx;
		}
	}
	return PhaseResult(false); 
}

		 
 
PhaseResult CBlockInterpreter::execute_phase_check(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{

	for (auto evh : event_handles)
	{
		if (evh->stage == StageCheck)
		{
			auto rx = execute_phase_any(evh, v_call, localsEntry, stk);
			if (rx.result)
			{
				if (HBlockExecutionResultFlag  flag = asHBlockExecutionResultFlag(rx.result) )
				{
					if (flag->flag == actionStop  )
					{
						return rx;
					} 
				}
			}
		}
	}

	return PhaseResult(false);

}


PhaseResult CBlockInterpreter::execute_phase_before(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{
	// busca por algum before que eh compativel com esta regra e aplica ela
	for(auto evh : event_handles)
	{
		if (evh->stage == StageBefore)
		{
			
			QueryResultContext qAction = query_is(v_call->action , evh->eventToObserve->action , localsEntry, stk);
			if (qAction.result == QEquals)
			{
				QueryResul qarg1 = QEquals;
				QueryResul qarg2 = QEquals;
				
				if (evh->eventToObserve->argument1 == nullptr &&  v_call->noum1 != nullptr) continue;
				if (evh->eventToObserve->argument1 != nullptr &&  v_call->noum1 == nullptr) continue;
				if (evh->eventToObserve->argument2 == nullptr &&  v_call->noum2 != nullptr) continue;
				if (evh->eventToObserve->argument2 != nullptr &&  v_call->noum2 == nullptr) continue;

				HRunLocalScope next_vars = nullptr;
				if (evh->eventToObserve->argument1 != nullptr)
				{
					auto r1 = Match(evh->eventToObserve->argument1, v_call->noum1, localsEntry, stk);
					if (r1.hasMatch == false) continue;
					  next_vars = std::make_shared< CRunLocalScope >(r1.maptch);
					  HRunLocalScope tmp_vars = newScope(localsEntry, next_vars);
					  next_vars = tmp_vars;
				}

				
				if (evh->eventToObserve->argument2 != nullptr)
				{
					auto r2 = Match(evh->eventToObserve->argument2, v_call->noum2, next_vars, stk); //observe que os valores ja estao sendo usados
					if (r2.hasMatch == false) continue;
					auto next_vars_2 = std::make_shared< CRunLocalScope >(r2.maptch);
					HRunLocalScope tmp_vars = newScope(next_vars, next_vars_2);
					next_vars = tmp_vars; 
				}

				//next vars contem as variaveis 
				PhaseResult  rx =  this->execute_now(evh->body, next_vars, stk);
			  
				if (rx.hasExecuted)
				{					 
					return rx;
				}
			}


		}
	}

	return PhaseResult(true); ;
}



PhaseResult CBlockInterpreter::execute_phase_carryOut(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{
	for (auto evh : event_handles)
	{
		if (evh->stage == StageCarryOut)
		{
			auto rx = execute_phase_any(evh, v_call, localsEntry, stk);
			if (rx.result)
			{
				if (HBlockExecutionResultFlag  flag = asHBlockExecutionResultFlag(rx.result))
				{
					if (flag->flag == actionStop)
					{
						return rx;
					}
				}
			}
		}
	}

	return PhaseResult(false);
}



PhaseResult CBlockInterpreter::execute_system_action(HBlockActionCall v_call)
{
	 

	if (v_call->action->named == "say_text")
	{
		if (HBlockText  ntext = asHBlockText(v_call->noum1))
		{
			printf("root$ %s \n", ntext->contents.c_str());
			return PhaseResult(true);;
		}
	}
	if (v_call->action->named == "say")
	{
		if (HBlockText  ntext = asHBlockText(v_call->noum1))
		{
			printf("root$ %s \n", ntext->contents.c_str());
			return PhaseResult(true);;
		}
	}

	return PhaseResult(false);;
}
 

PhaseResult CBlockInterpreter::execute_user_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack stk)
{
	 
	 
	 

	//verifica se os objetos da acao estao condicentes com os requeimentos
	for (auto &ah : actions_header)
	{
		if (ah->named == v_call->action->named)
		{
		//	ah->dump(" ");
		}
	}
	 
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
				QueryResultContext qarg1 = query_is(v_call->noum1, ap.second->applyTo->noum1, localsEntry, stk);
				if (qarg1.result != QEquals) continue; 
			}


			if (v_call->noum2 != nullptr)
			{
				QueryResultContext qarg2 = query_is(v_call->noum2, ap.second->applyTo->noum2, localsEntry, stk);
				if (qarg2.result != QEquals) continue;
			}


			kaction = ap.second;
			break;
		}

	}
	if (kaction == nullptr) {
		return PhaseResult(false);;
	}
	
	


 
	//Para executar a acao devo ir  na ordem

	//Check
	PhaseResult res_ck = execute_phase_check(v_call, localsEntry, stk);
	if (HBlockExecutionResultFlag  flag_ck = asHBlockExecutionResultFlag(res_ck.result))
	{
		if (flag_ck->flag == actionStop)
		{
			return res_ck;
		}
	}


	//Before
	PhaseResult res_before =  execute_phase_before(v_call, localsEntry, stk);
	if (HBlockExecutionResultFlag  flag_bf = asHBlockExecutionResultFlag(res_before.result))
	{
		if (flag_bf->flag == actionStop)
		{
			return res_before;
		}
	}

	//Instead

	

	//Daqui para  frente a acao eh sucesso 

	//CarryOut
	PhaseResult res_carryOut = execute_phase_carryOut(v_call, localsEntry, stk);
	if (HBlockExecutionResultFlag  flag_co = asHBlockExecutionResultFlag(res_carryOut.result))
	{
		if (flag_co->flag == actionStop)
		{
			return res_carryOut;
		}
	}


	//After

	//Report

	return PhaseResult(true);
}