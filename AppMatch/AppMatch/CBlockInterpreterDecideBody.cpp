
#include "CBlockMatch.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "CResultMatch.hpp"
#include <iostream>
#include "QueryStack.hpp"
#include "sharedCast.hpp"

#undef PROPAGATE_LETS

HRunLocalScope newScope(HRunLocalScope oldEntry ,HRunLocalScope headerEntry )
{
	HRunLocalScope localsNext = nullptr;
#ifdef PROPAGATE_LETS
	{
		if (oldEntry != nullptr)
		{
			  localsNext = localsEntry->Union(oldEntry);
		}
		else
		{
			  localsNext = headerEntry;
		}
#else

	  localsNext = headerEntry;
#endif

	return localsNext;
}


HBlock CBlockInterpreter::getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecideWhether dct) {

	return nullptr;

}

HBlock CBlockInterpreter::getDecidedValueOf(HBlock c_block, HBlockToDecideWhat dct , HRunLocalScope localsEntry, QueryStack stk) {
	HBlockMatch match =   (dct->queryToMatch);

	CResultMatch result = this->Match(match, c_block, localsEntry, stk);
	if (result.hasMatch ) 
	{
 
		auto localsHeader = std::make_shared< CRunLocalScope >(result.maptch);

		HRunLocalScope localsNext = newScope( localsHeader , localsHeader );


		//Execute body
		return dct->decideBody;
	}

	return nullptr;
}


QueryResul CBlockInterpreter::getDecidedIf(HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack stk)
{
	if(localsEntry != nullptr) localsEntry->dump("   ");
	CResultMatch result = this->Match(dct->queryToMatch, c_block, localsEntry,stk);
	if (result.hasMatch)
	{
		auto localsHeader = std::make_shared< CRunLocalScope >(result.maptch);
		HRunLocalScope localsNext = newScope( localsHeader , localsHeader );

		auto rr =  query(dct->decideBody, localsNext, stk);
		if (rr == QEquals) return  QEquals;
		return QNotEquals;

	}

	return QUndefined;
}