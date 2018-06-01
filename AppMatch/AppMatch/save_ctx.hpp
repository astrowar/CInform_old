

#ifndef SAVE_CTX_HPP
#define SAVE_CTX_HPP
#include "CBlockComposition.hpp"
#include <cstdio>
#include <map>
#include <set>

class SaveContext
{
public:
	std::map<CBlocking::CBlock*, int> locals;
	std::set<CBlocking::CBlock*> locked;
	int current_id;

	FILE *file;
	SaveContext(string filename) :current_id(1)
	{
		file = fopen(filename.c_str(), "w");
	}
	~SaveContext()
	{
		fclose(file);
	}

	SaveContext(const SaveContext&) = delete;


	void write(string s);
	void write(int i);
	void write(float  x);
	void end_line();
};


int  save_CBlock(HBlock x, SaveContext * ctx);
#endif // SAVE_CTX_HPP
