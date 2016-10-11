//
// Created by eraldo.rangel on 12/09/2016.
//
#include "BaseTest.hpp"
#include <cassert>


void testeRelation1() {

    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("direction is a kind  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("room is a kind  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("garden is a room  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("hall is a room  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("key is a thing  ", ISLOG));
    interpreter->execute_init(parse.parser_stmt("box is a thing  ", ISLOG));

    std::list< std::string >  slist(	{
                                                "Marriage relates (a person ) to another",
                                                "Marriage relates (a person ) to ( another called the spouse )",
                                                "Revenge relates (a person ) to various people",
                                                "Pet-ownership relates ( various animals ) to a person",
                                                "Pet-ownership relates ( various animals ) to ( a person called the owner)",
                                                "Awareness relates (various people ) to various people",
                                                "Meeting relates (a people ) to each other",
                                                "Nationality relates (a people ) to each other in groups"
                                        });
    for( auto s : slist)
    {
       // std::cout << s << std::endl;
       // auto p = parse.parser_stmt(s, ISLOG);
       // interpreter->execute_init(p );
    }

    

    interpreter->execute_init(parse.parser_stmt("unloking relates (a thing ) to another", ISLOG));
    interpreter->execute_init(parse.parser_stmt("the verb  unlock  implies a  unloking relation", ISLOG));
    interpreter->execute_init(parse.parser_stmt("the verb ( unlocked by ) implies a  unloking relation", ISLOG));

 

    interpreter->execute_now (parse.parser_stmt("   key unlocked  by box  ", ISLOG));

 
     
     
    //interpreter->execute_init(parse.parser_stmt("to decide if ( thing called T ) unloked by ( thing called K ) :  K unlocks T   ", ISLOG));

    //auto ret_true_a = interpreter->query(parse.parser_stmt("north points to exit of hall  ", ISLOG));

    auto ret_true_a = interpreter->query(parse.parser_stmt(" key unlock box ", ISLOG));
    auto ret_true_b = interpreter->query(parse.parser_stmt(" box unlock key ", ISLOG));
    auto ret_true_c = interpreter->query(parse.parser_stmt(" key unlock garden ", ISLOG));
    auto ret_true_d = interpreter->query(parse.parser_stmt(" key is unlocked by box ", ISLOG));

   // auto ret_true_b = interpreter->query(parse.parser_stmt("garden exits to south   ", ISLOG));


    return;
}