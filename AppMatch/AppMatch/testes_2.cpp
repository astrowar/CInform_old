
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

	interpreter->execute_init(parse.parser_stmt("to decide what ( thing ) is oposite of ( far item ) :  ( special item )    ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("to decide what ( thing ) is ( special item ) :   apple    ", ISLOG));

	auto ret = interpreter->query(parse.parser_stmt("( special item ) is apple  ", ISLOG));
	auto ret_2 = interpreter->query(parse.parser_stmt("( far item ) is apple  ", ISLOG));
	return;

}


void testeParser_5c() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("apple is a thing  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("to decide what ( thing ) is oposite of ( thing called X ) :  X   ", ISLOG));	

	auto ret = interpreter->query(parse.parser_stmt(" oposite of apple  is apple  ", ISLOG));
	
	return;

}

void testeParser_5d() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("room is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("apple is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("book is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("place is a room  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("apple can be lit  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("apple is  lit  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("the verb ( in same ) implies a equality relation ", ISLOG));
	 

	interpreter->execute_init(parse.parser_stmt("definition : ( (lit thing called T ) is in same ( room called R ) ) if ( (location of T ) is R )", ISLOG));

	//interpreter->execute_init(parse.parser_stmt("to decide what ( thing ) is oposite of ( thing called X ) :  X   ", ISLOG));
	//auto ret = interpreter->query(parse.parser_stmt(" oposite of apple  is apple  ", ISLOG));

	auto ret_lit = interpreter->query(parse.parser_stmt("apple is lit ", ISLOG));
	auto ret_true = interpreter->query(parse.parser_stmt("apple is in same  place ", ISLOG));
	auto ret_false = interpreter->query(parse.parser_stmt("book is in same  place ", ISLOG));
	return;

}

void testeParser_5e() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("direction is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("room is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("garden is a room  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("hall is a room  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("north is a direction  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("south is a direction  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("the verb  from   implies a  connection relation", ISLOG));

	//interpreter->execute_init(parse.parser_stmt("definition : ( a direction called thataway ) is viable if (  thataway from ( the location ) ) is ( a room )", ISLOG));
	interpreter->execute_init(parse.parser_stmt("definition : ( a direction called thataway ) is viable if (  thataway is north )", ISLOG));

	auto ret_true = interpreter->query(parse.parser_stmt("north is viable", ISLOG));
	return;
}