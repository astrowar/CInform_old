#include "BaseTest.hpp"
#include <cassert>


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
	 
    QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("[ best book ]"),
                                            std::make_shared<CBlockNoum>("diary") );

   

}


void testeParser_7b()//dynamic match
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	ErrorInfo err;
	{
		interpreter->execute_init(parse.Parser_Stmt("thing is a kind ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("book is a thing ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("diary is a thing ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("coin is a thing ", ISLOG));

		interpreter->execute_init(parse.Parser_Stmt("atom is a kind  ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("silver is a kind of atom ", ISLOG));
		interpreter->execute_init(parse.Parser_Stmt("gold is a kind of atom ", ISLOG));
	}

	auto p = parse.Parser_Stmt("to decide what (thing) is (the best book) : diary " , ISLOG );
	 
	interpreter->execute_init(p);

	QueryResul q_fa = interpreter->query_is_extern(std::make_shared<CBlockNoum>("[ best book ]"),
		std::make_shared<CBlockNoum>("diary") );




	interpreter->execute_init(parse.Parser_Stmt("he verb made of implies the materiality relation", ISLOG ));
	 
 
	interpreter->execute_init(parse.Parser_Stmt("coin is made of silver ", ISLOG ));
	QueryResul q_qq=  interpreter->query(parse.Parser_Stmt("coin is made of gold  ", ISLOG ));
 

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
		"Divisibility relates (a numbercalled N) to (a number called M) when remainder after dividing M by N is 0"
	});
	for (auto s : slist)
	{
		logMessage(s);
		auto p = parse.Parser_Stmt(s, ISLOG);

	}
	 

}