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



namespace NSParser
{
	class SourceLine
	{
	public:
		int linenumber;
		string filename;
		string line;
		SourceLine(string _filename, int _linenumber, string _line) :line(_line), linenumber(_linenumber), filename(_filename) {}
	};

	class ErrorInfo
	{
	public:
		bool hasError;
		string msg;
		//SourceLine errorLine;

		ErrorInfo() : hasError(false), msg("") {}
		ErrorInfo(string _msg) : hasError(true), msg(_msg) {}

		void setError(string cs) { msg = cs; hasError = true; }
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
		ParserResult(MatchResult  result, CBlocking::HBlock b) :result(result), block(b)
		{

		}
		ParserResult(const ParserResult  &other) = delete;

		void operator=(ParserResult const &x) = delete;

		ParserResult(ParserResult&& other)
		{
			// pilfer other�s resource
			std::swap(result, other.result);
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
		CBlocking::HBlock  block;
	};



	class UnderstandAction
	{
	public:
		std::vector<HPred> matchPhase;
		CBlocking::HBlockAction   matchAction;
		UnderstandAction(std::vector<HPred> _matching, CBlocking::HBlockAction  _Action) :matchPhase(_matching), matchAction(_Action) {}
	};


	//resolve as chamadas em tempo de execucao
	class staticDispatchEntry
	{
	public:
		staticDispatchEntry(CBlocking::HBlockMatchList  _argumentsMatch, CBlocking::HBlock  _action);
		staticDispatchEntry();
		CBlocking::HBlockMatchList entryArguments;
		CBlocking::HBlock  action;  //actions TO call
	};


	// Class que determina quais frases sao direcionados a quais dynamicDispatchs.. estes sao resolvidos em tempo de compilacao
	class StaticDispatchArgument
	{
	public:
		StaticDispatchArgument(int _entryId) :entryId(_entryId) {};
		std::list<staticDispatchEntry> entries;
		int  entryId;
	};



	class SentenceDispatchPredicate
	{
	public:
		SentenceDispatchPredicate(std::vector<HPred> _matchPhase, CBlocking::HBlockMatch  _matchPhaseDynamic, CBlocking::HBlock _output, int _entryId);
		std::vector<HPred> matchPhase;
		CBlocking::HBlockMatch _matchPhaseDynamic;
		CBlocking::HBlock output;
		int  entryId;
	};


	class DispatchArguments
	{
	public:
		DispatchArguments(std::vector<HPred> _sentencePredicade, CBlocking::HBlockMatchList  static_argument_match, CBlocking::HBlockMatch sentence_match)
			: staticPredicade(_sentencePredicade),
			staticArgumentMatch(static_argument_match),
			sentenceMatch(sentence_match)
		{
		}

		std::vector<HPred> staticPredicade;
		CBlocking::HBlockMatchList   staticArgumentMatch; // Only the arguments
		CBlocking::HBlockMatch   sentenceMatch; //Full Sentence

	};


	class CParser
	{


		 


	public:
		std::vector<CBlocking::NoumDefinition> nregisters;
		Interpreter::HBlockInterpreter interpreter_inner;
		std::map<string, CBlocking::HBlock > verbToRelation;		 
		std::shared_ptr<CPredBooleanOr>  actionPredList;
		std::list< UnderstandAction > actionUndestands;
		std::list<StaticDispatchArgument> staticDispatch;
		std::shared_ptr<CPredBooleanOr>  verbList;
		std::list<SentenceDispatchPredicate> sentenceDispatch;



		CParser(Interpreter::HBlockInterpreter  _interpreter);
		virtual ~CParser();


		void set_Noum(CBlocking::NoumDefinition ndef);
		void set_Noum(CBlocking::NoumDefinitions ndef);



		//Matchs 
		
	 

		CBlocking::HBlockVerbRelation STMT_verb_relation(CBlocking::HBlock a_verb, HTerm term);

 




		int registerStaticDispatch(int entryId, CBlocking::HBlockMatchList  argumentMatch, CBlocking::HBlock body);
		int registerDynamicDispatch(std::vector<HPred> _matchPhase, CBlocking::HBlockMatch entryMatch);
		int registerDynamicDispatch(std::vector<HPred> _matchPhase, CBlocking::HBlockMatch entry, CBlocking::HBlock ret);
		ParserResult parser_AssertionKind(std::vector<HTerm>&  lst);
		CBlocking::HBlockActionApply parse_AssertionAction_ApplyngTo(HTerm term);
		CBlocking::HBlockMatch parser_What_Which_Assertion(HTerm term);
		CBlocking::HBlockMatchIs parser_What_Which_Verb_Assertion(HTerm term);
		CBlocking::HBlockMatchIs parser_Match_IF_Assertion(HTerm term);





		CBlocking::HBlock parseAssertion_isDecide_inLine(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_isDecide_Block(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_isDecide(std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_DecideOn(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlock parserBoolean(HTerm  term);
		CBlocking::HBlock parser_stmt_str(string str, HGroupLines inner, ErrorInfo* err);

		CBlocking::HBlock Parser_Stmt(string str, bool dump);
		CBlocking::HBlock Parser_Expression(string str, bool dump);
		CBlocking::HBlock Parser_Condition(string str, bool dump); // Apenas para testes

		CBlocking::HBlock parser_stmt(string str, bool dump, ErrorInfo* err);

		CBlocking::HBlock parser_GroupLine(std::string v, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlockComandList parser_stmt_inner(HGroupLines inner, ErrorInfo* err);
		std::list<CBlocking::HBlock >  post_process_tokens(std::list< CBlocking::HBlock > list, ErrorInfo* err);

		std::list<CBlocking::HBlock> parser_GroupLines(HGroupLines pivot, ErrorInfo* err);

		CBlocking::HBlock STMT_Definition_Assertion(std::vector<HTerm>&  term);
		CBlocking::HBlockStaticDispatch  getStaticDispatchResolve(HTerm tem);
		//CBlocking::HBlockMatch parser_MatchArgument(std::vector<HTerm>&  term);
		CBlocking::HBlockAssertion_isInstanceOf  parseAssertion_isInstanceOf(std::vector<HTerm>& term);
		CBlocking::HBlockList  parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep);
		CBlocking::HBlockList  parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlocking::HBlockList  CList);
		CBlocking::HBlockList  parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlocking::HBlockList  CList);
		CBlocking::HBlockList  parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlocking::HBlockList  CList);
		CBlocking::HBlockList  parse_Strict_COMMA_AND(HTerm term);
		CBlocking::HBlockList  parse_Strict_COMMA_OR(HTerm term);
		CBlocking::HBlock parseAssertionFirstTerm_Compose(HTerm term);
		CBlocking::HBlock parseAssertionFirstTerm(HTerm match);
		CBlocking::HBlock parseAssertionEnumSecondTerm(HTerm term);
		CBlocking::HBlock STMT_Decide_Assertion(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err);


		//DispatchArguments  parser_buildMatchBlock_actionInput(HTerm term);
		//DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<HTerm>&  term);
		CBlocking::HBlock STMT_understand_generic_redirect(HTerm term, CBlocking::HBlock output_term);


		CBlocking::HBlock STMT_understand_Action_Assertion_static(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_toDecide_Entry(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_toDecide_Ret(std::vector<HTerm>&  term);
		CBlocking::HBlock parser_decides_Assertion(std::vector<HTerm>&  term);
		std::list<CBlocking::HBlock> ToMatchList(std::vector<HPred> pvector, MatchResult result);
		CBlocking::HBlock TryDispatch_action(std::vector<HTerm>& term);
		CBlocking::HBlock STMT_understand_Assertion(std::vector<HTerm>&  term);
		CBlocking::HBlock STMT_verb_Assertion_N(std::vector<HTerm>&  term);
		CBlocking::HBlock STMT_verb_Assertion(std::vector<HTerm>&  lst);

		CBlocking::HBlockEnums  parseAssertion_EnumTerms(HTerm  elist);


		CBlocking::HBlockAssertion_is parse_AssertionVerb(std::vector<HTerm>&  term);
		CBlocking::HBlockKindAction parse_AssertionAction_secondPart(HTerm term);
		CBlocking::HBlock parse_AssertionAction(std::vector<HTerm> term);
		CBlocking::HBlock parse_AssertionIsVariable(std::vector<HTerm>&  lst);
		CBlocking::HBlockKindOfName parse_KindOf(HTerm term);
		CBlocking::HBlock parse_AssertionIsKindOf(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_AssertionValuesOf(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_AssertionDefaultAssign(std::vector<HTerm>&  term);
		CBlocking::HBlockAssertion_is   parse_AssertionDirectAssign(std::vector<HTerm>&  term);


		CBlocking::HBlock   parser_VerbAssign(std::vector<HTerm>& term);



		CBlocking::HBlock parse_removeArticle(std::vector<HTerm>& term);
		CBlocking::HBlock parse_List_AND(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_List_OR(std::vector<HTerm>&  term);
		CBlocking::HBlock parse_noum(std::vector<HTerm>& term);
		CBlocking::HBlock parser_Declaration_Assertion(std::vector<HTerm>&  lst);
		CBlocking::HBlockProperty  parse_PropertyOf(std::vector<HTerm>& term);

		CBlocking::HBlock STMT_canBe_Assertion(std::vector<HTerm>& lst);
		CBlocking::HBlockInstanceVariable  CProperty_called(HTerm term);
		CBlocking::HBlock STMT_hasAn_Assertion(std::vector<HTerm>& lst);
		CBlocking::HBlock parser_stmt(HTerm term, HGroupLines inner, ErrorInfo* err);



		CBlocking::HBlock parserBoolean(std::vector<HTerm>&  term);


		CBlocking::HBlock parser_kind(HTerm term);
		CBlocking::HBlock parser_kind_or_instance(HTerm term);
		CBlocking::HBlock parser_valueReference(HTerm term);
		CBlocking::HBlock parser_assertionTarger(HTerm term);
		CBlocking::HBlock DynamicLookup_Relation(std::vector<HTerm>& term);
		CBlocking::HBlock parser_SeletorVerb(HTerm term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock DynamicLookup_Verb(std::vector<HTerm>& term);
		CBlocking::HBlockSelector parser_List_selector(std::vector<HTerm>&  term);
		CBlocking::HBlockSelector parser_List_selector(HTerm term);
		CBlocking::HBlock parser_expression_lst(std::vector<HTerm>& lst);
		CBlocking::HBlock parser_expression(HTerm term);

		CBlocking::HBlock parser_stmt_inner(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlock text_entry(std::vector<HTerm>&  lst);




		CBlocking::HBlockArgumentInput parser_KindCalled(HTerm term);
		CBlocking::HBlock STMT_relates_Assertion(std::vector<HTerm>&  term);
		CBlocking::HBlock STMT_relates_AssertionWhen(std::vector<HTerm>&  term);
		CBlocking::HBlock parser_SeletorRelation(HTerm term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock parser_SeletorTerm(HTerm term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock DynamicLookup_Seletor(std::vector<HTerm>& term);

		CBlocking::HBlock  DynamicDispatch_action(std::vector<HTerm>&  term);
		 
	 
 
 

		CBlocking::HBlock STMT_system_Assertion(std::vector<HTerm>& term);

		CBlocking::HBlock sys_say_action(std::vector<HTerm>&  term);
		CBlocking::HBlock parser_loop_A(HTerm& term);
		CBlocking::HBlockAssertion_is parse_Loop_AssertionVerb(HTerm& term, CBlocking::NoumLocation nlocation);
		CBlocking::HBlockAssertion_is parse_Loop_AssertionVerb(HTerm& term);
		CBlocking::HBlockAssertion_is parser_loop_B(HTerm& term, CBlocking::HBlock mutedVariable);

		CBlocking::HBlock sys_now_loop(std::vector<HTerm>& term);
		CBlocking::HBlock sys_now_action(std::vector<HTerm>&  term);

		CBlocking::HBlock parser_text(string str, ErrorInfo* err);
		CBlocking::HBlock parser_text(string str, bool dump); 
		HGroupLines get_identation_groups(string filename, std::vector<string> vlines, ErrorInfo* err);


		std::list<CBlocking::HBlockVerbConjugation> get_verb_conjugations(std::string verb) const;
		CBlocking::HBlock STMT_register_verb(std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo* err);
		string expression_adapt_viewPoint(HTerm& term);
		string expression_adapt_tense(HTerm& term);
		CBlocking::HBlock expression_adapt_verb_inner(HTerm& term);
		CBlocking::HBlock expression_adapt_verb(std::vector<HTerm>& term);
	 
	};
	 
	namespace ControlFlux
	{
		CBlocking::HBlock STMT_control_flux(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlock> post_process_tokens(CParser * p, std::list<CBlocking::HBlock> lst, ErrorInfo * err);
		CBlocking::HBlock stmt_resultflag(CParser * p, std::vector<HTerm>& term);
		CBlocking::HBlock parser_if_condition(CParser * p, HTerm term);
		CBlocking::HBlock   parser_control_else(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parser_control_end(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_if(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_unless(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlockControlSelectItem> get_CBlockControlSelectItem(CParser * p, CBlocking::HBlockComandList cmdList, ErrorInfo * err);
		CBlocking::HBlockControlSelect parser_control_select(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlockControlSelectItem parser_control_select_item(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo * err);
		
	};

	namespace Expression
	{
		CBlocking::HBlock  parser_expression(CParser *p, HTerm term);
		CBlocking::HBlock   parser_expression_lst(CParser *p, std::vector<HTerm>&   lst);
	}

	namespace ExpressionMatch
	{
		CBlocking::HBlockMatch parser_expression_match(CParser *p, HTerm term);
		CBlocking::HBlockMatch parser_expression_match(CParser *p, std::vector<HTerm>& term);

	    CBlocking::HBlockMatchProperty parse_PropertyOf_Match(CParser * p, std::vector<HTerm>& term);
	    CBlocking::HBlockMatch parse_match_noum(CParser * p, std::vector<HTerm>& term);
	 
		CBlocking::HBlockMatch  parse_Which_Verb_Match(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatch parse_AssertionVerb_Match(CParser * p, std::vector<HTerm>& term);
		std::list<CBlocking::HBlockMatch>  ToMatchListMatc(CParser *p, std::vector<HPred> pvector, MatchResult result);
		CBlocking::HBlockMatch   parse_Which_DirectAssign_Match(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatch   parse_AssertionDirectAssign_Match(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatch   parser_Verb_Match(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatch   DynamicDispatch_action_match(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatch   parse_match_list(CParser *p, std::vector<HTerm>&     term);



		CBlocking::HBlockMatch  parser_MatchArgument(CParser *p, HTerm term);
		CBlocking::HBlockMatch parser_MatchArgument(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlockMatchIs  parserMatchIsCondition(CParser *p, HTerm term);


		CBlocking::HBlockMatchIsVerb parserMatchIsConditionVerb(CParser *p, HTerm term);
	}

	namespace Statement
	{
		CBlocking::HBlock parser_stmt(CParser * p , string str, bool dump, ErrorInfo* err);
		CBlocking::HBlock parser_stmt(CParser * p, HTerm term, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlockComandList parser_stmt_inner(CParser * p, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlock  parser_stmt_inner(CParser * p, std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err);
	 
	}

	namespace DynamicDispatch
	{ 
		CBlocking::HBlockStaticDispatch  getStaticDispatchResolve(CParser *p, HTerm term);
		
		                                                       
	    NSParser::DispatchArguments  parser_buildMatchBlock_actionInput(CParser *p, HTerm term);		
		NSParser::DispatchArguments  parser_buildMatchBlock_actionInputList(CParser *p, std::vector<HTerm>&  term);

		CBlocking::HBlock  STMT_understand_generic_redirect(CParser *p, HTerm  term, CBlocking::HBlock  output_term);
		CBlocking::HBlock  STMT_understand_Action_Assertion_static(CParser *p, std::vector<HTerm>&  term);
		std::list<CBlocking::HBlock>  ToMatchList(CParser *p, std::vector<HPred> pvector, MatchResult result);
		CBlocking::HBlock  TryDispatch_action(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlock  DynamicDispatch_action(CParser *p, std::vector<HTerm>&  term);

	}

	namespace ParseAction
	{
		CBlocking::HBlockMatchActionCall  parser_actionMatch(CParser * p, HTerm & term);
		CBlocking::HBlock  STMT_Action_Controls(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err);
	}

	namespace ParseRelation
	{
		CBlocking::HBlock    parser_SeletorVerb(CParser *p, HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    STMT_relates_AssertionWhen(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlock    parser_SeletorRelation(CParser *p, HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    parser_SeletorTerm(CParser *p, HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    DynamicLookup_Seletor(CParser *p, std::vector<HTerm>& term);

		CBlocking::HBlockArgumentInput  parser_KindCalled(CParser *p, HTerm term);
		CBlocking::HBlock  STMT_relates_Assertion(CParser *p, std::vector<HTerm>&  term);
	}

	namespace ParseDecide
	{
		CBlocking::HBlockMatch  parser_What_Which_Assertion(CParser * p, HTerm term);
		CBlocking::HBlockMatchIs  parser_What_Which_Verb_Assertion(CParser * p, HTerm term);
		CBlocking::HBlockMatchIs  parser_Match_IF_Assertion(CParser * p, HTerm term);
		CBlocking::HBlock  parseAssertion_isDecide_inLine(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_isDecide(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_DecideOn(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock STMT_Definition_Assertion(CParser * p, std::vector<HTerm>&  term);

	}

};

	std::vector<HTerm> decompose(string phase);
	string  decompose_bracket(string phase, string dlm);
	MTermSet remove_boundaryListMark(MTermSet& m);

	string get_repr(MTermSet lst);
	HPred verb_IS_NOT();
	HPred mk_HPredLiteral(string str);


	HPred verb_IS();
	HPred undefinedArticle();
	HPred mk_HPredLiteral_OR(string _named, std::initializer_list<string> alist);

	HPred mk_What_Which();
	HTerm expandBract(HTerm term);
	std::vector<HTerm> get_tail(std::vector<HTerm>& qlist);
	std::pair<CBlocking::HBlock, HPred>   getVerbAndAux(HTerm  term);
	HPred convert_to_predicate(CTerm *termo);
	string CtoString(HTerm  value);
	string CtoString(CList * lst);
	string CtoString(CTerm  *value);
#endif