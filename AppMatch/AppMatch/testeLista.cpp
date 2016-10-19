
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

	 QueryResul q_true = interpreter->query_is_extern(std::make_shared<CBlockNoum>("target"), std::make_shared<CBlockNoum>("book"));
	 assert(q_true == QEquals);

	 QueryResul q_true_2 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("book"), std::make_shared<CBlockNoum>("target"));
	 assert(q_true_2 == QEquals);

	interpreter->execute_init(parse.Parser_Stmt("items is a list of object  that varies", ISLOG));
	//interpreter->execute_init(parse.Parser_Stmt("list of prohibited items is a list of object  that varies", ISLOG));

    interpreter->execute_init(parse.Parser_Stmt("items is  ( diary, book and box )", ISLOG));

    std::list<HBlock> alist = {noum("book"), noum("box")};
    QueryResul q_true_3 = interpreter->query_is_extern(noum("items"), std::make_shared<CBlockList>(  alist));
   // assert(q_true_3 == QEquals);


    QueryResul q_qq=  interpreter->query(parse.Parser_Stmt("target is listed in items", ISLOG));


	QueryResul q_select = interpreter->query(parse.Parser_Stmt(" diary is ( low or medium ) ", ISLOG));


	QueryResul q_all_of = interpreter->query(parse.Parser_Stmt(" ( all items ) are object ", ISLOG));
	QueryResul q_any_of = interpreter->query(parse.Parser_Stmt(" ( any items ) are red ", ISLOG));

    return  ;

}
void testeParser_listB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("object is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("distance is a kind of value ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("object has a distance ", ISLOG));


	interpreter->execute_init(parse.Parser_Stmt("book is a object  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("box is a object  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("diary is a object  ", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("far is a distance  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("near is a distance  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("closest is a distance  ", ISLOG));


	 

	interpreter->execute_init(parse.Parser_Stmt("distance of book  is far ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("distance of box  is far ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("distance of diary  is near ", ISLOG));


	interpreter->execute_init(parse.Parser_Stmt("items is a list of object  that varies", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("items is  ( diary, book and box )", ISLOG));

	QueryResul q_all_of = interpreter->query(parse.Parser_Stmt(" (all distance of items ) is (near or far)   ", ISLOG));


	return;
}