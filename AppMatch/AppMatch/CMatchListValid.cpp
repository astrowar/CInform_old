// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CMatchListValid.hpp"

using namespace NSTerm;
using namespace NSTerm::NSMatch;

bool NSMatch::isListValid_bounds(MTermSet Comb)
{
    if (Comb.size() > 1) {
        // if ((*it).front()->repr() == ")") return false;
        //if ((*it).back()->repr() == "(") return false;

        if (Comb.front()->is_closeBracket()) return false;
        if ((Comb).back()->is_openBracket()) return false;
    } else if (Comb.size() == 1) {
        // if ((*it).front()->repr() == "(") return false;
        // if ((*it).front()->repr() == ")") return false;

        if ((Comb).front()->is_openBracket()) return false;
        if ((Comb).front()->is_closeBracket()) return false;
    }

    return true;
}

bool NSMatch::isListValid_bounds_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
{
	auto isize = vend - vbegin;
	if (isize > 1) {
		// if ((*it).front()->repr() == ")") return false;
		//if ((*it).back()->repr() == "(") return false;

		if ((*vbegin)->is_closeBracket()) return false;
		auto last = vend - 1;
		if ((*last)->is_openBracket()) return false;
	}
	else if (isize == 1) {
		// if ((*it).front()->repr() == "(") return false;
		// if ((*it).front()->repr() == ")") return false;

		if ((*vbegin)->is_openBracket()) return false;
		if ((*vbegin)->is_closeBracket()) return false;
	}

	return true;
}

 

bool NSMatch::isListValid_count(const MTermSet & Comb)
{
    //para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim

    {
        int cc_open = 0;
        int cc_close = 0;
        int ns = (Comb.size());
        for (int j = 0; j < ns; ++j) {
            // if ((*it).at(j)->repr() == ")") cc_open++;
            // if ((*it).at(j)->repr() == "(") cc_close++;

            if ((Comb).at(j)->is_closeBracket()) cc_open++;
            if ((Comb).at(j)->is_openBracket()) cc_close++;
        }
        if (cc_open != cc_close) return false;
    }
    return true;
}


bool NSMatch::isListValid_count_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
{
	//para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim

	{
		int cc_open = 0;
		int cc_close = 0;
		auto isize = vend - vbegin;
		int ns = (isize);
		for (int j = 0; j < ns; ++j) {
			// if ((*it).at(j)->repr() == ")") cc_open++;
			// if ((*it).at(j)->repr() == "(") cc_close++;

			auto comb_j = vbegin + j;
			if ((*comb_j)->is_closeBracket()) cc_open++;
			if ((*comb_j)->is_openBracket()) cc_close++;
		}
		if (cc_open != cc_close) return false;
	}
	return true;
}

bool NSMatch::isListValid_bounds(MTermSetCombinatoria &listComb)
{
    //para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim
    for (auto it = listComb.begin(); it != listComb.end(); ++it) {

        if (it->size() > 1) {
            // if ((*it).front()->repr() == ")") return false;
            //if ((*it).back()->repr() == "(") return false;

            if ((*it).front()->is_closeBracket()) return false;
            if ((*it).back()->is_openBracket()) return false;
        } else if (it->size() == 1) {
            // if ((*it).front()->repr() == "(") return false;
            // if ((*it).front()->repr() == ")") return false;

            if ((*it).front()->is_openBracket()) return false;
            if ((*it).front()->is_closeBracket()) return false;
        }
    }
    return true;
}
 

bool NSMatch::isListValid_count(MTermSetCombinatoria &listComb)
{
    //para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim
    for (auto it = listComb.begin(); it != listComb.end(); ++it) {
        int cc_open = 0;
        int cc_close = 0;
        int ns = (it->size());
        for (int j = 0; j < ns; ++j) {
            // if ((*it).at(j)->repr() == ")") cc_open++;
            // if ((*it).at(j)->repr() == "(") cc_close++;

            if ((*it).at(j)->is_closeBracket()) cc_open++;
            if ((*it).at(j)->is_openBracket()) cc_close++;
        }
        if (cc_open != cc_close) return false;
    }
    return true;
}

bool NSTerm::NSMatch::isListValid(MTermSetCombinatoria &listComb)
{

    if (!isListValid_bounds(listComb)) return false;
    return isListValid_count(listComb);
}

bool NSMatch::isListValid(MTermSet &Comb)
{
    if (!isListValid_bounds(Comb)) return false;
    return isListValid_count(Comb);
}

bool  NSMatch::isListValid_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend )
{
	if (!isListValid_bounds_range(vbegin,vend)) return false;
	return isListValid_count_range(vbegin, vend);
}


