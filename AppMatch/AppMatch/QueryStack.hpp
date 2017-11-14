#pragma once
#include "BlockInterpreter.hpp"
#include <array>


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


class QueryItemRoute  {
public:
	QueryItemRoute(string  _verb,  CBlocking::HBlock _routeObject , CBlocking::HBlock b1, CBlocking::HBlock b2)
		:
		verb(_verb), 
		routeObject(_routeObject),
		b1(b1),
		b2(b2) {
	}
	string verb;
	CBlocking::HBlock routeObject;
	CBlocking::HBlock b1;
	CBlocking::HBlock b2;

};




class QueryStack {
	std::list<QueryItem> items;
	std::list<QueryItemRoute> itemsRoute;
	std::list<std::array<CBlocking::HBlock, 3>> execution_stack;

public:
	
	bool contains_phase_execution(CBlocking::HBlock action, CBlocking::HBlock b1, CBlocking::HBlock b2);
    void add_phase_execution(CBlocking::HBlock action, CBlocking::HBlock b1, CBlocking::HBlock b2);

	void addQuery(string vb, CBlocking::HBlock b1, CBlocking::HBlock b2);	 
	void addQuery(string _verb, CBlocking::HBlock route_object_ptr , CBlocking::HBlock b1, CBlocking::HBlock b2);


	bool isQuery(string _verb, CBlocking::HBlock b1, CBlocking::HBlock b2);
	bool isQuery(string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2);


	int size() const;
	void dump();
};

//funcao retorna null se nao poder gerar uma nova stack 
std::unique_ptr<QueryStack>  generateNextStack(QueryStack *actual , string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2) ;
std::unique_ptr<QueryStack>  generateNextStack(QueryStack  *stk_in);