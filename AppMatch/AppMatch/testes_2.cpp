
#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeParser_3() {
	CParser parse;
	{
		string phase_1 = "eat  is (an action  applying to (an thing ) )";
		auto res = Statement::Parser_Stmt(&parse,phase_1,ISLOG);

	}
	{
		string phase_1 = "(cut ) is    an action   applying to (an thing ) and (a Cutter)   ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}
	//std::cout << "Done" << std::endl;
	return;
}

void testeParser_4() {
	CParser parse;
	{
		string phase_1 = "a thing can be discovered or secret";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "( a person ) has a (table-name) called (the opinion-table)";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "the (singing action) has a (text) called the (lyric sung)";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "the torch has a brightness ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}


	//"Brightness is a kind of value";
	//"The brightnesses are guttering, weak, radiant and blazing";
	//"The torch has a brightness";
	//	"The torch	is blazing";
	//"The torch is lit";
	// logMessage("");
	return;
}


void testeParser_5() {
	CParser parse;
	{
		string phase_1 = "to decide what (room) is (the safest location) : (decide on) ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}
	{
		string phase_1 = "to decide what (person) is the (brother to/of (sibling - a person)) : (decide on (son of ( fater of sibling) )  ) ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "to decide if X is greater than Y : (decide on ( X > Y) )    ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "to decide if X is sucessor of Y : (decide on ( X   == Y + 1) )    ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "to decide what number  is sucessor of Y : (decide on (  Y + 1) )    ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}

	{
		string phase_1 = "to decide what (indexed text) is ((T - text) doubled) : (decide on T T ) ";
		auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

	}
}


void testeParser_5b() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG)); 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"orange is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"coal is a thing  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is oposite of ( far item ) :  ( special item )    ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is ( special item ) :   apple    ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is connected of ( far item ) :  ( special item )    ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is ( next item ) of apple :  orange   ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is ( previous item ) of apple :   orange    ", ISLOG));


	QueryResultContext ret = interpreter->query(Statement::Parser_Stmt(&parse,"( special item ) is apple  ", ISLOG));
	assert(ret.result == QEquals);
	QueryResultContext ret_2 = interpreter->query(Statement::Parser_Stmt(&parse,"( far item ) is apple  ", ISLOG));
	assert(ret_2.result == QUndefined); // what is far item ??

	//now set far item 
 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"( far item ) is a thing that varies  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"( far item ) is orange  ", ISLOG));
	QueryResultContext ret_3 = interpreter->query(Statement::Parser_Stmt(&parse,"oposite of orange is apple  ", ISLOG));
	assert(ret_3.result == QEquals);

	
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing  ) is oposite of ( oposite of ( thing called X ) ) :  X   ", ISLOG));
	QueryResultContext ret_4 = interpreter->query(Statement::Parser_Stmt(&parse,"( oposite of ( oposite of coal ) ) is coal  ", ISLOG));
	assert(ret_4.result == QEquals);

	return;

}


void testeParser_5c() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is a thing  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is oposite of ( thing called X ) :  X   ", ISLOG));	

	auto ret = interpreter->query(Statement::Parser_Stmt(&parse," oposite of apple  is apple  ", ISLOG));
	
	return;

}

void testeParser_5d() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"room is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"place is a room  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple can be lit  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is  lit  ", ISLOG));
	//it->ei->p.ps()
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb ( in same ) implies a equality relation ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb ( in same ) implies a dynamic relation ", ISLOG)); 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"definition : ( (lit thing called T ) is in same ( room called R ) ) if ( (location of T ) is R )", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( thing ) is oposite of ( thing called X ) :  X   ", ISLOG));
	//auto ret = interpreter->query(Statement::Parser_Stmt(&parse," oposite of apple  is apple  ", ISLOG));

	auto ret_lit = interpreter->query(Statement::Parser_Stmt(&parse,"apple is lit ", ISLOG));
	auto ret_true = interpreter->query(Statement::Parser_Stmt(&parse,"apple is in same  place ", ISLOG));
	auto ret_false = interpreter->query(Statement::Parser_Stmt(&parse,"book is in same  place ", ISLOG));
	return;

}

void testeParser_5e() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"direction is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"room is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"garden is a room  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"hall is a room  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"north is a direction  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"south is a direction  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  from   implies a  connection relation", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"definition : ( a direction called thataway ) is viable if (  thataway from ( the location ) ) is ( a room )", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"definition : ( a direction called thataway ) is viable if (  thataway is north )", ISLOG));

	auto ret_true = interpreter->query(Statement::Parser_Stmt(&parse,"north is viable", ISLOG));
	return;
}

void testeParser_5f() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"direction is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"room is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"garden is a room  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"hall is a room  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"north is a direction  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"south is a direction  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  from   implies a  dynamic relation", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb (points to)  implies a  dynamic relation", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb (exits to)  implies a  dynamic relation", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  wears  implies a  dynamic relation", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  in  implies a  dynamic relation", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( room ) is ( north from  hall ) :  garden   ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( room ) is ( south from  garden ) :  hall   ", ISLOG));

	// interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide what ( list of room ) is exits from ( room called _location ) : ( north ) ", ISLOG));
	//auto ret_true = interpreter->query(Statement::Parser_Stmt(&parse,"( north from hall ) is garden ", ISLOG));


	//auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse," ( ( north from hall ) is garden ) is true", ISLOG) );
	 
	//auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse," exits from ( room called _location ) : ( direction called _direction ) which ( ( _direction from _location ) is outside )  and ( _direction is reveled )", ISLOG));
	//auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse," let exit_list is ( direction called D ) and (room called R ) which ( ( D from R ) is outside )  and ( R is reveled )", ISLOG));


	interpreter->execute_init(Statement::Parser_Stmt(&parse,
	"to decide what ( direction )  points to exit of ( room called R )   : decide on north ", ISLOG));


    interpreter->execute_init(Statement::Parser_Stmt(&parse,
            "to decide if (room called R ) exits to ( direction called D ) :  D points to exit of R  ", true));


    interpreter->execute_init(Statement::Parser_Stmt(&parse,
            " south points to exit of garden  ", ISLOG));


	//auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse,"north points to exit of hall  ", ISLOG));

    auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse,"hall exits to north   ", ISLOG));
	assert(ret_true_a.result == QEquals);
   // auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse,"garden exits to south   ", ISLOG));


    return;
}

void testeParser_5g() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"colour is a kind of value  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the colour are red, blue and green  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"  block is an kind of thing ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"  block has a colour ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"  block is usually blue  ", ISLOG));
 
	
	//Liquid is a kind of value.The liquids are water, milk, lemonade, and iced tea
	interpreter->execute_init(Statement::Parser_Stmt(&parse," liquid is a kind of value", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"  the liquid are water, milk, lemonade and (iced tea ) ", ISLOG));

	return;
}


void testeParser_5_all()
{
 
	testeParser_5b();
	testeParser_5c();
	testeParser_5d();
	testeParser_5e();
	//testeParser_5f(); TODO FIX THIS TESTE
	testeParser_5g();

 
}