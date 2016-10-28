#include "Parser.hpp"

 
#include "CBlockRelation.hpp"


HBlock CParser::STMT_relates_AssertionWhen(std::vector<HTerm>&  term)
{
	//Contact relates (a thing called X) to (a thing called Y) when X is part of Y or Y is part of X.
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
			predList.push_back(mk_HPredLiteral("when"));
			predList.push_back(mkHPredAny("Condition"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			string rname = res.matchs["relationName"]->removeArticle()->repr();
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
					return  std::make_shared<CBlockSimetricRelation>(rname, arg1, arg2,false,false);
				}
			}

		}
	}
	return nullptr;

}