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

 class CBlockAssertionBase;

class CBlockAssertion_is;

using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;
using HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;




class CResultMatch;

class CBlockInterpreter {

    std::vector<HBlock> program; // main program .. to run IT


    std::vector<HBlockInstance> instancias;
    std::vector<HBlockInstanceVariable> instancias_vars;
    std::vector<HBlockAssertionBase> assertions_functional; //To define and others


    std::vector<NoumDefinition> nregisters;
    std::vector<HBlockAssertion_is> assertions;

//Relations
	std::map<string, HBlockRelationBase > staticRelation;
    std::list<HBlockRelationInstance > relInstances;


//Verb to relation
	std::map<string, HBlockVerbRelation > verbRelationAssoc;
	std::map<string, std::list<HBlockAssertion_is> > verbAssertation;
 

    std::vector<HBlockAssertionBase> dynamic_assertions;


    std::vector<HBlockAssertion_is> kindDefinitions;

	std::vector<HVariableNamed> global_variables;

    std::vector<HBlockAssertion_isDefaultAssign> default_assignments;
    std::vector<HBlockAssertionBase> instance_variables;
    std::vector<HBlockAssertionBase> kind_variables;
	std::vector<HBlockKind_InstanceVariable> kind_named_variables;

//Decides
    std::vector<HBlockToDecideWhat> decides_what;
    std::vector<HBlockToDecideWhether> decides_whether;
    std::vector<HBlockToDecideIf> decides_if;
	std::vector<HBlockToDecideWhat_FirstNoum> decides_noum1;


	std::vector<HBlockAction> actions_header;
	std::vector<HBlockUnderstandDynamic> dynamic_understand;


    QueryResul query_is_instance_valueSet(HBlock c_block, HBlock c_block1, QueryStack stk);
	QueryResul query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk);
 
	QueryResul query_is_propertyOf_value(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_is_Variable_value(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk);
 
	QueryResul query_is(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query(HBlockAssertion_is q, HBlockAssertion_is base, HRunLocalScope localsEntry, QueryStack stk);
 
	// QueryResul queryVerb(string vb, HBlock c_block, HBlock value, QueryStack stk);


    std::list<HBlockKind> getUpperKinds(HBlockKind kind);
	bool is_derivadeOf(HBlockInstance a, HBlockKind b, HRunLocalScope localsEntry);
 
	void dump_instance(string str, HRunLocalScope localsEntry);
	HBlockInstance new_Instance(string named, HBlockKind kind);

    void assign_variable_to_instance(HBlockAssertionBase kvar);
	bool setVerb(string cs, HBlock c_block, HBlock value);
	QueryResul query_relation_instance(HBlockRelationInstance rr, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_relation_property(HBlockNoum property_noum, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_relation(HBlockRelationBase rel, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_user_verbs(string vb, HBlock c_block, HBlock value, HRunLocalScope localsEntry, QueryStack stk);


	bool assert_newVerb(HBlockVerbRelation value);
	bool assert_it_variableGlobal(HBlock obj, HBlock value);
 
	CResultMatch MatchList(HBlockMatchList M, HBlockList value,HRunLocalScope localsEntry, QueryStack stk);
	CResultMatch Match(HBlockMatch M, HBlock value,HRunLocalScope localsEntry, QueryStack stk);
 
 
	QueryResul queryVerb_ListedIn(HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack stk);
	bool set_relation_property(HBlock n1, HBlock n2, HRunLocalScope localsEntry);
	bool is_nothing(HBlockNoum noum);
	bool set_relation_property(HBlockNoum property_noum, HBlock n1, HBlock n2, HRunLocalScope localsEntry);
	bool set_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry);
	bool unset_relation(HBlockRelationBase relation, HBlock n1, HBlock n2, HRunLocalScope localsEntry);
public:
    CBlockInterpreter();

    ~CBlockInterpreter();

    void initialize();
	bool assert_it_canBe(HBlock c_block, HBlockEnums value, HRunLocalScope localsEntry);
	 

	void dump_instance(string str);
	bool assert_newUnderstand(HBlockUnderstandDynamic value);

	bool assert_newRelation(HBlockRelationBase rel);

	bool assert_it_not_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry);
	void execute_init(HBlock p);

    bool assert_decideBlock(HBlockToDecide dct);
	bool assert_has_variable(HBlock obj, HBlock value, HRunLocalScope localsEntry);
	bool is_all_items_of_kind(HBlockList listvalues, HBlockKind kind, HRunLocalScope localsEntry);
	bool kind_has_property_called(HBlockKind kind, string propertyNamed);
	bool assert_property_defaultValue(HBlockProperty prop, HBlock value, HRunLocalScope localsEntry);
	bool assert_it_defaultValue(HBlock obj, HBlock value, HRunLocalScope localsEntry);
 

 

 

 
	bool assert_it_action(HBlock obj, HBlock value);
	bool assert_it_kind(HBlock obj, HBlock value, HRunLocalScope localsEntry);


	std::pair<HBlockKind, HBlockKind> create_derivadeKind(string called, string baseName);
	bool assert_it_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry);
 
	bool assert_it_instance(HBlock obj, HBlock value, HRunLocalScope localsEntry);
	bool assert_it_valuesDefinitions(HBlock c_block, HBlock value, HRunLocalScope localsEntry);
 

 
	std::list<HBlock> resolve_as_list(HBlock qlist, HRunLocalScope localsEntry);
	HBlockKind getKindOf(HBlockInstance obj);
	string BlockNoum(HBlock c_block); 
   // bool MatchOld(HBlock c_block, HBlockMatch m);
    HBlock getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecideWhether dct);
	HBlock getDecidedValueOf(HBlock c_block, HBlockToDecideWhat dct, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul getDecidedIf(HBlock c_block, HBlockToDecideIf dct, HRunLocalScope localsEntry, QueryStack stk);


	QueryResul Selector_all(HBlock aList, HRunLocalScope localsEntry ,std::function<QueryResul(HBlock)> selector );
	QueryResul Selector_any(HBlock aList, HRunLocalScope localsEntry, std::function<QueryResul(HBlock)> selector );
	QueryResul get_system_verbs(string cs, HBlock n1, HBlock n2, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_verb(HBlockIsVerb is_verb, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_not_verb(HBlockIsNotVerb is_verb, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query_decides(HBlock q, HRunLocalScope localsEntry, QueryStack stk);
	bool assert_it_verbRelation(std::string verbNamed, HBlock obj, HBlock value, HRunLocalScope localsEntry);
 
 

	QueryResul query(HBlock q, HRunLocalScope localsEntry, QueryStack stk);
	QueryResul query(HBlock  vquery);

 
 



	HTerm executeAssertion_is(HBlockAssertion_is b);

    HTerm executeAssertion(HBlockAssertionBase b);

    HTerm execute(HBlock b);

    HBlock resolve(CTerm *b);

    HBlock resolve_of(HBlock b, HBlock a);
	HBlockKind resolve_system_kind(string n);
 
	bool is_derivadeOf(HBlockKind a, HBlockKind b);

 

    HBlockKind resolve_kind(string n);
	HBlock resolve_noum(HBlockNoum n, HRunLocalScope localsEntry);

	HBlock resolve_noum_as_variable(HBlockNoum n);
	HBlock resolve_string(string n, HRunLocalScope localsEntry);
 
	//HBlock resolve_value(HBlock  c_block);

 

 
	HBlock value_can_be_assign_to(HBlock value, HBlockKind kind, HRunLocalScope localsEntry);
	bool assert_it_property(HBlock propname, HBlock obj, HBlock value, HRunLocalScope localsEntry);
	QueryResul query_is_List(CBlock *c_block, CBlock *c_block1);



	QueryResul query_is_extern(HBlock c_block, HBlock c_block1 );
	QueryResul query_is_same(HBlock c_block, HBlock c_block1, HRunLocalScope localsEntry, QueryStack stk);
	bool set_relation(HBlockRelationBase relation , HBlock n1, HBlock n2);
	bool execute_verb_set(HBlockIsVerb vverb, HRunLocalScope localsEntry);
	bool execute_verb_unset(HBlockIsNotVerb vverb, HRunLocalScope localsEntry);
	bool execute_set(HBlock obj, HBlock value, HRunLocalScope localsEntry);
	HBlock exec_eval_property_value_imp(HBlock prop, HBlock c_block);
	HBlock exec_eval_property_value(HBlock c_block, HRunLocalScope localsEntry);
	HBlock exec_eval_assertations(HBlock c_block, HRunLocalScope localsEntry, std::function<HBlock(HBlock)> is_accetable);
 
	HBlock exec_eval(HBlock c_block, HRunLocalScope localsEntry);
	HBlock resolve_as_callCommand(HBlock c_block, HRunLocalScope shared_ptr);
	HExecutionBlock create_dispach_env(HBlockList p, HRunLocalScope localsEntry);
 
 
 
	bool execute_now(HBlock c_block);
	bool execute_system_action(HBlockActionCall v_call);
	bool execute_user_action(HBlockActionCall v_call);
	//Executa este bloco !
	bool execute_now(HBlock p, HRunLocalScope localsEntry);
	bool execute_now(HBlock p, HRunLocalScope localsEntry, QueryStack stk);
	bool queryIsVerbToRelation(HBlockMatch m);



	void logMessage(std::string  msg );
};

using HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;

#endif