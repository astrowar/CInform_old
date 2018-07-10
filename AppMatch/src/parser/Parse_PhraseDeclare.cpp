#include <memory>
#include "parser/Parser.hpp"
#include "CBlockDecideIf.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



HBlock NSParser::ParseAssertion::parser_rulePreamble(CParser *p, std::vector<HTerm>&  term)
{
	return nullptr;
}


HBlock NSParser::ParseAssertion::STMT_Declare_rule(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{

		{
			CPredSequence predList = pAny("rulePreamble") << pLiteral("rule") << pLiteral("for") << pAny("target") << pLiteral(":") << pAny("RemainBody");
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{ 
					//HBlock match_Assign = ExpressionMatch::parser_expression_match(p, lst);
					HBlockMatch  ntarget   = ExpressionMatch::parser_expression_match(p, res.matchs["target"]);					
					if (ntarget != nullptr)
					{
						HBlock executeBlock = Statement::parser_stmt(p, res.matchs["RemainBody"], nullptr, err); // aqui tem erro					 
						if (executeBlock != nullptr)
						{
							return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, ntarget, executeBlock);
						}
					}
				}
			}
		}



		{
			CPredSequence predList =  pAny("rulePreamble") << pLiteral("rule") << pLiteral(":") << pAny("RemainBody");
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{				 
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{
				 
					 
					

						HBlock executeBlock = Statement::parser_stmt(p, res.matchs["RemainBody"], nullptr, err); // aqui tem erro					 
						if (executeBlock != nullptr)
						{
							return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, nullptr , executeBlock);
						}
					
				}
			}
		}
	}


	if (inner != nullptr)
	{

		{
			CPredSequence predList = pAny("rulePreamble") << pLiteral("rule") << pLiteral("for") << pAny("target") << pLiteral(":");
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{
					HBlockMatch  ntarget = ExpressionMatch::parser_expression_match(p, res.matchs["target"]);
					if (ntarget != nullptr)
					{
						HBlock executeBlock = Statement::parser_stmt_inner(p, inner, err); // aqui tem erro					 
						if (executeBlock != nullptr)
						{
							return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, ntarget , executeBlock);
						}
					}
				}
			}
		}


		//Com bloco inner 
		{ 
			CPredSequence predList = pAny("rulePreamble") << pLiteral("rule") << pLiteral(":")  ;
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{
					HBlock executeBlock = Statement::parser_stmt_inner(p,inner,err ); // aqui tem erro					 
					if (executeBlock != nullptr)
					{
						return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, nullptr, executeBlock);
					}
				}
			}
		}
	}




	return nullptr;


}


HBlock NSParser::ParseAssertion::STMT_Declare_Phrase(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{
		{
			CPredSequence predList = pLiteral("to") << pWord("InitialWord") << pAny("Match") << pLiteral(":") << pAny("RemainBody");

			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{



			}
		}
	}
	

	if (inner != nullptr)
	{
		//Com bloco inner 
		{

			CPredSequence predList = pLiteral("to") << pWord("InitialWord") << pAny("Match") << pLiteral(":");

			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{




			}
		}
	}




		return nullptr;


	}