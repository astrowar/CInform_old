#include "BaseTest.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeAdaptivePhases_1()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
 
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
keys  is a thing
book  is a thing

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));


	f_eval("\"[keys] [is] in room \"")->dump("");
	f_eval("\"[book] [are] in room \"")->dump("");

	f_eval("\"[books] [put] in this place \"")->dump("");

	//f_eval("\"keys  [negate disable in the future tense from the first person plural] \"")->dump("");
 

	//f_is("putting is an action  applying to (  thing  and   container ) ");

	return;
}


void testeAdaptivePhases_all()
{
	testeAdaptivePhases_1();
}