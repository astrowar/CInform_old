// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com



#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;


 

HBlockMatchActionCall NSParser::ParseAction::parser_actionMatch(CParser * p, HTerm & term)
{
	
	{
		std::vector<HPred> predList_b = {};
		if (predList_b.empty())
		{

			predList_b.push_back(mkHPredWord("Action"));
			predList_b.push_back(mkHPredAny("noum1"));
			predList_b.push_back(mkHPredPreposition("pred"));
			predList_b.push_back(mkHPredAny("noum2"));
		}

		MatchResult res = CMatch(term, predList_b);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr();
			HBlockMatch m_action = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(anamed)); 

			auto nn1 = ExpressionMatch::parser_expression_match(p, res.matchs["noum1"]);
			auto nn2 = ExpressionMatch::parser_expression_match(p, res.matchs["noum2"]);

			HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nn1, nn2); //An Action !!!
		
			return actionCall;
		}
	}

	 
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
			HBlockMatch m_action = ExpressionMatch::parser_expression_match(p,res.matchs["ActionMatch"]);			 
			HBlockMatch m_arg1 = ExpressionMatch::parser_expression_match(p,res.matchs["Argument1"]);
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
			HBlockMatch m_action = ExpressionMatch::parser_expression_match(p,res.matchs["ActionMatch"]);
			HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nullptr, nullptr);
			return actionCall;
		}
	}



	return nullptr;
}

 
HBlock  NSParser::ParseAction::STMT_phrase_Invoken(CParser * p, std::vector<HTerm>& term)
{
	auto h = NSParser::DynamicDispatch::parser_PhraseInvoke(p, term);
	return h;
}


HBlock NSParser::ParseAction::STMT_Action_Controls(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
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
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
				HBlockMatchActionCall   amatch = parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
				HBlockMatchActionCall   amatch = parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlockComandList executeBlock = Statement::parser_stmt_inner(p,inner, err);
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
