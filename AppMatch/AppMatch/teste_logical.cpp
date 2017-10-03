#include "BaseTest.hpp"
#include <cassert>
#include <iostream>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeLogical_1()//dynamic match
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	string ss1 =
		R"(

 thing is an kind
 milk is a thing
 cow is a thing
 cheese is a thing

 to decide what thing is the derivade of  (thing called C) : 
   if C is cow :
      decide on milk
   if C is milk :
      decide on cheese
 
  

 to decide what thing is the full derivade of  (thing called C) :  
   let the produto  be derivade of C
   let derivado base be derivade of produto
   decide on derivado base
   
    

)";
	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));

	auto target_q3 = interpreter->exec_eval(Expression::Parser_Expression(&parse, "full derivade of cheese   ", false), nullptr, nullptr);
	target_q3->dump("A ");
	 

 

	return;
}


void testeLogical_2()// local relations 
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	string ss1 =
		R"(

 thing is an kind
 milk is a thing
 cow is a thing
 cheese is a thing

 to decide what thing is the derivade of  (thing called C) : 
   let tabela be a various-to-one relation of thing
   now tabela relates milk to cow
   now tabela relates cheese  to milk      
   let D be ((the room ) which relates to C by the tabela relation)
   decide on D
  

 
   
    

)";
	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));

	//auto target_q3 = interpreter->exec_eval(Expression::Parser_Expression(&parse, " derivade of milk   ", false), nullptr, nullptr);
	//target_q3->dump("A ");




	return;
}



void testeLogical_All()
{
	//testeLogical_1();
	testeLogical_2();
}