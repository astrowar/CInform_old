#pragma once

#include "BlockInterpreter.h"
#include "CblockAssertion.h"


class CBlockAssertionBase;
class CBlockAssertion_is;
class   QueryStack;

class CBlockInterpreter
{

	std::vector<UBlock> program; // main program .. to run IT


	std::vector<CBlockInstance*> instancias;
	std::vector<CBlockInstanceVariable*> instancias_vars;
	std::vector<CBlockAssertionBase*>    assertions_functional; //To define and others


	std::vector<NoumDefinition> nregisters;
	std::vector<CBlockAssertion_is *> assertions;
	std::vector<CBlockAssertionBase*> dynamic_assertions;


	std::vector<CBlockAssertion_is*>   kindDefinitions;


	std::vector<CBlockAssertion_isDefaultAssign *> default_assignments;
	std::vector<CBlockAssertionBase* > instance_variables;
	std::vector<CBlockAssertionBase* > kind_variables;


	QueryResul query_is_instance_valueSet(CBlock* c_block, CBlock* c_block1);
	QueryResul query_is(CBlock* c_block, CBlock* c_block1, QueryStack stk);

	std::list<CBlockKind*> getUpperKinds(CBlockKind* kind);
	CBlockInstance*  new_Instance(std::string named, CBlockKind* kind);
	void assign_variable_to_instance(CBlockAssertionBase* kvar);
public:
	CBlockInterpreter();
	~CBlockInterpreter();

	void initialize();
	bool assert_it_canBe(UBlock c_block, CBlockEnums* value);

	bool assert_it_valuesDefinitions(UBlock c_block, UBlock value);
	void execute_init(UBlock p);
	bool assert_it_not_Value(UBlock obj, UBlock value);
	 
	bool assert_it_defaultValue(UBlock obj, UBlock value);
	bool  assert_it_kind(UBlock obj, UBlock value);
	bool  assert_it_instance (UBlock obj, UBlock value);
	CBlockKind* getKindOf(CBlockInstance* obj);

	QueryResul query_is_same(CBlock* c_block, CBlock* c_block1);
	QueryResul query_is(CBlock* c_block, CBlock* c_block1);
	 
 
	QueryResul query(CBlockAssertion_is* base, CBlockAssertion_is* q);
	QueryResul query(CBlockAssertion_is* query);
	HTerm executeAssertion_is(CBlockAssertion_is* b);
	HTerm executeAssertion(CBlockAssertionBase* b);
	HTerm execute(CBlock *b);
	CBlock* resolve(CTerm  *b);
	CBlock* resolve_of(CBlock  *b , CBlock *a);
	bool is_derivadeOf(CBlockKind* a, CBlockKind* b);
	bool is_derivadeOf(CBlockInstance* a, CBlockKind* b);
	CBlock* resolve_noum(CBlockNoum  *n);
	CBlock* resolve_string(std::string n);
	void dump_instance(std::string str);
};



 