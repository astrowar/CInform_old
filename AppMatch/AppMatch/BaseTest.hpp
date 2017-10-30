#pragma once
#include "Parser.hpp"
#include "CBlockInterpreterRuntime.hpp"

#define ISLOG false


std::vector<NSTerm::HTerm> decompose(string phase);;

string decompose_bracket(string phase, string dlm);

NSTerm::CList *mk_CList_Literal(std::vector<NSTerm::HTerm> strList);
CBlocking::HBlockNoum noum(std::string n) ;


void testeParser_listA();
void testeParser_listB();

void testeParser_actionA();
void testeParser_actionB();
void testeParser_actionC();
void testAction_all();

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
void testValues_all();
void testeParser_listAll();
void testedecide_all();
void testeLogical_All();

void testeComposition_all();