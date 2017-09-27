// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserPlural.hpp"
#include <cstring>
#include <cstdio>
#include <algorithm>
 

int binary_search(char *list_of_words[],  int isize, char *target)
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


char* plural_of(char* singular_noum, PLURALTABLE *ptable)
{
	int k = binary_search(ptable->base,   ptable->n, singular_noum);
	if (k < 0) return nullptr;
	k = ptable->base_idx[k];
	return ptable->plurals[k];


}

char* singular_of(char* plural_noum, PLURALTABLE *ptable)
{
	int k = binary_search(ptable->plurals,  ptable->n, plural_noum);
	if (k < 0) return nullptr;
	k = ptable->plurals_idx[k];
	return ptable->base[k];
}