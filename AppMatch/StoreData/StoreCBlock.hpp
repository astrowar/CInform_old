#pragma once
#ifndef CBLOCKSTORE_H
#define CBLOCKSTORE_H


#include "BlockInterpreter.hpp"
#include <map>
#include <BlockInstance.hpp>
#include <condition_variable>
#include <CBlockRelation.hpp>
#include <condition_variable>

using   iref  = int64_t;

class CStore
{

	std::map<CBlocking::CBlock*, CBlocking::CBlock*>  _copy;
	std::map<CBlocking::HBlock, CBlocking::HBlock>  hcopy;
	std::map<CBlocking::HBlock, bool>  exist;

	CBlocking::HBlock get_copy(CBlocking::HBlock org);
	// original -> copia
	CBlocking::CBlock* get_copy(CBlocking::CBlock *org);
	CBlocking::HBlock CStore::exist_copy(CBlocking::HBlock org);


	CBlocking::HBlockNoum copy_cell(CBlocking::HBlockNoum &n);
	CBlocking::HBlockKindValue copy_cell(CBlocking::HBlockKindValue& n);
	 
	CBlocking::HBlockKind  copy_cell(CBlocking::HBlockKind &n);
	HVariableSlot copy_cell(HVariableSlot &n);
	HVariableNamed copy_cell(HVariableNamed& n);
	CBlocking::HBlockInstance copy_cell(CBlocking::HBlockInstance& n);

	CBlocking::HBlockProperty  copy_cell(CBlocking::HBlockProperty &n);
	CBlocking::HBlockRelationInstance copy_cell(CBlocking::HBlockRelationInstance& n);


public:
	virtual ~CStore()
	{
	}

	CBlocking::HBlock copy_cell(CBlocking::HBlock& n);
};

 

#endif
