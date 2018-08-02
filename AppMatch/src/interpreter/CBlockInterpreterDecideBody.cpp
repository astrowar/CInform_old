// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "CBlockMatch.hpp"

#include "CResultMatch.hpp"
 
#include "interpreter/QueryStack.hpp"
#include "sharedCast.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
#undef PROPAGATE_LETS


using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;


//
//HRunLocalScope newScope(HRunLocalScope oldEntry ,HRunLocalScope headerEntry )
//{
//	HRunLocalScope localsNext = nullptr;
//
//	//printf("fuse contexts .....\n");
//	//if (oldEntry != nullptr) oldEntry->dump(" ");
//	//printf("with .....\n");
//	//if (headerEntry != nullptr) headerEntry->dump(" ");
//	//printf("end .....\n");
//	{
//		auto localsHeaderOut = std::make_shared< CRunLocalScope >();
//		for (auto e : headerEntry->locals)
//		{
//			if (oldEntry != nullptr)
//			{
//				auto resolved = oldEntry->resolve(e.first);
//				if (resolved != nullptr)
//				{
//					localsHeaderOut->locals.emplace_back(e.first, resolved);
//				}
//				else
//				{
//					localsHeaderOut->locals.emplace_back(e.first, e.second);
//				}
//			}
//			else
//			{
//				localsHeaderOut->locals.emplace_back(e.first, e.second);
//			}
//		}
//		if (oldEntry != nullptr) //tem no old ma nao no new
//		{
//			for (auto e : oldEntry->locals)
//			{
//				localsHeaderOut->locals.emplace_back(e.first, e.second);
//			}
//
//
//		}
//
//		return localsHeaderOut;
//	}
//
//#ifdef PROPAGATE_LETS
//	{
//		if (oldEntry != nullptr)
//		{
//			  localsNext = localsEntry->Union(oldEntry);
//		}
//		else
//		{
//			  localsNext = headerEntry;
//		}
//#else
//
//	  localsNext = headerEntry;
//#endif
//
//	return localsNext;
//}


CBlocking::HBlock CBlockInterpreter::getDecidedWhether(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, CBlocking::HBlockToDecideWhether dct) {

	return nullptr;

}

CBlocking::HBlock CBlockInterpreter::getDecidedValueOf(CBlocking::HBlock c_block, CBlocking::HBlockToDecideWhat dct , HRunLocalScope localsEntry, QueryStack *stk_in) {
	
	
	HBlockMatch match =   (dct->queryToMatch);

	std::unique_ptr<QueryStack> stk_unique = nullptr;
	if (stk_in != nullptr)
	{
		if (stk_in->isQuery("is", c_block, dct)) return nullptr;
		stk_unique = std::make_unique<QueryStack>(*stk_in);
	}
	else
	{
		stk_unique = std::make_unique<QueryStack>();
	}
  
	 
	QueryStack *stk = stk_unique.get();
	stk->addQuery("is", c_block, dct);


	if (stk->size() > 30 )
	{
		stk->dump();
		printf("huge");
	}

 
	CResultMatch result = this->Match(match, c_block, localsEntry, stk);
	 
	if (result.hasMatch ) 
	{
 
		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, result.maptch);

		 

		//Execute body		 

		if ( HBlockNoum anoum  = asHBlockNoum( dct->decideBody ))
		{		 
			auto qresolved =   resolve_noum(anoum, localsNext);
			if (qresolved != nullptr)  return qresolved;
		}

		auto r = exec_eval(dct->decideBody, localsNext,stk);
		if (HBlockToDecideOn adecided = asHBlockToDecideOn(r))
		{
			return adecided->decideBody;
		}
		return r;
	}

	return nullptr;
}


CBlocking::HBlock CBlockInterpreter::getDecidedValueOf(CBlocking::HBlock c_block, CBlocking::HBlockToDecideWhat_FirstNoum dct, HRunLocalScope localsEntry, QueryStack *stk_in) {


	HBlockMatch match = (dct->queryToMatch->value);

	std::unique_ptr<QueryStack> stk_unique = nullptr;
	if (stk_in != nullptr)
	{
		if (stk_in->isQuery("is", c_block, dct)) return nullptr;
		stk_unique = std::make_unique<QueryStack>(*stk_in);
	}
	else
	{
		stk_unique = std::make_unique<QueryStack>();
	}


	QueryStack *stk = stk_unique.get();
	stk->addQuery("is", c_block, dct);


	if (stk->size() > 30)
	{
		stk->dump();
		printf("huge");
	}


	CResultMatch result = this->Match(match, c_block, localsEntry, stk);

	if (result.hasMatch)
	{

		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, result.maptch);



		//Execute body		 

		if (HBlockNoum anoum = asHBlockNoum(dct->decideBody))
		{
			auto qresolved = resolve_noum(anoum, localsNext);
			if (qresolved != nullptr)  return qresolved;
		}

		auto r = exec_eval(dct->decideBody, localsNext, stk);
		if (HBlockToDecideOn adecided = asHBlockToDecideOn(r))
		{
			return adecided->decideBody;
		}
		return r;
	}

	return nullptr;
}



QueryResultContext CBlockInterpreter::getDecidedValue(CBlocking::HBlock decideBody,   HRunLocalScope localsEntry, QueryStack *stk)
{
 

	auto rdecided = exec_eval( decideBody , localsEntry,stk);
	 
	if (HBlockNoum ndecideRet = asHBlockNoum(rdecided))
	{
        if (language->is_nothing(ndecideRet))return QueryResultContext(QUndefined);
        HBlockBooleanValue  bv = language->asBoolean(ndecideRet);
        if (bv != nullptr)
        {
            if (bv->state   ) return QueryResultContext(QEquals);
            else { return QueryResultContext(QNotEquals);}
        }

//		if (ndecideRet->named == "true") return QueryResultContext(QEquals);
//		if (ndecideRet->named == "false") return QueryResultContext(QNotEquals);
//		if (ndecideRet->named == "nothing") return QueryResultContext(QUndefined);
	}

	if (rdecided == nullptr)
	{
		return QueryResultContext(QUndefined); //decide on nothing
	}
	if (HBlockToDecideOn ndecide = asHBlockToDecideOn(rdecided))
	{
		//verifica se eh true ou false 
		if (HBlockNoum ndecideValue = asHBlockNoum(ndecide->decideBody))
		{
            if (language->is_nothing(ndecideValue))return QueryResultContext(QUndefined);
            HBlockBooleanValue  bv = language->asBoolean(ndecideValue);
            if (bv != nullptr)
            {
                if (bv->state   ) return QueryResultContext(QEquals);
                else { return QueryResultContext(QNotEquals);}
            }

			//if (ndecideValue->named == "true") return QueryResultContext(QEquals);
			//if (ndecideValue->named == "false") return QueryResultContext(QNotEquals);
			//if (ndecideValue->named == "nothing") return QueryResultContext(QUndefined);
		}
		if (ndecide->decideBody == nullptr)
		{
			return QueryResultContext(QUndefined);
		}

		if (HBlockBooleanValue boolValuen = asHBlockBooleanValue(ndecide->decideBody))
		{
			if (boolValuen->state) return QueryResultContext(QEquals);
			else  return QueryResultContext(QNotEquals);
		}
		
		if (HBlockNothing ndecideValue = asHBlockNothing(ndecide->decideBody))
		{
			return QueryResultContext(QUndefined);
		}

		 

		ndecide->dump("");
		logError("Error on decided return value ");
		return QueryResultContext(QUndefined);
	}

	return QueryResultContext(QNotEquals); // deve decidir 

}
 

 
 


QueryResultContext CBlockInterpreter::getDecidedIf(CBlocking::HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack *stk_in)
{
 
	   

	std::unique_ptr<QueryStack> stk_unique = nullptr;
	if (stk_in != nullptr)
	{
		if (stk_in->isQuery("decide", c_block, dct))
		{
			return QUndefined;
		}
		stk_unique = std::make_unique<QueryStack>(*stk_in);
	}
	else
	{
		stk_unique = std::make_unique<QueryStack>();
	}


	QueryStack *stk = stk_unique.get();
	stk->addQuery("decide", c_block, dct);

	//if(localsEntry != nullptr) localsEntry->dump("   "); 

	CResultMatch result = this->Match(dct->queryToMatch, c_block, localsEntry,stk);

 
	if (result.hasMatch)
	{
		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry , result.maptch);
 
		 
		//auto rr =  query(dct->decideBody, localsNext, stk);
		//if (rr == QEquals) return QueryResultContext(QEquals);
 
		return getDecidedValue(dct->decideBody, localsNext,stk);
		 

	}

	return QueryResultContext(QUndefined);
}