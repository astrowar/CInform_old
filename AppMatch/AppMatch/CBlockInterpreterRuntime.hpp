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
//using CBlocking::HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;
//using CBlocking::HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;


class CResultMatch;

namespace Interpreter
{
class PhaseResult
{
public:
	PhaseResult(bool _hasExecuted);
	bool hasExecuted;
	 CBlocking::HBlock result;
};


class QueryResultContext // resultado da query incluindo variaveis do Match
{
public:
	const QueryResul result;
	std::map<string, CBlocking::HBlock> matchedResult;
	QueryResultContext(QueryResul r);
	QueryResultContext(QueryResul r, std::map<string, CBlocking::HBlock> _matchedResult);
	//QueryResultContext(QueryResul r, std::list< std::pair<string, CBlocking::HBlock> > _locals);
	QueryResultContext(QueryResul r, std::map<string, CBlocking::HBlock> _matchedResult_A, std::map<string, CBlocking::HBlock> _matchedResult_B);

	void dump();
};

 
struct  NamedValue
{
	string named;
	CBlocking::HBlock value;
};
 

using ListOfNamedValue = std::list<NamedValue>;


	class CBlockInterpreter {

		std::vector<CBlocking::HBlock> program; // main program .. to run IT


		std::vector<CBlocking::HBlockInstance> instancias;
		std::vector<CBlocking::HBlockInstanceVariable> instancias_vars;
		std::vector<CBlocking::HBlockAssertionBase> assertions_functional; //To define and others


		std::vector<CBlocking::NoumDefinition> nregisters;
		std::vector<CBlocking::HBlockAssertion_is> assertions;

		//Relations
		std::map<string, CBlocking::HBlockRelationBase > staticRelation;
		std::list<CBlocking::HBlockRelationInstance > relInstances;


		//Verb to relation
		std::list<  CBlocking::HBlockVerb > verbs;
		std::map<string, CBlocking::HBlockVerbRelation > verbRelationAssoc;
		std::map<string, std::list<CBlocking::HBlockAssertion_is> > verbAssertation;


		std::vector<CBlocking::HBlockAssertionBase> dynamic_assertions;


		std::vector<CBlocking::HBlockAssertion_is> kindDefinitions;

		std::vector<HVariableNamed> global_variables;

		std::vector<CBlocking::HBlockAssertion_isDefaultAssign> default_assignments;
		std::vector<CBlocking::HBlockAssertionBase> instance_variables;
		std::vector<CBlocking::HBlockAssertionBase> kind_variables;
		std::vector<CBlocking::HBlockKind_InstanceVariable> kind_named_variables;

		//Decides
		std::vector<CBlocking::HBlockToDecideWhat> decides_what;
		std::vector<CBlocking::HBlockToDecideWhether> decides_whether;
		std::vector<CBlocking::HBlockToDecideIf> decides_if;
		std::vector<CBlocking::HBlockToDecideWhat_FirstNoum> decides_noum1;


		std::vector<CBlocking::HBlockAction> actions_header;
		std::map<std::string, CBlocking::HBlockKindAction > actions_parameters;
		std::vector<CBlocking::HBlockUnderstandDynamic> dynamic_understand;

		//Plural
		std::list<  std::pair< CBlocking::HBlockNoum, CBlocking::HBlockNoum > > plural_assertations;



		//Event handles
		std::vector<CBlocking::HBlockEventHandle> event_handles;
		int instancia_id;


		QueryResultContext query_is_instance_valueSet(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, QueryStack *stk);
		QueryResultContext query_is_propertyOf_value_imp(CBlocking::HBlock propname, CBlocking::HBlock propObj, CBlocking::HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk);

		QueryResultContext query_is_propertyOf_value(CBlocking::HBlock c_property, CBlocking::HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_is_Variable_value(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk);

		QueryResultContext query_is(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query(CBlocking::HBlockAssertion_is q, CBlocking::HBlockAssertion_is base, HRunLocalScope localsEntry, QueryStack *stk);

		// QueryResul queryVerb(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, QueryStack *stk);


		std::list<CBlocking::HBlockKind> getUpperKinds(CBlocking::HBlockKind kind);
		bool is_derivadeOf(CBlocking::HBlockInstance a, CBlocking::HBlockKind b, HRunLocalScope localsEntry);

		void dump_instance(string str, HRunLocalScope localsEntry);
		void add_defaultValueVariableToAllinstances(CBlocking::HBlockAssertion_isDefaultAssign hdefault);
		void add_namedVariableToAllinstances(CBlocking::HBlockKind_InstanceVariable variable_);
		CBlocking::HBlockInstance new_Instance(string named, CBlocking::HBlockKind kind);

		void assign_variable_to_instance(CBlocking::HBlockAssertionBase kvar);
		CBlocking::HBlockList lookup_relation_List(const string& relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		
		CBlocking::HBlock lookup_relation_X_Y_1(const string& relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack* stk);
		CBlocking::HBlock lookup_relation_X_Y_2(const string& relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock lookup_relation_XS_Y_1(const string& relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock lookup_relation_X_YS_2(const string& relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock lookup_relation(CBlocking::HBlockRelationLookup rLookup, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock lookup_verb(CBlocking::HBlockVerbLookup vLookup, HRunLocalScope localsEntry, QueryStack *stk);
		std::list<string> getAllRegistedKinds();
		CBlocking::HBlockList lookup_value_by_Selector(CBlocking::HBlockMatch valueToMatch, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlockList lookup_verb_List(CBlocking::HBlockVerbLookup vLookup, HRunLocalScope localsEntry, QueryStack *stk);
	 
 
		bool exist_relation(string relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		bool setVerbRelation(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
 
		bool setVerb(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_relation_instance(CBlocking::HBlockRelationInstance rr, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_relation_property(CBlocking::HBlockNoum property_noum, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_relation(CBlocking::HBlockRelationBase rel, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_user_verbs(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);


		bool assert_newVerb(CBlocking::HBlockVerbRelation value);
		bool insert_newEventHandle(CBlocking::HBlockEventHandle event_handle);
		bool assert_it_variableGlobal(CBlocking::HBlock obj, CBlocking::HBlock value);

		CResultMatch MatchList(CBlocking::HBlockMatchList M, CBlocking::HBlockList value, HRunLocalScope localsEntry, QueryStack *stk);
		CResultMatch isEquivalenteMatch(CBlocking::HBlockMatch M, CBlocking::HBlockMatch mValue, HRunLocalScope localsEntry, QueryStack *stk);
		CResultMatch Match_DirectIs(CBlocking::HBlockMatch mObject, CBlocking::HBlockMatch mValue, CBlocking::HBlock object, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		CResultMatch Match(CBlocking::HBlockMatch M, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);


		QueryResultContext queryVerb_ListedIn(CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry, QueryStack *stk);

		bool is_nothing(CBlocking::HBlockNoum noum);
		bool set_relation_property(CBlocking::HBlockNoum property_noum, CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry, QueryStack *stk);
		bool set_relation(CBlocking::HBlockRelationBase relation, CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry, QueryStack *stk);
		bool unset_relation(CBlocking::HBlockRelationBase relation, CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry, QueryStack *stk);
		
		string adapt_verb_inner(const string& verb, string tense, string person, HRunLocalScope localsEntry);
		CBlocking::HBlockNoum adapt_verb(CBlocking::HBlockVerbAdapt nVerbAdp, HRunLocalScope localsEntry);
		
		string getStringPrexfedFromList(const std::vector<string>& noumFragmented, std::list<string> allStringNames);
		std::list<CBlocking::HBlock> getInstancesFromKind(CBlocking::HBlockKind kind, HRunLocalScope localsEntry);
		std::list<CBlocking::HBlock> getInstancesFromSelector(CBlocking::HBlockMatch seletor, HRunLocalScope localsEntry);
		CBlocking::HBlockMatch Resolve_Selector(CBlocking::HBlockMatch seletor, HRunLocalScope localsEntry);
	public:

		std::list<CBlocking::HBlockRelationInstance > getRelations();

		CBlockInterpreter();

		~CBlockInterpreter();

		void initialize();
		bool assert_it_canBe(CBlocking::HBlock c_block, CBlocking::HBlockEnums value, HRunLocalScope localsEntry);


		void dump_instance(string str);
		bool assert_newUnderstand(CBlocking::HBlockUnderstandDynamic value);

		bool assert_newRelation(CBlocking::HBlockRelationBase rel);

		bool assert_it_property(CBlocking::HBlock propname, CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);

		bool assert_it_not_Value(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		void execute_init(CBlocking::HBlock p);

		bool assert_decideBlock(CBlocking::HBlockToDecide dct);
		bool assert_has_variable(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		bool is_all_items_of_kind(CBlocking::HBlockList listvalues, CBlocking::HBlockKind kind, HRunLocalScope localsEntry);
		bool kind_has_property_called_inner(CBlocking::HBlockKind kind, string propertyNamed, std::list<std::basic_string<char>> kindsUsed);
		bool kind_has_property_called(CBlocking::HBlockKind kind, const string& propertyNamed);
	 
		bool assert_property_defaultValue(CBlocking::HBlockProperty prop, CBlocking::HBlock value, HRunLocalScope localsEntry);
		bool assert_it_defaultValue(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);







		bool assert_it_action(CBlocking::HBlock obj, CBlocking::HBlock value);
		bool assert_it_kind(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);


		std::pair<CBlocking::HBlockKind, CBlocking::HBlockKind> create_derivadeKind(string called, string baseName);
		bool assert_assertation(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		bool assert_it_Value(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);

		bool assert_it_instance(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		bool assert_it_valuesDefinitions(CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry);


		std::list<CBlocking::HBlock> resolve_as_list(CBlocking::HBlock qlist, HRunLocalScope localsEntry);
		std::list<CBlocking::HBlock> resolve_as_list(CBlocking::HBlock qlist, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		CBlocking::HBlockKind getKindOf(CBlocking::HBlockInstance obj);
		string BlockNoum(CBlocking::HBlock c_block);
		// bool MatchOld(CBlocking::HBlock c_block, CBlocking::HBlockMatch m);
		CBlocking::HBlock getDecidedWhether(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, CBlocking::HBlockToDecideWhether dct);
		CBlocking::HBlock getDecidedValueOf(CBlocking::HBlock c_block, CBlocking::HBlockToDecideWhat dct, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext getDecidedValue(CBlocking::HBlock decideBody, HRunLocalScope localsEntry, QueryStack *stk);		
		QueryResultContext getDecidedValue(CBlocking::HBlock decideBody, CBlocking::HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext getDecidedIf(CBlocking::HBlock c_block, CBlocking::HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack *stk);


		QueryResultContext Selector_all(CBlocking::HBlock aList, HRunLocalScope localsEntry, std::function<QueryResultContext(CBlocking::HBlock)> selector);
		QueryResultContext Selector_any(CBlocking::HBlock aList, HRunLocalScope localsEntry, std::function<QueryResultContext(CBlocking::HBlock)> selector);
		QueryResultContext get_system_verbs(string cs, CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_verb(CBlocking::HBlockIsVerb is_verb, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_not_verb(CBlocking::HBlockIsNotVerb is_verb, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query_decides(CBlocking::HBlock q, HRunLocalScope localsEntry, QueryStack *stk);
		
		bool assert_it_verbRelation(std::string verbNamed, CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk);
		bool insert_newVerb(CBlocking::HBlockVerb verb_dec);



		QueryResultContext query(CBlocking::HBlock q, HRunLocalScope localsEntry, QueryStack *stk);
		QueryResultContext query(CBlocking::HBlock  vquery);






	   NSTerm::HTerm executeAssertion_is(CBlocking::HBlockAssertion_is b);

	   NSTerm::HTerm executeAssertion(CBlocking::HBlockAssertionBase b);

	   NSTerm::HTerm execute(CBlocking::HBlock b);

		CBlocking::HBlock resolve(NSTerm::CTerm *b);

		CBlocking::HBlock resolve_of(CBlocking::HBlock b, CBlocking::HBlock a);
		CBlocking::HBlockKind resolve_system_kind(string n);
		CBlocking::HBlockKind resolve_user_kind(string n);


		bool is_derivadeOf(CBlocking::HBlockKind a, CBlocking::HBlockKind b);



		CBlocking::HBlockKind resolve_kind(string n);
		CBlocking::HBlock resolve_if_noum(CBlocking::HBlock n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		CBlocking::HBlock resolve_noum(CBlocking::HBlockNoum n, HRunLocalScope localsEntry);
		CBlocking::HBlock resolve_noum(CBlocking::HBlockNoum n, HRunLocalScope localsEntry, std::list<std::string>  noumsToResolve);
		CBlocking::HBlock resolve_string_noum(string named, HRunLocalScope localsEntry, std::list<std::string> noumsToResolve);
		CBlocking::HBlock resolve_noum_as_variable(CBlocking::HBlockNoum n);
		CBlocking::HBlock resolve_string(string n, HRunLocalScope localsEntry);

		//CBlocking::HBlock resolve_value(CBlocking::HBlock  c_block);




		CBlocking::HBlock value_can_be_assign_to(CBlocking::HBlock value, CBlocking::HBlockKind kind, HRunLocalScope localsEntry);
		bool set_plural_property(CBlocking::HBlock noum_singular, CBlocking::HBlock noum_plural, HRunLocalScope localsEntry);
		
		QueryResultContext query_is_List(CBlocking::CBlock *c_block, CBlocking::CBlock *c_block1);



		QueryResultContext query_is_extern(CBlocking::HBlock c_block, CBlocking::HBlock c_block1);
		QueryResultContext query_is_same(CBlocking::HBlock c_block, CBlocking::HBlock c_block1, HRunLocalScope localsEntry, QueryStack *stk);
		std::list<CBlocking::HBlock> getMatchedObjects(CBlocking::HBlock seletor, HRunLocalScope localsEntry);
		PhaseResult execute_verb_set(CBlocking::HBlockIsVerb vverb, HRunLocalScope localsEntry, QueryStack *stk);
		//bool set_relation(CBlocking::HBlockRelationBase relation , CBlocking::HBlock n1, CBlocking::HBlock n2);
 
	 
		PhaseResult execute_verb_unset(CBlocking::HBlockIsNotVerb vverb, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_unset(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		PhaseResult execute_set(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry);
		CBlocking::HBlock exec_eval_property_value_imp(CBlocking::HBlock prop, CBlocking::HBlock c_block);
		CBlocking::HBlock exec_eval_property_value(CBlocking::HBlock c_block, HRunLocalScope localsEntry);
		CBlocking::HBlock exec_eval_assertations(CBlocking::HBlock c_block, HRunLocalScope localsEntry, std::function<CBlocking::HBlock(CBlocking::HBlock)> is_accetable);
		CBlocking::HBlock exec_eval(CBlocking::HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock exec_eval_internal(CBlocking::HBlock c_block, HRunLocalScope localsEntry, QueryStack* stk);
		CBlocking::HBlock resolve_as_callCommand(CBlocking::HBlock c_block, HRunLocalScope shared_ptr);
		HExecutionBlock create_dispach_env(CBlocking::HBlockList p, HRunLocalScope localsEntry);



		PhaseResult execute_now(CBlocking::HBlock c_block);
		PhaseResult execute_phase_any(CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_phase_any(CBlocking::HBlockEventHandle evh, CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_phase_check(CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_phase_before(CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_phase_carryOut(CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);
		PhaseResult execute_system_action(CBlocking::HBlockActionCall v_call);
		PhaseResult  execute_user_action(CBlocking::HBlockActionCall v_call, HRunLocalScope localsEntry, QueryStack *stk);

		//Executa este bloco !
		PhaseResult execute_now(CBlocking::HBlock p, HRunLocalScope localsEntry);
		ListOfNamedValue getValuesFromMatch(CBlocking::HBlock c_block, HRunLocalScope localsEntry, QueryStack *stk);
		CBlocking::HBlock resolve_argument(CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack* stk);
		CBlocking::HBlockActionCall ActionResolveArguments(CBlocking::HBlockActionCall vCall, HRunLocalScope localsEntry, QueryStack* stk);
		PhaseResult execute_now(CBlocking::HBlock p, HRunLocalScope localsEntry, QueryStack *stk);
		bool queryIsVerbToRelation(CBlocking::HBlockMatch m);
		void logMessage(const string& msg);


	 

		CBlocking::HBlock evaluate_relation_property(CBlocking::HBlock c_block, CBlocking::HBlockNoum property_noum, HRunLocalScope localsEntry, QueryStack *stk, std::function<CBlocking::HBlock(CBlocking::HBlock, HRunLocalScope, QueryStack*)> isSuitable);
		CBlocking::HBlock evaluate_propertyValue(CBlocking::HBlockProperty cproperty, HRunLocalScope localsEntry, QueryStack *stk, std::function<CBlocking::HBlock(CBlocking::HBlock, HRunLocalScope, QueryStack*)> isSuitable);
		CBlocking::HBlock evaluate_values(CBlocking::HBlock q, HRunLocalScope localsEntry, QueryStack *stk, std::function<CBlocking::HBlock(CBlocking::HBlock, HRunLocalScope, QueryStack*)> isSuitable);
		CBlocking::HBlock evaluate_values(CBlocking::HBlock c_block);

		CBlocking::HBlockNoum get_plural_of(string s);
		bool isSameString(string s1, string s2);
	};

	using  HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;


	//Aux 


 

};
 
#endif