//
// Created by eraldo.rangel on 12/09/2016.
//
#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;
  


void testeRelation1() {
	Interpreter::HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse;

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"direction is a kind  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"room is a kind  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"garden is a room  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"hall is a room  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"key is a thing  ", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"box is a thing  ", ISLOG));

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
       // auto p = Statement::Parser_Stmt(&parse,s, ISLOG);
       // interpreter->execute_init(p );
    }

    

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"unloking relates (a thing ) to various thing", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  unlock  implies a  unloking relation", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb ( unlocked by ) implies a reverse  unloking relation", ISLOG)); 
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"   box is unlocked by   key  ", ISLOG));
	//interpreter->execute_now(Statement::Parser_Stmt(&parse, "  garden is unlocked by  key  ", ISLOG));
   // interpreter->execute_now (Statement::Parser_Stmt(&parse,"   key unlocked  by box  ", ISLOG)); 
     
    //interpreter->execute_init(Statement::Parser_Stmt(&parse,"to decide if ( thing called T ) unloked by ( thing called K ) :  K unlocks T   ", ISLOG));
	 

    auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse," key unlock box ", ISLOG));
    auto ret_false_b = interpreter->query(Statement::Parser_Stmt(&parse," box unlock key ", ISLOG));
    auto ret_false_c = interpreter->query(Statement::Parser_Stmt(&parse," key unlock garden ", ISLOG));
    auto ret_true_d = interpreter->query(Statement::Parser_Stmt(&parse," box is unlocked by key ", ISLOG)); 

	assert(ret_true_a.result == QEquals);
	assert(ret_false_b.result == QNotEquals);
	assert(ret_false_c.result == QNotEquals);
	assert(ret_true_d.result == QEquals);

	printf("_______________________________________\n");
	auto target_q3 = interpreter->exec_eval(Expression::Parser_Expression(&parse, " unloking relates a thing  to an thing   ", true), nullptr, nullptr);
	target_q3->dump("A ");
	 

    return;
}

void testeRelation2() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"box is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"key is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"book   is a thing  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"containner relates (a thing ) to another", ISLOG));	
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb  contains  implies a  containner relation", ISLOG));

	interpreter->execute_now(Statement::Parser_Stmt(&parse,"  box contains key  ", ISLOG));
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"  box contains book  ", ISLOG)); //remove a relacao anterior



	auto ret_false_a = interpreter->query(Statement::Parser_Stmt(&parse," box contains key ", ISLOG));
	auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse," box contains book ", ISLOG));

	assert(ret_false_a.result == QNotEquals);
	assert(ret_true_b.result == QEquals);
	return;
}


void testeRelation3() {

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipe is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"cake is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"soupe is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipe1 is a recipe  ", ISLOG)); 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipe2 is a recipe  ", ISLOG));
	 
	 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb produce  implies a  recipment relation", ISLOG));	
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb produces implies a  recipment relation", ISLOG));

	interpreter->execute_now(Statement::Parser_Stmt(&parse,"  recipe1 produce cake  ", ISLOG));
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"  recipe2 produces soupe  ", ISLOG)); // nao remove a relacao anterior



	auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse," recipe1 produces cake ", ISLOG)); 
	assert(ret_true_a.result == QEquals);
	 
	auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse," product of recipe2 is soupe ", ISLOG));
	assert(ret_true_b.result == QEquals);


	auto ret_true_c = interpreter->query(Statement::Parser_Stmt(&parse," recipe  of cake  is  recipe1  ", ISLOG));
	assert(ret_true_c.result == QEquals);

	return;
}


void testeRelation4() {



	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipe is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"cake is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"soupe is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"(cake recipe) is a recipe  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipe2 is a recipe  ", ISLOG));


	interpreter->execute_init(Statement::Parser_Stmt(&parse,"recipment relates ( recipe called recipe ) to ( thing called the product )  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb produce  implies a  recipment relation", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb produced by implies a  reverse recipment relation", ISLOG));

	interpreter->execute_now(Statement::Parser_Stmt(&parse," recipe of cake is  (cake recipe) ", ISLOG));
	interpreter->execute_now(Statement::Parser_Stmt(&parse," product of recipe2 is soupe ", ISLOG));
	
	 

	auto ret_true_a = interpreter->query(Statement::Parser_Stmt(&parse," (cake recipe) produce cake  ", ISLOG));
	assert(ret_true_a.result == QEquals);

	auto ret_true_b = interpreter->query(Statement::Parser_Stmt(&parse," soupe is produced by recipe2 ", ISLOG));
	assert(ret_true_b.result == QEquals);


	auto ret_false_c = interpreter->query(Statement::Parser_Stmt(&parse," recipe  of cake  is  recipe2  ", ISLOG));
	assert(ret_false_c.result == QNotEquals);

	interpreter->execute_now(Statement::Parser_Stmt(&parse," product of recipe2 is nothing ", ISLOG)); //exclui uma relacao
	auto ret_false_d = interpreter->query(Statement::Parser_Stmt(&parse," soupe is produced by recipe2 ", ISLOG));
	assert(ret_false_d.result == QNotEquals);


	interpreter->execute_now(Statement::Parser_Stmt(&parse," (cake recipe)  is not produce  cake  ", ISLOG)); //exclui uma relacao
	auto ret_false_e = interpreter->query(Statement::Parser_Stmt(&parse," cake is produced by (cake recipe) ", ISLOG));
	assert(ret_false_e.result == QNotEquals);

	return;


}


//Tem um padrao aqui 
// A kind ] ( Seletor ) 
// onde  Seletor pode ser a relation or a verb seletor
// a room which ( relates to hall by Connection )
// all kind which ( Seletor )
// if X is a kind which ( Seletor )

void testeRelation5()  //relations lockup
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
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

	 interpreter->execute_init(ParseText::parser_text(&parse,ss1, ISLOG) );
	
	 for (auto& rr : interpreter->getRelations()) rr->dump("");
	 
	 auto pBlock = Expression::Parser_Expression(&parse,"a room which hall relates to by Connection ", ISLOG);
	// auto res_q1 = interpreter->query(Expression::Parser_Expression(&parse,"  hall connect garden  ", ISLOG));
	// auto target_q = interpreter->exec_eval(Expression::Parser_Expression(&parse,"a room which hall  relates to by Connection ", ISLOG), nullptr);
	// target_q->dump("");

	// auto target_q2 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"a room which  relates to garden by Connection ", ISLOG), nullptr);
	// target_q2->dump("");

	 auto target_q3 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"a room which  relates to hall by Connection ", ISLOG), nullptr,nullptr);
	 target_q3->dump("");
	 

	 auto target_q4 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"a room which courage relates to by Inner ", ISLOG), nullptr,nullptr);
	 target_q4->dump("");

	 auto target_q5 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"a talent which relates to hall by Inner ", ISLOG), nullptr,nullptr);
	 target_q5->dump("");

	 //things which are in the teapot
	 //people who can see the mouse

	 auto target_v1 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"talent which are in hall", ISLOG), nullptr,nullptr);
	 target_v1->dump("");

	 printf("----------------\n");
	 auto target_v2 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"room which connect hall", ISLOG), nullptr,nullptr);
	 target_v2->dump("");


	 return;
}


void testeRelation6()  //relations  with actions
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
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
	interpreter->execute_init(ParseText::parser_text(&parse,ss1, ISLOG));

	//auto target_v2 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"getting  requires  touchable noun", true), nullptr);
	//target_v2->dump("");

	interpreter->execute_now(Statement::Parser_Stmt(&parse,"try getting orange ", ISLOG), nullptr);

	return;
}

 
void testeRelation7()  //relations  with actions
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	string ss1 =
		R"(
     thing is a kind 
     apple is an thing 
     orange is an thing
     pear is an thing

     getting  is   an action applying to ( an  thing ) 

     carry out getting an thing  :
       let the map  be a relation of thing
       now map relates orange to apple       
       say (text taken )
      

)";
	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));

	printf("init try ----------\n");
	auto ex = Statement::Parser_Stmt(&parse, "try getting orange", true);
	printf("end try parse--------------\n");
	
	auto target_v2 = interpreter->execute_now(ex);
	 
	printf("----------------\n");
	//interpreter->execute_now(Statement::Parser_Stmt(&parse, "try getting orange ", ISLOG), nullptr);

	return;
}


void testeParser_7_1()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind
unloking relates (a thing ) to various thing
the verb  unlock  implies a  unloking relation
the verb ( unlocked by ) implies a reverse  unloking relation 
key is a thing
box is a thing
apple is a thing
)";
 

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_eval(" unloking  ")->dump("R ");
	f_now(" key unlock box ");

	assert(f_is("key unlock box "));
	assert(f_is("apple unlock box ") == false);
	assert(f_is("box is unlocked by key "));
	assert(f_is("apple not unlock box ") ); 
}

void testeParser_7_2()
{
	//Relations as First class objects

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind
unloking relates (a thing ) to various thing
the verb  unlock  implies a  unloking relation
the verb ( unlocked by ) implies a reverse  unloking relation 
key is a thing
box is a thing
apple is a thing
key unlock box 
)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	//f_eval("  unloking relates a thing  to an thing   ")->dump("R ");
	// f_now(" key unlock box ");
	//assert(f_eval("unloking relates key  to  box  "));
	// assert(f_is("unloking relates a thing  to an thing  ")); // undefined behavior
	
	auto p = Expression::Parser_Expression(&parse, "unloking relates(a thing called N)  to (an thing called M)", false);
	p->dump("");
	//assert(f_eval("unloking relates (a thing called N)  to (an thing called M)  ")); // undefined behavior
 
}


void testeRelation_all()
{
	//testeParser_7_1();  //comportamento fundamental
	testeParser_7_2();

	 //testeRelation1(); 
	//testeRelation2(); 
	//testeRelation3(); 
	//testeRelation4(); 
	//testeRelation5();
	//testeRelation6();
	//testeRelation7();
}