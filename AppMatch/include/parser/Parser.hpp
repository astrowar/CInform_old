#pragma once
#ifndef CPARSER_H
#define CPARSER_H

#include "base/CBase.hpp"
#include "match/CMatch.hpp"

#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"
#include "CBlockRelation.hpp"
#include "CBlockCommand.hpp"
#include "CBlockControlFlux.hpp"
#include "CblockAssertion.hpp"
#include "CBlockDumpValues.hpp"
#include "CBlockDecideIf.hpp"
#include "Predicates.hpp"




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
        LanguageModule *lang;

		std::vector<CBlocking::NoumDefinition> nregisters;
		// Interpreter::HBlockInterpreter interpreter_inner;
		std::map<string, CBlocking::HBlock > verbToRelation;		 
		std::shared_ptr<NSTerm::CPredBooleanOr>  actionPredList;
		std::list< UnderstandAction > actionUndestands;
		std::list<StaticDispatchArgument> staticDispatch;
		std::shared_ptr<NSTerm::CPredBooleanOr>  verbList;
		std::list<SentenceDispatchPredicate> sentenceDispatch;
		std::list<CBlocking::HBlockPhraseHeader> phrases;

		std::list<NSTerm::HTerm> ruleList;


		CBlocking::HBlock blank_line;

		CParser(  LanguageModule * _lang );
		virtual ~CParser();


		void set_Noum(CBlocking::NoumDefinition ndef);
		void set_Noum(CBlocking::NoumDefinitions ndef);


		int phase_id;

		//Matchs 
 
	 

	 
		int registerStaticDispatch(int entryId, CBlocking::HBlockMatchList  argumentMatch, CBlocking::HBlock body);
		int registerDynamicDispatch(std::vector<NSTerm::HPred> _matchPhase, CBlocking::HBlockMatch entryMatch);
		int registerDynamicDispatch(std::vector<NSTerm::HPred> _matchPhase, CBlocking::HBlockMatch entry, CBlocking::HBlock ret);
	 
		CBlocking::HBlock Parser_Condition(string str, bool dump); // Apenas para testes
 
		HBlockNoum get_next_headerName();
 
 
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
		CBlocking::HBlock STMT_unit_test(CParser * p, std::vector< NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);		
		CBlocking::HBlock STMT_pass(CParser * p, std::vector< NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlock> post_process_tokens(CParser * p, std::list<CBlocking::HBlock> lst, ErrorInfo * err);
		CBlocking::HBlock stmt_resultflag(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock parser_if_condition(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock   parser_control_else(CParser *p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock parser_control_end(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_for_loop(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_if(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock parser_control_unless(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		std::list<CBlocking::HBlockControlSelectItem> get_CBlockControlSelectItem(CParser * p, CBlocking::HBlockComandList cmdList, ErrorInfo * err);
		CBlocking::HBlockControlSelect parser_control_select(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlockControlSelectItem parser_control_select_item(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo * err);
		
	};

	namespace Expression
	{

		CBlocking::HBlockNoum  parser_noum_expression(CParser *p, std::vector<string> term);
		CBlocking::HBlockNoum  parser_noum_expression(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  parser_expression(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  parser_expression_lst(CParser *p, std::vector<NSTerm::HTerm>&   lst);

		CBlocking::HBlock  parser_noumList(CParser *p, NSTerm::HTerm   lst);


		CBlocking::HBlock parser_kind(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockKind parser_kind_specification(CParser *p, NSTerm::HTerm term);

		CBlocking::HBlockKind  parse_CompositionOf(CParser * p, NSTerm::HTerm  term);

		CBlocking::HBlock parser_kind_or_instance(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parser_valueReference(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parser_assertionTarger(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  Parser_Expression(CParser * p, string str, bool dump);

		
		CBlocking::HBlock   parser_ComponentePhase(CParser *p, NSTerm::HTerm    lst);
		 std::vector<CBlocking::HBlock  >   getTriPartition_phase_item(CParser *p, std::vector< NSTerm::HTerm> & vs);
		//std::list<std::vector<HTerm   > >  NSParser::Expression::getTriPartition_phase_item(std::vector<HTerm> & vs)

	 
	  CBlocking::HBlockList   parser_phrase_literal_entry(CParser *p, std::vector<NSTerm::HTerm>&    lst);
		CBlocking::HBlockList   parser_phrase_literal(CParser *p, std::vector<NSTerm::HTerm>&    lst);
	}

	namespace User
	{
		CBlocking::HBlockUserParser  parser_input_syntax(CParser *p, NSTerm::HTerm  literalInput);
	}

	namespace ExpressionMatch
	{
		CBlocking::HBlockMatchNoum parser_expression_match_noum(CParser *p, string);
		CBlocking::HBlockMatchNoum parser_expression_match_noum(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parser_expression_match(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parser_expression_match(CParser *p, std::vector<NSTerm::HTerm>& term);


	    CBlocking::HBlockMatchProperty parse_PropertyOf_Match(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockMatchNoum parse_match_SigleNoum(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parse_match_muteVariable(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockMatch parse_match_noum(CParser * p, std::vector<NSTerm::HTerm> term);
	 
		CBlocking::HBlockMatch  parse_Which_Verb_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch parse_AssertionAdverb_Match(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockMatch parse_AssertionVerb_Match(CParser * p, std::vector<NSTerm::HTerm>& term);
		std::list<CBlocking::HBlockMatch>  ToMatchListMatc(CParser *p, std::vector<NSTerm::HPred> pvector, NSTerm::NSMatch::MatchResult result);
		CBlocking::HBlockMatch   parse_Which_DirectAssign_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   parse_AssertionDirectAssign_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   parser_Verb_Match(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatch   DynamicDispatch_action_match(CParser *p, std::vector<NSTerm::HTerm>&  term);

	 
		CBlocking::HBlockMatchOR  parse_match_or_list(CParser * p, std::vector<HTerm>& term);
		CBlocking::HBlockMatchOR  parse_match_or_list(CParser * p, NSTerm::HTerm term);

		CBlocking::HBlockMatchList  parse_match_comma_list(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatchList parse_match_comma_list(CParser * p, std::vector<NSTerm::HTerm>& term);
		 
	 
		CBlocking::HBlockMatchList    parse_match_list(CParser *p, std::vector<NSTerm::HTerm>&     term);
		CBlocking::HBlockMatchList    parse_match_list_inn(CParser *p, std::vector<NSTerm::HTerm>&     term);

	    CBlocking::HBlockMatch parse_APreposition(CParser * p, std::vector<NSTerm::HTerm>& term);


		CBlocking::HBlockMatch  parser_MatchArgument_kind_item(CParser *p, string term);
		CBlocking::HBlockMatchKind   parser_MatchKind(CParser *p, NSTerm::HTerm sNoum);


		CBlocking::HBlockMatch   parser_MatchComponentePhase(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch   parser_MatchVariableDeclare(CParser *p, NSTerm::HTerm term);
	 
		CBlocking::HBlockMatch  parser_MatchArgument_only(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch  parser_MatchArgument(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlockMatch parser_MatchArgument(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlockMatchIs  parserMatchIsCondition(CParser *p, NSTerm::HTerm term);


		CBlocking::HBlockMatchIsVerb parserMatchIsConditionVerb(CParser *p, NSTerm::HTerm term);
	}

	namespace Statement
	{
		CBlocking::HBlock parser_stmt(CParser * p , string str, bool dump, ErrorInfo* err);
		CBlocking::HBlock parser_stmt(CParser * p, NSTerm::HTerm term, HGroupLines inner, ErrorInfo* err);

		 

		CBlocking::HBlockComandList parser_stmt_list(CParser * p, bool top, HGroupLines inner, ErrorInfo* err);

		 
        CBlocking::HBlock  parser_stmt_call(CParser * p, std::vector<NSTerm::HTerm> lst);

		
		CBlocking::HBlock  parser_stmt_top(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  parser_stmt_inner(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  parserBoolean(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  parserBoolean(CParser * p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlock  parser_stmt_str(CParser * p, string str, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  Parser_Stmt(CParser * p, string str, bool dump);
		CBlocking::HBlock   parser_GroupLine(CParser * p, std::string v, bool topLevel, HGroupLines inner, ErrorInfo *err);
 

		std::list<CBlocking::HBlock> Text_Sentence_bakret(CParser * p, std::string text);

		CBlocking::HBlock Text_Sentence(CParser * p, std::string text);

		CBlocking::HBlock  text_entry(CParser * p, std::vector<NSTerm::HTerm>&  term);

		CBlocking::HBlock text_literal(CParser * p, std::vector<NSTerm::HTerm>& term);

		namespace Verbal
		{
			CBlocking::HBlock  STMT_verb_Assertion(CParser * p, std::vector<NSTerm::HTerm>&  term, ErrorInfo *err);
			CBlocking::HBlockVerbRelation STMT_verb_relation(CParser * p, CBlocking::HBlock a_verb, NSTerm::HTerm term, ErrorInfo *err);
			CBlocking::HBlock   STMT_verb_Assertion_N(CParser * p, std::vector<NSTerm::HTerm>&  term, ErrorInfo *err);
		 
		}
	}

	namespace DynamicDispatch
	{ 
		CBlocking::HBlockStaticDispatch  getStaticDispatchResolve(CParser *p, NSTerm::HTerm term);
		
		                                                       
		NSParser::DispatchArguments  parser_user_parser(CParser *p, HTerm termLiteral);

	    NSParser::DispatchArguments  parser_buildMatchBlock_actionInput(CParser *p, NSTerm::HTerm term);		
		NSParser::DispatchArguments  parser_buildMatchBlock_actionInputList(CParser *p, std::vector<NSTerm::HTerm>&  term);

		CBlocking::HBlock  STMT_understand_generic_redirect(CParser *p, NSTerm::HTerm  term, CBlocking::HBlock  output_term);
		CBlocking::HBlock  STMT_understand_Action_Assertion_static(CParser *p, std::vector<NSTerm::HTerm>&  term);
		std::list<CBlocking::HBlock>  ToMatchList(CParser *p, std::vector<NSTerm::HPred> pvector, NSTerm::NSMatch::MatchResult result);
		CBlocking::HBlock Dispatch_action_call(CParser * p, NSTerm::HTerm term);

	 
		CBlocking::HBlock  Instead_phase(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  TryDispatch_action(CParser *p, std::vector<NSTerm::HTerm>&  term);
		 
		CBlocking::HBlock parser_PhraseRelationInvoke(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock parser_PhraseInvoke(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  DynamicDispatch_action(CParser *p, std::vector<NSTerm::HTerm>&  term);

		
		CBlocking::HBlock  rule_spec(CParser *p, NSTerm::HTerm  term);
		CBlocking::HBlock  Follow_rule(CParser *p, std::vector<NSTerm::HTerm>&  term);

	 

	}

	namespace ParseAction
	{
		CBlocking::HBlockMatchActionCall  parser_actionMatch(CParser * p, NSTerm::HTerm & term);
		CBlocking::HBlock  STMT_Action_Controls(CParser * p, std::vector<NSTerm::HTerm>& term, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock   STMT_phrase_Invoken(CParser * p, std::vector<NSTerm::HTerm>& term);
	
		CBlocking::HBlock  sys_say_action(CParser * p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseRelation
	{
		CBlocking::HBlock    parser_SeletorVerb(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    STMT_relates_AssertionWhen(CParser *p, std::vector<NSTerm::HTerm>&  term);
		string parser_RelationNameID(NSParser::CParser * c_parser, NSTerm::HTerm term);
		CBlocking::HBlock    parser_SeletorRelation(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    parser_SeletorTerm(CParser *p, NSTerm::HTerm   term, CBlocking::HBlockMatch muteVariable);
		CBlocking::HBlock    DynamicLookup_Seletor(CParser *p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlockArgumentInput  parser_KindCalled(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_relates_Assertion(CParser *p, std::vector<NSTerm::HTerm>&  term);
	}

	namespace ParseDecide
	{		 
		 
 
		CBlocking::HBlockMatch  parseDecidePhaseMatchEntry_i(CParser * p, NSTerm::HTerm  term_in);

		CBlocking::HBlockMatchList  parseDecidePhaseMatchEntry(CParser * p, std::vector<HTerm> term_lst);
		CBlocking::HBlockMatchList  parseDecidePhaseMatchEntry(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatch  parseDecidePhaseMatchEntry(CParser * p, std::list<std::vector<NSTerm::HTerm > > terms);
		

		CBlocking::HBlockMatchList  parser_match_body(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockPhraseHeader  parser_What_Which_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatchIs  parser_What_Which_Verb_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockMatchIs  parser_Match_IF_Assertion(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockToDecide  parseAssertion_isDecide_inLine(CParser * p, std::vector<NSTerm::HTerm>&  term, HGroupLines inner, ErrorInfo *err);
		std::pair<HBlockMatchList, HBlockMatchList>   parser_match_phraseHeader(CParser * p, NSTerm::HTerm  term, int args_i_item);
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
		CBlocking::HBlockNoum  parse_noum_single(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockNoum  parse_noum(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockNoum  parse_noumVec(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  STMT_Decide_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock  parse_PropertyOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		 
		CBlocking::HBlock   parse_CompositionKindArgument(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock   parse_RelationArgument(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  STMT_Decide_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo *err);
		CBlocking::HBlock   parse_PropertyOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockInstanceVariable  CProperty_called(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_hasAn_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockEnums  parseAssertion_EnumTerms(CParser * p, NSTerm::HTerm enumList);
		CBlocking::HBlock  STMT_canBe_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockInstanceVariable  CProperty_called(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  STMT_hasAn_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockList   parseAssertionFirstTerm_COMMA_Supl(CParser * p, NSTerm::HTerm term, NSTerm::HPred sep, CBlocking::HBlockList cList);
		CBlocking::HBlockList parseAssertionList_COMMA_neutral(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlockList parseAssertionFirstTerm_COMMA_neutral(CParser * p, NSTerm::HTerm term, CBlocking::HBlockList cList);
		CBlocking::HBlockAssertion_is parse_AssertionAdverb(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockAssertion_is  parse_AssertionVerb(CParser *p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock parseAssertionFirstTerm(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parseAssertionFirstTerm_Compose(CParser *p, NSTerm::HTerm term);
		CBlocking::HBlock parseAssertionEnumSecondTerm(CParser *p, NSTerm::HTerm term);
		//CBlocking::HBlockActionApply  parse_AssertionAction_ApplyngTo(CParser * p, NSTerm::HTerm term);
		ParserResult  parser_AssertionKind(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockActionApply parse_AssertionAction_ApplyngTo(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock  parser_Declaration_Assertion(CParser * p, std::vector<NSTerm::HTerm>& lst);
		CBlocking::HBlockAssertion_is  parse_AssertionDirectAssign(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionDefaultAssign(CParser *p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionValuesOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock parse_ActionCompositionName(CParser * p, bool two_noums, NSTerm::HTerm term);		
		CBlocking::HBlock  parse_AssertionRulebook(CParser * p, std::vector<NSTerm::HTerm> term);
		CBlocking::HBlock  parse_AssertionAction(CParser * p, std::vector<NSTerm::HTerm> term);
		CBlocking::HBlock parse_AssertionIsLocalValue(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionIsVariable(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlockKindOfName  parse_KindOf(CParser * p, NSTerm::HTerm  term);
		CBlocking::HBlockKind  parse_CompositionOf(CParser * p, NSTerm::HTerm term);
		CBlocking::HBlock parse_AssertionIsCompositionOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  parse_AssertionIsKindOf(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock   parser_VerbAssign(CParser * p, std::vector<NSTerm::HTerm>& term);

		CBlocking::HBlock   STMT_system_call(CParser * p, std::vector<NSTerm::HTerm>& term);
		CBlocking::HBlock  sys_now_action(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock  sys_now_loop(CParser * p, std::vector<NSTerm::HTerm>&  term);
		CBlocking::HBlock parse_decide_on(CParser* c_parser, std::vector<std::shared_ptr<NSTerm::CTerm>> lst);
		CBlocking::HBlock STMT_Declare_Phrase(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo * err);


		CBlocking::HBlock parser_rulePreamble(CParser *p, std::vector<HTerm>&  term);
		CBlocking::HBlock STMT_Declare_rule_action(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo * err);
		CBlocking::HBlock STMT_Declare_rule(CParser * p, std::vector<NSTerm::HTerm>& lst, HGroupLines inner, ErrorInfo * err);
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
		CBlocking::HBlock parse_List_Neutral(CParser * p, std::vector<NSTerm::HTerm>& term);

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
		std::list<CBlocking::HBlockVerbConjugation> get_verb_conjugations( std::string verb);
		string  expression_adapt_viewPoint(CParser * p, NSTerm::HTerm& term);
		string  expression_adapt_tense(CParser * p, NSTerm::HTerm& term);
		CBlocking::HBlockVerbAdapt  expression_adapt_verb_inner(CParser * p,  NSTerm::HTerm& term);
		CBlocking::HBlock  expression_adapt_verb(CParser * p, std::vector<NSTerm::HTerm>& term);
	}
};

bool is_empty_string(std::string s);
	std::vector<NSTerm::HTerm> decompose(string phase);
	std::vector<NSTerm::HTerm> decompose_syntax(string phase);
	 
	string  decompose_bracket(string phase, string dlm);
NSTerm::MTermSet remove_boundaryListMark(NSTerm::MTermSet& m);

	string get_repr(NSTerm::MTermSet lst);
	NSTerm::HPred verb_IS_NOT();
	NSTerm::HPred pLiteral(string str);


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

	std::list<std::pair<HTerm, HTerm> > getBiPartition(std::vector<HTerm> & vs);
	std::list<std::pair<HTerm, HTerm> > getBiPartition(HTerm & term);
	std::list<std::vector<HTerm > > getBiPartition_v(HTerm & term);
	std::list<std::vector<HTerm> > getTriPartition(HTerm & term);
	std::list<std::vector<HTerm> > getTriPartition(std::vector<HTerm> & term);

	std::list<std::vector<HTerm > > getQuadPartition(std::vector<HTerm> & vs);
	std::list<std::vector<HTerm > > getQuadPartition(HTerm & term);


	std::list<std::vector<HTerm > > getQuiPartition(std::vector<HTerm> & vs);
	std::list<std::vector<HTerm > > getQuiPartition(HTerm & term);

	std::list<std::list<HBlock > > getBiPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func);
	std::list<std::list<HBlock > > getTriPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func);
	std::list<std::list<HBlock > > getQuadPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func);
	std::list<std::list<HBlock > > getQuiPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func);
	std::list<std::list<HBlock > > getHexPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func);
 

	std::vector<std::string> split_string(const std::string& str, const std::string& delimiter);

#endif