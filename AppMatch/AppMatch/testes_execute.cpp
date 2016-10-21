#include "BaseTest.hpp"
#include <cassert>


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
definition : ( route called PATH ) is viable exit   if (( destination of PATH ) is not limbo) and ( ( destination of PATH ) is not location )

garden is a room
hall is a room
door is a route
destination of door is garden
limbo is a room
location is a room that varies
location is hall

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

	auto stmt = parse.parser_text(ss1, ISLOG);

	interpreter->execute_init(stmt);
	

	auto ret_e = interpreter->query(parse.Parser_Stmt(" x is c  ", ISLOG));
	assert(ret_e == QEquals);

	auto ret_dst = interpreter->query(parse.Parser_Stmt("destination of door is garden  ", ISLOG));
	assert(ret_dst == QEquals);

	auto query_block = parse.Parser_Stmt("door points to garden  ", ISLOG);
	auto ret_points = interpreter->query(query_block);
	assert(ret_points == QEquals);

	 
	auto ret_points_q = interpreter->query(parse.Parser_Stmt("door points to hall  ", ISLOG));
	assert(ret_points_q == QNotEquals);

	auto ret_points_init = interpreter->query(parse.Parser_Stmt("door is viable exit ", ISLOG));
	assert(ret_points_init == QEquals);

	interpreter->execute_now(parse.Parser_Stmt("location is garden ", ISLOG));
	auto ret_points_garden = interpreter->query(parse.Parser_Stmt("door is viable exit  ", ISLOG));
	assert(ret_points_garden == QNotEquals);

	return;
}