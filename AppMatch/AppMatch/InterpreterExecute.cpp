

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

	if (CBlockKindValue * k0 = dynamic_cast<CBlockKindValue*>(c_block))
	{
		return k0->named;
	}
	return "";
}

 

bool CBlockInterpreter::query_is(CBlock* c_block, CBlock* c_block1)
{
	std::string name1 = BlockNoum(c_block);
	std::string name2 = BlockNoum(c_block1);
	if ( name1 == "" || name2 == "" ) return false;
	return (name1 == name2);
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
	for (auto it = assertions.begin(); it != assertions.end(); ++it)
	{
	  auto &base = *it;
	  if (CBlockAssertion_is  *qdef = dynamic_cast<CBlockAssertion_is*>(base))
		{		 
			if (CBlockInterpreter::query_is(q->obj, qdef->obj))
			{
				if (CBlockInterpreter::query_is(qdef->definition , q->definition))
				{
					return true;
				}				
			}
		}
	}	 
	return false;

}

HTerm CBlockInterpreter::executeAssertion(CBlockAssertionBase *b )
{
  

	assertions.push_back(b);
	return nullptr;
}

HTerm CBlockInterpreter::execute(CBlock* b)
{
	if (dynamic_cast<CBlockAssertionBase*>(b) != nullptr) return executeAssertion(dynamic_cast<CBlockAssertionBase*>(b));


	return nullptr;
}


