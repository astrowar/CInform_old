#pragma once
#include "BlockInterpreter.hpp"

class QueryItem {
public:
	QueryItem(string  _verb,  CBlocking::HBlock b1, CBlocking::HBlock b2)
		:
		verb(_verb),
		b1(b1),
		b2(b2) {
	}
	string verb;
	CBlocking::HBlock b1;
	CBlocking::HBlock b2;

};
class QueryStack {
	std::list<QueryItem> items;
public:
	void addQuery(CBlocking::HBlockVerb _verb, CBlocking::HBlock b1, CBlocking::HBlock b2);
	void addQuery(string vb, CBlocking::HBlock b1, CBlocking::HBlock b2);
	bool isQuery(CBlocking::HBlockVerb _verb, CBlocking::HBlock b1, CBlocking::HBlock b2);
	bool isQuery(string _verb, CBlocking::HBlock b1, CBlocking::HBlock b2);
	int size() const;
	void dump();
};