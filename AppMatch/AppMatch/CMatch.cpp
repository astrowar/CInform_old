#include "CBase.h"
#include <vector>
#include "CMatch.h"
#include <iostream>
#include <memory>
#include <functional>

#define CMLOG false

std::string get_repr(MTermSet lst) {
    std::string q;
    q += " [ ";
    for (auto tr = lst.begin(); tr != lst.end(); ++tr) {
        if (tr != lst.begin()) q += " , ";
        q += tr->get()->repr();
    }
    q += " ] ";
    return q;
}

std::string get_repr(MTermSetCombinatoria lst) {

    std::string q;
    q += " { ";
    for (auto tr = lst.begin(); tr != lst.end(); ++tr) {
        q += get_repr(*tr) + " ";
    }
    q += " } ";
    return q;
}

//Obtem uma lista de M termos e quebra ela em Combinacoes de Sets de tamanho N
MTermSetCombinatoria cons(MTermSet &head, MTermSetCombinatoria &tail) {
    MTermSetCombinatoria accTerms;
    accTerms.push_back(head);
    for (auto k = tail.begin(); k != tail.end(); ++k) {
        accTerms.push_back(*k);
    }
    return accTerms;
}

//cada termo eh um MTermSet
MTermSetCombinatoriaList getCombinatoriasUnitary(std::vector<HTerm> terms) {
    MTermSetCombinatoria uniq;
    for (auto it = terms.begin(); it != terms.end(); ++it) {
        uniq.push_back({MTermSet({*it})});
    }
    return MTermSetCombinatoriaList({uniq});
}

//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
MTermSetCombinatoriaList getCombinatoriasGroup(std::vector<HTerm> terms) {
    return MTermSetCombinatoriaList({MTermSetCombinatoria({terms})});
}


bool isListValid_bounds(MTermSet Comb) {
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

bool isListValid_count(MTermSet Comb) {
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


bool isListValid_bounds(MTermSetCombinatoria &listComb) {
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

bool isListValid_count(MTermSetCombinatoria &listComb) {
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

bool isListValid(MTermSetCombinatoria &listComb) {

    if (isListValid_bounds(listComb) == false) return false;
    if (isListValid_count(listComb) == false) return false;
    return true;
}

bool isListValid(MTermSet &Comb) {
    if (isListValid_bounds(Comb) == false) return false;
    if (isListValid_count(Comb) == false) return false;
    return true;
}

MTermSetCombinatoriaList getCombinatoriasRec(std::vector<HTerm> &terms, size_t n) //num termos que restam
{
    if (n == 1) {
        return getCombinatoriasGroup(terms); // apenas uma combinacao eh possivel
    }
    size_t lsize = terms.size();
    if (n == lsize) {
        return getCombinatoriasUnitary(terms); //Agiliza o processamento
    }
    //particiona de 1 a (n-1)
    MTermSetCombinatoriaList accTerms;
    for (size_t j = 1; j <= lsize - n + 1; ++j) {
        MTermSet head(terms.begin(), terms.begin() + j);
        std::vector<HTerm> tail(terms.begin() + j, terms.end());
        MTermSetCombinatoriaList tails;
        if (n > 2) tails = getCombinatoriasRec(tail, n - 1);
        else if (n == 2) tails = getCombinatoriasGroup(terms);

        for (auto c = tails.begin(); c != tails.end(); ++c) {
            MTermSetCombinatoria fullSet = cons(head, *c);

            if (isListValid(fullSet)) {
                accTerms.emplace_back(fullSet);
            }
        }
    }
    return accTerms;
}

MTermSetCombinatoria getUnicCombination(std::vector<HTerm> &lst) {
    MTermSetCombinatoria comb;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        comb.push_back({*it});
    }
    return comb;
}

MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm> &lst, size_t n) {
    if (lst.size() < n) {
        return MTermSetCombinatoriaList(); // impossivel ..
    }
    if (lst.size() == n) {

        return MTermSetCombinatoriaList({getUnicCombination(lst)}); // apenas uma combinacao eh possivel
    }
    return getCombinatoriasRec(lst, n);
}


//cada termo eh um MTermSet
bool applyCombinatoriasUnitary(MTermSetCombinatoria &partial_in, std::vector<HTerm> &terms, FuncCombinatoria &func) {
    MTermSetCombinatoria uniq(partial_in.begin(), partial_in.end());
    for (auto it = terms.begin(); it != terms.end(); ++it) {
        if (isListValid(uniq) == false) return false;
        uniq.push_back({MTermSet({*it})});
    }
    return func(uniq);

}

//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
bool applyCombinatoriasGroup(MTermSetCombinatoria &partial_in, std::vector<HTerm> &terms, FuncCombinatoria &func) {
    if (isListValid(terms) == false) return false;
    partial_in.push_back(terms);
    bool hasFound = func(partial_in);
    partial_in.pop_back();
    return hasFound;
}

bool applyCombinatoriasRec(MTermSetCombinatoria &partial_in, std::vector<HTerm> &terms, size_t n,
                           FuncCombinatoria &func) //num termos que restam
{

    if (n == 1) {
        return applyCombinatoriasGroup(partial_in, terms, func); // apenas uma combinacao eh possivel

    }
    size_t lsize = terms.size();
    if (n == lsize) {
        return applyCombinatoriasUnitary(partial_in, terms, func); //Agiliza o processamento

    }

    MTermSetCombinatoria partial = partial_in;//copy

    //particiona de 1 a (n-1)
    MTermSetCombinatoriaList accTerms;
    for (size_t j = 1; j <= lsize - n + 1; ++j) {
        MTermSet head(terms.begin(), terms.begin() + j);

        if (isListValid(head)) {
            std::vector<HTerm> tail(terms.begin() + j, terms.end());

            partial.push_back(head);
            bool hasFound = false;
            if (n > 2) hasFound = applyCombinatoriasRec(partial, tail, n - 1, func);
            else if (n == 2) hasFound = applyCombinatoriasGroup(partial, tail, func);
            partial.pop_back();
            if (hasFound) {
                return true;
            }
        }
    }
    return false;

}

void applyCombinatorias(std::vector<HTerm> &lst, size_t n, FuncCombinatoria &func) {

    if (lst.size() < n) {
        return; // impossivel ..
    }

    if (lst.size() == n) {

        MTermSetCombinatoria unip = {getUnicCombination(lst)};
        func(unip); // apenas uma combinacao eh possivel
        return;
    }
    MTermSetCombinatoria partial;
    applyCombinatoriasRec(partial, lst, n, func);
}

//======================================================================


bool
applyCombinatoriasGroupSmart(MTermSetCombinatoria &partial_in, std::vector<HTerm> &terms, std::vector<CPred *> &preds,
                             int pos, FuncCombinatoria &func) {
    if (preds[pos]->match(terms) != NotEquals) {
        if (isListValid(terms) == false) return false;
        partial_in.push_back(terms);
        bool hasFound = func(partial_in);
        partial_in.pop_back();
        return hasFound;
    }
    return false;
}

bool applyCombinatoriasRecSmart(MTermSetCombinatoria &partial_in, std::vector<HTerm> &terms, size_t n,
                                std::vector<CPred *> &preds, int pos, FuncCombinatoria &func) //num termos que restam
{

    if (n == 1) {
        return applyCombinatoriasGroup(partial_in, terms, func); // apenas uma combinacao eh possivel

    }
    size_t lsize = terms.size();
    if (n == lsize) {
        return applyCombinatoriasUnitary(partial_in, terms, func); //Agiliza o processamento

    }

    MTermSetCombinatoria partial = partial_in;//copy

    //particiona de 1 a (n-1)
    MTermSetCombinatoriaList accTerms;
    for (size_t j = 1; j <= lsize - n + 1; ++j) {
        MTermSet head(terms.begin(), terms.begin() + j);
        if (preds[pos]->match(head) != NotEquals) {
            if (isListValid(head)) {
                std::vector<HTerm> tail(terms.begin() + j, terms.end());

                partial.push_back(head);
                bool hasFound = false;
                if (n > 2) hasFound = applyCombinatoriasRecSmart(partial, tail, n - 1, preds, pos + 1, func);
                else if (n == 2) hasFound = applyCombinatoriasGroupSmart(partial, tail, preds, pos + 1, func);
                partial.pop_back();
                if (hasFound) {
                    return true;
                }
            }
        }
    }
    return false;

}


void applyCombinatorias_smart(std::vector<HTerm> &lst, size_t n, std::vector<CPred *> preds, FuncCombinatoria &func) {

    if (lst.size() < n) {
        return; // impossivel ..
    }

    if (lst.size() == n) {

        MTermSetCombinatoria unip = {getUnicCombination(lst)};
        func(unip); // apenas uma combinacao eh possivel
        return;
    }
    MTermSetCombinatoria partial;
    applyCombinatoriasRecSmart(partial, lst, n, preds, 0, func);
}





//=====================================================================




std::string get_repr(MTermSetCombinatoriaList lst) {
    std::string q = "{ ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        for (auto tt = it->begin(); tt != it->end(); ++tt) {
            q += " [ ";
            for (auto tr = tt->begin(); tr != tt->end(); ++tr) {
                if (tr != tt->begin()) {
                    q += "|";
                }
                q += tr->get()->repr();
            }
            q += " ] ";
        }
        q += "\n";
    }
    q += "}";
    return q;
}


//std::string get_repr(MTermSet  lst)
//{
//	std::string q = "";
//		
//		{
//			q += " [ ";
//			for (auto tr = lst.begin(); tr != lst.end(); ++tr)
//			{
//				if (tr != lst.begin())
//				{
//					q += "|";
//				}
//				q += tr->get()->repr();
//			}
//			q += " ] ";
//		}
//		 
//	return q;
//}



std::string CPred::repr() {
    return "Pred";
}

bool CPredAtom::isSame(HTerm b) {
    if (CPredAtom *hlist = dynamic_cast<CPredAtom *>(b.get())) {
        return (equals(this->h.get(), hlist->h.get()) == Equals);
    }
    return false;
}

std::string CPredAtom::repr() {
    return "Pred(" + this->h->repr() + ")";
}

CPredAtom::CPredAtom(std::string _named, HTerm atom) : CPred(_named), h(atom) {
}

EqualsResul CPredAtom::match(MTermSet &_h) {
    if (_h.size() == 3) {
        // if ((_h[0]->repr() == "(") &&  (_h[2]->repr() == ")"))
        if ((_h[0]->is_openBracket()) && (_h[2]->is_closeBracket())) {
            return equals(this->h.get(), _h[1].get());
        }
    }

    if (_h.size() == 1) {
        return equals(this->h.get(), _h[0].get());
    }
    return NotEquals;
}

EqualsResul CPredAtom::match(HTerm h) {

    return equals(this->h.get(), h.get());
}

bool CPredList::isSame(HTerm h) {
    if (CPredList *hlist = dynamic_cast<CPredList *>(h.get())) {
        if (this->plist.size() != hlist->plist.size()) return false;
        for (int i = 0; i < this->plist.size(); ++i) {
            if (this->plist[i]->isSame(hlist->plist[i]) == false) {
                return false;
            }
        }
        return true;

    }
    return false;
}

std::string CPredList::repr() {
    std::string s = "";
    size_t n = plist.size();
    for (size_t j = 0; j < n; ++j) {
        if (j != 0) s += " ";
        s += plist[j]->repr();
    }
    return "PredList(" + s + ")";
}

CPredList::CPredList(std::string _named, std::initializer_list<HPred> _plist) : CPred(_named), plist(_plist) {
}

EqualsResul CPredList::match(MTermSet &_h) {

    //if   ((_h.front()->repr() == "(") &&  (_h.back()->repr() == ")"))
    if ((_h.front()->is_openBracket()) && (_h.back()->is_closeBracket())) {
        size_t n = plist.size();
        if ((_h.size() - 2) != n) {
            return NotEquals;
        }
        for (size_t j = 0; j < n; ++j) {
            if (equals(this->plist[j].get(), _h[j + 1].get()) != Equals) {
                return NotEquals;
            }
        }

    }

    {

        if (_h.size() != plist.size()) {
            if (CMLOG) std::cout << _h.size() << " !=  " << plist.size() << std::endl;
            return NotEquals;
        }
        size_t n = plist.size();
        for (size_t j = 0; j < n; ++j) {
            if (this->plist[j]->match(_h[j]) != Equals) {
                if (CMLOG) std::cout << "Diff   " << this->plist[j]->repr() << " !=  " << _h[j]->repr() << std::endl;
                return NotEquals;
            }
        }
    }
    return Equals;
}

EqualsResul CPredList::match(HTerm h) {
    CList *lst = dynamic_cast<CList * >(h.get());
    if (lst != nullptr) {
        auto asVector = lst->asVector();
        return this->match(asVector); //chama o termo superior

    }
    return NotEquals;
}

bool CPredAny::isSame(HTerm h) {

    if (CPredAny *hlist = dynamic_cast<CPredAny *>(h.get())) {
        return true;
    }
    return false;
}

std::string CPredAny::repr() {
    return "Pred(_)";
}

CPredAny::CPredAny(std::string _named) : CPred(_named) {
}

EqualsResul CPredAny::match(MTermSet &_h) {
    return Equals;
}

EqualsResul CPredAny::match(HTerm h) {
    return Equals;
}

bool CPredWord::isSame(HTerm b) {
    if (CPredWord *hlist = dynamic_cast<CPredWord *>(b.get())) {
        return true;
    }
    return false;
}

std::string CPredWord::repr() {
    return "Pred(\\W)";
}

CPredWord::CPredWord(std::string _named) : CPred(_named) {
}

EqualsResul CPredWord::match(MTermSet &_h) {
    return NotEquals;

}

EqualsResul CPredWord::match(HTerm h) {
    if (CString *v = dynamic_cast<CString *>(h.get())) {
        return Equals;
    }
    return NotEquals;
}

CPredBoolean::CPredBoolean(const std::string &_named) : CPred(_named) {
}

bool CPredBooleanAnd::isSame(HTerm b) {
    if (CPredBooleanAnd *v = dynamic_cast<CPredBooleanAnd *>(b.get())) {
        if (this->b1->isSame(v->b1) == false) return false;
        if (this->b2->isSame(v->b2) == false) return false;
        return true;
    }
    return false;
}

std::string CPredBooleanAnd::repr() {

    return "(" + b1->repr() + " AND " + b1->repr() + ")";
}

EqualsResul CPredBooleanAnd::match(MTermSet &h) {
    if ((this->b1->match(h) == Equals) && (this->b2->match(h) == Equals)) return Equals;
    return NotEquals;
}

EqualsResul CPredBooleanAnd::match(HTerm h) {
    if ((this->b1->match(h) == Equals) && (this->b2->match(h) == Equals)) return Equals;
    return NotEquals;

}

CPredBooleanAnd::CPredBooleanAnd(const std::string &_named, const HPred &c_pred, const HPred &c_pred1) : CPredBoolean(
        _named),
                                                                                                         b1(c_pred),
                                                                                                         b2(c_pred1) {
}

bool CPredBooleanOr::isSame(HTerm b) {

    if (CPredBooleanOr *v = dynamic_cast<CPredBooleanOr *>(b.get())) {
        int n = blist.size();
        if (v->blist.size() != n) return false;

        for (int i = 0; i < n; ++i) {
            if (blist[i]->isSame(v->blist[i]) == false) return false;
        }
        return true;
    }
    return false;

}

std::string CPredBooleanOr::repr() {
    return "(" + blist.front()->repr() + " OR " + blist.back()->repr() + ")";
}

CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1) : CPredBoolean(
        _named), blist({c_pred, c_pred1}) {
}

CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1,
                               const HPred &c_pred2) : CPredBoolean(_named), blist({c_pred, c_pred1, c_pred2}) {

}

CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1,
                               const HPred &c_pred2, const HPred &c_pred3) : CPredBoolean(_named),
                                                                             blist({c_pred, c_pred1, c_pred2,
                                                                                    c_pred3}) {
}

CPredBooleanOr::CPredBooleanOr(const std::string &_named, std::list<HPred> plist) : CPredBoolean(_named),
                                                                                    blist(plist.begin(), plist.end()) {
}

EqualsResul CPredBooleanOr::match(MTermSet &h) {
    for (auto it = blist.begin(); it != blist.end(); ++it) {
        if ((*it)->match(h) == Equals) return Equals;
    }
    return NotEquals;

}

EqualsResul CPredBooleanOr::match(HTerm h) {
    for (auto it = blist.begin(); it != blist.end(); ++it) {
        if ((*it)->match(h) == Equals) return Equals;
    }
    return NotEquals;
}

//===============================================
//Makes 


bool isSamePred(std::vector<HPred> a, std::vector<HPred> b) {
    int n = a.size();
    if (n != b.size()) return false;
    for (int i = 0; i < n; ++i) {
        if (a[i]->isSame(b[i]) == false) return false;
    }
    return true;

}

HPred mkHPredAtom(std::string _named, HTerm atom) { return std::make_shared<CPredAtom>(_named, atom); };

HPred mkHPredList(std::string _named, std::initializer_list<HPred> plist) {
    return std::make_shared<CPredList>(_named, plist);
};

HPred mkHPredAny(std::string _named) { return std::make_shared<CPredAny>(_named); };

HPred mkHPredWord(std::string _named) { return std::make_shared<CPredWord>(_named); };

HPred mkHPredBooleanAnd(const std::string &_named, const HPred &c_pred,
                        const HPred &c_pred1) { return std::make_shared<CPredBooleanAnd>(_named, c_pred, c_pred1); };

HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred,
                       const HPred &c_pred1) { return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1); };

HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2) {
    return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1, c_pred2);
};

HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2,
                       const HPred &c_pred3) {
    return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1, c_pred2, c_pred3);
};


//======================================


void MatchResult::setValue(std::string named, HTerm value) {
    this->matchs[named] = value;
}

HTerm MatchResult::getValue(std::string named) {
    return this->matchs[named];
}

void MatchResult::insert(MatchResult &other) {
    for (auto kv = other.matchs.begin(); kv != other.matchs.end(); ++kv) {
        this->setValue(kv->first, kv->second);
    }
}

bool isFullListBracket(MTermSet m) {
    //alista so tem 1 par de () e eles estao nas bordas ?
    int cc_open = 0;
    int cc_close = 0;
    int level = 0;
    //if (m.front()->repr() != "(") return false;
    // if (m.back()->repr() != ")") return false;

    if (m.front()->is_openBracket() == false) return false;
    if (m.back()->is_closeBracket() == false) return false;

    bool isFullEnclose = true;

    int slen = m.size();

    for (int i = 0; i < slen; ++i) {

        if (m[i]->is_closeBracket()) level--;
        if (m[i]->is_openBracket()) level++;
        if (level == 0 && i != (slen - 1)) {
            isFullEnclose = false;
        }

    }

    return isFullEnclose;
}

MTermSet remove_boundaryListMark(MTermSet &m) {
    if (isFullListBracket(m) == false)return m;

    MTermSet mnext;
    int n = m.size();
    for (int j = 1; j < n - 1; ++j) {
        mnext.push_back(m[j]);
    }
    return mnext;
}

HTerm convertToTerm(MTermSet &m) {
    if (m.size() == 1) {
        return m[0];
    } else {
        //m = remove_boundaryListMark(m);
        auto lst_ptr = std::make_shared<CList>();
        lst_ptr->lst = std::list<HTerm>(m.begin(), m.end());
        //lst_ptr->lst.insert(lst_ptr->lst.end(), m.begin(), m.end());
        //return HTerm(lst_ptr);
        return lst_ptr;
    }
}


MatchResult makeMatch(std::string named, HTerm value) {
    MatchResult m;
    m.result = Equals;
    m.setValue(named, value);
    return m;
}


MatchResult CMatch_j(MTermSet &termo, CPred *predicate) {
    if (CMLOG) std::cout << "Query|   " << predicate->repr() << " >> " << get_repr(termo);
    bool has_match = (predicate->match(termo) == Equals);
    if (has_match) {
        if (CMLOG) std::cout << "   TRUE" << std::endl;
    } else {
        if (CMLOG) std::cout << "   FALSE" << std::endl;
    }
    if (has_match) {

        return makeMatch(predicate->named, convertToTerm(termo));
    }

    return MatchResult();
}


MatchResult CMatch_LI(std::vector<HTerm> term, HPred predicate) {
    CPredList *plst = dynamic_cast<CPredList * >(predicate.get());
    if (plst != nullptr) {
        return CMatch(term, plst->plist);

    }
    return MatchResult();
}

MatchResult CMatch_IL(HTerm term, std::vector<HPred> predicate) {
    CList *lst = dynamic_cast<CList * >(term.get());
    if (lst != nullptr) {
        return CMatch(lst->asVector(), predicate);
    }
    return MatchResult();
}


MatchResult CMatch_combinacao(MTermSetCombinatoria &combinacao, std::vector<CPred *> predicates_ptr) {
    size_t n = predicates_ptr.size();
    size_t tn = combinacao.size();

    if (tn != n) //numero de MTerset nao eh igual aos de predicates
    {
        // std::cout << get_repr(combinacao) << std::endl;
        return MatchResult();
    }

    //Test only the Literals, for early exit
    {
        MatchResult mm;
        mm.result = Equals; // inicia com tudo OK
        for (size_t i = 0; i < tn; ++i) {
            CPred *term_i = predicates_ptr[i];
            if (CPredAtom *v = dynamic_cast<CPredAtom *>(term_i )) {

                MTermSet &termGroup = combinacao[i];
                MatchResult mj = CMatch_j(termGroup, term_i);
                if (mj.result != Equals) {
                    return MatchResult();
                }
            }

        }

    }

    //All Others
    {
        MatchResult mm;
        mm.result = Equals; // inicia com tudo OK
        for (size_t i = 0; i < tn; ++i) {
            CPred *term_i = predicates_ptr[i];

            MTermSet &termGroup = combinacao[i];
            MatchResult mj = CMatch_j(termGroup, term_i);
            if (mj.result != Equals) {
                return MatchResult();
            }
            mm.insert(mj);
        }
        return mm;
    }

}


MatchResult CMatch(std::vector<HTerm> lst, std::vector<HPred> predicates) {
    size_t npred = predicates.size();
    int a = lst.size();

    if (a == npred) {
        if (CMLOG) std::cout << get_repr(lst) << std::endl;

    }

    MTermSet expandContents = remove_boundaryListMark(lst);

    int b = expandContents.size();

    if (b == npred) {
        if (CMLOG) std::cout << get_repr(lst) << std::endl;

    }
    if (a != b) {
        if (CMLOG) std::cout << "??" << std::endl;
    }

    //std::cout << get_repr(lst) << std::endl;
    //std::cout << get_repr(remove_boundaryListMark(lst)) << std::endl;

    std::vector<CPred *> predicates_ptr;
    for (auto it = predicates.begin(); it != predicates.end(); ++it) {
        predicates_ptr.push_back(it->get());
    }

    if (true) {
        MatchResult mmResultMatch;
        FuncCombinatoria f_disp = [&](MTermSetCombinatoria &x) {

            if (CMLOG) std::cout << std::endl;
            MatchResult mm = CMatch_combinacao(x, predicates_ptr);
            if (mm.result == Equals) {
                mmResultMatch = mm;
                return true;
            }
            return false;

        };

        //applyCombinatorias(expandContents, npred, f_disp);
        applyCombinatorias_smart(expandContents, npred, predicates_ptr, f_disp);
        return mmResultMatch;

    } else {
        MTermSetCombinatoriaList comb = getCombinatorias(expandContents, npred);
        size_t comSize = comb.size();
        for (auto it = comb.begin(); it != comb.end(); ++it) {
            if (CMLOG) std::cout << std::endl;
            MatchResult mm = CMatch_combinacao(*it, predicates_ptr);
            if (mm.result == Equals) {
                return mm;
            }
        }
        return MatchResult();
    }
}

MatchResult CMatch(HTerm term, std::vector<HPred> predicates) {
    if (predicates.size() == 1) {
        if (predicates.front()->match(term) == Equals) {
            return makeMatch(predicates.front()->named, term);
        }
        return MatchResult();
    }

    CList *lst = dynamic_cast<CList * >(term.get());
    if (lst != nullptr) {
        return CMatch(lst->asVector(), predicates); // trata como uma lista
    }
    return MatchResult();;
}


std::string get_repr(MatchResult r) {
    std::string s;
    for (auto kv = r.matchs.begin(); kv != r.matchs.end(); ++kv) {
        s += kv->first + ":";
        s += kv->second->repr();
        s += "\n";
    }
    return s;
};

