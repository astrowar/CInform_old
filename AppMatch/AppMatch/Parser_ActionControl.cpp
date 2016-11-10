

#include "Parser.hpp"


 

HBlockMatch CParser::parser_actionMatch(HTerm & term)
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

			//HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(nullptr, nullptr, nullptr);
			//return actionCall;
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
				HBlockMatch   amatch = CParser::parser_actionMatch(res.matchs["ActionMatch"]);
				 
			}

		}
	}


	return nullptr;



}
