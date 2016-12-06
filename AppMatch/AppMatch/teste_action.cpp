#include "BaseTest.hpp"

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeParser_actionA()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse," apple is a thing  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"eat_this  is ( an action  applying to ( an thing ) )", ISLOG));
	 
	// interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : next to   [ thing  ] as X ", ISLOG));
	printf("===========================================================\n"); 
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : eat  ( a thing ) as eat_this ", ISLOG));
	// interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : bite all [  thing called X ] as  eat  X  ", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse," apple is a thing  ", ISLOG));
	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"  bite all apple ", ISLOG));

	//interpreter->execute_init(Statement::Parser_Stmt(&parse,"book is a object  ", ISLOG));
	printf("===========================================================\n");
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"eat apple   ", ISLOG));

	return;
}


void testeParser_actionB()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"box is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"puting  is ( an action  applying to ( an thing ) and ( an thing)  )", ISLOG));
	
	
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : put  [ a thing called X ] intro [ box  called IB ]  as puting ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : insert  [ a thing called X ] intro [ thing called B ] as put X intro B ", ISLOG));

	interpreter->execute_now(Statement::Parser_Stmt(&parse," insert ( apple and box )  intro  box ", true));


	 

	return;
}




void testeParser_actionC()
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing is a kind  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"thing has a text called description  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"apple is a thing  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"description of apple is (text a red and round apple )  ", ISLOG));

	interpreter->execute_init(Statement::Parser_Stmt(&parse,"say_text  is ( an action  applying to ( an text ) ) ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"say_text has a thing called speaker  ", ISLOG));
	interpreter->execute_init(Statement::Parser_Stmt(&parse,"understand : say  [ a text called X ]   as say_text  ", ISLOG)); 


	interpreter->execute_init(Statement::Parser_Stmt(&parse,"speaker of  say_text is apple ", ISLOG));

	interpreter->execute_now(Statement::Parser_Stmt(&parse," say  (text apple) ", ISLOG));
 


	return;
}


//TODO add  usually is not X  
//TODO add  rarrally  is X  
void testeParser_actionD()
{
	// Eating Rule transcipt

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string s_eating = R"(
thing is a kind
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
	//interpreter->execute_init(parse.Parser_Stmt ("eating is   an action applying to(an  thing)", ISLOG));
	
	interpreter->execute_init(ParseText::parser_text(&parse,s_eating, ISLOG));
	auto e = interpreter->exec_eval(Expression::Parser_Expression(&parse," eating ", ISLOG), nullptr,QueryStack());
	 
	e->dump("");
	//interpreter->execute_now(Expression::Parser_Expression(&parse,"eat apple ", ISLOG), nullptr); 
	// Try eh um STMT
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"try eating apple ", ISLOG), nullptr);
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"try eating orange ", ISLOG), nullptr);

	return;
}


void testeParser_actionE()
{
	// Eating Rule transcipt

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

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
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"try eating apple ", ISLOG), nullptr);
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"eat    orange ", ISLOG), nullptr);

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

void testeParser_actionF()
{
	// Eating Rule transcipt

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string s_eating = R"(
thing is a kind
thing can be edible
 
person is a kind
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
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"try eating apple ", ISLOG), nullptr);
	interpreter->execute_now(Statement::Parser_Stmt(&parse,"eat    orange ", ISLOG), nullptr);

	return;
}


void testAction_all()
{
	//testeParser_actionA(); 
	//testeParser_actionB(); 
	//testeParser_actionC();
	//testeParser_actionD();
	testeParser_actionE();
}