#pragma once
#ifndef CPARSER_H
#define CPARSER_H

#include "CBase.h"
#include "BlockInterpreter.h"
#include "CBlockMatch.h"
#include "CMatch.h"
#include "CBlockInterpreterRuntime.h"
#include "CBlockRelation.h"
#include <condition_variable>


class ParserResult
{
 
	 


public:
	ParserResult(MatchResult  result)
		: result(result)
	{
		block = nullptr;
	}
	ParserResult(MatchResult  result, HBlock b) :result(result), block(b)
	{

	}
	ParserResult(const ParserResult  &other) = delete;
	 
	void operator=(ParserResult const &x) = delete;

	ParserResult(ParserResult&& other) 
	{
		// pilfer other�s resource
		std::swap(result , other.result);
		swap(block, other.block);
		other.block = nullptr; 
	}


	~ParserResult()
	{
		if (block != nullptr)
		{
			//delete block;
		}
	}

	MatchResult result;
	HBlock  block;
};
 


 class UnderstandAction
 {
 public:
	 std::vector<HPred> matchPhase;
	 HBlockAction   matchAction;
	 UnderstandAction(std::vector<HPred> _matching , HBlockAction  _Action):matchPhase(_matching),  matchAction(_Action) {}
 };


 //resolve as chamadas em tempo de execucao
 class staticDispatchEntry
 {
 public:	 
	 staticDispatchEntry(HBlockMatchList  _argumentsMatch, HBlock  _action);
	 staticDispatchEntry();
	 HBlockMatchList entryArguments;
	 HBlock  action;  //actions TO call
 };


 // Class que determina quais frases sao direcionados a quais dynamicDispatchs.. estes sao resolvidos em tempo de compilacao
 class StaticDispatchArgument
 {
 public:
	 StaticDispatchArgument( int _entryId ):entryId(_entryId){};	 
	 std::list<staticDispatchEntry> entries;
	 int  entryId;
 };


 
class SentenceDispatchPredicate
 {
 public:
	 SentenceDispatchPredicate(std::vector<HPred> _matchPhase , HBlockMatch  _matchPhaseDynamic, int _entryId);
	 std::vector<HPred> matchPhase;	 
	 HBlockMatch _matchPhaseDynamic;
	 int  entryId;
 };


 class DispatchArguments
 {
 public:
	 DispatchArguments(std::vector<HPred> _sentencePredicade , HBlockMatchList  static_argument_match, HBlockMatch sentence_match)
		 : staticPredicade(_sentencePredicade),
		 staticArgumentMatch(static_argument_match),
		 sentenceMatch(sentence_match)
	 {
	 }

	 std::vector<HPred> staticPredicade;
	 HBlockMatchList   staticArgumentMatch; // Only the arguments
	 HBlockMatch   sentenceMatch; //Full Sentence
	 
 };


class CParser
{

	std::vector<NoumDefinition> nregisters;
	HBlockInterpreter interpreter;

	std::map<string, HBlock > verbToRelation;
	std::shared_ptr<CPredBooleanOr>  verbList;
	std::shared_ptr<CPredBooleanOr>  actionPredList;
 
	std::list< UnderstandAction > actionUndestands;
	std::list<StaticDispatchArgument> staticDispatch;
	std::list<SentenceDispatchPredicate> sentenceDispatch;

	
public:
	CParser(HBlockInterpreter  _interpreter);
	virtual ~CParser();

 
	void set_Noum(NoumDefinition ndef);
	void set_Noum(NoumDefinitions ndef);
	HBlockIsVerb parserMatchIsConditionVerb(HTerm term);
	int registerStaticDispatch(int entryId, HBlockMatchList  argumentMatch, HBlock body );


	int registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entryMatch );

	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	HBlock parse_AssertionAction_ApplyngTo(HTerm term);
 
	 
 
 
 
	
	HBlock parser_What_Assertion( HTerm  term);
	HBlock parseAssertion_DecideWhat( HTerm  term);
	HBlock parseAssertion_isDecide(std::vector<HTerm> term);
	HBlock parserBoolean(  HTerm  term);
	HBlockAssertion_is parserMatchIsCondition(HTerm match);
	HBlock STMT_Definition_Assertion(std::vector<HTerm> term);
	HBlockStaticDispatch  getStaticDispatchResolve(HTerm tem);
	HBlockAssertion_isInstanceOf  parseAssertion_isInstanceOf(std::vector<HTerm> term)  ;
	HBlockList  parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep );
	HBlockList  parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, HBlockList  CList);
	HBlockList  parseAssertionFirstTerm_COMMA_AND(HTerm term, HBlockList  CList);
	HBlockList  parseAssertionFirstTerm_COMMA_OR(HTerm term, HBlockList  CList);
	HBlockList  parse_Strict_COMMA_AND(HTerm term );
	HBlockList  parse_Strict_COMMA_OR(HTerm term );
	HBlock parseAssertionFirstTerm_Compose(HTerm term);
	HBlock parseAssertionFirstTerm(HTerm match);
	HBlock parseAssertionEnumSecondTerm(HTerm term);
	HBlock STMT_Decide_Assertion(std::vector<HTerm> lst);
	
	HBlockMatch  parser_MatchArgument(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<HTerm> term);
	HBlock STMT_understand_Action_Assertion_static(std::vector<HTerm> term);
	HBlock parse_toDecide_Entry(std::vector<HTerm> term);
	HBlock parse_toDecide_Ret(std::vector<HTerm> term);
	HBlock parser_decides_Assertion(std::vector<HTerm> term);
	HBlock STMT_understand_Assertion(std::vector<HTerm> term);
	HBlock STMT_verb_Assertion_N(std::vector<HTerm> term);
	HBlock STMT_verb_Assertion(std::vector<HTerm> lst);

	HBlockEnums  parseAssertion_EnumTerms(  HTerm  elist);


	HBlock parse_AssertionVerb(std::vector<HTerm> term);
	HBlock parse_AssertionAction(std::vector<HTerm> term);
	HBlock parse_AssertionIsVariable(std::vector<HTerm> lst);
	HBlockKindOfName parse_KindOf(HTerm term);
	HBlock parse_AssertionIsKindOf(std::vector<HTerm> term);
	HBlock parse_AssertionValuesOf(std::vector<HTerm> term);
	HBlock parse_AssertionDefaultAssign(std::vector<HTerm> term);
	HBlockAssertion_is   parse_AssertionDirectAssign(std::vector<HTerm> term);


	HBlock   parser_VerbAssign(std::vector<HTerm> term);



	HBlock parse_removeArticle(std::vector<HTerm> term);
	HBlock parse_List_AND(std::vector<HTerm> term);
	HBlock parse_noum(std::vector<HTerm> term);
	HBlock parser_Declaration_Assertion(std::vector<HTerm> lst);
	HBlockProperty  parse_PropertyOf(std::vector<HTerm> term);
 
	HBlock STMT_canBe_Assertion(std::vector<HTerm> lst);
	HBlockInstanceVariable  CProperty_called(HTerm term);
	HBlock STMT_hasAn_Assertion(std::vector<HTerm> lst);
 
	HBlock parser_stmt(std::vector<HTerm> lst);
	HBlock parser_stmt(HTerm term);
	HBlock parserBoolean(std::vector<HTerm> term);
	HBlock parser_stmt(string str);
	HBlock parser_stmt(string str, bool dump);

	HBlock parser_kind(HTerm term); 
	HBlock parser_kind_or_instance(HTerm term);
	HBlock parser_valueReference(HTerm term);
	HBlock parser_assertionTarger(HTerm term);
	HBlock parser_expression(HTerm term);
	HBlock parser_expression(std::vector<HTerm>  term);

	HBlockArgumentInput parser_KindCalled(HTerm term);
	HBlock STMT_relates_Assertion(std::vector<HTerm> term);

};



std::vector<HTerm> decompose(string phase);;
string  decompose_bracket(string phase, string dlm);
MTermSet remove_boundaryListMark(MTermSet& m);

string get_repr(MTermSet lst);
HPred verb_IS_NOT();
HPred mk_HPredLiteral( string str );
HPred verb_IS();
HPred undefinedArticle();
HPred mk_HPredLiteral_OR(string _named , std::initializer_list<string> alist );
HPred mk_What_Which();
HTerm expandBract(HTerm term);
std::vector<HTerm> get_tail(std::vector<HTerm>& qlist);
std::pair<HBlock , HPred>   getVerbAndAux(   HTerm  term);
HPred convert_to_predicate(CTerm *termo);
string CtoString(HTerm  value);
string CtoString(CList * lst);
string CtoString(CTerm  *value);

#endif