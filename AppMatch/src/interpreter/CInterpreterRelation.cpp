// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "sharedCast.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;


bool CBlockInterpreter::is_nothing(HBlockNoum noum)
{
    return language->is_nothing(noum);

}

bool CBlockInterpreter::is_nothing(HBlock  noum_)
{
	if (asHBlockNothing(noum_) != nullptr) return true;
	if (HBlockNoum noum = asHBlockNoum(noum_))
	{
		return is_nothing(noum);
	}
	return false;
}



bool CBlockInterpreter::set_relation_property(HBlockNoum property_noum , HBlock obj, HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
	for(auto rr : this->staticRelation)
	{
	  if( rr.second->input_B->named == property_noum->named())
	  {
		  this->set_relation(rr.second, obj, value, localsEntry,stk );
		  return true;
	  }
	  else if (rr.second->input_A->named == property_noum->named())
	  {
		  this->set_relation(rr.second, value, obj, localsEntry, stk); //inverte o noums
		  return true;
	  }
	}

	return false;
}

bool CBlockInterpreter::set_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack *stk)
{
 
	//verifica os tipos

	QueryResultContext qk1 = query_is(n1,relation->input_A->kind ,   localsEntry, stk);
	if (qk1.result != QEquals)
	{
		raise_runtime_error("Incompatible type on first argumento of relation");
		  return false;
	}

	QueryResultContext qk2 = query_is(n2,relation->input_B->kind,   localsEntry, stk);
	if (qk2.result != QEquals)
	{
		raise_runtime_error("Incompatible type on second argumento of relation");
		return false;
	}


	if (relation->is_various_noum2() == false )
	{
       //remove todas as relacoes da entidade noum1
		for(auto it = relInstances.begin(); it != relInstances.end();++it)
		{
			auto & rel = *it;
			if (rel->relation->named ==  relation->named)
			{
				QueryResultContext qcc = query_is(rel->value1, n1, localsEntry, stk);
				if ( qcc.result== QueryResul::QEquals  ) 
				{
					it = relInstances.erase(it);
					if (it == relInstances.end()) break;
				}
				if  (rel->relation->is_symetric())
				{
					QueryResultContext qc2 = query_is(rel->value2, n1, localsEntry, stk);
					if ( qc2.result == QueryResul::QEquals)
					{
						it = relInstances.erase(it);
						if (it == relInstances.end()) break;
					}
				}
			}
		}
	}
	if (relation->is_various_noum1() == false) 
	{
		for (auto it = relInstances.begin(); it != relInstances.end(); ++it)
		{
			auto & rel = *it;
			if (rel->relation->named == relation->named)
			{
				QueryResultContext qcc = query_is(rel->value2, n2, localsEntry, stk);
				if (qcc.result == QueryResul::QEquals)
				{					 
					it = relInstances.erase(it);
					if (it == relInstances.end()) break;
					continue;
				}

				if (rel->relation->is_symetric())
				{
					auto qc2 = query_is(rel->value1, n2, localsEntry, stk);
					if ( qc2.result == QueryResul::QEquals)
					{
						it = relInstances.erase(it);
						if (it == relInstances.end()) break;
						continue;
					}
				}
			}
		}

	}

	if (HBlockNoum noum_2 = asHBlockNoum(n2))
	{
		if (is_nothing(noum_2  ) == false)
		{
			auto value_2 = resolve_noum(noum_2, localsEntry , std::list<std::string>() );
			if (value_2 == nullptr)
			{
				logMessage("unable to resolve :" + noum_2->named());
			}
			relInstances.push_back(std::make_shared<CBlockRelationInstance>(relation, n1, value_2));
			 
		}
		return true; // apenas apaga as referencias das relacoes
	}
	else
	{
		relInstances.push_back(std::make_shared<CBlockRelationInstance>(relation, n1, n2));
		return true;
	}

	return false;
}


bool CBlockInterpreter::unset_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack *stk)
{
 
	//Remove relations 
	for (auto it = relInstances.begin(); it != relInstances.end(); ++it)
	{
		auto   rel = *it;
		if (rel->relation->named == relation->named)
		{
			QueryResultContext qcc = query_is(rel->value1, n1, localsEntry, stk);
			if (qcc.result == QueryResul::QEquals)
			{
				QueryResultContext qc3 = query_is(rel->value2, n2, localsEntry, stk);
				if (qc3.result == QueryResul::QEquals) 
				{
					it = relInstances.erase(it);
					if (it == relInstances.end()) break;
					  rel = *it;
				}
			}
				
			if (rel->relation->is_symetric())
			{
				QueryResultContext qc2 = query_is(rel->value1, n2, localsEntry, stk);
				if (qc2.result == QueryResul::QEquals)
				{
					QueryResultContext qc3 = query_is(rel->value2, n1, localsEntry, stk);
					if ( qc3.result == QueryResul::QEquals)
					{
						it = relInstances.erase(it);
						if (it == relInstances.end()) break;
						rel = *it;
					}
				}
			}

		}
	}

	return false;
}