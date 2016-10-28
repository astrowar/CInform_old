
#include "CBlockMatch.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "CResultMatch.hpp"
 
#include "QueryStack.hpp"
#include "sharedCast.hpp"

#undef PROPAGATE_LETS

HRunLocalScope newScope(HRunLocalScope oldEntry ,HRunLocalScope headerEntry )
{
	HRunLocalScope localsNext = nullptr;

	//printf("fuse contexts .....\n");
	//if (oldEntry != nullptr) oldEntry->dump(" ");
	//printf("with .....\n");
	//if (headerEntry != nullptr) headerEntry->dump(" ");
	//printf("end .....\n");
	{
		auto localsHeaderOut = std::make_shared< CRunLocalScope >();
		for (auto e : headerEntry->locals)
		{
			if (oldEntry != nullptr)
			{
				auto resolved = oldEntry->resolve(e.first);
				if (resolved != nullptr)
				{
					localsHeaderOut->locals.emplace_back(e.first, resolved);
				}
				else
				{
					localsHeaderOut->locals.emplace_back(e.first, e.second);
				}
			}
			else
			{
				localsHeaderOut->locals.emplace_back(e.first, e.second);
			}
		}
		if (oldEntry != nullptr) //tem no old ma nao no new
		{
			for (auto e : oldEntry->locals)
			{
				localsHeaderOut->locals.emplace_back(e.first, e.second);
			}


		}

		return localsHeaderOut;
	}

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

	if (stk.isQuery("is", c_block, dct)) return nullptr;
	stk.addQuery("is", c_block, dct);

	if (stk.size() > 30 )
	{
		stk.dump();
		printf("huge");
	}

 
	CResultMatch result = this->Match(match, c_block, localsEntry, stk);
	 
	if (result.hasMatch ) 
	{
 
		auto localsHeader = std::make_shared< CRunLocalScope >(result.maptch);

		HRunLocalScope localsNext = newScope( localsHeader , localsHeader );


		//Execute body
		 
		if ( HBlockNoum anoum  = asHBlockNoum( dct->decideBody ))
		{
		 
			auto qresolved =   resolve_noum(anoum, localsNext);
			if (qresolved != nullptr)  return qresolved;
		}
		return dct->decideBody;
	}

	return nullptr;
}


QueryResul CBlockInterpreter::getDecidedIf(HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack stk)
{
	//stack overflow 
	if (stk.isQuery("decide", c_block, dct))
	{
		return QUndefined;
	}
	stk.addQuery("decide", c_block, dct);
	
	//if(localsEntry != nullptr) localsEntry->dump("   ");



	CResultMatch result = this->Match(dct->queryToMatch, c_block, localsEntry,stk);

		
	/*printf("MATCH ? ===========================\n");
	dct->queryToMatch->dump(" ");
	printf(" ->  \n");
	c_block->dump(" ");
	printf(".....................................\n");*/
	if (result.hasMatch)
	{
		auto localsHeaderC = std::make_shared< CRunLocalScope >(result.maptch);
		HRunLocalScope localsNext = newScope(localsEntry, localsHeaderC);
		 
		auto rr =  query(dct->decideBody, localsNext, stk);
		if (rr == QEquals) return QEquals;
 

		return QNotEquals; // deve decidir 
		 

	}

	return QUndefined;
}