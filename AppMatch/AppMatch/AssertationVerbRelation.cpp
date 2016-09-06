#include "CBlockInterpreterRuntime.h"
#include <iostream>
#include "QueryStack.h"
#include "CResultMatch.h"
using namespace std; 



bool CBlockInterpreter::setVerb(string vb, HBlock c_block, HBlock value)
{
	
	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		cout << "verb  |"<< vb << "| is not defined" << endl;
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
		decList.push_back(make_shared<CBlockAssertion_isDirectAssign>(c_block, value));
		return true ;
	}

}


QueryResul CBlockInterpreter::query_user_verbs(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk)
{

	if (stk.isQuery(vb, c_block, value)) return QUndefined;
	stk.addQuery(vb, c_block, value);


	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		return QueryResul::QUndefined;
	} 


	//Custom Define
	for(auto &v : decides_if)
	{
		if (HBlockMatchIsVerb qVerb = dynamic_pointer_cast<CBlockMatchIsVerb>(v->queryToMatch)) 
		{
			cout << vb <<  " =?= " << qVerb->verb << endl;
			if (vb == qVerb->verb)
			{
				CResultMatch  result_obj = Match(qVerb->obj, c_block,  stk);
				if (result_obj.hasMatch)
				{
					CResultMatch  result_value = Match(qVerb->value, value, stk);
					if (result_value.hasMatch)
					{
						//return v->decideBody;
						return QueryResul::QEquals;
					}

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
	if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
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
	cout << " new Verb |" <<vstr  <<"|"<< endl;
	verbAssertation[ vstr ] = std::list<HBlockAssertion_is>();

	verbRelationAssoc[vstr] = value->relation;
 

	return true;
}