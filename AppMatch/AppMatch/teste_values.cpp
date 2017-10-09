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

	string s_heat = R"(
thing is a kind
 
ice cube is a thing


Heat is a kind of value
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing has a heat 
The heat of a thing is usually room temperature

apple is a thing
  
)";
	 

	interpreter->execute_init(ParseText::parser_text(&parse,s_heat, ISLOG));
	auto e = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of ice cube ", ISLOG), nullptr, nullptr);
	auto ev = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of apple  ", ISLOG), nullptr, nullptr);

	assert(e != nullptr);
	assert(ev != nullptr);
	

	e->dump("");
	ev->dump("");

	return;


}

 

void testValues_1a()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string ss1 =
		R"(

thing is a kind 
ice cube is a thing
Heat is a kind of value
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing has a heat 
The heat of a thing is usually room temperature
apple is a thing

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	//f_eval("heat of ice cube  ")->dump("E ");
	assert(f_is("heat of ice cube is room temperature "));
	f_now("heat of ice cube is frosty ");
	assert(f_is("heat of ice cube is frosty "));
 
}
void testValues_2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string ss1 =
		R"(

device is a kind
battery is a device
The battery has a number called charge
)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("charge of battery")->dump("E ");
	//assert(f_is("heat of ice cube is room temperature "));
	//f_now("charge of battery is 20 ");
	//assert(f_is("heat of ice cube is frosty "));
	
}

void testValues_3()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string ss1 =
		R"(
direction is a kind of value
The direction are north, south , west and east
prevailing wind is a direction that varies
the prevailing wind is south
the prevailing wind is always west

the destination is always north

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("prevailing wind ")->dump("E ");
	f_eval("destination ")->dump("E ");
	//assert(f_is("heat of ice cube is room temperature "));
	f_now("prevailing wind is beta ");
	//assert(f_is("heat of ice cube is frosty "));

}


void testValues_all()
{
	//testValues_1();
	//testValues_2();
	testValues_3();
	//testValues_1();
	//testValues_2();
}