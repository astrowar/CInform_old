 

#include "BaseTest.hpp"
#include <cassert>
#include "ParserPlural.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;

void testeParser_6()//kind of value
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	{
		string phase_1 = "a limb is a kind of value";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color is a kind of value", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color can be light or dark", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color can be cold or warm", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color is usually light", ISLOG));
	}

	{
		string phase_1 = "an aspect ratio is a kind of value";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		interpreter->execute_init(res);
	}

	{
		string phase_1 = "   blue, green, yellow  and red are color ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);


		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"black is a color", ISLOG));
		auto q_tru = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												 std::make_shared<CBlockNoum>("light"));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"black is dark", ISLOG));
		auto q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												std::make_shared<CBlockNoum>("light"));

		string phase_1 = " ... ";
	}
	{
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"warm color is a  kind of color", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"warm color is usually warm", ISLOG));

		interpreter->execute_init(Statement::Parser_Stmt(&parse,"red is a warm color", ISLOG));
		auto q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("red"),
												std::make_shared<CBlockNoum>("warm"));

		string phase_1 = " ... ";
	}
	//std::cout );
}


void testeParser_6a()//kind of value
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	{
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color is a kind of value", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"blue, green, yellow  and red are color", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind ", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a thing", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"book has a color", ISLOG));
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color of book is red ", ISLOG));
	}

	auto q_fa = interpreter->query_is_extern(std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("color"),
																			 std::make_shared<CBlockNoum>("book")),
											std::make_shared<CBlockNoum>("red"));

	logMessage("");
}


void testeParser_20() //custrom rlacions
{

	CParser parse ;
	/*{
		std::string phase_1 = "Fanciness relates a ( thing called X ) to ( some money called Y ) when ( (the price of X) > (the price of Y ))";
		auto res = Statement::Parser_Stmt(&parse,phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG)
		{
			res->dump("");
			std::cout );
		}
	}

	 */

	//{
	//	std::string phase_1 = "the verb inside of implies a reverse container relation";
	//	auto res = Statement::Parser_Stmt(&parse,phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	//{
	//	std::string phase_1 = "the verb contains implies a container relation";
	//	auto res = Statement::Parser_Stmt(&parse,phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}


	//{
	//	std::string phase_1 = "book contains text";
	//	auto res = Statement::Parser_Stmt(&parse,phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	{
		auto block = Statement::Parser_Stmt(&parse,"the verb able to open implies a opening relation", ISLOG);
		 
	}
	{
		auto block = Statement::Parser_Stmt(&parse,"X is  able   to open   Z", ISLOG);
		 
	}
	logMessage( "----------------------------------------" );
	{
		auto block = Statement::Parser_Stmt(&parse,"to decide if (X    able   to open   Z) : (decides on true)", ISLOG);
		 
	}


	/*{
		std::string phase_1 = "let L be the (list of ( things fancier than/of/in/on 20 ) ) )";
		auto res = Statement::Parser_Stmt(&parse,phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG)
		{
			res->dump("");
			std::cout );
		}
	}*/
}

void testeParser_21() {
	CParser parse ;
	{
		{
			string phase_1 = "the verb ( stuck to ) implies a stuking relation ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}

		{
			string phase_1 = "coin is stuck to box";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}

		{
			string phase_1 = "the verb ( visible by ) implies a visibility relation";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is visible by other) if ( ( it is stuck to the noun) and (it is not within the location ) )";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is in same room ) if ( ( location of it  ) is ( location of player ) )";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is hide ) if ( it is not visible by player ) and ( it is in same room )";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

		}
		{
			string phase_1 = "definition : (a thing is in ( place : location )  ) if ( location of it is place ) ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "the verb made of implies the materiality relation ";

			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}
		{
			string phase_1 = "coin is made of golden";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

	}

}


void testeParser_22() {
	CParser parse ;
	{
		{
			string phase_1 = " use_with is an action applying to (one thing) and (a thing)  ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "understand : use  [ a thing ] as use_with ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "understand : use  [ a thing  - keyer ] with [ a thing ] as use_with ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "  use key with box ";
			auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
			 
		}

	}
}


void testeParser_10() {

	
	{
		CParser parse;
		string ss1 =
			R"(
the verb ( points to )  implies a  dynamic relation
now x points to b
  
)";
		ParseText::parser_text(&parse,ss1, true);
	}
 
	{
		string ss1 =
			R"(
if x is 10 :
  x is y
  x is z
  if y is a :
     a is z
else :
  a is z
)";
		CParser parse;
		ParseText::parser_text(&parse,ss1, true);
	}

	printf("========================================\n");
	{
		string ss1 =
			R"(
if x is 10 :
   x is y
if x is 10: 
  if y is 10: 
    if y is 10: 
       error is true 
)";
		CParser parse; 
		ParseText::parser_text(&parse,ss1, true);
	}

	printf("========================================\n");
	{
		string ss1 =
			R"(
if x is :
   -- a :   x is b
   -- b :   x is c
   -- c :  
           x is a
           y is b  
else:  
     x is b
)";
		CParser parse; 
		ParseText::parser_text(&parse,ss1, true);
	}

	printf("========================================\n");
	{
		HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
		CParser parse;
		
		ParseText::parser_text(&parse,"the verb (points to)  implies a  dynamic relation", true);
		string ss1 =
			R"(
the verb (points to)  implies a  dynamic relation
value is a kind of value
x is a value
x can be a , b or c
x is c
)";
		string ss2 =
			R"(
if x is :
   -- a : now x points to b
   -- b : now x is c
   -- c :  
         now x is a
          
else:  
   say  ( text error )
)";
		 
		auto stmt =  ParseText::parser_text(&parse,ss1, ISLOG);
		interpreter->execute_init( stmt );
		auto ret_e = interpreter->query(Statement::Parser_Stmt(&parse," x is c  ", ISLOG));		 
		assert(ret_e.result == QEquals);

		interpreter->execute_now(ParseText::parser_text(&parse,ss2, ISLOG));

		auto ret_e2 = interpreter->query(Statement::Parser_Stmt(&parse," x is a  ", ISLOG));
		assert(ret_e.result == QEquals);
	}


	return;
}

void testeParser_plural() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	{
		CParser parse;

		string ss1 =
			R"(
plural of passaro is passaros
plural of caixa  is caixas
plural of brother in law is brothers in law
  
)";
		auto pp =  ParseText::parser_text(&parse,ss1, ISLOG);
		interpreter->execute_init(pp);

		auto rt = interpreter->exec_eval(Expression::Parser_Expression(&parse," plural of caixa ", ISLOG),nullptr, nullptr);
		rt->dump("");

		rt = interpreter->exec_eval(Expression::Parser_Expression(&parse," plural of brother in law ", ISLOG), nullptr, nullptr);
		rt->dump("");
	}
	logMessage("...");
	return;
}

void testePlurals()
{

	auto ptable = plura_table();
	char* c_oxen = plural_of("ox", &ptable);
	char* c_hooves = singular_of("hooves", &ptable);

	printf("ox -> %s \n", c_oxen);
	printf("hooves <- %s \n", c_hooves);
	printf("done \n");


	testeParser_plural();
	return;
}


int main() {

	testeParser_7e();
 
	 
	testePlurals();
 
	// testeParser_1();

	//testValues_all();
	//return 0;
	
	testeRelation_all();
	//testeParser_7e();

//	testeExecute_all();
	//testeParser_listAll();
	//testAction_all();
	//testeVerb_all();
 

   for (int k = 0; k < 1000; ++k)
	{
		testeExecute_all();	 
		 testeParser_5_all();		 
		 testeRelation_all(); 
		 testeExecute_all();
		testeSelector_all();
		testAction_all();
		logMessage( ".");
	}
	logMessage("");
}


  #ifdef __EMSCRIPTEN__

//api_example.c
#include<stdio.h>
#include<emscripten.h>


extern "C"
{
   void sayHi();
   void sayStr(char* str);
}

EMSCRIPTEN_KEEPALIVE
void sayHi() {
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	{
		interpreter->execute_init(Statement::Parser_Stmt(&parse,"color is a kind of value", ISLOG));
	}
}

void sayStr(char* str) {
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	{
	std::string line (str);
		interpreter->execute_init(Statement::Parser_Stmt(&parse, line , ISLOG));
	}
}
#endif