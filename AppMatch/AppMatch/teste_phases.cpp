#include "BaseTest.hpp"
#include <cassert>

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



void testeParser_phase2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, true), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
brightness is a kind of value
brightness  are guttering, weak, radiant and blazing

To decide if (  X ) is darker than ( Y ) : 
   if X is less than Y : decide on yes
   decide on no

To decide if ( a brightness called X ) is brighter than ( a brightness called Y ) : 
   if X is greater than Y : decide on yes
   decide on no

To decide which  ( X ) is ( P ) of  ( Y ) :    
   decide on weak

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));


	//f_now("dig north until south  ");
	//f_now("dig red until red  ");
	assert(f_is("guttering is brighter than  radiant ") ==false );
	assert(f_is("guttering is darker than  radiant ") );
	assert(f_is("blazing is greater than  weak "));

	f_eval("blazing of  greater ")->dump("" );

	return;
}
void testeParser_phase3()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, true), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
brightness is a kind of value
brightness  are guttering, weak, radiant and blazing
color is a kind of value
color  are red and blue
brightness has a color called colour
colour of radiant is red
To decide which  ( X ) is related ( P )  by  ( Y ) :    
   decide on P of Y

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("related colour by radiant ")->dump("");

	return;
}


void testeParser_phase4()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, true), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
container is an kind of entity
 
to sort (S) in reverse (Z) order :
  try say "sorted [S]"

to sort (list called L):
  say "nada"
 

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("sort \"container\" in reverse kind order ")->dump("");

	return;
}

void testePhases_all()
{
	//testeParser_phase1();
	//testeParser_phase2();
	//testeParser_phase3();
	testeParser_phase4();
}