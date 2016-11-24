


#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"

bool CBlockInterpreter::is_nothing(HBlockNoum noum)
{
	if (noum->named == "nothing") return true;
	if (noum->named == "none") return true;
	if (noum->named == "nil") return true;
	return false;
}

bool CBlockInterpreter::set_relation_property(HBlockNoum property_noum , HBlock n1, HBlock n2, HRunLocalScope localsEntry)
{
	for(auto rr : this->staticRelation)
	{
	  if( rr.second->input_B->named == property_noum->named)
	  {
		  this->set_relation(rr.second, n1, n2, localsEntry);
		  return true;
	  }
	  else if (rr.second->input_A->named == property_noum->named)
	  {
		  this->set_relation(rr.second, n2, n1, localsEntry); //inverte o noums
		  return true;
	  }
	}

	return false;
}

bool CBlockInterpreter::set_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry)
{
	QueryStack stk;

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
				}
				if (rel->relation->is_symetric())
				{
					auto qc2 = query_is(rel->value1, n2, localsEntry, stk);
					if ( qc2.result == QueryResul::QEquals)
					{
						it = relInstances.erase(it);
						if (it == relInstances.end()) break;
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
				logMessage("unable to resolve :" + noum_2->named);
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


bool CBlockInterpreter::unset_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry)
{
	QueryStack stk;

	 
	 

	//Remove relations 
	for (auto it = relInstances.begin(); it != relInstances.end(); ++it)
	{
		auto & rel = *it;
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
					}
				}
			}

		}
	}

	 

	return false;
}