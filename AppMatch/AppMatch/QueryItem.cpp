// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "BlockInterpreter.hpp"
#include  "QueryStack.hpp"

 
using namespace CBlocking;


void QueryStack::addQuery(HBlockVerb vb, HBlock b1, HBlock b2) {
    items.push_back(QueryItem(vb->named,b1, b2));
}

void QueryStack::addQuery(string vb, HBlock b1, HBlock b2) {
	items.push_back(QueryItem(vb, b1, b2));
}

bool QueryStack::isQuery(HBlockVerb vb, HBlock b1, HBlock b2) {
	return isQuery(vb->named, b1, b2);
}

bool QueryStack::isQuery(string _verb, HBlock b1, HBlock b2)
{
	for (auto &q : items) {
		if ((q.verb  == _verb) && (q.b1->isSame(b1.get(), q.b1.get())) && q.b2->isSame(q.b2.get(), b2.get())) return true;
	}
	return false;
}

int QueryStack::size() const
{ return items.size(); }

void  QueryStack::dump()  
{
	printf("==============================\n");
	for(auto e : items)
	{
		printf("------------------\n");
		e.b1->dump("  ");
		e.b2->dump("  ");
	}
	printf("==============================\n");
}