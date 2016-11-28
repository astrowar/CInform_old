#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeParser_7a()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);
 
    {
        interpreter->execute_init(parse.Parser_Stmt("thing is a kind ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("book is a thing ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("diary is a thing ", ISLOG));
    }

    auto p = parse.Parser_Stmt("to decide what (thing) is (the best book) : diary ", ISLOG);
 
    interpreter->execute_init(p);
     
	QueryResultContext q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("[ best book ]"),
                                            std::make_shared<CBlockNoum>("diary") );

   

}


void testeParser_7b()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);
     
    {
        interpreter->execute_init(parse.Parser_Stmt("thing is a kind ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("book is a thing ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("diary is a thing ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("coin is a thing ", ISLOG));

        interpreter->execute_init(parse.Parser_Stmt("atom is a kind  ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("silver is a kind of atom ", ISLOG));
        interpreter->execute_init(parse.Parser_Stmt("gold is a kind of atom ", ISLOG));
    }

    auto p = parse.Parser_Stmt("to decide what (thing) is (  best book) : diary " , ISLOG );
     
    interpreter->execute_init(p);

    QueryResultContext q_fa = interpreter->query(parse.Parser_Stmt("best book is diary   ", ISLOG));
        

    assert(q_fa.result == QEquals);

    interpreter->execute_init(parse.Parser_Stmt("materiality relates (a thing ) to (an atom )", ISLOG));
    interpreter->execute_init(parse.Parser_Stmt("the verb made of implies the materiality relation", ISLOG ));
     
 
    interpreter->execute_init(parse.Parser_Stmt("coin is made of silver ", ISLOG ));
	QueryResultContext q_false=  interpreter->query(parse.Parser_Stmt("coin is made of gold  ", ISLOG ));
    assert(q_false.result != QEquals);
	QueryResultContext q_true = interpreter->query(parse.Parser_Stmt("coin is made of silver  ", ISLOG));
    assert(q_true.result == QEquals);

    interpreter->execute_now(parse.Parser_Stmt("coin is made of gold ", ISLOG));
	QueryResultContext q_false_2 = interpreter->query(parse.Parser_Stmt("coin is made of silver  ", ISLOG));
    assert(q_false_2.result != QEquals);
    
}


void testeParser_7c()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        auto p = parse.Parser_Stmt("Fanciness relates  ( a thing called X) to (some money called Y)", ISLOG );
    }
    {
        auto p = parse.Parser_Stmt("Fanciness relates  ( a thing called X) to another", ISLOG);
    }
    {
        auto p = parse.Parser_Stmt("Pet-ownership relates various animals to ( a person called the owner)", ISLOG);
    }
    {
        auto p = parse.Parser_Stmt("Fanciness relates  ( a thing called X) to each other in groups", ISLOG);
    }


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
        logMessage( s);
        auto p = parse.Parser_Stmt(s, ISLOG);
    }

     
}

void testeParser_7d()// relation When
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    std::list< std::string >  slist({
    "Contact relates (a thing called X) to (a thing called Y) when X is part of Y or Y is part of X",
        "Nearness relates (a room called A) to (a room called B) when the number of moves from B to A is less than 3",
        "Materiality relates (a thing called X) to (a material called Y) when Y is the material of X",
        "Divisibility relates (a number called N) to (a number called M) when remainder after dividing M by N is 0"
    });
    for (auto s : slist)
    {
        logMessage(s);
         auto p = parse.Parser_Stmt(s, ISLOG);

    }
      

    string slong = R"(
person is an kind
woman is a kind of person
Zora is an woman
language is a kind of value
language are English, Zubian and Perplexish 
speaking relates ( a person ) to   various  (  language )
the verb  speak  implies the speaking relation
Zora speak English
Zora speak Zubian
)";

    

      interpreter->execute_init(parse.parser_text ( slong, ISLOG));
      
      //auto q1 = interpreter->query(parse.Parser_Stmt(" Zora is a  person  ", ISLOG));
     // assert(q1 == QEquals);
      //auto q2 = interpreter->query(parse.Parser_Stmt(" English is a  language  ", ISLOG)); 
      //assert(q2 == QEquals);
	  QueryResultContext q3 =  interpreter->query(parse.Parser_Stmt("Zora speak English  ", ISLOG));
      assert(q3.result == QEquals);

	  auto q4 = interpreter->execute_now(parse.parser_text("if   Zora speak English   : say  (text yes) ", ISLOG));
      assert(q4.hasExecuted );
}


void testeParser_7e()
{
	string slong = R"(
person is an kind
woman is an kind of person
Zora is an woman
Mary is an woman

language is a kind of value
language are English, Zubian and Perplexish 
speaking relates ( a person ) to   various  (  language )
the verb  speak  implies the speaking relation


Mary speak Zubian

to decide  what ( person   ) is (the best person) :
   if Zora speak Zubian :
      decide on Zora
   else:
      decide on Mary   

to decide  if ( person called P  ) is ( suitable ) :
   if P speak Zubian :
      decide on true
   if P speak English :
      decide on false
   decide on nothing

to decide  if ( person called P  ) is oposite of ( person called Q )  :
   if P is Zora  :
      if Q is Mary  :
         decide on true 
   if P is Mary  :
      if Q is Zora  :
         decide on true 
   decide on false


)";

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(parse.parser_text(slong, ISLOG));

	//auto qr = interpreter->exec_eval(std::make_shared<CBlockNoum>("best person")  ,nullptr);
	//qr->dump("");

	//auto q3 = interpreter->query(parse.Parser_Stmt("best person is Mary  ", ISLOG));
	//assert(q3 == QEquals);

	QueryResultContext q4 = interpreter->query(parse.Parser_Stmt(" Mary is suitable ", ISLOG));
	assert(q4.result == QEquals);

	QueryResultContext q5 = interpreter->query(parse.Parser_Stmt(" Zora is suitable ", ISLOG));
	assert(q5.result != QEquals);

	QueryResultContext q6 = interpreter->query(parse.Parser_Stmt(" Zora is oposite of Mary ", ISLOG));
	assert(q6.result == QEquals);



	return;

}

 