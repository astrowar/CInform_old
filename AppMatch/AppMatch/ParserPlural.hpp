#pragma once


typedef struct PLURALTABLE
{
	int n;
	char** base;
	char** plurals;
	int* plurals_idx; // plural id to singular id 
	int* base_idx; // singular id to plural id 

}PLURALTABLE;


PLURALTABLE plura_table(); // obtem a tabela de plurals

//return nullptr if notfound
char* plural_of(char* singular_noum, PLURALTABLE *ptable );
char* singular_of(char* plural_noum, PLURALTABLE *ptable );