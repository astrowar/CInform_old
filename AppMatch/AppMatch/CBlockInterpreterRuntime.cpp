// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CBlockInterpreterRuntime.hpp"
#include "EqualsResult.hpp"

using namespace CBlocking;
using namespace Interpreter;
 


 QueryResultContext::QueryResultContext(QueryResul r) : result(r)
{
}

QueryResultContext::QueryResultContext(QueryResul r, std::map<string, HBlock> _matchedResult) : result(r)
{	 
	matchedResult = _matchedResult;
}

 

QueryResultContext::QueryResultContext(QueryResul r, std::map<string, CBlocking::HBlock> _matchedResult_A, std::map<string, CBlocking::HBlock> _matchedResult_B) : result(r)
{
	for (auto q = _matchedResult_A.rbegin(); q != _matchedResult_A.rend(); ++q)
	{
		matchedResult[q->first] = q->second;
	}
	for (auto q = _matchedResult_B.rbegin(); q != _matchedResult_B.rend(); ++q)
	{
		matchedResult[q->first] = q->second;
	}
}


void Interpreter::QueryResultContext::dump()
{
	for (auto q = matchedResult.begin(); q != matchedResult.end(); ++q)
	{
		printf("--------------------------------\n");
		logMessage(q->first);
		(*q).second->dump("");		
	}
}