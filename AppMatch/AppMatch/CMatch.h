#pragma once

#ifndef _CMATCH_H
#define _CMATCH_H

#include "CBase.h"
#include <vector>
#include <map>
#include "EqualsResult.h"


using  MTermSet = std::vector<HTerm>;
using  MTermSetCombinatoria = std::vector<MTermSet>;
using  MTermSetCombinatoriaList = std::vector<MTermSetCombinatoria>;



MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm> lst, size_t n);
std::string get_repr(MTermSetCombinatoriaList lst);




//predicado do match
//predicado pode ser: 
//      um Atom que deve ser Equal
//      um comparador que deve resultar em EqualsResul quando executado
//      um Any que pode ser qualquer coisa

class CPred: public CAtom
{
public:
	std::string repr() override;
	 
	std::string named;
	CPred(std::string _named) :named(_named) {};
	virtual EqualsResul match(MTermSet h) = 0;
};
 
using HPred = std::shared_ptr<CPred>;


class CPredAtom : public CPred
{
public:
	HTerm h;
	CPredAtom(std::string _named, HTerm atom);
	virtual EqualsResul match(MTermSet _h) override;
};

class CPredList : public CPred
{
public:
 
	std::vector<HPred> plist;
	CPredList(std::string _named,  std::initializer_list<HPred> plist);
	virtual EqualsResul match(MTermSet _h) override;
};

class CPredAny : public CPred
{
public:
	CPredAny(std::string _named);;
	virtual EqualsResul match(MTermSet _h) override;

};

class CPredBoolean : public CPred
{
public:
	  CPredBoolean(const std::string& _named);
};

class CPredBooleanAnd : public CPredBoolean
{
public:
	EqualsResul match(MTermSet h) override;
 
	CPredBooleanAnd(const std::string& _named, const HPred& c_pred, const HPred& c_pred1);

public:
	HPred b1,  b2;
	 
};

class CPredBooleanOr : public CPredBoolean
{
public:
	CPredBooleanOr(const std::string& _named, const HPred& c_pred, const HPred& c_pred1);
	EqualsResul match(MTermSet h) override;
public:
	HPred b1, b2;
	 
};






class MatchResult
{
public:
	MatchResult(): result(Undefined)
	{
	}

	std::map<std::string, HTerm> matchs;
	EqualsResul result;

	void setValue(std::string named, HTerm value);
	HTerm getValue(std::string named);

	void insert(MatchResult &other);
};


MatchResult makeMatch(std::string named, HTerm value);


MatchResult CMatch(std::vector<HTerm> lst, std::vector<HPred> predicates);

std::string get_repr(MatchResult r);

#endif