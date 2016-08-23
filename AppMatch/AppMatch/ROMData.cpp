#include "ROMData.h"

#include "BlockInterpreter.h"
#include <iostream>

ROMData::ROMData(int fields): id(fields)
{
	 
	cs1 = make_string("empty");
	slot = 0;
	data = std::vector<int>();
}


ROMData::~ROMData()
{
	 
}

void ROMData::aStore()
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive archive(os);
		 
	ROMData &r = *this;
	archive(r);

}

void ROMData::aLoad()
{
	std::ifstream os("out.cereal", std::ios::binary);
	cereal::BinaryInputArchive  archive(os);

	ROMData &r = *this;
	archive(r);

}


    