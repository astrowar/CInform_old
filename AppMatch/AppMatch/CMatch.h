#pragma once

#ifndef _CMATCH_H
#define _CMATCH_H

#include "CBase.h"
#include <vector>
#include "CMatch.h"


using  MTermSet = std::vector<HTerm>;
using  MTermSetCombinatoria = std::vector<MTermSet>;
using  MTermSetCombinatoriaList = std::vector<MTermSetCombinatoria>;



MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm> lst, int n);
std::string get_repr(MTermSetCombinatoriaList lst);




//predicado do match
//predicado pode ser: 
//      um Atom que deve ser Equal
//      um comparador que deve resultar em EqualsResul quando executado
//      um Any que pode ser qualquer coisa

class CPred: public CAtom
{
public:
	std::string named;
	CPred(std::string _named) :named(_named) {};
	virtual EqualsResul match(HTerm h) = 0;
};
 
using HPred = std::shared_ptr<CPred>;


class CPredAtom : public CPred
{
public:
	HTerm h;
	CPredAtom(std::string _named, HTerm atom);
	virtual EqualsResul match(HTerm _h) override;
};


class CPredAny : public CPred
{
public:
	CPredAny(std::string _named);;
	virtual EqualsResul match(HTerm _h) override;
};

class CPredBoolean : public CPred
{
public:
	explicit CPredBoolean(const std::string& _named);
};

class CPredBooleanAnd : public CPredBoolean
{
	CPredBooleanAnd(const std::string& _named, const HPred& c_pred, const HPred& c_pred1);

public:
	HPred b1,  b2;
	 
};

class CPredBooleanOr : public CPredBoolean
{
	CPredBooleanOr(const std::string& _named, const HPred& c_pred, const HPred& c_pred1);

public:
	HPred b1, b2;
	 
};


#endif