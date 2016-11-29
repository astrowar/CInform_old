#include "Parser.hpp"
using namespace NSTerm;
using namespace NSTerm::NSMatch;


 



#include  "verb_en.hpp"
using namespace CBlocking;

std::list<HBlockVerbConjugation> NSParser::ParseGrammar::get_verb_conjugations(CParser * p, std::string verb)  
{
	static const VERBTABLE verb_eng = verb_table(); 
	int  n = verb_eng.numEntries;

	std::list<HBlockVerbConjugation> vlist;
	for(int i = 0;i < n;++i)
	{
		if (verb_eng.verbs[i].verb == verb)
		{
			auto &ventry = verb_eng.verbs[i];
			int nk = ventry.tenses.size();
			for (auto &ve : ventry.tenses)
			{
				auto vj = std::make_shared<CBlockVerbConjugation>(  std::string( ve.world ), std::string(ve.tense));
				vlist.push_back(vj);
				 
			} 
			break;
		}
	}

	return  vlist;

}

//register verb funciona como um load especifico de um conjunto de verbos
HBlock NSParser::ParseGrammar::STMT_register_verb(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo* err)
{ 
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("register"));
			predList.push_back(mk_HPredLiteral("verb"));
			predList.push_back(mk_HPredLiteral("to"));
			predList.push_back(mkHPredAny("verbNamed"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{
				auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vbase = std::make_shared<CBlockVerb>(vrepr, get_verb_conjugations(p, vrepr));
				return vbase;
			}
		}
	}


	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("register"));
			predList.push_back(mk_HPredLiteral("verb"));
			predList.push_back(mkHPredAny("verbNamed"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{			
			{
				auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vbase = std::make_shared<CBlockVerb>(vrepr, get_verb_conjugations(p,vrepr));
				return vbase;
			}
		}
	}


	return nullptr;
}


 //adapt the verb

/*
"[adapt V]"
"[adapt V in T]"
"[adapt V from VP]"
"[adapt V in T from VP]"
"[negate V]"
"[negate V in T]"
"[negate V from VP]"
"[negate V in T from VP]"
*/

 
 
string NSParser::ParseGrammar::expression_adapt_viewPoint(CParser * p, HTerm& term)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("the"));
			predList.push_back(mkHPredAny("remainder"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto t = res.matchs["remainder"];
			return expression_adapt_viewPoint(p,t);
		}
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("first"),mk_HPredLiteral("person"),mk_HPredLiteral("plural")  };		
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "1P";
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("first"),mk_HPredLiteral("person"),mk_HPredLiteral("singular") };
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "1S";
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("second"),mk_HPredLiteral("person"),mk_HPredLiteral("plural") };
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "2P";
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("second"),mk_HPredLiteral("person"),mk_HPredLiteral("singular") };
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "2S";
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("third"),mk_HPredLiteral("person"),mk_HPredLiteral("plural") };
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "3P";
	}

	{
		static std::vector<HPred> predList = { mk_HPredLiteral("third"),mk_HPredLiteral("person"),mk_HPredLiteral("singular") };
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "3S";
	}

	return "";
}

string NSParser::ParseGrammar::expression_adapt_tense(CParser * p, HTerm& term)
{
	

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("the"));
			predList.push_back(mkHPredAny("remainder"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto t = res.matchs["remainder"];
			return expression_adapt_tense(p, t);
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("past"));
			predList.push_back(mk_HPredLiteral("tense"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "VBD";
		 
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("present"));
			predList.push_back(mk_HPredLiteral("participle"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return   ("VBG");

	}
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("gerund"));
		 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VBG");

	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("present"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VBP");

	}

	{ 
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("past"));
			predList.push_back(mk_HPredLiteral("participle"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return   ("VBN");
	}
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("infinitive"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VB");

	}
	 
 
	return  CtoString(expandBract(term )); ; //default

}

 string parser_verb_noum(HTerm& term)
{
	// remove det
	static std::vector<HPred> predList = {};
	if (predList.empty())
	{
		predList.push_back(mk_HPredLiteral("the"));
		predList.push_back(mkHPredAny("verbNamed"));		 
	}
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) return CtoString(expandBract(res.matchs["verbNamed"]));
	
	return CtoString(expandBract( term));

}


HBlock NSParser::ParseGrammar::expression_adapt_verb_inner(CParser * p, HTerm& term)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//predList.push_back(mk_HPredLiteral("adapt"));
			predList.push_back(mkHPredAny("verbNamed"));
			predList.push_back(mk_HPredLiteral("in"));
			predList.push_back(mkHPredAny("TenseForm"));
			predList.push_back(mk_HPredLiteral("from"));
			predList.push_back(mkHPredAny("ViewPoint"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{
				
				//auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vrepr = parser_verb_noum(res.matchs["verbNamed"]);
				auto vtense =  expression_adapt_tense(p, res.matchs["TenseForm"]);
				auto vp = expression_adapt_viewPoint(p, res.matchs["ViewPoint"]);
				if (vp == "") return nullptr;

				auto vbase = std::make_shared<CBlockVerbAdapt>(vrepr, vtense , vp);
				return vbase;
			}
		}
	}


	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//predList.push_back(mk_HPredLiteral("adapt"));
			predList.push_back(mkHPredAny("verbNamed"));
			predList.push_back(mk_HPredLiteral("in"));
			predList.push_back(mkHPredAny("TenseForm"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{

				//auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vrepr = parser_verb_noum(res.matchs["verbNamed"]);
				auto vtense = expression_adapt_tense(p, res.matchs["TenseForm"]);
				if (vtense == "") return nullptr;
				auto vbase = std::make_shared<CBlockVerbAdapt>(vrepr, vtense, "default");
				return vbase;
			}
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//predList.push_back(mk_HPredLiteral("adapt"));
			predList.push_back(mkHPredAny("verbNamed"));
			predList.push_back(mk_HPredLiteral("from"));
			predList.push_back(mkHPredAny("ViewPoint"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{
				//auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vrepr = parser_verb_noum(res.matchs["verbNamed"]);
				auto vp = expression_adapt_viewPoint(p, res.matchs["ViewPoint"]);
				if (vp == "") return nullptr;
				auto vbase = std::make_shared<CBlockVerbAdapt>(vrepr, "VBP", vp);
				return vbase;
			}
		}
	}


	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			//predList.push_back(mk_HPredLiteral("adapt"));
			predList.push_back(mkHPredAny("verbNamed"));			 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{
				auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				//auto vrepr = parser_verb_noum( term );				
				auto vbase = std::make_shared<CBlockVerbAdapt>(vrepr, "VBP", "default");
				return vbase;
			}
		}
	}


	return nullptr;
}
 

HBlock NSParser::ParseGrammar::expression_adapt_verb(CParser * p, std::vector<HTerm>& term)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("adapt"));
			predList.push_back(mkHPredAny("remainder"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			 
				return expression_adapt_verb_inner(p,res.matchs["remainder"]);				
		 
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("negate"));
			predList.push_back(mkHPredAny("remainder"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			return expression_adapt_verb_inner(p,res.matchs["remainder"]);

		}
	}


	return nullptr;

}
