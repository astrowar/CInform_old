#include  "StoreCBlock.hpp"
#include "sharedCast.hpp"
#include <cstring>


using namespace CBlocking;
using namespace DynamicCasting;




 


 
CBlocking::HBlockNoum CStore::copy_cell(CBlocking::HBlockNoum   n)
{
	return std::make_shared<CBlockNoum>(n->named);
}
 
 
 
CBlocking::HBlockKindValue CStore::copy_cell(CBlocking::HBlockKindValue   n)  
{
	return std::make_shared<CBlockKindValue>(n->named);
}



CBlocking::HBlockKind CStore::copy_cell(CBlocking::HBlockKind  n)
{
	return n;
}

 

HVariableSlot CStore::copy_cell(HVariableSlot n)
{
	  
	if (auto  nenum = asHVariableSlotEnum(n))
	{	
		auto nss = std::make_shared<CVariableSlotEnum>(nenum->valueDefinition);
		nss->value = copy_cell(nenum->value);
		return nss;
	}

	if (auto  nbool = asHVariableSlotBool(n))
	{
		auto nss = std::make_shared<CVariableSlotBool>(nbool->valueDefinition);
		nss->value = nbool->value ;
		return nss;
	}

	return n;
}


HVariableNamed CStore::copy_cell(HVariableNamed n)
{
	auto nvalue = copy_cell(n->value);	
	return std::make_shared<CVariableNamed>( n->name, n->kind, nvalue );

}

CBlocking::HBlockInstance CStore::copy_cell(CBlocking::HBlockInstance  n)
{
	HBlockInstance ns = std::make_shared<CBlockInstance>(n->id, n->baseKind );
	for(auto  q : n->anomimousSlots)
	{
		HVariableSlot qs = copy_cell(q);
		ns->anomimousSlots.push_back(qs);
	}

	for (auto q : n->namedSlots)
	{
		HVariableNamed qs = copy_cell(q);
		ns->namedSlots.push_back(qs);
	}

	return ns;
}

CBlocking::HBlockProperty CStore::copy_cell(CBlocking::HBlockProperty  n)
{

	auto n_prop = copy_cell(n->prop);
	auto n_obj = copy_cell(n->obj);

	HBlockProperty ns = std::make_shared<CBlockProperty>(n_prop,n_obj);
	return ns;
}


CBlocking::HBlockRelationInstance CStore::copy_cell(CBlocking::HBlockRelationInstance  n)
{
	auto n_value_1 = copy_cell(n->value1 );
	auto n_value_2 = copy_cell(n->value2 );
	HBlockRelationInstance ns = std::make_shared<CBlockRelationInstance>(n->relation, n_value_1, n_value_2);
	return ns;
}

HBlock CStore::copy_cell(HBlock  n)
{

	if (auto p = asHBlockProperty(n)) return copy_cell(p);
	if (auto p = asHBlockInstance(n)) return copy_cell(p);
	if (auto p = asHVariableNamed(n)) return copy_cell(p);
	if (auto p = asHBlockRelationInstance(n)) return copy_cell(p);

 
	
	return n;
}
