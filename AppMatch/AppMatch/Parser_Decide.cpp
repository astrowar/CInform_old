#include "Parser.hpp"
using namespace CBlocking;


HBlockMatch NSParser::ParseDecide::parser_What_Which_Assertion(CParser * p, HTerm term)
{
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which());
		predList.push_back(mkHPredAny("kindReturn"));  // which (Person) is (the targert) -> Enforce (Return Value) as Person
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = ExpressionMatch::parser_expression_match(p,res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				return AdjetiveMatch;
				//return std::make_shared<CBlockMatchDirectIs>(c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);

				return nullptr;
			}
		}
	}
	return nullptr;
}

HBlockMatchIs NSParser::ParseDecide::parser_What_Which_Verb_Assertion(CParser * p, HTerm term)
{
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which());
		predList.push_back(mkHPredAny("kindReturn"));  // which (Person) is (the targert) -> Enforce (Return Value) as Person
		predList.push_back(p->verbList);
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));


			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = ExpressionMatch::parser_expression_match(p,res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				//return AdjetiveMatch;
				return std::make_shared<CBlockMatchIsVerb>(vrepr, c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);


				return nullptr;
			}
		}
	}
	return nullptr;
}


HBlockMatchIs NSParser::ParseDecide::parser_Match_IF_Assertion(CParser * p, HTerm term )
{
    


	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("if"));
		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(p->verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchIsVerb >(vrepr, AValue, BValue);
		}
	}

	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("if"));
		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchDirectIs>(AValue, BValue);
		}
	}
    {
        std::vector<HPred> predList;
        predList.push_back(mk_HPredLiteral("if"));
        predList.push_back(mkHPredAny("AValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;
            auto r =  res.matchs["AValue"].get();
			logError(r->repr());
           // return std::make_shared<CBlockMatch>(AValue);

			return nullptr;
        }
    }

    return nullptr;

}



HBlock NSParser::ParseDecide::parseAssertion_isDecide_inLine(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{

   
	if (inner == nullptr)
	{
		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("to"));
				predList.push_back(mk_HPredLiteral("decide"));
				predList.push_back(mkHPredAny("Match"));
				predList.push_back(mk_HPredLiteral(":"));
				predList.push_back(mkHPredAny("RemainBody"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) {
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"] );
				if (a_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


				HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat>(w_match, body);
				}


				 


			}
		}
	}

	if (inner != nullptr)
	{
		//Com bloco inner 
		{

			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("to"));
				predList.push_back(mk_HPredLiteral("decide"));
				predList.push_back(mkHPredAny("Match"));
				predList.push_back(mk_HPredLiteral(":"));

			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) {
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"]);
				if (a_match!=nullptr )
				{
					HBlockComandList body = Statement::parser_stmt_inner(p, inner, err);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match != nullptr)
				{

					HBlockComandList body = Statement::parser_stmt_inner(p, inner, err);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


				HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match != nullptr)
				{

					HBlockComandList body = Statement::parser_stmt_inner(p, inner, err);
					return std::make_shared<CBlockToDecideWhat>(w_match, body);
				}


			}
		}
	}


    return nullptr;
}


HBlock NSParser::ParseDecide::parseAssertion_isDecide (CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{
	return parseAssertion_isDecide_inLine(p, term, inner, err);
}


HBlock NSParser::ParseDecide::parseAssertion_DecideOn(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{
		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("decide"));
				predList.push_back(mk_HPredLiteral("on"));
				predList.push_back(mkHPredAny("ExpressionBody"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
					logMessage((res.matchs["ExpressionBody"]->repr()));
					HBlock body = Expression::parser_expression(p, res.matchs["ExpressionBody"]);
					return std::make_shared<CBlockToDecideOn>( body);
			}
		}
	}
	 
		return nullptr;
	 


}

HBlock NSParser::ParseDecide::STMT_Definition_Assertion(CParser * p, std::vector<HTerm>&  term)
{

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto c1 = mkHPredList("def_A", { mk_HPredLiteral("definition"), mk_HPredLiteral(":") });
			auto c2 = mk_HPredLiteral("definition:");
			predList.push_back(mkHPredBooleanOr("kindpart", c1, c2));
			predList.push_back(mkHPredAny("Match"));
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("LogicalBody"));
		}

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			HBlockMatchIsVerb  v_match = ExpressionMatch::parserMatchIsConditionVerb (p,res.matchs["Match"]);
			if (v_match != nullptr)
			{
				HBlock body = parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(v_match, body);
			}

			HBlockMatchIs a_match = ExpressionMatch::parserMatchIsCondition(p,res.matchs["Match"]);
			if (a_match != nullptr)
			{
				HBlock body = parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}
			return nullptr;
        }
    }
    return nullptr;
}



