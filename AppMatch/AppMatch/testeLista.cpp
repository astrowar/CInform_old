
#include "BaseTest.hpp"
#include <cassert>

HBlockNoum noum(std::string n) {return std::make_shared<CBlockNoum>(n); };

void testeParser_listA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
 
	 interpreter->execute_init(parse.Parser_Stmt("object is a kind  ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("book is a object  ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("box is a object  ", ISLOG));

	 interpreter->execute_init(parse.Parser_Stmt("target is a  object  that varies", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("target is book ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("box is a object  ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("diary is a object  ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("diary can be (green , red or blue)  ", ISLOG));
	 interpreter->execute_init(parse.Parser_Stmt("diary is red  ", ISLOG));

     interpreter->execute_init(parse.Parser_Stmt("the verb listed in implies the listed_in relation", ISLOG));

	 auto q_true = interpreter->query_is_extern(std::make_shared<CBlockNoum>("target"), std::make_shared<CBlockNoum>("book"));
	 assert(q_true.result == QEquals);

	 auto q_true_2 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("book"), std::make_shared<CBlockNoum>("target"));
	 assert(q_true_2.result == QEquals);

	interpreter->execute_init(parse.Parser_Stmt("items is a list of object  that varies", ISLOG));
	//interpreter->execute_init(parse.Parser_Stmt("list of prohibited items is a list of object  that varies", ISLOG));

    interpreter->execute_init(parse.Parser_Stmt("items is  ( diary, book and box )", ISLOG));

    std::list<HBlock> alist = {noum("book"), noum("box")};
	auto q_true_3 = interpreter->query_is_extern(noum("items"), std::make_shared<CBlockList>(  alist));
   // assert(q_true_3 == QEquals);


	auto q_qq=  interpreter->query(parse.Parser_Stmt("target is listed in items", ISLOG));


	auto q_select = interpreter->query(parse.Parser_Stmt(" diary is ( low or medium ) ", ISLOG));


	auto q_all_of = interpreter->query(parse.Parser_Stmt(" ( all items ) are object ", ISLOG));
	auto q_any_of = interpreter->query(parse.Parser_Stmt(" ( any items ) are red ", ISLOG));

    return  ;

}
void testeParser_listB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

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
  
	auto q_all_of = interpreter->exec_eval(parse.Parser_Expression(" all distance of items   ", true), nullptr );
	
	q_all_of->dump("");


	return;
}

void testeParser_listAll(void )
{
	testeParser_listB();

}