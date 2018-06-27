#pragma once


typedef struct PLURALTABLE
{
	int n;
	const char** base;
	const char** plurals;
	const int* plurals_idx; // plural id to singular id
	const int* base_idx; // singular id to plural id
    constexpr  PLURALTABLE(int _n, const  char** _base, const  char** _plurals, const  int* _plurals_idx, const  int* _base_idx) :
            n(_n),
            base(_base),
            plurals(_plurals),
            plurals_idx(_plurals_idx),
            base_idx(_base_idx)
    {

    }

} PLURALTABLE;


 PLURALTABLE plura_table(); // obtem a tabela de plurals


#include <string>

//return nullptr if notfound
std::string plural_of(const std::string singular_noum, PLURALTABLE *ptable );
std::string singular_of(const std::string plural_noum, PLURALTABLE *ptable );