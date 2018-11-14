// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


//Executor de acoes 


#include "CResultMatch.hpp"

 
#include "CBlockScope.hpp"
#include "interpreter/QueryStack.hpp"

#include "interpreter/CBlockInterpreterRuntime.hpp"
#include <iostream>
#include "sharedCast.hpp"
#include "PhaseResult_init.h"

using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
using namespace EqualResulting;


HRunLocalScope CBlockInterpreter::match_phase_direct_args(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockActionCallNamed call_named = asHBlockActionCallNamed(v_call))
	{

		QueryResultContext qAction = query_is(call_named->action, evh->eventToObserve->action, localsEntry, stk);

		if (qAction.result == QEquals)
		{
			QueryResul qarg1 = QEquals;
			QueryResul qarg2 = QEquals;

			if (evh->eventToObserve->argument1 == nullptr &&  v_call->noum1 != nullptr) return nullptr;
			if (evh->eventToObserve->argument1 != nullptr &&  v_call->noum1 == nullptr) return nullptr;
			if (evh->eventToObserve->argument2 == nullptr &&  v_call->noum2 != nullptr) return nullptr;
			if (evh->eventToObserve->argument2 != nullptr &&  v_call->noum2 == nullptr) return nullptr;

			HRunLocalScope next_vars = nullptr;
			HRunLocalScope next_vars_2 = nullptr;
			if (evh->eventToObserve->argument1 != nullptr)
			{
				auto r1 = Match(evh->eventToObserve->argument1, v_call->noum1, localsEntry, stk);
				if (r1.hasMatch == false)
				{
					return   nullptr;
				}
				next_vars = std::make_shared< CRunLocalScope >(localsEntry, r1.maptch);
				next_vars_2 = next_vars;
			}


			if (evh->eventToObserve->argument2 != nullptr)
			{
				auto r2 = Match(evh->eventToObserve->argument2, v_call->noum2, next_vars, stk); //observe que os valores ja estao sendo usados
				if (r2.hasMatch == false)
				{
					return   nullptr;
				}
				next_vars_2 = std::make_shared< CRunLocalScope >(next_vars, r2.maptch);

			}

			//next vars contem as variaveis 
			return next_vars_2; 
		}
	}
	return nullptr;

}


HRunLocalScope CBlockInterpreter::match_phase_indirect_args(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockActionCallNamed call_named = asHBlockActionCallNamed(v_call))
	{

		QueryResultContext qAction = query_is(call_named->action, evh->eventToObserve->action, localsEntry, stk);

		if (qAction.result == QEquals)
		{
			QueryResul qarg1 = QEquals;
			QueryResul qarg2 = QEquals;

			if ((evh->eventToObserve->argument1 == nullptr) && (evh->eventToObserve->argument2 == nullptr))
			{
			std:map<string, HBlock> arguments;
				arguments["noum"] = v_call->noum1;
				arguments["second noum"] = v_call->noum2;
				HRunLocalScope next_vars = std::make_shared< CRunLocalScope >(localsEntry, arguments);

				return next_vars;

				 
			}
		}
	}

	return nullptr;

}


PhaseResult CBlockInterpreter::execute_phase_any_direct_args(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{


	HRunLocalScope next_vars = match_phase_direct_args(evh, v_call, localsEntry, stk);
	if (next_vars != nullptr)
	{
		PhaseResult  rx = this->execute_now(evh->body, next_vars, stk);
		if (rx.hasExecuted)
		{
			return rx;
		}
	}
	return PhaseResult(false);



	//if (HBlockActionCallNamed call_named = asHBlockActionCallNamed(v_call))
	//{

	//	QueryResultContext qAction = query_is(call_named->action, evh->eventToObserve->action, localsEntry, stk);

	//	if (qAction.result == QEquals)
	//	{
	//		QueryResul qarg1 = QEquals;
	//		QueryResul qarg2 = QEquals;

	//		if (evh->eventToObserve->argument1 == nullptr &&  v_call->noum1 != nullptr) return PhaseResult(false);
	//		if (evh->eventToObserve->argument1 != nullptr &&  v_call->noum1 == nullptr) return PhaseResult(false);
	//		if (evh->eventToObserve->argument2 == nullptr &&  v_call->noum2 != nullptr) return PhaseResult(false);
	//		if (evh->eventToObserve->argument2 != nullptr &&  v_call->noum2 == nullptr) return PhaseResult(false);

	//		HRunLocalScope next_vars = nullptr;
	//		HRunLocalScope next_vars_2 = nullptr;
	//		if (evh->eventToObserve->argument1 != nullptr)
	//		{
	//			auto r1 = Match(evh->eventToObserve->argument1, v_call->noum1, localsEntry, stk);
	//			if (r1.hasMatch == false)
	//			{
	//				return PhaseResult(false); ;
	//			}
	//			next_vars = std::make_shared< CRunLocalScope >(localsEntry, r1.maptch);
	//			next_vars_2 = next_vars;
	//		}


	//		if (evh->eventToObserve->argument2 != nullptr)
	//		{
	//			auto r2 = Match(evh->eventToObserve->argument2, v_call->noum2, next_vars, stk); //observe que os valores ja estao sendo usados
	//			if (r2.hasMatch == false)
	//			{
	//				return PhaseResult(false);
	//			}
	//			next_vars_2 = std::make_shared< CRunLocalScope >(next_vars, r2.maptch);

	//		}

	//		//next vars contem as variaveis 

	//		PhaseResult  rx = this->execute_now(evh->body, next_vars_2, stk);

	//		if (rx.hasExecuted)
	//		{
	//			return rx;
	//		}
	//	}
	//}

	//return PhaseResult(false);
}

PhaseResult CBlockInterpreter::execute_phase_any_indirect_args(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	HRunLocalScope next_vars = match_phase_indirect_args(evh, v_call, localsEntry, stk);
	if (next_vars != nullptr)
	{ 
		PhaseResult  rx = this->execute_now(evh->body, next_vars, stk);
		if (rx.hasExecuted)
		{
			return rx;
		}
	}
	return PhaseResult(false);

	//if (HBlockActionCallNamed call_named = asHBlockActionCallNamed(v_call))
	//{

	//	QueryResultContext qAction = query_is(call_named->action, evh->eventToObserve->action, localsEntry, stk);

	//	if (qAction.result == QEquals)
	//	{
	//		QueryResul qarg1 = QEquals;
	//		QueryResul qarg2 = QEquals;

	//		if ((evh->eventToObserve->argument1 == nullptr) && (evh->eventToObserve->argument2 == nullptr))
	//		{ 
	//		    std:map<string, HBlock> arguments;
	//			arguments["noum"] = v_call->noum1;
	//			arguments["second noum"] = v_call->noum2;
	//			HRunLocalScope next_vars = std::make_shared< CRunLocalScope >(localsEntry, arguments); 



	//			PhaseResult  rx = this->execute_now(evh->body, next_vars, stk); 
	//			if (rx.hasExecuted)
	//			{
	//				return rx;
	//			}
	//		}
	//	}
	//}

	//return PhaseResult(false);

}

PhaseResult CBlockInterpreter::execute_phase_any(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{

	// Match com  argumentos definidos
	PhaseResult r1 = execute_phase_any_direct_args(evh, v_call, localsEntry, stk);
	if (r1.hasExecuted == true) return r1;

	//Match sem argumentos .. repasse como Noum e second Noum
	PhaseResult r2 =  execute_phase_any_indirect_args(evh, v_call, localsEntry, stk);
	if (r2.hasExecuted == true) return r2; 

	return PhaseResult(false); 
}

	
PhaseResult CBlockInterpreter::execute_phase_any_system( HBlockEventHandle  evh, InternalActionHandle func_call, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	HRunLocalScope next_vars = match_phase_direct_args(evh , v_call, localsEntry, stk);
	if (next_vars != nullptr)
	{
		PhaseResult  rx = func_call(next_vars, stk);
		if (rx.hasExecuted)
		{
			return rx;
		}
	}
	return PhaseResult(false);

 
}



 
PhaseResult CBlockInterpreter::execute_phase_check(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{


	for (auto evh : system_event_handles)
	{
		if (evh.first->stage == StageCheck)
		{
			auto rx = execute_phase_any_system(evh.first, evh.second, v_call, localsEntry, stk);
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


PhaseResult CBlockInterpreter::execute_phase_before(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	// busca por algum before que eh compativel com esta regra e aplica ela
	for(auto evh : event_handles)
	{
		if (evh->stage == StageBefore)
		{

			if (HBlockActionCallNamed call_named = asHBlockActionCallNamed(v_call))
			{

				QueryResultContext qAction = query_is(call_named->action, evh->eventToObserve->action, localsEntry, stk);
				if (qAction.result == QEquals)
				{
					 
					QueryResul qarg1 = QEquals;
					QueryResul qarg2 = QEquals;

					if (evh->eventToObserve->argument1 == nullptr &&  call_named->noum1 != nullptr) continue;
					if (evh->eventToObserve->argument1 != nullptr &&  call_named->noum1 == nullptr) continue;
					if (evh->eventToObserve->argument2 == nullptr &&  call_named->noum2 != nullptr) continue;
					if (evh->eventToObserve->argument2 != nullptr &&  call_named->noum2 == nullptr) continue;

					HRunLocalScope next_vars = nullptr;
					HRunLocalScope next_vars_2 = nullptr;

					if (evh->eventToObserve->argument1 != nullptr)
					{
						auto r1 = Match(evh->eventToObserve->argument1, call_named->noum1, localsEntry, stk);
						if (r1.hasMatch == false) continue;
						next_vars = std::make_shared< CRunLocalScope >(localsEntry, r1.maptch);
						next_vars_2 = nullptr;
					}


					if (evh->eventToObserve->argument2 != nullptr)
					{
						auto r2 = Match(evh->eventToObserve->argument2, call_named->noum2, next_vars, stk); //observe que os valores ja estao sendo usados
						if (r2.hasMatch == false) continue;
						next_vars_2 = std::make_shared< CRunLocalScope >(next_vars, r2.maptch);

					}

					//next vars contem as variaveis 
					PhaseResult  rx = this->execute_now(evh->body, next_vars_2, stk);

					if (rx.hasExecuted)
					{
						return rx;
					}
				}


			}
		}
	}

	return PhaseResult(true); ;
}



PhaseResult CBlockInterpreter::execute_phase_carryOut(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
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




PhaseResult CBlockInterpreter::execute_system_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
 

	if (HBlockActionCallNamed  v_calln = asHBlockActionCallNamed(v_call))
	{
	 
		 
		if (v_calln->action->named == "say_text" || v_calln->action->named == "say")
		{
			 
			if (HBlockTextSentence ntexts = asHBlockTextSentence(v_call->noum1))
			{
				 auto resolved_text = adapt_text(ntexts, localsEntry, stk);
				 if (say_output)
				 {
					 say_output(resolved_text->contents.c_str());
				 }
				 else
				 {
					 printf("root$ %s \n", resolved_text->contents.c_str());
				 }
				 return PhaseResult(true);;

			}
			if (HBlockText  ntext = asHBlockText(v_call->noum1))
			{
				//printf("root$ %s \n", ntext->contents.c_str());
				if (say_output)
				{
					say_output(ntext->contents.c_str());
				}
				else
				{
					printf("root$ %s \n", ntext->contents.c_str());
				}
				return PhaseResult(true);;
			}
			return PhaseResult(false);
		}
		 
	}
	return PhaseResult(false);



	//if (v_call->action->named == "say_text")
	//{
	//	v_call->dump("");

	//	if (HBlockText  ntext = asHBlockText(v_call->noum1))
	//	{
	//		printf("root$ %s \n", ntext->contents.c_str());
	//		return PhaseResult(true);;
	//	}
	//	//printf("root$ something ??? \n");
	//	v_call->dump("");
	//	//printf("...................\n");
	//	return PhaseResult(true);;
	//}

	//if (v_call->action->named == "say")
	//{
	//	if (HBlockText  ntext = asHBlockText(v_call->noum1))
	//	{
	//		printf("root$ %s \n", ntext->contents.c_str());
	//		return PhaseResult(true);;
	//	}
	//	return PhaseResult(false);;
	//}

	//return PhaseResult(false);;
}
 
PhaseResult CBlockInterpreter::execute_user_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	if ( HBlockActionCallNamed c = asHBlockActionCallNamed(v_call))
	{
		return execute_user_action(c,   localsEntry,   stk);
	}
	return PhaseResult(false);;

}

HBlockActionCallNamed CBlockInterpreter::replaceByUndestandAction(HBlockActionCallNamed v_call, HRunLocalScope localsEntry, QueryStack *stk)
{
	for (auto d : dynamic_understand)
	{
		//d->dump(">");
		//v_call->dump("");
	}

	return v_call;
}


PhaseResult CBlockInterpreter::execute_user_action(HBlockActionCallNamed v_call_in, HRunLocalScope localsEntry, QueryStack *stk)
{ 
	//verifica se os objetos da acao estao condicentes com os requeimentos
 
	auto v_call = replaceByUndestandAction(v_call_in, localsEntry, stk);
	HBlockKindAction kaction = nullptr;
	HBlockActionInstance iaction = nullptr;

	//determina qual action corresponde a esse nome e esses parametros
	for (auto &ap : actions_definitions)
	{
        
		if (ap->named == v_call->action->named)
		{
			auto action_kind = ap->get_base();
			if (v_call->noum1 == nullptr  && action_kind->applyTo->noum1 != nullptr) continue;
			if (v_call->noum2 == nullptr  && action_kind->applyTo->noum2 != nullptr) continue;
			if (v_call->noum1 != nullptr  && action_kind->applyTo->noum1 == nullptr) continue;
			if (v_call->noum2 != nullptr  && action_kind->applyTo->noum2 == nullptr) continue;


			//verifica se os argumentos sao compativeis

			if (v_call->noum1 != nullptr)
			{
				QueryResultContext qarg1 = query_is(v_call->noum1, action_kind->applyTo->noum1, localsEntry, stk);
				if (qarg1.result != QEquals) continue; 
			}


			if (v_call->noum2 != nullptr)
			{
				QueryResultContext qarg2 = query_is(v_call->noum2, action_kind->applyTo->noum2, localsEntry, stk);
				if (qarg2.result != QEquals) continue;
			}


			kaction = ap->actionKind;
			break;
		}

	}
	if (kaction == nullptr) {
		return PhaseResult(false);;
	}
	
	

	printf("Action Called %s \n", v_call->action->named.c_str());
 
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
