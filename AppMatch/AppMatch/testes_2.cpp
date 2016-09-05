
#include "BaseTest.h"
#include <cassert>

void testeParser_3() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        string phase_1 = "eat  is (an action  applying to (an thing ) )";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
    {
        string phase_1 = "(cut ) is    an action   applying to (an thing ) and (a Cutter)   ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
    //std::cout << "Done" << std::endl;
    return;
}

void testeParser_4() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        string phase_1 = "a thing can be discovered or secret";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "( a person ) has a (table-name) called (the opinion-table)";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "the (singing action) has a (text) called the (lyric sung)";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "the torch has a brightness ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }


    //"Brightness is a kind of value";
    //"The brightnesses are guttering, weak, radiant and blazing";
    //"The torch has a brightness";
    //	"The torch	is blazing";
    //"The torch is lit";
    // std::cout << std::endl;
    return;
}


void testeParser_5() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        string phase_1 = "to decide what (room) is (the safest location) : (decide on) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
    {
        string phase_1 = "to decide what (person) is the (brother to/of (sibling - a person)) : (decide on (son of ( fater of sibling) )  ) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "to decide if X is greater than Y : (decide on ( X > Y) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "to decide if X is sucessor of Y : (decide on ( X   == Y + 1) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "to decide what number  is sucessor of Y : (decide on (  Y + 1) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        string phase_1 = "to decide what (indexed text) is ((T - text) doubled) : (decide on T T ) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
}


void testeParser_5b() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG)); 
	interpreter->execute_init(parse.parser_stmt("apple is a thing  ", ISLOG));


	interpreter->execute_init(parse.parser_stmt("to decide what ( thing ) is ( special item ) : ( decide on apple  )  ", ISLOG));

	auto ret = interpreter->query(parse.parser_stmt("( special item ) is apple  ", ISLOG));

	return;

}