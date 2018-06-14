// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "Parser.hpp"
 
 
#include "CBlockRelation.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


string  parser_OtherCalledAs(HTerm term)
{
	CPredSequence predList  =  pLiteral("called") <<pAny("var_named");
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
		  CPredSequence predList = 		pAny("relationName")	<<pLiteral("relates")	<<pAny("K1")<<pLiteral("to") <<pLiteral("each")	<<pLiteral("other")	<<pLiteral("in")	<<pLiteral("groups");

		 
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
	  CPredSequence predList = pAny("relationName")	<<pLiteral("relates")<<pAny("K1")<<pLiteral("to")	<<pLiteral("each")	<<(mk_HPredLiteral_OR("other", { "other", "another" }));
	 

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
		 CPredSequence predList =  pAny("relationName")	<<pLiteral("relates")	<<mk_HPredLiteral_OR("various",{"various","many"})	<<pAny("K1")	<<pLiteral("to")	<<(mk_HPredLiteral_OR("various", { "various","many" }))  <<pAny("K2");
		
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
		CPredSequence predList =  pAny("relationName")	<<pLiteral("relates")	<<(mk_HPredLiteral_OR("various", { "various","many" }))	  <<pAny("K1")	<<pLiteral("to")	<<pAny("K2");
		 
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
		CPredSequence predList = pAny("relationName")	<<pLiteral("relates")	<<pAny("K1")<<pLiteral("to")<<(mk_HPredLiteral_OR("various", { "various","many" }))	<<pAny("K2");

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
	    CPredSequence predList = pAny("relationName")	<<pLiteral("relates")	<<pAny("K1")	<<pLiteral("to")<<pAny("K2")	<<pLiteral("when")	<<pAny("Condition");
		
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
		 CPredSequence predList =  pAny("relationName")	<<pLiteral("relates")  <<pAny("K1")	<<pLiteral("to")	<<pAny("K2");
		

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
