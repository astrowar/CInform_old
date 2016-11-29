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
		ParserResult(NSTerm::NSMatch::MatchResult  result)
			: result(result)
		{
			block = nullptr;
		}
		ParserResult(NSTerm::NSMatch::MatchResult  result, CBlocking::HBlock b) :result(result), block(b)
		{

		}
		ParserResult(const ParserResult  &other) = delete;

		void operator=(ParserResult const &x) = delete;

		ParserResult(ParserResult&& other)
		{
			// pilfer other,s resource
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

		NSTerm::NSMatch::MatchResult result;
		CBlocking::HBlock  block;
	};



	class UnderstandAction
	{
	public:
		std::vector< NSTerm::HPred> matchPhase;
		CBlocking::HBlockAction   matchAction;
		UnderstandAction(std::vector< NSTerm::HPred> _matching, CBlocking::HBlockAction  _Action) :matchPhase(_matching), matchAction(_Action) {}
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
		SentenceDispatchPredicate(std::vector<NSTerm::HPred> _matchPhase, CBlocking::HBlockMatch  _matchPhaseDynamic, CBlocking::HBlock _output, int _entryId);
		std::vector<NSTerm::HPred> matchPhase;
		CBlocking::HBlockMatch _matchPhaseDynamic;
		CBlocking::HBlock output;
		int  entryId;
	};


	class DispatchArguments
	{
	public:
		DispatchArguments(std::vector<NSTerm::HPred> _sentencePredicade, CBlocking::HBlockMatchList  static_argument_match, CBlocking::HBlockMatch sentence_match)
			: staticPredicade(_sentencePredicade),
			staticArgumentMatch(static_argument_match),
			sentenceMatch(sentence_match)
		{
		}

		std::vector<NSTerm::HPred> staticPredicade;
		CBlocking::HBlockMatchList   staticArgumentMatch; // Only the arguments
		CBlocking::HBlockMatch   sentenceMatch; //Full Sentence

	};


	class CParser
	{


		 


	public:
		std::vector<CBlocking::NoumDefinition> nregisters;
		Interpreter::HBlockInterpreter interpreter_inner;
		std::map<string, CBlocking::HBlock > verbToRelation;		 
		std::shared_ptr<NSTerm::CPredBooleanOr>  actionPredList;
		std::list< UnderstandAction > actionUndestands;
		std::list<StaticDispatchArgument> staticDispatch;
		std::shared_ptr<NSTerm::CPredBooleanOr>  verbList;
		std::list<SentenceDispatchPredicate> sentenceDispatch;



		CParser(Interpreter::HBlockInterpreter  _interpreter);
		virtual ~CParser();


		void set_Noum(CBlocking::NoumDefinition ndef);
		void set_Noum(CBlocking::NoumDefinitions ndef);



		//Matchs 
		
	 

	 
		int registerStaticDispatch(int entryId, CBlocking::HBlockMatchList  argumentMatch, CBlocking::HBlock body);
		int registerDynamicDispatch(std::vector<NSTerm::HPred> _matchPhase, CBlocking::HBlockMatch entryMatch);
		int registerDynamicDispatch(std::vector<NSTerm::HPred> _matchPhase, CBlocking::HBlockMatch entry, CBlocking::HBlock ret);
	 
		CBlocking::HBlock Parser_Condition(string str, bool dump); // Apenas para testes
 
	 
 
 
		//CBlocking::HBlockMatch parser_MatchArgument(std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockAssertion_isInstanceOf  parseAssertion_isInstanceOf(std::vector<NSTerm::HTerm>& term); 
 
		//DispatchArguments  parser_buildMatchBlock_actionInput(NSTerm::HTerm term);
		//DispatchArguments  parser_buildMatchBlock_actionInput(std::vector<NSTerm::HTerm>&  term);
 
 
 
	 
 
	 
	};
	namespace ParseText
	{
		NSParser::HGroupLines  get_identation_groups(CParser *p, string filename, std::vector<string> vlines, ErrorInfo *err);
		CBlocking::HBlock  parser_text(CParser *p, string str, ErrorInfo *err);
		CBlocking::HBlock parser_text(CParser *p, string str, bool dump);

	}
	namespace ControlFlux
	{
		CBlocking::HBlock STMT_control_flux(CParser * p, std::vector< NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlock> post_process_tokens(CParser * p, std::list<CBlocking::HBlock> lst, ErrorInfo * err);
		CBlocking::HBlock stmt_resultflag(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock parser_if_condition(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock   parser_control_else(CParser *p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parser_control_end(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_if(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_unless(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlockControlSelectItem> get_CBlockControlSelectItem(CParser * p, CBlocking::HBlockComandList cmdList, ErrorInfo * err);
		CBlocking::HBlockControlSelect parser_control_select(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlockControlSelectItem parser_control_select_item(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		
	};

	namespace Expression
	{
		CBlocking::HBlock  parser_expression(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  parser_expression_lst(CParser *p, std::vector<NSTerm::HTerm>&   lst);

		CBlocking::HBlock parser_kind(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parser_kind_or_instance(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parser_valueReference(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parser_assertionTarger(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  Parser_Expression(CParser * p, string str, bool dump);
	}

	namespace ExpressionMatch
	{
		CBlocking::HBlockMatch parser_expression_match(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parser_expression_match(CParser *p, std::vector<NSTerm::HTerm>& term);

	    CBlocking::HBlockMatchProperty parse_PropertyOf_Match(CParser * p, std::vector<NSTerm::HTerm>& term);
	    CBlocking::HBlockMatch parse_match_noum(CParser * p, std::vector<NSTerm::HTerm>& term);
	 
		CBlocking::HBlockMatch  parse_Which_Verb_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch parse_AssertionVerb_Match(CParser * p, std::vector<NSTerm::HTerm>& term);
		std::list<CBlocking::HBlockMatch>  ToMatchListMatc(CParser *p, std::vector<NSTerm::HPred> pvector, NSTerm::NSMatch::MatchResult result);
		CBlocking::HBlockMatch   parse_Which_DirectAssign_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   parse_AssertionDirectAssign_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   parser_Verb_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   DynamicDispatch_action_match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   parse_match_list(CParser *p, std::vector<NSTerm::HTerm>&     term);



		CBlocking::HBlockMatch  parser_MatchArgument(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parser_MatchArgument(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatchIs  parserMatchIsCondition(CParser *p, NSTerm::HTerm term);


		CBlocking::HBlockMatchIsVerb parserMatchIsConditionVerb(CParser *p, NSTerm::HTerm term);
	}

	namespace Statement
	{
		CBlocking::HBlock parser_stmt(CParser * p , string str, bool dump, ErrorInfo* err);
		CBlocking::HBlock parser_stmt(CParser * p, NSTerm::HTerm term, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlockComandList parser_stmt_inner(CParser * p, HGroupLines inner, ErrorInfo* err);
		CBlocking::HBlock  parser_stmt_inner(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  parserBoolean(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  parserBoolean(CParser * p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlock  parser_stmt_str(CParser * p, string str, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  Parser_Stmt(CParser * p, string str, bool dump);
		CBlocking::HBlock   parser_GroupLine(CParser * p, std::string v, HGroupLines inner, ErrorInfo *err);
 

		CBlocking::HBlock  text_entry(CParser * p, std::vector<NSTerm::HTerm>&  term);

		namespace Verbal
		{
			CBlocking::HBlock  STMT_verb_Assertion(CParser * p, std::vector<NSTerm::HTerm>&  term);
			CBlocking::HBlockVerbRelation STMT_verb_relation(CParser * p, CBlocking::HBlock a_verb, NSTerm::HTerm term);
			CBlocking::HBlock   STMT_verb_Assertion_N(CParser * p, std::vector<NSTerm::HTerm>&  term);
		}
	}

	namespace DynamicDispatch
	{ 
		CBlocking::HBlockStaticDispatch  getStaticDispatchResolve(CParser *p, NSTerm::HTerm term);
		
		                                                       
	    NSParser::DispatchArguments  parser_buildMatchBlock_actionInput(CParser *p, NSTerm::HTerm term);		
		NSParser::DispatchArguments  parser_buildMatchBlock_actionInputList(CParser *p, std::vector<NSTerm::HTerm>&  term);

		CBlocking::HBlock  STMT_understand_generic_redirect(CParser *p, NSTerm::HTerm  term, CBlocking::HBlock  output_term);
		CBlocking::HBlock  STMT_understand_Action_Assertion_static(CParser *p, std::vector<NSTerm::HTerm>&  term);
		std::list<CBlocking::HBlock>  ToMatchList(CParser *p, std::vector<NSTerm::HPred> pvector, NSTerm::NSMatch::MatchResult result);
		CBlocking::HBlock  TryDispatch_action(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  DynamicDispatch_action(CParser *p, std::vector<NSTerm::HTerm>&  term);

	}

	namespace ParseAction
	{
		CBlocking::HBlockMatchActionCall  parser_actionMatch(CParser * p, NSTerm::HTerm & term);
		CBlocking::HBlock  STMT_Action_Controls(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo *err);
	
		CBlocking::HBlock  sys_say_action(CParser * p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseRelation
	{
		CBlocking::HBlock    parser_SeletorVerb(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    STMT_relates_AssertionWhen(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock    parser_SeletorRelation(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    parser_SeletorTerm(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    DynamicLookup_Seletor(CParser *p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlockArgumentInput  parser_KindCalled(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_relates_Assertion(CParser *p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseDecide
	{
		CBlocking::HBlockMatch  parser_What_Which_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatchIs  parser_What_Which_Verb_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatchIs  parser_Match_IF_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  parseAssertion_isDecide_inLine(CParser * p, std::vector<NSTerm::HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_isDecide(CParser * p, std::vector<NSTerm::HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parseAssertion_DecideOn(CParser * p, std::vector<NSTerm::HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock STMT_Definition_Assertion(CParser * p, std::vector<NSTerm::HTerm>&  term);

		CBlocking::HBlock  parse_toDecide_Entry(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  parse_toDecide_Ret(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  parser_decides_Assertion(CParser * p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseAssertion
	{

		CBlocking::HBlockAssertion_is parse_Loop_AssertionVerb(CParser * p, NSTerm::HTerm&  term, CBlocking::NoumLocation nlocation);
		CBlocking::HBlock  STMT_understand_Assertion(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock parse_removeArticle(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_noum(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  STMT_Decide_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlockProperty  parse_PropertyOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  STMT_Decide_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlockProperty  parse_PropertyOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockInstanceVariable  CProperty_called(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_hasAn_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockEnums  parseAssertion_EnumTerms(CParser * p, NSTerm::HTerm enumList);
		CBlocking::HBlock  STMT_canBe_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockInstanceVariable  CProperty_called(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_hasAn_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockList   parseAssertionFirstTerm_COMMA_Supl(CParser * p, NSTerm::HTerm term, NSTerm::HPred sep, CBlocking::HBlockList cList);
		CBlocking::HBlockAssertion_is  parse_AssertionVerb(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock parseAssertionFirstTerm(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parseAssertionFirstTerm_Compose(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parseAssertionEnumSecondTerm(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockActionApply  parse_AssertionAction_ApplyngTo(CParser * p, NSTerm::HTerm term);
		ParserResult  parser_AssertionKind(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlock  parser_Declaration_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockAssertion_is  parse_AssertionDirectAssign(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionDefaultAssign(CParser *p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionValuesOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionAction(CParser * p, std::vector<NSTerm::HTerm> term);
		CBlocking::HBlock  parse_AssertionIsVariable(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockKindOfName  parse_KindOf(CParser * p, NSTerm::HTerm  term);
		CBlocking::HBlock  parse_AssertionIsKindOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock   parser_VerbAssign(CParser * p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlock   STMT_system_Assertion(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  sys_now_action(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  sys_now_loop(CParser * p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseAssertionSecondary
	{
		CBlocking::HBlockKindAction  parse_AssertionAction_secondPart(CParser * p, NSTerm::HTerm  term);
 
	}

	

	namespace ParseList
	{
		CBlocking::HBlockList  parseAssertion_Strict_COMMA_Supl(CParser * p, NSTerm::HTerm term, NSTerm::HPred sep);
		CBlocking::HBlockList  parseAssertionFirstTerm_COMMA_AND(CParser * p, NSTerm::HTerm term, CBlocking::HBlockList CList);
		CBlocking::HBlockList  parseAssertionFirstTerm_COMMA_OR(CParser * p, NSTerm::HTerm term, CBlocking::HBlockList CList);
		CBlocking::HBlock  parse_List_AND(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_List_OR(CParser * p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlockList  parse_Strict_COMMA_AND(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockList  parse_Strict_COMMA_OR(CParser * p, NSTerm::HTerm term);
	}

	namespace ParseSelector
	{
		CBlocking::HBlockSelector parser_List_selector(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockSelector parser_List_selector(CParser * p, NSTerm::HTerm term);
	}

	namespace ParseGrammar
	{
		CBlocking::HBlock  STMT_register_verb(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo* err);
		std::list<CBlocking::HBlockVerbConjugation> get_verb_conjugations(CParser * p, std::string verb);
		string  expression_adapt_viewPoint(CParser * p, NSTerm::HTerm& term);
		string  expression_adapt_tense(CParser * p, NSTerm::HTerm& term);
		CBlocking::HBlock  expression_adapt_verb_inner(CParser * p,  NSTerm::HTerm& term);
		CBlocking::HBlock  expression_adapt_verb(CParser * p, std::vector<NSTerm::HTerm>& term);
	}
};

	std::vector<NSTerm::HTerm> decompose(string phase);
	string  decompose_bracket(string phase, string dlm);
NSTerm::MTermSet remove_boundaryListMark(NSTerm::MTermSet& m);

	string get_repr(NSTerm::MTermSet lst);
	NSTerm::HPred verb_IS_NOT();
	NSTerm::HPred mk_HPredLiteral(string str);


	NSTerm::HPred verb_IS();
	NSTerm::HPred undefinedArticle();
	NSTerm::HPred mk_HPredLiteral_OR(string _named, std::initializer_list<string> alist);

	NSTerm::HPred mk_What_Which();
	NSTerm::HTerm expandBract(NSTerm::HTerm term);
	std::vector<NSTerm::HTerm> get_tail(std::vector<NSTerm::HTerm>& qlist);
	std::pair<CBlocking::HBlock, NSTerm::HPred>   getVerbAndAux(NSTerm::HTerm  term);
	NSTerm::HPred convert_to_predicate(NSTerm::CTerm *termo);
	string CtoString(NSTerm::HTerm  value);
	string CtoString(NSTerm::CList * lst);
	string CtoString(NSTerm::CTerm  *value);
#endif