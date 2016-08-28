
#include "BaseTest.h"
#include <cassert>

HBlockNoum noum(std::string n) {return std::make_shared<CBlockNoum>(n); };

void testeParser_listA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
 
	 interpreter->execute_init(parse.parser_stmt("object is a kind  ", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("book is a object  ", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("box is a object  ", ISLOG));

	 interpreter->execute_init(parse.parser_stmt("target is a  object  that varies", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("target is book ", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("box is a object  ", ISLOG));

    interpreter->execute_init(parse.parser_stmt("the verb listed in implies the listed_in relation", ISLOG));

	 QueryResul q_true = interpreter->query_is(std::make_shared<CBlockNoum>("target"), std::make_shared<CBlockNoum>("book"));
	 assert(q_true == QEquals);

	 QueryResul q_true_2 = interpreter->query_is(std::make_shared<CBlockNoum>("book"), std::make_shared<CBlockNoum>("target"));
	 assert(q_true_2 == QEquals);

	interpreter->execute_init(parse.parser_stmt("items is a list of object  that varies", ISLOG));
	//interpreter->execute_init(parse.parser_stmt("list of prohibited items is a list of object  that varies", ISLOG));

    interpreter->execute_init(parse.parser_stmt("items is  ( book and box )", ISLOG));

    std::list<HBlock> alist = {noum("book"), noum("box")};
    QueryResul q_true_3 = interpreter->query_is(noum("items"), std::make_shared<CBlockList>(  alist));
   // assert(q_true_3 == QEquals);


    QueryResul q_qq=  interpreter->query(parse.parser_stmt("box is listed in items", ISLOG));
    return  ;
}
void testeParser_listB()
{
	

}