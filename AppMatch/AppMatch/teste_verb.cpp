#include "BaseTest.hpp"
#include <cassert>



/*
V verb 
T time (tense T )
VP viewpoint 

"[adapt V]"
"[adapt V in T]"
"[adapt V from VP]"
"[adapt V in T from VP]"
"[negate V]"
"[negate V in T]"
"[negate V from VP]"
"[negate V in T from VP]"

*/

// "we [adapt the verb provoke in the future tense from the first person plural]"


//"[infinitive of V]"
//"[past participle of V]"
//"[present participle of V]"


//new command register verb
// serve para registrar todas as conjugacoes de um verbo


//  os Verbos validos sao :
//past tense
//present tense
//future tense
//perfect tense
//past perfect tense



void testeVerb1()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"( 
register verb to have
register verb to relate
register verb to contain
register verb to provoke
register verb to carry
register verb to will
register verb to be

a thing is an kind 
equality relates (a thing ) to another
containment relates  various (  thing  called container  ) to  ( a thing   )
the verb ( contained by ) implies a reverse  containment relation
the verb ( contains )  implies a  containment relation 
the verb ( provoke )  implies a  equality relation   

box is a thing
book is a thing

box contains a book

)";
	//definition : ( ( route called PATH ) points to ( room called R ) ) if ( ( destination of PATH ) is R )


	printf("=========================================\n");
	auto stmt = parse.parser_text(ss1, ISLOG);

	interpreter->execute_init(stmt);


	//auto ret_e = interpreter->query(parse.Parser_Stmt(" x is c  ", ISLOG));
	//	assert(ret_e == QEquals);

	//auto ret_dst = interpreter->query(parse.Parser_Stmt("destination of door is garden  ", ISLOG));
	//assert(ret_dst == QEquals);




	auto query_block = parse.Parser_Stmt("box contains book  ", ISLOG);
	auto ret_points = interpreter->query(query_block);
	assert(ret_points == QEquals);


	auto ret_cc = interpreter->query(parse.Parser_Stmt("book is  contained by box   ", ISLOG));
	assert(ret_cc == QEquals);


	auto verb_cc = interpreter->exec_eval(parse.Parser_Expression("the verb provoke", ISLOG), nullptr);
	verb_cc->dump("");

	auto verb_ccv = parse.Parser_Expression("adapt the verb provoke in past participle", ISLOG);
	verb_ccv->dump("");
	auto verb_to_adapt = interpreter->exec_eval(parse.Parser_Expression("adapt the verb provoke in past participle", ISLOG), nullptr);
	verb_to_adapt->dump("");

	auto verb_to_adapt_3 = interpreter->exec_eval(parse.Parser_Expression("adapt the verb carry in present participle  ", ISLOG), nullptr);
	verb_to_adapt_3->dump("");



	auto verb_to_adapt_4 = interpreter->exec_eval(parse.Parser_Expression("adapt the verb contain in past perfect  ", ISLOG), nullptr);
	verb_to_adapt_4->dump("");

	auto verb_to_adapt_5 = interpreter->exec_eval(parse.Parser_Expression("adapt the verb will in past perfect  ", ISLOG), nullptr);
	verb_to_adapt_5->dump("");


	auto verb_to_adapt_6 = interpreter->exec_eval(parse.Parser_Expression("adapt the verb contain  from the third person singular  ", ISLOG), nullptr);
	verb_to_adapt_6->dump("");

	auto verb_to_adapt_7 = interpreter->exec_eval(parse.Parser_Expression("adapt the verb be in past   from the second person plural  ", ISLOG), nullptr);
	verb_to_adapt_7->dump("");
	return;
}

 
void testeVerb_all()
{
	testeVerb1();
}