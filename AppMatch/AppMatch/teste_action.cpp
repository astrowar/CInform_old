#include "BaseTest.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeParser_action1()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
R"( 
thing is an kind of entity
apple is a thing 
orange is a thing
eat_this  is ( an action  applying to ( an thing ) )
understand : eat  ( a thing ) as eat_this

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true)); 
	f_now("try eat ( bad apple ) and orange "); 

	return;
}


void testeParser_action2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
apple is a thing 
box is a thing 
puting  is ( an action  applying to ( an thing ) and ( an thing)  )

understand : put  [ a thing called X ] intro [ box  called IB ]  as puting
understand : insert  [ a thing called X ] intro [ thing called B ] as put X intro B 

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_now("insert ( apple and box )  intro  box  ");
	f_now("try insert  apple and box  intro  box  ");
	 

	return;
}




void testeParser_action3()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string ss1 =
		R"( 
thing is an kind of entity
apple is a thing 
thing has a text called description
description of apple is (text a red and round apple ) 

say_an_text  is ( an action  applying to ( an text ) )
say_an_text has a thing called speaker 
understand : say  [ a text called X ]   as say_an_text 
speaker of  say_text is apple

box is a thing 
puting  is ( an action  applying to ( an thing ) and ( an thing)  )

understand : put  [ a thing called X ] intro [ box  called IB ]  as puting
understand : insert  [ a thing called X ] intro [ thing called B ] as put X intro B 

)";


	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	f_now("say  (text apple)   ");
	return;
}


//TODO add  usually is not X  
//TODO add  rarrally  is X  
void testeParser_action4()
{
	// Eating Rule transcript

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string s_eating = R"(
thing is a kind of entity
thing can be edible
 
person is a kind
apple is a thing
orange is a thing
bob is a person

apple is edible 
orange is not edible

eating is   an action applying to ( an  thing )  

understand : eat  ( a thing ) as eating 

before eating ( thing called X  which is not edible ) :
  say  (text i cant eat  this !)
  stop the action
  
 
  
carry out eating ( thing called X  which is edible ) :
  say  (text eaten !)

)";

	interpreter->execute_init(ParseText::parser_text(&parse, s_eating, true));

	f_eval(" eating   ")->dump("E ");

	f_now("try eating apple   ");
	f_now("try eating orange   ");
	return; 
}


void testeParser_action5()
{
	// Eating Rule transcipt

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string s_eating = R"(
thing is a kind
thing can be edible
 
person is a kind
apple is a thing
orange is a thing
 

apple is edible 
orange is not edible

eating is   an action applying to ( an  thing )  

understand : eat  ( a thing ) as eating 

before eating ( thing called X   ) :  
  if X is edible  :
     say ( text  i will eat )
     continue the action
  say ( text  what ? )
      
  
carry out eating ( thing called X  which is edible ) :
  say  (text eaten !)

)";

	interpreter->execute_init(ParseText::parser_text(&parse,s_eating, ISLOG));

 
	//interpreter->execute_now(Expression::Parser_Expression(&parse,"eat apple ", ISLOG), nullptr); 
	// Try eh um STMT
	f_now("try eating apple " );
	f_now("eat    orange " );

	return;
}


 
//este teste indruduz o conceito de Protocols ( kind of action )
// de tal forma que uma acao X pode ser um protocolo . protocolos nao tem assinatura de acao
// mas uma acao especifica tem uma assinatura
// se uma dada acao se encaivar na deficiao da acao que define um protocolo ... trate a acao como uma invocao daquele protocolo
// os protocolos sao invocados DEPOIS das acoes especificas.
// Ex   shot someone is a a hurting
//      se o player executar o shot em algo, nao so procesa os events handles de shot
//      se o player atirar em alguem, processa os handle de shot e depois os de hurt, intercalados
//      ie  check shot, check hurt, before shot, before hurt,  carry on shot, carry on hurt ....

void testeParser_action6()
{
	// Eating Rule transcipt

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };

	string s_eating = R"(
thing is a kind of entity
thing can be edible
 
person is a kind of entity
apple is a thing
orange is a thing

speech is an kind of action  
 
asking someone about something is speech
telling someone about something is speech
answering someone that something is speech
asking someone for something is speech 


)";

	interpreter->execute_init(ParseText::parser_text(&parse,s_eating, ISLOG));

	//interpreter->execute_now(Expression::Parser_Expression(&parse,"eat apple ", ISLOG), nullptr); 
	// Try eh um STMT
 

	f_now("try eating apple ");
	f_now("eat    orange ");


	return;
}


//analysing something is an activity
//the analysing activity has a text called first impression




void testAction_all()
{
	testeParser_action1();
	return;
	testeParser_action1(); 
	testeParser_action2(); 
	testeParser_action3();
	testeParser_action4();
	testeParser_action5();
	testeParser_action6();
}