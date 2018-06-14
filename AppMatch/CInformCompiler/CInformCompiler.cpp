// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


// CInformCompiler.cpp : Defines the entry point for the compiler front end.
 

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include "PARSER.HPP"
#include "sharedCast.hpp"
#include "save_ctx.hpp"

using namespace std;

std::string load_file_c(string filename)
{
	FILE *f = fopen(filename.c_str(), "rb");
	if (f == nullptr)
	{
		printf("Error , file not found \n");
		return "";
	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *a = (char*)malloc(fsize + 1);
	fread(a, fsize, 1, f);
	fclose(f);

	a[fsize] = 0;
	return std::string(a);
}



std::vector<std::string> remove_options(std::vector<std::string> va)
{
	std::vector<std::string> ret;
	size_t n = va.size();

	for(int i =0 ; i< n;++i)
	{
		if( va[i][0] != '-')
		{
			ret.push_back(va[i]);
		}
	}
	return ret;

}

HBlockComandList  compile_files(std::vector<std::string> files)
{
	HBlockComandList ret = nullptr;
	NSParser::CParser parse;
	for (auto f : files)
	{
		const std::string file_contents = load_file_c(f);
		const CBlocking::HBlock p_result = NSParser::ParseText::parser_text(&parse, file_contents, false);
		if (p_result == nullptr)
		{
			return nullptr;
		}
		HBlockComandList cont_block = DynamicCasting::asHBlockComandList(p_result);
		if (cont_block !=nullptr)
		{
			if (ret == nullptr) { ret = cont_block; }
			else
			{
				ret->lista.insert(ret->lista.end(), cont_block->lista.begin(), cont_block->lista.end());
			}
		}
	}
	return ret;
}


void  write_bytecode(HBlockComandList lines, std::string filename)
{
	SaveContext ctx(filename);
	save_CBlock(lines, &ctx);  
	
	FILE *f = fopen(filename.c_str(), "w");
	fprintf(f,"%s \n", ctx.data.c_str());
	fclose(f);
	
}


int main(int argc, char **argv)
{
	if (argc < 1 )
	{
		printf("no input files \n"); return 0;
	}

	std::vector<std::string> vargs;
	for(int i = 1 ; i< argc ;++i)
	{
		vargs.push_back(std::string(argv[i]));
		printf("%s.\n", vargs.back().c_str());
	}

	//remove as opcoes .. deve restar apenas os filenames
	std::vector<std::string> files = remove_options(vargs);

	auto hcc = compile_files(vargs);
	write_bytecode(hcc, "bytecode.txt");

    return 0;
}

