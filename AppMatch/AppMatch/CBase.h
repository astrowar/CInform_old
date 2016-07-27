#pragma once
#ifndef _CBASE_H
#define _CBASE_H
#include <string>
#include <list>
#include <memory>
#include <vector>
enum EqualsResul;

class CTerm
{
public:
	virtual ~CTerm()
	{
	}

	virtual std::string repr() = 0;
};

using HTerm = std::shared_ptr<CTerm>;

class CAtom :public CTerm
{
};

class CString : public CAtom
{
public :
	std::string s;
	CString(std::string _s);
	virtual std::string repr() override;
};

class CNumber : public CAtom
{
public:
	int val;
	CNumber(int _val);
	virtual std::string repr() override;
};

//typedef TermList = std::list<CTerm*>;
class CList : public CAtom
{
public:
	std::list<HTerm> lst;
	CList();
	CList(std::initializer_list<HTerm>);
	void push_back(HTerm x);
	void push_front(HTerm x);
	std::vector<HTerm> asVector();
	virtual std::string repr() override;
};

EqualsResul equals(CTerm* c1, CTerm* c2);
EqualsResul equals(HTerm c1, HTerm c2);
HTerm make_number(int x);
HTerm make_string(std::string x);
HTerm make_list(std::initializer_list<HTerm> x);
#endif;

