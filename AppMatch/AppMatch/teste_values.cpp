#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testValues_1()
{
	
	// Values Testes

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };
	 
	string s_heat = R"(
thing is a kind 
ice cube is a thing
Heat is a kind of value
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing has a heat 
The heat of a thing is usually room temperature
apple is a thing
  
)";
	 
	interpreter->execute_init(ParseText::parser_text(&parse, s_heat, true));
	f_eval(" heat of ice cube  ")->dump("R ");
	f_eval(" heat of apple ")->dump("R ");

	assert(f_is("heat of apple   is  room temperature "));
	return;
}

void testValues_2() //numeric values
{
 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string s_cc = R"(
The current size is a number that varies
current size is 20
device is a kind
battery is a device
The battery has a number called charge
  
)";

	interpreter->execute_init(ParseText::parser_text(&parse, s_cc, true));
 
	
	f_eval(" current size  ")->dump("R ");
	f_eval(" list of thing  ")->dump("R ");

	assert(f_is("heat of apple   is  room temperature, warm "));
	return;

}

void testValues_all()
{
	testValues_1();
	//testValues_2();
}