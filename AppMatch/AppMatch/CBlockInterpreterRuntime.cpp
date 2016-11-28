#include "CBlockInterpreterRuntime.hpp"


using namespace CBlocking;
using namespace Interpreter;
 


 QueryResultContext::QueryResultContext(QueryResul r) : result(r)
{
}

QueryResultContext::QueryResultContext(QueryResul r, std::map<string, HBlock> _matchedResult) : result(r)
{
	 
	matchedResult = _matchedResult;
}
