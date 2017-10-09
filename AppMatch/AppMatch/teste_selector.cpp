#include "BaseTest.hpp"
#include <cassert>
using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeSelector_1()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string slong = R"(
room is an kind
a room can be lit or dark
thing is an kind
stucking relates (a thing ) to another
inner relates (a thing ) to (a room)
garden is a room 
hall is a room
cave is a room
machine cauderon is a kind of room
cave is dark
hall is dark 
garden is lit

the verb ( stuck to ) implies the stucking relation
the verb ( in ) implies the inner relation
coil is a thing
box is a thing
jar is a thing
coil is stuck to box 
box is in hall
jar is in garden
cauderon beta is a machine cauderon
)";

	
	interpreter->execute_init(ParseText::parser_text(&parse,slong, ISLOG));

	auto sentence_0 = "the coil is stuck to box ";
	auto sentence_1 = "the coil is stuck to a thing ";
    auto sentence_2 = "the coil is stuck to a thing which is in  (a room called the next room )";
	auto sentence_3 = "the coil is stuck to ( (a thing called owner ) which is not in garden )";
	auto sentence_4 = "the coil is stuck to (a thing which is in  ( ( a room called the next room ) which is not the garden ) )";


	//f_eval(" a thing which is in  (a room called the next room ) ")->dump("E ");

	auto p = Expression::Parser_Expression(&parse, "  ( a room called the next room ) which is not the garden   ", true);
 

	f_eval("  ( (a thing called owner ) which is in lit machine cauderon  )   ")->dump("E ");
	//f_eval(" ( ( a room called the next room ) which is lit)  ")->dump("E ");
	f_eval("  ( a room called the next room ) which is lit  and  is not  hall  ")->dump("E ");
	f_eval(" box ")->dump("G ");
 



	return;
}

void testeSelector_all()
{
	
	testeSelector_1();
}