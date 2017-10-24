#pragma once
  
#ifndef CBLOCKCOMPOSITION_H
#define CBLOCKCOMPOSITION_H

#include "BlockInterpreter.hpp"

namespace CBlocking
{
	class CBlockCompostionPhrase :  public CBlock
	{
	 
	 
		BlockType   type() override
		{
			return BlockType::BlockCompostionPhrase;
		}
		void dump(string ident) override;
	};

}
#endif