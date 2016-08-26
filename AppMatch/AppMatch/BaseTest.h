#pragma once
#include "Parser.h"
#include <iostream>

#define ISLOG true


std::vector<HTerm> decompose(string phase);;

string decompose_bracket(string phase, string dlm);

CList *mk_CList_Literal(std::vector<HTerm> strList);


void testeParser_listA();
void testeParser_listB();


void testeParser_1();
void testeParser_2();
void testeParser_2a();
void testeParser_3();
void testeParser_4();
void testeParser_5();
void testeParser_6();
void testeParser_7a();
void testeParser_7b();
void testeParser_7c();
void testeParser_7d();
void testeParser_21();