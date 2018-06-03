#include "BaseTest.hpp"
#include <cassert>
#include <iostream>
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testedecide_1()//dynamic match
{


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };



	 
	string ss1 =
		R"(
 
thing is a kind of entity
book is a thing
diary is a thing 
to decide what (thing) is (the best book) : diary 
 

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("best book ")->dump("E ");
	//f_eval("destination ")->dump("E ");
	assert(f_is("best book is diary"));
	//f_now("prevailing wind is beta ");
	//assert(f_is("prevailing wind  is west "));

	return;
}





 


void testedecide_2()//dynamic match
{
	 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); }; 
	string ss1 =
		R"(
 
thing is a kind of entity
book is a thing
diary is a thing 
coin is a thing 

atom is a kind of value
silver is an  atom 
gold is an atom 

to decide what (thing) is (the best book) : diary 
 
materiality relates (a thing ) to (an atom )
the verb made of implies the materiality relation

coin is made of silver
 

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval("best book ")->dump("E ");
	//f_eval("destination ")->dump("E ");
	assert(f_is("coin is made of gold") ==false);
	assert(f_is("coin is made of silver")  );
	f_now("coin is made of gold ");
	assert(f_is("coin is made of gold"));

	 
	return;
	 
}


void testedecide_3()//dynamic match
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	{
		auto p = Statement::Parser_Stmt(&parse, "Fanciness relates  ( a thing called X) to (some money called Y)", ISLOG);
	}
	{
		auto p = Statement::Parser_Stmt(&parse, "Fanciness relates  ( a thing called X) to another", ISLOG);
	}
	{
		auto p = Statement::Parser_Stmt(&parse, "Pet-ownership relates various animals to ( a person called the owner)", ISLOG);
	}
	{
		auto p = Statement::Parser_Stmt(&parse, "Fanciness relates  ( a thing called X) to each other in groups", ISLOG);
	}


	std::list<std::string> slist({
		"Marriage relates (a person ) to another",
		"Marriage relates (a person ) to ( another called the spouse )",
		"Revenge relates (a person ) to various people",
		"Pet-ownership relates ( various animals ) to a person",
		"Pet-ownership relates ( various animals ) to ( a person called the owner)",
		"Awareness relates (various people ) to various people",
		"Meeting relates (a people ) to each other",
		"Nationality relates (a people ) to each other in groups"
	});
	for (auto s : slist)
	{
		logMessage(s);
		auto p = Statement::Parser_Stmt(&parse, s, ISLOG);
	}
}

void testedecide_4()// relation When
{


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };
	string ss1 =
		R"(
 
concret thing is a kind of entity
thing is a kind of concret thing
book is a thing
diary is a thing 
coin is a thing 
dagger is a thing 

atom is a kind of value
silver is an  atom 
gold is an atom 


materiality relates ( a concret thing ) to (an atom called material)
the verb ( made of ) implies the materiality relation
coin is made of silver
dagger is made of silver 
to decide if (thing called T ) is grand prize:
   decide on yes

to decide which thing is the grand prized:
   if coin is made of gold:
      decide on coin 
   decide on book
)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval(" material of coin ")->dump("Silver? ");
	assert(f_is("coin is made of nothing"));
	assert(f_is("coin is made of silver") ==false );
	assert(f_is("coin is not made of silver")  );

	assert(f_is("diary is grand prize") );	 
 
	assert(f_is("coin is made of gold") == false);
	
	assert(f_is("material of coin is silver"));
	f_now("coin is made of gold ");
	assert(f_is("coin is made of gold"));
	assert(f_is("grand prize  is coin") ==false );
	//f_eval(" grand prize ")->dump("E ");

	return;


	 
}


void testedecide_5()
{
	string slong = R"(
person is an kind
woman is an kind of person
man is an kind of person
Zora is an woman
Mary is an woman
Bob is a  man
Julian  is a man

language is a kind of value
language are English, Zubian and Perplexish 
speaking relates various ( a person ) to  ( a  language )
the verb  speak  implies the speaking relation


Mary speak Zubian
Bob speak Zubian
Zora speak Perplexish
Julian speak English
 
to decide  if ( person called P1  ) is ( suitable  for  ( person called P2  ) ) :
   if ( P1 speak  ( language called L ) ) and (  P2 speak L)   :
      if  P1 is not P2  :      
        decide on true      
   decide on false
   
 
)";

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(ParseText::parser_text(&parse, slong, ISLOG));


	//  interpreter->exec_eval(Expression::Parser_Expression(&parse, "  Mary is suitable for Bob  ", ISLOG), nullptr,nullptr)->dump("");
	//  interpreter->exec_eval(Expression::Parser_Expression(&parse, "  Bob is suitable for Zora ", ISLOG), nullptr,nullptr)->dump("");
	auto qList = interpreter->exec_eval(Expression::Parser_Expression(&parse, " ( Person called P ) which  is  suitable for Bob  ", ISLOG), nullptr, nullptr);

	//auto qList = interpreter->exec_eval(Expression::Parser_Expression(&parse, " ( Person called P ) which  is  canonical  ", true), nullptr,nullptr);
	qList->dump("");


	//auto qr = interpreter->exec_eval(std::make_shared<CBlockNoumStr>("best person")  ,nullptr);
	//qr->dump("");

	//auto q3 = interpreter->query(Statement::Parser_Stmt(&parse,"best person is Mary  ", ISLOG));
	//assert(q3 == QEquals);

	QueryResultContext q4 = interpreter->query(Statement::Parser_Stmt(&parse, " Mary is suitable for Bob ", ISLOG));
	return;
	assert(q4.result == QEquals);

	QueryResultContext q5 = interpreter->query(Statement::Parser_Stmt(&parse, " Zora is suitable for Bob ", ISLOG));
	assert(q5.result != QEquals);

	QueryResultContext q6 = interpreter->query(Statement::Parser_Stmt(&parse, " Zora is oposite of Mary ", ISLOG));
	assert(q6.result != QEquals);


	return;
}


void testedecide_6()
{
	string slong = R"(
room is an kind

hall is an room
garden is an room
cave is an room
exit is a  room
secret  is a room

connecting relates various ( room ) to various ( room )
the verb connect  implies the connecting relation
the verb lead  implies the dynamic relation
the verb edge to implies the dynamic relation


hall connect garden
garden connect cave
hall connect secret
secret connect exit
 
to decide  if ( room  called R1  ) edge to  ( room called R2  )   :
   if  R2 connect R1 :
       decide on true
   if  R1 connect R2 :
       decide on true
   decide on false 

to decide  if ( room  called R1  ) lead ( room called R2  )   :
   if  R2 edge to  R1 :
       decide on true      
   decide on false
   
 
)";

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(ParseText::parser_text(&parse, slong, true));


	auto q3 = interpreter->query(Expression::Parser_Expression(&parse, " garden lead hall  ", ISLOG), nullptr, nullptr);
	assert(q3.result == QEquals);

	auto q4 = interpreter->query(Expression::Parser_Expression(&parse, "exit lead secret  ", ISLOG), nullptr, nullptr);
	assert(q4.result == QEquals);

	auto q5 = interpreter->query(Expression::Parser_Expression(&parse, "exit lead garden  ", ISLOG), nullptr, nullptr);
	assert(q5.result != QEquals);
}


void testedecide_7() //loop testes
{
	string slong = R"(
room is an kind

hall is an room
garden is an room
cave is an room
exit is a  room
secret  is a room

top is a room
botton is a room
left is a room


ship is a room
island is a room
void is a room

connecting relates various ( room ) to various ( room )
the verb connect  implies the connecting relation
the verb lead  implies the dynamic relation
the verb edge to implies the dynamic relation


hall connect garden
garden connect cave
hall connect secret
secret connect exit
ship connect exit
island connect ship
void connect island

left connect botton
top connect left
 
to decide if (room called Q1) edge to (a room called Q2) :
   if Q1 connect Q2 :
          decide on true
   if Q2 connect Q1 :
          decide on true 
   decide on false
 

to decide if (a room called R1) lead (a room called R2) :
   if R1 is R2 :      
      decide on false   
   if R1 edge to R2 :
      decide on true
   for each ( a room called Z ) :      
      if R1 edge to Z :
         if Z edge to R2 :
            decide on true             
   decide on false   

liste is  an action applying to ( an  room )  
carry out liste ( room called X   ) :
  for each (room called Y ):
      if X connect Y :
          say  (text connect )
   

listem is  an action applying to ( an  room )
carry out listem ( room called X   ) :
  for each (room called Y ):      
      if X lead Y :
         say  Y

)";

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(ParseText::parser_text(&parse, slong, true));


	//auto q5 = interpreter->query(Expression::Parser_Expression(&parse, "hall edge to garden  ", ISLOG), nullptr, nullptr);
	// assert(q5.result == QEquals);

	//auto q6 = interpreter->query(Expression::Parser_Expression(&parse, "garden edge to hall  ", ISLOG), nullptr, nullptr);
	//assert(q6.result == QEquals);


	//auto q7 = interpreter->query(Expression::Parser_Expression(&parse, "hall lead cave  ", ISLOG), nullptr, nullptr);
	//assert(q7.result == QEquals);
	std::cout << "*******************************************************************************************" << std::endl;
	std::cout << "Start Evals" << std::endl << std::endl;

	//auto q8 = interpreter->execute_now(Statement::Parser_Stmt(&parse, "try liste hall ", ISLOG));

    // auto q8a = interpreter->query(Expression::Parser_Expression(&parse, "hall lead cave  ", ISLOG), nullptr, nullptr);
    //assert(q8a.result == QEquals);
	auto q8b = interpreter->execute_now(Statement::Parser_Stmt(&parse, "try listem hall ", ISLOG));

	logMessage("end");
}

void testedecide_all()
{
 
	testedecide_1();
	testedecide_2();
	testedecide_3();
	testedecide_4();
	testedecide_5();
	testedecide_6();
	testedecide_7();
	

}