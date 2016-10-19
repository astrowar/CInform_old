
#include "BaseTest.hpp"
#include <cassert>

//Basic Assertations

void testeParser_1() {
    string phase_1 = "(red  book)    is a kind of    thing  ";
    phase_1 = "( book,  stone and  ( metal bird))  are  some things ";
    phase_1 = decompose_bracket(phase_1, "(");
    phase_1 = decompose_bracket(phase_1, ")");
   logMessage( phase_1);

    std::vector<HTerm> lst = decompose(phase_1);
    CList *lst_ptr = mk_CList_Literal(lst);
	logMessage(lst_ptr->repr() );
    //MTermSetCombinatoriaList mlist = getCombinatorias(lst_ptr->asVector(), 3);

    auto vecList = lst_ptr->asVector();
    FuncCombinatoria f_disp = [](MTermSetCombinatoria &x) {
		logMessage(get_repr(x) );
        return false;
    };
    applyCombinatorias(vecList, 3, f_disp);

	logMessage("..." );
}

void testeParser_2() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();

   

    {
        CParser parse(interpreter);
        string phase_1 = "thing is a kind ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
         
         interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "book is a kind of thing ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
         
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "magic object is a kind  ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
         
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of book ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
			logMessage("");
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of magic object ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
       
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "diary is a special book ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        interpreter->execute_init(parse.Parser_Stmt("metal  is a kind ", ISLOG));

        string phase_1 = "(chopper, iron )  are kinds of metal  ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "rare metal  is a kind  of metal ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "(gold, silver )  are kinds of rare metal  ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

    QueryResul q = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("thing"));
    bool qclass_k = interpreter->is_derivadeOf(std::make_shared<CBlockKindThing>("silver"),
                                               std::make_shared<CBlockKindThing>("metal"));

	assert(q == QEquals);
	assert(qclass_k);

    //bool qclass_i = interpreter->is_derivadeOf(std::make_shared<CBlockInstance>("diary"), std::make_shared<CBlockKindThing>("thing"));
    logMessage( "Done" );
    return;
}

void testeParser_2a() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("book is a kind of thing ", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("kelement is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("fire is a kelement ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("air is a kelement ", ISLOG));

    interpreter->execute_init(parse.Parser_Stmt("book  can be normal , huge or  small", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("thing has a thing called element", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("fire is a kelement ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("air is a kelement ", ISLOG));
 
	interpreter->execute_init(parse.Parser_Stmt(" element of thing is usually fire ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt(" element of book is usually air ", ISLOG));

    interpreter->execute_init(parse.Parser_Stmt("book can be read", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("diary is a book", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("rock is a thing", ISLOG));

  
	QueryResul q_true = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), 		std::make_shared<CBlockNoum>("read"));
	assert(q_true == QEquals);

    {
        string phase_1 = "diary is not read ";
        auto res = parse.Parser_Stmt(phase_1, ISLOG);
        
        interpreter->execute_init(res);
    }

    interpreter->dump_instance("diary" );

    QueryResul q_false_1 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("read"));
    QueryResul q_false_2 = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("huge"));
	QueryResul q_false_2n = interpreter->query_is_extern(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("normal"));


	assert(q_false_1 == QNotEquals);
	assert(q_false_2 == QNotEquals);
	assert(q_false_2n == QEquals);

    logMessage( "Done" );

	//interpreter->execute_init(parse.Parser_Stmt("element of  diary is air "));

	auto propV =std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("diary"));
	QueryResul q_true_2 = interpreter->query_is_extern(propV,	std::make_shared<CBlockNoum>("air"));
	assert(q_true_2 == QEquals);
    
	auto propT = std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("rock"));
	QueryResul q_true_3 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("air"));
	QueryResul q_true_4 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("fire"));
	QueryResul q_true_5 = interpreter->query_is_extern(propV, std::make_shared<CBlockNoum>("water"));

	assert(q_true_3 == QEquals);
	assert(q_true_4 == QNotEquals);
	assert(q_true_5 == QNotEquals);
    logMessage( "Done" );
    return;
}
