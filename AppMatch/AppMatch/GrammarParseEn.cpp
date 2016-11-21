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
 

	 
	 
}

