#pragma once
#include "BlockInterpreter.h"

class QueryItem {
public:
	QueryItem(string  _verb,  HBlock b1, HBlock b2)
		:
		verb(_verb),
		b1(b1),
		b2(b2) {
	}
	string verb;
	HBlock b1;
	HBlock b2;

};
class QueryStack {
	std::list<QueryItem> items;
public:
	void addQuery(HBlockVerb _verb, HBlock b1, HBlock b2);
	void addQuery(string vb, HBlock b1, HBlock b2);
	bool isQuery(HBlockVerb _verb, HBlock b1, HBlock b2);
	bool isQuery(string _verb, HBlock b1, HBlock b2);
};