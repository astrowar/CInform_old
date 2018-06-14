// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "BlockInterpreter.hpp"
#include  "QueryStack.hpp"

 
using namespace CBlocking;


namespace QueryStacking {

	bool QueryStack::contains_phase_execution(CBlocking::HBlock action, CBlocking::HBlock b1, CBlocking::HBlock b2)
	{

		for (auto &e : execution_stack)
		{
			if (CBlock::isSame(e[0].get(), action.get()))
			{

				if ((e[1] == nullptr && b1 == nullptr) || CBlock::isSame(e[1].get(), b1.get()))
				{
					if ((e[2] == nullptr && b2 == nullptr) || CBlock::isSame(e[2].get(), b2.get()))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	void QueryStack::add_phase_execution(CBlocking::HBlock action, CBlocking::HBlock b1, CBlocking::HBlock b2)
	{
		std::array<HBlock, 3> x;
		x[0] = action;
		x[1] = b1;
		x[2] = b2;
		execution_stack.push_back(x);
	}

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
			if ((q.verb == _verb) && (q.b1->isSame(b1.get(), q.b1.get())) && q.b2->isSame(q.b2.get(), b2.get())) return true;
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
	{
		return items.size();
	}

	void  QueryStack::dump()
	{
		printf("==============================\n");
		for (auto e : items)
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




	std::unique_ptr<QueryStack>  generateNextStack(QueryStack  *stk_in, string _verb, CBlocking::HBlock route_object_ptr, CBlocking::HBlock b1, CBlocking::HBlock b2)
	{
		std::unique_ptr<QueryStack> stk_unique = nullptr;

		if (stk_in != nullptr)
		{
			if (stk_in->isQuery(_verb, route_object_ptr, b1, b2))
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



	std::unique_ptr<QueryStack>  generateNextStack(QueryStack  *stk_in)
	{
		std::unique_ptr<QueryStack> stk_unique = nullptr;

		if (stk_in != nullptr)
		{
			stk_unique = std::make_unique<QueryStack>(*stk_in);
		}
		else
		{
			stk_unique = std::make_unique<QueryStack>();
		}

		QueryStack *stk = stk_unique.get();

		return stk_unique;
	}

}