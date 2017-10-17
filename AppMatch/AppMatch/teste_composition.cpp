#include "BaseTest.hpp"
#include <cassert>
using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeComposition_1()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string slong = R"(
room is an kind
garden is a room
hall is a room
ceils is list of room
)";


	interpreter->execute_init(ParseText::parser_text(&parse, slong, true));

 


	//f_eval(" a thing which is in  (a room called the next room ) ")->dump("E ");

	//auto p = Expression::Parser_Expression(&parse, "  ( a room called the next room ) which is not the garden   ", false);


	f_eval(" ceils   ")->dump("E ");
	f_eval(" ceils is a list of room  ")->dump("E ");
	f_eval(" ceils is a list of K  ")->dump("E ");
	




	return;
}

void testeComposition_all()
{

	testeComposition_1();
}