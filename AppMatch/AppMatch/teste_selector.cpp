#include "BaseTest.hpp"
#include <cassert>

void testeSelector_1()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string slong = R"(
room is an kind
thing is an kind
stucking relates (a thing ) to another
inner relates (a thing ) to (a room)
garden is a room 
hall is a room
the verb ( stuck to ) implies the stucking relation
the verb ( in ) implies the inner relation
coil is a thing
box is a thing
coil is stuck to box 
box is in hall
)";

	
	interpreter->execute_init(parse.parser_text(slong, ISLOG));

	auto sentence_0 = "the coil is stuck to box ";
	auto sentence_1 = "the coil is stuck to a thing ";
    auto sentence_2 = "the coil is stuck to a thing which is in  (a room called the next room )";
	auto sentence_3 = "the coil is stuck to ( (a thing called owner ) which is not in garden )";
	auto sentence_4 = "the coil is stuck to (a thing which is in  ( ( a room called the next room ) which is not the garden ) )";

	printf("---------------------------------------------\n");
	auto ret_true_a = interpreter->query(parse.Parser_Condition(sentence_0, ISLOG));
	assert(ret_true_a.result == QEquals);
	
	auto ret_true_b = interpreter->query(parse.Parser_Condition(sentence_1, ISLOG));
	assert(ret_true_b.result == QEquals);

	
	auto ret_true_c = interpreter->query(parse.Parser_Condition(sentence_2, ISLOG));
	assert(ret_true_c.result == QEquals);

	auto ret_true_d = interpreter->query(parse.Parser_Condition(sentence_3, ISLOG));
	assert(ret_true_d.result == QEquals);

	auto ret_true_e = interpreter->query(parse.Parser_Condition(sentence_4, ISLOG));
	assert(ret_true_e.result == QEquals);



	return;
}

void testeSelector_all()
{
	
	testeSelector_1();
}