
//Executor de acoes 

#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <memory>
#include <iostream>
#include "CBlockScope.h"
#include "QueryStack.h"
using namespace std;


bool CBlockInterpreter::execute_set(HBlock obj, HBlock value)
{
	if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
		HBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr) {
			return assert_it_Value(nobj, value);

		}

	}

	// value tem que ser uma instancia, propriedade ou variavel

	if (HBlockInstance nInst = dynamic_pointer_cast<CBlockInstance>(obj)) {
		if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(value)) {
			HBlock nobj = resolve_noum(nbase);
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
		return assert_it_property(propNamed, destination, value);
	}

	//
	if (HVariableNamed  var_n = dynamic_pointer_cast<CVariableNamed>(obj)) {

		HBlock destination = var_n->value;
		if (value_can_be_assign_to(value, var_n->kind))
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

HBlock CBlockInterpreter::exec_eval_property_value(HBlock c_block  ) {
	if (HBlockProperty cproperty = dynamic_pointer_cast<CBlockProperty>(c_block)) 
	{
		if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(cproperty->obj)) 
		{
			auto resolved = resolve_noum(cnn);
			if (resolved != nullptr) {
				return exec_eval_property_value_imp(cproperty->prop, resolved );
			}			 

		}
		
	
		return exec_eval_property_value_imp(cproperty->prop, cproperty->obj );
	}
	return nullptr;

}



HBlock  CBlockInterpreter::exec_eval_assertations(HBlock c_block , std::function< HBlock(HBlock) > is_accetable )
{
	// is_accetable recebe um block, terona true se pode parar de descer na arvore
	QueryStack stk = QueryStack( );

	for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		if (HBlockAssertion_is qdef = dynamic_pointer_cast<CBlockAssertion_is>(*it)) 		
		{
			if (query_is_same(c_block, qdef->get_obj(), stk) == QEquals) 
			{				
			HBlock br = (is_accetable(qdef->get_definition()));
			if (br !=nullptr)
			  {
				  return br ;
			  }
			}
		}
	}


	HBlock qprop_value = exec_eval_property_value(c_block );
	HBlock qbr = is_accetable(qprop_value);
	if (qbr != nullptr)
	{
		return qbr;
	}

	return nullptr;
}


HBlock CBlockInterpreter::exec_eval(HBlock c_block)
{

		if (HBlockNoum nn = dynamic_pointer_cast<CBlockNoum>(c_block))
		{
			auto  obj = resolve_noum(nn);
			return  exec_eval(obj);
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
				rList->lista.push_back(exec_eval(e));
			}
			return rList;
		}

		// Bla ! 
		return nullptr;
}

HExecutionBlock CBlockInterpreter::create_dispach_env(HBlockList  p)
{
	for (auto &d : dynamic_understand)
	{
		auto result = (Match(d->input_n, p));
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
			 HRunLocalScope localsEntry = make_shared< CRunLocalScope >();
			 // Argumentos batem com os matchs dos argumentos ??

			 if (d->argument_n->matchList.size() > 0)
			 {
				 auto arg_header_first = d->argument_n->matchList.begin();
				 // eh um Match Named ???
				 if (HBlockMatchNamed arg1_named = dynamic_pointer_cast<CBlockMatchNamed>(*arg_header_first))
				 {
					 cout << " named " << arg1_named->named  << " == " <<  endl;
					 result.maptch["noum1"]->dump("               ");
					 
					 auto obj_resolved = exec_eval (result.maptch["noum1"]);
						 localsEntry->locals.push_back(std::pair<string, HBlock>( arg1_named->named , obj_resolved));
					 
				 } 

				 if (d->argument_n->matchList.size() > 1)
				 {
					 auto arg_header_second = std::next( arg_header_first);
					 // eh um Match Named ???
					 if (HBlockMatchNamed arg2_named = dynamic_pointer_cast<CBlockMatchNamed>(*arg_header_second))
					 {
						 cout << " named " << arg2_named->named << " == " << endl;
						 result.maptch["noum2"]->dump("               ");

						 auto obj_resolved = exec_eval(result.maptch["noum2"]);
						 localsEntry->locals.push_back(std::pair<string, HBlock>(arg2_named->named, obj_resolved));
					 }

				 }
			 }

			 HExecutionBlock executionBlock = make_shared< CExecutionBlock >(localsEntry , d->output_n);
			 return executionBlock;

		 }
	}
	return nullptr;
}

bool CBlockInterpreter::execute_now(HBlock p) //executa STMT
{	 

	if (HBlockAssertion_is vk = dynamic_pointer_cast<CBlockAssertion_is>(p)) {
		HBlock obj = vk->get_obj();
		HBlock value = vk->get_definition();
		execute_set(obj, value);
	}


	if (HBlockDinamicDispatch  vdyn = dynamic_pointer_cast<CBlockDinamicDispatch>(p)) 
	{
		//determina quem eh o action do dynamica dispatch

		HExecutionBlock dispExec = create_dispach_env(vdyn->commandList);
		cout << "EXEC     "  << " == " << endl;
		dispExec->dump("        ");

		return true;
	}


	return false;

}