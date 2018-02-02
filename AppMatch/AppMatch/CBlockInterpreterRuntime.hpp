 #pragma once

#ifndef CBLOCKRUNTIME_H
#define CBLOCKRUNTIME_H


#include "BlockInterpreter.hpp"
#include "CblockAssertion.hpp"
#include "CBlockMatch.hpp"
#include <functional> 
#include <map>
#include "CBlockUndestand.hpp"
#include <condition_variable>
#include "CBlockDecideIf.hpp"
#include "CBlockScope.hpp"
#include <condition_variable>
#include "CBlockAction.hpp"
#include "CBlockRelation.hpp"
#include "QueryStack.hpp"
#include "CBlockCommand.hpp"
#include "CBlockMatch.hpp"
#include "EqualsResult.hpp"

//class CBlockAssertionBase;
//class CBlockAssertion_is;
//using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;
//using HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;


class CResultMatch;

using namespace  CBlocking;
 

namespace Interpreter
{
	void assert_batch_kinds(HBlockList &nList, HBlockKindOfName &k);
class PhaseResult
{
public:
	PhaseResult(bool _hasExecuted);
	bool hasExecuted;
	 HBlock result;
};


class QueryResultContext // resultado da query incluindo variaveis do Match
{
public:
	const QueryResul result;
	std::map<string, HBlock> matchedResult;
	QueryResultContext(QueryResul r);
	QueryResultContext(QueryResul r, std::map<string, HBlock> _matchedResult);
	//QueryResultContext(QueryResul r, std::list< std::pair<string, HBlock> > _locals);
	QueryResultContext(QueryResul r, std::map<string, HBlock> _matchedResult_A, std::map<string, HBlock> _matchedResult_B);

	void dump();
};

 
struct  NamedValue
{
	string named;
	HBlock value;
};
 

class SentenceBlock
{
public:
	SentenceBlock(bool inner, const std::string& text)
		: inner(inner),
		text(text)
	{
	}

	bool inner;
	std::string text;
};



using ListOfNamedValue = std::list<NamedValue>;


	class CBlockInterpreter {

		std::vector<HBlock> program; // main program .. to run IT

		std::list< std::pair<string, HBlock> > symbols;

		std::list<HBlockActionNamed>  system_actions;


		std::vector<HBlockInstance> instancias;

		std::vector<HBlockInstanceVariable> instancias_vars;
		std::vector<HBlockAssertionBase> assertions_functional; //To define and others


		std::vector<NoumDefinition> nregisters;
		std::vector<HBlockAssertion_is> assertions;

		//Phases
		std::list<HBlockPhraseDefine> phrases;

		//Relations
		std::map<string, HBlockRelationBase > staticRelation;
		std::list<HBlockRelationInstance > relInstances;


		//Verb to relation
		std::list<  HBlockVerb > verbs;
		std::map<string, HBlockVerbRelation > verbRelationAssoc;
		std::map<string, std::list<HBlockAssertion_is> > verbAssertation;


		std::vector<HBlockAssertionBase> dynamic_assertions;
		std::vector<HBlockNoum> registred_adjetives;
		std::vector<HBlockAssertion_is> kindDefinitions;
		std::vector<VariableSloting::HVariableNamed> global_variables;
		
		std::vector<HBlockAssertion_isConstantAssign>  constant_assignments;
		std::vector<HBlockAssertion_isForbiddenAssign>  forbiden_assignments;
		std::vector<HBlockAssertion_isDefaultAssign> default_assignments;
		std::vector<HBlockAssertionBase> instance_variables;
		std::vector<HBlockAssertionBase> kind_variables;
		std::vector<HBlockKind_InstanceVariable> kind_named_variables;







		//Decides
		std::vector<HBlockToDecideWhat> decides_what;
		std::vector<HBlockToDecideWhether> decides_whether;
		std::vector<HBlockToDecideIf> decides_if;
		std::vector<HBlockToDecideWhat_FirstNoum> decides_noum1;


		//std::vector<HBlockAction> actions_header;
		
		std::list<HBlockActionNamed > actions_definitions; //cada acao com o mesmo nome pode ter varias instancias, OVERLOAD baby !

		std::vector<HBlockUnderstandDynamic> dynamic_understand;

		//Plural
		std::list<  std::pair< HBlockNoum, HBlockNoum > > plural_assertations;



		//Event handles
		std::vector<HBlockEventHandle> event_handles;
		int instancia_id;
		HBlockNothing Nothing;
		HBlockAnything Anything;

		HBlockKind MetaKind;
		HBlockKind MetaKindEntity;
		HBlockKind MetaKindRelation;
		HBlockKind MetaKindPhrase;
		HBlockKind MetaKindBoolean;
		HBlockKind MetaKindAction;
		HBlockKind MetaKindList;
		HBlockKind MetaKindText;

		HBlockKind MetaKindAny;
		std::function<bool(std::string)>  say_output;


		//if (asHBlockText(c)) return true;
		//if (asHBlockNothing(c)) return true;
		//if (asHBlockBooleanValue(c)) return true;
		//if (asHBlockList(c)) return true;
		//if (asHBlockInstance(c)) return true;
		//if (asHBlockRelationBase(c)) return true;
		//if (asHBlockAction(c)) return true;
		//if (asHBlockNamedValue(c)) return true;



		QueryResultContext query_is_instance_valueSet(HBlock c_block, HBlock c_block1, QueryStacking::QueryStack *stk);
		HBlock resolve_by_evaluation(HBlock c_block,   HRunLocalScope localsEntry, QueryStacking::QueryStack * stk_in);
		QueryResultContext query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		QueryResultContext query_is_propertyOf_value(HBlock c_property, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_is_Variable_value(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		//QueryResultContext query_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query(HBlockAssertion_is q, HBlockAssertion_is base, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		// QueryResul queryVerb(string vb, HBlock c_block, HBlock value, QueryStacking::QueryStack *stk);


		std::list<HBlockKind> getUpperKinds(HBlockKind kind);
		bool is_derivadeOf(HBlockInstance a, HBlockKind b, HRunLocalScope localsEntry);

		bool is_InstanceOf(HBlock a, HBlockKind b);

		void dump_instance(string str, HRunLocalScope localsEntry);
		void add_constantValueVariableToAllinstances(HBlockAssertion_isConstantAssign kvar);
		void add_defaultValueVariableToAllinstances(HBlockAssertion_isDefaultAssign hdefault);
		void add_forbidenValueVariableToAllinstances(HBlockAssertion_isForbiddenAssign kvar);

		void add_namedVariableToAllinstances(HBlockKind_InstanceVariable variable_);
		HBlockInstance new_Instance(string named, HBlockKind kind);

		void assign_variable_to_instance(HBlockAssertionBase kvar);
		HBlockList lookup_relation_List(const string& relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		
		HBlock lookup_relation_X_Y_1(const string& relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlock lookup_relation_X_Y_2(const string& relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlock lookup_relation_XS_Y_1(const string& relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlock lookup_relation_X_YS_2(const string& relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		CBlocking::HBlock get_property_by_relation(HBlockNoum propNamed, HBlock obj, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		bool set_property_by_relation(HBlockNoum propNamed, HBlock obj, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlock lookup_relation(HBlockRelationLookup rLookup, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_lookup_relation(HBlock value, HBlockRelationLookup rLookup, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlock lookup_union(HBlock v1, HBlock v2, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlock lookup_intersection(HBlock v1, HBlock v2, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlock lookup_verb(HBlockVerbLookup vLookup, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		std::list<string> getAllRegistedEnums();
		std::list<string> getAllRegistedKinds();
		HBlockList lookup_value_by_Selector(HBlockMatch valueToMatch, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlockList lookup_verb_List(HBlockVerbLookup vLookup, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
	 
 
		bool exist_relation(string relationNamed, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool setVerbRelation(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
 
		bool setVerb(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_relation_instance(HBlockRelationInstance rr, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_relation_property(HBlockNoum property_noum, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_relation(HBlockRelationBase rel, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_user_verbs(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);


		bool isReservedWord(string cs);
		bool existSymbol(string cs);
		void addSymbol(string cs, HBlock  value);
		bool assert_newVerb(HBlockVerbRelation value);
		bool insert_newEventHandle(HBlockEventHandle event_handle);
		bool assert_it_variableGlobal(HBlock obj, HBlock baseKind, HBlock defaultValue);

		CResultMatch MatchList(HBlockMatchList M, HBlockList value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		CResultMatch isEquivalenteMatch(HBlockMatch M, HBlockMatch mValue, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		CResultMatch Match_DirectIs(HBlockMatch mObject, HBlockMatch mValue, HBlock object, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		CResultMatch MatchListCombinaria(HBlockMatchList Ms, HBlockNoum n, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		CResultMatch Match(HBlockMatch M, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);


		QueryResultContext queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		bool is_nothing(HBlockNoum noum);
		bool is_nothing(HBlock noum_);
		bool set_relation_property(HBlockNoum property_noum, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool set_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool unset_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		string adapt_verb_inner_inner(const string& verb, string tense, string person, HRunLocalScope localsEntry);
		string adapt_verb_inner(const string& verb, string tense, string person, HRunLocalScope localsEntry);
		HBlockNoum adapt_verb(HBlockVerbAdapt nVerbAdp, HRunLocalScope localsEntry);
		HBlockNoum adapt_negate_verb(HBlockVerbNegate negVerbAdp, HRunLocalScope localsEntry);


		string getStringPrexfedFromList(const std::vector<string>& noumFragmented, std::list<string> allStringNames);
		std::list<HBlock> getInstancesFromKind(HBlockKind kind, HRunLocalScope localsEntry);
		std::list<HBlock> getInstancesFromSelector(HBlockMatch seletor, HRunLocalScope localsEntry);

		HBlockMatch Resolve_Selector_item(HBlockMatch seletor, std::list<string>& allKindsNames, std::list<string> &allEnumNames , HRunLocalScope localsEntry);

		HBlockMatch Resolve_Selector_Noum_fragment(std::vector<string> strList_in, std::list<string>& allKindsNames, std::list<string>& allEnumNames, HRunLocalScope localsEntry);

		HBlockMatch Resolve_Selector_NoumList(std::vector<string> strList, std::list<string>& allKindsNames, std::list<string>& allEnumNames, HRunLocalScope localsEntry);

		HBlockMatch Resolve_Selector_List(HBlockMatchList mList, std::list<string>& allKindsNames, std::list<string> &allEnumNames , HRunLocalScope localsEntry);
		 
		 
		HBlockMatch Resolve_Selector(HBlockMatch seletor, HRunLocalScope localsEntry);
		PhaseResult raise_runtime_error(std::string message);
	public:

		std::list<HBlockRelationInstance > getRelations();

		CBlockInterpreter();

		~CBlockInterpreter();

		void initialize();
		void add_modifier_keyword(HBlockEnums _enums);
		void add_modifier_keyword(HBlockNoum _nn);
		bool assert_it_canBe(HBlock c_block, HBlockEnums value, HRunLocalScope localsEntry);


		void dump_instance(string str);
		bool assert_newUnderstand(HBlockUnderstandDynamic value);

		bool assert_newRelation(HBlockRelationBase rel);

		bool assert_it_property(HBlock propname, HBlock obj, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		bool assert_it_not_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		void execute_init(HBlock p);

		bool assert_decideBlock(HBlockToDecide dct);
		bool assert_has_variable(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		bool is_all_items_of_kind(HBlockList listvalues, HBlockKind kind, HRunLocalScope localsEntry);
		bool kind_has_property_called_inner(HBlockKind kind, string propertyNamed, std::list< CBlockKind* > kindsUsed);
		bool kind_has_property_called(HBlockKind kind, const string& propertyNamed);

		bool assert_property_ForbiddenValue(HBlockProperty prop, HBlock value, HRunLocalScope localsEntry);

		bool assert_property_ConstantValue(HBlockProperty prop, HBlock value, HRunLocalScope localsEntry);

		 
	 
		bool assert_property_defaultValue(HBlockProperty prop, HBlock value, HRunLocalScope localsEntry);
		bool assert_it_ConstantAssign(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		bool assert_it_ForbiddenValue(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		bool assert_it_defaultValue(HBlock obj, HBlock value, HRunLocalScope localsEntry);







		bool assert_it_action(HBlock obj, HBlock value);

		void assert_batch_kinds(std::list<HBlock>& nList, HBlockKindOfName & k);
		 
		 
		bool assert_it_kind(HBlock obj, HBlock value, HRunLocalScope localsEntry);


		std::pair<HBlockKind, HBlockKind> create_derivadeKind(string called, string baseName);
		bool assert_assertation(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		bool  assert_it_composition(HBlock obj, HBlock  value, HRunLocalScope localsEntry);
		bool assert_it_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry);

		bool assert_it_instance(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		bool assert_it_valuesDefinitions_list(HBlock c_block, std::list<HBlock> values, HRunLocalScope localsEntry);
		 
		bool assert_it_valuesDefinitions(HBlock c_block, HBlock value, HRunLocalScope localsEntry);

		HBlockKind  resolve_comp_kind(HBlockKind obj, HRunLocalScope localsEntry);

		std::list<HBlock> resolve_as_list(HBlock qlist, HRunLocalScope localsEntry);
		std::list<HBlock> resolve_as_list(HBlock qlist, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		HBlockKind getKindOf(HBlockInstance obj);
		string BlockNoum(HBlock c_block);
		// bool MatchOld(HBlock c_block, HBlockMatch m);
		HBlock getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecideWhether dct);
		HBlock getDecidedValueOf(HBlock c_block, HBlockToDecideWhat dct, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext getDecidedValue(HBlock decideBody, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);		
		QueryResultContext getDecidedValue(HBlock decideBody, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext getDecidedIf(HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);


		QueryResultContext Selector_all(HBlock aList, HRunLocalScope localsEntry, std::function<QueryResultContext(HBlock)> selector);
		QueryResultContext Selector_any(HBlock aList, HRunLocalScope localsEntry, std::function<QueryResultContext(HBlock)> selector);
		QueryResultContext get_system_verbs(string cs, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_verb_innn(string verb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk_in);
		QueryResultContext query_verb(HBlockIsVerb is_verb, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_not_verb(HBlockIsNotVerb is_verb, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query_decides(HBlock q, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		
		bool assert_it_verbRelation(std::string verbNamed, HBlock obj, HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool insert_newPhrase(HBlockPhraseDefine phrase_dec);
		bool insert_newVerb(HBlockVerb verb_dec);


		QueryResultContext query_comp(string cs, HBlock vr1, HBlock vr2, HRunLocalScope shared_ptr, QueryStacking::QueryStack* stk);
		QueryResultContext query(HBlock q, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		QueryResultContext query(HBlock  vquery);
		QueryResultContext query_direct_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk_in);
		QueryResultContext query_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);


		std::list<HBlockVerbConjugation> get_verb_conjugations(std::string verb) const;
		HBlockNoum get_verbal_regarding(string verb, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlockNoumSupl resolve_number_gender(string  n, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlockNoumSupl textual_representation(HBlock x, string person, string number, string gender, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlockText adapt_text(HBlockTextSentence text, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);


	   NSTerm::HTerm executeAssertion_is(HBlockAssertion_is b);

	   NSTerm::HTerm executeAssertion(HBlockAssertionBase b);

	   NSTerm::HTerm execute(HBlock b);

		HBlock resolve(NSTerm::CTerm *b);

		HBlock resolve_of(HBlock b, HBlock a);
		HBlockKind resolve_system_kind(string n);
		HBlockKind resolve_user_kind(string n);


		bool is_derivadeOf(HBlockKind a, HBlockKind b);



		HBlockKind resolve_kind(string n);
		HBlock resolve_if_noum(HBlock n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		HBlock resolve_noum(HBlockNoum n, HRunLocalScope localsEntry);
		HBlock has_resolve_noum(HBlockNoum n, HRunLocalScope localsEntry);
		HBlock resolve_noum(HBlockNoum n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		HBlock has_resolve_noum(HBlockNoum n, HRunLocalScope localsEntry, std::list<std::string> noumsToResolve);
		HBlock resolve_string_noum(string named, HRunLocalScope localsEntry, std::list<std::string> noumsToResolve);
		HBlock has_resolve_string_noum(string named, HRunLocalScope localsEntry, std::list<std::string> noumsToResolve);
		HBlock resolve_noum_as_variable(HBlockNoum n);
		HBlock resolve_string(string n, HRunLocalScope localsEntry);

		//HBlock resolve_value(HBlock  c_block);




		HBlock value_can_be_assign_to(HBlock value, HBlockKind kind, HRunLocalScope localsEntry);
		bool set_plural_property(HBlock noum_singular, HBlock noum_plural, HRunLocalScope localsEntry);
		
		QueryResultContext query_is_List(CBlock *c_block, CBlock *c_block1);



		QueryResultContext query_is_extern(HBlock c_block, HBlock c_block1);
		bool is_primitive_value(HBlock c, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		QueryResultContext query_is_same(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		std::list<HBlock> getMatchedObjects(HBlock seletor, HRunLocalScope localsEntry);
		bool is_valid_for_relation_kind(HBlock baseType, HBlock object, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		PhaseResult execute_verb_set_inn(HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		PhaseResult execute_verb_set(HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		//bool set_relation(HBlockRelationBase relation , HBlock n1, HBlock n2);
 
	 
		PhaseResult execute_verb_unset(HBlockIsNotVerb vverb, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_unset(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		PhaseResult execute_set_inn(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		PhaseResult execute_set(HBlock obj, HBlock value, HRunLocalScope localsEntry);
		HBlock exec_eval_property_value_imp(HBlock prop, HBlock c_block);
		HBlock exec_eval_property_value(HBlock c_block, HRunLocalScope localsEntry);
		HBlock exec_eval_assertations(HBlock c_block, HRunLocalScope localsEntry, std::function<HBlock(HBlock)> is_accetable);		
		HBlock get_default_property_value(HBlockNoum c_value, HBlockInstance c_obj, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		 
		HBlock exec_eval(HBlock c_block, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool assert_equals(HBlock c_block, HBlock c_result);
		HBlock eval_boolean_AND(HBlock c1, HBlock c2);
		HBlock eval_boolean_OR(HBlock c1, HBlock c2);
		HBlock eval_boolean_NOT(HBlock c1);
		HBlock exec_eval_internal_boolean_relation(HBlock c_block, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		bool existe_relation_property(HBlockNoum property_noum, HBlock obj);
		HBlock eval_relation_property(HBlockNoum propNoum, HBlock obj, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlock eval_property(HBlockProperty pblock, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlock get_PropertyOfKind_DefaultValue(HBlockProperty kprop, HBlock c_block, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		HBlock disptch_action_call(HBlockPhraseInvoke phr, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlock exec_eval_internal(HBlock c_block, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlock resolve_as_callCommand(HBlock c_block, HRunLocalScope shared_ptr);
		HExecutionBlock create_dispach_env(HBlockList p, HRunLocalScope localsEntry);



		PhaseResult execute_now(HBlock c_block);
		PhaseResult execute_phase_any(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_phase_any(HBlockEventHandle evh, HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_phase_check(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_phase_before(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_phase_carryOut(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		PhaseResult execute_system_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
 
		PhaseResult execute_user_action(HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlockActionCallNamed replaceByUndestandAction(HBlockActionCallNamed v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack * stk);
		PhaseResult execute_user_action(HBlockActionCallNamed v_call, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);

		//Executa este bloco !
		PhaseResult execute_now(HBlock p, HRunLocalScope localsEntry);
		ListOfNamedValue getValuesFromMatch(HBlock c_block, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlockMatch  resolve_argument_match(HBlock  value, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		HBlock resolve_argument(HBlock value, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		HBlockActionCall ActionResolveArguments(HBlockActionCall vCall, HRunLocalScope localsEntry, QueryStacking::QueryStack* stk);
		PhaseResult execute_now(HBlock p, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk);
		bool queryIsVerbToRelation(HBlockMatch m);
		void logMessage(const string& msg);


	 

		HBlock evaluate_relation_property(HBlock c_block, HBlockNoum property_noum, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk, std::function<HBlock(HBlock, HRunLocalScope, QueryStacking::QueryStack*)> isSuitable);
		HBlock evaluate_propertyValue(HBlockProperty cproperty, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk, std::function<HBlock(HBlock, HRunLocalScope, QueryStacking::QueryStack*)> isSuitable);
		HBlock evaluate_values(HBlock q, HRunLocalScope localsEntry, QueryStacking::QueryStack *stk, std::function<HBlock(HBlock, HRunLocalScope, QueryStacking::QueryStack*)> isSuitable);
		HBlock evaluate_values(HBlock c_block);

		HBlockNoum get_plural_of(string s);
		bool isSameString(string s1, string s2);
	};

	using  HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;


	//Aux 


 

};
 
#endif
