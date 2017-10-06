
#include "BaseTest.hpp"
#include <cassert>
#include <functional>


using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;



//Basic Assertations

void testeParser_1() {
    
}

void testeParser_2_1() {



	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;	
	std::function<bool(std::string )> f_is = [&](std::string a ) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr,nullptr ).result == QEquals; };


	string ss1 =
		R"(

 thing is an kind
 book is a kind of thing
 magic object is a kind 
 special book is a kind of book 
 special book is a kind of magic object
 diary is a special book

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	assert(f_is("special book is a kind "));
	assert(f_is("special book is book "));
	assert(f_is("diary is thing"));
	assert(f_is("diary is book"));



}

   

 
 

void testeParser_2_2() {
    


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };

	string ss1 =
		R"(

 thing is an kind
 kelement is a kind

 fire is a kelement
 air is a kelement

 thing has a kelement called element
 
 arrow is a thing
 paper is a thing
 slime  is a thing

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("element of paper  ")->dump("E ");
	assert(f_is("element of paper is nothing "));
	interpreter->execute_now(Statement::Parser_Stmt(&parse, " element of paper is fire ", false));
	assert(f_is("element of paper is fire "));
	
	interpreter->execute_now(Statement::Parser_Stmt(&parse, " element of paper is nothing ", false));
	assert(f_is("element of paper is fire "));

	interpreter->execute_now(Statement::Parser_Stmt(&parse, " element of arrow is slime ", false));
	assert(!f_is("element of arrow is slime "));



 //   interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
 //   interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a kind of thing ", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"kelement is a kind  ", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"fire is a kelement ", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"air is a kelement ", ISLOG));

 //   interpreter->execute_init(Statement::Parser_Stmt(&parse,"book  can be normal , huge or  small", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing has a thing called element", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"fire is a kelement ", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"air is a kelement ", ISLOG));
 //
	//interpreter->execute_init(Statement::Parser_Stmt(&parse," element of thing is usually fire ", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse," element of book is usually air ", ISLOG));

 //   interpreter->execute_init(Statement::Parser_Stmt(&parse,"book can be read", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is a book", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"rock is a thing", ISLOG));

 // 
	//QueryResultContext q_true = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), 		std::make_shared<CBlockNoum>("read"));
	//assert(q_true.result == QEquals);

 //   {
 //       string phase_1 = "diary is not read ";
 //       auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
 //       
 //       interpreter->execute_init(res);
 //   }

 //   interpreter->dump_instance("diary" );

	//QueryResultContext q_false_1 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("read"));
	//QueryResultContext q_false_2 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("huge"));
	//QueryResultContext q_false_2n = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("normal"));


	//assert(q_false_1.result == QNotEquals);
	//assert(q_false_2.result == QNotEquals);
	//assert(q_false_2n.result == QEquals);

 //   logMessage( "Done" );

	////interpreter->execute_init(Statement::Parser_Stmt(&parse,"element of  diary is air "));

	//auto propV =std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("diary"));
	//QueryResultContext q_true_2 = interpreter->query_is_extern(propV,	std::make_shared<CBlockNoum>("air"));
	//assert(q_true_2.result == QEquals);
 //   
	//auto propT = std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("rock"));
	//QueryResultContext q_true_3 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("air"));
	//QueryResultContext q_true_4 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("fire"));
	//QueryResultContext q_true_5 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("water"));

	//assert(q_true_3.result == QEquals);
	//assert(q_true_4.result == QNotEquals);
	//assert(q_true_5.result == QNotEquals);
 //   logMessage( "Done" );
 //   return;
}



void testeParser_2_3() {



	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false) ); };
	 

	string ss1 =
		R"(

 thing is an kind
 kelement is a kind

 fire is a kelement
 air is a kelement
 water is a kelement

 thing has a kelement called element
 element of thing is usually air 

 arrow is a thing
 paper is a thing
 slime  is a thing

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("element of paper  ")->dump("E ");
	assert(f_is("element of paper is air "));

	f_now( " element of paper is fire " );
	assert(f_is("element of paper is fire "));

	f_now(" element of arrow is water" );
	f_now(" element of paper is  element of arrow " );
	assert(f_is("element of paper is water "));
}

void testeParser_2_4()
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse;
    std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
    std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
    std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false) ); };

    string ss1 =
            R"(

 thing is an kind

 thing can be portable or fixed

 arrow is a thing
 paper is a thing
 slime  is a thing

 arrow is portable
 slime is never fixed

)";

    interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
    f_eval("arrow is portable  ")->dump("E ");
    assert(f_is("arrow is portable "));


    assert(f_is("paper is portable "));

    f_now( " paper is fixed " );
    assert(f_is("paper is fixed "));
    f_now( " paper is not fixed " );
    assert(f_is("paper is portable "));

    f_now( " slime is fixed " );
	// assert(f_is("slime is portable "));  Forbiden setting is not taken effect in executio engine


}


void testeParser_2_5()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"(
thing is an kind
the treasure  is a thing that varies
arrow is a thing
bow is a thing

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("treasure  ")->dump("E ");
	assert(f_is("treasure is nothing "));
	f_now(" treasure is arrow ");
	assert(f_is("treasure is arrow "));
	
	// assert(f_is("slime is portable "));  Forbiden setting is not taken effect in executio engine


}

void testeParser_2_6()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"(
heat is a kind of value
 
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing is an kind
thing has a heat
The heat of a thing is usually room temperature
the treasure  is a thing that varies
coin is a thing
ruby is a thing
)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("treasure  ")->dump("E ");
	assert(f_is("heat of ruby is  room temperature "));
	f_now(" treasure is ruby ");
	assert(f_is("heat of treasure is  room temperature "));  
}
 
void testeParser_2_7()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"(
heat is a kind of value 
colour is a kind of value
red, green and blue are colour

thing is an kind
blood is a thing
thing has a colour
colour of blood is red
)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("red  ")->dump("E ");	
	assert(f_is("red is colour "));
	assert(f_is("red is blue ") ==false );
	assert(f_is("red is not blue "));
}



void testeParser_2()
{
  // testeParser_2_1();
  // testeParser_2_2();
  // testeParser_2_3();
  // testeParser_2_4(); // anonimous properties
  // testeParser_2_5(); // variables
  // testeParser_2_6(); //kind values
	 testeParser_2_7(); //kind values 
}