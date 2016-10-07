#pragma once
#include <string>
#include <map>
#include <fstream>


class CBlock;

#include "CBase.h"

 


class ROMData
{
 
public:
	
	std::vector<int> data;
	int slot;
	int32_t id;
	HTerm cs1;

	ROMData(int fields );
	virtual ~ROMData();
	 


	void aStore();

	void aLoad();
};






