
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


string CBlockInterpreter::adapt_verb_inner(string verb, string tense, string person, HRunLocalScope localsEntry)
{
	auto vb_n = resolve_string_noum (verb, localsEntry, std::list<std::string>());
	if (HBlockVerb nnVerb = asHBlockVerb(vb_n))
	{
		for (auto &cc : nnVerb->conjugations)
		{
			if (cc->tense == tense) return  cc->word;
		}
	}
	return "None";
}
HBlockNoum CBlockInterpreter::adapt_verb(HBlockVerbAdapt nVerbAdp, HRunLocalScope localsEntry )
{

	if (nVerbAdp->tense == "past perfect")
	{
		string n1 = adapt_verb_inner("have", "VBD", nVerbAdp->viewPoint, localsEntry);
		string n2 = adapt_verb_inner(nVerbAdp->verb, "VBN", nVerbAdp->viewPoint, localsEntry);
		return std::make_shared<CBlockNoum>( n1+n2);
	}

	auto nn =  adapt_verb_inner(nVerbAdp->verb, nVerbAdp->tense, nVerbAdp->viewPoint, localsEntry);
	if(nn !="None") return   std::make_shared<CBlockNoum>(nn);


	 
	return nullptr;
}
 