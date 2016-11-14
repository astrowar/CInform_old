#pragma once
#ifndef CPARSER_H
#define CPARSER_H

#include "CBase.hpp"
#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"
#include "CMatch.hpp"

#include "CBlockRelation.hpp"
#include <condition_variable>
#include "CBlockCommand.hpp"
#include <condition_variable>
#include "CBlockControlFlux.hpp"
#include <condition_variable>
#include "CBlockInterpreterRuntime.hpp"

class SourceLine
{
public:
	int linenumber;
	string filename;	
	string line;
	SourceLine(string _filename, int _linenumber, string _line):line(_line),linenumber(_linenumber),filename(_filename){}
};

class ErrorInfo
{
public:
	bool hasError;
	string msg;
	//SourceLine errorLine;

	ErrorInfo() : hasError(false), msg("") {}
	ErrorInfo(string _msg) : hasError(true), msg(_msg) {}

	void setError(string cs) { msg =  cs; hasError = true; }
};

class GroupLines;
using HGroupLines = std::shared_ptr<GroupLines>;
class GroupLines
{
public:
	int identarion;
	std::vector<SourceLine> lines;
	HGroupLines inner;
	HGroupLines next;
	HGroupLines prev;
};



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
	 SentenceDispatchPredicate(std::vector<HPred> _matchPhase , HBlockMatch  _matchPhaseDynamic, HBlock _output, int _entryId);
	 std::vector<HPred> matchPhase;	 
	 HBlockMatch _matchPhaseDynamic;
	 HBlock output;
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
	HBlockInterpreter interpreter_inner;

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



	//Matchs 
	HBlockMatchIsVerb parserMatchIsConditionVerb(HTerm term);
	HBlockVerbRelation STMT_verb_relation(HBlock a_verb, HTerm term);
 
	HBlockMatchIs parserMatchIsCondition(HTerm match);
    HBlockMatch  parser_MatchArgument(HTerm term);




	int registerStaticDispatch(int entryId, HBlockMatchList  argumentMatch, HBlock body );
	int registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entryMatch );
	int registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry, HBlock ret);
	ParserResult parser_AssertionKind(std::vector<HTerm>&  lst);
	HBlockActionApply parse_AssertionAction_ApplyngTo(HTerm term);
	HBlockMatch parser_What_Which_Assertion(HTerm term);
	HBlockMatchIs parser_What_Which_Verb_Assertion(HTerm term);
	HBlockMatchIs parser_Match_IF_Assertion(HTerm term );
 


 
	 
	HBlock parseAssertion_isDecide_inLine(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
	HBlock parseAssertion_isDecide_Block(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
	HBlock parseAssertion_isDecide(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
	HBlock parseAssertion_DecideOn(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo* err);
	HBlock parserBoolean(  HTerm  term);
	HBlock parser_stmt_str(string str, HGroupLines inner, ErrorInfo* err);
	 
	HBlock Parser_Stmt(string str, bool dump);
	HBlock Parser_Expression(string str, bool dump);
	HBlock Parser_Condition(string str, bool dump); // Apenas para testes
	 
	HBlock parser_stmt(string str, bool dump, ErrorInfo* err);
	
	HBlock parser_GroupLine(std::string v, HGroupLines inner, ErrorInfo* err);
	HBlockComandList parser_stmt_inner(HGroupLines inner, ErrorInfo* err);
	std::list<HBlock >  post_process_tokens(std::list< HBlock > list, ErrorInfo* err);
	 
	std::list<HBlock> parser_GroupLines(HGroupLines pivot, ErrorInfo* err);
	 
	HBlock STMT_Definition_Assertion(std::vector<HTerm>&  term);
	HBlockStaticDispatch  getStaticDispatchResolve(HTerm tem);
	HBlockMatch parser_MatchArgument(std::vector<HTerm>&  term);
	HBlockAssertion_isInstanceOf  parseAssertion_isInstanceOf(std::vector<HTerm>& term)  ;
	HBlockList  parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep );
	HBlockList  parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, HBlockList  CList);
	HBlockList  parseAssertionFirstTerm_COMMA_AND(HTerm term, HBlockList  CList);
	HBlockList  parseAssertionFirstTerm_COMMA_OR(HTerm term, HBlockList  CList);
	HBlockList  parse_Strict_COMMA_AND(HTerm term );
	HBlockList  parse_Strict_COMMA_OR(HTerm term );
	HBlock parseAssertionFirstTerm_Compose(HTerm term);
	HBlock parseAssertionFirstTerm(HTerm match);
	HBlock parseAssertionEnumSecondTerm(HTerm term);
	HBlock STMT_Decide_Assertion(std::vector<HTerm>& lst,   HGroupLines inner, ErrorInfo *err);
	
	
	DispatchArguments  parser_buildMatchBlock_actionInput(HTerm term);
	DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<HTerm>&  term);
	HBlock STMT_understand_generic_redirect(HTerm term, HBlock output_term);
	 
 
	HBlock STMT_understand_Action_Assertion_static(std::vector<HTerm>&  term);
	HBlock parse_toDecide_Entry(std::vector<HTerm>&  term);
	HBlock parse_toDecide_Ret(std::vector<HTerm>&  term);
	HBlock parser_decides_Assertion(std::vector<HTerm>&  term);
	std::list<HBlock> ToMatchList(std::vector<HPred> pvector, MatchResult result);
	HBlock TryDispatch_action(std::vector<HTerm>& term);
	HBlock STMT_understand_Assertion(std::vector<HTerm>&  term);
	HBlock STMT_verb_Assertion_N(std::vector<HTerm>&  term);
	HBlock STMT_verb_Assertion(std::vector<HTerm>&  lst);

	HBlockEnums  parseAssertion_EnumTerms(  HTerm  elist);


	HBlockAssertion_is parse_AssertionVerb(std::vector<HTerm>&  term);
	HBlockKindAction parse_AssertionAction_secondPart(HTerm term);
	HBlock parse_AssertionAction(std::vector<HTerm> term);
	HBlock parse_AssertionIsVariable(std::vector<HTerm>&  lst);
	HBlockKindOfName parse_KindOf(HTerm term);
	HBlock parse_AssertionIsKindOf(std::vector<HTerm>&  term);
	HBlock parse_AssertionValuesOf(std::vector<HTerm>&  term);
	HBlock parse_AssertionDefaultAssign(std::vector<HTerm>&  term);
	HBlockAssertion_is   parse_AssertionDirectAssign(std::vector<HTerm>&  term);


	HBlock   parser_VerbAssign(std::vector<HTerm>& term);



	HBlock parse_removeArticle(std::vector<HTerm>& term);
	HBlock parse_List_AND(std::vector<HTerm>&  term);
	HBlock parse_List_OR(std::vector<HTerm>&  term);
	HBlock parse_noum(std::vector<HTerm>& term);
	HBlock parser_Declaration_Assertion(std::vector<HTerm>&  lst);
	HBlockProperty  parse_PropertyOf(std::vector<HTerm>& term);
 
	HBlock STMT_canBe_Assertion(std::vector<HTerm>& lst);
	HBlockInstanceVariable  CProperty_called(HTerm term);
	HBlock STMT_hasAn_Assertion(std::vector<HTerm>& lst);
	HBlock parser_stmt(HTerm term, HGroupLines inner, ErrorInfo* err);
	 
 

	HBlock parserBoolean(std::vector<HTerm>&  term);
 

	HBlock parser_kind(HTerm term); 
	HBlock parser_kind_or_instance(HTerm term);
	HBlock parser_valueReference(HTerm term);
	HBlock parser_assertionTarger(HTerm term);
	HBlock DynamicLookup_Relation(std::vector<HTerm>& term);
	HBlock parser_SeletorVerb(HTerm term, HBlockMatch muteVariable);
	HBlock DynamicLookup_Verb(std::vector<HTerm>& term);
	HBlockSelector parser_List_selector(std::vector<HTerm>&  term);
	HBlockSelector parser_List_selector(HTerm term);
	HBlock parser_expression_lst(std::vector<HTerm>& lst);
	HBlock parser_expression(HTerm term);

	HBlock parser_stmt_inner(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo* err);
	HBlock text_entry(std::vector<HTerm>&  lst);
 
 
	 
	 
	HBlockArgumentInput parser_KindCalled(HTerm term);
	HBlock STMT_relates_Assertion(std::vector<HTerm>&  term);
	HBlock STMT_relates_AssertionWhen(std::vector<HTerm>&  term);
	HBlock parser_SeletorRelation(HTerm term, HBlockMatch muteVariable);
	HBlock parser_SeletorTerm(HTerm term, HBlockMatch muteVariable);
	HBlock DynamicLookup_Seletor(std::vector<HTerm>& term);
 
	HBlock  DynamicDispatch_action(std::vector<HTerm>&  term);
	HBlockMatchProperty parse_PropertyOf_Match(std::vector<HTerm>&  term);
	HBlockMatch parse_match_noum(std::vector<HTerm>&  term);
	HBlockMatch parse_Which_Verb_Match(std::vector<HTerm>&  term);
	HBlockMatch parse_AssertionVerb_Match(std::vector<HTerm>&  term);
	HBlockMatch  parse_Which_DirectAssign_Match(std::vector<HTerm>&  term);
	HBlockMatch  parse_AssertionDirectAssign_Match(std::vector<HTerm>&  term);
	HBlockMatch parser_Verb_Match(std::vector<HTerm>&  term);
	HBlockMatch parser_expression_match(HTerm term);
	std::list<HBlockMatch> ToMatchListMatc(std::vector<HPred> pvector, MatchResult result);
	HBlockMatch DynamicDispatch_action_match(std::vector<HTerm>&  term);
	HBlockMatch parse_match_list(std::vector<HTerm>&  term);
	HBlockMatch parser_expression_match(std::vector<HTerm>&  lst);

    HBlock STMT_system_Assertion(std::vector<HTerm>& term);

	HBlock sys_say_action(std::vector<HTerm>&  term);
	HBlock parser_loop_A(HTerm& term);
	HBlockAssertion_is parse_Loop_AssertionVerb(HTerm& term, NoumLocation nlocation);
	HBlockAssertion_is parse_Loop_AssertionVerb(HTerm& term);
	HBlockAssertion_is parser_loop_B(HTerm& term, HBlock mutedVariable);
	 
	HBlock sys_now_loop(std::vector<HTerm>& term);
	HBlock sys_now_action(std::vector<HTerm>&  term);

	HBlock parser_text(string str, ErrorInfo* err);
	HBlock parser_text(string str, bool dump);

	std::list<HBlock> group_tokens(std::list<HBlock>  lst);
	HGroupLines get_identation_groups(string filename, std::vector<string> vlines, ErrorInfo* err);


	HBlock expression_resultflag(std::vector<HTerm>& term);
	HBlock stmt_resultflag(std::vector<HTerm>& term);
	HBlock parser_if_condition(HTerm term );
	HBlock  parser_control_else(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	HBlock  parser_control_end(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	HBlock  parser_control_if(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	HBlock parser_control_unless(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	std::list<HBlockControlSelectItem> get_CBlockControlSelectItem(HBlockComandList shared_ptr, ErrorInfo* err);
	HBlockControlSelect parser_control_select(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	 
	HBlockControlSelectItem parser_control_select_item(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);
	HBlock  STMT_control_flux(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo* err);


	std::list<HBlockVerbConjugation> get_verb_conjugations(std::string verb) const;
	HBlock STMT_register_verb(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo* err);
	string expression_adapt_viewPoint(HTerm& term);
	string expression_adapt_tense(HTerm& term);
	HBlock expression_adapt_verb_inner(HTerm& term);
	HBlock expression_adapt_verb(std::vector<HTerm>& term);
	HBlockMatchActionCall parser_actionMatch(HTerm& term);
	HBlock STMT_Action_Controls(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo* err);
};



std::vector<HTerm> decompose(string phase); 
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