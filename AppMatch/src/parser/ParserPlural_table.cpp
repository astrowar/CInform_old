// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "Parser\ParserPlural.hpp"
#include <cstring>
#include <cstdio>
#include <algorithm>
 

int binary_search(const char *list_of_words[],  int isize, const  char *target)
{
	int bottom = 0;
	int mid;
	int top = isize - 1;
	auto ws = strlen(target);

	while (bottom <= top)
	{

		if ((top - bottom) < 10)
		{
			mid = -1;
			for (int i = bottom; i <= top; ++i)
			{
				auto ww = list_of_words[i];
				auto r = strcmp(ww, target);
				if (r == 0)
				{ 
					return i;
				} 
			}
			return -1;
		}


		mid = (top + bottom) / 2;


		auto ww = list_of_words[mid];
		auto rpos = strcmp(ww, target);
		if (rpos == 0)
		{
			return mid;
		}

		if (rpos > 0)
		{
			 
			top = std::min(mid+1 , isize -1);
		}
		else
		{
			 
			bottom = std::max(0,mid-1);
		}
	}

 
	 
	return -1;
}


std::string plural_of(const std::string singular_noum, PLURALTABLE *ptable)
{
	int k1 = binary_search(ptable->base,   ptable->n, singular_noum.c_str());
	if (k1 < 0) return "";
	
	int k2 = ptable->base_idx[k1];
 

	return std::string(ptable->plurals[k2]);


}

std::string singular_of(const std::string plural_noum, PLURALTABLE *ptable)
{
	int k = binary_search(ptable->plurals,  ptable->n, plural_noum.c_str());
	if (k < 0) return "";
	k = ptable->plurals_idx[k];
	return std::string(ptable->base[k]);
}