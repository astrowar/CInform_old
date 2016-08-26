#pragma once

#ifndef CBLOCKRUNTIME_H
#define CBLOCKRUNTIME_H


#include "BlockInterpreter.h"
#include "CblockAssertion.h"
#include "CBlockMatch.h"
#include <map>

class CBlockAssertionBase;

class CBlockAssertion_is;

using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;
using HBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;

class QueryStack;

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


    std::vector<HBlockAssertion_isDefaultAssign> default_assignments;
    std::vector<HBlockAssertionBase> instance_variables;
    std::vector<HBlockAssertionBase> kind_variables;
	std::vector<HBlockKind_InstanceVariable> kind_named_variables;

    std::vector<HBlockToDecide> decides_what;
    std::vector<HBlockToDecidewhether> decides_whether;
    std::vector<HBlockToDecideIf> decides_if;


    QueryResul query_is_instance_valueSet(HBlock c_block, HBlock c_block1);

    QueryResul query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, QueryStack stk);

    QueryResul query_is_propertyOf_value(HBlock c_block, HBlock c_block1, QueryStack stk);

    QueryResul query_is(HBlock c_block, HBlock c_block1, QueryStack stk);

    std::list<HBlockKind> getUpperKinds(HBlockKind kind);

    HBlockInstance new_Instance(string named, HBlockKind kind);

    void assign_variable_to_instance(HBlockAssertionBase kvar);
	bool setVerb(string cs, HBlock c_block, HBlock value);
	QueryResul getVerb(string vb, HBlock c_block, HBlock value);
	bool assert_it_verbRelation(std::string verbNamed, HBlock obj, HBlock value);
	bool assert_newVerb(HBlockVerbRelation value);
public:
    CBlockInterpreter();

    ~CBlockInterpreter();

    void initialize();

    bool assert_it_canBe(HBlock c_block, HBlockEnums value);

    bool assert_it_valuesDefinitions(HBlock c_block, HBlock value);

    void execute_init(HBlock p);

    bool assert_decideBlock(HBlockToDecide dct);
	bool kind_has_property_called(HBlockKind kind, string propertyNamed);
	bool assert_has_variable(HBlock obj, HBlock value);

    HBlock value_can_be_assign_to(HBlock value, HBlockKind kind);

    bool assert_it_property(HBlock propname, HBlock obj, HBlock value);

    bool assert_it_Value(HBlock obj, HBlock value);

    bool assert_it_not_Value(HBlock obj, HBlock value);
	bool assert_property_defaultValue(HBlockProperty obj, HBlock value);
	bool assert_it_defaultValue(HBlock obj, HBlock value);

    std::pair<HBlockKind, HBlockKind> create_derivadeKind(string called, string baseName);

    bool assert_it_kind(HBlock obj, HBlock value);

    bool assert_it_instance(HBlock obj, HBlock value);

    HBlockKind getKindOf(HBlockInstance obj);
	string BlockNoum(HBlock c_block);
	QueryResul query_is_same(HBlock c_block, HBlock c_block1);

    QueryResul query_is(HBlock c_block, HBlock c_block1);


    bool Match(HBlock c_block, HBlockMatch m);

    HBlock getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecidewhether dct);

    HBlock getDecidedValueOf(HBlock c_block, HBlockToDecide dct);


    QueryResul query(HBlockAssertion_is base, HBlockAssertion_is q);
	QueryResul query(HBlock  vquery);

	QueryResul query_verb(HBlockIsVerb is_verb);
	QueryResul query_not_verb(HBlockIsNotVerb is_verb);

	HTerm executeAssertion_is(HBlockAssertion_is b);

    HTerm executeAssertion(HBlockAssertionBase b);

    HTerm execute(HBlock b);

    HBlock resolve(CTerm *b);

    HBlock resolve_of(HBlock b, HBlock a);

    bool is_derivadeOf(HBlockKind a, HBlockKind b);

    bool is_derivadeOf(HBlockInstance a, HBlockKind b);

    HBlockKind resolve_kind(string n);

    HBlock resolve_noum(HBlockNoum n);

    HBlock resolve_string(string n);

    void dump_instance(string str);
 
};

using HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;

#endif
