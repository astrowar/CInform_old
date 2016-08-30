#include "BaseTest.h"

void testeParser_actionA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("eat_this  is ( an action  applying to ( an thing ) )", ISLOG));
	 
	// interpreter->execute_init(parse.parser_stmt("understand : next to   [ thing  ] as X ", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("understand : eat  [ a thing ] as eat_this ", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("understand : bite all [  thing called X ] as  eat  X  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("apple is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("  bite all apple ", ISLOG));

	//interpreter->execute_init(parse.parser_stmt("book is a object  ", ISLOG));
	//interpreter->execute_init(parse.parser_stmt("box is a object  ", ISLOG));

	return;
}


void testeParser_actionB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("puting  is ( an action  applying to ( an thing ) and ( an thing)  )", ISLOG));

	
	interpreter->execute_init(parse.parser_stmt("understand : put  [ a thing called X ] intro [ box  called IB ]  as puting ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("understand : insert  [ a thing ] intro [ thing ]  as put X intro B ", ISLOG));
	 

	interpreter->execute_init(parse.parser_stmt("apple is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("box is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt(" insert red apple intro large box ", ISLOG));
}

void testeParser_actionC()
{

}