// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// PVS
// PVQ

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

