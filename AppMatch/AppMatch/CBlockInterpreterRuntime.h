#pragma once

#ifndef CBLOCKRUNTIME_H
#define CBLOCKRUNTIME_H


#include "BlockInterpreter.h"
#include "CblockAssertion.h"
#include "CBlockMatch.h"
#include <functional>
#include <map>
#include "CBlockUndestand.h"
#include <condition_variable>
#include "CBlockDecideIf.h"
#include "CBlockScope.h"
#include <condition_variable>

class CBlockAssertionBase;

class CBlockAssertion_is;

using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;
using HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;

class QueryStack;


class CResultMatch;

class CBlockInterpreter {

    std::vector<HBlock> program; // main program .. to run IT


    std::vector<HBlockInstance> instancias;
    std::vector<HBlockInstanceVariable> instancias_vars;
    std::vector<HBlockAssertionBase> assertions_functional; //To define and others


    std::vector<NoumDefinition> nregisters;
    std::vector<HBlockAssertion_is> assertions;

	
	std::map<string, HBlock> verbRelationAssoc;
	std::map<string, std::list<HBlockAssertion_is> > verbAssertation;
 

    std::vector<HBlockAssertionBase> dynamic_assertions;


    std::vector<HBlockAssertion_is> kindDefinitions;

	std::vector<HVariableNamed> global_variables;

    std::vector<HBlockAssertion_isDefaultAssign> default_assignments;
    std::vector<HBlockAssertionBase> instance_variables;
    std::vector<HBlockAssertionBase> kind_variables;
	std::vector<HBlockKind_InstanceVariable> kind_named_variables;

    std::vector<HBlockToDecide> decides_what;
    std::vector<HBlockToDecidewhether> decides_whether;
    std::vector<HBlockToDecideIf> decides_if;


	std::vector<HBlockAction> actions_header;
	std::vector<HBlockUnderstandDynamic> dynamic_understand;


    QueryResul query_is_instance_valueSet(HBlock c_block, HBlock c_block1, QueryStack stk);
    QueryResul query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, QueryStack stk);
    QueryResul query_is_propertyOf_value(HBlock c_block, HBlock c_block1, QueryStack stk);
	QueryResul query_is_Variable_value(HBlock c_block, HBlock c_block1, QueryStack stk);
	QueryResul queryVerb_ListedIn(HBlock n1, HBlock n2, QueryStack stk); 
   // QueryResul queryVerb(string vb, HBlock c_block, HBlock value, QueryStack stk);


    std::list<HBlockKind> getUpperKinds(HBlockKind kind);

    HBlockInstance new_Instance(string named, HBlockKind kind);

    void assign_variable_to_instance(HBlockAssertionBase kvar);
	bool setVerb(string cs, HBlock c_block, HBlock value);
	
 
	bool assert_it_verbRelation(std::string verbNamed, HBlock obj, HBlock value);
	bool assert_newVerb(HBlockVerbRelation value);
	bool assert_it_variableGlobal(HBlock obj, HBlock value);
	CResultMatch MatchList(HBlockMatchList M, HBlockList value);
	CResultMatch Match(HBlockMatch M, HBlock value);
public:
    CBlockInterpreter();

    ~CBlockInterpreter();

    void initialize();

    bool assert_it_canBe(HBlock c_block, HBlockEnums value);

    bool assert_it_valuesDefinitions(HBlock c_block, HBlock value);

	bool assert_newUnderstand(HBlockUnderstandDynamic value);
	void execute_init(HBlock p);

    bool assert_decideBlock(HBlockToDecide dct);
	bool kind_has_property_called(HBlockKind kind, string propertyNamed);
	bool assert_has_variable(HBlock obj, HBlock value);

    HBlock value_can_be_assign_to(HBlock value, HBlockKind kind);

    bool assert_it_property(HBlock propname, HBlock obj, HBlock value);

    bool assert_it_Value(HBlock obj, HBlock value);
	bool assert_it_action(HBlock obj, HBlock value);
	bool assert_it_not_Value(HBlock obj, HBlock value);
	bool assert_property_defaultValue(HBlockProperty obj, HBlock value);
	bool assert_it_defaultValue(HBlock obj, HBlock value);

    std::pair<HBlockKind, HBlockKind> create_derivadeKind(string called, string baseName);

    bool assert_it_kind(HBlock obj, HBlock value);

    bool assert_it_instance(HBlock obj, HBlock value);

	std::list<HBlock> resolve_as_list(HBlock qlist);
	HBlockKind getKindOf(HBlockInstance obj);
	string BlockNoum(HBlock c_block); 
   // bool MatchOld(HBlock c_block, HBlockMatch m);
    HBlock getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecidewhether dct);
    HBlock getDecidedValueOf(HBlock c_block, HBlockToDecide dct);




	QueryResul query_is_same(HBlock c_block, HBlock c_block1, QueryStack stk);
    QueryResul query_is(HBlock c_block, HBlock c_block1, QueryStack stk);
    QueryResul query(HBlockAssertion_is base, HBlockAssertion_is q, QueryStack stk);
	
	QueryResul get_system_verbs(string cs, HBlock n1, HBlock n2, QueryStack stk);
	QueryResul query_user_verbs(string cs, HBlock n1, HBlock n2, QueryStack stk);
	QueryResul query_verb(HBlockIsVerb is_verb, QueryStack stk);
	QueryResul query_not_verb(HBlockIsNotVerb is_verb, QueryStack stk);
	QueryResul query(HBlock  vquery, QueryStack stk);
	QueryResul query(HBlock  vquery);

 
 QueryResul Selector_all(HBlock what, std::function< QueryResul(HBlock) > selector);
 QueryResul Selector_any(HBlock what, std::function< QueryResul(HBlock) > selector);



	HTerm executeAssertion_is(HBlockAssertion_is b);

    HTerm executeAssertion(HBlockAssertionBase b);

    HTerm execute(HBlock b);

    HBlock resolve(CTerm *b);

    HBlock resolve_of(HBlock b, HBlock a);

    bool is_derivadeOf(HBlockKind a, HBlockKind b);

    bool is_derivadeOf(HBlockInstance a, HBlockKind b);

    HBlockKind resolve_kind(string n);

    HBlock resolve_noum(HBlockNoum n);
	HBlock resolve_noum_as_variable(HBlockNoum n);
	HBlock resolve_string(string n);
	HBlock resolve_value(HBlock  c_block);

    void dump_instance(string str);

    bool is_all_items_of_kind(HBlockList listvalues, HBlockKind kind);

	QueryResul query_is_List(CBlock *c_block, CBlock *c_block1);



	QueryResul query_is_extern(HBlock c_block, HBlock c_block1 );
	bool execute_set(HBlock obj, HBlock value);
	HBlock exec_eval_property_value_imp(HBlock prop, HBlock c_block);
	HBlock exec_eval_property_value(HBlock c_block);
	HBlock exec_eval_assertations(HBlock c_block, std::function<HBlock(HBlock) > is_accetable);
	HBlock exec_eval( HBlock c_block);
	HExecutionBlock create_dispach_env(HBlockList p);
 
	bool execute_now(HBlock c_block); //Executa este bloco !
};

using HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;

#endif
