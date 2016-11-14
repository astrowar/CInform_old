

#include "Parser.hpp"


 

HBlockMatchActionCall CParser::parser_actionMatch(HTerm & term)
{
	
	 
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			 
			predList.push_back(mkHPredAny("ActionMatch"));
			predList.push_back(mkHPredAny("Argument1"));
		 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 
			HBlockMatch m_action = parser_expression_match(res.matchs["ActionMatch"]);			 
			HBlockMatch m_arg1 = parser_expression_match(res.matchs["Argument1"]);
			HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, m_arg1, nullptr);
			return actionCall;
		}
	}


	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			 
			predList.push_back(mkHPredAny("ActionMatch"));
		 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch m_action = parser_expression_match(res.matchs["ActionMatch"]);
			HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nullptr, nullptr);
			return actionCall;
		}
	}



	return nullptr;
}

HBlock CParser::STMT_Action_Controls(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	if (inner != nullptr)
	{
		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("before"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				HBlockComandList executeBlock = parser_stmt_inner(inner, err);
				HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>( EventHandleStage::StageBefore, amatch, executeBlock);
				return actionCallEv;

			}

		}
	}


	return nullptr;



}
