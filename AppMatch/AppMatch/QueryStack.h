#pragma once
#include "BlockInterpreter.h"

class QueryItem {
public:
	QueryItem(HBlock b1, HBlock b2)
		: b1(b1),
		b2(b2) {
	}

	HBlock b1;
	HBlock b2;

};
class QueryStack {
	std::list<QueryItem> items;
public:
	void addQuery(HBlock b1, HBlock b2);

	bool isQuery(HBlock b1, HBlock b2);
};