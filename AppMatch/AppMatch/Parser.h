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
public:
	CParser();
	virtual ~CParser();
	ParserResult parser_AssertionAction(std::vector<HTerm> lst);
	ParserResult parser_AssertionKind(std::vector<HTerm> lst);
	CBlock* parseAssertionActionDeclare(HTerm term);
	CBlock* parseAssertionSecondTerm(HTerm match);
	CBlockList* parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList* CList);
	CBlock* parseAssertionFirstTerm_Compose(HTerm term);
	CBlock* parseAssertionFirstTerm(HTerm match);
	ParserResult parser_SingleAssertion(std::vector<HTerm> lst);
	ParserResult parserAssertion(std::vector<HTerm> lst);
	CBlock* parser(std::string str);
};

