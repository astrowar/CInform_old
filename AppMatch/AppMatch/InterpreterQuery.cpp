

#include "BlockInterpreter.h"
#include <iostream>
#include "CBlockInterpreterRuntime.h"
#include "CblockAssertion.h"
#include "QueryStack.h"

using namespace std;




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

QueryResul CBlockInterpreter::query_is_same(HBlock c_block, HBlock c_block1) {
    string name1 = BlockNoum(c_block);
    string name2 = BlockNoum(c_block1);
    if (name1 == "" || name2 == "") return QUndefined;
    //std::cout << name1 << "  " << name2 << std::endl;
    if (name1 == name2) {
        return QEquals;
    }
    return QNotEquals;
}

QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1) {
    if (HBlockNoum nnoum = dynamic_pointer_cast<CBlockNoum>(c_block1)) {
        HBlock resolved = resolve_noum(nnoum);
        if (resolved) {
            return query_is(c_block, resolved, QueryStack());
        }
        // pode ser um atributo
        return query_is(c_block, nnoum, QueryStack());
    }

	 


    return query_is(c_block, c_block1, QueryStack());
}

QueryResul CBlockInterpreter::query_is_instance_valueSet(HBlock c_block, HBlock c_block1) {

	

    if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(c_block))
        if (HBlockNoum value = dynamic_pointer_cast<CBlockNoum>(c_block1)) {
            if (cinst->has_slot(value)) {
                cout << cinst->named << "  " << value->named << endl;
                if (cinst->is_set(value)) {
                    return QEquals;
                }
                return QNotEquals;
            }
        }
    return QUndefined;

}

QueryResul
CBlockInterpreter::query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, QueryStack stk) {
    if (HBlockInstance cinst = dynamic_pointer_cast<CBlockInstance>(propObj)) {
        if (HBlockNoum property_noum = dynamic_pointer_cast<CBlockNoum>(propname)) {
            HVariableNamed pvar = cinst->get_property(property_noum->named);
            if (pvar != nullptr) {
                cout << "property  is " << endl;
				if (pvar->value != nullptr)
				{
					pvar->value->dump("  ");
				}
				else
				{
					cout << "     EMPTY" << endl;
				}

                c_block1->dump("  ");
                auto rprop = query_is(pvar->value, c_block1, stk);
                if (rprop == QEquals) return QEquals;
                return QNotEquals;
            }
        }
    }
    return QUndefined;
}


QueryResul CBlockInterpreter::query_is_propertyOf_value(HBlock c_block, HBlock c_block1, QueryStack stk) {
    if (HBlockProperty cproperty = dynamic_pointer_cast<CBlockProperty>(c_block)) {
        if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(cproperty->obj)) {
            auto resolved = resolve_noum(cnn);
            if (resolved != nullptr) {
                return query_is_propertyOf_value_imp(cproperty->prop, resolved, c_block1, stk);
            }
            return QUndefined;

        }
        // property of What ??
        return query_is_propertyOf_value_imp(cproperty->prop, cproperty->obj, c_block1, stk); 
    }
    return QUndefined;

}


QueryResul CBlockInterpreter::query_is_Variable_value(HBlock c_block, HBlock c_block1, QueryStack stk)
{

	if (HBlockNoum cnn = dynamic_pointer_cast<CBlockNoum>(c_block ))
	{
		auto var_1 = resolve_noum_as_variable(cnn);
		if (var_1 !=nullptr)
		{
			return query_is_Variable_value(var_1, c_block1, stk);
		}
	}

	if (HVariableNamed nvar1 = dynamic_pointer_cast<CVariableNamed>(c_block))
	{
		if (nvar1->value == nullptr) return QUndefined;
		if (HVariableNamed nvar2 = dynamic_pointer_cast<CVariableNamed>(c_block1))
		{
			if (nvar2->value == nullptr) return QUndefined;
			if (nvar1 == nvar2) return QEquals; //same reference			 
			return query_is(nvar1->value, nvar2->value, stk);
		}
		return query_is(nvar1->value, c_block1, stk);		
	}

	if (HVariableNamed nvar2 = dynamic_pointer_cast<CVariableNamed>(c_block1))
	{
		if (nvar2->value == nullptr) return QUndefined;		 
		return query_is(c_block , nvar2->value, stk);
	}

	return QUndefined;
}

QueryResul CBlockInterpreter::query_is(HBlock c_block, HBlock c_block1, QueryStack stk) {
    if (stk.isQuery(c_block, c_block1)) return QUndefined;
    stk.addQuery(c_block, c_block1);

    {
        if (HBlockInstance ninst_1 = dynamic_pointer_cast<CBlockInstance>(c_block))
            if (HBlockInstance ninst_2 = dynamic_pointer_cast<CBlockInstance>(c_block1)) {
                if (ninst_1->baseKind != nullptr && ninst_1->baseKind != ninst_1->baseKind) {
                    if (ninst_1 == ninst_2) return QEquals;
                }

            }
    }

    for (auto dct : decides_what) {
        auto dctValueWrap = getDecidedValueOf(c_block, dct);
        if (dctValueWrap != nullptr) {
            return query_is(dctValueWrap, c_block1, stk); //is not opnional
        }
    }

    for (auto dct : decides_what) {
        auto dctValueWrap_1 = getDecidedValueOf(c_block1, dct);
        if (dctValueWrap_1 != nullptr) {
            return query_is(c_block, dctValueWrap_1, stk);  //is not opnional
        }
    }



    //is scond a kind of anything ??
    if (HBlockKind bkind = dynamic_pointer_cast<CBlockKind>(c_block1)) {
        if (HBlockKind akind = dynamic_pointer_cast<CBlockKind>(c_block)) {
            bool b = is_derivadeOf(akind, bkind);
            if (b) return QEquals;
        } else if (HBlockInstance aInstance = dynamic_pointer_cast<CBlockInstance>(c_block)) {
            bool b = is_derivadeOf(aInstance, bkind);
            if (b) return QEquals;
        }
    }

    for (auto it = assertions_functional.begin(); it != assertions_functional.end(); ++it) {
        if (HBlockToDecide tdef = dynamic_pointer_cast<CBlockToDecide>(*it)) {

        }
    }


    {
		QueryResul qprop = query_is_Variable_value(c_block, c_block1, stk);  // Verifica as variaveis globais
		if (qprop != QUndefined) {
			return qprop;
		}
    }

    {
        QueryResul rinst = (query_is_instance_valueSet(c_block, c_block1));
        if (rinst != QUndefined) {
            return rinst;
        }

        QueryResul qprop = query_is_propertyOf_value(c_block, c_block1, stk);
        if (qprop != QUndefined) {
            return qprop;
        }
    }

    auto r2 = query_is_same(c_block, c_block1);
    if (r2 == QEquals) {
        return r2;
    }

    for (auto it = assertions.begin(); it != assertions.end(); ++it) {
        if (HBlockAssertion_is qdef = dynamic_pointer_cast<CBlockAssertion_is>(*it)) {
            if (query_is_same(c_block, qdef->get_obj()) == QEquals) {
                auto r = query_is(qdef->get_definition(), c_block1, stk);
                if (r != QUndefined) {
                    return r;
                }

            }
        }
    }
    return QUndefined;

}


QueryResul CBlockInterpreter::query(HBlockAssertion_is q,
                                    HBlockAssertion_is base) //Compara as duas queries e retorna true se base valida q
{
    if (query_is(q->get_obj(), base->get_obj()) &&
        query_is(q->get_definition(), base->get_definition())) {
        return QEquals;
    }
    return QUndefined;

}

QueryResul CBlockInterpreter::query_verb(HBlockIsVerb is_verb)
{
	QueryResul rr =  getVerb(is_verb->verb, is_verb->n1, is_verb->n2);
	return rr; 
}

QueryResul CBlockInterpreter::query_not_verb(HBlockIsNotVerb is_verb)
{
	QueryResul rr = getVerb(is_verb->verb, is_verb->n1, is_verb->n2);
	if (rr == QEquals) return QNotEquals;
	if (rr == QNotEquals) return QEquals;
	return rr;
}

QueryResul CBlockInterpreter::query(HBlock q)
{

	if (HBlockIsNotVerb is_nverb = dynamic_pointer_cast<CBlockIsNotVerb>(q))
	{
		return  query_not_verb(is_nverb);
	}

	if (HBlockIsVerb is_verb = dynamic_pointer_cast<CBlockIsVerb>(q) )
	{
	return 	query_verb(is_verb);

	}
	if (HBlockAssertion_is q_assign = dynamic_pointer_cast<CBlockAssertion_is>(q))
	{
		return query_is(q_assign->get_obj(), q_assign->get_definition());
	}
    return QUndefined;

}

 



HTerm CBlockInterpreter::executeAssertion_is(HBlockAssertion_is b) {

    // is what ??

    if (HBlockNamedValue is_namedValue = dynamic_pointer_cast<CBlockNamedValue>(b->get_obj())) {


    }

    if (HBlockAssertion_canBe noum_canBe = dynamic_pointer_cast<CBlockAssertion_canBe>(b->get_definition())) {

    }

    if (HBlockKind is_define_kind = dynamic_pointer_cast<CBlockKind>(b->get_definition())) {

    }
    return nullptr;

}


HTerm CBlockInterpreter::executeAssertion(HBlockAssertionBase b) {

    if (HBlockAssertion_isInstanceOf inst = dynamic_pointer_cast<CBlockAssertion_isInstanceOf>(b)) {
        instancias.push_back(inst->noum);
    }

    //assertions.push_back(b);
    return nullptr;
}

HTerm CBlockInterpreter::execute(HBlock b) {
    if (b == nullptr) {
        throw "parse error";
    }

    if (dynamic_pointer_cast<CBlockAssertionBase>(b) != nullptr)
        return executeAssertion(dynamic_pointer_cast<CBlockAssertionBase>(b));

    return nullptr;
}


