
//Executor de acoes 

#include "CBlockInterpreterRuntime.h"
#include "CResultMatch.h"
#include <memory>
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

HBlock CBlockInterpreter::find_dispach_object(HBlockList  p)
{
	for (auto &d : dynamic_understand)
	{
		 //if (Match( d->input_n , p ))
		 {
			 
		 }
	}
	return nullptr;
}

bool CBlockInterpreter::execute_now(HBlock p)
{	 

	if (HBlockAssertion_is vk = dynamic_pointer_cast<CBlockAssertion_is>(p)) {
		HBlock obj = vk->get_obj();
		HBlock value = vk->get_definition();
		execute_set(obj, value);
	}


	if (HBlockDinamicDispatch  vdyn = dynamic_pointer_cast<CBlockDinamicDispatch>(p)) 
	{
		//determina quem eh o action do dynamica dispatch

		HBlock disp =  find_dispach_object(vdyn->commandList);
		

		return true;
	}


	return false;

}