// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "parser/Parser.hpp"

 
#include "CBlockRelation.hpp"
#include "CBlockBoolean.hpp"
#include "CBlockComposition.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;




HBlockArgumentInput NSParser::ParseRelation::parser_KindCalled(CParser *p, HTerm term)
{

	{
		//Various never has name called
		CPredSequence predList = undefinedArticle() << pAny("KindCalled");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return parser_KindCalled(p, res.matchs["KindCalled"]);
		}
	}


	{
		//Various never has name called
		CPredSequence predList = pLiteral("various")<<pAny("kind");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());

			auto kindStr = Expression::parser_noum_expression(p, res.matchs["kind"]);

			HBlockKindNamed argumentKindItem = std::make_shared<CBlockKindNamed >(kindStr);
			HBlockKind argumentKind = std::make_shared<CBlockCompositionList>(argumentKindItem);
			HBlockArgumentInput argumentEntry = std::make_shared<CBlockArgumentInput>(argumentKind, "");
			return argumentEntry;
		}
	}


	{
		CPredSequence predList  = pAny("kind") <<pLiteral("called") <<pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());
			auto kindStr = Expression::parser_noum_expression(p, res.matchs["kind"]);

			HBlockKind argumentKind = std::make_shared<CBlockKindNamed>(kindStr);
			string argumentName = (res.matchs["var_named"]->removeArticle()->repr());
			HBlockArgumentInput argumentEntry = std::make_shared<CBlockArgumentInput>(argumentKind, argumentName);
			return argumentEntry;
		}
	}

	{
		CPredSequence predList = pAny("kind");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//auto kindStr = CtoString(expandBract(res.matchs["kind"])->removeArticle());
			auto kindStr = Expression::parser_noum_expression(p, res.matchs["kind"]);
			auto rp = kindStr;
			HBlockKind argumentKind = std::make_shared<CBlockKindNamed>(rp);
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
		  CPredSequence predList = pAny("relationName")	<<pLiteral("relates")	<<pAny("K1")	<<pLiteral("to")	<<pAny("K2")	<<pLiteral("when")	<<pAny("Condition");
		

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
					if (auto kind_n = DynamicCasting::asHBlockKindNamed(arg2->kind))
					{
						if (kind_n->named->named() == "other")  arg2->kind = arg1->kind;
					}
					return  std::make_shared<CBlockSimetricRelation>(rname, arg1, arg2,false,false);
				}
			}

		}
	}
	return nullptr;

}


string  NSParser::ParseRelation::parser_RelationNameID(NSParser::CParser* c_parser, HTerm term)
{

	  CPredSequence predList =  pAny("RelationName") <<pLiteral("relation");		
	

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		return res.matchs["RelationName"]->removeArticle()->repr();
	}

	return term->removeArticle()->repr();
}

HBlock   NSParser::ParseRelation::parser_SeletorRelation(CParser *p, HTerm   term , HBlockMatch muteVariable  )
{
	return nullptr;
	//relation 
	{
		  CPredSequence predList =  pAny("K2")	<<pLiteral("relates")	<<pLiteral("to")	<<pLiteral("by") <<pAny("RelationName");
		 

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			string rname = parser_RelationNameID(p, res.matchs["RelationName"]);

			//string rname = res.matchs["RelationName"]->removeArticle()->repr();
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
		  CPredSequence predList = pLiteral("relates")	<<pLiteral("to")	<<pAny("K2")	<<pLiteral("by") <<pAny("RelationName");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			//string rname = res.matchs["RelationName"]->removeArticle()->repr();
			string rname = parser_RelationNameID(p, res.matchs["RelationName"]);
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

HBlock    NSParser::ParseRelation::parser_SeletorTerm(CParser *p, HTerm   term, HBlockMatch muteVariable)
{

	{
		  CPredSequence predList = pAny("S1")	<<pLiteral("and")	<<pAny("S2");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto arg1 = parser_SeletorTerm(p, res.matchs["S1"], muteVariable);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_SeletorTerm(p, res.matchs["S2"], muteVariable);
				if (arg2 != nullptr)
				{
					//std::list<HBlockMatch> alist;
					//alist.push_back(arg1);
					//alist.push_back(arg2);
					return  std::make_shared<CBlockSelectorAND>( arg1,arg2);
				}
			}
		}
	}




	auto rrel = parser_SeletorRelation(p, term, muteVariable);
	if (rrel != nullptr)
	{
		return rrel;
	}
	auto rverb = parser_SeletorVerb(p,term, muteVariable);
	if (rverb != nullptr)
	{
		return rverb;
	}

	return nullptr;
}
 


HBlock   NSParser::ParseRelation::DynamicLookup_Seletor(CParser *p, std::vector<HTerm>& term)
{
	/*{
		 static CPredSequence predList = {};
		if (predList.empty())
		{ <<pAny("K1");
			<<mk_What_Which(); <<pAny("K2"); <<pLiteral("relates"); <<pLiteral("to"); <<pLiteral("by"); <<pAny("RelationName");
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
		static CPredSequence predList = {};
		if (predList.empty())
		{ <<pAny("K1");
			<<mk_What_Which(); <<pLiteral("relates"); <<pLiteral("to"); <<pAny("K2"); <<pLiteral("by"); <<pAny("RelationName");
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
		  CPredSequence predList =  pLiteral("list")	<<pLiteral("of")	<<pAny("K1")	<<mk_What_Which()	<<pAny("Seletor");
 
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
		 CPredSequence predList = pAny("K1") <<mk_What_Which()	<<pLiteral("not")	<<pAny("Seletor");

		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto arg1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["K1"]);
			if (arg1 != nullptr)
			{

				auto seletor = parser_SeletorTerm(p, res.matchs["Seletor"], arg1);
				if (seletor != nullptr)
				{

					return std::make_shared<CBlockSelector_Where>(seletor);
				}
			}
		}
	}





	{
		 CPredSequence predList =  pAny("K1")	<<mk_What_Which()	<<pAny("Seletor");

		
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
		  CPredSequence predList = verb_IS()<<pLiteral("not")	<<pAny("K2");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto n2 = ExpressionMatch::parser_expression_match(p, res.matchs["K2"]);
			HBlockMatch n_not = std::make_shared<CBlockMatchNOT>(n2);
			return std::make_shared<CBlockVerbLookup>("is", muteVariable, n_not , FirstNoum);
			 
		}
	}


	{
		  CPredSequence predList =  verb_IS() <<p->verbList	<<pAny("K2");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 
			auto n2 = ExpressionMatch::parser_expression_match(p,res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	}

	{
	   CPredSequence predList = p->verbList	<<pAny("K2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto n2 = ExpressionMatch::parser_expression_match(p,res.matchs["K2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
			return std::make_shared<CBlockVerbLookup>(vrepr, muteVariable, n2, FirstNoum);
		}
	} 


	{
		  CPredSequence predList = verb_IS()	<<pAny("K2");
		
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto n2 = ExpressionMatch::parser_expression_match(p, res.matchs["K2"]);			
			return std::make_shared<CBlockVerbLookup>("is", muteVariable, n2, FirstNoum);
		}
	}


	return nullptr;
}
 

 