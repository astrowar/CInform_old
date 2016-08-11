#pragma once

#include "BlockInterpreter.h"
#include "CBase.h"
#include "CMatch.h"


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
 


 

class CParser
{

	std::vector<NoumDefinition> nregisters;
	CBlockInterpreter *interpreter;

	std::map<string, CBlock* > verbToRelation;
	std::shared_ptr<CPredBooleanOr>  verbList;
	
public:
	CParser(CBlockInterpreter *_interpreter);
	virtual ~CParser();

 
	void set_Noum(NoumDefinition ndef);
	void set_Noum(NoumDefinitions ndef);


	 
	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	CBlock* parse_AssertionAction_ApplyngTo(HTerm term);
	CBlock* parse_AssertionVerb(std::vector<HTerm> term);
	CBlock * parse_AssertionAction(std::vector<HTerm> term);
	 
 
 
 
	CBlock* parseAssertion_isKindOf(std::vector<HTerm> term);
	CBlock* parseAssertion_valuesOf(std::vector<HTerm> term);
	CBlock* parser_What_Assertion(std::vector<HTerm> term);
	CBlock* parseAssertion_DecideWhat( HTerm  term);
	CBlock* parseAssertion_isDecide(std::vector<HTerm> term);
	CBlock* parserBoolean(  HTerm  term);
	CBlock* parser_Definition_Assertion(std::vector<HTerm> term);
	CBlockAssertion_isInstanceOf* parseAssertion_isInstanceOf(std::vector<HTerm> term)  ;
	CBlockList* parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep );
	CBlockList* parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlockList* CList);
	CBlockList* parse_Strict_COMMA_AND(HTerm term );
	CBlockList* parse_Strict_COMMA_OR(HTerm term );
	CBlock* parseAssertionFirstTerm_Compose(HTerm term);
	CBlock* parseAssertionFirstTerm(HTerm match);
	CBlock* parseAssertionEnumSecondTerm(HTerm term);
	CBlock* parser_Decide_Assertion(std::vector<HTerm> lst);
	CBlock* parser_verb_Assertion(std::vector<HTerm> lst);

	CBlockEnums* parseAssertion_EnumTerms(  HTerm  elist);


	CBlock* parseAssertion_isVariable(std::vector<HTerm> lst);
	CBlock* parseAssertion_DefaultAssign(std::vector<HTerm> term);
	CBlockAssertion_is * parseAssertion_DirectAssign(std::vector<HTerm> term);
	CBlock* parse_removeArticle(std::vector<HTerm> term);
	CBlock* parse_List_AND(std::vector<HTerm> term);
	CBlock* parse_noum(std::vector<HTerm> term);
	CBlock* parser_Declaration_Assertion(std::vector<HTerm> lst);
	CBlockProperty* parse_PropertyOf(std::vector<HTerm> term);
 
	CBlock* parser_canBe_Assertion(std::vector<HTerm> lst);
	CBlockInstanceVariable* CProperty_called(HTerm term);
	CBlock* parser_hasAn_Assertion(std::vector<HTerm> lst);
 
	CBlock* parser_only(std::vector<HTerm> lst);
	CBlock*  parser(HTerm term);
	CBlock* parserBoolean(std::vector<HTerm> term);
	CBlock* parser(std::string str);
};

