#include "BaseTest.hpp"
#include <cassert>

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
	std::function<bool(std::string, std::string)> f_same = [&](std::string a, std::string b){auto xa =   interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr);	auto xb = interpreter->exec_eval(Expression::Parser_Expression(&parse, b, false), nullptr, nullptr);	return CBlock::isSame(xa.get(), xb.get());	};

	string ss1 =
		R"( 
thing is an kind of entity
keys  is a thing
book  is a thing

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));

	assert(f_same("\"[keys] [is] in  room \""  , "\"keys are in room \""));
	assert(f_same("\"[( book , keys )] [are] items \"", "\"book and keys are items \""));
	assert(f_same("\"keys  [negate open in the future tense from the first person plural] the door\"", "\"keys will not open the door\""));
	assert(f_same("\"[keys] [are] [negate open in the gerund ] the door\"", "\"keys are not opening the door\""));


	f_eval("\"[keys] [is] in room \"")->dump("");
	f_eval("\"[book] [are] in room \"")->dump("");
	f_eval("\"[( book , keys )] [are] items  \"")->dump("");


	f_eval("\"[keys] [are] [negate open in the gerund ] the door\"")->dump("");
	//f_is("putting is an action  applying to (  thing  and   container ) ");

	return;
}



void testeAdaptivePhases_2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, true), nullptr, nullptr); };

	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };
	std::function<bool(std::string, std::string)> f_same = [&](std::string a, std::string b) {auto xa = interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr);	auto xb = interpreter->exec_eval(Expression::Parser_Expression(&parse, b, false), nullptr, nullptr);	return CBlock::isSame(xa.get(), xb.get());	};

	string ss1 =
		R"( 
thing is an kind of entity
keys  is a thing
book  is a thing

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));

	assert(f_same("\"[a book] \"", "\"a book\""));
	assert(f_same("\"[an book] \"", "\"an book\""));
	assert(f_same("\"[the book] \"", "\"the book\""));
	assert(f_same("\"[The book] \"", "\"The book\""));
	assert(f_same("\"[An book] \"", "\"An book\""));


	f_eval("\"[the keys]\"")->dump("");
	f_eval("\"[a book]\"")->dump("");
	f_eval("\"[The keys]\"")->dump("");
	f_eval("\"[an book]\"")->dump("");

	//f_eval("\"[book] [are] in room \"")->dump("");
	//f_eval("\"[( book , keys )] [are] items  \"")->dump("");


	//f_eval("\"[keys] [are] [negate open in the gerund ] the door\"")->dump("");
	//f_is("putting is an action  applying to (  thing  and   container ) ");

	return;
}


void testeAdaptivePhases_3()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, true), nullptr, nullptr); };

	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };
	std::function<bool(std::string, std::string)> f_same = [&](std::string a, std::string b) {auto xa = interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr);	auto xb = interpreter->exec_eval(Expression::Parser_Expression(&parse, b, false), nullptr, nullptr);	return CBlock::isSame(xa.get(), xb.get());	};

	string ss1 =
		R"( 
thing is an kind of entity
 
book  is a thing
 
to say printed name of (an thing called M ):
   say "public name of [M]"

 
)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	
	//f_eval("\"message [danger message]\"")->dump("");	
	//f_eval("\"object = [book]\"")->dump("");
	f_eval("\" [ printed name of book ]\"")->dump("");

	//f_eval("\"[book] [are] in room \"")->dump("");
	//f_eval("\"[( book , keys )] [are] items  \"")->dump("");


	//f_eval("\"[keys] [are] [negate open in the gerund ] the door\"")->dump("");
	//f_is("putting is an action  applying to (  thing  and   container ) ");

	return;
}




void testeAdaptivePhases_all()
{
	//testeAdaptivePhases_1();
	//testeAdaptivePhases_2();
	testeAdaptivePhases_3();
}