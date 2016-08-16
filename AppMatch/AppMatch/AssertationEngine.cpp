
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
		
		if (assert_it_kind(obj, value)) return;
		if (assert_it_instance(obj, value)) return;		 
		if (assert_it_valuesDefinitions(obj, value)) return;

		throw "undefined block";
	}
	 
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
bool CBlockInterpreter::assert_it_kind(UBlock obj, UBlock value)
{
	if (CBlockKindOf * k = dynamic_cast<CBlockKindOf*>(value))
	{
		if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(obj))
		{
			{
				UBlock b = nullptr;
				 
				if (k->baseClasseName  == "value")
				{
					b = new CBlockKindValue("");
				}
				else
				{
					b = new CBlockKind(nbase->named);
				}
				{
					CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(b, k);
					kindDefinitions.push_back(newDefi);
					assertions.push_back(newDefi);
				}

				{

					CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(nbase, b);
					kindDefinitions.push_back(newDefi);
					assertions.push_back(newDefi);
				}

				std::cout << "new Kind add" << endl;
				return true;
			}

			//Processa a lista
			if (CBlockList * nList = dynamic_cast<CBlockList*>(obj))
			{
				for (auto nObj : nList->lista)
				{
					if (CBlockNoum * nbase = dynamic_cast<CBlockNoum*>(nObj))
					{
						{
							UBlock b = new CBlockKind(nbase->named);
							CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(b, k);
							kindDefinitions.push_back(newDefi);
							assertions.push_back(newDefi);
						}

						{
							UBlock b = new CBlockKind(nbase->named);
							CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(nbase, b);
							kindDefinitions.push_back(newDefi);
							assertions.push_back(newDefi);
						}
						std::cout << "new Kind add" << endl;
					}
				}
				return true;

			}
		}
	}
	return false;

}

bool CBlockInterpreter::assert_it_instance(UBlock obj, UBlock value)
{
	if (CBlockNoum * nvalue = dynamic_cast<CBlockNoum*>(value))
		if (CBlockNoum * nobj = dynamic_cast<CBlockNoum*>(obj))
		{
			UBlock nn = resolve_noum(nvalue);
			if (CBlockKind* k = dynamic_cast<CBlockKind*>(nn))
			{
				//CBlockInstance* binstance = new CBlockInstance(nobj->named);
				 
				CBlockInstance* binstance = new_Instance(nobj->named ,k );

				CBlockAssertion_isDirectAssign* newDefi = new CBlockAssertion_isDirectAssign(obj, binstance);
				CBlockAssertion_isInstanceOf * newInst = new CBlockAssertion_isInstanceOf(binstance, k);
				assertions.push_back(newDefi);
				assertions.push_back(newInst);
			} 
			std::cout << "new Instance add" << endl;
			return true;
		}

	return false;
}

