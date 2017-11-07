#include "BaseTest.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeParser_phase1()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
color is an kind of value
direction is an kind of value
north is a direction
south is a direction

red is a color
blue is a color

to decide what color is double (a color called N) : 
   decide on red

to dig ( direction called eastward) until (direction called northward ): 
   try say_text (text digging directions )

to dig ( color called X) until (color called Y ): 
   try say_text (text digging colors)



to decide which text is (text called T) repeated (a color called C) times: 
   decide on ( text What ? )


)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));


	f_now("dig north until south  ");
	f_now("dig red until red  ");
	//f_is("putting is an action  applying to (  thing  and   container ) ");

	return;
}


void testePhases_all()
{
	testeParser_phase1();
}