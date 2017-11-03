// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"
 
 
#include "CBlockRelation.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



string  parser_OtherCalledAs(HTerm term)
{
	std::vector<HPred> predList; 
	predList.push_back( mk_HPredLiteral("called"));
	predList.push_back(mkHPredAny("var_named"));
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		string argumentName = (res.matchs["var_named"]->removeArticle()->repr());
		return argumentName;
	}
	return "";
}
 
HBlock NSParser::ParseRelation::STMT_relates_Assertion(CParser *p, std::vector<HTerm>&  term)
{

	// Simetricos em grupo
	//  R relates K to each other in groups


	// Simetricos
	// R relates K to each other

	// Assimetricos in grupo
	// R relates various K to various E
	// R relates various K to one E
	// R relates one K to various E

	// Assimetricos
	// R relates one K to another

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{


			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral("each"));
			predList.push_back(mk_HPredLiteral("other"));
			predList.push_back(mk_HPredLiteral("in"));
			predList.push_back(mk_HPredLiteral("groups"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p,res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = std::make_shared<CBlockArgumentInput>(arg1->kind, "");
				return  std::make_shared<CBlockSimetricRelation>(rname, arg1, arg2, true, true);
			}
		}
	}


{
	static std::vector<HPred> predList;
	if (predList.empty())
	{
		predList.push_back(mkHPredAny("relationName"));
		predList.push_back(mk_HPredLiteral("relates"));
		predList.push_back(mkHPredAny("K1"));
		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mk_HPredLiteral("each"));
		predList.push_back(mk_HPredLiteral_OR("other", { "other", "another" }));
	}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = std::make_shared<CBlockArgumentInput>(arg1->kind, "");
				if (arg2 != nullptr)
				{
					return  std::make_shared<CBlockSimetricRelation>(rname, arg1, arg2,false,false);
				}
			}
		}
	}

 

	//___________________________________________________________________________________ 


	{  
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral_OR("various",{"various","many"}));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral_OR("various", { "various","many" }));
			predList.push_back(mkHPredAny("K2"));
		}
		

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			{
				auto arg2 = parser_KindCalled(p, res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
						if (kind_n->named == "other" || kind_n->named == "another" )  arg2->kind = arg1->kind;
					}
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2, true,true);
				}
			}

		}

	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mk_HPredLiteral_OR("various", { "various","many" }));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			{
				auto arg2 = parser_KindCalled(p, res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
						if (kind_n->named == "other" || kind_n->named == "another" )  arg2->kind = arg1->kind;
					 
					}
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,true,false);
				}
			}

		} 
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral_OR("various", { "various","many" }));
			predList.push_back(mkHPredAny("K2"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(p, res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
						if (kind_n->named == "other" || kind_n->named == "another")  arg2->kind = arg1->kind;
					 
					}
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,false,true);
				}
			}
		} 
	}
	//___________________________________________________________________________________ 

	
	//___________________________________________________________________________________ 

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
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(p, res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
					if (kind_n->named == "other" || kind_n->named == "another")  arg2->kind = arg1->kind;
					 
					}

					auto condition = ControlFlux::parser_if_condition(p, res.matchs["Condition"]);

					auto relation =   std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,false,false);

					logError(" Coditional relations is deprecated, use dynamic verbs");
					return nullptr;
					return std::make_shared<CBlockConditionalRelation>(relation, condition);
				}
			}
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("relationName"));
			predList.push_back(mk_HPredLiteral("relates"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(p, res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				HBlockArgumentInput arg2 = parser_KindCalled(p, res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
						if (kind_n->named == "other" || kind_n->named == "another")  arg2->kind = arg1->kind;
					}

				 
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,false,false);
				}
			}

		}
	}
	 




	return nullptr;
}
