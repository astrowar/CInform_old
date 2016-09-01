#pragma once
 



class CRunLocalScope	 
{
public: 

	std::list< std::pair<string, HBlock> > locals;
	CRunLocalScope()
	{
		
	}

	void dump(string ident);
};

 
using HRunLocalScope = std::shared_ptr<CRunLocalScope>;



class CExecutionBlock
{
public:

	HRunLocalScope locals;
	HBlock block;
	CExecutionBlock(HRunLocalScope _locals,  HBlock _block  ): locals(_locals),block(_block)
	{

	}
	void dump(string ident) const;
};

using HExecutionBlock = std::shared_ptr<CExecutionBlock>;