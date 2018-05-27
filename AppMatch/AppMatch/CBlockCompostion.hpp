#pragma once
  
#ifndef CBLOCKCOMPOSITION_H
#define CBLOCKCOMPOSITION_H

#include "BlockInterpreter.hpp"

namespace CBlocking
{
	class CBlockCompostionPhrase :  public CBlock
	{ 
	public:
		BlockType   type() override
		{
			return BlockType::BlockCompostionPhrase;
		}
		void dump(string ident) override;
		CBlockCompostionPhrase(){}
	};
	using HBlockCompostionPhrase = std::shared_ptr<CBlockCompostionPhrase>;
}
#endif