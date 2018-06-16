// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Parser\Parser.hpp"
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

 



#include  "verb_en.hpp"
using namespace CBlocking;

std::list<HBlockVerbConjugation> NSParser::ParseGrammar::get_verb_conjugations(  std::string verb)  
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
		static CPredSequence predList = pLiteral("register")<<pLiteral("verb")<<pLiteral("to")<<pAny("verbNamed");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			{
				auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vbase = std::make_shared<CBlockVerb>(vrepr, get_verb_conjugations(  vrepr));
				return vbase;
			}
		}
	}


	{
		  CPredSequence predList =  pLiteral("register")<<pLiteral("verb")	<<pAny("verbNamed");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{			
			{
				auto vrepr = CtoString(expandBract(res.matchs["verbNamed"]));
				auto vbase = std::make_shared<CBlockVerb>(vrepr, get_verb_conjugations( vrepr));
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
		CPredSequence predList = pLiteral("the") <<pAny("remainder");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto t = res.matchs["remainder"];
			return expression_adapt_viewPoint(p,t);
		}
	}

	{
		static CPredSequence predList =  pLiteral("first") << pLiteral("person") << pLiteral("plural")  ;		
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "1P";
	}

	{
		static CPredSequence predList =  pLiteral("first") << pLiteral("person") << pLiteral("singular") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "1S";
	}

	{
		static CPredSequence predList =  pLiteral("second") << pLiteral("person") << pLiteral("plural") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "2P";
	}

	{
		static CPredSequence predList = pLiteral("second") <<pLiteral("person") << pLiteral("singular") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "2S";
	}

	{
		static CPredSequence predList =  pLiteral("third") << pLiteral("person")<<pLiteral("plural") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "3P";
	}

	{
		static CPredSequence predList =  pLiteral("third")<<pLiteral("person") <<pLiteral("singular") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "3S";
	}

	return "";
}

string NSParser::ParseGrammar::expression_adapt_tense(CParser * p, HTerm& term)
{
	

	{
		  CPredSequence predList =  pLiteral("the") <<pAny("remainder");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto t = res.matchs["remainder"];
			return expression_adapt_tense(p, t);
		}
	}

	{
		  CPredSequence predList = pLiteral("past") <<pLiteral("tense");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return   "VBD";
		 
	}

	{
		  CPredSequence predList =  pLiteral("present")	<<pLiteral("participle");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return   ("VBG");

	}
	{
		  CPredSequence predList = pLiteral("gerund");
		 
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VBG");

	}

	{
		  CPredSequence predList = pLiteral("present");

	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VBP");

	}

	{ 
		  CPredSequence predList =  pLiteral("past")	<<pLiteral("participle");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return   ("VBN");
	}
	{
		static CPredSequence predList =  pLiteral("infinitive"); 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  return    ("VB");

	}
	 
 
	return  CtoString(expandBract(term )); ; //default

}

 string parser_verb_noum(HTerm& term)
{
	// remove det
	  CPredSequence predList = pLiteral("the")<<pAny("verbNamed");		 
	 
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) return CtoString(expandBract(res.matchs["verbNamed"]));
	
	return CtoString(expandBract( term));

}


 HBlockVerbAdapt NSParser::ParseGrammar::expression_adapt_verb_inner(CParser * p, HTerm& term)
{
	{
		CPredSequence predList =  pAny("verbNamed")<<pLiteral("in")<<pAny("TenseForm")<<pLiteral("from")	<<pAny("ViewPoint");
		 
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
		CPredSequence predList = pAny("verbNamed") << pLiteral("in") << pAny("TenseForm");

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
		  CPredSequence predList = pAny("verbNamed")<<pLiteral("from")	<<pAny("ViewPoint");
		 
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
		  CPredSequence predList = pAny("verbNamed");			 
		 
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
		static CPredSequence predList = pLiteral("adapt")	<<pAny("remainder");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 
				return expression_adapt_verb_inner(p,res.matchs["remainder"]);				
		}
	}

	{
		  CPredSequence predList = pLiteral("negate") << pAny("remainder");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto v = expression_adapt_verb_inner(p, res.matchs["remainder"]);
			if (v!=nullptr)
			return   std::make_shared<CBlockVerbNegate>(v); 
		}
	}


	return nullptr;

}
