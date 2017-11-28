#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;

#include <stdio.h>
#include <stdlib.h>

string load_file(string filename )
{
	FILE *f = fopen(filename.c_str(), "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *a = (char*)malloc(fsize + 1);
	fread(a, fsize, 1, f);
	fclose(f);

	a[fsize] = 0;
	return std::string(a);
}

void testeGM_1()
{
	// testes GM sao grand major. testam a engine como um todo

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };


	std::string file_contents = load_file("teste_1.txt");
	auto p_result = ParseText::parser_text(&parse, file_contents, true);
	interpreter->execute_init(p_result);

	auto x1 = f_is("location is garden");
	auto x2 = f_is("location is adjacent");

	return;

}


void testeGM_all()
{
	testeGM_1();

}