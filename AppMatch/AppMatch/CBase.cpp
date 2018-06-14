// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "CBase.hpp"
#include "EqualsResult.hpp"
#include <algorithm>

using namespace NSTerm;

 CString::CString(std::string _s) : s(_s) {
}

std::string  CString::repr() {
    return this->s;
}

EqualResulting::EqualsResul  equals_cstring( CString *c1, CString *c2) {
    if (c1 == nullptr || c2 == nullptr) return EqualResulting::Undefined;
    if (c1->s == c2->s) return EqualResulting::Equals;
	if ((c1->s.size() == c2->s.size()) && (tolower(c1->s[0]) == tolower(c2->s[0])))
	{
		int n = c1->s.size();
		for (int j = 0; j< n; ++j)
		{
			if (tolower(c1->s[j]) != tolower(c2->s[j])) return EqualResulting::NotEquals;
		}
		return EqualResulting::Equals;
	}

    return EqualResulting::NotEquals;
}

EqualResulting::EqualsResul  equals_cnumber(CNumber *c1, CNumber *c2) {
    if (c1 == nullptr || c2 == nullptr) return EqualResulting::Undefined;
    if (c1->val == c2->val) return EqualResulting::Equals;
    return EqualResulting::NotEquals;
}

EqualResulting::EqualsResul equals_clist(CList *c1, CList *c2) {
    if (c1 == nullptr || c2 == nullptr) return EqualResulting::Undefined;
    if (c1->lst.size() != c2->lst.size()) return EqualResulting::NotEquals;
    if (c1->lst.empty()) return EqualResulting::Equals;
    auto it1 = c1->lst.begin();
    auto it2 = c2->lst.begin();
    while (it1 != c1->lst.end()) {
	    EqualResulting::EqualsResul q = NSTerm::equals((*it1).get(), (*it2).get());
        if (q != EqualResulting::Equals) return EqualResulting::NotEquals;
        ++it1;
        ++it2;
    }
    return EqualResulting::Equals;
}

CNumber::CNumber(int _val) : val(_val) {
}

std::string CNumber::repr() {
    return std::to_string(this->val);
}

CList::CList() {
}

CList::CList(std::initializer_list<HTerm> ll) : lst(ll) {
}

void CList::push_back(HTerm x) {
    this->lst.push_back(x);
}

void CList::push_front(HTerm x) {
    this->lst.push_front(x);
}

std::vector<HTerm> CList::asVector() {
    return std::vector<HTerm>(this->lst.begin(), this->lst.end());
}

std::string CList::repr() {
    std::string q = "[";
    for (auto it = this->lst.begin(); it != this->lst.end(); ++it) {
        q += " " + it->get()->repr();
    }
    q += " ]";
    return q;
}

CTerm *CList::removeArticle() {
    if (this->lst.size() > 0) {
        if ((this->lst.front()->repr() == "a") || (this->lst.front()->repr() == "the") ||
            (this->lst.front()->repr() == "an")) {

            if (this->lst.size() == 2) {
                //restou apenas o outro termo
                auto it = this->lst.begin();
                ++it; // pula o artigo
                return it->get()->removeArticle();
            }

            CList *r = new CList();
            r->lst = this->lst;
            r->lst.pop_front();
            return r;
        }
    }
    return this;
}

EqualResulting::EqualsResul NSTerm::equals(CTerm *c1, CTerm *c2) {
	EqualResulting::EqualsResul q ;
   /* q = equals(dynamic_cast<CString *>(c1), dynamic_cast<CString *>(c2));
    if (q != Undefined) return q;
    q = equals(dynamic_cast<CNumber *>(c1), dynamic_cast<CNumber *>(c2));
    if (q != Undefined) return q;
    q = equals(asCList(c1), asCList(c2));
    if (q != Undefined) return q;*/

    q = equals_cstring(NSTerm::asCString(c1), NSTerm::asCString(c2));
    if (q != EqualResulting::Undefined) return q;
    q = equals_cnumber(NSTerm::asCNumber(c1), NSTerm::asCNumber(c2));
    if (q != EqualResulting::Undefined) return q;
    q = equals_clist(NSTerm::asCList(c1), NSTerm::asCList(c2));
    if (q != EqualResulting::Undefined) return q;

    return EqualResulting::Undefined;
}

EqualResulting::EqualsResul NSTerm::equals(HTerm c1, HTerm c2) {
    return NSTerm::equals(c1.get(), c2.get());
}

HTerm NSTerm::make_number(int x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CNumber>(x));
}

HTerm NSTerm::make_list(std::initializer_list<HTerm> x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CList>(x));
}

CList* NSTerm::asCList(CTerm* c)
{
    if (c->type() == TermList) return static_cast<CList*>(c);
    return nullptr;
}

CNumber* NSTerm::asCNumber(CTerm* c)
{
    if (c->type() == TermNumber) return static_cast<CNumber*>(c);
    return nullptr;
}

CString* NSTerm::asCString(CTerm* c)
{
    if (c->type() == TermString) return static_cast<CString*>(c);
    return nullptr;
}

HTerm NSTerm::make_string(std::string x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CString>(x));
}



