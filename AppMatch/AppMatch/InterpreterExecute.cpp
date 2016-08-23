

#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "CInterpreterKindTree.h"

using namespace std;


class QueryItem
{
public:
	QueryItem(HBlock b1, HBlock b2)
		: b1(b1),
		  b2(b2)
	{
	}

	HBlock b1;
	HBlock b2;

};

class QueryStack
{
	std::list<QueryItem> items;
public:
	void addQuery(HBlock b1, HBlock b2);
	bool isQuery(HBlock b1, HBlock b2);
};

void QueryStack::addQuery(HBlock b1, HBlock b2)
{
	items.push_back(QueryItem(b1, b2));
}

bool QueryStack::isQuery(HBlock b1, HBlock b2)
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


HBlockKind CBlockInterpreter::getKindOf(HBlockInstance obj)
{
	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		if (HBlockAssertion_is   v = dynamic_pointer_cast<CBlockAssertion_is>(*it))
		{
			if (v->get_obj() == obj)
			{
				if (HBlockKind   k = dynamic_pointer_cast<CBlockKind>(v->get_definition()))
				{
					return k;
				}
			}
		}
	}
	return nullptr;
}

 

 

std::string BlockNoum(HBlock c_block)
{
	if (HBlockKind   k0 = dynamic_pointer_cast<CBlockKind>(c_block))
	{
		return k0->named;
	}

	if (HBlockInstance   k0 = dynamic_pointer_cast<CBlockInstance>(c_block))
	{
		return k0->named;
	}

	if (HBlockKindValue  k0 = dynamic_pointer_cast<CBlockKindValue>(c_block))
	{
		return k0->named;
	}

	if (HBlockNamedValue   k0 = dynamic_pointer_cast<CBlockNamedValue>(c_block))
	{
		return k0->named ;
	}

	if (HBlockVariable    k0 = dynamic_pointer_cast<CBlockVariable>(c_block))
	{
		return k0->named;
	}

	if (HBlockNoum  k0 = dynamic_pointer_cast<CBlockNoum>(c_block))
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

QueryResul CBlockInterpreter::query_is_same(HBlock c_block, HBlock c_block1)
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

QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1)
{
	if (HBlockNoum  nnoum = dynamic_pointer_cast<CBlockNoum>(c_block1))
	{
		HBlock resolved =  resolve_noum(nnoum);
		if (resolved)
		{
			return query_is(c_block, resolved, QueryStack());
		}
		// pode ser um atributo
		return query_is(c_block, nnoum, QueryStack());

	}

	return query_is(c_block, c_block1, QueryStack());
}

QueryResul CBlockInterpreter::query_is_instance_valueSet(HBlock  c_block, HBlock  c_block1)
{
	if (HBlockInstance  cinst = dynamic_pointer_cast<CBlockInstance >(c_block))
		if (HBlockNoum  value = dynamic_pointer_cast<CBlockNoum >(c_block1))
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

QueryResul CBlockInterpreter::query_is_propertyOf_value_imp(HBlock  propname, HBlock  propObj, HBlock  c_block1, QueryStack stk)
{
	if (HBlockInstance  cinst = dynamic_pointer_cast<CBlockInstance >(propObj))
	{
		if (HBlockNoum  property_noum = dynamic_pointer_cast<CBlockNoum >(propname))
		{
			HVariableNamed   pvar = cinst->get_property(property_noum->named);
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


QueryResul CBlockInterpreter::query_is_propertyOf_value(HBlock  c_block, HBlock  c_block1,   QueryStack stk)
{
	if (HBlockProperty  cproperty = dynamic_pointer_cast<CBlockProperty >(c_block))
	{
		if (HBlockNoum  cnn = dynamic_pointer_cast<CBlockNoum >(cproperty->obj))
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



QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, QueryStack stk)
{
	if (stk.isQuery(c_block, c_block1))  return QUndefined;
	stk.addQuery(c_block, c_block1);

	{
		if (HBlockInstance   ninst_1 = dynamic_pointer_cast<CBlockInstance>(c_block))
			if (HBlockInstance   ninst_2 = dynamic_pointer_cast<CBlockInstance>(c_block1))
			{
				if (ninst_1->baseKind != nullptr && ninst_1->baseKind != ninst_1->baseKind)
				{
					if (ninst_1 == ninst_2) return QEquals;
				}
				
			}
	}
	 


	for  (auto dct : decides_what )
	{
		auto dctValueWrap = getDecidedValueOf(c_block, dct);
		if (dctValueWrap != nullptr)
		{
			return  CBlockInterpreter::query_is(dctValueWrap, c_block1, stk); //is not opnional	
		}
	}

	for  (auto dct : decides_what)
	{
		auto dctValueWrap_1 = getDecidedValueOf(c_block1, dct);
		if (dctValueWrap_1 != nullptr)
		{
			return  CBlockInterpreter::query_is(c_block, dctValueWrap_1, stk);  //is not opnional				 
		}
	}



	//is scond a kind of anything ??
	if (HBlockKind  bkind = dynamic_pointer_cast<CBlockKind>(c_block1))
	{
		if (HBlockKind  akind = dynamic_pointer_cast<CBlockKind>(c_block))
		{
			bool b = is_derivadeOf(akind, bkind);
			if (b) return QEquals;
		}
		else if (HBlockInstance  aInstance = dynamic_pointer_cast<CBlockInstance>(c_block))
		{
			bool b = is_derivadeOf(aInstance, bkind);
			if (b) return QEquals;
		}
	}


	for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it)
	{
		if (HBlockToDecide  tdef = dynamic_pointer_cast<CBlockToDecide>(*it))
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
		if (HBlockAssertion_is  qdef = dynamic_pointer_cast<CBlockAssertion_is>(*it))
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

 

QueryResul CBlockInterpreter::query(HBlockAssertion_is q , HBlockAssertion_is base ) //Compara as duas queries e retorna true se base valida q
{
	if (CBlockInterpreter::query_is(  q->get_obj(),base->get_obj()) && CBlockInterpreter::query_is(  q->get_definition(),base->get_definition()))
	{
		return QEquals;
	}
	return QUndefined;

}
 
QueryResul CBlockInterpreter::query(HBlockAssertion_is q)
{
	return query_is(q->get_obj(), q->get_definition());
	return QUndefined;

}

HTerm CBlockInterpreter::executeAssertion_is(HBlockAssertion_is  b)
{
	
	// is what ??

	if (HBlockNamedValue   is_namedValue = dynamic_pointer_cast<CBlockNamedValue>(b->get_obj()))
	{


	}

	if (HBlockAssertion_canBe   noum_canBe = dynamic_pointer_cast<CBlockAssertion_canBe>(b->get_definition()))
	{
		
	}
	 
	if (HBlockKind   is_define_kind = dynamic_pointer_cast<CBlockKind>(b->get_definition()))
	{

	}
	return nullptr;

}



HTerm CBlockInterpreter::executeAssertion(HBlockAssertionBase  b )
{
	 
  
	if (HBlockAssertion_isInstanceOf  inst =   dynamic_pointer_cast<CBlockAssertion_isInstanceOf  >(b) )
	{
		instancias.push_back(inst->noum);
	}

	//assertions.push_back(b);
	return nullptr;
}

HTerm CBlockInterpreter::execute(HBlock b)
{
	if (b == nullptr)
	{
		throw "parse error";
	}	 

	if (dynamic_pointer_cast<CBlockAssertionBase>(b) != nullptr) return executeAssertion(dynamic_pointer_cast<CBlockAssertionBase>(b));


	return nullptr;
}

 
HBlock CBlockInterpreter::resolve(CTerm  *b)
{
	return make_shared<CBlockNoum>(b->repr());
}
HBlock CBlockInterpreter::resolve_of(HBlock   b, HBlock  a)
{
	//return new CBlockProperty( b , a);
	return nullptr;
}

HBlockKind CBlockInterpreter::resolve_kind(std::string n)
{
	for (auto &defs : assertions)
	{
		if (HBlockKind   nn = dynamic_pointer_cast<CBlockKind  >(defs->get_definition()))
		{			 
			if (nn->named == n)
			{
				return nn;
			}
		}
	}
	return nullptr;

}

HBlock CBlockInterpreter::resolve_noum(HBlockNoum n)
{
	// eh um kind de alguma coisa ?
	for(auto &defs : assertions )
	{
		if (HBlockNoum   nn  = dynamic_pointer_cast<CBlockNoum  >(defs->get_obj() ))
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

HBlock CBlockInterpreter::resolve_string(std::string n)
{
	for (auto &defs : assertions)
	{
		if (HBlockNoum   nn = dynamic_pointer_cast<CBlockNoum  >(defs->get_obj()))
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
	HBlock  n = resolve_string(str);
	if (HBlockInstance   nn = dynamic_pointer_cast<CBlockInstance  >(n))
	{
		for (auto &va : nn->anomimousSlots)
		{
			std::cout << "====================" << std::endl;
			if (HVariableSlotEnum   venum = dynamic_pointer_cast<CVariableSlotEnum>(va))
			{
				
				venum->valueDefinition->dump("    ");
				venum->value->dump("    ");
				
			}
			if (HVariableSlotBool   vbool = dynamic_pointer_cast<CVariableSlotBool>(va))
			{
				 
				
				vbool->valueDefinition->dump("    ");
				cout << vbool->value << std::endl;
			}
		}

	}
}
