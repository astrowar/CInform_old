//
// Created by eraldo.rangel on 12/09/2016.
//
#include "BaseTest.h"
#include <cassert>


void testeRelation1() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);



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
        std::cout << s << std::endl;
        auto p = parse.parser_stmt(s, ISLOG);
        interpreter->execute_init(p );
    }

    std::cout << std::endl;

    return;

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("direction is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("room is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("garden is a room  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("hall is a room  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("north is a direction  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("south is a direction  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("the verb  from   implies a  direction relation", ISLOG));

	interpreter->execute_init(parse.parser_stmt("the verb (points to)  implies a  dynamic relation", ISLOG));
    interpreter->execute_init(parse.parser_stmt("the verb (exits to)  implies a  dynamic relation", ISLOG));

	interpreter->execute_init(parse.parser_stmt("the verb  wears  implies a  dynamic relation", ISLOG));
	 interpreter->execute_init(parse.parser_stmt("the verb  in  implies a  dynamic relation", ISLOG));
	interpreter->execute_init(parse.parser_stmt("to decide what ( room ) is ( north from  hall ) :  garden   ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("to decide what ( room ) is ( south from  garden ) :  hall   ", ISLOG));


	interpreter->execute_init(parse.parser_stmt(
	"to decide what ( direction )  points to exit of ( room called R )   : north ", ISLOG));


    interpreter->execute_init(parse.parser_stmt(
            "to decide if (room called R ) exits to ( direction called D ) :  D points to exit of R  ", ISLOG));


    interpreter->execute_init(parse.parser_stmt(
            " south points to exit of garden  ", ISLOG));


	//auto ret_true_a = interpreter->query(parse.parser_stmt("north points to exit of hall  ", ISLOG));

    auto ret_true_a = interpreter->query(parse.parser_stmt("hall exits to north   ", ISLOG));

   // auto ret_true_b = interpreter->query(parse.parser_stmt("garden exits to south   ", ISLOG));


    return;
}