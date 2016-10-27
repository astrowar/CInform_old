 

#include "BaseTest.hpp"
#include <cassert>

void testeParser_6()//kind of value
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	{
		string phase_1 = "a limb is a kind of value";
		auto res = parse.Parser_Stmt(phase_1, ISLOG);

		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(parse.Parser_Stmt("color is a kind of value", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("color can be light or dark", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("color can be cold or warm", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("color is usually light", ISLOG));
	}

	{
		string phase_1 = "an aspect ratio is a kind of value";
		auto res = parse.Parser_Stmt(phase_1, ISLOG);

		interpreter->execute_init(res);
	}

	{
		string phase_1 = "   blue, green, yellow  and red are color ";
		auto res = parse.Parser_Stmt(phase_1, ISLOG);


		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(parse.Parser_Stmt("black is a color", ISLOG));
		QueryResul q_tru = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												 std::make_shared<CBlockNoum>("light"));
		interpreter->execute_init(parse.Parser_Stmt("black is dark", ISLOG));
		QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												std::make_shared<CBlockNoum>("light"));

		string phase_1 = " ... ";
	}
	{
		interpreter->execute_init(parse.Parser_Stmt("warm color is a  kind of color", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("warm color is usually warm", ISLOG));

		interpreter->execute_init(parse.Parser_Stmt("red is a warm color", ISLOG));
		QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("red"),
												std::make_shared<CBlockNoum>("warm"));

		string phase_1 = " ... ";
	}
	//std::cout );
}


void testeParser_6a()//kind of value
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	{
		interpreter->execute_init(parse.Parser_Stmt("color is a kind of value", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("blue, green, yellow  and red are color", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("thing is a kind ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("book is a thing", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("book has a color", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("color of book is red ", ISLOG));
	}

	QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("color"),
																			 std::make_shared<CBlockNoum>("book")),
											std::make_shared<CBlockNoum>("red"));

	logMessage("");
}


void testeParser_20() //custrom rlacions
{

	CParser parse(std::make_shared<CBlockInterpreter>());
	/*{
		std::string phase_1 = "Fanciness relates a ( thing called X ) to ( some money called Y ) when ( (the price of X) > (the price of Y ))";
		auto res = parse.Parser_Stmt(phase_1);
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
	//	auto res = parse.Parser_Stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	//{
	//	std::string phase_1 = "the verb contains implies a container relation";
	//	auto res = parse.Parser_Stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}


	//{
	//	std::string phase_1 = "book contains text";
	//	auto res = parse.Parser_Stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	{
		auto block = parse.Parser_Stmt("the verb able to open implies a opening relation", ISLOG);
		 
	}
	{
		auto block = parse.Parser_Stmt("X is  able   to open   Z", ISLOG);
		 
	}
	logMessage( "----------------------------------------" );
	{
		auto block = parse.Parser_Stmt("to decide if (X    able   to open   Z) : (decides on true)", ISLOG);
		 
	}


	/*{
		std::string phase_1 = "let L be the (list of ( things fancier than/of/in/on 20 ) ) )";
		auto res = parse.Parser_Stmt(phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG)
		{
			res->dump("");
			std::cout );
		}
	}*/
}

void testeParser_21() {
	CParser parse(std::make_shared<CBlockInterpreter>());
	{
		{
			string phase_1 = "the verb ( stuck to ) implies a stuking relation ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}

		{
			string phase_1 = "coin is stuck to box";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}

		{
			string phase_1 = "the verb ( visible by ) implies a visibility relation";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is visible by other) if ( ( it is stuck to the noun) and (it is not within the location ) )";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is in same room ) if ( ( location of it  ) is ( location of player ) )";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}

		{
			string phase_1 = "definition : (a thing is hide ) if ( it is not visible by player ) and ( it is in same room )";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);

		}
		{
			string phase_1 = "definition : (a thing is in ( place : location )  ) if ( location of it is place ) ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "the verb made of implies the materiality relation ";

			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}
		{
			string phase_1 = "coin is made of golden";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

	}

}


void testeParser_22() {
	CParser parse(std::make_shared<CBlockInterpreter>());
	{
		{
			string phase_1 = " use_with is an action applying to (one thing) and (a thing)  ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "understand : use  [ a thing ] as use_with ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "understand : use  [ a thing  - keyer ] with [ a thing ] as use_with ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

		{
			string phase_1 = "  use key with box ";
			auto res = parse.Parser_Stmt(phase_1, ISLOG);
			 
		}

	}
}


void testeParser_10() {

	
	{
		CParser parse(std::make_shared<CBlockInterpreter>()); 
		string ss1 =
			R"(
the verb ( points to )  implies a  dynamic relation
now x points to b
  
)";
		parse.parser_text(ss1, true);
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
		CParser parse(std::make_shared<CBlockInterpreter>()); 
		parse.parser_text(ss1, true);
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
		CParser parse(std::make_shared<CBlockInterpreter>()); 
		parse.parser_text(ss1, true);
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
		CParser parse(std::make_shared<CBlockInterpreter>()); 
		parse.parser_text(ss1, true);
	}

	printf("========================================\n");
	{
		HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
		CParser parse(interpreter);
		
		parse.parser_text("the verb (points to)  implies a  dynamic relation", true);
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
		 
		auto stmt =  parse.parser_text(ss1, ISLOG);
		interpreter->execute_init( stmt );
		auto ret_e = interpreter->query(parse.Parser_Stmt(" x is c  ", ISLOG));		 
		assert(ret_e == QEquals);

		interpreter->execute_now(parse.parser_text(ss2, ISLOG));

		auto ret_e2 = interpreter->query(parse.Parser_Stmt(" x is a  ", ISLOG));
		assert(ret_e == QEquals);
	}


	return;
}

int main() {
	// testeParser_1();

	//testeParser_7b();
	testeExecute_all();
	return 0 ;
	 
  // for (int k = 0; k < 100; ++k)
	{
		// testeParser_listA();
		// testeParser_listB();

		// testeParser_actionC();
	   // testeParser_2();
	   // testeParser_2a();
		//testeParser_3();
		//testeParser_4();
		// testeParser_5b();
	//	 testeParser_5c();
	//	 testeParser_5d();
	//	 testeParser_5e();
	//	 testeParser_5f();

		//testeParser_5d();
		//testeParser_5f();
		//testeParser_6();

		 testeParser_5_all();

		//testeParser_5g();
	   //testeParser_7a();
	   //testeParser_7b();
		//testeParser_7c();
		 //testeParser_7d();
	  //testeParser_22();

		//testeRelation1();
		//testeRelation2();
		//testeRelation3();
		//testeRelation3();
		//testeRelation4();
		 testeRelation_all();

	//	testeSerialize1();
        //testeParser_10();
		//testeExecute2();
		 testeExecute_all();
		testeSelector_all();
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
}

EMSCRIPTEN_KEEPALIVE
void sayHi() {
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	{
		interpreter->execute_init(parse.Parser_Stmt("color is a kind of value", ISLOG));
	}
}
#endif