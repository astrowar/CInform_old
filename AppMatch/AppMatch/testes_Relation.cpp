//
// Created by eraldo.rangel on 12/09/2016.
//
#include "BaseTest.hpp"
#include <cassert>


void testeRelation1() {

    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("direction is a kind  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("room is a kind  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("garden is a room  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("hall is a room  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("key is a thing  ", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("box is a thing  ", ISLOG));

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
       // auto p = parse.Parser_Stmt(s, ISLOG);
       // interpreter->execute_init(p );
    }

    

    interpreter->execute_init(parse.Parser_Stmt("unloking relates (a thing ) to another", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("the verb  unlock  implies a  unloking relation", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("the verb ( unlocked by ) implies a reverse  unloking relation", ISLOG));

 

	interpreter->execute_now(parse.Parser_Stmt("   box is unlocked by   key  ", ISLOG));
   // interpreter->execute_now (parse.Parser_Stmt("   key unlocked  by box  ", ISLOG)); 
     
    //interpreter->execute_init(parse.Parser_Stmt("to decide if ( thing called T ) unloked by ( thing called K ) :  K unlocks T   ", ISLOG));
	 

    auto ret_true_a = interpreter->query(parse.Parser_Stmt(" key unlock box ", ISLOG));
    auto ret_false_b = interpreter->query(parse.Parser_Stmt(" box unlock key ", ISLOG));
    auto ret_false_c = interpreter->query(parse.Parser_Stmt(" key unlock garden ", ISLOG));
    auto ret_true_d = interpreter->query(parse.Parser_Stmt(" box is unlocked by key ", ISLOG)); 

	assert(ret_true_a == QEquals);
	assert(ret_false_b == QNotEquals);
	assert(ret_false_c == QNotEquals);
	assert(ret_true_d == QEquals);

    return;
}

void testeRelation2() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("box is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("key is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("book   is a thing  ", ISLOG));

	interpreter->execute_init(parse.Parser_Stmt("containner relates (a thing ) to another", ISLOG));	
	interpreter->execute_init(parse.Parser_Stmt("the verb  contains  implies a  containner relation", ISLOG));

	interpreter->execute_now(parse.Parser_Stmt("  box contains key  ", ISLOG));
	interpreter->execute_now(parse.Parser_Stmt("  box contains book  ", ISLOG)); //remove a relacao anterior



	auto ret_false_a = interpreter->query(parse.Parser_Stmt(" box contains key ", ISLOG));
	auto ret_true_b = interpreter->query(parse.Parser_Stmt(" box contains book ", ISLOG));

	assert(ret_false_a == QNotEquals);
	assert(ret_true_b == QEquals);
	return;
}


void testeRelation3() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("recipe is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("cake is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("soupe is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("recipe1 is a recipe  ", ISLOG)); 
	interpreter->execute_init(parse.Parser_Stmt("recipe2 is a recipe  ", ISLOG));
	 
	 
	interpreter->execute_init(parse.Parser_Stmt("recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("the verb produce  implies a  recipment relation", ISLOG));	
	interpreter->execute_init(parse.Parser_Stmt("the verb produces implies a  recipment relation", ISLOG));

	interpreter->execute_now(parse.Parser_Stmt("  recipe1 produce cake  ", ISLOG));
	interpreter->execute_now(parse.Parser_Stmt("  recipe2 produces soupe  ", ISLOG)); // nao remove a relacao anterior



	auto ret_true_a = interpreter->query(parse.Parser_Stmt(" recipe1 produces cake ", ISLOG)); 
	assert(ret_true_a == QEquals);
	 
	auto ret_true_b = interpreter->query(parse.Parser_Stmt(" product of recipe2 is soupe ", ISLOG));
	assert(ret_true_b == QEquals);


	auto ret_true_c = interpreter->query(parse.Parser_Stmt(" recipe  of cake  is  recipe1  ", ISLOG));
	assert(ret_true_c == QEquals);

	return;
}


void testeRelation4() {



	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(parse.Parser_Stmt("thing is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("recipe is a kind  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("cake is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("soupe is a thing  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("(cake recipe) is a recipe  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("recipe2 is a recipe  ", ISLOG));


	interpreter->execute_init(parse.Parser_Stmt("recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("the verb produce  implies a  recipment relation", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt("the verb produced by implies a  reverse recipment relation", ISLOG));

	interpreter->execute_now(parse.Parser_Stmt(" recipe of cake is  (cake recipe) ", ISLOG));
	interpreter->execute_now(parse.Parser_Stmt(" product of recipe2 is soupe ", ISLOG));
	
	 

	auto ret_true_a = interpreter->query(parse.Parser_Stmt(" (cake recipe) produce cake  ", ISLOG));
	assert(ret_true_a == QEquals);

	auto ret_true_b = interpreter->query(parse.Parser_Stmt(" soupe is produced by recipe2 ", ISLOG));
	assert(ret_true_b == QEquals);


	auto ret_false_c = interpreter->query(parse.Parser_Stmt(" recipe  of cake  is  recipe2  ", ISLOG));
	assert(ret_false_c == QNotEquals);

	interpreter->execute_now(parse.Parser_Stmt(" product of recipe2 is nothing ", ISLOG)); //exclui uma relacao
	auto ret_false_d = interpreter->query(parse.Parser_Stmt(" soupe is produced by recipe2 ", ISLOG));
	assert(ret_false_d == QNotEquals);


	interpreter->execute_now(parse.Parser_Stmt(" (cake recipe)  is not produce  cake  ", ISLOG)); //exclui uma relacao
	auto ret_false_e = interpreter->query(parse.Parser_Stmt(" cake is produced by (cake recipe) ", ISLOG));
	assert(ret_false_e == QNotEquals);

	return;


}


//Tem um padrao aqui 
// A kind which ( Seletor ) 
// onde  Seletor pode ser a relation or a verb seletor
// a room which ( relates to hall by Connection )
// all kind which ( Seletor )
// if X is a kind which ( Seletor )

void testeRelation5()  //relations lockup
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"(
route is a kind 
room is a kind 
thing is a kind 
route has a room called destination
garden is a room
hall is a room 
lab is a room 
exit is a route
destination of exit is garden
 
Connection relates ( a room ) to each other
the verb connect   implies a  Connection relation 
hall connect garden
garden connect hall
lab connect hall
a talent is a kind of thing
strength, courage, luck, scent, honor, spirit and freedom is talent

Inner relates many ( a thing ) to (a room )
the verb in  implies a  Inner relation 

courage is in lab
honor is in garden
freedom is in hall
scent is in hall
)";

	 interpreter->execute_init(parse.parser_text(ss1, ISLOG) );
	
	 for (auto& rr : interpreter->getRelations()) rr->dump("");
	 
	 auto pBlock = parse.Parser_Expression("a room which hall relates to by Connection ", ISLOG);
	// auto res_q1 = interpreter->query(parse.Parser_Expression("  hall connect garden  ", ISLOG));
	// auto target_q = interpreter->exec_eval(parse.Parser_Expression("a room which hall  relates to by Connection ", ISLOG), nullptr);
	// target_q->dump("");

	// auto target_q2 = interpreter->exec_eval(parse.Parser_Expression("a room which  relates to garden by Connection ", ISLOG), nullptr);
	// target_q2->dump("");

	 auto target_q3 = interpreter->exec_eval(parse.Parser_Expression("a room which  relates to hall by Connection ", ISLOG), nullptr);
	 target_q3->dump("");
	 

	 auto target_q4 = interpreter->exec_eval(parse.Parser_Expression("a room which courage relates to by Inner ", ISLOG), nullptr);
	 target_q4->dump("");

	 auto target_q5 = interpreter->exec_eval(parse.Parser_Expression("a talent which relates to hall by Inner ", ISLOG), nullptr);
	 target_q5->dump("");

	 //things which are in the teapot
	 //people who can see the mouse

	 auto target_v1 = interpreter->exec_eval(parse.Parser_Expression("talent which are in hall", ISLOG), nullptr);
	 target_v1->dump("");

	 printf("----------------\n");
	 auto target_v2 = interpreter->exec_eval(parse.Parser_Expression("room which connect hall", ISLOG), nullptr);
	 target_v2->dump("");


	 return;
}


void testeRelation6()  //relations  with actions
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"(
 
thing is a kind 
getting  is   an action applying to ( an  thing )  
apple is an thing 
orange is an thing 

the verb ( requires ) implies a dynamic relation 
 
to decide if getting requires a touchable noun : 
   decide on true

before getting ( an thing called T ) :
  if getting requires touchable noun : 
        say (text unable to take )
        stop the action

carry out getting an thing  :
   say (text taken ! )

)";
	interpreter->execute_init(parse.parser_text(ss1, true));

	//auto target_v2 = interpreter->exec_eval(parse.Parser_Expression("getting  requires  touchable noun", true), nullptr);
	//target_v2->dump("");

	interpreter->execute_now(parse.Parser_Stmt("try getting orange ", ISLOG), nullptr);

	return;
}
void testeRelation_all()
{
	//testeRelation1(); 
	//testeRelation2(); 
	//testeRelation3(); 
	//testeRelation4(); 
	//testeRelation5();
	testeRelation6();
}