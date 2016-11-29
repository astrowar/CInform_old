#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testValues_1()
{
	
	// Values Testes

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

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
	auto e = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of ice cube ", ISLOG), nullptr);
	auto ev = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of apple  ", ISLOG), nullptr);

	assert(e != nullptr);
	assert(ev != nullptr);
	

	e->dump("");
	ev->dump("");

	return;


}

void testValues_2() //numeric values
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string s_price = R"(

The current size is a number that varies
current size is 20
device is a kind
battery is a device
The battery has a number called charge

)";


	interpreter->execute_init(ParseText::parser_text(&parse,s_price, ISLOG));
	auto ev = interpreter->exec_eval(Expression::Parser_Expression(&parse,"current size  ", ISLOG), nullptr);
	auto ev2 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"charge of battery  ", ISLOG), nullptr);
	auto ev3 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"list of thing   ", true), nullptr);

	assert(ev != nullptr);
	assert(ev2 != nullptr);
	ev->dump("");
	ev2->dump("");
	ev3->dump("");
	return;

}

void testValues_all()
{
	//testValues_1();
	testValues_2();
}