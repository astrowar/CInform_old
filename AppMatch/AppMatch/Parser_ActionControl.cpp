

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
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageBefore, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("after"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageAfter, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("check"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageCheck, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("report"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageReport, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}

		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("instead"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageInstead, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			static std::vector<HPred> predList = {};
			if (predList.empty())
			{
				predList.push_back(mk_HPredLiteral("carry"));
				predList.push_back(mk_HPredLiteral("out"));
				predList.push_back(mkHPredAny("ActionMatch"));
				predList.push_back(mk_HPredLiteral(":"));
			}
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = parser_stmt_inner(inner, err);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageCarryOut, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}
	}


	return nullptr;



}
