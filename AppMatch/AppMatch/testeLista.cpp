
#include "BaseTest.h"
#include <cassert>


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


	 QueryResul q_true = interpreter->query_is(std::make_shared<CBlockNoum>("target"), std::make_shared<CBlockNoum>("book"));
	 assert(q_true == QEquals);

	 QueryResul q_true_2 = interpreter->query_is(std::make_shared<CBlockNoum>("book"), std::make_shared<CBlockNoum>("target"));
	 assert(q_true_2 == QEquals);

	interpreter->execute_init(parse.parser_stmt("items is a list of object  that varies", ISLOG));



	return  ;
}
void testeParser_listB()
{
	

}