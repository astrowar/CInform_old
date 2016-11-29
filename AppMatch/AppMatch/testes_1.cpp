
#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;



//Basic Assertations

void testeParser_1() {
    
}

void testeParser_2() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();

   

    {
        CParser parse(interpreter);
        string phase_1 = "thing is a kind ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
         
         interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "book is a kind of thing ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
         
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "magic object is a kind  ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
         
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of book ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);

        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of magic object ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
       
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "diary is a special book ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"metal  is a kind ", ISLOG));

        string phase_1 = "(chopper, iron )  are kinds of metal  ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "rare metal  is a kind  of metal ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "(gold, silver )  are kinds of rare metal  ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

	QueryResultContext q = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("thing"));
    bool qclass_k = interpreter->is_derivadeOf(std::make_shared<CBlockKindThing>("silver"),
                                               std::make_shared<CBlockKindThing>("metal"));

	assert(q.result == QEquals);
	assert(qclass_k);

    //bool qclass_i = interpreter->is_derivadeOf(std::make_shared<CBlockInstance>("diary"), std::make_shared<CBlockKindThing>("thing"));
    logMessage( "Done" );
    return;
}

void testeParser_2a() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a kind of thing ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"kelement is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"fire is a kelement ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"air is a kelement ", ISLOG));

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"book  can be normal , huge or  small", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing has a thing called element", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"fire is a kelement ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"air is a kelement ", ISLOG));
 
	interpreter->execute_init(Statement::Parser_Stmt(&parse," element of thing is usually fire ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse," element of book is usually air ", ISLOG));

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"book can be read", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is a book", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"rock is a thing", ISLOG));

  
	QueryResultContext q_true = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), 		std::make_shared<CBlockNoum>("read"));
	assert(q_true.result == QEquals);

    {
        string phase_1 = "diary is not read ";
        auto res = Statement::Parser_Stmt(&parse,phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

    interpreter->dump_instance("diary" );

	QueryResultContext q_false_1 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("read"));
	QueryResultContext q_false_2 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("huge"));
	QueryResultContext q_false_2n = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("normal"));


	assert(q_false_1.result == QNotEquals);
	assert(q_false_2.result == QNotEquals);
	assert(q_false_2n.result == QEquals);

    logMessage( "Done" );

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"element of  diary is air "));

	auto propV =std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("diary"));
	QueryResultContext q_true_2 = interpreter->query_is_extern(propV,	std::make_shared<CBlockNoum>("air"));
	assert(q_true_2.result == QEquals);
    
	auto propT = std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("rock"));
	QueryResultContext q_true_3 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("air"));
	QueryResultContext q_true_4 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("fire"));
	QueryResultContext q_true_5 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("water"));

	assert(q_true_3.result == QEquals);
	assert(q_true_4.result == QNotEquals);
	assert(q_true_5.result == QNotEquals);
    logMessage( "Done" );
    return;
}
