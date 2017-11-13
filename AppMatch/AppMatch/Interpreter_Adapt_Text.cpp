

#include "CResultMatch.hpp"
#include <memory>

#include "CBlockScope.hpp"
#include "QueryStack.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"
using namespace std;
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;



#include  "verb_en.hpp" 
#include "ParserPlural.hpp"



std::list<HBlockVerbConjugation> CBlockInterpreter::get_verb_conjugations(std::string verb) const
{
	static const VERBTABLE verb_eng = verb_table();
	int  n = verb_eng.numEntries;

	std::list<HBlockVerbConjugation> vlist;
	for (int i = 0; i < n; ++i)
	{
		if (verb_eng.verbs[i].verb == verb)
		{
			auto &ventry = verb_eng.verbs[i];
			int nk = ventry.tenses.size();
			for (auto &ve : ventry.tenses)
			{
				auto vj = std::make_shared<CBlockVerbConjugation>(std::string(ve.world), std::string(ve.tense));
				vlist.push_back(vj);

			}
			break;
		}
	}
	return  vlist;
}


string complex_viewPoint( string person, string number, string gender )
{
	string s = "";
	if (person == "first") s = s + "1";
	else if (person == "second ") s = s + "2";
	else  s = s + "3"; //default 

	if (number == "plural") s = s + "P";
	else  s = s + "S"; //singular
	 
	return s;

}

HBlockNoum CBlockInterpreter:: get_verbal_regarding(string verb, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	if (verb == "are" || verb == "is")
	{
		verb = "be";
	}


	auto vc = get_verb_conjugations(verb);
	if (vc.empty()) return nullptr;


	auto r = localsEntry->resolve("viewPoint");
	if (auto nr = asHBlockNoum(r))
	{
		string viewPoint = nr->named;
		string conjugadet = "None";
		 
		 
		conjugadet = adapt_verb_inner(verb, "VBP", viewPoint, localsEntry);
		 
		 
		if (conjugadet != "None")
		{
			return   std::make_shared<CBlockNoum>(conjugadet);
		}

	}

	return std::make_shared<CBlockNoum >("[Missing ViewPoint]");

}

HBlockNoumSupl CBlockInterpreter::resolve_number_gender(string  n, HRunLocalScope localsEntry, QueryStack *stk)
{
	static PLURALTABLE plural_tab = plura_table();
	auto pSingle = singular_of(n , &plural_tab);
	if (pSingle.empty() == false)
	{
		return std::make_shared<CBlockNoumSupl>(n , "plural", "neutral");
	}
	auto pPlural = plural_of(n , &plural_tab);
	if (pPlural.empty() == false)
	{
		return std::make_shared<CBlockNoumSupl>(n , "singular", "neutral");
	}

	return std::make_shared<CBlockNoumSupl>(n , "", ""); //undefined 
}


HBlockNoumSupl CBlockInterpreter::textual_representation(HBlock  x, string person,   string number, string gender, HRunLocalScope localsEntry, QueryStack *stk)
{
	static PLURALTABLE plural_tab = plura_table();
	
	const  std::map<string, CBlocking::HBlock> nextVarSet = { { "viewPoint" , std::make_shared<CBlockNoum >(complex_viewPoint(person, number, gender))  },{ "tense" , std::make_shared<CBlockNoum >("present tense") } };
	

	auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, nextVarSet);

	auto y = exec_eval(x, localsNext, stk);



	// o verbo que vem a seguir concorda com o noum atual
	if (auto n = asHBlockNoumSupl(y)) return n ;
	if (auto n = asHBlockNamedValue(y)) return resolve_number_gender(n->named  , localsNext, stk);
	if (auto n = asHBlockInstanceNamed(y)) return resolve_number_gender(n->named , localsNext, stk);
	
    if (auto n = asHBlockNoum(y))
		{
		 
		auto vreg = get_verbal_regarding(n->named, localsNext, stk);
		if (vreg != nullptr) return std::make_shared<CBlockNoumSupl>(vreg->named, number, gender);

		return resolve_number_gender(n->named , localsNext, stk);
			 
		} 
 
	 
	// eh um verbo ?
	if (y == nullptr)
	{
		if (auto n = asHBlockNoum(x))
		{
			auto vreg = get_verbal_regarding(n->named, localsNext, stk);
			if (vreg != nullptr) return std::make_shared<CBlockNoumSupl>(vreg->named, number, gender);

			//return resolve_number_gender(n->named, localsNext, stk);
		}

	}

	return std::make_shared<CBlockNoumSupl>( "###", "singular", "neutral");
}


HBlockText CBlockInterpreter::adapt_text(HBlockTextSentence texts, HRunLocalScope localsEntry, QueryStack *stk)
{
	std::string s = "";

	std::string number = "singular";
	std::string gender = "neutral";
	std::string person = "3S";


	for(auto t : texts->contents)
	{
		if (HBlockText tx = asHBlockText(t)) s = s + tx->contents;
		else
		{
			auto nx = textual_representation(t,person, number , gender,  localsEntry, stk);
			//nx->dump("+ ");
			s = s + " " +  nx->named;
			if (nx->gender != "") gender = nx->gender;
			if (nx->number != "") number = nx->number;
		}
	}

	 
	return std::make_shared<CBlockText>(s);
}
 