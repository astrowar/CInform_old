#include "BaseTest.hpp"
#include <cassert>
#include "CDataMananger.hpp"
#include <fstream>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testeSerialize1() {


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);



	auto p = (Statement::Parser_Stmt(&parse,"puting  is ( an action  applying to ( an thing ) and ( an thing)  )", ISLOG));
	
	//data_d_mananger.store( std::make_shared<CBlockNoum>("teste") );

	auto h = std::make_shared<CBlockNoum>("teste");

	 
	 
	
	return;

 

	 

}
