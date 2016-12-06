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
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a thing ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is a thing ", ISLOG));
    }

    auto p = Statement::Parser_Stmt(&parse,"to decide what (thing) is (the best book) : diary ", ISLOG);
 
    interpreter->execute_init(p);
     
	QueryResultContext q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("[ best book ]"),
                                            std::make_shared<CBlockNoum>("diary") );

   

}


void testeParser_7b()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);
     
    {
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a thing ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"diary is a thing ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"coin is a thing ", ISLOG));

        interpreter->execute_init(Statement::Parser_Stmt(&parse,"atom is a kind  ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"silver is a kind of atom ", ISLOG));
        interpreter->execute_init(Statement::Parser_Stmt(&parse,"gold is a kind of atom ", ISLOG));
    }

    auto p = Statement::Parser_Stmt(&parse,"to decide what (thing) is (  best book) : diary " , ISLOG );
     
    interpreter->execute_init(p);

    QueryResultContext q_fa = interpreter->query(Statement::Parser_Stmt(&parse,"best book is diary   ", ISLOG));
        

    assert(q_fa.result == QEquals);

    interpreter->execute_init(Statement::Parser_Stmt(&parse,"materiality relates (a thing ) to (an atom )", ISLOG));
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"the verb made of implies the materiality relation", ISLOG ));
     
 
    interpreter->execute_init(Statement::Parser_Stmt(&parse,"coin is made of silver ", ISLOG ));
	QueryResultContext q_false=  interpreter->query(Statement::Parser_Stmt(&parse,"coin is made of gold  ", ISLOG ));
    assert(q_false.result != QEquals);
	QueryResultContext q_true = interpreter->query(Statement::Parser_Stmt(&parse,"coin is made of silver  ", ISLOG));
    assert(q_true.result == QEquals);

    interpreter->execute_now(Statement::Parser_Stmt(&parse,"coin is made of gold ", ISLOG));
	QueryResultContext q_false_2 = interpreter->query(Statement::Parser_Stmt(&parse,"coin is made of silver  ", ISLOG));
    assert(q_false_2.result != QEquals);
    
}


void testeParser_7c()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        auto p = Statement::Parser_Stmt(&parse,"Fanciness relates  ( a thing called X) to (some money called Y)", ISLOG );
    }
    {
        auto p = Statement::Parser_Stmt(&parse,"Fanciness relates  ( a thing called X) to another", ISLOG);
    }
    {
        auto p = Statement::Parser_Stmt(&parse,"Pet-ownership relates various animals to ( a person called the owner)", ISLOG);
    }
    {
        auto p = Statement::Parser_Stmt(&parse,"Fanciness relates  ( a thing called X) to each other in groups", ISLOG);
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
        auto p = Statement::Parser_Stmt(&parse,s, ISLOG);
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
         auto p = Statement::Parser_Stmt(&parse,s, ISLOG);

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

    

      interpreter->execute_init(ParseText::parser_text(&parse, slong, ISLOG));
      
      //auto q1 = interpreter->query(Statement::Parser_Stmt(&parse," Zora is a  person  ", ISLOG));
     // assert(q1 == QEquals);
      //auto q2 = interpreter->query(Statement::Parser_Stmt(&parse," English is a  language  ", ISLOG)); 
      //assert(q2 == QEquals);
	  QueryResultContext q3 =  interpreter->query(Statement::Parser_Stmt(&parse,"Zora speak English  ", ISLOG));
      assert(q3.result == QEquals);

	  auto q4 = interpreter->execute_now(ParseText::parser_text(&parse,"if   Zora speak English   : say  (text yes) ", ISLOG));
      assert(q4.hasExecuted );
}


void testeParser_7e()
{
	string slong = R"(
person is an kind
woman is an kind of person
man is an kind of person
Zora is an woman
Mary is an woman
Bob is a  man
Julian  is a man

language is a kind of value
language are English, Zubian and Perplexish 
speaking relates various ( a person ) to  ( a  language )
the verb  speak  implies the speaking relation


Mary speak Zubian
Bob speak Zubian
Zora speak Perplexish
Julian speak English
 

 


to decide  if ( person called P  ) is ( suitable  for  ( person called Q  ) ) :
   if ( P speak  Zubian ) and ( Q speak Zubian ) :
      decide on true   
   if( P speak  Perplexish) and ( Q speak Perplexish ):
      decide on true       
   decide on false
   

 


)";

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	interpreter->execute_init(ParseText::parser_text(&parse,slong, true));


	  interpreter->exec_eval(Expression::Parser_Expression(&parse, "  Mary is   suitable for Bob  ", true), nullptr, QueryStack())->dump("");
	  interpreter->exec_eval(Expression::Parser_Expression(&parse, "  Bob is suitable for Zora ", true), nullptr, QueryStack())->dump("");

	//auto qList = interpreter->exec_eval(Expression::Parser_Expression(&parse, " ( Person called P ) which  is suitable for Bob ", true), nullptr, QueryStack());
	//qList->dump("");
	//return;

	//auto qr = interpreter->exec_eval(std::make_shared<CBlockNoum>("best person")  ,nullptr);
	//qr->dump("");

	//auto q3 = interpreter->query(Statement::Parser_Stmt(&parse,"best person is Mary  ", ISLOG));
	//assert(q3 == QEquals);

	QueryResultContext q4 = interpreter->query(Statement::Parser_Stmt(&parse," Mary is suitable ", ISLOG));
	assert(q4.result == QEquals);

	QueryResultContext q5 = interpreter->query(Statement::Parser_Stmt(&parse," Zora is suitable ", ISLOG));
	assert(q5.result != QEquals);

	QueryResultContext q6 = interpreter->query(Statement::Parser_Stmt(&parse," Zora is oposite of Mary ", ISLOG));
	assert(q6.result == QEquals);

	 

	assert(q6.result == QEquals);
	return;

}

 