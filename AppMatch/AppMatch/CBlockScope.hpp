#pragma once
 



class CRunLocalScope	 
{
public: 

	std::list< std::pair<string, CBlocking::HBlock> > locals;
	CRunLocalScope()
	{
		
	}
	CRunLocalScope( std::map<string,CBlocking::HBlock> varMap)
	{
		for( auto &e: varMap)
		{
			locals.push_back(e);
		}
	}

	CBlocking::HBlock resolve(const std::string& noum)
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


HRunLocalScope copy_CRunLocalScope(HRunLocalScope _inn);

class CExecutionBlock
{
public:

	HRunLocalScope locals;
	CBlocking::HBlock block;
	CExecutionBlock(HRunLocalScope _locals,  CBlocking::HBlock _block  ): locals(_locals),block(_block)
	{

	}
	void dump(string ident) const;
};


HRunLocalScope newScope(HRunLocalScope oldEntry, HRunLocalScope headerEntry);
using HExecutionBlock = std::shared_ptr<CExecutionBlock>;


