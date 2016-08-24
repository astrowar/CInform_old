#pragma once

#include "BlockInterpreter.h"
#include "CblockAssertion.h"

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
    std::vector<HBlockAssertionBase> dynamic_assertions;


    std::vector<HBlockAssertion_is> kindDefinitions;


    std::vector<HBlockAssertion_isDefaultAssign> default_assignments;
    std::vector<HBlockAssertionBase> instance_variables;
    std::vector<HBlockAssertionBase> kind_variables;

    std::vector<HBlockToDecide> decides_what;
    std::vector<HBlockToDecidewhether> decides_whether;
    std::vector<HBlockToDecideIf> decides_if;


    QueryResul query_is_instance_valueSet(HBlock c_block, HBlock c_block1);

    QueryResul query_is_propertyOf_value_imp(HBlock propname, HBlock propObj, HBlock c_block1, QueryStack stk);

    QueryResul query_is_propertyOf_value(HBlock c_block, HBlock c_block1, QueryStack stk);

    QueryResul query_is(HBlock c_block, HBlock c_block1, QueryStack stk);

    std::list<HBlockKind> getUpperKinds(HBlockKind kind);

    HBlockInstance new_Instance(std::string named, HBlockKind kind);

    void assign_variable_to_instance(HBlockAssertionBase kvar);

public:
    CBlockInterpreter();

    ~CBlockInterpreter();

    void initialize();

    bool assert_it_canBe(HBlock c_block, HBlockEnums value);

    bool assert_it_valuesDefinitions(HBlock c_block, HBlock value);

    void execute_init(HBlock p);

    bool assert_decideBlock(HBlockToDecide dct);

    bool assert_has_variable(HBlock obj, HBlock value);

    HBlock value_can_be_assign_to(HBlock value, HBlockKind kind);

    bool assert_it_property(HBlock propname, HBlock obj, HBlock value);

    bool assert_it_Value(HBlock obj, HBlock value);

    bool assert_it_not_Value(HBlock obj, HBlock value);

    bool assert_it_defaultValue(HBlock obj, HBlock value);

    std::pair<HBlockKind, HBlockKind> create_derivadeKind(std::string called, std::string baseName);

    bool assert_it_kind(HBlock obj, HBlock value);

    bool assert_it_instance(HBlock obj, HBlock value);

    HBlockKind getKindOf(HBlockInstance obj);

    QueryResul query_is_same(HBlock c_block, HBlock c_block1);

    QueryResul query_is(HBlock c_block, HBlock c_block1);


    bool Match(HBlock c_block, HBlockMatch m);

    HBlock getDecidedWhether(HBlock c_block, HBlock c_block1, HBlockToDecidewhether dct);

    HBlock getDecidedValueOf(HBlock c_block, HBlockToDecide dct);


    QueryResul query(HBlockAssertion_is base, HBlockAssertion_is q);

    QueryResul query(HBlockAssertion_is query);

    HTerm executeAssertion_is(HBlockAssertion_is b);

    HTerm executeAssertion(HBlockAssertionBase b);

    HTerm execute(HBlock b);

    HBlock resolve(CTerm *b);

    HBlock resolve_of(HBlock b, HBlock a);

    bool is_derivadeOf(HBlockKind a, HBlockKind b);

    bool is_derivadeOf(HBlockInstance a, HBlockKind b);

    HBlockKind resolve_kind(std::string n);

    HBlock resolve_noum(HBlockNoum n);

    HBlock resolve_string(std::string n);

    void dump_instance(std::string str);
};

using HBlockInterpreter = std::shared_ptr<CBlockInterpreter>;