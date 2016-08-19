
#include "CBlockInterpreterRuntime.h"
#include <iostream>
using namespace std;


void CBlockInterpreter::initialize()
{
	for(auto &p : program)
	{
		execute_init(p);
	}

}

bool CBlockInterpreter::assert_it_canBe(UBlock c_block, CBlockEnums* value)
{
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(c_block))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_it_canBe(nobj, value);
		}
		return false;
	}
	else if (CBlockKind * nkind = dynamic_cast<CBlockKind*>(c_block))
	{
		kind_variables.push_back(new CBlockAssertion_canBe(nkind, value));
		return true;
	}
	else if (CBlockInstance * nInst = dynamic_cast<CBlockInstance*>(c_block))
	{
		auto p = new CBlockAssertion_canBe(nInst, value);
		assign_variable_to_instance(new CBlockAssertion_canBe(nInst, value));
		delete p;
		return true;
	}

	return true;
}

bool CBlockInterpreter::assert_it_valuesDefinitions(UBlock c_block, UBlock value)
{
	// Value Kind , is , list of Noums 

	if (CBlockList  * vlist = dynamic_cast<CBlockList*>(value)) // segundo argumento eh uma lista
		if (CBlockNoum   * nn = dynamic_cast<CBlockNoum*>(c_block)) //primeiro eh um noum
		{
			// nn eh um value Kind ??
			UBlock nobj = resolve_noum(nn); 
			if (CBlockKind   *nkind = dynamic_cast<CBlockKind*>(nobj)) //mas na verdade o primeiro eh um kind ja definido
			{
				for( auto &v : vlist->lista )
				{
					assert_it_instance(v, nkind);
				}
				return true;
			}

		}
	return false;
}

void CBlockInterpreter::execute_init(UBlock p)
{
 
	if (CBlockAssertion_isNotDirectAssign  * v = dynamic_cast<CBlockAssertion_isNotDirectAssign*>(p))
	{
		UBlock obj = v->get_obj();
		UBlock value = v->get_definition();
		if (assert_it_not_Value(obj, value)) return;
	}

	if (CBlockAssertion_isDefaultAssign * v = dynamic_cast<CBlockAssertion_isDefaultAssign*>(p))
	{
		UBlock obj = v->get_obj();
		UBlock value = v->get_definition();
		if (assert_it_defaultValue(obj, value)) return;
	}

	else if (CBlockAssertion_canBe * vee = dynamic_cast<CBlockAssertion_canBe*>(p))
	{
		UBlock obj = vee->get_obj();
		CBlockEnums* evalue = vee->definition;
		if (assert_it_canBe(obj, evalue)) return;
	}

	else if (CBlockAssertion_is * vk = dynamic_cast<CBlockAssertion_is*>(p))
	{
		UBlock obj = vk->get_obj();
		UBlock value = vk->get_definition();
		//Static Definition de uma instancia derivado
	 	if (assert_it_Value(obj, value)) return;
		if (assert_it_kind(obj, value)) return;
		if (assert_it_instance(obj, value)) return;		 
		if (assert_it_valuesDefinitions(obj, value)) return;

		throw "undefined block";
	}
	else if (CBlockAssertion_InstanceVariable * ivar = dynamic_cast<CBlockAssertion_InstanceVariable*>(p))
	{
		UBlock obj = ivar->noum  ;
		UBlock value = ivar->instance_variable ;
		if (assert_has_variable(obj, value)) return;
	}
	 

	std::cout << "not found block definition " <<   endl;
	return  ;
}



 
bool CBlockInterpreter::assert_has_variable(UBlock obj, UBlock value)
{
	
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_has_variable(nobj, value);
		}
		return false;
	}

	if (CBlockInstance * nInst = dynamic_cast<CBlockInstance*>(obj))
	{
		//name da variavel 
		if (CBlockInstanceVariable * variable_ = dynamic_cast<CBlockInstanceVariable*>(value))
		{		  
			CBlockKind* nkindBase = resolve_kind (variable_->kind_name->named );			 
			nInst->newNamedVariable(variable_->property_name , nkindBase);
			return true;
		}
		   
	}
	else if (CBlockKind * nKind = dynamic_cast<CBlockKind*>(obj))
	{		
		return true;
	}
	return false;
}


//Forca value a ser Kind
UBlock CBlockInterpreter::value_can_be_assign_to(UBlock value, CBlockKind* kind)
{
	if (value == nullptr) return nullptr;


	if (CBlockEnums* enumarate = dynamic_cast<CBlockEnums  *>(kind))
	{
		// Acha todas as instancias

	}

	if (CBlockNoum* cnn = dynamic_cast<CBlockNoum *>(value))
	{
		UBlock resolved = resolve_noum(cnn);
		if (CBlockInstance * cinst = dynamic_cast<CBlockInstance *>(resolved))
		{
			if (is_derivadeOf(cinst, kind))
			{
				return cinst;
			}
		}
	}

	return nullptr;

}



bool CBlockInterpreter::assert_it_property(UBlock propname,  UBlock obj, UBlock value)
{
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_it_property(propname , nobj, value);
		}
		return false;
	}
	if (CBlockInstance * cinst = dynamic_cast<CBlockInstance *>(obj))
	{
		if (CBlockNoum * property_noum = dynamic_cast<CBlockNoum *>(propname))
		{
			CVariableNamed* vv = cinst->get_property(property_noum->named );
			UBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind));
			if (instanceValueRefered)
			{
				cinst->set_property(property_noum->named, instanceValueRefered);
				return true;
			}
		}
	}
    return false;

}

bool CBlockInterpreter::assert_it_Value(UBlock obj, UBlock value)
{
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_it_Value(nobj, value);
		}
		return false;
	}

	if (CBlockInstance * nInst = dynamic_cast<CBlockInstance*>(obj))
	{
		if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(value))
		{
			UBlock nobj = resolve_noum(nbase);
			if (nobj == nullptr)
			{
				nInst->set(nbase);
				return true;
			}
		}
	}

	if (CBlockProperty * prop_n = dynamic_cast<CBlockProperty*>(obj))
	{
		UBlock  propNamed = prop_n->prop;		
		UBlock  destination = prop_n->obj;   
		return assert_it_property(propNamed, destination, value); 
	}


	return false;

}



bool CBlockInterpreter::assert_it_not_Value(UBlock obj, UBlock value)
{	
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_it_not_Value(nobj, value);
		}
		return false;
	}


 
	if (CBlockInstance * nInst = dynamic_cast<CBlockInstance*>(obj))
	{
		if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(value))
		{
			UBlock nobj = resolve_noum(nbase);
			if (nobj == nullptr)
			{
				nInst->unset(nbase);
				return true;
			}
		}
			
	}
	return false;
}

bool CBlockInterpreter::assert_it_defaultValue(UBlock obj, UBlock value)
{
	//default value so eh valudi para Kinds
	if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
	{
		UBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr)
		{
			return assert_it_defaultValue(nobj, value);
		}
		return false;
	}
	else if (CBlockInstance  * ibase = dynamic_cast<CBlockInstance*>(obj))
	{
		throw "cant assign Ususally to Instances";
	}
	else if (CBlockProperty   * pbase = dynamic_cast<CBlockProperty*>(obj))
	{
		
		return true;



	}
	else if (CBlockKind  * kbase = dynamic_cast<CBlockKind*>(obj))
	{		 
		if (CBlockNoum * nvalue = dynamic_cast<CBlockNoum*>(value))
		{
			std::cout << kbase->named << "  " << nvalue->named << std::endl;
			//default_assignments.push_back(new CBlockAssertion_isDefaultAssign(kbase, nvalue));
		}
		 
		default_assignments.push_back(new CBlockAssertion_isDefaultAssign(kbase, value));
	}

	return false;
}

std::pair<CBlockKind* , CBlockKind*> CBlockInterpreter::create_derivadeKind(std::string called , std::string baseClasseName)
{

	CBlockKind* b = nullptr;
	CBlockKind* bup = nullptr;

	if ( baseClasseName == "value")
	{
		b = new CBlockKindValue(called);
		
	}
	else if ( baseClasseName == "")
	{
		b = new CBlockKindThing(called);  //Default
	}
	else
	{
		// o que eh a baseclass ???
		UBlock r = resolve_string( baseClasseName );


		if (CBlockKindThing* kt = dynamic_cast<CBlockKindThing*>(r))
		{
			b = new CBlockKindThing(called);
			bup = kt;
		}
		else if (CBlockKindValue* ktv = dynamic_cast<CBlockKindValue*>(r))
		{
			b = new CBlockKindValue(called);
			bup = ktv;
		}
		else
		{
			std::cout << "What ?? " <<  baseClasseName << endl;
			throw "Error on derive a kind";
		}

	}
	return std::pair<CBlockKind*, CBlockKind*>(b, bup);
	
}

bool CBlockInterpreter::assert_it_kind(UBlock obj, UBlock value)
{
	if (CBlockKindOfName * k = dynamic_cast<CBlockKindOfName*>(value))
	{
		if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
		{

			auto  b_up = create_derivadeKind(nbase->named, k->baseClasseName);
			CBlockKind* b = b_up.first;

			if (b_up.second!= nullptr)
			{
				
				CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(b, new CBlockKindOf(b_up.second) );
				kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}

			{

				CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(nbase, b);
				kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}

			std::cout << "new Kind add " << endl;
			return true;
		}

		//Processa a lista
		else if (CBlockList * nList = dynamic_cast<CBlockList*>(obj))
		{
			for (auto nObj : nList->lista)
			{
				if (CBlockNoum * nbasei = dynamic_cast<CBlockNoum*>(nObj))
				{
					auto  b_up = create_derivadeKind(nbase->named, k->baseClasseName);
					CBlockKind* b = b_up.first;
					if (b_up.second != nullptr) 
					{

						CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(b, new CBlockKindOf(b_up.second));
						kindDefinitions.push_back(newDefi);
						assertions.push_back(newDefi);
					}

					{

						CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(nbasei, b);
						kindDefinitions.push_back(newDefi);
						assertions.push_back(newDefi);
					}
					std::cout << "new Kind add" << endl;
				}
			}
			return true;

		}

	}
	return false;

}

bool CBlockInterpreter::assert_it_instance(UBlock obj, UBlock value)
{
	if (CBlockNoum * nvalue = dynamic_cast<CBlockNoum*>(value))
	{
		if (CBlockNoum * nobj = dynamic_cast<CBlockNoum*>(obj))
		{
			UBlock nn = resolve_noum(nvalue);
			if (CBlockKind* k = dynamic_cast<CBlockKind*>(nn))
			{
				//CBlockInstance* binstance = new CBlockInstance(nobj->named);

				CBlockInstance* binstance = new_Instance(nobj->named, k);

				CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(obj, binstance);
				CBlockAssertion_isInstanceOf * newInst = new CBlockAssertion_isInstanceOf(binstance, k);
				assertions.push_back(newDefi);
				assertions.push_back(newInst);
				std::cout << "new Instance add" << endl;
				return true;
			}			
			return false;
		}

		//Many instances
		else if (CBlockList * nobjList = dynamic_cast<CBlockList*>(obj))
		{
			for(auto &e : nobjList->lista)
			{
				assert_it_instance(e, value);
			}			 
			return true;
		}

	}

	return false;
}

