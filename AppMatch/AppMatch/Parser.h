#pragma once

#include "BlockInterpreter.h"
#include "CBase.h"
#include "CMatch.h"
#include "CBlockInterpreterRuntime.h"


class CBlockAssertion_isInstanceOf;

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
		// pilfer other’s resource
		std::swap(result , other.result);
		std::swap(block, other.block);
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
	int registerStaticDispatch(int entryId, HBlockMatchList  argumentMatch, HBlock body );


	int registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entryMatch );

	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	HBlock parse_AssertionAction_ApplyngTo(HTerm term);
	HBlock parse_AssertionVerb(std::vector<HTerm> term);
	HBlock parse_AssertionAction(std::vector<HTerm> term);
	 
 
 
 
	HBlock parseAssertion_isKindOf(std::vector<HTerm> term);
	HBlock parseAssertion_valuesOf(std::vector<HTerm> term);
	HBlock parser_What_Assertion(std::vector<HTerm> term);
	HBlock parseAssertion_DecideWhat( HTerm  term);
	HBlock parseAssertion_isDecide(std::vector<HTerm> term);
	HBlock parserBoolean(  HTerm  term);
	HBlock parser_Definition_Assertion(std::vector<HTerm> term);
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
	HBlock parser_Decide_Assertion(std::vector<HTerm> lst);
	
	HBlockMatch  parser_MatchArgument(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<HTerm> term);
	HBlock parser_understand_Action_Assertion(std::vector<HTerm> term);
	HBlock parser_understand_Assertion(std::vector<HTerm> term);
	HBlock parser_verb_Assertion(std::vector<HTerm> lst);

	HBlockEnums  parseAssertion_EnumTerms(  HTerm  elist);


	HBlock parseAssertion_isVariable(std::vector<HTerm> lst);
	HBlock parseAssertion_DefaultAssign(std::vector<HTerm> term);
	HBlockAssertion_is   parseAssertion_DirectAssign(std::vector<HTerm> term);
	HBlock parse_removeArticle(std::vector<HTerm> term);
	HBlock parse_List_AND(std::vector<HTerm> term);
	HBlock parse_noum(std::vector<HTerm> term);
	HBlock parser_Declaration_Assertion(std::vector<HTerm> lst);
	HBlockProperty  parse_PropertyOf(std::vector<HTerm> term);
 
	HBlock parser_canBe_Assertion(std::vector<HTerm> lst);
	HBlockInstanceVariable  CProperty_called(HTerm term);
	HBlock parser_hasAn_Assertion(std::vector<HTerm> lst);
 
	HBlock parser_only(std::vector<HTerm> lst);
	HBlock  parser(HTerm term);
	HBlock parserBoolean(std::vector<HTerm> term);
	HBlock parser(std::string str);
};

