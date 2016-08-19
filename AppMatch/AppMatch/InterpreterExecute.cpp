

#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "CInterpreterKindTree.h"

using namespace std;


class QueryItem
{
public:
	QueryItem(UBlock b1, UBlock b2)
		: b1(b1),
		  b2(b2)
	{
	}

	UBlock b1;
	UBlock b2;

};

class QueryStack
{
	std::list<QueryItem> items;
public:
	void addQuery(UBlock b1, UBlock b2);
	bool isQuery(UBlock b1, UBlock b2);
};

void QueryStack::addQuery(UBlock b1, UBlock b2)
{
	items.push_back(QueryItem(b1, b2));
}

bool QueryStack::isQuery(UBlock b1, UBlock b2)
{
	for(auto &q : items)
	{
		if ((q.b1 == b1) && (q.b2 == b2)) return true;
	}
	return false;
}


CBlockInterpreter::CBlockInterpreter()
{
}

CBlockInterpreter::~CBlockInterpreter()
{
}


CBlockKind* CBlockInterpreter::getKindOf(CBlockInstance* obj)
{
	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		if (CBlockAssertion_is * v = dynamic_cast<CBlockAssertion_is*>(*it))
		{
			if (v->get_obj() == obj)
			{
				if (CBlockKind * k = dynamic_cast<CBlockKind*>(v->get_definition()))
				{
					return k;
				}
			}
		}
	}
	return nullptr;
}

 

 

std::string BlockNoum(CBlock* c_block)
{
	if (CBlockKind * k0 = dynamic_cast<CBlockKind*>(c_block))
	{
		return k0->named;
	}

	if (CBlockInstance * k0 = dynamic_cast<CBlockInstance*>(c_block))
	{
		return k0->named;
	}

	if (CBlockKindValue * k0 = dynamic_cast<CBlockKindValue*>(c_block))
	{
		return k0->named;
	}

	if (CBlockNamedValue  * k0 = dynamic_cast<CBlockNamedValue*>(c_block))
	{
		return k0->named ;
	}

	if (CBlockVariable   * k0 = dynamic_cast<CBlockVariable*>(c_block))
	{
		return k0->named;
	}

	if (CBlockNoum * k0 = dynamic_cast<CBlockNoum*>(c_block))
	{
		return k0->named;
	}
	return "";
}

//bool CBlockInterpreter::query_is_sameKind(CBlock* c_block, CBlock* c_block1)
//{
//	
//}
//bool CBlockInterpreter::query_is_sameInstance(CBlock* c_block, CBlock* c_block1)
//{
//
//}
//bool CBlockInterpreter::query_is_sameNamedValue(CBlock* c_block, CBlock* c_block1)
//{
//
//}
//bool CBlockInterpreter::query_is_sameVariable(CBlock* c_block, CBlock* c_block1)
//{
//
//}

QueryResul CBlockInterpreter::query_is_same(CBlock* c_block, CBlock* c_block1)
{
	std::string name1 = BlockNoum(c_block);
	std::string name2 = BlockNoum(c_block1);
	if (name1 == "" || name2 == "") return QUndefined;
	//std::cout << name1 << "  " << name2 << std::endl;
	if (name1 == name2)
	{
		return QEquals;
	}
	return QNotEquals;
}

QueryResul CBlockInterpreter::query_is(CBlock* c_block, CBlock* c_block1)
{
	if (CBlockNoum  *nnoum = dynamic_cast<CBlockNoum*>(c_block1))
	{
		UBlock resolved =  resolve_noum(nnoum);
		if (resolved)
		{
			return query_is(c_block, resolved, QueryStack());
		}
		// pode ser um atributo
		return query_is(c_block, nnoum, QueryStack());

	}

	return query_is(c_block, c_block1, QueryStack());
}

QueryResul CBlockInterpreter::query_is_instance_valueSet(CBlock * c_block, CBlock * c_block1)
{
	if (CBlockInstance * cinst = dynamic_cast<CBlockInstance *>(c_block))
		if (CBlockNoum * value = dynamic_cast<CBlockNoum *>(c_block1))
		{
			if (cinst->has_slot(value))
			{
				std::cout << cinst->named << "  " << value->named << std::endl;
				if (cinst->is_set(value))
				{
					return QEquals;
				}
				return QNotEquals;
			}
		}
	return QUndefined;

}

QueryResul CBlockInterpreter::query_is_propertyOf_value_imp(CBlock * propname, CBlock * propObj, CBlock * c_block1, QueryStack stk)
{
	if (CBlockInstance * cinst = dynamic_cast<CBlockInstance *>(propObj))
	{
		if (CBlockNoum * property_noum = dynamic_cast<CBlockNoum *>(propname))
		{
			CVariableNamed * pvar = cinst->get_property(property_noum->named);
			if (pvar != nullptr)
			{
				std::cout << "property  is " <<  std::endl;
				pvar->value->dump("  ");
				c_block1->dump("  ");
				auto rprop =  query_is(pvar->value, c_block1, stk);
				if (rprop == QEquals) return QEquals;
				return QNotEquals;
			}
		}
	}
	return QUndefined;
}


QueryResul CBlockInterpreter::query_is_propertyOf_value(CBlock * c_block, CBlock * c_block1,   QueryStack stk)
{
	if (CBlockProperty * cproperty = dynamic_cast<CBlockProperty *>(c_block))
	{
		if (CBlockNoum * cnn = dynamic_cast<CBlockNoum *>(cproperty->obj))
		{
			auto resolved = resolve_noum(cnn);
			if (resolved != nullptr)
			{
				return query_is_propertyOf_value_imp(cproperty->prop,  resolved, c_block1, stk);
			}
			return QUndefined;

		}
		// property of What ??
	 	return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_block1, stk);

		 
	}
	 
	return QUndefined;

}



QueryResul CBlockInterpreter::query_is(CBlock* c_block, CBlock* c_block1, QueryStack stk)
{
	if (stk.isQuery(c_block, c_block1))  return QUndefined;
	stk.addQuery(c_block, c_block1);

	{

		if (CBlockInstance  * ninst_1 = dynamic_cast<CBlockInstance*>(c_block))
			if (CBlockInstance  * ninst_2 = dynamic_cast<CBlockInstance*>(c_block1))
			{
				if (ninst_1->baseKind != nullptr && ninst_1->baseKind != ninst_1->baseKind)
				{
					if (ninst_1 == ninst_2) return QEquals;
				}
				
			}

	}
	//is scond a kind of anything ??
	if (CBlockKind * bkind = dynamic_cast<CBlockKind*>(c_block1))
	{
		if (CBlockKind * akind = dynamic_cast<CBlockKind*>(c_block))
		{
			bool b = is_derivadeOf(akind, bkind);
			if (b) return QEquals;
		}
		else if (CBlockInstance * aInstance = dynamic_cast<CBlockInstance*>(c_block))
		{
			bool b = is_derivadeOf(aInstance, bkind);
			if (b) return QEquals;
		}
	}


	for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it)
	{
		if (CBlockToDecide  *tdef = dynamic_cast<CBlockToDecide*>(*it))
		{
			 
		}
	}

	{
		QueryResul rinst = (CBlockInterpreter::query_is_instance_valueSet(c_block, c_block1));
		if (rinst != QUndefined)
		{
			return rinst;
		}

		QueryResul qprop = query_is_propertyOf_value(c_block, c_block1, stk);
		if (qprop != QUndefined)
		{
			return qprop;
		}
	}


 
	auto r2 = CBlockInterpreter::query_is_same(c_block, c_block1);	
	if (r2 ==  QEquals)
	{
		return  r2;
	}
	

	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		if (CBlockAssertion_is  *qdef = dynamic_cast<CBlockAssertion_is*>(*it))
		{
			if (CBlockInterpreter::query_is_same(c_block, qdef->get_obj()) == QEquals)
			{
				auto r = CBlockInterpreter::query_is(qdef->get_definition(), c_block1, stk);
				if (r != QUndefined)
				{
					return r;
				}
				
			}
		}
	}
	return QUndefined;

}

 

QueryResul CBlockInterpreter::query( CBlockAssertion_is* q , CBlockAssertion_is* base ) //Compara as duas queries e retorna true se base valida q
{
	if (CBlockInterpreter::query_is(  q->get_obj(),base->get_obj()) && CBlockInterpreter::query_is(  q->get_definition(),base->get_definition()))
	{
		return QEquals;
	}
	return QUndefined;

}
 
QueryResul CBlockInterpreter::query(CBlockAssertion_is* q)
{
	return query_is(q->get_obj(), q->get_definition());
	return QUndefined;

}

HTerm CBlockInterpreter::executeAssertion_is(CBlockAssertion_is *b)
{
	
	// is what ??

	if (CBlockNamedValue * is_namedValue = dynamic_cast<CBlockNamedValue*>(b->get_obj()))
	{


	}

	if (CBlockAssertion_canBe * noum_canBe = dynamic_cast<CBlockAssertion_canBe*>(b->get_definition()))
	{
		
	}
	 
	if (CBlockKind * is_define_kind = dynamic_cast<CBlockKind*>(b->get_definition()))
	{

	}
	return nullptr;

}



HTerm CBlockInterpreter::executeAssertion(CBlockAssertionBase *b )
{
	 
  
	if (CBlockAssertion_isInstanceOf* inst =   dynamic_cast<CBlockAssertion_isInstanceOf *>(b) )
	{
		instancias.push_back(inst->noum);
	}

	//assertions.push_back(b);
	return nullptr;
}

HTerm CBlockInterpreter::execute(CBlock* b)
{
	if (b == nullptr)
	{
		throw "parse error";
	}	 

	if (dynamic_cast<CBlockAssertionBase*>(b) != nullptr) return executeAssertion(dynamic_cast<CBlockAssertionBase*>(b));


	return nullptr;
}

 
CBlock* CBlockInterpreter::resolve(CTerm  *b)
{
	return new CBlockNoum(b->repr());
}
CBlock* CBlockInterpreter::resolve_of(CBlock  *b, CBlock *a)
{
	//return new CBlockProperty( b , a);
	return nullptr;
}

bool CBlockInterpreter::is_derivadeOf(CBlockKind  *a, CBlockKind *b)
{
	if (a->named == "" || b->named == "") return false;
	if (a->named ==  b->named ) return true;

	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{		
		{
			if (CBlockKind * nbase = dynamic_cast<CBlockKind*>((*it)->get_obj()))

				if (nbase->named == a->named)
				{
					if (CBlockKindOf * k = dynamic_cast<CBlockKindOf*>((*it)->get_definition()))
					{
						if (k->baseClasse->named  == b->named)
						{
							return true;
						}	
						else
						{
						 bool bnn =  is_derivadeOf(k->baseClasse, b);
								if (bnn == true)
								{
									return true;
								}
							 
						}
					}
				}
		}
	}
	return false;
}

std::list<CBlockKind*> CBlockInterpreter::getUpperKinds(CBlockKind* a  )
{
	std::list<CBlockKind*> upperList;
 
	std::cout << "U " << a->named << std::endl;
	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{

		if (CBlockKind * nbase = dynamic_cast<CBlockKind*>((*it)->get_obj()))
			if (nbase->named == a->named)  //  A -> X
			{
				if (CBlockKindOf * k = dynamic_cast<CBlockKindOf*>((*it)->get_definition()))
				{
 
				 
						std::list<CBlockKind*> ap = getUpperKinds(k->baseClasse);
						upperList.insert(upperList.end(), ap.begin(), ap.end());						

				 
				}
			}

	}
	
	//upperList.erase(unique(upperList.begin(), upperList.end()), upperList.end());
	upperList.push_back(a);
	return upperList;
}

bool CBlockInterpreter::is_derivadeOf(CBlockInstance  *a, CBlockKind *b)
{
	if (a->named == "" || b->named == "")
	{
		return false;
	}
	if (a->named == b->named)
	{
		return true;
	}

	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		{if (CBlockInstance * nbase = dynamic_cast<CBlockInstance*>((*it)->get_obj()))

			if (nbase->named == a->named)
			{
				if (CBlockKind  * k = dynamic_cast<CBlockKind *>((*it)->get_definition()))
				{
					if (k->named  == b->named)
					{
						return true;
					}
					else
					{
						UBlock bnext = resolve_string(k->named);
						if (CBlockKind *baseClasse = dynamic_cast<CBlockKind*>(bnext))
						{
							bool bnn = is_derivadeOf(baseClasse, b);
							if (bnn == true)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

 
CBlockKind* CBlockInterpreter::resolve_kind(std::string n)
{
	for (auto &defs : assertions)
	{
		if (CBlockKind * nn = dynamic_cast<CBlockKind *>(defs->get_definition()))
		{			 
			if (nn->named == n)
			{
				return nn;
			}
		}
	}
	return nullptr;

}

CBlock* CBlockInterpreter::resolve_noum(CBlockNoum* n)
{
	// eh um kind de alguma coisa ?
	for(auto &defs : assertions )
	{
		if (CBlockNoum * nn  = dynamic_cast<CBlockNoum *>(defs->get_obj() ))
		{
			//std::cout << nn->named << std::endl;
			if (nn->named == n->named)
			{
				return defs->get_definition();
			}
		}
	}
	std::cout << "Fail to "<< n->named << std::endl;
	return nullptr;


}

CBlock* CBlockInterpreter::resolve_string(std::string n)
{
	for (auto &defs : assertions)
	{
		if (CBlockNoum * nn = dynamic_cast<CBlockNoum *>(defs->get_obj()))
		{
			//std::cout << nn->named << std::endl;
			if (nn->named == n)
			{
				return defs->get_definition();
			}
		}
	}
	return nullptr;
}

void CBlockInterpreter::dump_instance(std::string str)
{
	CBlock *n = resolve_string(str);
	if (CBlockInstance * nn = dynamic_cast<CBlockInstance *>(n))
	{
		for (auto &va : nn->anomimousSlots)
		{
			std::cout << "====================" << std::endl;
			if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
			{
				
				venum->valueDefinition->dump("    ");
				venum->value->dump("    ");
				
			}
			if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
			{
				 
				
				vbool->valueDefinition->dump("    ");
				cout << vbool->value << std::endl;
			}
		}

	}
}
