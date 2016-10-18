 

#include "BaseTest.hpp"

void testeParser_6()//kind of value
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	{
		string phase_1 = "a limb is a kind of value";
		auto res = parse.parser_stmt(phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG) {
			res->dump("");
			logMessage("");
		}
		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(parse.parser_stmt("color is a kind of value"));
		interpreter->execute_init(parse.parser_stmt("color can be light or dark"));
		interpreter->execute_init(parse.parser_stmt("color can be cold or warm"));
		interpreter->execute_init(parse.parser_stmt("color is usually light"));
	}

	{
		string phase_1 = "an aspect ratio is a kind of value";
		auto res = parse.parser_stmt(phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG) {
			res->dump("");
			logMessage("");
		}
		interpreter->execute_init(res);
	}

	{
		string phase_1 = "   blue, green, yellow  and red are color ";
		auto res = parse.parser_stmt(phase_1);
		if (res == nullptr) throw "parse error";
		if (ISLOG) {
			res->dump("");
			logMessage("");
		}
		interpreter->execute_init(res);
	}

	{
		interpreter->execute_init(parse.parser_stmt("black is a color"));
		QueryResul q_tru = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												 std::make_shared<CBlockNoum>("light"));
		interpreter->execute_init(parse.parser_stmt("black is dark"));
		QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("black"),
												std::make_shared<CBlockNoum>("light"));

		string phase_1 = " ... ";
	}
	{
		interpreter->execute_init(parse.parser_stmt("warm color is a  kind of color"));
		interpreter->execute_init(parse.parser_stmt("warm color is usually warm"));

		interpreter->execute_init(parse.parser_stmt("red is a warm color"));
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
		interpreter->execute_init(parse.parser_stmt("color is a kind of value"));
		interpreter->execute_init(parse.parser_stmt("blue, green, yellow  and red are color"));
		interpreter->execute_init(parse.parser_stmt("thing is a kind "));
		interpreter->execute_init(parse.parser_stmt("book is a thing"));
		interpreter->execute_init(parse.parser_stmt("book has a color"));
		interpreter->execute_init(parse.parser_stmt("color of book is red "));
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
		auto res = parse.parser_stmt(phase_1);
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
	//	auto res = parse.parser_stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	//{
	//	std::string phase_1 = "the verb contains implies a container relation";
	//	auto res = parse.parser_stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}


	//{
	//	std::string phase_1 = "book contains text";
	//	auto res = parse.parser_stmt(phase_1);
	//	if (res == nullptr) throw "parse error";
	//	if (ISLOG)
	//	{
	//		res->dump("");
	//		std::cout );
	//	}
	//}
	{
		auto block = parse.parser_stmt("the verb able to open implies a opening relation");
		if (ISLOG) {
			block->dump("");
			logMessage("");
		}
	}
	{
		auto block = parse.parser_stmt("X is  able   to open   Z");
		if (ISLOG) {
			block->dump("");
			logMessage("");
		}
	}
	logMessage( "----------------------------------------" );
	{
		auto block = parse.parser_stmt("to decide if (X    able   to open   Z) : (decides on true)");
		if (ISLOG) {
			block->dump("");
			logMessage("");
		}
	}


	/*{
		std::string phase_1 = "let L be the (list of ( things fancier than/of/in/on 20 ) ) )";
		auto res = parse.parser_stmt(phase_1);
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
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "coin is stuck to box";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "the verb ( visible by ) implies a visibility relation";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "definition : (a thing is visible by other) if ( ( it is stuck to the noun) and (it is not within the location ) )";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "definition : (a thing is in same room ) if ( ( location of it  ) is ( location of player ) )";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "definition : (a thing is hide ) if ( it is not visible by player ) and ( it is in same room )";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}
		{
			string phase_1 = "definition : (a thing is in ( place : location )  ) if ( location of it is place ) ";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "the verb made of implies the materiality relation ";

			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}
		{
			string phase_1 = "coin is made of golden";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

	}

}


void testeParser_22() {
	CParser parse(std::make_shared<CBlockInterpreter>());
	{
		{
			string phase_1 = " use_with is an action applying to (one thing) and (a thing)  ";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "understand : use  [ a thing ] as use_with ";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "understand : use  [ a thing  - keyer ] with [ a thing ] as use_with ";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

		{
			string phase_1 = "  use key with box ";
			auto res = parse.parser_stmt(phase_1);
			if (res == nullptr) throw "parse error";
			if (ISLOG) {
				res->dump("");
				logMessage("");
			}
		}

	}
}


void testeParser_10() {

	CParser parse(std::make_shared<CBlockInterpreter>());
	{
		string ss1 =
			R"(
thing is an kind
book is a thing
diary can be big or small 
  
)";
		parse.parser_text(ss1, true);
	}
	
	{
		string ss1 =
			R"(
if x > 10 :
  let x = 10 
  let y =y +1
  if y > 4 :
     y = 0
else:
  let x = x + 1  
end
to call x :
   try call system
   try call user
)";
		parse.parser_text(ss1, true);
	}

	return;
}

int main() {
	// testeParser_1();

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
	//	testeSerialize1();
        testeParser_10();
		logMessage( ".");
	}
	logMessage("");
}