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
    interpreter->execute_init(parse.parser_stmt("the verb ( unlocked by ) implies a reverse  unloking relation", ISLOG));

 

	interpreter->execute_now(parse.parser_stmt("   box is unlocked by   key  ", ISLOG));
   // interpreter->execute_now (parse.parser_stmt("   key unlocked  by box  ", ISLOG)); 
     
    //interpreter->execute_init(parse.parser_stmt("to decide if ( thing called T ) unloked by ( thing called K ) :  K unlocks T   ", ISLOG));
	 

    auto ret_true_a = interpreter->query(parse.parser_stmt(" key unlock box ", ISLOG));
    auto ret_false_b = interpreter->query(parse.parser_stmt(" box unlock key ", ISLOG));
    auto ret_false_c = interpreter->query(parse.parser_stmt(" key unlock garden ", ISLOG));
    auto ret_true_d = interpreter->query(parse.parser_stmt(" box is unlocked by key ", ISLOG)); 

	assert(ret_true_a == QEquals);
	assert(ret_false_b == QNotEquals);
	assert(ret_false_c == QNotEquals);
	assert(ret_true_d == QEquals);

    return;
}

void testeRelation2() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("box is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("key is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("book   is a thing  ", ISLOG));

	interpreter->execute_init(parse.parser_stmt("containner relates (a thing ) to another", ISLOG));	
	interpreter->execute_init(parse.parser_stmt("the verb  contains  implies a  containner relation", ISLOG));

	interpreter->execute_now(parse.parser_stmt("  box contains key  ", ISLOG));
	interpreter->execute_now(parse.parser_stmt("  box contains book  ", ISLOG)); //remove a relacao anterior



	auto ret_false_a = interpreter->query(parse.parser_stmt(" box contains key ", ISLOG));
	auto ret_true_b = interpreter->query(parse.parser_stmt(" box contains book ", ISLOG));

	assert(ret_false_a == QEquals);
	assert(ret_true_b == QEquals);
	return;
}


void testeRelation3() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("recipe is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("cake is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("soupe is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("recipe1 is a recipe  ", ISLOG)); 
	interpreter->execute_init(parse.parser_stmt("recipe2 is a recipe  ", ISLOG));
	 
	 
	interpreter->execute_init(parse.parser_stmt("recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("the verb produce  implies a  recipment relation", ISLOG));	
	interpreter->execute_init(parse.parser_stmt("the verb produces implies a  recipment relation", ISLOG));

	interpreter->execute_now(parse.parser_stmt("  recipe1 produce cake  ", ISLOG));
	interpreter->execute_now(parse.parser_stmt("  recipe2 produces soupe  ", ISLOG)); // nao remove a relacao anterior



	auto ret_true_a = interpreter->query(parse.parser_stmt(" recipe1 produces cake ", ISLOG)); 
	assert(ret_true_a == QEquals);
	 
	auto ret_true_b = interpreter->query(parse.parser_stmt(" product of recipe2 is soupe ", ISLOG));
	assert(ret_true_b == QEquals);


	auto ret_true_c = interpreter->query(parse.parser_stmt(" recipe  of cake  is  recipe1  ", ISLOG));
	assert(ret_true_c == QEquals);

	return;
}


void testeRelation4() {



	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.parser_stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("recipe is a kind  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("cake is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("soupe is a thing  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("(cake recipe) is a recipe  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("recipe2 is a recipe  ", ISLOG));


	interpreter->execute_init(parse.parser_stmt("recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("the verb produce  implies a  recipment relation", ISLOG));
	interpreter->execute_init(parse.parser_stmt("the verb produced by implies a  reverse recipment relation", ISLOG));

	interpreter->execute_now(parse.parser_stmt(" recipe of cake is  (cake recipe) ", ISLOG));
	interpreter->execute_now(parse.parser_stmt(" product of recipe2 is soupe ", ISLOG));
	
	 

	auto ret_true_a = interpreter->query(parse.parser_stmt(" (cake recipe) produce cake ", ISLOG));
	assert(ret_true_a == QEquals);

	auto ret_true_b = interpreter->query(parse.parser_stmt(" soupe is produced by recipe2 ", ISLOG));
	assert(ret_true_b == QEquals);


	auto ret_false_c = interpreter->query(parse.parser_stmt(" recipe  of cake  is  recipe2  ", ISLOG));
	assert(ret_false_c == QNotEquals);

	interpreter->execute_now(parse.parser_stmt(" product of recipe2 is nothing ", ISLOG)); //ecluit uma relacao
	auto ret_false_d = interpreter->query(parse.parser_stmt(" soupe is produced by recipe2 ", ISLOG));
	assert(ret_false_d == QNotEquals);

	return;


}