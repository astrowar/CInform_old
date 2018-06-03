
#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


HBlockNoum noum(std::string n) {return std::make_shared<CBlockNoumStr>(n); };

void testeParser_listA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
 
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"object is a kind  ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a object  ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"box is a object  ", ISLOG));

	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"target is a  object  that varies", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"target is book ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"box is a object  ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is a object  ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary can be (green , red or blue)  ", ISLOG));
	 interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is red  ", ISLOG));

     interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb listed in implies the listed_in relation", ISLOG));

	 auto q_true = interpreter->query_is_extern(std::make_shared<CBlockNoumStr>("target"), std::make_shared<CBlockNoumStr>("book"));
	 assert(q_true.result == QEquals);

	 auto q_true_2 = interpreter->query_is_extern(std::make_shared<CBlockNoumStr>("book"), std::make_shared<CBlockNoumStr>("target"));
	 assert(q_true_2.result == QEquals);

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"items is a list of object  that varies", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"list of prohibited items is a list of object  that varies", ISLOG));

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"items is  ( diary, book and box )", ISLOG));

    std::list<HBlock> alist = {noum("book"), noum("box")};
	auto q_true_3 = interpreter->query_is_extern(noum("items"), std::make_shared<CBlockList>(  alist));
   // assert(q_true_3 == QEquals);


	auto q_qq=  interpreter->query(Statement::Parser_Stmt(&parse,"target is listed in items", ISLOG));


	auto q_select = interpreter->query(Statement::Parser_Stmt(&parse," diary is ( low or medium ) ", ISLOG));


	auto q_all_of = interpreter->query(Statement::Parser_Stmt(&parse," ( all items ) are object ", ISLOG));
	auto q_any_of = interpreter->query(Statement::Parser_Stmt(&parse," ( any items ) are red ", ISLOG));

    return  ;

}
void testeParser_listB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	string s_price = R"(

object is a kind 
distance is a kind of value 
object has a distance

book is a object 
box is a object
diary is a object


far is a distance
near is a distance 
closest is a distance 

distance of book  is far 
distance of box  is far 
distance of diary  is near 

items is a list of object  that varies
items is  ( diary, book and box )

 

)";
  
	auto q_all_of = interpreter->exec_eval(Expression::Parser_Expression(&parse," all distance of items   ", true), nullptr,nullptr);
	
	q_all_of->dump("");


	return;
}


void testeParser_listC()
{
	


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	string s_price = R"(

object is a kind 
distance is a kind of value 
object has a distance

book is a object 
box is a object
diary is a object


far is a distance
near is a distance 
closest is a distance 

distance of book  is far 
distance of box  is far 
distance of diary  is near 

items is a list of object  that varies
items is  ( diary, book and box )

 

)";

	auto q_all_of = interpreter->exec_eval(Expression::Parser_Expression(&parse, " all distance of items   ", true), nullptr,nullptr);

	q_all_of->dump("");

	assert(q_all_of != nullptr);

	return;



}

void testeParser_listAll(void )
{
	//testeParser_listB();
	testeParser_listC();

}