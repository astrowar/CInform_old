#include "BlockInterpreter.h"
#include  "QueryStack.h"

 

 

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
		if ((q.verb  == _verb) && (q.b1 == b1) && (q.b2 == b2)) return true;
	}
	return false;
}
