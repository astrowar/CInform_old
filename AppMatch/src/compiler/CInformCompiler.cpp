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
#include "Parser\Parser.hpp"
#include "sharedCast.hpp"
#include "save_ctx.hpp"

using namespace std;

using namespace CBlocking;



class CompilerFlags
{
public:
	std::map<std::string,bool> flags;
	std::map<std::string, string> options;

	std::map<std::string, string> flags_desc;
	std::map<std::string, string> options_desc;

	std::vector<std::string> files;
	CompilerFlags()
	{
		options_desc["output"] = "Place output in file ";
		flags_desc["v"] = "Print the commands executed to run the stages of compilation";
		flags_desc["c"] = "Compile  the source files";
		options["output"] = "bytecode.txt";
	}

	void setFlag(string name, bool value)
	{
		flags[name] = value;
	}

	void setOption(string name, string value)
	{
		options[name] = value;
	}

	void printDesc()
	{
		for (auto kv : flags_desc)	printf("-%s  : %s \n", kv.first.c_str(), kv.second.c_str());
		for (auto kv : options_desc)	printf("-%s  : %s \n", kv.first.c_str(), kv.second.c_str());
	}
};

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



CompilerFlags process_options(std::vector<std::string> va)
{
	CompilerFlags cflags;
	std::vector<std::string> ret;
	size_t n = va.size();

	for(int i =0 ; i< n;++i)
	{
		if( va[i][0] != '-')
		{
			cflags.files.push_back(va[i]);
		}
		if (va[i] == "-o")
		{
			if (i < n - 1)
			{
				cflags.setOption("output", va[i + 1]);
				i++;
			}
			else
			{
				fprintf(stderr, "missing output argument\n");
				return CompilerFlags();
			}
		}
	}
	return cflags;

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
	 CompilerFlags comp = process_options(vargs);



	if (!comp.files.empty())
	{
		auto hcc = compile_files(comp.files);
		if (hcc != nullptr)hcc->dump("");
		write_bytecode(hcc, comp.options["output"]);
	}
    return 0;
}
