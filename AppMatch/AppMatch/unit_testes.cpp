//Todos os testes da unidade ligados a linguagem


#include <string>
#include "Parser.hpp"
#include "CBlockInterpreterRuntime.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


class  LTest
{
public:
	std::string buffer;
	//carrega o arquivo com os testes
	LTest(std::string filename)
	{
		auto f = fopen(filename.c_str(), "r");
		if (f != nullptr)
		{
			fseek(f, 0, SEEK_END);
			long fsize = ftell(f);
			fseek(f, 0, SEEK_SET);  //same as rewind(f);

			char *s = static_cast<char*>(malloc(fsize + 1));
			fread(s, fsize, 1, f);
			fclose(f);
			s[fsize] = 0;

			buffer = std::string(s);
		}
	}


};


class runTeste
{
	//executa os testes dentro da propria linguagem . se alguem falhar, execute no framework


	runTeste( LTest teste )
	{
		Interpreter::HBlockInterpreter interpreter = std::make_shared<Interpreter::CBlockInterpreter>();
		CParser parse;
		interpreter->execute_init(NSParser::ParseText::parser_text(&parse,  teste.buffer, true));

		//dentro do intepreter ha asserts , execute um por um

		//std::list<HBlockAssert>  assert_list = interpreter.get_asserts();
		//for(auto a: assert_list)
		//{
		//	interpreter.call_assert(a);
		//}

		
	}

	runTeste( std::string filename):runTeste(LTest(filename))
	{
		
	}

};