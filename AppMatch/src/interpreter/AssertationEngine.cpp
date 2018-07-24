// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "CBlockMatch.hpp"

#include "CBlockUndestand.hpp"
#include "CBlockDecideIf.hpp"
#include "CBlockRelation.hpp"
#include "sharedCast.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "CBlockNumber.hpp"


using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;



void CBlockInterpreter::initialize() {
	for (auto &p : program) {
		execute_init(p);
	}

}

void CBlockInterpreter::start()
{
	//verifica se tem algum unit init ?
	for (const auto u_env : this->unit_test)
	{
		if (u_env.init != nullptr)
		{
			this->execute_init(u_env.init->contents);
		}
		for (auto t : u_env.tests)
		{
			auto r = this->execute_now(t.test->contents);
			if (r.result)
			{
				r.result->dump("");

			}
			for (auto asrt : t.assertion)
			{
				auto result = query(asrt->contents, nullptr, nullptr).result;
				if (result != QEquals)
				{
					printf("Assertion Failed \n");
					asrt->dump(" ");
					printf("\n");
					auto result_2 = query(asrt->contents, nullptr, nullptr).result;
				}
				else
				{
					printf("Assertion Pass \n");
				}
			}


		};


	}
}








bool CBlockInterpreter::is_runnig()
{
	return true;
}



string  CBlockInterpreter::prompt()
{
	for (auto v : this->global_variables)
	{
		if (v->name->named() == "command prompt" )
		{
			std::string number = "singular";
			std::string gender = "neutral";
			std::string person = "3S";
			auto nn =  textual_representation(v->value, person , number , gender ,nullptr, nullptr  );
			return nn->named();
		}
	}
	return ">";
}

void   CBlockInterpreter::feed(string user_input)
{
	//printf("\nenter:%s\n", user_input.c_str());
	HRunLocalScope localsEntry = make_shared< CRunLocalScope >(nullptr);
	HBlockActionNamed actionCall = std::make_shared<CBlockActionNamed>("Commanding");	 
	HBlockText  argument = std::make_shared<CBlockText>(user_input) ;
	execute_now(std::make_shared<CBlockActionCallNamed>(actionCall, argument, nullptr), localsEntry);

}



void   CBlockInterpreter::add_modifier_keyword(HBlockEnums _enums)
{
	for (auto e : _enums->values)
	{
		registred_adjetives.push_back(e);
	}
}

void   CBlockInterpreter::add_modifier_keyword(HBlockNoum _nn)
{
	registred_adjetives.push_back(_nn);
}


bool CBlockInterpreter::assert_it_canBe(CBlocking::HBlock c_block, HBlockEnums value, HRunLocalScope localsEntry) {
	if (const HBlockNoum nbase = DynamicCasting::asHBlockNoum(c_block))
	{
		const CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr)
		{
			return assert_it_canBe(nobj, value, localsEntry);
		}
		return false;
	}
	else if (HBlockKind nkind = DynamicCasting::asHBlockKind(c_block)) 
	{
		kind_variables.push_back(make_shared<CBlockAssertion_canBe>(nkind, value));
		//Acha todas as instancias derivadas desse tipo e assign o slot
		
		for (auto iObj : getInstancesFromKind(nkind, localsEntry) )
		{			 
			assign_variable_to_instance(make_shared<CBlockAssertion_canBe>(iObj, value));
		}

		add_modifier_keyword(value);
		return true;
	}
	else if (HBlockInstance nInst = DynamicCasting::asHBlockInstance(c_block)) 
	{
		auto p = make_shared<CBlockAssertion_canBe>(nInst, value);
		assign_variable_to_instance(make_shared<CBlockAssertion_canBe>(nInst, value));
		add_modifier_keyword(value);
		return true;
	}

	return true;
}


bool CBlockInterpreter::queryIsVerbToRelation(HBlockMatch m)
{
	if (auto vv = DynamicCasting::asHBlockMatchIsVerb(m))
	{
		auto cfind = verbRelationAssoc.find(vv->verb);
		if (cfind != verbRelationAssoc.end())
		{
			if (cfind->second->relationNoum->named() != "dynamic")
			{
				logError("verb " + vv->verb + " belongs to relation " + cfind->second->relationNoum->named());
				return true;
			}
		}
	}
	return false;
}

void CBlockInterpreter::logMessage(const string & msg)
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



bool CBlockInterpreter::assert_has_variable(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {

	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) {
			return assert_has_variable(nobj, value, localsEntry);
		}

	}

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		//name da variavel
		if (HBlockInstanceVariable variable_ = asHBlockInstanceVariable(value)) {
			HBlockKind nkindBase = resolve_kind(variable_->kind_name->named());
			nInst->newNamedVariable(variable_->property_name, nkindBase);
			return true;
		}

	}

	if (HBlockActionInstance nAction = asHBlockActionInstance(obj))
	{
		//name da variavel
		if (HBlockInstanceVariable variable_ = asHBlockInstanceVariable(value))
		{
			HBlockKind nkindBase = resolve_kind(variable_->kind_name->named());
			nAction->newNamedVariable(variable_->property_name, nkindBase);
			return true;
		}

	}

	if (HBlockKind nKind = asHBlockKind(obj)) {

		if (HBlockInstanceVariable iVariableNamed = asHBlockInstanceVariable(value)) {
			if (HBlockKind_InstanceVariable variable_ = make_shared<CBlockKind_InstanceVariable>(nKind, iVariableNamed))
			{
				kind_named_variables.push_back(variable_);
				add_namedVariableToAllinstances(variable_);
				return true;
			}
		}

	}
	return false;
}

bool CBlockInterpreter::is_all_items_of_kind(HBlockList listvalues, HBlockKind kind, HRunLocalScope localsEntry)
{
	for (auto &v : listvalues->lista)
	{
		if (value_can_be_assign_to(v, kind, localsEntry) == nullptr) return false;

	}
	return true;


}

//Forca value a ser Kind
CBlocking::HBlock CBlockInterpreter::value_can_be_assign_to(CBlocking::HBlock value, HBlockKind kind, HRunLocalScope localsEntry) {
	if (value == nullptr) return nullptr;

	if (value == Nothing)
	{
		if (asHBlockKindEntity(kind) != nullptr) return value;
	}



	if (HBlockEnums enumarate = asHBlockEnums(kind)) {
		// Acha todas as instancias
		if (HBlockNoum cnn = asHBlockNoum(value))
		{
			for (auto &ee : enumarate->values)
			{
				if (ee->named() == cnn->named()) return ee;
			}
			return nullptr;
		}
	}


	if (HBlockInstance cinst = asHBlockInstance(value))
	{
		if (is_derivadeOf(cinst, kind, localsEntry)) {
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

	if (HBlockText cText = asHBlockText(value))
	{
		if (HBlockKindValue kText = asHBlockKindValue(kind))
		{
			if (CBlock::isSame(kText.get(), MetaKindText.get())) return cText;
			if (  isSameString(kText->named , MetaKindText->named )) return cText;
			return nullptr;
		}
	}


	if (HBlockNoum cnn = asHBlockNoum(value)) {
		CBlocking::HBlock resolved = has_resolve_noum(cnn, localsEntry);
		if (resolved != nullptr)
		{
			return value_can_be_assign_to(resolved, kind, localsEntry);
		}
	}

	if (HBlockList clist = asHBlockList(value))
	{
		//Kind precisa ser uma lista tambem
		if (HBlockCompositionList klist = asHBlockCompositionList(kind))
		{
			//tem algum tipo que nao corresponde ?
			if (is_all_items_of_kind(clist, klist->itemKind, localsEntry) == false)
			{
				return nullptr;
			}
			return value;

		}
	}

	logWarring("Unable to set ");

	return nullptr;

}



bool CBlockInterpreter::set_plural_property(CBlocking::HBlock  _singular, CBlocking::HBlock  _plural, HRunLocalScope localsEntry)
{
	if (HBlockNoum noum_singular = asHBlockNoum(_singular))
	{
		if (HBlockNoum noum_plural = asHBlockNoum(_plural))
		{
			plural_assertations.push_back(make_pair(noum_singular, noum_plural));
			return true;
		}
	}
	return false;
}




bool CBlockInterpreter::assert_it_property(CBlocking::HBlock propname, CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk) {
	if (HBlockNoum nbase = asHBlockNoum(obj))
	{
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr)
		{
			return assert_it_property(propname, nobj, value, localsEntry, stk);
		}
	}


	if (HBlockNoum property_noum = asHBlockNoum(propname))
	{

		if (isSameString(property_noum->named(), "plural"))
		{
			bool set_prop_plural = set_plural_property(obj, value, localsEntry);
			if (set_prop_plural) return set_prop_plural;
		}


		if (HBlockInstance cinst = asHBlockInstance(obj))
		{
			HBlockVariableNamed vv = cinst->get_property(property_noum->named());
			if (vv != nullptr)
			{
				if (is_primitive_value(value, localsEntry, stk) == false)
				{
					auto next_value = exec_eval(value, localsEntry, stk);
					return assert_it_property(propname, obj, next_value, localsEntry, stk);
				}


				CBlocking::HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind, localsEntry));
				if (instanceValueRefered) {
					cinst->set_property(property_noum->named(), instanceValueRefered);
					return true;
				}
			}
			else
			{

				logMessage("Obje dont have " + property_noum->named() + " property ");
			}

		}

		if (HBlockActionInstance cAction = asHBlockActionInstance(obj))
		{

			HBlockVariableNamed vv = cAction->get_property(property_noum->named());
			if (vv != nullptr)
			{
				if (is_primitive_value(value, localsEntry, stk) == false)
				{
					auto next_value = exec_eval(value, localsEntry, stk);
					return assert_it_property(propname, obj, next_value, localsEntry, stk);
				}

				const CBlocking::HBlock instanceValueRefered = (value_can_be_assign_to(value, vv->kind, localsEntry));
				if (instanceValueRefered) {
					cAction->set_property(property_noum->named(), instanceValueRefered);
					return true;
				}
			}
			else
			{
				logMessage("Obje dont have " + property_noum->named() + "property ");
			}
		}


		{

			bool set_prop_rel = set_relation_property(property_noum, obj, value, localsEntry, stk);
			if (set_prop_rel) return set_prop_rel;
		}


	}
	return false;

}



bool CBlockInterpreter::assert_it_not_Value(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
	if (HBlockNoum nbase = asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
		if (nobj != nullptr) {
			return assert_it_not_Value(nobj, value, localsEntry);
		}
		return false;
	}

	if (HBlockInstance nInst = asHBlockInstance(obj)) {
		if (HBlockNoum nbase = asHBlockNoum(value)) {
			CBlocking::HBlock nobj = resolve_noum(nbase, localsEntry);
			if (nobj == nullptr) {
				nInst->unset(nbase);
				return true;
			}
		}

	}
	return false;
}

void CBlockInterpreter::add_new_init(HBlockUnitInit u_init)
{
	this->unit_test.push_back(UnitTest_Env(u_init));
}

void CBlockInterpreter::add_new_test(HBlockUnitTest u_test)
{
	if (this->unit_test.empty())
	{
		this->unit_test.push_back(UnitTest_Env(nullptr));
	}
	this->unit_test.back().tests.push_back(UnitTest_Single(u_test));
}

void CBlockInterpreter::add_new_assertion(HBlockUnitAssert asserti)
{
	if (this->unit_test.empty() == false)
	{
		if (this->unit_test.back().tests.empty() == false)
		{
			this->unit_test.back().tests.back().assertion.push_back(asserti);
		}
	}
}


void CBlockInterpreter::execute_init(CBlocking::HBlock p) {

	if (p == nullptr)
	{
		logError("empty init block ");
		return;
	}

	p->dump("E   ");

	HRunLocalScope localsEntry = nullptr;

	if (HBlockComandList cmdList = asHBlockComandList(p))
	{
		for (auto it : cmdList->lista)
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

	if (HBlockAssertion_isForbiddenAssign fb = asHBlockAssertion_isForbiddenAssign(p)) {
		CBlocking::HBlock obj = fb->get_obj();
		CBlocking::HBlock value = fb->get_definition();
		if (assert_it_ForbiddenValue(obj, value, localsEntry)) return;
	}

	if (HBlockAssertion_isConstantAssign fb = asHBlockAssertion_isConstantAssign(p)) {
		CBlocking::HBlock obj = fb->get_obj();
		CBlocking::HBlock value = fb->get_definition();
		if (assert_it_ConstantAssign(obj, value, localsEntry)) return;
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
		logError("Can Be undefined");
	}
	else if (HBlockIsVerb  vRelation = asHBlockIsVerb(p)) {

		CBlocking::HBlock obj = vRelation->get_obj();
		CBlocking::HBlock value = vRelation->get_definition();


		if (assert_it_verbRelation(vRelation->verb, obj, value, localsEntry, nullptr)) return;
	}
	else if (HBlockAssertion_isVariable  vGlobal = asHBlockAssertion_isVariable(p)) {

		if (assert_it_variableGlobal(vGlobal->variable, vGlobal->baseKind, nullptr)) {
			return;
		}
		else
		{
			//throw error
			logError("Undefined error");
			return;
		}
	}

	else if (HBlockAssertion_is vk = asHBlockAssertion_is(p)) {
		CBlocking::HBlock obj = vk->get_obj();
		CBlocking::HBlock value = vk->get_definition();
		if (assert_assertation(obj, value, localsEntry)) return;
		logError("Undefined error");
		p->dump("  ");
		//throw "undefined block";
		return;
	}
	else if (HBlockAssertion_InstanceVariable ivar = asHBlockAssertion_InstanceVariable(p)) {
		CBlocking::HBlock obj = ivar->noum;
		CBlocking::HBlock value = ivar->instance_variable;
		if (assert_has_variable(obj, value, localsEntry)) return;
	}
	else if (HBlockToDecide dcMatch = asHBlockToDecide(p)) {
		if (assert_decideBlock(dcMatch)) return;

	}
	if (HBlockVerbRelation dcverbImpl = asHBlockVerbRelation(p))
	{
		if (assert_newVerb(dcverbImpl)) return;
	}


	if (HBlockUnderstandDynamic    dn_dispatch = asHBlockUnderstandDynamic(p))
	{
		if (assert_newUnderstand(dn_dispatch)) return;

	}

	if (HBlockRelationBase    dn_relation = asHBlockRelationBase(p))
	{
		if (assert_newRelation(dn_relation)) return;

	}
	if (HBlockVerb    reg_verb = asHBlockVerb(p))
	{
		if (insert_newVerb(reg_verb)) return;

	}

	if (HBlockPhraseDefine    reg_phrase = asHBlockPhraseDefine(p))
	{
		if (insert_newPhrase(reg_phrase)) return;

	}


	if (HBlockEventHandle    reg_event_handle = asHBlockEventHandle(p))
	{
		if (insert_newEventHandle(reg_event_handle)) return;

	}


	if (HBlockUnitInit   unit_init = asHBlockUnitInit(p))
	{
		this->add_new_init(unit_init);
		return;
	}

	if (HBlockUnitTest  unit_test = asHBlockUnitTest(p))
	{
		this->add_new_test(unit_test);
		return;
	}
	if (HBlockUnitAssert  unit_assert = asHBlockUnitAssert(p))
	{
		this->add_new_assertion(unit_assert);
		return;
	}

	p->dump("");
	logError("not found block definition ");

	return;
}
