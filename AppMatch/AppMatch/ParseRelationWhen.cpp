// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"

 
#include "CBlockRelation.hpp"
#include "CBlockBoolean.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;





HBlockArgumentInput NSParser::ParseRelation::parser_KindCalled(CParser *p, HTerm term)
{

	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("various")); //Various never has name called
		predList.push_back(mkHPredAny("kind"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());
			HBlockKind argumentKindItem = std::make_shared<CBlockKindValue>(kindStr);
			HBlockKind argumentKind = std::make_shared<CBlockListOfKind>(argumentKindItem);
			HBlockArgumentInput argumentEntry = std::make_shared<CBlockArgumentInput>(argumentKind, "");
			return argumentEntry;
		}
	}


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("var_named"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());
			HBlockKind argumentKind = std::make_shared<CBlockKindValue>(kindStr);
			string argumentName = (res.matchs["var_named"]->removeArticle()->repr());
			HBlockArgumentInput argumentEntry = std::make_shared<CBlockArgumentInput>(argumentKind, argumentName);
			return argumentEntry;
		}
	}

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());
			auto rp = kindStr;
			HBlockKind argumentKind = std::make_shared<CBlockKindValue>(rp);
			HBlockArgumentInput argumentEntry = std::make_shared<CBlockArgumentInput>(argumentKind, "");
			return argumentEntry;
		}
	}
	return nullptr;
}














HBlock NSParser::ParseRelation::STMT_relates_AssertionWhen(CParser *p, std::vector<HTerm>&  term)
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
			auto arg1 = parser_KindCalled(p,res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(p,res.matchs["K2"]);
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

HBlock   NSParser::ParseRelation::parser_SeletorRelation(CParser *p, HTerm   term , HBlockMatch muteVariable  )
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
					auto arg2 = ExpressionMatch::parser_MatchArgument(p,res.matchs["K2"]);
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
					auto arg2 = ExpressionMatch::parser_MatchArgument(p,res.matchs["K2"]);
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

HBlock   NSParser::ParseRelation::parser_SeletorTerm(CParser *p, HTerm   term, HBlockMatch muteVariable)
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
			auto arg1 = parser_SeletorTerm(p,res.matchs["S1"],muteVariable);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_SeletorTerm(p,res.matchs["Seletor"], muteVariable);
				if (arg2 != nullptr)
				{

					  return  std::make_shared<CBlockBooleanAND>(arg1, arg2);
				}
			}
		}
	}




	auto rrel = parser_SeletorRelation(p,term, muteVariable);
	if (rrel != nullptr) return rrel;
	auto rverb = parser_SeletorVerb(p,term, muteVariable);
	if (rverb != nullptr) return rverb;

	return nullptr;
}
 


HBlock   NSParser::ParseRelation::DynamicLookup_Seletor(CParser *p, std::vector<HTerm>& term)
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
			auto arg1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto seletor = parser_SeletorTerm(p,res.matchs["Seletor"] , arg1);
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
			auto arg1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				 
				auto seletor = parser_SeletorTerm(p,res.matchs["Seletor"],arg1);
				if (seletor != nullptr)
				{
					
					return std::make_shared<CBlockSelector_Where>(seletor );
				}
			}
		}
	}
	return nullptr;
}


 
HBlock   NSParser::ParseRelation::parser_SeletorVerb(CParser *p, HTerm   term, HBlockMatch muteVariable)
{

	// TODO implementar os NOT 
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{ 
			predList.push_back(verb_IS());
			predList.push_back(p->verbList);
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 
			auto n2 = ExpressionMatch::parser_expression_match(p,res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//Sem o IS
			predList.push_back(p->verbList);
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto n2 = ExpressionMatch::parser_expression_match(p,res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	} 
	return nullptr;
}
 

 