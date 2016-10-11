#include "CBlockInterpreterRuntime.hpp"
 
#include "QueryStack.hpp"
#include "CResultMatch.hpp"
#include "sharedCast.hpp"

using namespace std; 



bool CBlockInterpreter::setVerb(string vb, HBlock c_block, HBlock value)
{
	
	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		logMessage("verb  |" + vb + "| is not defined");
		return false;
	}

	{
		std::list<HBlockAssertion_is> &decList = alist->second;
		for(auto &c_is : decList)
		{
			if ((c_is->get_obj() == c_block) && (c_is->get_definition() == value))
			{
				return true; // ja existe
			}
		}
		//decList.push_back(make_shared<CBlockAssertion_isDirectAssign>(c_block, value));

		decList.push_back( make_shared<CBlockIsVerb>( vb,  c_block, value));
		return true ;
	}

}


QueryResul CBlockInterpreter::query_relation(HBlockRelationBase rel, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk)
{
	// Percorre todos e retorna o valor
	for (auto &rr : relInstances)
	{
		if (rr->relation == rel)
		{
			QueryResul query_2 = QUndefined;
			if (QEquals == query_is(c_block, rr->value1, localsEntry, stk))
			{
				if (QEquals == query_is(value,rr->value2, localsEntry, stk))
				{
					return QEquals;
				}
				query_2 = QNotEquals;
				if (rr->relation->is_various_noum1() == false)
				{
					return QNotEquals;
				}
			}
			else if (QUndefined == query_2 )
			{
				if (QEquals == query_is(value, rr->value2, localsEntry, stk))
				{
					if (QEquals == query_is(c_block, rr->value1, localsEntry, stk))
					{
						return QEquals;
					}
					if (rr->relation->is_various_noum2() == false)
					{
						return QNotEquals;
					}
				}
			}


			if (rr->relation->is_symetric()) // Trocado
			{
				if (QEquals == query_is(c_block, rr->value2, localsEntry, stk))
				{
					if (QEquals == query_is(value, rr->value1, localsEntry, stk))
					{
						return QEquals;
					}
					if (rr->relation->is_various_noum1() == false)
					{
						return QNotEquals;
					}
				}
			}
		}
	}
	return QUndefined;
}

QueryResul CBlockInterpreter::query_user_verbs(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk)
{

	if (stk.isQuery(vb, c_block, value)) return QUndefined;
	stk.addQuery(vb, c_block, value);




	// Tem alguma relacao associada ??
	for (auto & rv : verbRelationAssoc)
	{
		if (rv.first == vb)
		{
			auto relation_name = rv.second->named;
			if (relation_name != "dynamic")
			{
				auto rel_find = this->staticRelation.find(relation_name);
				if (rel_find != this->staticRelation.end())
				{
					HBlockRelationBase rel = rel_find->second;
					QueryResul rel_query = this->query_relation(rel,  c_block , value,localsEntry,stk);
					if (rel_query == QEquals) return  QEquals;
					return QNotEquals;
				}
			}
		}

	}


	



	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		return QueryResul::QUndefined;
	} 


	//Custom Define
	for(auto &v : decides_if)
	{
		if (HBlockMatchIsVerb qVerb = asHBlockMatchIsVerb(v->queryToMatch))
		{
			 
			if (vb == qVerb->verb)
			{
				CResultMatch  result_obj = Match(qVerb->obj, c_block, localsEntry, stk);
				if (result_obj.hasMatch)
				{
					CResultMatch  result_value = Match(qVerb->value, value, localsEntry , stk);
					if (result_value.hasMatch)
					{
						//return v->decideBody;
						return QueryResul::QEquals;
					}

				}
			}
		}
	}

	// Match com o What

	for(auto &dct : decides_what)
	{
		if (HBlockMatchIsVerb qVerb = asHBlockMatchIsVerb(dct->queryToMatch)) {
			//cout << vb << " =?= " << qVerb->verb << endl;
			if (qVerb->verb == vb) {
				HBlock wvalued = getDecidedValueOf(value, dct, localsEntry, stk);
				if (wvalued != nullptr) {
					auto wresult = query_is(c_block, wvalued, localsEntry, stk);
					return wresult;
				}
			}
		}
	}


	// Match com o primeiro Noum


	//Custom Define
	for (auto &v : decides_noum1)
	{
		if (HBlockMatchIsVerb qVerb_N1 = asHBlockMatchIsVerb(v->queryToMatch))
		{
			
			if (vb == qVerb_N1->verb)
			{
			//	cout << vb << " =?= " << qVerb_N1->verb << endl;
				CResultMatch  result_value = Match(qVerb_N1->value, value, localsEntry, stk); // o resto da match ??
				if (result_value.hasMatch)
				{
					auto  obj_resolved = v->decideBody;
					value->dump("   ");
					obj_resolved->dump("  ");
					
					return query_is(c_block, obj_resolved,localsEntry,stk );
				}
			}
		}
	}



	std::list<HBlockAssertion_is> &decList = alist->second;
	for (auto &c_is : decList)
	{
		QueryResul a1 = query_is(c_block , c_is->get_obj() , localsEntry,stk );
		if (a1 == QEquals)
		{
			QueryResul a2 = query_is(c_is->get_definition(), value,localsEntry,stk);
			if (a2 == QEquals)
			{
				return QEquals;
			}
		}
	}
	return QueryResul::QUndefined;
}



bool CBlockInterpreter::assert_it_verbRelation( std::string verbNamed ,HBlock obj, HBlock value, HRunLocalScope localsEntry) {
	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_it_verbRelation(verbNamed , nobj, value, localsEntry);
		}		
	}
	return setVerb(verbNamed, obj, value);

	return false;
}




bool CBlockInterpreter::assert_newVerb(HBlockVerbRelation value)
{
	std::string vstr = HtoString(value->verbNoum);
	//verifica se ja existe esse verbo

	auto vfind = verbAssertation.find(vstr);
	if (vfind != verbAssertation.end() )
	{
		throw  "Verb is Assigned";
		return false;
	}

	//cout << " new Verb |" <<vstr  <<"|"<< endl;
	verbAssertation[ vstr ] = std::list<HBlockAssertion_is>();

    // Existe essa relacao ??
	verbRelationAssoc[vstr] = value->relationNoum;
 

	return true;
}