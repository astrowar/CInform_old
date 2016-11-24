#include "CBlockInterpreterRuntime.hpp"

QueryResultContext::QueryResultContext(QueryResul r) : result(r)
{
}

QueryResultContext::QueryResultContext(QueryResul r, std::map<string, HBlock> _matchedResult) : result(r)
{
	 
	matchedResult = _matchedResult;
}
