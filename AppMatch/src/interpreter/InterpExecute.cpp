// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


//Executor de acoes 


#include "CResultMatch.hpp"
#include "CBlockScope.hpp"
#include "interpreter/QueryStack.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"
#include <memory>

using namespace std;
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
 


std::list<HBlock> CBlockInterpreter::getMatchedObjects(HBlock seletor, HRunLocalScope localsEntry)
{
   // matched objects is valid only for some things	
	if (HBlockNoum nbase = asHBlockNoum(seletor)) 
	{
		HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj == nullptr) return std::list<HBlock>();
		return getMatchedObjects(nobj, localsEntry);
	}
	if (HBlockInstance nInst = asHBlockInstance(seletor))
	{
		return  {nInst};
	}

	if (HBlockKind  nKind = asHBlockKind(seletor))
	{
		auto ret = std::list<HBlock>();
		for(auto &r : assertions)
		{
			if (HBlockAssertion_isInstanceOf inst2 = asHBlockAssertion_isInstanceOf(r))
			{	 

				if (is_derivadeOf(inst2->noum, nKind, localsEntry))
				{
					ret.push_back(inst2->noum);
				}
			}
		}
		return ret;
	}

	return std::list<HBlock>();
}

bool  CBlockInterpreter::is_valid_for_relation_kind(HBlock baseType, HBlock object, HRunLocalScope localsEntry, QueryStack *stk)
{
	  
	auto r = query_is(std::move(object), baseType, localsEntry, stk);
	return r.result == QueryResul::QEquals;
}

PhaseResult CBlockInterpreter::execute_verb_set_inn(HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStack *stk)
{

	// Eh uma relacao ??
	for (auto & rv : verbRelationAssoc)
	{
		if (rv.first == vverb->verb)
		{
			auto relation_name = rv.second->relationNoum->named();
			if (relation_name == "dynamic")
			{
				logError(" dynamic relations is READ ONLY ");
				return false;
			}
			auto rel_find = this->staticRelation.find(relation_name);
			if (rel_find != this->staticRelation.end())
			{
				if (rv.second->type() == BlockVerbDirectRelation)
				{
					HBlockRelationBase rel = rel_find->second;
					if (is_valid_for_relation_kind(rel->input_A->kind, vverb->n1, localsEntry, stk) && is_valid_for_relation_kind(rel->input_B->kind, vverb->n2, localsEntry, stk))
					{
						return this->set_relation(rel, vverb->n1, vverb->n2, localsEntry, stk);
					} 
					else
					{
						return 	raise_runtime_error("relation type is Wrong ");
					}
				}
				else if (rv.second->type() == BlockVerbReverseRelation)
				{
					HBlockRelationBase rel = rel_find->second;					 
					if (is_valid_for_relation_kind(rel->input_B->kind, vverb->n1, localsEntry, stk) && is_valid_for_relation_kind(rel->input_A->kind, vverb->n2, localsEntry, stk))
					{
						return this->set_relation(rel, vverb->n2, vverb->n1, localsEntry, stk); // inverte a relacao					
					}
					else
					{
						return raise_runtime_error("relation type is Wrong ");
					}
				}
			}
			else
			{
				//verbis not set to an relation
				logError("verb "+ vverb->verb + " not set to an relation");
			}
		}

	}
	return PhaseResult(false);
}

PhaseResult CBlockInterpreter::execute_verb_set(HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStack *stk)
{
	auto n1 = exec_eval(vverb->n1, localsEntry, stk);
	auto n2 = exec_eval(vverb->n2, localsEntry, stk);
	HBlockIsVerb v_adv = std::make_shared<CBlockIsVerb>(vverb->verb , n1 , n2  );
	return execute_verb_set_inn(v_adv, localsEntry, stk);
}


PhaseResult CBlockInterpreter::execute_verb_unset(HBlockIsNotVerb vverb, HRunLocalScope localsEntry, QueryStack *stk)
{

	// Eh uma relacao ??
	for (auto & rv : verbRelationAssoc)
	{
		if (rv.first == vverb->verb)
		{
			auto relation_name = rv.second->relationNoum->named();
			if (relation_name == "dynamic")
			{
				logError(" dynamic relations is READ ONLY ");
				return false;
			}
			auto rel_find = this->staticRelation.find(relation_name);
			if (rel_find != this->staticRelation.end())
			{
				if (rv.second->type() == BlockVerbDirectRelation)
				{
					HBlockRelationBase rel = rel_find->second;
					this->unset_relation(rel, vverb->n1, vverb->n2, localsEntry,stk);
					return true;
				}
				else if (rv.second->type() == BlockVerbReverseRelation)
				{
					HBlockRelationBase rel = rel_find->second;
					this->unset_relation(rel, vverb->n2, vverb->n1, localsEntry,stk); // inverte a relacao
					return true;
				}
			}
		}

	}
	return false;
}

PhaseResult CBlockInterpreter::execute_unset(HBlock obj, HBlock value, HRunLocalScope localsEntry)
{

	if (HBlockNoum nobj = asHBlockNoum(obj)) 
	{
		HBlock vobj = resolve_noum(nobj, localsEntry);
		if (CBlock::isSame(vobj.get(), obj.get()))
		{
			return false;
		}
		return execute_unset(vobj, value, localsEntry);
	}

	if (HBlockEvery nevery = asHBlockEvery(obj))
	{
		std::list<HBlock> matchedObjects = getMatchedObjects(nevery->assertation, localsEntry);

		for (const auto &r : matchedObjects)
		{
			execute_unset(r, value, localsEntry);
		}
		return true;

	}
	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		if (HBlockNoum nbase = asHBlockNoum(value)) {
			HBlock nobj = resolve_noum(nbase, localsEntry);
			if (nobj == nullptr)
			{
				nInst->unset(nbase);
				return true;
			}
		}
	}


	if (HBlockProperty prop_n = asHBlockProperty(obj)) {
		//HBlock propNamed = prop_n->prop;
		//HBlock destination = prop_n->obj;
		//return assert_it_property(propNamed, destination, value, localsEntry);
		logError("Unable to Unset a property");
	}

	return false;
}




PhaseResult CBlockInterpreter::execute_set_direct_valueInstance(HBlockInstance obj, HBlockInstanceNamed value, HRunLocalScope localsEntry)
{
	
	//tem alguma propriedade cujo name eh igual ao tipo ?
	for (auto &va : obj->namedSlots)
	{
	 
		{
			//if (va_kindnamed->named == va->name->named)
			{

				if (HBlockKindValue kindv = asHBlockKindValue(va->kind))
				{
					if (kindv->named == va->name->named())
					{
						if (is_InstanceOf(value, va->kind))
						{
							// pode ser  assigned ...					 
								{
									va->value = value;
									return true;
								}
						}
					}
				}
			}
		}
	}


	return false;
}

PhaseResult CBlockInterpreter::execute_set_inn(HBlock obj, HBlock value, HRunLocalScope localsEntry)
{

 

	if (HBlockEvery nevery = asHBlockEvery(obj))
	{ 
		std::list<HBlock> matchedObjects = getMatchedObjects(nevery->assertation, localsEntry);
		for (const auto &r : matchedObjects)
		{
			execute_set(r, value, localsEntry);
		}
		return true;

	}


	// value tem que ser uma instancia, propriedade ou variavel

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		if (HBlockNoum nvalue = asHBlockNoum(value)) 
		{
		       return  nInst->set(nvalue);
			 
		}
		if (HBlockInstanceNamed ivalue = asHBlockInstanceNamed(value))
		{
			//eh instancia de um kindValue ??  apple is red por exemplo, sendo red um Kind of value 
			//nInst->set(invalue);
			PhaseResult  p = execute_set_direct_valueInstance(nInst, ivalue, localsEntry);
			if (p.hasExecuted)return true;
			return true;
		}

	}

	if (HBlockProperty prop_n = asHBlockProperty(obj)) {
		HBlock propNamed = prop_n->prop;
		HBlock destination = prop_n->obj;
		 
		return assert_it_property(propNamed, destination, value, localsEntry, nullptr);
	}

 



	/*if (HBlockProperty prop_n = asHBlockProperty(value)) {
		HBlock propNamed = prop_n->prop;
		HBlock destination = prop_n->obj;
		return assert_it_property(propNamed, destination, obj, localsEntry);
	}*/

	//
	if (HBlockVariableNamed  var_n = asHBlockVariableNamed(obj)) {

		HBlock destination = var_n->value;
		if (value_can_be_assign_to(value, var_n->kind, localsEntry))
		{
			if (HBlockList   val_list = asHBlockList(value))
			{
				//list is passed as copy
				HBlockList lcopy = make_shared<CBlockList>(std::list<HBlock>());
				lcopy->lista = val_list->lista;
				var_n->value = lcopy;

			}
			else {
				var_n->value = value;
			}
			return true;
		}
		else
		{
			return false;
		}

	}


	return false;
}


PhaseResult CBlockInterpreter::execute_set(HBlock obj, HBlock value, HRunLocalScope localsEntry)
{

	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		HBlock nobj = has_resolve_noum(nbase, localsEntry);
		if (nobj != nullptr && (CBlock::isSame(obj.get(),nobj.get())==false)) 
		{
			return execute_set(nobj, value, localsEntry);
		}
	}

	if (HBlockNoum nvalue = asHBlockNoum(value)) {
		HBlock vvalue = has_resolve_noum(nvalue, localsEntry);
		if (vvalue != nullptr && (CBlock::isSame(value.get(), vvalue.get()) == false))
		{
			return execute_set(obj, vvalue, localsEntry);
		}
	}
	return execute_set_inn(obj, value, localsEntry);

}

HBlock CBlockInterpreter::exec_eval_property_value_imp(HBlock propname, HBlock propObj )
{
	if (HBlockInstance cinst = asHBlockInstance( (propObj)))
	{
		if (HBlockNoum property_noum = asHBlockNoum( (propname)))
		{
			HBlockVariableNamed pvar = cinst->get_property(property_noum->named());
			if (pvar != nullptr) 
			{ 
				if (pvar->value != nullptr)
				{
					return pvar->value;
				} 
			}
		}
	}
	return nullptr;
}

HBlock CBlockInterpreter::exec_eval_property_value(HBlock c_block, HRunLocalScope localsEntry) {
	if (HBlockProperty cproperty = asHBlockProperty(c_block))
	{
		if (HBlockNoum cnn = asHBlockNoum(cproperty->obj))
		{
			auto resolved = has_resolve_noum(cnn,localsEntry);
			if (resolved != nullptr) {
				return exec_eval_property_value_imp(cproperty->prop, resolved );
			}			 

		}
		
	
		return exec_eval_property_value_imp(cproperty->prop, cproperty->obj );
	}
	return nullptr;

}



HBlock  CBlockInterpreter::exec_eval_assertations(HBlock c_block ,  HRunLocalScope localsEntry, std::function< HBlock(HBlock) > is_accetable )
{
	// is_accetable recebe um block, terona true se pode parar de descer na arvore
	
	QueryStack *stk = nullptr;

	

	for (auto &assertion : assertions) {
		if (HBlockAssertion_is qdef = asHBlockAssertion_is(assertion))
		{
			auto qcc = query_is_same(c_block, qdef->get_obj(), localsEntry, stk);
			if (qcc.result == QEquals) 
			{				
			HBlock br = (is_accetable(qdef->get_definition()));
			if (br !=nullptr)
			  {
				  return br ;
			  }
			}
		}
	}


	HBlock qprop_value = exec_eval_property_value(c_block ,localsEntry);
	HBlock qbr = is_accetable(qprop_value);
	if (qbr != nullptr)
	{
		return qbr;
	}

	return nullptr;
}


HBlock CBlockInterpreter::get_default_property_value(HBlockNoum c_value, HBlockInstance c_obj, HRunLocalScope localsEntry, QueryStack *stk)
{

	c_value->dump("");
	//c_obj->dump("");

	c_obj->baseKind->dump("");

	for (auto sii = default_assignments.rbegin(); sii!= default_assignments.rend();++sii)
	{
		HBlockAssertion_isDefaultAssign s = *sii;

		

		if (auto sp = asHBlockProperty(s->get_obj()))
		{
			if (CBlock::isSame(sp->prop.get(), c_value.get()))
			{
				if (query_is(c_obj, sp->obj, localsEntry,stk).result == QEquals)
				{
				 return  s->value;
				}
			}
		}
		s->dump("");

	}

	return nullptr;
}

HBlock CBlockInterpreter::exec_eval(HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk)
{
	 
	HBlock b =  exec_eval_internal(c_block, localsEntry, stk);

	//printf("_______________________________________\nEval\n");
	//localsEntry->dump("");
	//c_block->dump("");
	//printf("_______________________________________\n==Result\n");
	//if (b != nullptr) { b->dump(""); }
	//else { printf("nullPTR"); }
	return b;

}


bool CBlockInterpreter::assert_equals(HBlock c_block , HBlock c_result)
{
	auto a = exec_eval(std::move(c_block),nullptr,nullptr);
	auto b = exec_eval(std::move(c_result), nullptr, nullptr);

	auto res = query_is(a, b, nullptr, nullptr);
	if (res.result == QEquals) return true;


	return false;

}


HBlock CBlockInterpreter :: eval_boolean_AND(HBlock c1, HBlock c2)
{
	if (HBlockNoum ndecideValue = asHBlockNoum(c1))
	{
		if (ndecideValue->named() == "false") return std::make_shared<CBlockBooleanValue>(false);
		if (ndecideValue->named() == "nothing") return Nothing;
	}

	if (HBlockNoum ndecideValue = asHBlockNoum(c2))
	{
		if (ndecideValue->named() == "false") return std::make_shared<CBlockBooleanValue>(false);
		if (ndecideValue->named() == "nothing") return Nothing;
	}

	if (HBlockBooleanValue  ndecideValue = asHBlockBooleanValue(c1))
	{
		if (ndecideValue->state ==false) return std::make_shared<CBlockBooleanValue>(false);
	}

	if (HBlockBooleanValue  ndecideValue = asHBlockBooleanValue(c2))
	{
		if (ndecideValue->state == false) return std::make_shared<CBlockBooleanValue>(false);
	}

	return std::make_shared<CBlockBooleanValue>(true);
}

HBlock CBlockInterpreter :: eval_boolean_OR(HBlock c1, HBlock c2)
{
	if (HBlockNoum ndecideValue = asHBlockNoum(c1))
	{
		if (ndecideValue->named() == "true") return std::make_shared<CBlockBooleanValue>(true);
	}

	if (HBlockNoum ndecideValue = asHBlockNoum(c2))
	{
		if (ndecideValue->named() == "true") return std::make_shared<CBlockBooleanValue>(true);
	}

	if (HBlockBooleanValue  ndecideValue = asHBlockBooleanValue(c1))
	{
		if (ndecideValue->state == true) return std::make_shared<CBlockBooleanValue>(true);
	}

	if (HBlockBooleanValue  ndecideValue = asHBlockBooleanValue(c2))
	{
		if (ndecideValue->state == true) return std::make_shared<CBlockBooleanValue>(true);
	}

	return std::make_shared<CBlockBooleanValue>(false);
}

HBlock CBlockInterpreter::eval_boolean_NOT(HBlock c1)
{
	if (HBlockNoum ndecideValue = asHBlockNoum(c1))
	{
		if (ndecideValue->named() == "true") return std::make_shared<CBlockBooleanValue>(false);
		if (ndecideValue->named() == "false") return std::make_shared<CBlockBooleanValue>(true);
		if (ndecideValue->named() == "nothing") return Nothing;
	}

 

	if (HBlockBooleanValue  ndecideValue = asHBlockBooleanValue(c1))
	{
		if (ndecideValue->state == true) return std::make_shared<CBlockBooleanValue>(false);
		if (ndecideValue->state == false) return std::make_shared<CBlockBooleanValue>(true);
	}

	 

	return Nothing;
}


HBlock CBlockInterpreter::exec_eval_internal_boolean_relation(HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockBooleanAND nbool_and = asHBlockBooleanAND(c_block))
	{
		auto b1 = exec_eval(nbool_and->input_A , localsEntry, stk);
		auto b2 = exec_eval(nbool_and->input_B, localsEntry, stk);
		 

		b1->dump("");
		b2->dump("");
		return eval_boolean_AND(b1, b2);
	}

	if (HBlockBooleanOR nbool_or = asHBlockBooleanOR(c_block))
	{
		auto b1 = exec_eval(nbool_or->input_A, localsEntry, stk);
		auto b2 = exec_eval(nbool_or->input_B, localsEntry, stk);
		return eval_boolean_OR (b1, b2);
	}

	if (HBlockBooleanNOT nbool_not = asHBlockBooleanNOT(c_block))
	{
		auto b1 = exec_eval(nbool_not->input_A, localsEntry, stk);	 
		return   std::make_shared<CBlockBooleanValue>(true);
		return eval_boolean_NOT(b1);
	}

	return nullptr;
}


bool CBlockInterpreter::existe_relation_property(HBlockNoum property_noum, HBlock  obj )
{
	for (auto r : staticRelation)
	{
		auto rbase = r.second;
		if (rbase->input_A->named == property_noum->named())
		{
			if (is_InstanceOf(obj, rbase->input_B->kind ) )
			{
				return true;
			}
		}
		if (rbase->input_B->named == property_noum->named())
		{
			if (is_InstanceOf(obj, rbase->input_A->kind ))
			{
				return true;
			}
		}
	}
	return false;

}

HBlock CBlockInterpreter::eval_relation_property(HBlockNoum property_noum, HBlock  obj  ,  HRunLocalScope localsEntry, QueryStack *stk)
{

	bool existe_relation_prop = false;
	// procupara pela relacao que tem um called que eh compativel com o property_noum
	for (auto &rr : relInstances)
	{
		if (rr->relation->input_B->named == property_noum->named()) //Ok, this is 
		{
			auto res = query_is(obj, rr->value1, localsEntry, stk);
			if (res.result == QEquals)
			{
			
				return rr->value2;
			}
		}

		if (rr->relation->input_A->named == property_noum->named()) //Ok, this is 
		{
			auto res = query_is(obj, rr->value2, localsEntry, stk);
			
			if (res.result == QEquals)
			{
				return rr->value1;
			}
		}
	}

	return nullptr;
}
 
HBlock CBlockInterpreter::eval_property(HBlockProperty kprop, HRunLocalScope localsEntry, QueryStack *stk)
{
 
 
		{
			//check for plural
			if (HBlockNoum propNoum = asHBlockNoum(kprop->prop))
			{
				if (isSameString(propNoum->named(), "plural"))
				{
					string c = asBlockNoum(kprop->obj);
					if (!(c.empty()))
					{
						return  get_plural_of(c);
					}
				}
			}
		}

		auto instancia = exec_eval(kprop->obj, localsEntry, stk);
		if (is_nothing(instancia)) return Nothing;

		if (HBlockInstance objInst = asHBlockInstance(instancia))
			if (HBlockNoum propNoum = asHBlockNoum(kprop->prop))
			{

				//objInst->dump("P  ");

				HBlockVariableNamed pvar = objInst->get_property(propNoum->named());

				//pvar->dump("P  ");

				HBlock ret_val = Nothing;
				if (pvar != nullptr)
				{
					if (pvar->value != nullptr)
					{
						ret_val = pvar->value;
					}


					if (is_nothing(ret_val))
					{
						HBlock default_val = get_default_property_value(propNoum, objInst, localsEntry, stk);
						if (default_val != nullptr)
						{
							ret_val = default_val;
						}
					}

					return ret_val;
				}
			}
	 
 
		

		if (HBlockNoum propNoum = asHBlockNoum(kprop->prop))
		{
			if (existe_relation_property(propNoum, instancia))
			{

				HBlock  result_prop = eval_relation_property(propNoum, instancia, localsEntry, stk);
				if (result_prop != nullptr)
				{
					return result_prop;
				}
				return Nothing;
			}
		}
	return nullptr;

}



HBlock CBlockInterpreter::disptch_action_call(HBlockPhraseInvoke phr, HRunLocalScope localsEntry, QueryStack *stk_in)
{

	std::unique_ptr<QueryStack> stk_ptr = generateNextStack(stk_in);
	QueryStack* stk = stk_ptr.get();


	for (auto sph : system_phrases)
	{
		HRunLocalScope execute_scope = PhraseHeader_matchs(sph, phr, localsEntry, stk);
		if (execute_scope != nullptr)
		{
			return   Nothing;
		}
	}

 







 
	{
		//uma acao nao pode chamar ela mesma com os mesmo argumentos 
		for (auto ph : phrases)
		{
			if (CBlock::isSame(ph->header->verb.get(), phr->header->verb.get()) == false) continue;

			if (ph->header->pred1 == nullptr && phr->header->pred1 != nullptr) continue;
			if (ph->header->pred1 != nullptr && phr->header->pred1 == nullptr) continue;
			if (ph->header->pred1 != nullptr && phr->header->pred1 != nullptr)
			{
				if (ph->header->pred1->named() != phr->header->pred1->named()) continue;
			}


			if (ph->header->pred2 == nullptr && phr->header->pred2 != nullptr) continue;
			if (ph->header->pred2 != nullptr && phr->header->pred2 == nullptr) continue;
			if (ph->header->pred2 != nullptr && phr->header->pred2 != nullptr)
			{
				if (ph->header->pred2->named() != phr->header->pred2->named()) continue;
			}

 

 

			//dois argumentos
			if (ph->header->arg1 != nullptr && ph->header->arg2 != nullptr)
			{
				CResultMatch result_1 = this->Match(ph->header->arg1, phr->arg1, localsEntry, stk);
				if (result_1.hasMatch == false)
				{
					auto arg1 = resolve_argument(phr->arg1, localsEntry, stk);
					result_1 = this->Match(ph->header->arg1, arg1, localsEntry, stk);
				}
				if (result_1.hasMatch)
				{
					auto localstmp = std::make_shared< CRunLocalScope >(localsEntry, result_1.maptch);
					CResultMatch result_2 = this->Match(ph->header->arg2, phr->arg2, localsEntry, stk);

					if (result_2.hasMatch == false)
					{
						auto arg2 = resolve_argument(phr->arg2, localstmp, stk);
						result_2 = this->Match(ph->header->arg2, arg2, localsEntry, stk);
					}

					if (result_2.hasMatch)
					{
						auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result_1.maptch);
						localsNext = std::make_shared< CRunLocalScope >(localsNext, result_2.maptch);
						localsNext->dump("");
						return  exec_eval(ph->body, localsNext, stk);
					}
				}
			}
			//um argumento
			if (ph->header->arg1 != nullptr && ph->header->arg2 == nullptr)
			{
				HBlock arg1 = phr->arg1;
				HBlock arg2 = nullptr;
				CResultMatch result_1 = this->Match(ph->header->arg1, phr->arg1, localsEntry, stk);
				if (result_1.hasMatch == false)
				{
					arg1 = resolve_argument(phr->arg1, localsEntry, stk);
					result_1 = this->Match(ph->header->arg1, arg1, localsEntry, stk);
				}
				  

				if (result_1.hasMatch)
				{
					if (stk->contains_phase_execution(ph, arg1, arg2) == false)
					{
						stk->add_phase_execution(ph,  arg1,  arg2);
						printf("-------------------------------\n");
						ph->dump("");
						if ( arg1 != nullptr)  arg1->dump("");
				 
						printf("\n");



						auto localstmp = std::make_shared< CRunLocalScope >(localsEntry, result_1.maptch);
						auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result_1.maptch);
						//localsNext->dump("");
						//ph->body->dump("B ");
						//return  exec_eval(ph->body, localsNext, stk);
						auto q = execute_now(ph->body, localsNext, stk);
						if (q.hasExecuted)
						{
							return Nothing;
						}
					}

				}

			}

		}
		return nullptr;
	}
}
HBlock CBlockInterpreter::exec_eval_if_then(HBlockControlIF cIF, HRunLocalScope localsEntry, QueryStack *stk)
{
	HBlock ret = nullptr;

	if (HBlockAssertion_isDirectAssign  adirect = asHBlockAssertion_isDirectAssign(cIF->block_if))
	{

		if (HBlockMatch  mm = asHBlockMatch(adirect->get_definition()))
		{
			auto mres = Match(mm, adirect->get_obj(), localsEntry, stk);
			if (mres.hasMatch)
			{
				auto localstmp = std::make_shared< CRunLocalScope >(localsEntry, mres.maptch);
				auto r =  exec_eval(cIF->block_then, localstmp, stk);
				return r;
			}

		}
		

	}


	auto r = query(cIF->block_if, localsEntry, stk);
	if (r.result == QEquals)
	{
		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, r.matchedResult);

		auto result_then =  exec_eval(cIF->block_then, localsNext, stk);
		return result_then;
	}
	else
	{
		if (cIF->block_else != nullptr)
		{
			auto result_else =  exec_eval(cIF->block_else, localsEntry, stk);
			return result_else;
		}
		return nullptr;
	}
}

 
HBlock CBlockInterpreter::exec_eval_forEach(HBlockControlForEach cForE, HRunLocalScope localsEntry, QueryStack *stk)
{
	HBlock ret = nullptr;
	ListOfNamedValue  loopListEnummerator = getValuesFromMatch(cForE->block_variable, localsEntry, stk);
	{
		for (auto hii : loopListEnummerator)
		{

			const  std::map<string, CBlocking::HBlock> nextVarSet = { { hii.named , hii.value } };
			auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, nextVarSet);

			auto rloop_result = exec_eval(cForE->block_body, localsNext, stk);

			if (rloop_result == nullptr)
			{
				//printf("_______________________________________\n");
				//localsNext->dump("");
				//cForE->block_body->dump("");
				continue;
			}
			ret = rloop_result;
			if (HBlockToDecideOn ndecide = asHBlockToDecideOn(ret))
			{
				return ret;
			}
		}
		if (ret == nullptr)
		{
			//c_block->dump("");
			//cForE->block_variable->dump("");
			//logError("What ?");
		}
		return ret;
	}
}
HBlock CBlockInterpreter::exec_eval_internal(HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk )
{
	 

	if (c_block == nullptr)
	{
		return nullptr;
	}

	

	if (is_nothing(c_block)) return Nothing;

 
	{
		HBlock nbool = exec_eval_internal_boolean_relation(c_block, localsEntry, stk);
		if (nbool  != nullptr) return nbool;
	}


	if (HBlockComandList nlist = asHBlockComandList(c_block))
	{
		const  std::map<string, CBlocking::HBlock> nextVarSet ;
		auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, nextVarSet); // cria uma nova stack para as variaveis locais
		

		HBlock ret_out = nullptr;
		for (auto e : nlist->lista)
		{
			auto ret = exec_eval(e, localsNext,stk);
			if (ret != nullptr)
			{
				ret_out = ret;
				if (ret_out->type() == BlockToDecideOn)
				{
					return ret_out;
				}
				
			}
		}
		return  ret_out;
	}


	if (HBlockControlIF cIF = asHBlockControlIF(c_block))
	{
		return exec_eval_if_then(cIF, localsEntry, stk);
	}


	if (HBlockControlForEach cForE = asHBlockControlForEach(c_block))
	{
		return exec_eval_forEach(cForE, localsEntry, stk);
	}



	{
		if (HBlockAssertion_isDirectAssign nDirect = asHBlockAssertion_isDirectAssign(c_block))
		{
			QueryResultContext q = query(nDirect, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoumStr>("true");
			return std::make_shared<CBlockNoumStr>("false");
		}


		if (HBlockIsVerb  nVerbDirect = asHBlockIsVerb(c_block))
		{
			QueryResultContext q = query(nVerbDirect, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoumStr>("true");
			return std::make_shared<CBlockNoumStr>("false");
		}


		if (HBlockAssertion_isNotDirectAssign nDirectv = asHBlockAssertion_isNotDirectAssign(c_block))
		{
			QueryResultContext q = query(nDirectv, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoumStr>("true");
			return std::make_shared<CBlockNoumStr>("false");
		}


		if (HBlockIsNotVerb  nVerbDirectv = asHBlockIsNotVerb(c_block))
		{
			QueryResultContext q = query(nVerbDirectv, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoumStr>("true");
			return std::make_shared<CBlockNoumStr>("false");
		}
	}


	if (HBlockToDecideOn ndecide = asHBlockToDecideOn(c_block))
	{

		auto r = exec_eval(ndecide->decideBody, localsEntry, stk);
		return std::make_shared<CBlockToDecideOn>(r);
	}

	if (HBlockNoum nn = asHBlockNoum(c_block))
	{
		 
		auto  obj = has_resolve_noum(nn, localsEntry, std::list<std::string>());
		if (obj != nullptr)
		{
			return  exec_eval(obj, localsEntry, stk);
		}
	}

	if (HBlockBooleanValue nbool = asHBlockBooleanValue(c_block))
	{
		return nbool;
	}


	if (HBlockInstance nIns = asHBlockInstance(c_block))
	{
		return nIns;
	}

	if (HBlockActionInstance nAction = asHBlockActionInstance(c_block))
	{
		return   nAction ;
	}

	if (HBlockActionNamed nAction = asHBlockActionNamed(c_block))
	{
		return has_resolve_string_noum( nAction->named ,localsEntry ,{} );
	}


	if (HBlockKind kIns = asHBlockKind(c_block))
	{
		return kIns;
	}

	if (auto  kvar = asHBlockVariableNamed(c_block))
	{
		if (kvar->value == nullptr) return Nothing;
		return kvar->value;
	}


	if (auto  krel_args = asHBlockRelationArguments(c_block))
	{
		auto vr1 = exec_eval_internal(krel_args->value1, localsEntry, stk);
		auto vr2 = exec_eval_internal(krel_args->value2, localsEntry, stk);
		return std::make_shared<CBlockRelationArguments>(vr1,vr2);
	}

	if (auto  kprop = asHBlockProperty(c_block))
	{
		HBlock res = eval_property(kprop, localsEntry, stk);
		if (res != nullptr) return res;
	}

	if (HBlockNamedValue nvalue = asHBlockNamedValue(c_block))
	{
		return nvalue;
	}



	//resolve To decides
	for (const auto &dct : decides_what)
	{
		auto dctValueWrap = getDecidedValueOf(c_block, dct, nullptr,stk);
		if (dctValueWrap != nullptr)
		{
			return dctValueWrap;
		}
	}

	if (HBlockRelationLookup nrlookup = asHBlockRelationLookup(c_block))
	{
		return lookup_relation(nrlookup, localsEntry, stk);
	}
	if (HBlockVerbLookup nvlookup = asHBlockVerbLookup(c_block))
	{
		return lookup_verb(nvlookup, localsEntry, stk);
	}

	if (HBlockSelector_Where nrWhere = asHBlockSelector_Where(c_block))
	{
		if (HBlockRelationLookup nrlookup = asHBlockRelationLookup(nrWhere->what))
		{
			return lookup_relation(nrlookup, localsEntry,stk);
		}
		if (HBlockVerbLookup nvlookup = asHBlockVerbLookup(nrWhere->what))
		{
			return lookup_verb(nvlookup, localsEntry,stk);
		}
		if (HBlockSelectorAND nvlookup_and = asHBlockSelectorAND(nrWhere->what))
		{
		 
			auto auto_value1 = exec_eval(nvlookup_and->value1, localsEntry, stk);
			auto auto_value2 = exec_eval(nvlookup_and->value2, localsEntry, stk);
			return lookup_intersection(auto_value1, auto_value2, localsEntry, stk);
		} 
	}


	if (auto  kList = asHBlockList(c_block))
	{
		auto rList = std::make_shared<CBlockList>(std::list<HBlock>());
		for (auto &e : kList->lista)
		{
			rList->lista.push_back(exec_eval(e, localsEntry, stk));
		}
		return rList;
	}


	if (HBlockNow  bNow = asHBlockNow(c_block))
	{
		execute_now(bNow->assertation, localsEntry);
		return bNow->assertation->get_obj();
	}


	if (HBlockVerb nVerb = asHBlockVerb(c_block))
	{
		return nVerb;
	}

	if (HBlockVerbAdapt nVerbAdp = asHBlockVerbAdapt(c_block))
	{

		return adapt_verb(nVerbAdp, localsEntry);
		
	}

	if (HBlockVerbNegate nVerbNeg = asHBlockVerbNegate(c_block))
	{

	 return  adapt_negate_verb(nVerbNeg , localsEntry);

	}


	
	if (HBlockText ntext = asHBlockText(c_block))
	{
		return ntext;
	}

	if (HBlockTextSentence ntexts = asHBlockTextSentence(c_block))
	{
			return adapt_text(ntexts , localsEntry, stk );
	}


	if (asHBlockSimetricRelation(c_block) != nullptr) return c_block; //fundamental value
	if (asHBlockASimetricRelation(c_block) != nullptr) return c_block; //fundamental value
	


	if (HBlockAssertion_isLocalVariable  local_var = asHBlockAssertion_isLocalVariable(c_block))
	{		
		CBlocking::HBlock actual_value = exec_eval_internal(local_var->valueExpression, localsEntry, stk);		
		if (actual_value == nullptr)
		{
			actual_value = Nothing;
		}
		std::pair<string, CBlocking::HBlock> local_entry = { local_var->variableName->named() , actual_value };
		localsEntry->locals.push_back(local_entry);
		return nullptr;
	}




	//case has fail
	if (auto  kprop = asHBlockProperty(c_block))
	{
		if (is_nothing(kprop->obj)) return Nothing; //qualquer coisa de nothing eh nothing

		 auto obj = exec_eval(kprop->obj, localsEntry, stk);  //evaluate o objeto que deseja pegar a propriedade
		 if (obj == nullptr) return nullptr;
		 if (is_nothing(obj)) return Nothing;

		 if (obj->isSame(obj.get(), kprop->obj.get()) == false)  // se o objeto for o mesmo da entradas entao ele ja esta no estado mais fundamental
		 {
			 auto b = std::make_shared<CBlockProperty>(kprop->prop, obj);

			 if (HBlockNoum pNoum = asHBlockNoum(kprop->prop))
			 if (localsEntry != nullptr)
			 {
				 auto next_prop = localsEntry->resolve(pNoum->named());
				 if (next_prop != nullptr)
				 {
					 b->prop = next_prop;
				 }
			 }

			 //printf("------------------------------\n");
			 //b->dump("");
			 //kprop->obj->dump("");
			 auto pres =   exec_eval(b, localsEntry, stk);
			 return pres;
		 }
	}
	
 
	if (HBlockPhraseInvoke phr = asHBlockPhraseInvoke(c_block))
	{
		return disptch_action_call(phr, localsEntry, stk);
	 
	}

	for (auto cc : constant_assignments)
	{
		if (CBlock::isSame(cc->get_obj().get(), c_block.get()))
		{
			return cc->get_definition();
		}
	}

	if (auto t = asHBlockTryCall(c_block))
	{
		execute_now(t->sentence, localsEntry);
		return Nothing;
	}

	//if (localsEntry!=nullptr)localsEntry->dump("");	 
	// Bla ! 
	//c_block->dump("");
	//throw "Unhandle CBlock";

	if (auto nn = asHBlockNoum(c_block))
	{
		HBlock  lnoum = nullptr;
		if (localsEntry != nullptr )  lnoum = localsEntry->resolve(nn->named());
		auto xs = resolve_noum(nn, localsEntry);
		if (xs == nullptr)
		{
			if (lnoum != nullptr) return lnoum; 
		}
		else
		{
			return xs;
		}
	}

	return nullptr;
}


HBlock CBlockInterpreter::resolve_as_callCommand(HBlock p, HRunLocalScope localsEntry)
{
 

	//Execution block is not an action ??
	if (HBlockNoum noumCall = asHBlockNoum(p))
	{
		auto callAs = resolve_noum(noumCall, localsEntry);
		if (callAs != nullptr)
		{
			return  resolve_as_callCommand(callAs, localsEntry);
		}
	}

	if (HBlockActionNamed actionCalln = asHBlockActionNamed(p))
	{
		return actionCalln;
	}

	if (HBlockAction actionCall = asHBlockAction(p))
	{
		logError("Something worng here ");
		(p.get() + 1000)->dump(""); //causa um belo erro !

		return actionCall;
	}

	if (HBlockVariableNamed callAsVar = asHBlockVariableNamed(p))
	{
		auto actionCall_1 = callAsVar->value;
		return  resolve_as_callCommand(actionCall_1, localsEntry);
	}
	

	return nullptr;
}

HBlockExecution  CBlockInterpreter::create_dispach_env(HBlockList  p, HRunLocalScope localsEntry)
{
	QueryStack *stk = nullptr;
	for (auto &d : dynamic_understand)
	{
		auto result = (Match(d->input_n, p, localsEntry, stk));
		if (result.hasMatch)
		 {

			 d->output_n->dump("            ");


			 // Forma eh esta 
			 for(auto &arg : result.maptch)
			 {
				 
			 
			 }
			 HRunLocalScope localsNext = make_shared< CRunLocalScope >(nullptr);

			 HRunLocalScope locals_obj_1 = nullptr; //local que vem do argumento 1 
			 HRunLocalScope locals_obj_2 = nullptr; //locals que vem do argumento 2

			 
			 // Argumentos batem com os matchs dos argumentos ??
			 HBlock ref_Arg_1 = nullptr;
			 HBlock ref_Arg_2 = nullptr;

			 if (d->argument_n->matchList.size() > 0)
			 {
				 auto arg_header_first = d->argument_n->matchList.begin();
				 // eh um Match Named ???
				 if (HBlockMatchNamed arg1_named = asHBlockMatchNamed(*arg_header_first))
				 {
				 
					 			 
				     auto obj_resolved = exec_eval (result.maptch["noum1"], localsEntry, stk);

					 auto result_arg1 = Match(arg1_named->matchInner, obj_resolved,  localsEntry,stk);
					 if (result_arg1.hasMatch == true)
					 {
						 localsNext->locals.emplace_back(arg1_named->named, obj_resolved);
						 ref_Arg_1 = obj_resolved;
					 }
					 else
					 {
						 continue; //Este match nao serve .. Proximo
					 }
				 }
				 else //match noum ??
				 {
					 if (HBlockMatch  arg1_match_required =  *arg_header_first)
					 {
						 					  
						 auto obj_resolved = exec_eval(result.maptch["noum1"], localsEntry, stk);
						 auto result_arg1_requ = Match(arg1_match_required , obj_resolved, localsEntry, stk);						 
						 if (result_arg1_requ.hasMatch)
						 {
							 ref_Arg_1 = obj_resolved;
							 locals_obj_1 = std::make_shared< CRunLocalScope >( nullptr, result_arg1_requ.maptch);
							 locals_obj_1->locals.emplace_back("noum1" , obj_resolved);
						 }
						 else
						 {
							 continue; 
						 }
					 }
				 }



				 if (d->argument_n->matchList.size() > 1)
				 {
					 auto arg_header_second = std::next( arg_header_first);
					 // eh um Match Named ???
					 if (HBlockMatchNamed arg2_named = asHBlockMatchNamed(*arg_header_second))
					 {
						 

						 auto obj_resolved = exec_eval(result.maptch["noum2"], localsEntry, stk);
						 auto result_arg2 = Match(arg2_named->matchInner, obj_resolved, localsEntry , stk);
						 if (result_arg2.hasMatch == true)
						 {
							 localsNext->locals.emplace_back(arg2_named->named, obj_resolved);
							 ref_Arg_2 = obj_resolved;
						 }
						 else
						 {
							 continue; //Este match nao serve .. Proximo
						 }

						 
					 }
					 else //match noum ??
					 {
						 if (HBlockMatch  arg2_match_required = *arg_header_second)
						 {
							 arg2_match_required->dump(" ");
							 auto obj_resolved = exec_eval(result.maptch["noum2"], localsEntry, stk);
							 auto result_arg2_requ = Match(arg2_match_required, obj_resolved, localsEntry, stk);
							 if (result_arg2_requ.hasMatch)
							 {
								 ref_Arg_2 = obj_resolved;
								 locals_obj_2 = std::make_shared< CRunLocalScope >(nullptr, result_arg2_requ.maptch);
								 locals_obj_2->locals.emplace_back("noum2", obj_resolved);
							 }
							 else
							 {
								 continue;
							 }
						 }
					 }


				 }
			 }

			 
			 auto output_block =  resolve_as_callCommand(d->output_n, localsEntry); 


			 if (HBlockActionNamed actionCall = asHBlockActionNamed (output_block))
			 {
				
				 HRunLocalScope localsNextp = std::make_shared< CRunLocalScope >(localsEntry , result.maptch);
				  
				return  make_shared< CBlockExecution >(localsNextp, std::make_shared<CBlockActionCallNamed>(actionCall, ref_Arg_1 , ref_Arg_2));
			 } 

			 HBlockExecution executionBlock = make_shared< CBlockExecution >(localsNext, output_block);
			 return executionBlock;

		 }
	}

	return nullptr;
}

PhaseResult  CBlockInterpreter::execute_now(HBlock p) //executa STMT
{
	
	HRunLocalScope localsEntry = make_shared< CRunLocalScope >(nullptr);
	auto b =   execute_now(p, localsEntry);
	if (b.hasExecuted == false)
	{
		logWarring("fail to execute ");
		p->dump(">");
		logWarring("fail to execute ");
	 
	}
	return b;
}

PhaseResult CBlockInterpreter::execute_now(HBlock p, HRunLocalScope localsEntry) //executa STMT
{
	QueryStack *stk = nullptr;
	return execute_now(p, std::move(localsEntry), stk);
}
ListOfNamedValue Interpreter::CBlockInterpreter::getValuesFromMatch(CBlocking::HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockNoum nbase = asHBlockNoum(c_block))
	{
		HBlock nobj = resolve_noum(nbase, localsEntry );
		if (nobj == nullptr)
		{
			return ListOfNamedValue();
		}
		return getValuesFromMatch(nobj, localsEntry,stk);
	}


	if (HBlockMatchNoum nbase = asHBlockMatchNoum(c_block))
	{
		HBlock nobj = resolve_noum(nbase->inner, localsEntry);
		if (nobj == nullptr)
		{
			return ListOfNamedValue();
		}
		return getValuesFromMatch(nobj, localsEntry, stk);
	}

	if (HBlockMatchNamed  mnamed = asHBlockMatchNamed(c_block))
	{
		ListOfNamedValue mm = getValuesFromMatch(mnamed->matchInner, localsEntry, stk);
		 
		for (auto &v : mm)
		{
			v.named = mnamed->named;
		}
		return mm;
	}

	 

	if (HBlockKind  nKind = asHBlockKind(c_block))
	{
		ListOfNamedValue ret = ListOfNamedValue();
		for (auto &r : assertions)
		{
			if (HBlockAssertion_isInstanceOf inst2 = asHBlockAssertion_isInstanceOf(r))
			{
				if (is_derivadeOf(inst2->noum, nKind, localsEntry))
				{
					ret.push_back({ "", inst2->noum });
				}
			}
		}
		return ret;
	} 

	return ListOfNamedValue();
}

HBlockMatch CBlockInterpreter::resolve_argument_match(HBlock  value, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	if (HBlockMatchNamed rel_mn = DynamicCasting::asHBlockMatchNamed(value))
	{
		auto v1 = resolve_argument_match(rel_mn->matchInner, localsEntry, stk);		 
		return std::make_shared<CBlockMatchNamed>(rel_mn->named, v1);
	}

	if (HBlockMatchNoum nnoum  = DynamicCasting::asHBlockMatchNoum(value))
	{
		auto r = resolve_noum(nnoum->inner , localsEntry );
		if (r == nullptr) return nnoum;

		if (HBlockKind k = asHBlockKind( r) )
		{
			return std::make_shared<CBlockMatchKind>(k);
		}
		if (HBlockInstance rv = asHBlockInstance (r))
		{
			return std::make_shared<CBlockMatchValue>(rv);
		}

		r->dump("R");
		nnoum->inner->dump("inner  ");
		logError("What ?");
		
	}

	if (HBlockMatchList mlist = DynamicCasting::asHBlockMatchList(value))
	{
		std::list<HBlockMatch> mlist_next;
		for(auto m: mlist->matchList)
		{
			mlist_next.push_back(resolve_argument_match(m, localsEntry, stk));
		}
		return std::make_shared<CBlockMatchList>(mlist_next);

	}

	if (HBlockMatchKind k = DynamicCasting::asHBlockMatchKind(value))
	{
		auto inner = k->kind;
		auto kind_res = resolve_argument(k->kind, localsEntry, stk);

		if (HBlockKind kinn = asHBlockKind(kind_res))
		{
			return std::make_shared<CBlockMatchKind>(kinn);
		}
		 
		 
	}


	if (HBlockMatchAny aa = DynamicCasting::asHBlockMatchAny(value))
	{
		return aa;
	}

	value->dump("uR");
	 
 

	return nullptr;
}

HBlock CBlockInterpreter::resolve_argument(HBlock  value, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (value == nullptr)
	{
		return nullptr;
	}
	auto value_2 = value;
	
	if (HBlockMatchNoum mvalue_2 = DynamicCasting::asHBlockMatchNoum(value_2)) 
	{
		return resolve_argument_match(value_2, localsEntry, stk);
	}

	if (HBlockMatchText mvalue_2 = DynamicCasting::asHBlockMatchText(value_2))
	{
		return mvalue_2->inner;
	}
	
	if (HBlockProperty nnoum_p = DynamicCasting::asHBlockProperty(value))
	{
		HBlock resolved_obj = resolve_argument(nnoum_p->obj, localsEntry,stk);
		if (resolved_obj != nullptr)
		{
		   auto tmp = std::make_shared<CBlockProperty>(nnoum_p->prop, resolved_obj);
		   auto prop_value =  exec_eval_internal(tmp, localsEntry, stk);
		   if (prop_value != nullptr) return  prop_value;
		   return tmp;
		}
		 
	}


	if (HBlockNoum nnoum_2 = DynamicCasting::asHBlockNoum(value_2))
	{
		HBlock resolved = resolve_noum(nnoum_2, localsEntry);
		if (resolved != nullptr) return resolved;
		value_2->dump("");
		return nullptr;
	}
	
	if (HBlockRelationArguments rel_args = DynamicCasting::asHBlockRelationArguments (value_2))
	{
		auto v1 = resolve_argument(rel_args->value1, localsEntry, stk);
		auto v2 = resolve_argument(rel_args->value2, localsEntry, stk);
		return std::make_shared<CBlockRelationArguments>(v1, v2);
	}

	if (HBlockMatchNamed rel_mn = DynamicCasting::asHBlockMatchNamed(value_2))
	{
		auto v1 = resolve_argument_match(rel_mn->matchInner , localsEntry, stk);
		{
			return std::make_shared<CBlockMatchNamed>(rel_mn->named, v1);
		}
	}

	if (value_2 != nullptr)
	{
		return  exec_eval_internal(value_2, localsEntry, stk);
	}

	return value_2;
}



HBlockActionCall CBlockInterpreter::ActionResolveArguments(HBlockActionCall vCall, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockActionCallNamed  vCalln = asHBlockActionCallNamed(vCall))
	{
	HBlockActionCallNamed c = std::make_shared< CBlockActionCallNamed >(vCalln->action, vCall->noum1, vCall->noum2);
	if (vCall->noum1 != nullptr)
	{
		c->noum1 = resolve_argument(vCall->noum1, localsEntry, stk);
	}
	
	if (vCall->noum2 != nullptr)
	{
		c->noum2 = resolve_argument(vCall->noum2, localsEntry, stk);
	}
	
	return c;
	}
	return nullptr;
}


HRunLocalScope CBlockInterpreter::PhraseHeader_matchs(HBlockPhraseHeader pheader, HBlockPhraseInvoke phr, HRunLocalScope localsEntry, QueryStack *stk)
{

	if (CBlock::isSame(pheader->verb.get(), phr->header->verb.get()) == false) return nullptr;

	if (pheader->pred1 == nullptr && phr->header->pred1 != nullptr) return nullptr;
	if (pheader->pred1 != nullptr && phr->header->pred1 == nullptr) return nullptr;
	if (pheader->pred1 != nullptr && phr->header->pred1 != nullptr)
	{
		if (pheader->pred1->named() != phr->header->pred1->named()) return nullptr;
	}


	if (pheader->pred2 == nullptr && phr->header->pred2 != nullptr) return nullptr;
	if (pheader->pred2 != nullptr && phr->header->pred2 == nullptr) return nullptr;
	if (pheader->pred2 != nullptr && phr->header->pred2 != nullptr)
	{
		if (pheader->pred2->named() != phr->header->pred2->named()) return nullptr;
	}

	{
		auto arg1 = resolve_argument(phr->arg1, localsEntry, stk);
		CResultMatch result_1 = this->Match(pheader->arg1, arg1, localsEntry, stk);
		if (result_1.hasMatch)
		{
			auto localstmp = std::make_shared< CRunLocalScope >(localsEntry, result_1.maptch);
			auto arg2 = resolve_argument(phr->arg2, localstmp, stk);

			CResultMatch result_2 = this->Match(pheader->arg2, arg2, localsEntry, stk);
			if (result_2.hasMatch)
			{
				HRunLocalScope localsNext = std::make_shared< CRunLocalScope >(nullptr, result_1.maptch);
				localsNext = std::make_shared< CRunLocalScope >(localsNext, result_2.maptch);

				return localsNext;
				 
			}
		}
	}

	return nullptr;
}



 

PhaseResult CBlockInterpreter::execute_PhraseInvoke(HBlockPhraseInvoke phr, HRunLocalScope localsEntry, QueryStack *stk)
{
	for (auto sph : system_phrases)
	{
		HRunLocalScope execute_scope = PhraseHeader_matchs(sph , phr, localsEntry, stk);
		if (execute_scope != nullptr)
		{
			return   PhaseResult(true);
		}
	}

	for (auto ph : phrases)
	{
		HRunLocalScope execute_scope = PhraseHeader_matchs(ph->header, phr, localsEntry, stk);
		if (execute_scope != nullptr)
		{
			return  execute_now(ph->body, execute_scope, stk);
		}


	/*	if (CBlock::isSame(ph->header->verb.get(), phr->header->verb.get()) == false) continue;

		if (ph->header->pred1 == nullptr && phr->header->pred1 != nullptr) continue;
		if (ph->header->pred1 != nullptr && phr->header->pred1 == nullptr) continue;
		if (ph->header->pred1 != nullptr && phr->header->pred1 != nullptr)
		{
			if (ph->header->pred1->named != phr->header->pred1->named) continue;
		}


		if (ph->header->pred2 == nullptr && phr->header->pred2 != nullptr) continue;
		if (ph->header->pred2 != nullptr && phr->header->pred2 == nullptr) continue;
		if (ph->header->pred2 != nullptr && phr->header->pred2 != nullptr)
		{
			if (ph->header->pred2->named != phr->header->pred2->named) continue;
		}

		{
			auto arg1 = resolve_argument(phr->arg1, localsEntry, stk);
			CResultMatch result_1 = this->Match(ph->header->arg1, arg1, localsEntry, stk);
			if (result_1.hasMatch)
			{
				auto localstmp = std::make_shared< CRunLocalScope >(localsEntry, result_1.maptch);
				auto arg2 = resolve_argument(phr->arg2, localstmp, stk);

				CResultMatch result_2 = this->Match(ph->header->arg2, arg2, localsEntry, stk);
				if (result_2.hasMatch)
				{
					auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result_1.maptch);
					localsNext = std::make_shared< CRunLocalScope >(localsNext, result_2.maptch);

					return  execute_now(ph->body, localsNext, stk);
				}
			}
		}*/

	}
	return PhaseResult(false);

}

PhaseResult CBlockInterpreter::execute_now(HBlock p , HRunLocalScope localsEntry, QueryStack *stk ) //executa STMT
{	 
	if (asHBlockNothing(p) != nullptr)
	{
		return PhaseResult(true);
	}

	if (HBlockComandList  vCommandList= asHBlockComandList(p))
	{
		 
		//HRunLocalScope nextLocals = std::make_shared< CRunLocalScope >(localsEntry   );
		 
		PhaseResult rs_result(false);
		for(const auto &cmd : vCommandList->lista)
		{
			HRunLocalScope nextLocals = std::make_shared< CRunLocalScope >(localsEntry);
			auto pret = execute_now(cmd, nextLocals, stk);
			if (pret.hasExecuted == false)
			{ 
				printf("fail \n");
				cmd->dump("   ");
				return false;
			}
			rs_result = pret;			
			
			if (HBlockExecutionResultFlag  flag_ck = asHBlockExecutionResultFlag(rs_result.result))
			{
				return rs_result;
			}
			
		}
		return rs_result;

	}
	 
	if (HBlockIsVerb vverb = asHBlockIsVerb (p)) {
 
		auto rr = execute_verb_set(vverb, localsEntry,stk );
		if (rr.hasExecuted)		return rr;
	}

	if (HBlockIsNotVerb vverb = asHBlockIsNotVerb(p)) {

		auto r = (execute_verb_unset(vverb, localsEntry,stk ));
		if (r.hasExecuted)		return r;
	}


	if (HBlockAssertion_is vk = asHBlockAssertion_isDirectAssign (p)) {
		HBlock obj = vk->get_obj();
		HBlock value = vk->get_definition();
		return execute_set(obj, value,localsEntry);
	}


	 


	if (HBlockAssertion_is vk = asHBlockAssertion_isNotDirectAssign(p)) {
		HBlock obj = vk->get_obj();
		HBlock value = vk->get_definition();
		auto r =  execute_unset(obj, value, localsEntry);
		if (r.hasExecuted) return r;
	}



	if (auto phr = asHBlockPhraseInvoke(p))
	{
		return execute_PhraseInvoke(phr, localsEntry, stk);
	}



	if (HBlockDinamicDispatch  vdyn = asHBlockDinamicDispatch(p))
	{ 
		//determina quem eh o action do dynamica dispatch
		HBlockExecution  dispExec = create_dispach_env(vdyn->commandList, localsEntry);
		if (dispExec != nullptr)
		{ 
			return execute_now(dispExec->block , dispExec->locals);
		}
	}

	if (HBlockTryCall tCall = asHBlockTryCall (p))
	{
		execute_now(tCall->sentence);
		return PhaseResult(true);
	}

	if (HBlockActionCall  vCall = asHBlockActionCall (p))
	{	 		 
		{	
			//vCall->dump("");
			HBlockActionCall rCall = ActionResolveArguments(vCall, localsEntry, stk);
			if (rCall->noum1 == nullptr) 
				if (HBlockNoum  n1 = asHBlockNoum(vCall->noum1))
				{
					rCall->noum1 = n1;
				}
			if (rCall->noum2 == nullptr)
				if (HBlockNoum  n2 = asHBlockNoum(vCall->noum2))
				{
					rCall->noum2 = n2;
				}

			 
			auto r1 = execute_system_action(rCall, localsEntry, stk);
			if (r1.hasExecuted ) return r1;
			auto r2 = execute_user_action(rCall, localsEntry, stk);
			if (r2.hasExecuted ) return r2;
			return PhaseResult(false);
		}
	}

	if (HBlockControlIF  vControlIf =  asHBlockControlIF(p))
	{
		QueryResultContext qResult =  query(vControlIf->block_if, localsEntry, stk); 

		if (qResult.result == QEquals)
		{
			auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, qResult.matchedResult);
			return execute_now(vControlIf->block_then, localsNext, stk);
		}
		else
		{
			if (vControlIf->block_else != nullptr)
			{
				 
				auto r =  execute_now(vControlIf->block_else, localsEntry, stk);
				return r;
			}
		}
		return PhaseResult(true);
		
	}

	if (HBlockControlForEach   vControlForEach = asHBlockControlForEach(p))
	{

		ListOfNamedValue  loopListEnummerator = getValuesFromMatch(vControlForEach->block_variable, localsEntry, stk);
		{
			for(auto hii : loopListEnummerator)
			{
			
				const  std::map<string, CBlocking::HBlock> nextVarSet = { { hii.named , hii.value } };
				auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, nextVarSet);
				//printf("For Loop Begin__________________________________\n");
				//localsNext->dump("");
				//vControlForEach->block_body->dump("");
				//printf("For Loop End __________________________________\n");

				auto rloop_result = execute_now(vControlForEach->block_body , localsNext, stk);
				if (HBlockExecutionResultFlag  flag_ck = asHBlockExecutionResultFlag(rloop_result.result))
				{
					return rloop_result;
				}
			}
			return PhaseResult(true);
		}

	}

	if (HBlockControlSelect  vControlSelect = asHBlockControlSelect(p))
	{
		for (auto item : vControlSelect->block_selectList)
		{
			QueryResultContext qResult = query_is(vControlSelect->block_seletor, item->block_seletor, localsEntry, stk);
			if (qResult.result == QEquals)
			{
				return execute_now(item->block_execute, localsEntry, stk);
			}
		}
		//Execute the else
		if (vControlSelect->block_else != nullptr)
		{
			return execute_now(vControlSelect->block_else, localsEntry, stk);
		}

		return PhaseResult(true);

	}

	if (HBlockNow  vNow = asHBlockNow (p)) 
	{
		return execute_now( vNow->assertation, localsEntry,stk);
	}


	if (HBlockDinamicDispatch  vdispAtion = asHBlockDinamicDispatch(p))
	{
		
		return PhaseResult(true);
	}
	 
	if (HBlockExecutionResultFlag  flag_ck = asHBlockExecutionResultFlag(p))
	{
		auto qres=  PhaseResult(true);
		qres.result = flag_ck;
		return qres;
	}


	return PhaseResult(false);

}

