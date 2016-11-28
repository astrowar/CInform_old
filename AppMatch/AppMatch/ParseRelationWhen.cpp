#include "Parser.hpp"

 
#include "CBlockRelation.hpp"
#include "CBlockBoolean.hpp"
using namespace CBlocking;

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

HBlock   CParser::parser_SeletorRelation( HTerm   term , HBlockMatch muteVariable  )
{

	//relation 
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("K2"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral("by"));
			predList.push_back(mkHPredAny("RelationName"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			string rname = res.matchs["RelationName"]->removeArticle()->repr();
			{

				{
					auto arg2 = parser_MatchArgument(res.matchs["K2"]);
					if (arg2 != nullptr)
					{
						return  std::make_shared<CBlockRelationLookup>(rname, arg2, muteVariable, SecondNoum);
					}
				}
			}
		}
	}


	
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
	 
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
			predList.push_back(mk_HPredLiteral("by"));
			predList.push_back(mkHPredAny("RelationName"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			string rname = res.matchs["RelationName"]->removeArticle()->repr();
			{
		 
				{
					auto arg2 = parser_MatchArgument(res.matchs["K2"]);
					if (arg2 != nullptr)
					{
						return  std::make_shared<CBlockRelationLookup>(rname, muteVariable, arg2, FirstNoum);
					}
				}
			}
		}
	}


	return nullptr;


}

HBlock   CParser::parser_SeletorTerm(HTerm   term, HBlockMatch muteVariable)
{
	
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("S1"));
			predList.push_back(mk_HPredLiteral("and"));
			predList.push_back(mkHPredAny("S2"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto arg1 = parser_SeletorTerm(res.matchs["S1"],muteVariable);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_SeletorTerm(res.matchs["Seletor"], muteVariable);
				if (arg2 != nullptr)
				{

					  return  std::make_shared<CBlockBooleanAND>(arg1, arg2);
				}
			}
		}
	}




	auto rrel = parser_SeletorRelation(term, muteVariable);
	if (rrel != nullptr) return rrel;
	auto rverb = parser_SeletorVerb(term, muteVariable);
	if (rverb != nullptr) return rverb;

	return nullptr;
}
 


HBlock   CParser::DynamicLookup_Seletor(std::vector<HTerm>& term)
{
	/*{
		 static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_What_Which());
			predList.push_back(mkHPredAny("K2"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral("by"));
			predList.push_back(mkHPredAny("RelationName"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			 
			string rname = res.matchs["RelationName"]->removeArticle()->repr();
			{
				auto arg1 = parser_MatchArgument(res.matchs["K1"]);
				if (arg1 != nullptr)
				{
					auto arg2 = parser_MatchArgument(res.matchs["K2"]);
					if (arg2 != nullptr)
					{
						return  std::make_shared<CBlockRelationLookup>(rname, arg2, arg1 , SecondNoum);
					}
				}
			}
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_What_Which());			
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
			predList.push_back(mk_HPredLiteral("by"));
			predList.push_back(mkHPredAny("RelationName"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			string rname = res.matchs["RelationName"]->removeArticle()->repr();
			{
				auto arg1 = parser_MatchArgument(res.matchs["K1"]);
				if (arg1 != nullptr)
				{
					auto arg2 = parser_MatchArgument(res.matchs["K2"]);
					if (arg2 != nullptr)
					{
						return  std::make_shared<CBlockRelationLookup>(rname, arg1, arg2, FirstNoum);
					}
				}
			}
		}
	}*/
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("list"));
			predList.push_back(mk_HPredLiteral("of"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_What_Which());
			predList.push_back(mkHPredAny("Seletor"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto arg1 = parser_MatchArgument(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto seletor = parser_SeletorTerm(res.matchs["Seletor"] , arg1);
				if (seletor != nullptr)
				{
					//CBlockListComputed( )
					logError("not implemented");
					return nullptr;
				}
			}
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_What_Which());
			predList.push_back(mkHPredAny("Seletor"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto arg1 = parser_MatchArgument(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto seletor = parser_SeletorTerm(res.matchs["Seletor"],arg1);
				if (seletor != nullptr)
				{
					
					return std::make_shared<CBlockSelector_Where>(seletor );
				}
			}
		}
	}
	return nullptr;
}


 
HBlock   CParser::parser_SeletorVerb(HTerm   term, HBlockMatch muteVariable)
{

	// TODO implementar os NOT 
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{ 
			predList.push_back(verb_IS());
			predList.push_back(verbList);
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 
			auto n2 = parser_expression_match(res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//Sem o IS
			predList.push_back(verbList);
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto n2 = parser_expression_match(res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	} 
	return nullptr;
}
 

 