#include <utility>

// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "BlockInterpreter.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"

 
#include "CblockAssertion.hpp"
#include "interpreter/QueryStack.hpp"
#include "CResultMatch.hpp"
#include "dynamicCast.hpp"
#include "sharedCast.hpp"
#include <cassert>


using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
 





namespace CBlocking {
	namespace Comparison {
		bool   isSame_BlockInstance(CBlockInstance* b1, CBlockInstance* b2);
	}
}


std::list<HBlockRelationInstance> CBlockInterpreter::getRelations()
{
	return  relInstances;
}



//bool CBlockInterpreter::query_is_sameKind(CBlock* c_block, CBlock* c_block1)
//{
//	
//}
//bool CBlockInterpreter::query_is_sameInstance(CBlock* c_block, CBlock* c_block1)
//{
//
//}
//bool CBlockInterpreter::query_is_sameNamedValue(CBlock* c_block, CBlock* c_block1)
//{
//
//}
//bool CBlockInterpreter::query_is_sameVariable(CBlock* c_block, CBlock* c_block1)
//{
//
//}

QueryResultContext CBlockInterpreter::query_is_List(CBlock *c_block, CBlock *c_block1) {
    if (CBlockList *lst1 = asCBlockList(c_block)) {
        if (CBlockList *lst2 = asCBlockList(c_block1))
        {
            if (lst1->lista.size() != lst2->lista.size()) return QNotEquals;			
        }

    }
    return QUndefined;
}

QueryResultContext CBlockInterpreter::query_is_extern(HBlock c_block, HBlock c_block1)
{
	
    return  query_is(std::move(c_block), std::move(c_block1),nullptr, nullptr);
}



 
bool CBlockInterpreter::is_primitive_value(HBlock c , HRunLocalScope localsEntry, QueryStack *stk)
{
	if (c == nullptr)
	{
		 printf( "Unable to do eval it");
		 return true;
	}

	if (asHBlockNothing(c)) return true;
	if (asHBlockBooleanValue(c)) return true;
	if (asHBlockList(c)) return true;
	if (asHBlockInstance(c)) return true;
	if (asHBlockRelationBase(c)) return true;
	if (asHBlockAction(c)) return true;
	if (asHBlockNamedValue(c)) return true;
	if (asHBlockText(c)) return true;
	 
	return false;
}



QueryResultContext CBlockInterpreter::query_is_same(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk) {
    string name1 = asBlockNoum(c_block);
    string name2 = asBlockNoum(c_block1);
    if (name1 == "" || name2 == "") return QUndefined;
    //std::cout << name1 << "  " << name2 << std::endl;
    if ( isSameString(name1 ,name2)) 
	{
        return QEquals;
    }
    return QNotEquals;
}

//QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, QueryStack *stk) {
//    if (HBlockNoum nnoum = asHBlockNoum(c_block1)) {
//        HBlock resolved = resolve_noum(nnoum);
//        if (resolved) {
//            return query_is(c_block, resolved, stk);
//        }
//        // pode ser um atributo
//        return query_is(c_block, nnoum, stk);
//    }
//	 
//    return query_is(c_block, c_block1, stk);
//}

PhaseResult::PhaseResult(bool _hasExecuted): hasExecuted(_hasExecuted)
{
	result = nullptr;
}

QueryResultContext CBlockInterpreter::query_is_instance_valueSet_valueInstance(HBlockInstance obj, HBlockInstanceNamed   valueName)
{

	for (auto &va : obj->namedSlots)
	{
		if (HBlockKindValue kindv = DynamicCasting::asHBlockKindValue(va->kind))
		{
			if (kindv->named == va->name->named())
			{
				if (is_InstanceOf(valueName, va->kind))
				{
					// pode ser  assigned ...
					if (CBlock::isSame(va->value.get(), valueName.get()))
					{
						return QueryResultContext(QEquals);
					}
					return  QueryResultContext(QNotEquals);
				}
			}
		}
	}

	return QueryResultContext(QUndefined);

}



QueryResultContext CBlockInterpreter::query_is_instance_valueSet(HBlock c_block, HBlock c_block1 , QueryStack *stk) {

    

	if (HBlockInstance cinst = asHBlockInstance(c_block))
	{
		if (HBlockNoum value = asHBlockNoum(c_block1)) {
			if (cinst->has_slot(value))
			{
				bool _value = false;
				const bool has_value = cinst->is_set(value, _value);
				if (has_value == true)
				{
					if (_value == true) {
						return QueryResultContext(QEquals);
					}
					return QueryResultContext(QNotEquals);
				}
			}
		}



		if (HBlockInstanceNamed nvalue = asHBlockInstanceNamed(c_block1)) {
			{
				bool _value = false;
				const QueryResultContext  has_value = query_is_instance_valueSet_valueInstance(cinst, nvalue);
				if (has_value.result != QUndefined) return has_value;
				
			}
		}



	}
    return QueryResultContext(QUndefined);

}






QueryResultContext
CBlockInterpreter::query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk) 
{

	if (HBlockNoum property_noum = asHBlockNoum(propname))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", property_noum, propObj, c_block1);
		if (next_stack != nullptr)
		{
			//eh plural de algo ?
			if (isSameString(property_noum->named(), "plural"))
			{
				string c = asBlockNoum(propObj);
				if (c != "")
				{
					HBlockNoum plural_named = get_plural_of(c);
					if (plural_named != nullptr)
					{
						return query_is(plural_named, c_block1, localsEntry, next_stack.get());
					}
				}
				return QueryResultContext(QUndefined);
			}

			//propObj->dump("");

			if (HBlockInstance cinst = asHBlockInstance(propObj))
			{
				{
					HBlockVariableNamed pvar = cinst->get_property(property_noum->named());
					if (pvar != nullptr)
					{
						auto next_var = pvar->value;
						if (next_var == nullptr) next_var = Nothing;
						if (CBlock::isSame(next_var.get(), Nothing.get()))
						{
							auto def_var = get_default_property_value(property_noum, cinst, localsEntry, stk);
							if (def_var != nullptr) next_var = def_var;
						}

						QueryResultContext rprop = query_is(next_var, c_block1, localsEntry, next_stack.get());
						if (rprop.result == QEquals) return rprop;
						return QNotEquals;
					}
					//logMessage(cinst->named + " Dont have Property " + property_noum->named);
					{
						QueryResultContext  result_prop = query_relation_property(property_noum, propObj, c_block1, localsEntry, next_stack.get());
						if (result_prop.result != QUndefined)
						{
							return result_prop;
						}
						return QueryResultContext(QUndefined);
					}


				}
			}

			// resolve object
			auto obj_resolved = exec_eval(propObj, localsEntry, stk);
			if (CBlock::isSame(obj_resolved.get(), propObj.get()) == false)
			{
				QueryResultContext  result_prop = query_is_propertyOf_value_imp(property_noum, obj_resolved, c_block1, localsEntry, next_stack.get());
				if (result_prop.result != QUndefined) return result_prop;

			}
		}
	}
	else
	{
		//logError("some mistake where\n");
		return QueryResultContext(QUndefined);
	}
    return QueryResultContext(QUndefined);
}


QueryResultContext CBlockInterpreter::query_is_propertyOf_value(HBlock c_property, HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk) {


	if (HBlockNoum cnoum_1 = asHBlockNoum(c_block1))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", cnoum_1, c_property, c_block1);
		if (next_stack != nullptr)
		{
			auto resolved = resolve_noum(cnoum_1, localsEntry);
			if (resolved != nullptr)
			{
				return query_is_propertyOf_value(c_property, resolved, localsEntry, next_stack.get());
			}
			 
		}
	}

	if (HBlockNoum cnoum_2 = asHBlockNoum(c_property))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", cnoum_2, c_property, c_block1);
		if (next_stack != nullptr)
		{
			auto resolved = resolve_noum(cnoum_2, localsEntry);
			return query_is_propertyOf_value(resolved, c_block1, localsEntry, next_stack.get());
		}
	}


	 
	if (HBlockProperty cproperty = asHBlockProperty(c_property))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", cproperty, c_property, c_block1);
		if (next_stack != nullptr)
		{
			if (HBlockNoum cnn = asHBlockNoum(cproperty->obj))
			{
				auto resolved = resolve_noum(cnn, localsEntry);
				if (resolved != nullptr)
				{
					return query_is_propertyOf_value_imp(cproperty->prop, resolved, c_block1, localsEntry, next_stack.get());
				}
				return QUndefined;

			}
			// property of What ??
			return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_block1, localsEntry, next_stack.get());
		}
	}

	if (HBlockProperty cproperty = asHBlockProperty(c_block1))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", cproperty, c_property, c_block1);
		if (next_stack != nullptr)
		{
			if (HBlockNoum cnn = asHBlockNoum(cproperty->obj))
			{
				auto resolved = resolve_noum(cnn, localsEntry);
				if (resolved != nullptr)
				{
					return query_is_propertyOf_value_imp(cproperty->prop, resolved, c_property, localsEntry, next_stack.get());
				}
				return QUndefined;

			}
			// property of What ??
			return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_property, localsEntry, next_stack.get());
		}
	}


	return QUndefined;

}


QueryResultContext CBlockInterpreter::query_is_Variable_value(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk)
{

    if (HBlockNoum cnn = asHBlockNoum(c_block ))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", cnn, c_block, c_block1);
		if (next_stack != nullptr)
		{
			auto var_1 = resolve_noum_as_variable(cnn);
			if (var_1 != nullptr)
			{
				return query_is_Variable_value(var_1, c_block1, localsEntry, next_stack.get());
			}
		}
    }

    if (HBlockVariableNamed nvar1 = asHBlockVariableNamed(c_block))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", nvar1, c_block, c_block1);
		if (next_stack != nullptr)
		{
			if (nvar1->value == nullptr) return QUndefined;
			if (HBlockVariableNamed nvar2 = asHBlockVariableNamed(c_block1))
			{
				if (nvar2->value == nullptr) return QUndefined;
				if (nvar1 == nvar2) return QEquals; //same reference			 
				return query_is(nvar1->value, nvar2->value, localsEntry, next_stack.get());
			}
			return query_is(nvar1->value, c_block1, localsEntry, next_stack.get());
		}
    }

    if (HBlockVariableNamed nvar2 = asHBlockVariableNamed(c_block1))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", nvar2, c_block, c_block1);
		if (next_stack != nullptr)
		{
			if (nvar2->value == nullptr) return QUndefined;
			return query_is(c_block, nvar2->value, localsEntry, next_stack.get());
		}
    }

    return QUndefined;
}

 

QueryResultContext CBlockInterpreter::query_is_DecideIf(HBlockMatchDirectIs DctQueryDirectIS,   HBlock c_block, HBlock c_block1, HBlock decideBody,HRunLocalScope localsEntry, QueryStack *stk)
{
	 
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", DctQueryDirectIS, c_block, c_block1);
		if (next_stack != nullptr)
		{
			auto result = Match_DirectIs(DctQueryDirectIS->obj, DctQueryDirectIS->value, c_block, c_block1, nullptr, next_stack.get());
			if (result.hasMatch == true)
			{
				//printf("Matched\n");
				//c_block->dump("");
				//DctQueryDirectIS->obj->dump("");
				//printf("\n");
				//c_block1->dump("");
				//DctQueryDirectIS->value->dump("");
				auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result.maptch);
				localsNext->locals.push_back({ "it", c_block });
				auto r = getDecidedValue( decideBody, localsNext, next_stack.get());
				if (r.result == QEquals)
				{
					return r;
				}
				else
				{
					return QNotEquals; //Default Outcome for Decide  IF
				}
				return r;
			}
		}
		return QUndefined;
}
 


QueryResultContext CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk_in) {

	 
 

	if (c_block->isSame(c_block.get(), c_block1.get()))
	{
		return QEquals;
	}
	if (c_block == nullptr)
	{
		return QUndefined;
	}
	if (c_block1 == nullptr)
	{
		return QUndefined;
	}

	std::unique_ptr<QueryStack> stk_unique = nullptr;
	 
	if (stk_in != nullptr)
	{
		if (stk_in->isQuery("is", c_block, c_block1))
		{
			return QUndefined;
		}
		 stk_unique = make_unique<QueryStack>(*stk_in); 
	}
	else
	{
		  stk_unique = make_unique<QueryStack>();
		 
	}

	QueryStack *stk   = stk_unique.get();
	stk->addQuery("is", c_block, c_block1);


 



    //resolve It

	if (HBlockKindNamed nkind = asHBlockKindNamed(c_block1))
	{
		HBlock resolved = resolve_kind(nkind  );
		if (resolved != nullptr)
		{
			return query_is(c_block, resolved, localsEntry, stk);
		}
	}

	if (HBlockKindNamed nkind = asHBlockKindNamed(c_block))
	{
		HBlock resolved = resolve_kind(nkind  );
		if (resolved != nullptr)
		{
			return query_is(resolved, c_block1, localsEntry, stk);
		}
	}

	if (CBlock::isSame(c_block1.get(), Anything.get()))
	{
		if (is_primitive_value(c_block,localsEntry,stk))
		{
			return QEquals;
		}
	}


	if (HBlockNoum nnoum = asHBlockNoum(c_block1))
	{
		HBlock resolved = resolve_noum(nnoum, localsEntry);
		if (resolved != nullptr)
		{			
			return query_is(c_block, resolved, localsEntry, stk);
		}
		if (nnoum->named() == "kind")
		{
			if ( asHBlockKind(c_block) != nullptr) return QEquals;
		} 
	}

    if (HBlockNoum nnoum2 = asHBlockNoum(c_block))
    {
        HBlock resolved = resolve_noum(nnoum2, localsEntry);
        if (resolved) 
		{
			return query_is(resolved, c_block1, localsEntry, stk);
        }
		
		if (nnoum2->named() == "kind")
		{
			if (asHBlockKind(c_block1) != nullptr) return QEquals;
		}
    }

	//printf("Query :\n");
	//c_block->dump("");
	//c_block1->dump("");
	//printf("\n");


	if (HBlockKind bkind = asHBlockKind(c_block1))
	{
		if (auto avar = asHBlockVariableNamed(c_block))
		{
			c_block->dump("");
			c_block1->dump("");
			auto qr =  query_is(avar->kind, bkind, localsEntry, stk);
			return qr;
		}		
	}


	//Metakinds
	if (HBlockKind bkind = asHBlockKind(c_block))
	{
		if (c_block1 == MetaKind )   return QEquals;
	}
	if (HBlockKindEntity bkind = asHBlockKindEntity(c_block))
	{		
		if (c_block1 == MetaKindEntity)   return QEquals;
	}
	if (HBlockCompositionPhrase bkind = asHBlockCompositionPhrase(c_block))
	{
		if (c_block1 == MetaKindPhrase)   return QEquals;
	}
	if (HBlockCompositionRelation bkind = asHBlockCompositionRelation(c_block))
	{
		if (c_block1 == MetaKindRelation)   return QEquals;
	}
	if (HBlockText btext = asHBlockText(c_block))
	{
		if (CBlock::isSame(c_block1.get() , MetaKindText.get()))   return QEquals;
		 
	}
 


	if (auto vvar = asCBlockVariableNamed(c_block1.get()))
	{
		auto r_var = vvar->value;
		if (r_var == nullptr) r_var = Nothing;
		return query_is(c_block, r_var, localsEntry, stk);
	}
	if (auto vvar = asCBlockVariableNamed(c_block.get()))
	{
		auto r_var = vvar->value;
		if (r_var == nullptr) r_var = Nothing;
		return query_is( r_var, c_block1, localsEntry, stk);
	}


	// check constant values
	for (auto cc : constant_assignments)
	{
		if (CBlock::isSame(  cc->get_obj().get(), c_block.get()) )
			if (CBlock::isSame(cc->get_definition().get(), c_block1.get()))
			{
				return QEquals;
			}
	}

	if (HBlockActionNamed cann = asHBlockActionNamed(c_block))
	{
		if (HBlockNoum nnoum2 = asHBlockNoum(c_block1))
		{			 
			if ((cann->named== nnoum2->named()))
			{
				return QEquals;
			}
		}
	}
	if (HBlockActionNamed cann = asHBlockActionNamed(c_block1))
	{
		if (HBlockNoum nnoum2 = asHBlockNoum(c_block))
		{
			if ((cann->named == nnoum2->named())) return QEquals;
		}
	}


	if (HBlockInstance cinst1 = asHBlockInstance(c_block))
	{
		if (HBlockInstanceNamed cinstvalNamed = asHBlockInstanceNamed(c_block1))
		{
			auto req = query_is_instance_valueSet_valueInstance(cinst1 , cinstvalNamed  );
			if (req.result != QUndefined) return req;
		}

		if (HBlockInstance cinst2 = asHBlockInstance(c_block1))
		{
			//if (isSameString(cinst1  , cinst2 )) return QEquals;
			if ( CBlock::isSame(cinst1.get(), cinst2.get())) return QEquals;
			return QNotEquals;
		}

		if (HBlockKindEntity kThing = asHBlockKindEntity(c_block1))
		{
			if (is_derivadeOf(cinst1, kThing, localsEntry))
			{
				return QEquals;
			}
			return QNotEquals;
		}
		if (HBlockKindValue kVal = asHBlockKindValue(c_block1))
		{
			if (is_derivadeOf(cinst1, kVal, localsEntry)) return QEquals;
			return QNotEquals;
		}

		//if (HBlockNoum knn = asHBlockNoum(c_block1))
		//{
		//	if (isSameString(knn->named, cinst1->named)) return QEquals;
		//}

	}

	
	

	 
		if (HBlockAction act = asHBlockAction(c_block))
			if (HBlockKindValue kval = asHBlockKindValue(c_block1))
			{
				if (isSameString(kval->named, "action"))
				{
					return QEquals;
				}
			}
	   
    
    //Resolve List OR
    if (HBlockList_OR  orList = asHBlockList_OR(c_block1))
    {
        for (auto &item : orList->lista)
        {
			std::unique_ptr<QueryStack>  next_stack =  generateNextStack(stk, "is", orList, c_block, item);
			if (next_stack != nullptr)
			{
				QueryResultContext qcc = query_is(c_block, item, localsEntry, next_stack.get());
				if (qcc.result == QEquals) return qcc;
			}
        }
    }

    //Resolve List OR
    if (HBlockSelector_All  selector_all = asHBlockSelector_All(c_block))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", selector_all, c_block, c_block1);
		if (next_stack != nullptr)
		{
			return Selector_all(selector_all->what, localsEntry, [&](HBlock e1)
			{
				return query_is(e1, c_block1, localsEntry, next_stack.get());

			});
		}
    }

    if (HBlockSelector_Any  selector_any = asHBlockSelector_Any(c_block))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", selector_any, c_block, c_block1);
		if (next_stack != nullptr)
		{
			return Selector_any(selector_any->what, localsEntry, [&](HBlock e1)
			{
				return query_is(e1, c_block1, localsEntry, next_stack.get());

			});
		}
    }



	if (HBlockMatch  m1 = asHBlockMatch(c_block1))
	{
		auto res_x = Match(m1, c_block, localsEntry, stk);
		if (res_x.hasMatch)
		{
			return QueryResultContext(QEquals, res_x.maptch);
		}
		return QueryResultContext(QNotEquals);
	}

	if (HBlockMatch  m2 = asHBlockMatch(c_block))
	{
		auto res_x = Match(m2, c_block1, localsEntry, stk);
		if (res_x.hasMatch)
		{
			return QueryResultContext(QEquals, res_x.maptch);
		}
		return QueryResultContext(QNotEquals);
	}



    for (auto dct : decides_what) 
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", dct, c_block, c_block1);
		if (next_stack != nullptr)
		{

			//porque testando isso ?
			if (asHBlockInstance(c_block1) == nullptr)
			{
				auto dctValueWrap_1 = getDecidedValueOf(c_block1, dct, nullptr, next_stack.get());
				if (dctValueWrap_1 != nullptr) {
					QueryResultContext rw = query_is(c_block, dctValueWrap_1, localsEntry, next_stack.get());  //is not opnional
					if (rw.result != QUndefined)
					{
						return rw;
					}
				}
			}
		}
    }



    //is scond a kind of anything ??
    if (HBlockKind bkind = asHBlockKind(c_block1)) 
	{
        if (HBlockKind akind = asHBlockKind(c_block)) 
		{
            bool b = is_derivadeOf(akind, bkind);
            if (b) return QEquals;
        } else if (HBlockInstance aInstance = asHBlockInstance(c_block)) {
            bool b = is_derivadeOf(aInstance, bkind,localsEntry);
            if (b) return QEquals;
        } 
    }
    
	QueryResultContext qprop = query_is_propertyOf_value(c_block, c_block1, localsEntry, stk);
		if (qprop.result != QUndefined)
		{
			return qprop;
		}


	
		QueryResultContext rinst = (query_is_instance_valueSet(c_block, c_block1, stk));
		if (rinst.result != QUndefined) {
			return rinst;
		}

	
	




    for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it) {
        if (HBlockToDecide tdef = asHBlockToDecide(*it)) 
		{

        }
    }


    {
		QueryResultContext qprop = query_is_Variable_value(c_block, c_block1,localsEntry, stk);  // Verifica as variaveis globais
        if (qprop.result != QUndefined) {
            return qprop;
        }
    }

  

	QueryResultContext r2 = query_is_same(c_block, c_block1,localsEntry, stk);
    if (r2.result == QEquals) {
        return r2;
    }

	{
		if (HBlockInstance ninst_1 = asHBlockInstance(c_block))
			if (HBlockInstance ninst_2 = asHBlockInstance(c_block1)) 
			{
				if (Comparison::isSame_BlockInstance(ninst_1.get(), ninst_2.get()))
				{
					return QEquals;
				}
				/*if (ninst_1->baseKind != nullptr && ninst_1->baseKind != ninst_1->baseKind) {
					if (ninst_1 == ninst_2) return QEquals;
				}*/

			}
	}

	{
		if (HBlockAction act = asHBlockAction(c_block))
			if (HBlockKindValue kval = asHBlockKindValue(c_block1))
			{
				if (isSameString(kval->named ,  "action"))
				{
					return QEquals;
				} 
			}
	}

	for (auto dctIF : decides_if)
	{
		if (HBlockMatchDirectIs  DctQueryDirectIS = asHBlockMatchDirectIs(dctIF->queryToMatch))
		{

			auto r = query_is_DecideIf(DctQueryDirectIS, c_block, c_block1, dctIF->decideBody, localsEntry, stk);
			if (r.result != QUndefined)
			{
				return r;
			}

			//std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", DctQueryDirectIS, c_block, c_block1);
			//if (next_stack != nullptr)
			//{
			//	auto result = Match_DirectIs(DctQueryDirectIS->obj, DctQueryDirectIS->value, c_block, c_block1, nullptr, next_stack.get());
			//	if (result.hasMatch == true)
			//	{
			//		printf("Matched\n");
			//		c_block->dump("");
			//		DctQueryDirectIS->obj->dump("");
			//		printf("\n");
			//		c_block1->dump("");
			//		DctQueryDirectIS->value->dump("");
			//		auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result.maptch);					
			//		localsNext->locals.push_back({ "it", c_block });
			//		auto r = getDecidedValue(dctIF->decideBody, localsNext, next_stack.get());
			//		if (r.result ==QEquals)
			//		{
			//			return r;
			//		}
			//		else
			//		{
			//			return QNotEquals; //Default Outcome for Decide  IF
			//		}
			//		return r;
			//	}
			//}
		}
	}


	if (HBlockMatchNOT matchBlock_not = asHBlockMatchNOT(c_block1))
	{
		auto result = query_is(c_block, matchBlock_not->input, localsEntry, stk);
		if (result.result == QEquals) return QNotEquals;
		if (result.result == QNotEquals) return QEquals;
		return QEquals;
	}


	if (HBlockMatch matchBlock = asHBlockMatch(c_block1))
	{
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", matchBlock, c_block, c_block1);
		if (next_stack != nullptr)
		{
			 
			auto matchBlock_r = Resolve_Selector(matchBlock, localsEntry);


			auto r_mtch = Match(matchBlock_r, c_block, localsEntry, next_stack.get());
			if (r_mtch.hasMatch)
			{
				return  QueryResultContext(QEquals, r_mtch.maptch);
			}
			return QUndefined;
		}
	}

    
    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		 
		if (HBlockAssertion_is qdef = asHBlockAssertion_is(*it))
		{
			std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, "is", qdef, c_block, c_block1);
			if (next_stack != nullptr)
			{
				auto qc = query_is_same(c_block, qdef->get_obj(), localsEntry, next_stack.get());
				if (qc.result == QEquals) 
				{
					{
						QueryResultContext r = query_is(qdef->get_definition(), c_block1, localsEntry, next_stack.get());
						if (r.result != QUndefined) 
						{
							return r;
						}
					}

				}
			}
		}
    }


	if (HBlockVariableNamed var_n = asHBlockVariableNamed(c_block1))
	{
		if (var_n->value == nullptr)	return query_is(c_block, Nothing, localsEntry,  stk);
		return query_is(c_block, var_n->value, localsEntry, stk);
	}

	if (HBlockVariableNamed var_n = asHBlockVariableNamed(c_block))
	{
		if (var_n->value == nullptr)	return query_is( Nothing, c_block1, localsEntry, stk);
		return query_is(var_n->value ,c_block1,   localsEntry, stk);
	}



	//logMessage("I cant query");
	//c_block->dump("");
	//c_block1->dump("");

	//se tudo falhar , tente isso ....
	auto resolved_b = exec_eval(c_block1, localsEntry, stk);
	if (resolved_b != nullptr)
	{
		if (CBlock::isSame(resolved_b.get(), c_block1.get()) == false)
		{
			return query_is(c_block, resolved_b, localsEntry, stk);
		}
	}
	auto resolved_a = exec_eval(c_block , localsEntry, stk);
	if (resolved_a != nullptr)
	{
		if (CBlock::isSame(resolved_a.get(), c_block.get()) == false)
		{
			return query_is(resolved_a, c_block1, localsEntry, stk);
		}
	}

 
    return QueryResultContext(QUndefined);

}


QueryResultContext CBlockInterpreter::query(HBlockAssertion_is q,
                                    HBlockAssertion_is base, HRunLocalScope localsEntry , QueryStack *stk) //Compara as duas queries e retorna true se base valida q
{
	QueryResultContext qcc1 =  query_is(q->get_obj(), base->get_obj(), localsEntry, stk);
	if (qcc1.result == QEquals)
	{
		QueryResultContext qcc2 = query_is(q->get_definition(), base->get_definition(), localsEntry, stk);
		if (  qcc2.result == QEquals)
		{
			return qcc2;
		}
	}
    return QUndefined;

}


QueryResultContext  CBlockInterpreter::Selector_all(HBlock aList, HRunLocalScope localsEntry, std::function< QueryResultContext(HBlock) > selector )
{
    std::list<HBlock> hlist = resolve_as_list(aList, localsEntry);
    if (hlist.empty()) return QUndefined;
    for(HBlock &e : hlist)
    {
		QueryResultContext qcc = selector(e);
        if ( qcc.result != QEquals)
        {
            logError("fail on |");
            e->dump("  ");
            return  QNotEquals;
        }		
    }
    return QEquals;
}


QueryResultContext  CBlockInterpreter::Selector_any(HBlock aList, HRunLocalScope localsEntry, std::function< QueryResultContext(HBlock) > selector )
{
    std::list<HBlock> hlist = resolve_as_list(aList, localsEntry);
    if (hlist.empty()) return QUndefined;
    for (HBlock &e : hlist)
    {
		QueryResultContext qcc = selector(e);
        if (qcc.result == QEquals) return qcc;		
    }
    return QNotEquals;
}



QueryResultContext CBlockInterpreter::get_system_verbs(string cs, HBlock n1, HBlock n2, HRunLocalScope localsEntry,QueryStack *stk)
{
    

    //Resolve List OR
    if (HBlockList_OR  orList = asHBlockList_OR(n2))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, cs, orList,  n1,  n2);
		if (next_stack != nullptr)
		{
			for (auto &item : orList->lista)
			{
				QueryResultContext qcc = get_system_verbs(cs, n1, item, localsEntry, next_stack.get());
				if (qcc.result == QEquals) return qcc;
			}
		}
    }

    //Resolve List ALL
    if (HBlockSelector_All  selector_all = asHBlockSelector_All(n1))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, cs, selector_all, n1, n2);
		if (next_stack != nullptr)
		{
			return Selector_all(selector_all->what, localsEntry, [&](HBlock e1)
			{
				return get_system_verbs(cs, e1, n2, localsEntry, next_stack.get());

			});
		}
    }


    //Resolve List ANY
    if (HBlockSelector_Any  selector_any = asHBlockSelector_Any(n1))
    {
		std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, cs, selector_any, n1, n2);
		if (next_stack != nullptr)
		{
			return Selector_any(selector_any->what, localsEntry, [&](HBlock e1)
			{
				return get_system_verbs(cs, e1, n2, localsEntry, next_stack.get());

			});
		}
    }


    //logMessage("try verb|" + cs + "|");
    if (cs =="listed in")
    {
        return queryVerb_ListedIn(n1, n2,localsEntry, stk);
    }


	if (cs == "relates")
	{
		//printf("System relates verb \n");
		if (HBlockRelationBase  r_rel = asHBlockRelationBase(n1))
		{
			if (HBlockRelationArguments  r_args = asHBlockRelationArguments(n2))
			{
				auto r_exist = query_relation(r_rel, r_args->value1, r_args->value2, localsEntry, stk); 
				return r_exist; 
			}
		}
		return QueryResultContext(QUndefined);
	}

	if (cs == "exactly matches")
	{
		//printf("System exactly matches verb \n");
		return queryVerb_exactly_matches(n1, n2, localsEntry, stk);
	}

	if (cs == "matches")
	{
		//printf("System matches verb \n");
		return queryVerb_matches(n1, n2, localsEntry, stk);
	}



    return QueryResultContext( QUndefined);
}

QueryResultContext CBlockInterpreter::query_verb_innn(string verb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk_in)
{
	QueryResultContext rrcstm = get_system_verbs(verb, c_block, value, localsEntry, stk_in); // "listed in" , "size of"
	if (rrcstm.result != QUndefined) return rrcstm;
	QueryResultContext rr = query_user_verbs(verb, c_block, value, localsEntry, stk_in);
	if (rr.result != QUndefined)
	{
		return rr;
	}
	return rr;
}

QueryResultContext CBlockInterpreter::query_verb(HBlockIsVerb is_verb, HRunLocalScope localsEntry ,QueryStack *stk)
{ 

	HBlock val_1 = nullptr;
	HBlock val_2 = nullptr;
	if (is_verb->n1 != nullptr)  val_1 = resolve_argument(is_verb->n1, localsEntry, stk);
	if (is_verb->n2 != nullptr)  val_2 = resolve_argument(is_verb->n2, localsEntry, stk); 

	if (is_verb->n1 != nullptr && val_1 ==nullptr )
	{
		printf("Noum 1 undefined\n");
		is_verb->n1->dump("");
		if (localsEntry != nullptr)localsEntry->dump("+ ");
	}

	if (is_verb->n2 != nullptr && val_2 == nullptr)
	{
		printf("Noum 2 undefined\n");
		is_verb->n2->dump("");


		if (localsEntry != nullptr)localsEntry->dump("+ ");
	}


	if (CBlock::isSame(val_2.get(), Nothing.get()))
	{
		auto vr = query_verb_innn(is_verb->verb, val_1, Anything, localsEntry, stk);
		if (vr.result != QEquals)
		{
			return QueryResultContext(QEquals, vr.matchedResult);
		}
		else
		{
			return  QNotEquals;
		}		
	}

	return query_verb_innn(is_verb->verb, val_1, val_2, localsEntry, stk);
	 

   
}

QueryResultContext CBlockInterpreter::query_not_verb(HBlockIsNotVerb is_verb, HRunLocalScope localsEntry , QueryStack *stk)
{

	HBlock val_1 = nullptr;
	HBlock val_2 = nullptr;
	if (is_verb->n1 != nullptr)  val_1 = resolve_argument(is_verb->n1, localsEntry, stk);
	if (is_verb->n2 != nullptr)  val_2 = resolve_argument(is_verb->n2, localsEntry, stk);


	if (CBlock::isSame(val_2.get(), Nothing.get()))
	{
		auto vr = query_verb_innn(is_verb->verb, val_1, Anything, localsEntry, stk);
		if (vr.result == QEquals)
		{
			return QEquals;
		}
		else
		{
			return QNotEquals;
		}
		 
	}


	QueryResultContext rr = query_verb_innn(is_verb->verb, val_1, val_2, localsEntry, stk);
	if (rr.result == QEquals)
	{
		return QNotEquals;
	}
	else
	{
		return QEquals;
	}

	//QueryResultContext rrcstm = get_system_verbs(is_verb->verb, val_1, val_2, localsEntry, stk); // "listed in" , "size of"
 //   if (rrcstm.result == QEquals) return QNotEquals;
 //   if (rrcstm.result == QNotEquals) return QEquals;


	//QueryResultContext rr = query_user_verbs(is_verb->verb, val_1, val_2, localsEntry, stk);
 //   if (rr.result == QEquals) return QNotEquals;
 //   if (rr.result == QNotEquals) return QEquals;
 //   return rr;
}



QueryResultContext CBlockInterpreter::query_decides(HBlock q, HRunLocalScope localsEntry, QueryStack *stk)
{
	for (auto dctIF : decides_if)
	{
		QueryResultContext dctValueWrap_1 = getDecidedIf(q, dctIF, nullptr, stk);
		if (dctValueWrap_1.result != QUndefined)
		{
			return  dctValueWrap_1;
		}
	}


    for (HBlockToDecideWhat &e : decides_what)
    {
      CResultMatch  reMatch = Match(e->queryToMatch, q, nullptr, stk);
      if (reMatch.hasMatch )
      {
		  
		  auto localsNext = std::make_shared< CRunLocalScope >(nullptr, reMatch.maptch);
		  QueryResultContext rr = query(e->decideBody, localsNext, stk);
		  if (rr.result == QEquals) return rr;

		  return QueryResultContext(QNotEquals);
          //return   e->decideBody;
      }

    }

 

    return QueryResultContext(QUndefined);

}



 

QueryResultContext Interpreter::CBlockInterpreter::query_comp(string cs, HBlock vr1, HBlock vr2, HRunLocalScope localsEntry, QueryStack * stk)
{

	// vr1 e vr2 sao enum do mesmo tipo ?
	
	if (HBlockMatchNoum mm1 = asHBlockMatchNoum(vr1))
	{
		auto ax = resolve_argument(mm1->inner, localsEntry, stk);
		if (ax != nullptr)
		{
			if (CBlock::isSame(vr1.get(), ax.get()) == false)
			{
				return query_comp(cs,  ax, vr2, localsEntry, stk);
			}
		}
	}


	 if (HBlockMatchNoum mm2 = asHBlockMatchNoum(vr2))
	 {
		 auto ax = resolve_argument(mm2->inner, localsEntry, stk);
		 if (ax !=nullptr)
		 {
			 if (CBlock::isSame( vr2.get() , ax.get() ) ==false )
			 {
				 return query_comp(cs, vr1, ax, localsEntry, stk);
			 }
		 }
	 }

	if (cs == "greater" || cs == "less")
	{
		if (HBlockInstanceNamed in1 = asHBlockInstanceNamed(vr1))
		{
			if (HBlockInstanceNamed in2 = asHBlockInstanceNamed(vr2))
			{
				auto k1 = in1->baseKind;
				auto k2 = in2->baseKind;

				if (HBlockKindValue kv1 = asHBlockKindValue(k1))
					if (HBlockKindValue kv2 = asHBlockKindValue(k2))
					{
						bool is_equivalent = false;

						if (CBlock::isSame(kv1.get(), kv2.get()))is_equivalent = true;
						else
						{
							if (is_derivadeOf(k1, k2) || is_derivadeOf(k2, k1))is_equivalent = true;
						}
						if(is_equivalent)
						{
							if ((cs == "greater")&&(in1->id > in2->id)) return QueryResultContext(QEquals);
							if ((cs == "greater") && (in1->id <= in2->id)) return QueryResultContext(QNotEquals);
							if ((cs == "less") && (in1->id < in2->id)) return QueryResultContext(QEquals);
							if ((cs == "less") && (in1->id >= in2->id)) return QueryResultContext(QNotEquals);
						}
						else
						{
							logError("incompatible comparasion");
						}
					}
			}
		}
	}

	// tem algum decide para isso ?
	for (auto dctIF : decides_if)
	{
		if (HBlockMatchIsAdverbialComparasion  mAdvComp = asHBlockMatchIsAdverbialComparasion(dctIF->queryToMatch))
		{
			 
			if (mAdvComp->adverb == cs)
			{

				auto result1 = Match(mAdvComp->obj, vr1, localsEntry, stk);
				if (result1.hasMatch == true)
				{
					printf("Matched\n");
					auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result1.maptch);
					
					auto result2 = Match(mAdvComp->value, vr2, localsNext, stk);
					if (result2.hasMatch == true)
					{

						HRunLocalScope localsNext_inner = std::make_shared< CRunLocalScope >(localsNext, result2.maptch);
				 

						auto r = getDecidedValue(dctIF->decideBody, localsNext_inner, stk);

						if (r.result == QEquals)
						{
							return r;
						}
						return r;
					}
				}
			}
		}
	}


	printf("==============================\n");
	if(localsEntry!=nullptr)localsEntry->dump("");
	vr1->dump("");
	vr2->dump("");

	return QueryResultContext(QUndefined);
}

QueryResultContext CBlockInterpreter::query(HBlock q, HRunLocalScope localsEntry ,QueryStack *stk  )
{
 
	 
 

    if (HBlockIsNotVerb is_nverb = asHBlockIsNotVerb(q))
    {
		QueryResultContext retv = query_not_verb(is_nverb, localsEntry , stk);
		if (retv.result != QUndefined)
		{
			return retv;
		}
    }

    if (HBlockIsVerb is_verb = asHBlockIsVerb(q) )
    {
 

	   QueryResultContext retv = query_verb(is_verb, localsEntry , stk);


	   if (retv.result != QUndefined) return retv;
    }


		if (HBlockAssertion_isDirectAssign q_dir_assign = asHBlockAssertion_isDirectAssign(q))
		{
			auto vr1 = resolve_if_noum(q_dir_assign->get_obj() , localsEntry , std::list<std::string>() );
			if (vr1 == nullptr) vr1 = q_dir_assign->get_obj();
			auto vr2 = resolve_if_noum(q_dir_assign->get_definition(), localsEntry, std::list<std::string>());
			if (vr2 == nullptr) vr2 = q_dir_assign->get_definition();
			if (q_dir_assign->isSame(vr1.get(), vr2.get()))
			{
			return QEquals;
			}

 

			QueryResultContext ret =  query_is(vr1,vr2, localsEntry, stk);
			if (ret.result != QUndefined)
			{
				return ret;
			}

 
		}
    

		if ( HBlockAssertion_isNotDirectAssign q_not_dir = asHBlockAssertion_isNotDirectAssign(q))
		{
			if (q_not_dir->isSame(q_not_dir->get_obj().get(), q_not_dir->get_definition().get()))
			{
				return QNotEquals;
			}

			QueryResultContext rr =  query_is(q_not_dir->get_obj(), q_not_dir->get_definition(), localsEntry, stk);
			if (rr.result == QEquals) return QNotEquals;
			if (rr.result == QNotEquals) return QEquals;			
		 
		}



		if (HBlockIsAdverbialComparasion q_comp = asHBlockIsAdverbialComparasion (q))
		{
			auto vr1 = resolve_if_noum(q_comp->get_obj(), localsEntry, std::list<std::string>());
			if (vr1 == nullptr && q_comp->get_obj() != nullptr) vr1 = q_comp->get_obj();

			auto vr2 = resolve_if_noum(q_comp->get_definition(), localsEntry, std::list<std::string>());
			if (vr2 == nullptr && q_comp->get_definition() != nullptr) vr2 = q_comp->get_definition();

			QueryResultContext rr = query_comp( q_comp->adverb,vr1,vr2, localsEntry, stk);
			return rr;
		}


	//Booleans
		 

	if (HBlockBooleanAND q_bool_and = asHBlockBooleanAND(q))
	{
		QueryResultContext result_A = query(q_bool_and->input_A, localsEntry, stk);
		if (result_A.result == QNotEquals) return  QNotEquals;
		if (result_A.result == QUndefined) return  QNotEquals;

		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry , result_A.matchedResult);
		 

		QueryResultContext result_B = query(q_bool_and->input_B, localsNext, stk);
		if (result_B.result == QNotEquals) return  QNotEquals;
		if (result_B.result == QUndefined) return  QNotEquals;

		auto localsNext_2 = std::make_shared< CRunLocalScope >(localsNext ,  result_B.matchedResult);
		
		return QueryResultContext(QEquals, result_A.matchedResult, result_B.matchedResult);
	}

	if (HBlockBooleanOR q_bool_or = asHBlockBooleanOR(q))
	{
		QueryResultContext result_A = query(q_bool_or->input_A, localsEntry, stk);
		if (result_A.result == QEquals) return  result_A;
		QueryResultContext result_B = query(q_bool_or->input_B, localsEntry, stk);
		if (result_B.result == QEquals) return  result_B;
		return QUndefined;
	}


	if (HBlockBooleanNOT q_bool_not = asHBlockBooleanNOT (q))
	{

		QueryResultContext result_A = query(q_bool_not->input_A, localsEntry, stk);

		if (result_A.result == QEquals) return  QNotEquals;		 
		auto rNothing =  QueryResultContext(QEquals  );
		rNothing.matchedResult = result_A.matchedResult;
		return rNothing;
	}

	/*for (auto dctIF : decides_if)
	{
		QueryResultContext dctValueWrap_1 = getDecidedIf(q, dctIF, localsEntry, stk);
		if (dctValueWrap_1.result != QUndefined)
		{
			return  dctValueWrap_1;
		}
	}*/

	if (HBlockComandList q_cmd = asHBlockComandList(q))
	{
		logError("cannot query a Command list ");
		assert(false);
	}
	//q->dump("");
 

    return QUndefined;

}

QueryResultContext CBlockInterpreter::query(HBlock q)
{
	
    return query(q, nullptr,  nullptr); 
}


//NSTerm::HTerm CBlockInterpreter::executeAssertion_is(HBlockAssertion_is b) {
//
//    // is what ??
//
//    if (HBlockNamedValue is_namedValue = asHBlockNamedValue(b->get_obj())) {
//
//
//    }
//
//    if (HBlockAssertion_canBe noum_canBe = asHBlockAssertion_canBe(b->get_definition())) {
//
//    }
//
//    if (HBlockKind is_define_kind = asHBlockKind(b->get_definition())) {
//
//    }
//    return nullptr;
//
//}


