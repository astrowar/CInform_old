 
#pragma once

#ifndef CBLOCKNUMBER_H
#define CBLOCKNUMBER_H

#include "BlockInterpreter.hpp"

namespace CBlocking
{

	class CBlockNumber  //number se refere sempre a uma instancia do Kind chamado number  : public CBlockValue
	{
	public:
		CBlockNumber() {}


	};
	using HBlockNumber = std::shared_ptr<CBlockNumber>;



	class CBlockIntegerNumber     // default Class ??  : public CBlockNumber
	{
	public:
		CBlockIntegerNumber(int _value) :value(_value) {}
		int value;
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockIntegerNumber; }
	};
	using HBlockIntegerNumber = std::shared_ptr<CBlockIntegerNumber>;



	class CBlockFactionalNumber  : public CBlockNumber
	{
	public:
		CBlockFactionalNumber(float _value) :value(_value) {}
		float value;
		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockFactionalNumber; }
	};



	using HBlockFactionalNumber = std::shared_ptr<CBlockFactionalNumber>;

}


#endif