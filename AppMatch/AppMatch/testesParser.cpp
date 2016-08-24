#include "Parser.h"
#include <iostream>

#define ISLOG true

std::vector<HTerm> decompose(std::string phase);;

std::string decompose_bracket(std::string phase, std::string dlm);

CList *mk_CList_Literal(std::vector<HTerm> strList);

void testeParser_1() {
    std::string phase_1 = "(red  book)    is a kind of    thing  ";
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

        /*interpreter->execute(parse.parser_stmt("  book is a kind of thing "));
        interpreter->execute(parse.parser_stmt("diary are an book "));
        interpreter->execute(parse.parser_stmt("book is small "));*/
        //parse.parser_stmt("book is a kind of thing  ")->dump("");
        //std::cout << std::endl;
        //	parse.parser_stmt("diary are an book")->dump("");
        //std::cout << std::endl;
       // parse.parser_stmt("book is small ")->dump("");
        //std::cout << std::endl;


       // parse.parser_stmt("(iron, silver and chopper)  are ( kinds of metal)")->dump("");
        //std::cout << std::endl;




    }

    {
        CParser parse(interpreter);
        std::string phase_1 = "thing is a kind ";
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
        std::string phase_1 = "book is a kind of thing ";
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
        std::string phase_1 = "magic object is a kind  ";
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
        std::string phase_1 = "special book is a kind of book ";
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
        std::string phase_1 = "special book is a kind of magic object ";
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
        std::string phase_1 = "diary is a special book ";
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

        std::string phase_1 = "(chopper, iron )  are kinds of metal  ";
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
        std::string phase_1 = "rare metal  is a kind  of metal ";
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
        std::string phase_1 = "(gold, silver )  are kinds of rare metal  ";
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
    //bool qclass_i = interpreter->is_derivadeOf(std::make_shared<CBlockInstance>("diary"), std::make_shared<CBlockKindThing>("thing"));
    std::cout << "Done" << std::endl;
    return;
}

void testeParser_2a() {
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(parse.parser_stmt("thing is a kind  "));
    interpreter->execute_init(parse.parser_stmt("book is a kind of thing "));
    interpreter->execute_init(parse.parser_stmt("book  can be normal , huge or  small"));

    {
        std::string phase_1 = "book is usually small ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    interpreter->execute_init(parse.parser_stmt("book can be read"));
    {
        std::string phase_1 = "diary is a book ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        std::string phase_1 = "diary is not read ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    interpreter->dump_instance("diary");

    QueryResul q_true = interpreter->query_is(std::make_shared<CBlockNoum>("diary"),
                                              std::make_shared<CBlockNoum>("read"));
    QueryResul q_false = interpreter->query_is(std::make_shared<CBlockNoum>("diary"),
                                               std::make_shared<CBlockNoum>("huge"));
    std::cout << "Done" << std::endl;

    {
        std::string phase_1 = "color of book is usually white ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }
    {
        std::string phase_1 = "the (length of (internal description of  a container )) is usually ( lenght of ( Its cramped in here))";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    std::cout << "Done" << std::endl;
    return;
}

void testeParser_3() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        std::string phase_1 = "eat  is (an action  applying to (an thing ) )";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
    {
        std::string phase_1 = "(cut ) is    an action   applying to (an thing ) and (a Cutter)   ";
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
        std::string phase_1 = "a thing can be discovered or secret";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "( a person ) has a (table-name) called (the opinion-table)";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "the (singing action) has a (text) called the (lyric sung)";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "the torch has a brightness ";
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
        std::string phase_1 = "to decide what (room) is (the safest location) : (decide on) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
    {
        std::string phase_1 = "to decide what (person) is the (brother to/of (sibling - a person)) : (decide on (son of ( fater of sibling) )  ) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "to decide if X is greater than Y : (decide on ( X > Y) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "to decide if X is sucessor of Y : (decide on ( X   == Y + 1) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "to decide what number  is sucessor of Y : (decide on (  Y + 1) )    ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }

    {
        std::string phase_1 = "to decide what (indexed text) is ((T - text) doubled) : (decide on T T ) ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
    }
}


void testeParser_6()//kind of value
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        std::string phase_1 = "a limb is a kind of value";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        interpreter->execute_init(parse.parser_stmt("color is a kind of value"));
        interpreter->execute_init(parse.parser_stmt("color can be light or dark"));
        interpreter->execute_init(parse.parser_stmt("color can be cold or warm"));
        interpreter->execute_init(parse.parser_stmt("color is usually light"));
    }

    {
        std::string phase_1 = "an aspect ratio is a kind of value";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        std::string phase_1 = "   blue, green, yellow  and red are color ";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG) {
            res->dump("");
            std::cout << std::endl;
        }
        interpreter->execute_init(res);
    }

    {
        interpreter->execute_init(parse.parser_stmt("black is a color"));
        QueryResul q_tru = interpreter->query_is(std::make_shared<CBlockNoum>("black"),
                                                 std::make_shared<CBlockNoum>("light"));
        interpreter->execute_init(parse.parser_stmt("black is dark"));
        QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockNoum>("black"),
                                                std::make_shared<CBlockNoum>("light"));

        std::string phase_1 = " ... ";
    }
    {
        interpreter->execute_init(parse.parser_stmt("warm color is a  kind of color"));
        interpreter->execute_init(parse.parser_stmt("warm color is usually warm"));

        interpreter->execute_init(parse.parser_stmt("red is a warm color"));
        QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockNoum>("red"),
                                                std::make_shared<CBlockNoum>("warm"));

        std::string phase_1 = " ... ";
    }
    //std::cout << std::endl;
}


void testeParser_6a()//kind of value
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        interpreter->execute_init(parse.parser_stmt("color is a kind of value"));
        interpreter->execute_init(parse.parser_stmt("blue, green, yellow  and red are color"));
        interpreter->execute_init(parse.parser_stmt("thing is a kind "));
        interpreter->execute_init(parse.parser_stmt("book is a thing"));
        interpreter->execute_init(parse.parser_stmt("book has a color"));
        interpreter->execute_init(parse.parser_stmt("color of book is red "));
    }

    QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockProperty>(std::make_shared<CBlockNoum>("color"),
                                                                             std::make_shared<CBlockNoum>("book")),
                                            std::make_shared<CBlockNoum>("red"));

    std::cout << std::endl;
}


void testeParser_7a()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        interpreter->execute_init(parse.parser_stmt("thing is a kind "));
        interpreter->execute_init(parse.parser_stmt("book is a thing "));
        interpreter->execute_init(parse.parser_stmt("diary is a thing "));
    }
    {
        auto block = parse.parser_stmt("to decide what (thing) is (the best book) : diary ");
        if (ISLOG) {
            block->dump("");
            std::cout << std::endl;
        }
        //interpreter->execute_init( block);

    }
    {
        auto block = parse.parser_stmt("if X is capable to open a Y ");
        if (ISLOG) {
            block->dump("");
            std::cout << std::endl;
        }
       // interpreter->execute_init(block);

    }

    QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockNoum>("[ best book ]"),
                                            std::make_shared<CBlockNoum>("diary"));

    std::cout << std::endl;

}

void testeParser_20() //custrom rlacions
{

    CParser parse(std::make_shared<CBlockInterpreter>());
    /*{
        std::string phase_1 = "Fanciness relates a ( thing called X ) to ( some money called Y ) when ( (the price of X) > (the price of Y ))";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG)
        {
            res->dump("");
            std::cout << std::endl;
        }
    }

     */

    //{
    //	std::string phase_1 = "the verb inside of implies a reverse container relation";
    //	auto res = parse.parser_stmt(phase_1);
    //	if (res == nullptr) throw "parse error";
    //	if (ISLOG)
    //	{
    //		res->dump("");
    //		std::cout << std::endl;
    //	}
    //}
    //{
    //	std::string phase_1 = "the verb contains implies a container relation";
    //	auto res = parse.parser_stmt(phase_1);
    //	if (res == nullptr) throw "parse error";
    //	if (ISLOG)
    //	{
    //		res->dump("");
    //		std::cout << std::endl;
    //	}
    //}


    //{
    //	std::string phase_1 = "book contains text";
    //	auto res = parse.parser_stmt(phase_1);
    //	if (res == nullptr) throw "parse error";
    //	if (ISLOG)
    //	{
    //		res->dump("");
    //		std::cout << std::endl;
    //	}
    //}
    {
        auto block = parse.parser_stmt("the verb able to open implies a opening relation");
        if (ISLOG) {
            block->dump("");
            std::cout << std::endl;
        }
    }
    {
        auto block = parse.parser_stmt("X is  able   to open   Z");
        if (ISLOG) {
            block->dump("");
            std::cout << std::endl;
        }
    }
    std::cout << "----------------------------------------" << std::endl;
    {
        auto block = parse.parser_stmt("to decide if (X    able   to open   Z) : (decides on true)");
        if (ISLOG) {
            block->dump("");
            std::cout << std::endl;
        }
    }


    /*{
        std::string phase_1 = "let L be the (list of ( things fancier than/of/in/on 20 ) ) )";
        auto res = parse.parser_stmt(phase_1);
        if (res == nullptr) throw "parse error";
        if (ISLOG)
        {
            res->dump("");
            std::cout << std::endl;
        }
    }*/
}

void testeParser_21() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        {
            std::string phase_1 = "the verb ( stuck to ) implies a stuking relation ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "coin is stuck to box";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "the verb visible by implies a visibility relation";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "definition : (a thing is hindering) if ( ( it is stuck to the noun) and (it is not within the location ) )";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "definition : (a thing is in same room ) if ( ( location of it  ) is ( location of player ) )";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "definition : (a thing is hide ) if ( it is not visible by player ) and ( it is in same room )";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }
        {
            std::string phase_1 = "definition : (a thing is in ( place : location )  ) if ( location of it is place ) ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "the verb made of implies the materiality relation ";

            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }
        {
            std::string phase_1 = "coin is made of golden";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

    }

}


void testeParser_22() {
    CParser parse(std::make_shared<CBlockInterpreter>());
    {
        {
            std::string phase_1 = " use_with is an action applying to (one thing) and (a thing)  ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "understand : use  [ a thing ] as use_with ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "understand : use  [ a thing  - keyer ] with [ a thing ] as use_with ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

        {
            std::string phase_1 = "  use key with box ";
            auto res = parse.parser_stmt(phase_1);
            if (res == nullptr) throw "parse error";
            if (ISLOG) {
                res->dump("");
                std::cout << std::endl;
            }
        }

    }
}


void testeParser() {
    // testeParser_1();

    for (int k = 0; k < 100; ++k)
    {
        testeParser_2();
        //testeParser_2a();
        //testeParser_3();
        //testeParser_4();
        //testeParser_5();
        //testeParser_6();
        // testeParser_7a();
        //testeParser_20();
        std::cout << ".";
    }
    std::cout << std::endl;
}