#pragma once
#include "Parser.hpp"
 

#define ISLOG false


std::vector<HTerm> decompose(string phase);;

string decompose_bracket(string phase, string dlm);

CList *mk_CList_Literal(std::vector<HTerm> strList);
HBlockNoum noum(std::string n) ;


void testeParser_listA();
void testeParser_listB();

void testeParser_actionA();
void testeParser_actionB();
void testeParser_actionC();


void testeParser_1();
void testeParser_2();
void testeParser_2a();
void testeParser_3();
void testeParser_4();
void testeParser_5();
void testeParser_5b();
void testeParser_5c();
void testeParser_5d();
void testeParser_5e();
void testeParser_5f();
void testeParser_5g();
void testeParser_5_all();

void testeParser_6();


//Blocks
void testeParser_10();
void testeParser_11();
void testeParser_12();


void testeParser_7a();
void testeParser_7b();
void testeParser_7c();
void testeParser_7d();

void testeParser_7e();
void testeParser_7f();
void testeParser_7g();

void testeParser_21();

void testeRelation1();
void testeRelation2();
void testeRelation3();
void testeRelation4();
void testeRelation5();
void testeRelation6();
void testeRelation7();
void testeRelation_all();

void testeExecute1();
void testeExecute2();
void testeExecute3();
void testeExecute4();
void testeExecute_all();

void testeSerialize1();

void testeSelector_all();

void testeVerb_all();