#pragma once
#ifndef CBLOCKSTORE_H
#define CBLOCKSTORE_H


#include "BlockInterpreter.hpp"
 
#include <BlockInstance.hpp>
 
#include <CBlockRelation.hpp>
 

 

class CStore
{

 

 


	CBlocking::HBlockNoum copy_cell(CBlocking::HBlockNoum n);
	CBlocking::HBlockKindValue copy_cell(CBlocking::HBlockKindValue n);
	 
	CBlocking::HBlockKind  copy_cell(CBlocking::HBlockKind n);
	HVariableSlot copy_cell(HVariableSlot n);
	HVariableNamed copy_cell(HVariableNamed n);
	CBlocking::HBlockInstance copy_cell(CBlocking::HBlockInstance n);

	CBlocking::HBlockProperty  copy_cell(CBlocking::HBlockProperty n);
	CBlocking::HBlockRelationInstance copy_cell(CBlocking::HBlockRelationInstance n);


public:
	virtual ~CStore()
	{
	}

	CBlocking::HBlock copy_cell(CBlocking::HBlock n);
};

 

#endif
