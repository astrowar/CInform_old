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

HBlock NSParser::ParseAssertion::STMT_Declare_rule_action(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	CPredSequence pred_base =   pAny("target") << pLiteral(":") << pAny("RemainBody");
	MatchResult res_base = CMatch(term, pred_base);
	if (res_base.result != EqualResulting::Equals)
	{
		return nullptr;
	}

	for (auto r : p->ruleList)
	{
		auto pred = convert_to_predicate(r.get());

		CPredSequence predList = pred << pAny("target") << pLiteral(":") << pAny("RemainBody");
		MatchResult res = CMatch(term, predList);
		if (res.result == EqualResulting::Equals)
		{
			HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, r);
			if (noum_rulebook != nullptr)
			{
				HBlockMatch  ntarget = ExpressionMatch::parser_expression_match(p, res.matchs["target"]);
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

	return nullptr;


}
HBlock NSParser::ParseAssertion::STMT_Declare_rule(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{


	auto raction = STMT_Declare_rule_action(p, term, inner, err);
	if (raction != nullptr) return raction;


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
					HBlockMatch  ntarget = ExpressionMatch::parser_expression_match(p, res.matchs["target"]);
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
			CPredSequence predList = pAny("rulePreamble") << pLiteral("rule") << pLiteral(":") << pAny("RemainBody");
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{




					HBlock executeBlock = Statement::parser_stmt(p, res.matchs["RemainBody"], nullptr, err); // aqui tem erro					 
					if (executeBlock != nullptr)
					{
						return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, nullptr, executeBlock);
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
						HBlock executeBlock = Statement::parser_stmt_list_later(p,inner); // aqui tem erro					 
						if (executeBlock != nullptr)
						{
							return std::make_shared<CBlockRule>(std::make_shared<CBlockNoumStr>(""), noum_rulebook, ntarget, executeBlock);
						}
					}
				}
			}
		}


		//Com bloco inner 
		{
			CPredSequence predList = pAny("rulePreamble") << pLiteral("rule") << pLiteral(":");
			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{
				HBlockNoum noum_rulebook = ParseAssertion::parse_noum(p, res.matchs["rulePreamble"]);
				if (noum_rulebook != nullptr)
				{
					HBlock executeBlock = Statement::parser_stmt_list_later(p,   inner ); // aqui tem erro					 
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





HBlock NSParser::DynamicDispatch::rule_spec(CParser *p, HTerm  term)
{
	{
		CPredSequence  predList = pAny("rulebookName") << mk_HPredLiteral_OR("_rule", { "rulebook", "rules" });
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock mrulebook = Expression::parser_noumList(p, res.matchs["rulebookName"]);
			if (mrulebook != nullptr)
			{
				return  std::make_shared<CBlockList>(std::list<HBlock>{ mrulebook, std::make_shared<CBlockNoumStr>("rulebook") });
			}
			HBlockNoum  n1 = NSParser::ParseAssertion::parse_noum(p, res.matchs["rulebookName"]);
			if (n1 != nullptr)
			{
				return  std::make_shared<CBlockList>(std::list<HBlock>{ n1, std::make_shared<CBlockNoumStr>("rulebook") });
			}

		}
	}

	{
		CPredSequence  predList = pAny("ruleName") << pLiteral("rule");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock mrule = Expression::parser_noumList(p, res.matchs["ruleName"]);
			if (mrule != nullptr)
			{
				return  std::make_shared<CBlockList>(std::list<HBlock>{ mrule, std::make_shared<CBlockNoumStr>("rule") });
			}
			HBlockNoum  n1 = NSParser::ParseAssertion::parse_noum(p, res.matchs["ruleName"]);
			if (n1 != nullptr)
			{
				return  std::make_shared<CBlockList>(std::list<HBlock>{ n1, std::make_shared<CBlockNoumStr>("rule") });
			}

		}
	}

	return nullptr;
}


HBlock NSParser::DynamicDispatch::Follow_rule(CParser *p, std::vector<HTerm>&  term)
{

	{
		CPredSequence  predList = pLiteral("follow") << pAny("ruleSpec") << pLiteral("for") << pAny("argument"); //com argumento 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock mruleSpecifier = rule_spec(p, res.matchs["ruleSpec"]);
			if (mruleSpecifier != nullptr)
			{
				HBlock margument = Expression::parser_expression(p, res.matchs["argument"]);
				return  std::make_shared<CBlockRuleCall>(mruleSpecifier, margument);
			}
		}
	}


	{
		CPredSequence  predList = pLiteral("follow") << pAny("ruleSpec"); //sem argumento
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock mruleSpecifier = rule_spec(p, res.matchs["ruleSpec"]);
			if (mruleSpecifier != nullptr)
			{
				return  std::make_shared<CBlockRuleCall>(mruleSpecifier, nullptr);
			}
		}
	}







	return nullptr;

}



