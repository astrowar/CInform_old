#include "BaseTest.h"
#include <cassert>


void testeParser_7a()//dynamic match
{
    HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
    CParser parse(interpreter);

    {
        interpreter->execute_init(parse.parser_stmt("thing is a kind "));
        interpreter->execute_init(parse.parser_stmt("book is a thing "));
        interpreter->execute_init(parse.parser_stmt("diary is a thing "));
    }

	auto p = parse.parser_stmt("to decide what (thing) is (the best book) : diary ");
	if (ISLOG) {p->dump("");std::cout << std::endl;	}
	interpreter->execute_init(p);
	 
    QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockNoum>("[ best book ]"),
                                            std::make_shared<CBlockNoum>("diary"));

    std::cout << std::endl;

}


void testeParser_7b()//dynamic match
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	{
		interpreter->execute_init(parse.parser_stmt("thing is a kind "));
		interpreter->execute_init(parse.parser_stmt("book is a thing "));
		interpreter->execute_init(parse.parser_stmt("diary is a thing "));
		interpreter->execute_init(parse.parser_stmt("coin is a thing "));
	}

	auto p = parse.parser_stmt("to decide what (thing) is (the best book) : diary " , ISLOG);
	 
	interpreter->execute_init(p);

	QueryResul q_fa = interpreter->query_is(std::make_shared<CBlockNoum>("[ best book ]"),
		std::make_shared<CBlockNoum>("diary"));




	interpreter->execute_init(parse.parser_stmt("the verb made of implies the materiality relation ", ISLOG));
	interpreter->execute_init(parse.parser_stmt("thing is made of atoms ", ISLOG));
	QueryResul q_qq=  interpreter->query(parse.parser_stmt("coin is made of atoms  ", ISLOG));
	std::cout << std::endl;

}