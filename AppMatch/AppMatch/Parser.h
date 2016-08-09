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
	
public:
	CParser();
	virtual ~CParser();

	CBlock*  get_Noum(string named) const;
	void set_Noum(NoumDefinition ndef);
	void set_Noum(NoumDefinitions ndef);


	ParserResult parser_AssertionAction(std::vector<HTerm> lst);
	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	CBlockActionApply* parseAssertionActionDeclare( HTerm  term);
 
 
	CBlockAssertion_isActionOf* parseAssertion_isAction(std::vector<HTerm> term);
	CBlock* parseAssertion_isKindOf(std::vector<HTerm> term);
	CBlock* parseAssertion_valuesOf(std::vector<HTerm> term);
	CBlock* parseAssertion_DecideWhat( HTerm  term);
	CBlock* parseAssertion_isDecide(std::vector<HTerm> term);
	CBlockAssertion_isInstanceOf* parseAssertion_isInstanceOf(std::vector<HTerm> term)  ;
	CBlockList* parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList* CList);
	CBlockList* parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlockList* CList);
	CBlock* parseAssertionFirstTerm_Compose(HTerm term);
	CBlock* parseAssertionFirstTerm(HTerm match);
	CBlock* parseAssertionEnumSecondTerm(HTerm term);
	CBlock* parser_Decide_Assertion(std::vector<HTerm> lst);

	CBlockProperty * parseAssertion_PropertyFirstTerm(   HTerm  term);
	CBlockEnums* parseAssertion_EnumTerms(  HTerm  elist);


	CBlock* parseAssertion_isVariable(std::vector<HTerm> lst);
	CBlock* parser_Declaration_Assertion(std::vector<HTerm> lst);
	CBlock* parser_canBe_Assertion(std::vector<HTerm> lst);
	CBlockInstanceVariable* CProperty_called(HTerm term);
	CBlock* parser_hasAn_Assertion(std::vector<HTerm> lst);
	CBlock* parser_only(std::string str);

	CBlock* parser(std::string str);
};

