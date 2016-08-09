

#include "BlockInterpreter.h"
#include <iostream>
using namespace std;

 




CBlockKind* CBlockInterpreter::getKindOf(CBlockInstance* obj)
{
	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		if (CBlockAssertion_is * v = dynamic_cast<CBlockAssertion_is*>(*it))
		{
			if (v->obj == obj)
			{
				if (CBlockKind * k = dynamic_cast<CBlockKind*>(v->definition))
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

bool CBlockInterpreter::query_is_same(CBlock* c_block, CBlock* c_block1)
{
	std::string name1 = BlockNoum(c_block);
	std::string name2 = BlockNoum(c_block1);
	if (name1 == "" || name2 == "") return false;
	std::cout << name1 << "  " << name2 << std::endl;
	return  (name1 == name2);
}

bool CBlockInterpreter::query_is(CBlock* c_block, CBlock* c_block1)
{
	for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it)
	{
		if (CBlockToDefine  *tdef = dynamic_cast<CBlockToDefine*>(*it))
		{
			 
		}
	}
 
	if (CBlockInterpreter::query_is_same(c_block, c_block1))
	{
		return true;
	}

	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
		if (CBlockAssertion_is  *qdef = dynamic_cast<CBlockAssertion_is*>(*it))
		{
			if (CBlockInterpreter::query_is_same(c_block, qdef->obj))
			{
				if (CBlockInterpreter::query_is(qdef->definition, c_block1))
				{
					return true;
				}
			}
		}
	}
	return false;

}

bool CBlockInterpreter::query( CBlockAssertion_is* q , CBlockAssertion_is* base ) //Compara as duas queries e retorna true se base valida q
{
	if (CBlockInterpreter::query_is(  q->obj,base->obj) && CBlockInterpreter::query_is(  q->definition,base->definition))
	{
		return true;
	}
	return false;

}
 
bool CBlockInterpreter::query(CBlockAssertion_is* q)
{
	return query_is(q->obj, q->definition);
	return false;

}

HTerm CBlockInterpreter::executeAssertion_is(CBlockAssertion_is *b)
{
	
	// is what ??

	if (CBlockNamedValue * is_namedValue = dynamic_cast<CBlockNamedValue*>(b->obj))
	{


	}

	if (CBlockAssertion_Noum_canBe * noum_canBe = dynamic_cast<CBlockAssertion_Noum_canBe*>(b->definition))
	{
		
	}
	 
	if (CBlockKind * is_define_kind = dynamic_cast<CBlockKind*>(b->definition))
	{

	}


}



HTerm CBlockInterpreter::executeAssertion(CBlockAssertionBase *b )
{
	 
  
	if (CBlockAssertion_isInstanceOf* inst =   dynamic_cast<CBlockAssertion_isInstanceOf *>(b) )
	{
		instancias.push_back(inst->noum);
	}

	assertions.push_back(b);
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


