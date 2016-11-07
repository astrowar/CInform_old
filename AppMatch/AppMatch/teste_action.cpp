#include "BaseTest.hpp"

void testeParser_actionA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt(" apple is a thing  ", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("eat_this  is ( an action  applying to ( an thing ) )", ISLOG));
	 
	// interpreter->execute_init(parse.Parser_Stmt("understand : next to   [ thing  ] as X ", ISLOG));
	printf("===========================================================\n"); 
	interpreter->execute_init(parse.Parser_Stmt("understand : eat  ( a thing ) as eat_this ", ISLOG));
	// interpreter->execute_init(parse.Parser_Stmt("understand : bite all [  thing called X ] as  eat  X  ", ISLOG));

	//interpreter->execute_init(parse.Parser_Stmt(" apple is a thing  ", ISLOG));
	//interpreter->execute_init(parse.Parser_Stmt("  bite all apple ", ISLOG));

	//interpreter->execute_init(parse.Parser_Stmt("book is a object  ", ISLOG));
	printf("===========================================================\n");
	interpreter->execute_now(parse.Parser_Stmt("eat apple   ", ISLOG));

	return;
}


void testeParser_actionB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("apple is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("box is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("puting  is ( an action  applying to ( an thing ) and ( an thing)  )", ISLOG));
	
	
	interpreter->execute_init(parse.Parser_Stmt("understand : put  [ a thing called X ] intro [ box  called IB ]  as puting ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("understand : insert  [ a thing called X ] intro [ thing called B ] as put X intro B ", ISLOG));

	interpreter->execute_now(parse.Parser_Stmt(" insert ( apple and box )  intro  box ", true));


	 

	return;
}




void testeParser_actionC()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("thing has a text called description  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("apple is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("description of apple is (text a red and round apple )  ", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("say_text  is ( an action  applying to ( an text ) ) ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("say_text has a thing called speaker  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("understand : say  [ a text called X ]   as say_text  ", ISLOG)); 


	interpreter->execute_init(parse.Parser_Stmt("speaker of  say_text is apple ", ISLOG));

	interpreter->execute_now(parse.Parser_Stmt(" say  (text apple) ", ISLOG));
 


	return;
}

void testAction_all()
{
	testeParser_actionA(); 
	//testeParser_actionB(); 
	//testeParser_actionC();
}