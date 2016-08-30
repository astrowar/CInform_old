#include "GrammarParser.h"

void GrammarParserEn::LoadVerbs()
{

 
	static const verbalConj verbs[] = {
		{ "abandon","abandon",VB },
		{ "abandon","abandon",VBP },
		{ "abandoned","abandon",VBD },
		{ "abandoned","abandon",VBN },
		{ "abandoning","abandon",VBG },
		{ "abandons","abandon",VBZ } };
 
	int N = sizeof(verbs) / sizeof(noumConj);
	for (int i = 0; i< N; ++i)
	{
		verb_map[std::string(verbs[i].verb)] = verbs[i];
	}
		 
}
void GrammarParserEn::LoadNoums()
{

 
	static const noumConj noms[] = {
		 
		{ "aardvark","aardvark",NN },
		{ "aardvarks","aardvark",NNS },
		{ "abacavir","abacavir",NN },
		{ "abaci","abacus",NNS },
		{ "abacus","abacus",NN },
		{ "abacuses","abacus",NNS },
		{ "abalone","abalone",NN },
		{ "abalones","abalone",NNS } };
 

	 
	 int N = sizeof(noms) / sizeof(noumConj);
	 for( int i = 0; i< N ; ++i)
	 {
		 noum_map[ std::string(noms[i].noum)] = noms[i];
	 }

}

