
//Executor de acoes 

#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <memory>
#include <iostream>
#include "CBlockScope.h"
#include "QueryStack.h"
using namespace std;


bool CBlockInterpreter::execute_set(HBlock obj, HBlock value,  HRunLocalScope localsEntry)
{
	if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
		HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_it_Value(nobj, value,localsEntry);

		}

	}

	// value tem que ser uma instancia, propriedade ou variavel

	if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
		if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
			HBlock nobj = resolve_noum(nbase,localsEntry);
			if (nobj == nullptr)
			{
				nInst->set(nbase);
				return true;
			}
		}
	}
	if (HBlockProperty prop_n = dynamic_pointer_cast<CBlockProperty>(obj)) {
		HBlock propNamed = prop_n->prop;
		HBlock destination = prop_n->obj;
		return assert_it_property(propNamed, destination, value,localsEntry);
	}

	//
	if (HVariableNamed  var_n = dynamic_pointer_cast<CVariableNamed>(obj)) {

		HBlock destination = var_n->value;
		if (value_can_be_assign_to(value, var_n->kind,localsEntry))
		{
			if (HBlockList   val_list = dynamic_pointer_cast<CBlockList>(value))
			{
				//list is passed as copy
				HBlockList lcopy = make_shared<CBlockList>();
				lcopy->lista = val_list->lista;
				var_n->value = lcopy;

			}
			else {
				var_n->value = value;
			}
			return true;
		}
		 
	}


	return false;
}

HBlock CBlockInterpreter::exec_eval_property_value_imp(HBlock propname, HBlock propObj )
{
	if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(propObj)) 
	{
		if (HBlockNoum property_noum = dynamic_pointer_cast<CBlockNoum>(propname)) 
		{
			HVariableNamed pvar = cinst->get_property(property_noum->named);
			if (pvar != nullptr) {
				cout << "property  is " << endl;
				if (pvar->value != nullptr)
				{
					return pvar->value;
				}
				else
				{
					cout << "     EMPTY" << endl;
					return pvar->value;
				}
			}
		}
	}
	return nullptr;
}

HBlock CBlockInterpreter::exec_eval_property_value(HBlock c_block, HRunLocalScope localsEntry) {
	if (HBlockProperty cproperty = dynamic_pointer_cast<CBlockProperty>(c_block)) 
	{
		if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(cproperty->obj)) 
		{
			auto resolved = resolve_noum(cnn,localsEntry);
			if (resolved != nullptr) {
				return exec_eval_property_value_imp(cproperty->prop, resolved );
			}			 

		}
		
	
		return exec_eval_property_value_imp(cproperty->prop, cproperty->obj );
	}
	return nullptr;

}



HBlock  CBlockInterpreter::exec_eval_assertations(HBlock c_block ,  HRunLocalScope localsEntry, std::function< HBlock(HBlock) > is_accetable )
{
	// is_accetable recebe um block, terona true se pode parar de descer na arvore
	QueryStack stk = QueryStack( );

	for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		if (HBlockAssertion_is qdef = dynamic_pointer_cast<CBlockAssertion_is>(*it)) 		
		{
			if (query_is_same(c_block, qdef->get_obj(), localsEntry, stk) == QEquals) 
			{				
			HBlock br = (is_accetable(qdef->get_definition()));
			if (br !=nullptr)
			  {
				  return br ;
			  }
			}
		}
	}


	HBlock qprop_value = exec_eval_property_value(c_block ,localsEntry);
	HBlock qbr = is_accetable(qprop_value);
	if (qbr != nullptr)
	{
		return qbr;
	}

	return nullptr;
}


HBlock CBlockInterpreter::exec_eval(HBlock c_block, HRunLocalScope localsEntry)
{

		if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(c_block))
		{
			auto  obj = resolve_noum(nn,localsEntry);
			return  exec_eval(obj , localsEntry);
		}

		if (HBlockInstance nIns = dynamic_pointer_cast<CBlockInstance>(c_block))
		{
			return nIns;
		}

		if (HBlockKind kIns = dynamic_pointer_cast<CBlockKind>(c_block))
		{
			return kIns;
		}

		if (auto  kvar= dynamic_pointer_cast<CVariableNamed >(c_block))
		{
			return kvar->value ;
		}

		

		if (auto  kprop = dynamic_pointer_cast<CBlockProperty >(c_block))
		{
			auto instancia = exec_eval(kprop->obj, localsEntry);
			if (HBlockInstance objInst = dynamic_pointer_cast<CBlockInstance>(instancia))
				if (HBlockNoum propNoum = dynamic_pointer_cast<CBlockNoum>(kprop->prop))
				{
					HVariableNamed pvar = objInst->get_property(propNoum->named);
					return pvar->value;
				}
			return nullptr;
		}

		if (HBlockNamedValue nvalue = dynamic_pointer_cast<CBlockNamedValue>(c_block))
		{
			return nvalue;
		}

		if (auto  kList = dynamic_pointer_cast<CBlockList  >(c_block))
		{
			auto rList = std::make_shared<CBlockList>( );
			for(auto &e : kList->lista)
			{
				rList->lista.push_back(exec_eval(e,localsEntry));
			}
			return rList;
		}

		// Bla ! 
		return nullptr;
}


HBlock CBlockInterpreter::resolve_as_callCommand(HBlock p, HRunLocalScope localsEntry)
{
 

	//Execution block is not an action ??
	if (HBlockNoum noumCall = dynamic_pointer_cast<CBlockNoum>(p))
	{
		auto callAs = resolve_noum(noumCall, localsEntry);
		if (callAs != nullptr)
		{
			return  resolve_as_callCommand(callAs, localsEntry);
		}
	}

	if (HBlockAction actionCall = dynamic_pointer_cast<CBlockAction>(p))
	{
		return actionCall;
	}

	if (HVariableNamed callAsVar = dynamic_pointer_cast<CVariableNamed>(p))
	{
		auto actionCall_1 = callAsVar->value;
		return  resolve_as_callCommand(actionCall_1, localsEntry);
	}
	

	return nullptr;
}

HExecutionBlock CBlockInterpreter::create_dispach_env(HBlockList  p, HRunLocalScope localsEntry)
{
	QueryStack stk;
	for (auto &d : dynamic_understand)
	{
		auto result = (Match(d->input_n, p, stk));
		if (result.hasMatch)
		 {
			 cout << "Dispatch " << endl;
			 d->output_n->dump("            ");


			 // Forma eh esta 
			 for(auto &arg : result.maptch)
			 {
				 cout << "      Arg "<< arg.first  << "==" <<  endl;
				 arg.second->dump("                          ");
			 }
			 HRunLocalScope localsNext = make_shared< CRunLocalScope >();
			 // Argumentos batem com os matchs dos argumentos ??
			 HBlock ref_Arg_1 = nullptr;
			 HBlock ref_Arg_2 = nullptr;

			 if (d->argument_n->matchList.size() > 0)
			 {
				 auto arg_header_first = d->argument_n->matchList.begin();
				 // eh um Match Named ???
				 if (HBlockMatchNamed arg1_named = dynamic_pointer_cast<CBlockMatchNamed>(*arg_header_first))
				 {
					 cout << " named " << arg1_named->named  << " == " <<  endl;

					 result.maptch["noum1"]->dump("               ");					 
				     auto obj_resolved = exec_eval (result.maptch["noum1"], localsEntry);

					 auto result_arg1 = Match(arg1_named->matchInner, obj_resolved, stk);
					 if (result_arg1.hasMatch == true)
					 {
						 localsNext->locals.push_back(std::pair<string, HBlock>(arg1_named->named, obj_resolved));
						 ref_Arg_1 = obj_resolved;
					 }
					 else
					 {
						 continue; //Este match nao serve .. Proximo
					 }
				 } 



				 if (d->argument_n->matchList.size() > 1)
				 {
					 auto arg_header_second = std::next( arg_header_first);
					 // eh um Match Named ???
					 if (HBlockMatchNamed arg2_named = dynamic_pointer_cast<CBlockMatchNamed>(*arg_header_second))
					 {
						 cout << " named " << arg2_named->named << " == " << endl;
						 result.maptch["noum2"]->dump("               ");

						 auto obj_resolved = exec_eval(result.maptch["noum2"], localsEntry);
						 auto result_arg2 = Match(arg2_named->matchInner, obj_resolved, stk);
						 if (result_arg2.hasMatch == true)
						 {
							 localsNext->locals.push_back(std::pair<string, HBlock>(arg2_named->named, obj_resolved));
							 ref_Arg_2 = obj_resolved;
						 }
						 else
						 {
							 continue; //Este match nao serve .. Proximo
						 }

						 
					 }

				 }
			 }

			 
			 auto output_block =  resolve_as_callCommand(d->output_n, localsEntry); 


			 if (HBlockAction actionCall = dynamic_pointer_cast<CBlockAction >(output_block))
			 {
				return  make_shared< CExecutionBlock >(make_shared< CRunLocalScope >() , std::make_shared<CBlockActionCall>(actionCall, ref_Arg_1 , ref_Arg_2));
			 } 

			 HExecutionBlock executionBlock = make_shared< CExecutionBlock >(localsNext, output_block);
			 return executionBlock;

		 }
	}

	return nullptr;
}

bool CBlockInterpreter::execute_now(HBlock p) //executa STMT
{
	HRunLocalScope localsEntry = make_shared< CRunLocalScope >();
	auto b =   execute_now(p, localsEntry);
	if (b == false) cout << "fail to execute ";
	return b;
}


bool CBlockInterpreter::execute_now(HBlock p , HRunLocalScope localsEntry ) //executa STMT
{	 

	 


	if (HBlockAssertion_is vk = dynamic_pointer_cast<CBlockAssertion_is>(p)) {
		HBlock obj = vk->get_obj();
		HBlock value = vk->get_definition();
		execute_set(obj, value,localsEntry);
	}


	if (HBlockDinamicDispatch  vdyn = dynamic_pointer_cast<CBlockDinamicDispatch>(p)) 
	{
		//determina quem eh o action do dynamica dispatch
		HExecutionBlock dispExec = create_dispach_env(vdyn->commandList, localsEntry);
		if (dispExec != nullptr)
		{
			cout << "EXEC     " << " == " << endl;
			dispExec->dump("        ");
			return execute_now(dispExec->block , dispExec->locals);
		}
	}

	if (HBlockActionCall  vCall = dynamic_pointer_cast<CBlockActionCall >(p))
	{		 
		 
		{
			cout << "CALL     " << vCall->action <<  endl;		
			if (execute_system_action(vCall)) return true;
			if (execute_user_action(vCall)) return true;
			return false;
		}
	}

	


	return false;

}