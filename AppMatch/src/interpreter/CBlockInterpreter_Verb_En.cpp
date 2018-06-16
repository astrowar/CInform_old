// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "CResultMatch.hpp"

#include "CBlockScope.hpp"
#include "interpreter/QueryStack.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"
#include <memory>

using namespace std; 
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;

//http://www.ef.com/english-resources/english-grammar/verbs/

//The present perfect of any verb is composed of two elements : the appropriate form of the auxiliary verb to have (present tense), plus the past participle of the main verb. 
//The Past Perfect tense in English is composed of two parts: the past tense of the verb to have (had) + the past participle of the main verb.
//The passive voice in English is composed of two elements: the appropriate form of the verb 'to be' + past participle

//The present perfect of any verb is composed of two elements : the appropriate form of the auxiliary verb to have(present tense), plus the past participle of the main verb

string CBlockInterpreter::adapt_verb_inner_inner( const  string &  verb ,   string   tense, string person, HRunLocalScope localsEntry)
{
	auto vb_n = resolve_string_noum (  verb, localsEntry, std::list<std::string>());

 

	if (vb_n == nullptr)
	{
		 
		for (auto &v : verbs)
		{
			if (v->named == verb)
			{
				logMessage(" verb " + verb);
				vb_n =  v;
			}
		} 
		auto _conjugations = get_verb_conjugations(verb);
		if (_conjugations.empty())
		{
			logError(verb + " not registed");
		}
		vb_n = std::make_shared<CBlockVerb>(verb, _conjugations);

	}

	if (person == "default")
	{ 
		logError(" view Point Undefined");
		return "!!!!"; 
	}

	if (tense == "VBP")//non-3rd person singular present
	{
		if (person == "3S") tense = "VBZ";	 //Verb, 3rd person singular present
	}

	else if (tense == "VBZ")//Verb, 3rd person singular present
	{
		if (person != "3S") tense = "VBP";	 //non-3rd person singular present
	}

	if (HBlockVerb nnVerb = asHBlockVerb(vb_n))
	{ 
		if (person == "1S" || person == "2S" || person == "3S")
		{
			for (auto &cc : nnVerb->conjugations)
			{
				if (cc->tense == tense)
				{
					return  cc->word;
				}
			}
		}
		else 
		{
			for (  auto it = nnVerb->conjugations.rbegin(); it != nnVerb->conjugations.rend(); ++ it)
			{
				if ((*it)->tense == tense)
				{
					return  (*it)->word;
				}
			}
		}

		logError("unable to find " + verb + " " + tense);
	 
	}
	 

	logError("unable to adapt " + verb + " " + tense);
	return "None";
}


string CBlockInterpreter::adapt_verb_inner(const  string &  verb, string   tense, string person, HRunLocalScope localsEntry)
{
	if (person == "default")
	{
		auto nn = localsEntry->resolve("viewPoint");
		if (auto nviewPoint = asHBlockNoum(nn))
		{
			person = nviewPoint->named; 
		} 
	}

	auto x = adapt_verb_inner_inner(verb, tense, person, localsEntry);
	printf("%s in %s  %s=%s\n", verb.c_str(), person.c_str(), tense.c_str(), x.c_str());
	return x;
}
 

HBlockNoum CBlockInterpreter::adapt_verb(HBlockVerbAdapt nVerbAdp,   HRunLocalScope localsEntry )
{
	if (nVerbAdp->tense == "past")
	{
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBD", nVerbAdp->viewPoint, localsEntry);
		if (nn != "None") return   std::make_shared<CBlockNoumStr>(nn);
	}

	if (nVerbAdp->tense == "gerund" || nVerbAdp->tense == "present participle" )
	{
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBG", nVerbAdp->viewPoint, localsEntry);
		if (nn != "None") return   std::make_shared<CBlockNoumStr>(nn);
	}

	if ( nVerbAdp->tense == "present perfect")
	{
		string n1 = adapt_verb_inner("have", "VBP", nVerbAdp->viewPoint, localsEntry);
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>(n1 + " " + n2);
	}

	if (nVerbAdp->tense == "past perfect")
	{
		string n1 = adapt_verb_inner("have", "VBD", nVerbAdp->viewPoint, localsEntry);
		//string n1 = "had";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>( n1+" "+n2);
	}

	if (nVerbAdp->tense == "future")
	{
		//string n1 = adapt_verb_inner("will", "VBD", nVerbAdp->viewPoint, localsEntry);
		string n1 = "will";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VB", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>(n1 + " " + n2);
	}


	auto nn =  adapt_verb_inner(nVerbAdp->verb, nVerbAdp->tense, nVerbAdp->viewPoint, localsEntry);
	if(nn !="None") return   std::make_shared<CBlockNoumStr>(nn); 
	 
	return nullptr;
}
 
HBlockNoum CBlockInterpreter::adapt_negate_verb(HBlockVerbNegate negVerbAdp, HRunLocalScope localsEntry)
{
	HBlockVerbAdapt nVerbAdp = negVerbAdp->verbAdapt;

	if (nVerbAdp->tense == "past" || nVerbAdp->tense == "VBD")
	{
		auto n1 = adapt_verb_inner("be", "VBD", nVerbAdp->viewPoint, localsEntry);
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBD", nVerbAdp->viewPoint, localsEntry);
		if (nn != "None") return std::make_shared<CBlockNoumStr>(n1 + " not " + nn);
	}

	if (nVerbAdp->tense == "gerund" || nVerbAdp->tense == "present participle" || nVerbAdp->tense == "VBG")
	{
		auto n1 = adapt_verb_inner("be", "VBG", nVerbAdp->viewPoint, localsEntry);
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBG", nVerbAdp->viewPoint, localsEntry);
		//if (nn != "None") return   std::make_shared<CBlockNoumStr>(n1 + " " + nn);
		if (nn != "None") return   std::make_shared<CBlockNoumStr>("not " + nn);
	}

	if (nVerbAdp->tense == "present perfect" || nVerbAdp->tense == "VBP")
	{
		string n1 = adapt_verb_inner("have", "VBP", nVerbAdp->viewPoint, localsEntry);
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>( n1 +" not "+ n2);
	}

	if (nVerbAdp->tense == "past perfect" || nVerbAdp->tense == "VBD")
	{
		string n1 = adapt_verb_inner("have", "VBD", nVerbAdp->viewPoint, localsEntry);
		//string n1 = "had";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>(n1 + " not " + n2);
	}

	if (nVerbAdp->tense == "future"|| nVerbAdp->tense == "future tense" || nVerbAdp->tense == "VB")
	{
		//string n1 = adapt_verb_inner("will", "VBD", nVerbAdp->viewPoint, localsEntry);
		string n1 = "will";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VB", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoumStr>(n1 + " not " + n2);
	}


	//auto nn = adapt_verb_inner(nVerbAdp->verb, nVerbAdp->tense, nVerbAdp->viewPoint, localsEntry);
	//if (nn != "None") return   std::make_shared<CBlockNoumStr>(nn);

	nVerbAdp->dump("?");
	return nullptr;



	 
}