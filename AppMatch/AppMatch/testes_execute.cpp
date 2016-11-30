#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;



void testeExecute1() 
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"( 
the verb (points to)  implies a  dynamic relation
value is a kind of value
x is a value
x can be a , b or c
x is c
route is a kind 
room is a kind 
route has a room called destination
route has a room called origin

definition : ( ( route called PATH ) points to ( room called R ) ) if ( ( destination of PATH ) is R )
definition : ( route called PATH ) is viable exit  if (( destination of PATH ) is not limbo) and ( ( destination of PATH ) is not location ) 
      

garden is a room
hall is a room
door is a route
destination of door is garden
limbo is a room
location is a room that varies
location is hall

Connection relates (a room ) to  ( a room )
the verb connect   implies a  Connection relation

hall connect garden

)";
	//definition : ( ( route called PATH ) points to ( room called R ) ) if ( ( destination of PATH ) is R )
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

	printf("=========================================\n");
	auto stmt = ParseText::parser_text(&parse,ss1, ISLOG);

	interpreter->execute_init(stmt);
	

	//auto ret_e = interpreter->query(Statement::Parser_Stmt(&parse," x is c  ", ISLOG));
//	assert(ret_e == QEquals);

	//auto ret_dst = interpreter->query(Statement::Parser_Stmt(&parse,"destination of door is garden  ", ISLOG));
	//assert(ret_dst == QEquals);

	auto query_block = Statement::Parser_Stmt(&parse,"door points to garden  ", ISLOG);
	auto ret_points = interpreter->query(query_block);
	assert(ret_points.result == QEquals);

	 
	auto ret_points_q = interpreter->query(Statement::Parser_Stmt(&parse,"door points to hall  ", ISLOG));
	assert(ret_points_q.result == QNotEquals);

	auto ret_points_init = interpreter->query(Statement::Parser_Stmt(&parse,"door is viable exit ", ISLOG));
	assert(ret_points_init.result == QEquals);

	interpreter->execute_now(Statement::Parser_Stmt(&parse,"location is garden ", ISLOG));
	auto ret_points_garden = interpreter->query(Statement::Parser_Stmt(&parse,"door is viable exit  ", ISLOG));
	assert(ret_points_garden.result == QNotEquals);

	auto ret_connect_init = interpreter->query(Statement::Parser_Stmt(&parse,"hall connect garden ", ISLOG));
	assert(ret_connect_init.result == QEquals);

	return;
}


void testeExecute2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
			R"(

room is a kind
garden is a room
hall is a room 
Connection relates ( a room ) to  ( a room )
the verb connect   implies a  Connection relation 
hall connect garden

)";


	auto stmt = ParseText::parser_text(&parse,ss1, ISLOG);

	interpreter->execute_init(stmt);


	auto ret_connect_init = interpreter->query(Statement::Parser_Stmt(&parse,"hall connect garden ", ISLOG));
	assert(ret_connect_init.result == QEquals);

	auto ret_connect_b = interpreter->query(Statement::Parser_Stmt(&parse,"garden connect hall  ", ISLOG));
	assert(ret_connect_b.result == QNotEquals  );

	return;
}


void testeExecute3()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"(
route is a kind 
room is a kind 
route has a room called destination
garden is a room
hall is a room 
exit is a route
destination of exit is garden
Connection relates ( a room called source ) to  ( a room called destination )
the verb connect   implies a  Connection relation 
hall connect garden
garden connect hall

direction  is a kind 
direction has a direction called ops

Oposition relates ( a direction  ) to   ( a direction called opposite )
the verb opposte by implies a  Oposition relation 

north is a direction
south is a direction
east  is a direction
west is a direction

)";
 

	interpreter->execute_init(ParseText::parser_text(&parse,ss1, false));

	//auto ret_1 = interpreter->evaluate_values(Expression::Parser_Expression(&parse,"source of garden", false ));
	//printf("=============================\n");
	//ret_1->dump(" ");

//	auto ret_2 = interpreter->evaluate_values(Expression::Parser_Expression(&parse,"destination of exit", false));
	//printf("=============================\n");
	//ret_2->dump(" ");

	

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( room  ) is oposite of ( oposite of ( room called X ) ) :  X   ", ISLOG));
	//auto ret_3 = interpreter->evaluate_values(Expression::Parser_Expression(&parse,"oposite of ( oposite of  garden) ", ISLOG));
	//printf("=============================\n");
	//ret_3->dump(" ");


	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide if ( direction called Y ) is opposite of (  direction called X )   :  X is opposite of Y   ", ISLOG));	
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"south is  opposte by  north", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse," west  is opposte by  east ", ISLOG));

	//auto ret_4 = interpreter->evaluate_values(Expression::Parser_Expression(&parse,"oposite of north  ", ISLOG));
	//printf("=============================\n");
	//ret_4->dump(" ");
	auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse,"north is  opposite  of south  ", ISLOG));
	auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse,"south is  opposite  of north  ", ISLOG));
	 auto ret_true_ba = interpreter->query(Statement::Parser_Stmt(&parse," south is  opposite  of ( opposite of  south ) ", ISLOG));
	assert(ret_true_a.result == QEquals);
	assert(ret_true_ba.result == QEquals);
 
	 
	return;
}


void testeExecute4()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string ss1 =
		R"(
object is a kind 
book is a object
key is a object
box is a object
target is a object that varies
target is box 
)";

	interpreter->execute_init(ParseText::parser_text(&parse,ss1, ISLOG));

	string ss2 =
		R"(
if ( target ) is key :
   decide on book
else : 
   decide on target
)";

	

	auto target_q = interpreter->exec_eval(ParseText::parser_text(&parse,ss2, true), nullptr);
	target_q->dump("");
	//assert(ret_true_a == QEquals);
	return;
}



void testeExecute5()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string ss1 =
		R"(
object is a kind 
object can be small or huge
object is usually  small
book is a object
key is a object
box is a object
target is a object that varies
target is box 

a talent is a kind of value
a talent can be normal 
strength, courage, luck, scent, honor, spirit and freedom is talent
luck is normal
)";

	interpreter->execute_init(ParseText::parser_text(&parse,ss1, ISLOG));

	if(true){
		string ss2 = R"(now every object is huge)";
		auto res_q = interpreter->query(Statement::Parser_Stmt(&parse,"box is small ", true));
		auto target_q = interpreter->exec_eval(ParseText::parser_text(&parse,ss2, true), nullptr);
		//target_q->dump("");
		//assert(ret_true_a == QEquals);
		auto res_2 = interpreter->query(Statement::Parser_Stmt(&parse,"box is huge ", true));
		assert(res_2.result == QEquals);
	}

	if (true)
	{
		auto res_3 = interpreter->query(Statement::Parser_Stmt(&parse,"courage is not normal ", true));
		assert(res_3.result == QNotEquals);
		//string ss3 = R"(now every talent is not normal )"; 
		interpreter->exec_eval(ParseText::parser_text(&parse,"now every talent is not  normal", true), nullptr);
		 auto  res_4 = interpreter->query(Statement::Parser_Stmt(&parse,"courage is not normal ", true));
		assert(res_4.result == QEquals);
	}

	return;
}




void testeExecute7()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string ss1 =
		R"(
room is a kind 
r1 is a room
r2 is a room
r3 is a room
r4 is a room

Connection relates ( a room called source ) to  ( a room called destination )
the verb connect   implies a  Connection relation 
r1 connect r2
r2 connect r3
r3 connect r4

 


)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, ISLOG));

	auto target_q3 = interpreter->exec_eval(Expression::Parser_Expression(&parse, "a room which  relates to r2 by Connection ", ISLOG), nullptr);
	target_q3->dump("");

	if (true) 
	{	
		auto res_q = interpreter->query(Expression::Parser_Expression(&parse, "r4 is destination of r1 ", true));
		assert(res_q.result == QEquals);
	}

	return;
}
void testeExecute_all()
{
 
	//testeExecute5();
	 
	   // testeExecute1();  precisa ser revisto o DEFINE
	// testeExecute2();
	// testeExecute3();
	 //testeExecute4();

	testeExecute7();
		 
}