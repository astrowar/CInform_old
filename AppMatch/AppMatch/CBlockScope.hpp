#pragma once
 



class CRunLocalScope	 
{
public: 

	std::list< std::pair<string, HBlock> > locals;
	CRunLocalScope()
	{
		
	}
	CRunLocalScope( std::map<string,HBlock> varMap)
	{
		for( auto &e: varMap)
		{
			locals.push_back(e);
		}
	}

	HBlock resolve(std::string noum)
	{
		for(auto &e:locals )
		{
			if (e.first == noum) return e.second;
		}
		return nullptr;
	}
	void dump(string ident);


	std::shared_ptr<CRunLocalScope> Union(std::shared_ptr<CRunLocalScope> other);
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