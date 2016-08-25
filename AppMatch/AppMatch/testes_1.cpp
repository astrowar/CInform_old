
#include "BaseTest.h"
#include <cassert>

//Basic Assertations

void testeParser_1() {
    string phase_1 = "(red  book)    is a kind of    thing  ";
    phase_1 = "( book,  stone and  ( metal bird))  are  some things ";
    phase_1 = decompose_bracket(phase_1, "(");
    phase_1 = decompose_bracket(phase_1, ")");
    std::cout << phase_1 << std::endl;

    std::vector<HTerm> lst = decompose(phase_1);
    CList *lst_ptr = mk_CList_Literal(lst);
    std::cout << lst_ptr->repr() << std::endl;
    //MTermSetCombinatoriaList mlist = getCombinatorias(lst_ptr->asVector(), 3);

    auto vecList = lst_ptr->asVector();
    FuncCombinatoria f_disp = [](MTermSetCombinatoria &x) {
        std::cout << get_repr(x) << std::endl;
        return false;
    };
    applyCombinatorias(vecList, 3, f_disp);

    std::cout << "..." << std::endl;
}

void testeParser_2() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();

   

    {
        CParser parse(interpreter);
        string phase_1 = "thing is a kind ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
         interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "book is a kind of thing ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "magic object is a kind  ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of book ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "special book is a kind of magic object ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        string phase_1 = "diary is a special book ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        CParser parse(interpreter);
        interpreter->execute_init(parse.parser_stmt("metal  is a kind "));

        string phase_1 = "(chopper, iron )  are kinds of metal  ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "rare metal  is a kind  of metal ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }
    {
        CParser parse(interpreter);
        string phase_1 = "(gold, silver )  are kinds of rare metal  ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    QueryResul q = interpreter->query_is(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("thing"));
    bool qclass_k = interpreter->is_derivadeOf(std::make_shared<CBlockKindThing>("silver"),
                                               std::make_shared<CBlockKindThing>("metal"));

	assert(q == QEquals);
	assert(qclass_k);

    //bool qclass_i = interpreter->is_derivadeOf(std::make_shared<CBlockInstance>("diary"), std::make_shared<CBlockKindThing>("thing"));
    std::cout << "Done" << std::endl;
    return;
}

void testeParser_2a() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(parse.parser_stmt("thing is a kind  "));
    interpreter->execute_init(parse.parser_stmt("book is a kind of thing "));

	interpreter->execute_init(parse.parser_stmt("kelement is a kind  "));
	interpreter->execute_init(parse.parser_stmt("fire is a kelement "));
	interpreter->execute_init(parse.parser_stmt("air is a kelement "));

    interpreter->execute_init(parse.parser_stmt("book  can be normal , huge or  small")); 
	interpreter->execute_init(parse.parser_stmt("thing has a thing called element"));	

	interpreter->execute_init(parse.parser_stmt("fire is a kelement "));
	interpreter->execute_init(parse.parser_stmt("air is a kelement "));
 
	interpreter->execute_init(parse.parser_stmt(" element of thing is usually fire "));
	interpreter->execute_init(parse.parser_stmt(" element of book is usually air "));

    interpreter->execute_init(parse.parser_stmt("book can be read"));

	interpreter->execute_init(parse.parser_stmt("diary is a book"));
	interpreter->execute_init(parse.parser_stmt("rock is a thing"));

  
	QueryResul q_true = interpreter->query_is(std::make_shared<CBlockNoum>("diary"), 		std::make_shared<CBlockNoum>("read"));
	assert(q_true == QEquals);

    {
        string phase_1 = "diary is not read ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    interpreter->dump_instance("diary");

    QueryResul q_false_1 = interpreter->query_is(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("read"));
    QueryResul q_false_2 = interpreter->query_is(std::make_shared<CBlockNoum>("diary"),  std::make_shared<CBlockNoum>("huge"));
	QueryResul q_false_2n = interpreter->query_is(std::make_shared<CBlockNoum>("diary"), std::make_shared<CBlockNoum>("normal"));


	assert(q_false_1 == QNotEquals);
	assert(q_false_2 == QNotEquals);
	assert(q_false_2n == QEquals);

    std::cout << "Done" << std::endl;

	//interpreter->execute_init(parse.parser_stmt("element of  diary is air "));

	auto propV =std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("diary"));
	QueryResul q_true_2 = interpreter->query_is(propV,	std::make_shared<CBlockNoum>("air"));
	assert(q_true_2 == QEquals);
    
	auto propT = std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("element"), std::make_shared<CBlockNoum>("rock"));
	QueryResul q_true_3 = interpreter->query_is(propV, std::make_shared<CBlockNoum>("air"));
	QueryResul q_true_4 = interpreter->query_is(propV, std::make_shared<CBlockNoum>("fire"));
	QueryResul q_true_5 = interpreter->query_is(propV, std::make_shared<CBlockNoum>("water"));

	assert(q_true_3 == QEquals);
	assert(q_true_4 == QNotEquals);
	assert(q_true_5 == QNotEquals);
    std::cout << "Done" << std::endl;
    return;
}
