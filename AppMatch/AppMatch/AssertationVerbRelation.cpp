#include "CBlockInterpreterRuntime.h"
#include <iostream>
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


QueryResul CBlockInterpreter::getVerb(string vb, HBlock c_block, HBlock value)
{

	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		return QueryResul::QUndefined;
	} 

	std::list<HBlockAssertion_is> &decList = alist->second;
	for (auto &c_is : decList)
	{
		QueryResul a1 = query_is(c_block , c_is->get_obj() );
		if (a1 == QEquals)
		{
			QueryResul a2 = query_is(c_is->get_definition(), value);
			if (a2 == QEquals)
			{
				return QEquals;
			}
		}
	}
	return QueryResul::QUndefined;
}



bool CBlockInterpreter::assert_it_verbRelation( std::string verbNamed ,HBlock obj, HBlock value) {
	if (HBlockNoum nbase = dynamic_pointer_cast<CBlockNoum>(obj)) {
		HBlock nobj = resolve_noum(nbase);
		if (nobj != nullptr) {
			return assert_it_verbRelation(verbNamed , nobj, value);
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