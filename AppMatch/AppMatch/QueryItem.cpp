// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "BlockInterpreter.hpp"
#include  "QueryStack.hpp"

 
using namespace CBlocking;


 

void QueryStack::addQuery(string vb, HBlock b1, HBlock b2) {
	items.push_back(QueryItem(vb, b1, b2));
}

void QueryStack::addQuery(string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2)
{
	itemsRoute.push_back(QueryItemRoute(_verb, route_object_ptr, b1, b2));
}


bool QueryStack::isQuery(string _verb, HBlock b1, HBlock b2)
{
	for (auto &q : items) {
		if ((q.verb  == _verb) && (q.b1->isSame(b1.get(), q.b1.get())) && q.b2->isSame(q.b2.get(), b2.get())) return true;
	}
	return false;
}

bool QueryStack::isQuery(string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2)
{
	for (auto &q : itemsRoute) 
	{
		if ((q.verb == _verb) && (q.routeObject->isSame(route_object_ptr.get(), q.routeObject.get())) && (q.b1->isSame(b1.get(), q.b1.get())) && q.b2->isSame(q.b2.get(), b2.get())) return true;
	}
	return false;

}

int QueryStack::size() const
{ return items.size() ; }

void  QueryStack::dump()  
{
	printf("==============================\n");
	for(auto e : items)
	{
		printf("------------------\n");
		e.b1->dump("  ");
		e.b2->dump("  ");
	}
	printf("\n");

	for (auto e : itemsRoute)
	{
		printf("------------------\n");
		e.routeObject->dump("  ");
		e.b1->dump("  ");
		e.b2->dump("  ");
	}
	printf("==============================\n");
}




std::unique_ptr<QueryStack>  generateNextStack( QueryStack  *stk_in, string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2)
{	
	std::unique_ptr<QueryStack> stk_unique = nullptr;

	if (stk_in != nullptr)
	{
		if (stk_in->isQuery(_verb, route_object_ptr , b1, b2))
		{
			return nullptr;
		}
		stk_unique = std::make_unique<QueryStack>(*stk_in);
	}
	else
	{
		stk_unique = std::make_unique<QueryStack>();

	}

	QueryStack *stk = stk_unique.get();
	stk->addQuery(_verb, route_object_ptr, b1, b2);
	return stk_unique;
}