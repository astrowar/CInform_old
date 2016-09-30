#include "Parser.h"
 
 
#include "CBlockRelation.h"

string  parser_OtherCalledAs(HTerm term)
{
	std::vector<HPred> predList; 
	predList.push_back(mk_HPredLiteral("called"));
	predList.push_back(mkHPredAny("var_named"));
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		string argumentName = (res.matchs["var_named"]->removeArticle()->repr());
		return argumentName;
	}
	return "";
}
HBlockArgumentInput CParser::parser_KindCalled(HTerm term)
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
			HBlockArgumentInput argumentEntry  = std::make_shared<CBlockArgumentInput>(argumentKind ,argumentName );			 
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

HBlock CParser::STMT_relates_Assertion(std::vector<HTerm> term)
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
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
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
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
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
			predList.push_back(mk_HPredLiteral("various"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mk_HPredLiteral("various"));
			predList.push_back(mkHPredAny("K2"));
		}
		

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
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
			predList.push_back(mk_HPredLiteral("various"));
			predList.push_back(mkHPredAny("K1"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("K2"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
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
			predList.push_back(mk_HPredLiteral("various"));
			predList.push_back(mkHPredAny("K2"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//string rname = res.matchs["relationName"]->removeArticle()->repr();
			string rname = CtoString(res.matchs["relationName"]->removeArticle());
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
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
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,false,false);
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
			auto arg1 = parser_KindCalled(res.matchs["K1"]);
			if (arg1 != nullptr)
			{
				auto arg2 = parser_KindCalled(res.matchs["K2"]);
				if (arg2 != nullptr)
				{
					if (arg2->kind->named == "other")  arg2->kind = arg1->kind;
					return  std::make_shared<CBlockASimetricRelation>(rname, arg1, arg2,false,false);
				}
			}

		}
	}
	 




	return nullptr;
}
