// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


//Executor de acoes 


#include "CResultMatch.hpp"
#include <memory>
 
#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;


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

PhaseResult CBlockInterpreter::execute_verb_set(HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStack *stk)
{

	// Eh uma relacao ??
	for (auto & rv : verbRelationAssoc)
	{
		if (rv.first == vverb->verb)
		{
			auto relation_name = rv.second->relationNoum->named;
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
					this->set_relation(rel, vverb->n1, vverb->n2, localsEntry,stk );
					return true;
				}
				else if (rv.second->type() == BlockVerbReverseRelation)
				{
					HBlockRelationBase rel = rel_find->second;
					this->set_relation(rel, vverb->n2, vverb->n1, localsEntry,stk); // inverte a relacao
					return true;
				}
			}
			else
			{
				//verbis not set to an relation
				logError("verb "+ vverb->verb + " not set to an relation");
			}
		}

	}
	return false;
}


PhaseResult CBlockInterpreter::execute_verb_unset(HBlockIsNotVerb vverb, HRunLocalScope localsEntry, QueryStack *stk)
{

	// Eh uma relacao ??
	for (auto & rv : verbRelationAssoc)
	{
		if (rv.first == vverb->verb)
		{
			auto relation_name = rv.second->relationNoum->named;
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
	if (HBlockEvery nevery = asHBlockEvery(obj))
	{
		std::list<HBlock> matchedObjects = getMatchedObjects(nevery->assertation, localsEntry);
		for (auto r : matchedObjects)
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


PhaseResult CBlockInterpreter::execute_set(HBlock obj, HBlock value, HRunLocalScope localsEntry)
{


	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) {
			return assert_it_Value(nobj, value, localsEntry);
		}
	}

	if (HBlockEvery nevery = asHBlockEvery(obj))
	{ 
		std::list<HBlock> matchedObjects = getMatchedObjects(nevery->assertation, localsEntry);
		for (auto r : matchedObjects)
		{
		 
			execute_set(r, value, localsEntry);
		}
		return true;

	}


	// value tem que ser uma instancia, propriedade ou variavel

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		if (HBlockNoum nbase = asHBlockNoum(value)) {
			HBlock nobj = resolve_noum(nbase, localsEntry);
			if (nobj == nullptr)
			{
				nInst->set(nbase);
				return true;
			}
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
	if (HVariableNamed  var_n = asHVariableNamed(obj)) {

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

HBlock CBlockInterpreter::exec_eval_property_value_imp(HBlock propname, HBlock propObj )
{
	if (HBlockInstance cinst = asHBlockInstance(propObj))
	{
		if (HBlockNoum property_noum = asHBlockNoum(propname))
		{
			HVariableNamed pvar = cinst->get_property(property_noum->named);
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
			auto resolved = resolve_noum(cnn,localsEntry);
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

	

	for (auto it = assertions.begin(); it != assertions.end(); ++it) {
		if (HBlockAssertion_is qdef = asHBlockAssertion_is(*it))
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


HBlock CBlockInterpreter::exec_eval(HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk )
{

	if (c_block == nullptr)
	{
		return nullptr;
	}
	 

	if (HBlockComandList nlist = asHBlockComandList(c_block))
	{
		HBlock ret_out = nullptr;
		for (auto e : nlist->lista)
		{
			auto ret = exec_eval(e, localsEntry,stk);
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
		HBlock ret = nullptr;
 
  		auto r = query(cIF->block_if, localsEntry, stk);
		if (r.result == QEquals)
		{
			auto localsNext = std::make_shared< CRunLocalScope >(localsEntry , r.matchedResult );
			 
			return exec_eval(cIF->block_then, localsNext, stk);
		}
		else
		{
			if (cIF->block_else != nullptr)
			{
				return exec_eval(cIF->block_else, localsEntry, stk);
			}
			return nullptr;
		}
	}

	{
		if (HBlockAssertion_isDirectAssign nDirect = asHBlockAssertion_isDirectAssign(c_block))
		{
			QueryResultContext q = query(nDirect, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoum>("true");
			return std::make_shared<CBlockNoum>("false");
		}


		if (HBlockIsVerb  nVerbDirect = asHBlockIsVerb(c_block))
		{
			QueryResultContext q = query(nVerbDirect, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoum>("true");
			return std::make_shared<CBlockNoum>("false");
		}


		if (HBlockAssertion_isNotDirectAssign nDirectv = asHBlockAssertion_isNotDirectAssign(c_block))
		{
			QueryResultContext q = query(nDirectv, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoum>("true");
			return std::make_shared<CBlockNoum>("false");
		}


		if (HBlockIsNotVerb  nVerbDirectv = asHBlockIsNotVerb(c_block))
		{
			QueryResultContext q = query(nVerbDirectv, localsEntry, stk);
			if (q.result == QEquals) return std::make_shared<CBlockNoum>("true");
			return std::make_shared<CBlockNoum>("false");
		}
	}


	if (HBlockToDecideOn ndecide = asHBlockToDecideOn(c_block))
	{

		auto r = exec_eval(ndecide->decideBody, localsEntry, stk);
		return std::make_shared<CBlockToDecideOn>(r);
	}

	if (HBlockNoum nn = asHBlockNoum(c_block))
	{
		if (nn->named == "nothing") return nn;
		auto  obj = resolve_noum(nn, localsEntry, std::list<std::string>());
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

	if (HBlockAction nAction = asHBlockAction(c_block))
	{
		return nAction;
	}


	if (HBlockKind kIns = asHBlockKind(c_block))
	{
		return kIns;
	}

	if (auto  kvar = asHVariableNamed(c_block))
	{
		return kvar->value;
	}



	if (auto  kprop = asHBlockProperty(c_block))
	{
		{
			//check for plural
			if (HBlockNoum propNoum = asHBlockNoum(kprop->prop))
			{
				if ( isSameString(propNoum->named, "plural"))
				{
					string c = BlockNoum(kprop->obj);
					if (!(c.empty()))
					{
						return  get_plural_of(c);
					}					 
				}
			}
		}

		auto instancia = exec_eval(kprop->obj, localsEntry, stk);
		if (HBlockInstance objInst = asHBlockInstance(instancia))
			if (HBlockNoum propNoum = asHBlockNoum(kprop->prop))
			{
				HVariableNamed pvar = objInst->get_property(propNoum->named);
				return pvar->value;
			}
		return nullptr;
	}

	if (HBlockNamedValue nvalue = asHBlockNamedValue(c_block))
	{
		return nvalue;
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

	//resolve To decides
	for (auto dct : decides_what)
	{
		auto dctValueWrap = getDecidedValueOf(c_block, dct, nullptr,stk);
		if (dctValueWrap != nullptr)
		{
			return dctValueWrap;
		}
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

	 

	// Bla ! 
	c_block->dump("");
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

	if (HBlockAction actionCall = asHBlockAction(p))
	{
		return actionCall;
	}

	if (HVariableNamed callAsVar = asHVariableNamed(p))
	{
		auto actionCall_1 = callAsVar->value;
		return  resolve_as_callCommand(actionCall_1, localsEntry);
	}
	

	return nullptr;
}

HExecutionBlock CBlockInterpreter::create_dispach_env(HBlockList  p, HRunLocalScope localsEntry)
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
						 localsNext->locals.push_back(std::pair<string, HBlock>(arg1_named->named, obj_resolved));
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
							 locals_obj_1->locals.push_back(std::pair<string, HBlock>("noum1" , obj_resolved));
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
							 localsNext->locals.push_back(std::pair<string, HBlock>(arg2_named->named, obj_resolved));
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
								 locals_obj_2->locals.push_back(std::pair<string, HBlock>("noum2", obj_resolved));
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


			 if (HBlockAction actionCall = asHBlockAction (output_block))
			 {
				
				 HRunLocalScope localsNextp = std::make_shared< CRunLocalScope >(localsEntry , result.maptch);
				  
				return  make_shared< CExecutionBlock >(localsNextp, std::make_shared<CBlockActionCall>(actionCall, ref_Arg_1 , ref_Arg_2));
			 } 

			 HExecutionBlock executionBlock = make_shared< CExecutionBlock >(localsNext, output_block);
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
		logError("fail to execute ");
		p->dump("");
		logError("");
	}
	return b;
}

PhaseResult CBlockInterpreter::execute_now(HBlock p, HRunLocalScope localsEntry) //executa STMT
{
	QueryStack *stk = nullptr;
	return execute_now(p, localsEntry, stk);
}
PhaseResult CBlockInterpreter::execute_now(HBlock p , HRunLocalScope localsEntry, QueryStack *stk ) //executa STMT
{	 
	if (HBlockComandList  vCommandList= asHBlockComandList(p))
	{
		auto nextLocals = copy_CRunLocalScope(localsEntry);
		PhaseResult rs_result(false);
		for(auto cmd : vCommandList->lista)
		{
			auto pret = execute_now(cmd, nextLocals, stk);
			if (pret.hasExecuted == false)
			{
				logError("fail to execute ");
				p->dump("");
				logError("");
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



	if (HBlockDinamicDispatch  vdyn = asHBlockDinamicDispatch(p))
	{ 
		//determina quem eh o action do dynamica dispatch
		HExecutionBlock dispExec = create_dispach_env(vdyn->commandList, localsEntry);
		if (dispExec != nullptr)
		{ 
			return execute_now(dispExec->block , dispExec->locals);
		}
	}

	if (HBlockActionCall  vCall = asHBlockActionCall (p))
	{	 		 
		{			 
	 
			auto r1 = execute_system_action(vCall); 
			if (r1.hasExecuted ) return r1;
			auto r2 = execute_user_action(vCall, localsEntry, stk);
			if (r2.hasExecuted ) return r2;
			return PhaseResult(false);
		}
	}

	if (HBlockControlIF  vControlIf =  asHBlockControlIF(p))
	{

		QueryResultContext qResult =  query (vControlIf->block_if, localsEntry, stk);

		 

		if (qResult.result == QEquals)
		{
			  return execute_now(vControlIf->block_then, localsEntry, stk);
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