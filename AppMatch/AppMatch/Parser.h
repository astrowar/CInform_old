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
	ParserResult(MatchResult  result, CBlock *b) :result(result), block(b)
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
			delete block;
		}
	}

	MatchResult result;
	CBlock *block;
};
 


 class UnderstandAction
 {
 public:
	 std::vector<HPred> matchPhase;
	 CBlockAction *  matchAction;
	 UnderstandAction(std::vector<HPred> _matching , CBlockAction*  _Action):matchPhase(_matching),  matchAction(_Action) {}
 };


 //resolve as chamadas em tempo de execucao
 class staticDispatchEntry
 {
 public:	 
	 staticDispatchEntry(CBlockMatchList* _argumentsMatch, CBlock* _action);
	 staticDispatchEntry();
	 CBlockMatchList* entryArguments;
	 CBlock * action;  //actions TO call
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
	 SentenceDispatchPredicate(std::vector<HPred> _matchPhase , CBlockMatch* _matchPhaseDynamic, int _entryId);
	 std::vector<HPred> matchPhase;	 
	 CBlockMatch* _matchPhaseDynamic;
	 int  entryId;
 };


 class DispatchArguments
 {
 public:
	 DispatchArguments(std::vector<HPred> _sentencePredicade , CBlockMatchList* static_argument_match, CBlockMatch* sentence_match)
		 : staticPredicade(_sentencePredicade),
		 staticArgumentMatch(static_argument_match),
		 sentenceMatch(sentence_match)
	 {
	 }

	 std::vector<HPred> staticPredicade;
	 CBlockMatchList*   staticArgumentMatch; // Only the arguments
	 CBlockMatch*   sentenceMatch; //Full Sentence
	 
 };


class CParser
{

	std::vector<NoumDefinition> nregisters;
	CBlockInterpreter *interpreter;

	std::map<string, UBlock > verbToRelation;
	std::shared_ptr<CPredBooleanOr>  verbList;
	std::shared_ptr<CPredBooleanOr>  actionPredList;
 
	std::list< UnderstandAction > actionUndestands;
	std::list<StaticDispatchArgument> staticDispatch;
	std::list<SentenceDispatchPredicate> sentenceDispatch;

	
public:
	CParser(CBlockInterpreter *_interpreter);
	virtual ~CParser();

 
	void set_Noum(NoumDefinition ndef);
	void set_Noum(NoumDefinitions ndef);
	int registerStaticDispatch(int entryId, CBlockMatchList *argumentMatch, CBlock* body );


	int registerDynamicDispatch(std::vector<HPred> _matchPhase, CBlockMatch* entryMatch );

	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	UBlock parse_AssertionAction_ApplyngTo(HTerm term);
	UBlock parse_AssertionVerb(std::vector<HTerm> term);
	UBlock parse_AssertionAction(std::vector<HTerm> term);
	 
 
 
 
	UBlock parseAssertion_isKindOf(std::vector<HTerm> term);
	UBlock parseAssertion_valuesOf(std::vector<HTerm> term);
	UBlock parser_What_Assertion(std::vector<HTerm> term);
	UBlock parseAssertion_DecideWhat( HTerm  term);
	UBlock parseAssertion_isDecide(std::vector<HTerm> term);
	UBlock parserBoolean(  HTerm  term);
	UBlock parser_Definition_Assertion(std::vector<HTerm> term);
	CBlockStaticDispatch* getStaticDispatchResolve(HTerm tem);
	CBlockAssertion_isInstanceOf* parseAssertion_isInstanceOf(std::vector<HTerm> term)  ;
	CBlockList* parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep );
	CBlockList* parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlockList* CList);
	CBlockList* parse_Strict_COMMA_AND(HTerm term );
	CBlockList* parse_Strict_COMMA_OR(HTerm term );
	UBlock parseAssertionFirstTerm_Compose(HTerm term);
	UBlock parseAssertionFirstTerm(HTerm match);
	UBlock parseAssertionEnumSecondTerm(HTerm term);
	UBlock parser_Decide_Assertion(std::vector<HTerm> lst);
	
	CBlockMatch* parser_MatchArgument(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<HTerm> term);
	UBlock parser_understand_Action_Assertion(std::vector<HTerm> term);
	UBlock parser_understand_Assertion(std::vector<HTerm> term);
	UBlock parser_verb_Assertion(std::vector<HTerm> lst);

	CBlockEnums* parseAssertion_EnumTerms(  HTerm  elist);


	UBlock parseAssertion_isVariable(std::vector<HTerm> lst);
	UBlock parseAssertion_DefaultAssign(std::vector<HTerm> term);
	CBlockAssertion_is * parseAssertion_DirectAssign(std::vector<HTerm> term);
	UBlock parse_removeArticle(std::vector<HTerm> term);
	UBlock parse_List_AND(std::vector<HTerm> term);
	UBlock parse_noum(std::vector<HTerm> term);
	UBlock parser_Declaration_Assertion(std::vector<HTerm> lst);
	CBlockProperty* parse_PropertyOf(std::vector<HTerm> term);
 
	UBlock parser_canBe_Assertion(std::vector<HTerm> lst);
	CBlockInstanceVariable* CProperty_called(HTerm term);
	UBlock parser_hasAn_Assertion(std::vector<HTerm> lst);
 
	UBlock parser_only(std::vector<HTerm> lst);
	UBlock  parser(HTerm term);
	UBlock parserBoolean(std::vector<HTerm> term);
	UBlock parser(std::string str);
};

