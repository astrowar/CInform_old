
#include "CBlockInterpreterRuntime.hpp"
#include "CResultMatch.hpp"
#include <memory>

#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
using namespace std; 

//http://www.ef.com/english-resources/english-grammar/verbs/

//The present perfect of any verb is composed of two elements : the appropriate form of the auxiliary verb to have (present tense), plus the past participle of the main verb. 
//The Past Perfect tense in English is composed of two parts: the past tense of the verb to have (had) + the past participle of the main verb.
//The passive voice in English is composed of two elements: the appropriate form of the verb 'to be' + past participle

//The present perfect of any verb is composed of two elements : the appropriate form of the auxiliary verb to have(present tense), plus the past participle of the main verb

string CBlockInterpreter::adapt_verb_inner(string verb, string tense, string person, HRunLocalScope localsEntry)
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
		logError(  verb + " not registed");

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
HBlockNoum CBlockInterpreter::adapt_verb(HBlockVerbAdapt nVerbAdp, HRunLocalScope localsEntry )
{
	if (nVerbAdp->tense == "past")
	{
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBD", nVerbAdp->viewPoint, localsEntry);
		if (nn != "None") return   std::make_shared<CBlockNoum>(nn);
	}

	if (nVerbAdp->tense == "gerund" || nVerbAdp->tense == "present participle" )
	{
		auto nn = adapt_verb_inner(nVerbAdp->verb, "VBG", nVerbAdp->viewPoint, localsEntry);
		if (nn != "None") return   std::make_shared<CBlockNoum>(nn);
	}

	if ( nVerbAdp->tense == "present perfect")
	{
		string n1 = adapt_verb_inner("have", "VBP", nVerbAdp->viewPoint, localsEntry);
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoum>(n1 + " " + n2);
	}

	if (nVerbAdp->tense == "past perfect")
	{
		string n1 = adapt_verb_inner("have", "VBD", nVerbAdp->viewPoint, localsEntry);
		//string n1 = "had";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoum>( n1+" "+n2);
	}

	if (nVerbAdp->tense == "future")
	{
		//string n1 = adapt_verb_inner("will", "VBD", nVerbAdp->viewPoint, localsEntry);
		string n1 = "will";
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VB", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoum>(n1 + " " + n2);
	}


	auto nn =  adapt_verb_inner(nVerbAdp->verb, nVerbAdp->tense, nVerbAdp->viewPoint, localsEntry);
	if(nn !="None") return   std::make_shared<CBlockNoum>(nn);


	 
	return nullptr;
}
 