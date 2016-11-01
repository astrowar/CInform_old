

#include "BlockInterpreter.hpp"
  #include "CBlockInterpreterRuntime.hpp"
#include "CblockAssertion.hpp"
#include "QueryStack.hpp"
#include "CResultMatch.hpp"
#include "dynamicCast.hpp"
#include "sharedCast.hpp"
#include <cassert>

using namespace std;




std::list<HBlockRelationInstance> CBlockInterpreter::getRelations()
{
	return  relInstances;
}

CBlockInterpreter::CBlockInterpreter() {
}

CBlockInterpreter::~CBlockInterpreter() {
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

QueryResul CBlockInterpreter::query_is_List(CBlock *c_block, CBlock *c_block1) {
    if (CBlockList *lst1 = asCBlockList(c_block)) {
        if (CBlockList *lst2 = asCBlockList(c_block1))
        {
            if (lst1->lista.size() != lst2->lista.size()) return QNotEquals;

        }

    }
    return QUndefined;
}

QueryResul CBlockInterpreter::query_is_extern(HBlock c_block, HBlock c_block1)
{
    return  query_is(c_block, c_block1,nullptr, QueryStack());
}



QueryResul CBlockInterpreter::query_is_same(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk) {
    string name1 = BlockNoum(c_block);
    string name2 = BlockNoum(c_block1);
    if (name1 == "" || name2 == "") return QUndefined;
    //std::cout << name1 << "  " << name2 << std::endl;
    if (name1 == name2) {
        return QEquals;
    }
    return QNotEquals;
}

//QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, QueryStack stk) {
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

QueryResul CBlockInterpreter::query_is_instance_valueSet(HBlock c_block, HBlock c_block1 , QueryStack stk) {

    

    if (HBlockInstance cinst = asHBlockInstance(c_block))
        if (HBlockNoum value = asHBlockNoum(c_block1)) {
            if (cinst->has_slot(value)) 
			{
                logMessage( cinst->named+ "  " + value->named);
                if (cinst->is_set(value)) {
                    return QEquals;
                }
                return QNotEquals;
            }
        }
    return QUndefined;

}

QueryResul
CBlockInterpreter::query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk) {
    
	 

	if (HBlockNoum property_noum = asHBlockNoum(propname))
	{
		if (HBlockInstance cinst = asHBlockInstance(propObj))
		{

			{
				HVariableNamed pvar = cinst->get_property(property_noum->named);
				if (pvar != nullptr)
				{
					// logMessage("property  is ");
					//if (pvar->value != nullptr)
					//{
					//	pvar->value->dump("  ");
					//}
					//else
					//{
					//	logMessage("    EMPTY   ");

					//}
					//c_block1->dump("  ");


					auto rprop = query_is(pvar->value, c_block1, localsEntry, stk);
					if (rprop == QEquals) return QEquals;
					return QNotEquals;
				}
				logMessage(" Dont have Property");
				{
					auto  result_prop = query_relation_property(property_noum, propObj, c_block1, localsEntry, stk);

 

					if (result_prop != QUndefined) return result_prop;
					return QUndefined;
				}


			}
		}
	}
	else
	{
		logError("some mistake where\n");
		return QUndefined;
	}
    return QUndefined;
}


QueryResul CBlockInterpreter::query_is_propertyOf_value(HBlock c_property, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk) {


	if (HBlockNoum cnoum_1 = asHBlockNoum(c_block1))
	{
		auto resolved = resolve_noum(cnoum_1, localsEntry);
		return query_is_propertyOf_value(c_property, resolved, localsEntry, stk);
	}

	if (HBlockNoum cnoum_2 = asHBlockNoum(c_property))
	{
		auto resolved = resolve_noum(cnoum_2, localsEntry);
		return query_is_propertyOf_value(resolved, c_block1, localsEntry, stk);
	}


	 
	if (HBlockProperty cproperty = asHBlockProperty(c_property))
	{
		if (HBlockNoum cnn = asHBlockNoum(cproperty->obj))
		{
			auto resolved = resolve_noum(cnn, localsEntry);
			if (resolved != nullptr)
			{
				return query_is_propertyOf_value_imp(cproperty->prop, resolved, c_block1, localsEntry, stk);
			}
			return QUndefined;

		}
		// property of What ??
		return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_block1, localsEntry, stk);
	}

	if (HBlockProperty cproperty = asHBlockProperty(c_block1))
	{
		if (HBlockNoum cnn = asHBlockNoum(cproperty->obj))
		{
			auto resolved = resolve_noum(cnn, localsEntry);
			if (resolved != nullptr)
			{
				return query_is_propertyOf_value_imp(cproperty->prop, resolved, c_property, localsEntry, stk);
			}
			return QUndefined;

		}
		// property of What ??
		return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_property, localsEntry, stk);
	}


	return QUndefined;

}


QueryResul CBlockInterpreter::query_is_Variable_value(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk)
{

    if (HBlockNoum cnn = asHBlockNoum(c_block ))
    {
        auto var_1 = resolve_noum_as_variable(cnn);
        if (var_1 !=nullptr)
        {
            return query_is_Variable_value(var_1, c_block1, localsEntry, stk);
        }
    }

    if (HVariableNamed nvar1 = asHVariableNamed(c_block))
    {
        if (nvar1->value == nullptr) return QUndefined;
        if (HVariableNamed nvar2 = asHVariableNamed(c_block1))
        {
            if (nvar2->value == nullptr) return QUndefined;
            if (nvar1 == nvar2) return QEquals; //same reference			 
            return query_is(nvar1->value, nvar2->value, localsEntry,stk);
        }
        return query_is(nvar1->value, c_block1,localsEntry, stk);		
    }

    if (HVariableNamed nvar2 = asHVariableNamed(c_block1))
    {
        if (nvar2->value == nullptr) return QUndefined;		 
        return query_is(c_block , nvar2->value,localsEntry, stk);
    }

    return QUndefined;
}

 


QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk) {
    
 

	if (c_block->isSame(c_block.get(), c_block1.get() ))
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

	if (stk.isQuery("is", c_block, c_block1))
	{
		return QUndefined;
	}
    stk.addQuery("is", c_block, c_block1);
	

    //resolve It
	if (HBlockNoum nnoum = asHBlockNoum(c_block1))
	{
		HBlock resolved = resolve_noum(nnoum, localsEntry);
		if (resolved != nullptr)
		{
			return query_is(c_block, resolved, localsEntry, stk);
		}

	}

    if (HBlockNoum nnoum2 = asHBlockNoum(c_block))
    {
        HBlock resolved = resolve_noum(nnoum2, localsEntry);
        if (resolved) 
		{
			return query_is(resolved, c_block1, localsEntry, stk);
        }
 
    }


	if (HBlockInstance cinst1 = asHBlockInstance (c_block))
		if (HBlockInstance cinst2 = asHBlockInstance(c_block1))
		{
			if (cinst1->named == cinst2->named) return QEquals;
			return QNotEquals;
		}

	if (HBlockMatch matchBlock = asHBlockMatch  (c_block1))
	{
		 auto r_mtch =  Match(matchBlock, c_block, localsEntry, stk);
		 if (r_mtch.hasMatch)
		 {
			 return QEquals;			 
		 }
		 //printf("Match Fail \n");
		 //c_block->dump("  ");
		 //c_block1->dump("  ");

		 return QUndefined;
	}


    
    //Resolve List OR
    if (HBlockList_OR  orList = asHBlockList_OR(c_block1))
    {
        for (auto &item : orList->lista)
        {
            if (query_is(c_block, item,localsEntry, stk) == QEquals) return QEquals;
        }
    }

    //Resolve List OR
    if (HBlockSelector_All  selector_all = asHBlockSelector_All(c_block))
    {
        return Selector_all(selector_all->what, localsEntry, [&](HBlock e1)
        {
            return query_is( e1, c_block1,localsEntry, stk);

        });
    }

    if (HBlockSelector_Any  selector_any = asHBlockSelector_Any(c_block))
    {
        return Selector_any(selector_any->what, localsEntry, [&](HBlock e1)
        {
            return query_is(e1, c_block1, localsEntry, stk);

        });
    }



    

    for (auto dct : decides_what) {
        auto dctValueWrap = getDecidedValueOf(c_block, dct,localsEntry, stk);
        if (dctValueWrap != nullptr) 
        {
         
            auto rw =  query_is(dctValueWrap, c_block1, localsEntry, stk); //is not opnional
			if (rw != QUndefined) return rw;
            //return rw;
        }
    }

    for (auto dct : decides_what) 
    {
        
        auto dctValueWrap_1 = getDecidedValueOf(c_block1, dct, localsEntry, stk);
        if (dctValueWrap_1 != nullptr) {
            auto rw = query_is(c_block, dctValueWrap_1, localsEntry,stk);  //is not opnional
			if (rw != QUndefined) return rw;
			//return rw;
        }
    }



    //is scond a kind of anything ??
    if (HBlockKind bkind = asHBlockKind(c_block1)) {
        if (HBlockKind akind = asHBlockKind(c_block)) {
            bool b = is_derivadeOf(akind, bkind);
            if (b) return QEquals;
        } else if (HBlockInstance aInstance = asHBlockInstance(c_block)) {
            bool b = is_derivadeOf(aInstance, bkind,localsEntry);
            if (b) return QEquals;
        } 
    }
    






    for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it) {
        if (HBlockToDecide tdef = asHBlockToDecide(*it)) {

        }
    }


    {
        QueryResul qprop = query_is_Variable_value(c_block, c_block1,localsEntry, stk);  // Verifica as variaveis globais
        if (qprop != QUndefined) {
            return qprop;
        }
    }

    {
        QueryResul rinst = (query_is_instance_valueSet(c_block, c_block1,stk));
        if (rinst != QUndefined) {
            return rinst;
        }

        QueryResul qprop = query_is_propertyOf_value(c_block, c_block1, localsEntry, stk);
        if (qprop != QUndefined) 
		{
            return qprop;
        }
    }

    auto r2 = query_is_same(c_block, c_block1,localsEntry, stk);
    if (r2 == QEquals) {
        return r2;
    }

	{
		if (HBlockInstance ninst_1 = asHBlockInstance(c_block))
			if (HBlockInstance ninst_2 = asHBlockInstance(c_block1)) {
				if (ninst_1->baseKind != nullptr && ninst_1->baseKind != ninst_1->baseKind) {
					if (ninst_1 == ninst_2) return QEquals;
				}

			}
	}

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		break;
        if (HBlockAssertion_is qdef = asHBlockAssertion_is(*it)) {
            if (query_is_same(c_block, qdef->get_obj(), localsEntry, stk) == QEquals) {
                auto r = query_is(qdef->get_definition(), c_block1,localsEntry, stk);
                if (r != QUndefined) {
                    return r;
                }

            }
        }
    }

	 
	 

 
    return QUndefined;

}


QueryResul CBlockInterpreter::query(HBlockAssertion_is q,
                                    HBlockAssertion_is base, HRunLocalScope localsEntry , QueryStack stk) //Compara as duas queries e retorna true se base valida q
{
    if (query_is(q->get_obj(), base->get_obj(), localsEntry, stk) &&
        query_is(q->get_definition(), base->get_definition(), localsEntry ,stk)) {
        return QEquals;
    }
    return QUndefined;

}


QueryResul  CBlockInterpreter::Selector_all(HBlock aList, HRunLocalScope localsEntry, std::function< QueryResul(HBlock) > selector )
{
    std::list<HBlock> hlist = resolve_as_list(aList, localsEntry);
    if (hlist.empty()) return QUndefined;
    for(HBlock &e : hlist)
    {
        if (selector(e) != QEquals)
        {
            logError("fail on |");
            e->dump("  ");
            return  QNotEquals;
        }
    }
    return QEquals;
}


QueryResul  CBlockInterpreter::Selector_any(HBlock aList, HRunLocalScope localsEntry, std::function< QueryResul(HBlock) > selector )
{
    std::list<HBlock> hlist = resolve_as_list(aList, localsEntry);
    if (hlist.empty()) return QUndefined;
    for (HBlock &e : hlist)
    {
        if (selector(e) == QEquals) return QEquals;		
    }
    return QNotEquals;
}



QueryResul CBlockInterpreter::get_system_verbs(string cs, HBlock n1, HBlock n2, HRunLocalScope localsEntry,QueryStack stk)
{
    

    //Resolve List OR
    if (HBlockList_OR  orList = asHBlockList_OR(n2))
    {
        for (auto &item : orList->lista)
        {
            if (get_system_verbs(cs,n1, item, localsEntry, stk) == QEquals) return QEquals;
        }
    }

    //Resolve List ALL
    if (HBlockSelector_All  selector_all = asHBlockSelector_All(n1))
    {
        return Selector_all( selector_all->what , localsEntry,[&](HBlock e1 )
        {
            return get_system_verbs(cs, e1, n2,localsEntry, stk);

        });
    }


    //Resolve List ANY
    if (HBlockSelector_Any  selector_any = asHBlockSelector_Any(n1))
    {
        return Selector_any(selector_any->what, localsEntry, [&](HBlock e1)
        {
            return get_system_verbs(cs, e1, n2,localsEntry, stk);

        });
    }


    logMessage("try verb|" + cs + "|");
    if (cs =="listed in")
    {
        return queryVerb_ListedIn(n1, n2,localsEntry, stk);
    }
    return QUndefined;
}

 

QueryResul CBlockInterpreter::query_verb(HBlockIsVerb is_verb, HRunLocalScope localsEntry ,QueryStack stk)
{
    QueryResul rrcstm =  get_system_verbs(is_verb->verb, is_verb->n1, is_verb->n2, localsEntry, stk); // "listed in" , "size of"
    if (rrcstm != QUndefined) return rrcstm;



    QueryResul rr =  query_user_verbs(is_verb->verb, is_verb->n1, is_verb->n2,localsEntry, stk);
    return rr; 
}

QueryResul CBlockInterpreter::query_not_verb(HBlockIsNotVerb is_verb, HRunLocalScope localsEntry , QueryStack stk)
{
    QueryResul rrcstm = get_system_verbs(is_verb->verb, is_verb->n1, is_verb->n2, localsEntry, stk); // "listed in" , "size of"
    if (rrcstm == QEquals) return QNotEquals;
    if (rrcstm == QNotEquals) return QEquals;


    QueryResul rr = query_user_verbs(is_verb->verb, is_verb->n1, is_verb->n2, localsEntry, stk);
    if (rr == QEquals) return QNotEquals;
    if (rr == QNotEquals) return QEquals;
    return rr;
}



QueryResul CBlockInterpreter::query_decides(HBlock q, HRunLocalScope localsEntry, QueryStack stk)
{
	for (auto dctIF : decides_if)
	{
		QueryResul dctValueWrap_1 = getDecidedIf(q, dctIF, localsEntry, stk);
		if (dctValueWrap_1 != QUndefined)
		{
			return  dctValueWrap_1;
		}
	}


    for (HBlockToDecideWhat &e : decides_what)
    {
      CResultMatch  reMatch = Match(e->queryToMatch, q, localsEntry, stk);
      if (reMatch.hasMatch )
      {
 
		  auto localsHeaderC = std::make_shared< CRunLocalScope >(reMatch.maptch);
		  HRunLocalScope localsNext = newScope(localsEntry, localsHeaderC);

		  auto rr = query(e->decideBody, localsNext, stk);
		  if (rr == QEquals) return QEquals;

          return QNotEquals;
          //return   e->decideBody;
      }

    }

 

    return QUndefined;

}



 

QueryResul CBlockInterpreter::query(HBlock q, HRunLocalScope localsEntry ,QueryStack stk  )
{
 

  /*  
    for (auto dctIF : decides_if)
    {
        QueryResul dctValueWrap_1 = getDecidedIf(q, dctIF, localsEntry, stk);
        if (dctValueWrap_1 !=  QUndefined) 
        {
            return  dctValueWrap_1;
        }
    }*/

	 


    if (HBlockIsNotVerb is_nverb = asHBlockIsNotVerb(q))
    {
		auto retv = query_not_verb(is_nverb, localsEntry , stk);
		if (retv != QUndefined) return retv;
    }

    if (HBlockIsVerb is_verb = asHBlockIsVerb(q) )
    {
       auto retv = query_verb(is_verb, localsEntry , stk);
	   if (retv != QUndefined) return retv;

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
			auto ret =  query_is(vr1,vr2, localsEntry, stk);
			if (ret != QUndefined) return ret;

			 
			
			/*if (q_dir_assign->isSame(q_dir_assign->get_obj().get(), q_dir_assign->get_definition().get()))
			{
				return QEquals;
			}
			return query_is(q_dir_assign->get_obj(), q_dir_assign->get_definition(), localsEntry, stk);*/
		}
    

		if ( HBlockAssertion_isNotDirectAssign q_not_dir = asHBlockAssertion_isNotDirectAssign(q))
		{
			if (q_not_dir->isSame(q_not_dir->get_obj().get(), q_not_dir->get_definition().get()))
			{
				return QNotEquals;
			}

			auto rr =  query_is(q_not_dir->get_obj(), q_not_dir->get_definition(), localsEntry, stk);
			if (rr == QEquals) return QNotEquals;
			if (rr == QNotEquals) return QEquals;
		 
		}



		 


	//Booleans
	if (HBlockBooleanAND q_bool_and = asHBlockBooleanAND(q))
	{
		auto result_A = query(q_bool_and->input_A, localsEntry, stk);
		if (result_A == QNotEquals) return  QNotEquals;
		if (result_A == QUndefined) return  QNotEquals;
		auto result_B = query(q_bool_and->input_B, localsEntry, stk);		 
		if (result_B == QNotEquals) return  QNotEquals;
		if (result_B == QUndefined) return  QNotEquals;
		return QEquals;
	}
	if (HBlockBooleanNOT q_bool_not = asHBlockBooleanNOT (q))
	{
		auto result_A = query(q_bool_not->input_A, localsEntry, stk);
		if (result_A == QNotEquals) return  QEquals;
		if (result_A == QEquals) return  QNotEquals;
		return result_A;
	}

	for (auto dctIF : decides_if)
	{
		QueryResul dctValueWrap_1 = getDecidedIf(q, dctIF, localsEntry, stk);
		if (dctValueWrap_1 != QUndefined)
		{
			return  dctValueWrap_1;
		}
	}

	if (HBlockComandList q_cmd = asHBlockComandList(q))
	{
		logError("cannot query a Command list ");
		assert(false);
	}
    return QUndefined;

}

QueryResul CBlockInterpreter::query(HBlock q)
{
    return query(q, nullptr,  QueryStack()); 
}


 


HTerm CBlockInterpreter::executeAssertion_is(HBlockAssertion_is b) {

    // is what ??

    if (HBlockNamedValue is_namedValue = asHBlockNamedValue(b->get_obj())) {


    }

    if (HBlockAssertion_canBe noum_canBe = asHBlockAssertion_canBe(b->get_definition())) {

    }

    if (HBlockKind is_define_kind = asHBlockKind(b->get_definition())) {

    }
    return nullptr;

}


HTerm CBlockInterpreter::executeAssertion(HBlockAssertionBase b) {

    if (HBlockAssertion_isInstanceOf inst = asHBlockAssertion_isInstanceOf(b)) {
        instancias.push_back(inst->noum);
    }

    //assertions.push_back(b);
    return nullptr;
}

HTerm CBlockInterpreter::execute(HBlock b) {
    assert(b != nullptr);

    if (asHBlockAssertion_is(b) != nullptr)
        return executeAssertion(asHBlockAssertion_is(b));

    return nullptr;
}


