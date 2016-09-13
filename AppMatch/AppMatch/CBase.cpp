#include "CBase.h"
#include "EqualsResult.h"

CString::CString(std::string _s) : s(_s) {
}

std::string CString::repr() {
    return this->s;
}

EqualsResul equals(CString *c1, CString *c2) {
    if (c1 == nullptr || c2 == nullptr) return Undefined;
    if (c1->s == c2->s) return Equals;
    return NotEquals;
}

EqualsResul equals(CNumber *c1, CNumber *c2) {
    if (c1 == nullptr || c2 == nullptr) return Undefined;
    if (c1->val == c2->val) return Equals;
    return NotEquals;
}

EqualsResul equals(CList *c1, CList *c2) {
    if (c1 == nullptr || c2 == nullptr) return Undefined;
    if (c1->lst.size() != c2->lst.size()) return NotEquals;
    if (c1->lst.empty()) return Equals;
    auto it1 = c1->lst.begin();
    auto it2 = c2->lst.begin();
    while (it1 != c1->lst.end()) {
        EqualsResul q = equals((*it1).get(), (*it2).get());
        if (q != Equals) return NotEquals;
        ++it1;
        ++it2;
    }
    return Equals;
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

EqualsResul equals(CTerm *c1, CTerm *c2) {
    EqualsResul q ;
   /* q = equals(dynamic_cast<CString *>(c1), dynamic_cast<CString *>(c2));
    if (q != Undefined) return q;
    q = equals(dynamic_cast<CNumber *>(c1), dynamic_cast<CNumber *>(c2));
    if (q != Undefined) return q;
    q = equals(asCList(c1), asCList(c2));
    if (q != Undefined) return q;*/

	q = equals(asCString(c1), asCString(c2));
	if (q != Undefined) return q;
	q = equals(asCNumber(c1), asCNumber(c2));
	if (q != Undefined) return q;
	q = equals(asCList(c1), asCList(c2));
	if (q != Undefined) return q;

    return Undefined;
}

EqualsResul equals(HTerm c1, HTerm c2) {
    return equals(c1.get(), c2.get());
}

HTerm make_number(int x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CNumber>(x));
}

HTerm make_list(std::initializer_list<HTerm> x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CList>(x));
}

CList* asCList(CTerm* c)
{
	if (c->type() == TermList) return static_cast<CList*>(c);
	return nullptr;
}

CNumber* asCNumber(CTerm* c)
{
	if (c->type() == TermNumber) return static_cast<CNumber*>(c);
	return nullptr;
}

CString* asCString(CTerm* c)
{
	if (c->type() == TermString) return static_cast<CString*>(c);
	return nullptr;
}

HTerm make_string(std::string x) {
    return std::static_pointer_cast<CTerm>(std::make_shared<CString>(x));
}



