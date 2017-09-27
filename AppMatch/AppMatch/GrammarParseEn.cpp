// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

