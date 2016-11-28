


#include "CBlockMatch.hpp"
 
#include "CBlockUndestand.hpp"
#include "CBlockDecideIf.hpp"
#include "CBlockRelation.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "CBlockNumber.hpp"
using namespace std;
 
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;

void CBlockInterpreter::initialize() {
	for (auto &p : program) {
		execute_init(p);
	}

}

bool CBlockInterpreter::assert_it_canBe(CBlocking::HBlock c_block, HBlockEnums value, HRunLocalScope localsEntry) {
	if (HBlockNoum nbase = DynamicCasting::asHBlockNoum(c_block)) {
		CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_it_canBe(nobj, value,localsEntry);
		}
		return false;
	} else if (HBlockKind nkind = DynamicCasting::asHBlockKind(c_block)) {
		kind_variables.push_back(make_shared<CBlockAssertion_canBe>(nkind, value));
		return true;
	} else if (HBlockInstance nInst = DynamicCasting::asHBlockInstance(c_block)) {
		auto p = make_shared<CBlockAssertion_canBe>(nInst, value);
		assign_variable_to_instance(make_shared<CBlockAssertion_canBe>(nInst, value));

		return true;
	}

	return true;
}


bool CBlockInterpreter::queryIsVerbToRelation( HBlockMatch m)
{
	if (auto vv = DynamicCasting::asHBlockMatchIsVerb(m))
	{
		auto cfind = verbRelationAssoc.find(vv->verb);
		if (cfind != verbRelationAssoc.end())
		{
		   if (cfind->second->relationNoum->named  != "dynamic")
		   {
			  logError( "verb " + vv->verb + " belongs to relation " + cfind->second->relationNoum->named);
			   return true;
		   }
		}
	}
	return false;
}

void CBlockInterpreter::logMessage(std::string msg)
{
	printf("%s\n", msg.c_str());

}


bool CBlockInterpreter::assert_decideBlock(HBlockToDecide dct) {




	if (auto dct_w = asHBlockToDecideWhat(dct))
	{
		if (queryIsVerbToRelation(dct_w->queryToMatch))
		{

			return false;
		}

		decides_what.push_back(dct_w);
		return true;
	}
 

	if (auto dct_if = asHBlockToDecideIf(dct))
	{
		if (queryIsVerbToRelation(dct_if->queryToMatch))
		{
			return false;
		}
		decides_if.push_back(dct_if);
		return true;
	}
	 
	if (auto dct_noum1 = asHBlockToDecideWhat_FirstNoum(dct))
	{
		if (queryIsVerbToRelation(dct_noum1->queryToMatch))
		{
			return false;
		}

		decides_noum1.push_back(dct_noum1);
		return true;
	}
 
	return false;
}


 
bool CBlockInterpreter::assert_has_variable(CBlocking::HBlock obj, CBlocking::HBlock value,   HRunLocalScope localsEntry) {

	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_has_variable(nobj, value, localsEntry);
		}
		return false;
	}

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		//name da variavel
		if (HBlockInstanceVariable variable_ = asHBlockInstanceVariable(value)) {
			HBlockKind nkindBase = resolve_kind(variable_->kind_name->named);
			nInst->newNamedVariable(variable_->property_name, nkindBase);
			return true;
		}

	} 

	if (HBlockAction nAction = asHBlockAction(obj))
	{
		//name da variavel
		if (HBlockInstanceVariable variable_ = asHBlockInstanceVariable(value)) {
			HBlockKind nkindBase = resolve_kind(variable_->kind_name->named);
			nAction->newNamedVariable(variable_->property_name, nkindBase);
			return true;
		}

	}
	
	if (HBlockKind nKind = asHBlockKind(obj)) 	{
		
		if (HBlockInstanceVariable iVariableNamed = asHBlockInstanceVariable(value)) {
			if (HBlockKind_InstanceVariable variable_ = make_shared<CBlockKind_InstanceVariable>(nKind, iVariableNamed))
			{			 
				kind_named_variables.push_back(variable_);
				add_namedVariableToAllinstances(  variable_);
				return true;
			}
		}
		 
	}
	return false;
}

bool CBlockInterpreter::is_all_items_of_kind(HBlockList listvalues, HBlockKind kind , HRunLocalScope localsEntry)
{
	for( auto &v : listvalues->lista )
	{
		if (value_can_be_assign_to(v,kind,localsEntry) == nullptr  ) return false ;

	}
	return true;


}

//Forca value a ser Kind
CBlocking::HBlock CBlockInterpreter::value_can_be_assign_to(CBlocking::HBlock value, HBlockKind kind, HRunLocalScope localsEntry) {
	if (value == nullptr) return nullptr;

	if (HBlockEnums enumarate = asHBlockEnums(kind)) {
		// Acha todas as instancias
		if (HBlockNoum cnn = asHBlockNoum(value))
		{
			for (auto &ee : enumarate->values)
			{
				if (ee->named == cnn->named) return ee;
			}
			return nullptr;
		}
	}

	
	if (HBlockInstance cinst = asHBlockInstance(value)) {
		if (is_derivadeOf(cinst, kind ,localsEntry )) {
			return cinst;
		}
	}

	if (HBlockAction cAction = asHBlockAction(value))
	{
		if (HBlockKindValue kAction = asHBlockKindValue(kind))
		{					
			if ((kAction->named == "action")) return cAction;
			return nullptr;
		}
	}


	if (HBlockNumber cNumber = asHBlockNumber(value))
	{
		if (HBlockKindValue kNumber = asHBlockKindValue(kind))
		{
			if ((kNumber->named == "number")) return cNumber;
			return nullptr;
		}
	}




	if (HBlockNoum cnn = asHBlockNoum(value)) {
		CBlocking::HBlock resolved = resolve_noum(cnn,localsEntry);
		if (resolved != nullptr)
		{
			return value_can_be_assign_to(resolved, kind,localsEntry);
		}
	}

	if (HBlockList clist = asHBlockList(value))
	{
		//Kind precisa ser uma lista tambem
		if (HBlockListOfKind klist = asHBlockListOfKind(kind)) {
			//tem algum tipo que nao corresponde ?
			if (is_all_items_of_kind(clist, klist->itemKind,localsEntry) == false)
			{
				return nullptr;
			}
			return value;

		}
	}

	logError("Unable to set ");
	//value->dump("    ");	
	//kind->dump("    ");
	return nullptr;

}



bool CBlockInterpreter::set_plural_property(CBlocking::HBlock  _singular, CBlocking::HBlock  _plural, HRunLocalScope localsEntry)
{
	if ( HBlockNoum noum_singular = asHBlockNoum( _singular ) )
	{
		if ( HBlockNoum noum_plural = asHBlockNoum( _plural ) )
		{			 
			plural_assertations.push_back(make_pair(noum_singular, noum_plural));
			return true;
		}
	}
	return false;
}




bool CBlockInterpreter::assert_it_property(CBlocking::HBlock propname, CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) 
		{
			return assert_it_property(propname, nobj, value, localsEntry);
		}
		  
	}

	if (HBlockNoum property_noum = asHBlockNoum(propname))
	{

		if (isSameString(property_noum->named, "plural"))
		{
			bool set_prop_plural = set_plural_property(obj, value, localsEntry);
			if (set_prop_plural) return set_prop_plural;
		}


		if (HBlockInstance cinst = asHBlockInstance(obj))
		{
			HVariableNamed vv = cinst->get_property(property_noum->named);
			if (vv != nullptr)
			{
				CBlocking::HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind, localsEntry));
				if (instanceValueRefered) {
					cinst->set_property(property_noum->named, instanceValueRefered);
					return true;
				}
			}
			else
			{
				logMessage("Obje dont have " + property_noum->named + "property ");
			}

		}

		if (HBlockAction cAction = asHBlockAction(obj))
		{

			HVariableNamed vv = cAction->get_property(property_noum->named);
			if (vv != nullptr)
			{
				CBlocking::HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind, localsEntry));
				if (instanceValueRefered) {
					cAction->set_property(property_noum->named, instanceValueRefered);
					return true;
				}
			}
			else
			{
				logMessage("Obje dont have " + property_noum->named + "property ");
			} 
		}
	 

		{
			bool set_prop_rel = set_relation_property(property_noum, obj, value, localsEntry);
			if (set_prop_rel) return set_prop_rel;
		}

		 
	}
	return false;

}



bool CBlockInterpreter::assert_it_not_Value(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_it_not_Value(nobj, value,localsEntry);
		}
		return false;
	}

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		if (HBlockNoum nbase = asHBlockNoum(value)) {
			CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
			if (nobj == nullptr) {
				nInst->unset(nbase);
				return true;
			}
		}

	}
	return false;
}



void CBlockInterpreter::execute_init(CBlocking::HBlock p) {

	if (p == nullptr)
	{
		logError("empty init block ");
		return;
	}

	  HRunLocalScope localsEntry = nullptr;

	  if (HBlockComandList cmdList = asHBlockComandList(p)) 
	  {
		for(auto it : cmdList->lista)
		{
 
			execute_init(it);
	 
		}
		return;
	  }

	if (HBlockAssertion_isNotDirectAssign v = asHBlockAssertion_isNotDirectAssign(p)) {
		CBlocking::HBlock obj = v->get_obj();
		CBlocking::HBlock value = v->get_definition();
		if (assert_it_not_Value(obj, value, localsEntry)) return;
	}

	if (HBlockAssertion_isDefaultAssign v = asHBlockAssertion_isDefaultAssign(p)) {
		CBlocking::HBlock obj = v->get_obj();
		CBlocking::HBlock value = v->get_definition();
		if (assert_it_defaultValue(obj, value, localsEntry)) return;
	}
	else if (HBlockAssertion_canBe vee = asHBlockAssertion_canBe(p)) {
		CBlocking::HBlock obj = vee->get_obj();
		HBlockEnums evalue = vee->definition;
		if (assert_it_canBe(obj, evalue, localsEntry)) return;
	}
	else if (HBlockIsVerb  vRelation = asHBlockIsVerb(p)){

		CBlocking::HBlock obj = vRelation->get_obj();
		CBlocking::HBlock value = vRelation->get_definition();
		if (assert_it_verbRelation(vRelation->verb , obj, value,localsEntry)) return;
	}
	else if (HBlockAssertion_isVariable  vGlobal  = asHBlockAssertion_isVariable(p)) {


		if (assert_it_variableGlobal(vGlobal->variable, vGlobal->baseKind )) {
			return;
		}
		else
		{
			//throw error
			logError("Undefined error");
			return ;
		}
	}

	else if (HBlockAssertion_is vk = asHBlockAssertion_is(p)) {
		CBlocking::HBlock obj = vk->get_obj();
		CBlocking::HBlock value = vk->get_definition(); 
		if (assert_assertation(obj, value, localsEntry)) return;		
		logError("Undefined error");
		p->dump("  ");
		//throw "undefined block";
		return ;
	} else if (HBlockAssertion_InstanceVariable ivar = asHBlockAssertion_InstanceVariable(p)) {
		CBlocking::HBlock obj = ivar->noum;
		CBlocking::HBlock value = ivar->instance_variable;
		if (assert_has_variable(obj, value,localsEntry)) return;
	} else if (HBlockToDecide dcMatch = asHBlockToDecide(p)) {
		if (assert_decideBlock(dcMatch)) return;

	}
	if (HBlockVerbRelation dcverbImpl = asHBlockVerbRelation(p))
	{
		if (assert_newVerb(dcverbImpl)) return; 
	}
	  

	if (HBlockUnderstandDynamic    dn_dispatch = asHBlockUnderstandDynamic (p))
	{
		if (assert_newUnderstand(dn_dispatch)) return;
		
	}

	if (HBlockRelationBase    dn_relation = asHBlockRelationBase (p))
	{
		if (assert_newRelation(dn_relation)) return;

	}
	if (HBlockVerb    reg_verb = asHBlockVerb (p))
	{
		 if (insert_newVerb(reg_verb)) return;

	}

	if (HBlockEventHandle    reg_event_handle = asHBlockEventHandle(p))
	{
		if (insert_newEventHandle(reg_event_handle)) return;

	}


	logError("not found block definition ");
	p->dump("");
	return;
}
