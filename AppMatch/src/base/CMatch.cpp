// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

 #include "match/CMatch.hpp"
#include "match/CMatchCombinatoria.hpp"
#include "base/EqualsResult.hpp"
#include "base/CBase.hpp"


#include <vector> 
#include <memory>
#include <functional>
#include <iostream>

#include <cassert>


#undef CMLOG 


#ifdef CMLOG
#include <iostream>
#endif

using namespace NSTerm;

using namespace  NSMatch;

using namespace EqualResulting;

 

std::string get_repr_i(std::vector<HTerm> lst) {
	std::string q;
	q += " [ ";
	for (auto tr = lst.begin(); tr != lst.end(); ++tr) {
		if (tr != lst.begin()) q += " , ";
		q += tr->get()->repr();
	}
	q += " ] ";
	return q;
}
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

		std::string  get_repr(MTermSetCombinatoria lst) {

			std::string q;
			q += " { ";
			for (auto tr = lst.begin(); tr != lst.end(); ++tr) {
				q += get_repr(*tr) + " ";
			}
			q += " } ";
			return q;
		}




		//=====================================================================




		std::string  get_repr(MTermSetCombinatoriaList lst) {
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

		bool CPredAtom::isSame(HTerm b)
		{
			if (b->type() == TermType::PredAtom)
			{
				CPredAtom *hlist = static_cast<CPredAtom*>(b.get());
				{
					return (equals(this->h.get(), hlist->h.get()) == Equals);
				}
			}
			return false;
		}

		std::string CPredAtom::repr() {
			return "Pred(" + this->h->repr() + ")";
		}

		CPredAtom::CPredAtom(std::string _named, HTerm atom) : CPred(_named), h(atom) {
		}

		EqualsResul CPredAtom::match(MTermSet &_h)
		{
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
		EqualsResul CPredAtom::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			auto hsize = vend - vbegin;
			if (hsize == 3) {
				// if ((_h[0]->repr() == "(") &&  (_h[2]->repr() == ")"))
				if (((*(vbegin + 0))->is_openBracket()) && ((*(vbegin + 2))->is_closeBracket())) {
					return equals(this->h.get(), (*(vbegin + 1)).get());
				}
			}
			if (hsize == 1) {
				return equals(this->h.get(), (*vbegin).get());
			}
			return NotEquals;
		}



		EqualsResul CPredAtom::match(HTerm h) {

			return equals(this->h.get(), h.get());
		}

		bool CPredList::isSame(HTerm h) {
			if (CPredList *hlist = asPredList(h.get())) {
				if (this->plist.size() != hlist->plist.size()) return false;
				for (size_t i = 0; i < this->plist.size(); ++i) {
					if (!this->plist[i]->isSame(hlist->plist[i])) {
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

					{
#ifdef CMLOG
						std::cout << _h.size() << " !=  " << plist.size() << std::endl;
#endif
					}
					return NotEquals;
				}
				size_t n = plist.size();
				for (size_t j = 0; j < n; ++j) {
					if (this->plist[j]->match(_h[j]) != Equals) {

						{
#ifdef CMLOG
							std::cout << "Diff   " << this->plist[j]->repr() << " !=  " << _h[j]->repr() << std::endl;
#endif
						}
						return NotEquals;
					}
				}
			}
			return Equals;
		}

		EqualsResul CPredList::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			auto hfront = *vbegin;
			auto hback = *(vend - 1);
			auto hsize = vend - vbegin;
			//if   ((_h.front()->repr() == "(") &&  (_h.back()->repr() == ")"))
			if ((hfront->is_openBracket()) && (hback->is_closeBracket())) {
				size_t n = plist.size();
				if ((hsize - 2) != n) {
					return NotEquals;
				}
				for (size_t j = 0; j < n; ++j) {
					//if (equals(this->plist[j].get(), _h[j + 1].get()) != Equals) {			return NotEquals;		}
					if (equals(this->plist[j].get(), (*(vbegin + j + 1)).get()) != Equals) { return NotEquals; }
				}

			}

			{

				if (hsize != plist.size()) {

					{
#ifdef CMLOG
						std::cout << hsize << " !=  " << plist.size() << std::endl;
#endif
					}
					return NotEquals;
				}
				size_t n = plist.size();
				for (size_t j = 0; j < n; ++j) {
					if (this->plist[j]->match((*(vbegin + j))) != Equals) {

						{
#ifdef CMLOG
							std::cout << "Diff   " << this->plist[j]->repr() << " !=  " << (*(vbegin + j))->repr() << std::endl;
#endif
						}
						return NotEquals;
					}
				}
			}
			return Equals;
		}


		EqualsResul CPredList::match(HTerm h)
		{
			CList *lst = asCList(h.get());
			if (lst != nullptr) {

				MTermSet v = lst->asVector();
				return this->match(v);
			}
			return NotEquals;
		}


		bool CPredAny::isSame(HTerm h) {

			if (CPredAny *hlist = asPredAny(h.get())) {
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

		EqualsResul CPredAny::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			return Equals;
		}

		EqualsResul CPredAny::match(HTerm h) {
			return Equals;
		}


		
		CPredOptional::CPredOptional(HPred _inner) : inner(_inner), CPred("_") {}


		bool CPredOptional::isSame(HTerm b)
		{
			if (CPredOptional *h  = asPredOptional(b.get())) {
				return (inner->isSame(h->inner));
			}
			return false;
		
		}
		std::string CPredOptional::repr() 
		{
			return "Optional(" + inner->repr()+ ")";
		};


		EqualsResul CPredOptional::match(MTermSet &_h) {
			return Equals;
		}

		EqualsResul CPredOptional::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			return Equals;
		}

		EqualsResul CPredOptional::match(HTerm h) {
			return Equals;
		}




		bool CPredWord::isSame(HTerm b) {
			if (CPredWord *hlist = asPredWord(b.get())) {
				return true;
			}
			return false;
		}

		std::string CPredWord::repr() {
			return "Pred(\\W)";
		}

		CPredWord::CPredWord(std::string _named) : CPred(_named) {
		}

		EqualsResul CPredWord::match(MTermSet &_h) 
		{
			if (_h.size() == 1) return this->match(_h[0]);
			return NotEquals;

		}

		EqualsResul CPredWord::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			auto nn = std::next(vbegin);
			if (nn == vend) return this->match(*vbegin);
			return NotEquals;
		}

		EqualsResul CPredWord::match(HTerm h) {
			if (CString *v = asCString(h.get())) 
			{
				return Equals;
			}
			return NotEquals;
		}

		CPredBoolean::CPredBoolean(const std::string &_named) : CPred(_named) {
		}

		bool CPredBooleanAnd::isSame(HTerm b) {
			if (b->type() == TermType::PredBooleanAnd)
			{
				if (CPredBooleanAnd *v = static_cast<CPredBooleanAnd *>(b.get())) {
					if (!this->b1->isSame(v->b1)) return false;
					return this->b2->isSame(v->b2);
				}
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

		EqualsResul CPredBooleanAnd::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			if ((this->b1->match(vbegin, vend) == Equals) && (this->b2->match(vbegin, vend) == Equals)) return Equals;
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
			if (b->type() == TermType::PredBooleanOr)
			{
				if (CPredBooleanOr *v = static_cast<CPredBooleanOr *>(b.get())) {
					size_t n = blist.size();
					if (v->blist.size() != n) return false;

					for (int i = 0; i < n; ++i) {
						if (!blist[i]->isSame(v->blist[i])) return false;
					}
					return true;
				}
			}
			return false;

		}

		std::string CPredBooleanOr::repr() {
			return "(" + blist.front()->repr() + " OR " + blist.back()->repr() + ")";
		}

		CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1) : CPredBoolean(
			_named), blist({ c_pred, c_pred1 }) {
		}

		CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1,
			const HPred &c_pred2) : CPredBoolean(_named), blist({ c_pred, c_pred1, c_pred2 }) {

		}

		CPredBooleanOr::CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1,
			const HPred &c_pred2, const HPred &c_pred3) : CPredBoolean(_named),
			blist({ c_pred, c_pred1, c_pred2,
				   c_pred3 }) {
		}

		CPredBooleanOr::CPredBooleanOr(const std::string &_named, std::list<HPred> plist) : CPredBoolean(_named),
			blist(plist.begin(), plist.end()) {
		}

		EqualsResul CPredBooleanOr::match(MTermSet &h) 
		{
			
			for (auto it = blist.begin(); it != blist.end(); ++it) 
			{ 
				if ((*it)->match(h) == Equals) return Equals;
			}
			if (h.size() == 1) return this->match(h[0]);
			return NotEquals;
		}

		EqualsResul CPredBooleanOr::match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend)
		{
			for (auto it = blist.begin(); it != blist.end(); ++it) 
			{ 
				if ((*it)->match(vbegin, vend) == Equals) return Equals;
			}
			return NotEquals;
		}

		EqualsResul CPredBooleanOr::match(HTerm h) {
			for (auto it = blist.begin(); it != blist.end(); ++it) 
			{ 
				if ((*it)->match(h) == Equals) return Equals;
			}
			return NotEquals;
		}

		//===============================================
		//Makes 


		bool NSTerm::isSamePred(std::vector<HPred> a, std::vector<HPred> b) {
			size_t n = a.size();
			if (n != b.size()) return false;
			for (int i = 0; i < n; ++i) {
				if (!a[i]->isSame(b[i])) return false;
			}
			return true;

		}

		HPred NSTerm::pAtom(std::string _named, HTerm atom) 
		{
			return std::make_shared<CPredAtom>(std::move(_named), std::move(atom));
		};

		HPred NSTerm::pList(std::string _named, std::initializer_list<HPred> plist) {
			return std::make_shared<CPredList>(std::move(_named), std::move((plist)));
		};

		HPred NSTerm::pList( std::initializer_list<HPred> plist) {
			return std::make_shared<CPredList>( "_", std::move((plist)));
		};

		HPred NSTerm::pOptional(HPred p){ return std::make_shared<CPredOptional>(p); }		

		
	 

		HPred NSTerm::pAny(std::string _named) { return std::make_shared<CPredAny>(_named); };

		HPred NSTerm::pWord(std::string _named) { return std::make_shared<CPredWord>(_named); };

		HPred NSTerm::pAnd(const std::string _named, const HPred c_pred,	const HPred c_pred1) {
			return std::make_shared<CPredBooleanAnd>(_named, c_pred, c_pred1);
		};

		HPred NSTerm::pOr(const std::string _named, const HPred c_pred,	const HPred c_pred1) {
			return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1);
		};

		HPred NSTerm::pOr(const std::string _named, const HPred c_pred, const HPred c_pred1, const HPred c_pred2) {
			return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1, c_pred2);
		};

		HPred NSTerm::pOr(const std::string _named, const HPred c_pred, const HPred c_pred1, const HPred c_pred2,
			const HPred c_pred3) {
			return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1, c_pred2, c_pred3);
		};

		HPred NSTerm::pOr(const std::string _named, const HPred c_pred, const HPred c_pred1, const HPred c_pred2, const HPred c_pred3 , const HPred c_pred4 ) {
			return std::make_shared<CPredBooleanOr>(_named, std::list<HPred>({ c_pred, c_pred1, c_pred2, c_pred3, c_pred4 }));
		};

		HPred NSTerm::pOr(const std::string _named, const HPred c_pred, const HPred c_pred1, const HPred c_pred2, const HPred c_pred3, const HPred c_pred4, const HPred c_pred5) {
			return std::make_shared<CPredBooleanOr>(_named, std::list<HPred>({ c_pred, c_pred1, c_pred2, c_pred3, c_pred4, c_pred5 }));
		};



		HPred pLiteral(std::string str);
		HPred NSTerm::pPreposition(const std::string &_named ) 
		{
			std::list<std::string> vlist = std::list<std::string>({ "above", "across", "after", "against", "along", "among", "around","at", "before", "behind", "below", "beneath", "beside", "between", "things", "by", "down", "for", "from", "originates", "in", "inside", "into", "near", "off", "on", "onto", "opposite", "out", "outside", "over", "past", "round", "through", "throughout", "to", "towards", "under", "underneath", "up" ,"until" });
			std::list<HPred> plist;
			for (auto r : vlist)
			{   
			
				plist.push_back(pLiteral(r));
			}
			auto r = std::make_shared<CPredBooleanOr>(_named,  plist);		 
			return r;
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

		bool isFullListBracket(const MTermSet& m) {
			//alista so tem 1 par de () e eles estao nas bordas ?
			int cc_open = 0;
			int cc_close = 0;
			int level = 0;
			//if (m.front()->repr() != "(") return false;
			// if (m.back()->repr() != ")") return false;

			if (!m.front()->is_openBracket()) return false;
			if (!m.back()->is_closeBracket()) return false;

			bool isFullEnclose = true;

			size_t slen = m.size();

			for (int i = 0; i < slen; ++i) {

				if (m[i]->is_closeBracket()) level--;
				if (m[i]->is_openBracket()) level++;
				if (level == 0 && i != (slen - 1)) {
					isFullEnclose = false;
				}

			}

			return isFullEnclose;
		}

		MTermSet remove_boundaryListMark(MTermSet &m)
		{
			if (!isFullListBracket(m)) return m;
			size_t n = m.size();
			return MTermSet(m.begin() + 1, m.begin() + (n - 1));

			MTermSet mnext;
			for (int j = 1; j < n - 1; ++j) {
				mnext.push_back(m[j]);
			}
			return mnext;
		}

		std::pair<MTermSet::iterator, MTermSet::iterator> remove_boundaryListMark_range(MTermSet &m)
		{
			if (!isFullListBracket(m)) return std::make_pair(m.begin(), m.end());
			size_t n = m.size();
			return std::make_pair(m.begin() + 1, m.begin() + (n - 1));


			MTermSet mnext;
			for (int j = 1; j < n - 1; ++j) {
				mnext.push_back(m[j]);
			}
			return std::make_pair(mnext.begin(), mnext.end());
			//return mnext;
		}

		HTerm  NSTerm::convertToTerm(MTermSet &m) 
		{
			if (m.size() == 1) {
				return m[0];
			}
			else {
				//m = remove_boundaryListMark(m);
				auto lst_ptr = std::make_shared<CList>();
				lst_ptr->lst = std::list<HTerm>(m.begin(), m.end());
				//lst_ptr->lst.insert(lst_ptr->lst.end(), m.begin(), m.end());
				//return HTerm(lst_ptr);
				return lst_ptr;
			}
		}


		MatchResult NSMatch::makeMatch(std::string named, HTerm value) {
			MatchResult m;
			m.result = Equals;
			m.setValue(named, value);
			return m;
		}




		MatchResult CMatch_LI(std::vector<HTerm> term, HPred predicate) {
			CPredList *plst = asPredList(predicate.get());
			if (plst != nullptr) {
				return CMatch(term, plst->plist);

			}
			return MatchResult();
		}

		MatchResult CMatch_IL(HTerm term, std::vector<HPred> predicate) {
			CList *lst = asCList(term.get());
			if (lst != nullptr) {
				auto vv = lst->asVector();
				return CMatch(vv, predicate);
			}
			return MatchResult();
		}


 

 

		MatchResult  NSMatch::CMatch__(std::vector<HTerm>&   lst, const std::vector<HPred> &predicates) 
		{
			if (lst.size() == 1)
			{
				if (lst[0]->type() == TermList)
				{
					auto vs = asCList(lst[0].get())->asVector();
					return CMatch__(vs, predicates);
				}
			}



			size_t npred = predicates.size();
			size_t a = lst.size();

			if (a == 0)
			{
				return MatchResult();
			}

			if (a < npred)
			{
				return MatchResult();
			}
#ifdef CMLOG
			if (a == npred) {
				std::cout << get_repr_i(lst) << std::endl;
			}
#endif

		 

			auto expandContents = remove_boundaryListMark_range(lst);
			std::vector<HTerm>::iterator vbegin = expandContents.first;
			std::vector<HTerm>::iterator vend = expandContents.second;


#ifdef CMLOG
			int b = vend - vbegin;
			if (b == npred) {
				std::cout << get_repr_i(lst) << std::endl;

			}
			if (a != b) {
				std::cout << "??" << std::endl;
			}
#endif

			//std::cout << get_repr(lst) << std::endl;
			//std::cout << get_repr(remove_boundaryListMark(lst)) << std::endl;


			std::vector<CPred *> predicates_ptr(npred);
			for (size_t k = 0; k < npred; ++k)predicates_ptr[k] = predicates[k].get();
			//for (auto it = predicates.begin(); it != predicates.end(); ++it) {     predicates_ptr.push_back(it->get());  }

			MatchResult mmResultMatch;
			FuncCombinatoria f_disp = [&](MTermSetCombinatoria &x) {

#ifdef CMLOG
				std::cout << std::endl;
#endif

				MatchResult mm = NSMatch::CMatch_combinacao(x, predicates_ptr);
				if (mm.result == Equals) {
					mmResultMatch = mm;
					return true;
				}
				return false;

			};
			applyCombinatorias_smart_range(vbegin, vend, npred, predicates_ptr, f_disp);
			return mmResultMatch;
		}

		 
		MatchResult NSMatch::CMatch_opt__(HTerm term, const  std::vector<HPred>& predicates)
		{
			//expand os optionais... se tiver			
			for (auto it = predicates.begin(); it != predicates.end();++it)
			{
				if ((*it)->type() == PredOptional)
				{
					std::vector<HPred> v1 = std::vector<HPred>(predicates.begin(), it);
					
					CPredOptional *c = asPredOptional((*it).get());
					v1.push_back(c->inner);
					auto it2 = std::next(it);
					v1.insert(v1.end(), it2, predicates.end());
					auto res1 =  CMatch_opt__(term, v1);
					if (res1.result == EqualResulting::Equals) return res1;
					std::vector<HPred> v2 = std::vector<HPred>(predicates.begin(), it);
					v2.insert(v2.end(), it2, predicates.end());					
					auto res2 = CMatch_opt__(term, v2);
					if (res2.result == EqualResulting::Equals) return res2;
				}
			}			
			return CMatch__(term, predicates);
		}


		MatchResult NSMatch::CMatch_opt__(std::vector<HTerm>& termList, const  std::vector<HPred>& predicates)
		{
			//expand os optionais... se tiver			
			for (auto it = predicates.begin(); it != predicates.end(); ++it)
			{
				if ((*it)->type() == PredOptional)
				{
					std::vector<HPred> v1 = std::vector<HPred>(predicates.begin(), it);

					CPredOptional *c = asPredOptional((*it).get());
					v1.push_back(c->inner);
					auto it2 = std::next(it);
					v1.insert(v1.end(), it2, predicates.end());
					auto res1 = CMatch_opt__(termList, v1);
					if (res1.result == EqualResulting::Equals) return res1;
					std::vector<HPred> v2 = std::vector<HPred>(predicates.begin(), it);
					v2.insert(v2.end(), it2, predicates.end());
					auto res2 = CMatch_opt__(termList, v2);
					if (res2.result == EqualResulting::Equals) return res2;
				}
			}
			return CMatch__(termList, predicates);
		}



		MatchResult NSMatch::CMatch__(HTerm term, const  std::vector<HPred>& predicates) 
		{
			
			if (predicates.size() == 1) {
				if (predicates.front()->match(term) == Equals) {
					return makeMatch(predicates.front()->named, term);
				}
				return MatchResult();
			}

			CList *lst = asCList(term.get());
			if (lst != nullptr) {
				auto v = lst->asVector();
				return CMatch(v, predicates); // trata como uma lista
			}
			return MatchResult();;
		}

		MatchResult  NSMatch::CMatch(HTerm term, const CPredSequence  & predicates)		
		{ 
			assert(predicates.optional == false);

			{
				for (auto data_next : predicates.data_list)
				{
					auto sub_res = CMatch_opt__(term, data_next);
					if (sub_res.result == EqualResulting::Equals)
					{
						return sub_res;
					}
				}
			}
			return MatchResult();; 
		}

		MatchResult  NSMatch::CMatch(std::vector<HTerm>&    termList, const CPredSequence   &predicates)
		{ 
			assert(predicates.optional == false);
			{
				for (auto data_next : predicates.data_list)
				{
					auto sub_res = CMatch_opt__(termList, data_next);
					if (sub_res.result == EqualResulting::Equals)
					{
						return sub_res;
					}
				}
			}
			return MatchResult();;
		}


		std::string NSMatch::get_repr_result(MatchResult r) {
			std::string s;
			for (auto kv = r.matchs.begin(); kv != r.matchs.end(); ++kv) {
				s += kv->first + ":";
				s += kv->second->repr();
				s += "\n";
			}
			return s;
		}

	 

		CPredAtom* NSTerm::asPredAtom(CTerm* c)
		{
			if (c->type() == PredAtom) return static_cast<CPredAtom*>(c);
			return nullptr;
		}

	 

	 	CPredOptional* NSTerm::asPredOptional(CTerm* c)
		{
			if (c->type() == PredOptional) return static_cast<CPredOptional*>(c);
			return nullptr;
		};

		CPredList* NSTerm::asPredList(CTerm* c)
		{
			if (c->type() == PredList) return static_cast<CPredList*>(c);
			return nullptr;
		};

		CPredAny* NSTerm::asPredAny(CTerm* c)
		{
			if (c->type() == TermType::PredAny) return static_cast<CPredAny*>(c);
			return nullptr;
		};

		CPredWord* NSTerm::asPredWord(CTerm* c)
		{
			if (c->type() == TermType::PredWord) return static_cast<CPredWord*>(c);
			return nullptr;
		};

		CPredSequence  NSTerm::pOptional(CPredSequence p)
		{
			p.optional = true;
			return p;
		}

		namespace NSTerm
		{
			 


			//======================================

			CPredSequence operator<<(HPred a, HPred b)
			{
				return CPredSequence({ a,b });
			}
			CPredSequence operator<<(CPredSequence a, HPred b)
			{	
				for (auto &lst : a.data_list) lst.push_back(b);

				if (a.optional)
				{
					a.data_list.push_back({ b });
				}
				a.optional = false;
				return a;
			}

			CPredSequence operator<<(CPredSequence a, CPredSequence b)
			{
				std::list<std::vector<HPred>> v_comb;
				std::list<std::vector<HPred>> a_data_lst = a.data_list;
				std::list<std::vector<HPred>> b_data_lst = b.data_list;
					
				for (auto lst_a : a_data_lst)
				{
					for (auto &lst_b : b_data_lst)
					{
						std::vector<HPred> i_comb(lst_a);
						i_comb.insert(i_comb.end(), lst_b.begin(), lst_b.end());
						v_comb.push_back(i_comb);
					}					
				}	
				if (a.optional)
				{
					for (auto &lst_b : b_data_lst)
					{
						v_comb.push_back(lst_b);
					}
				}

				if (b.optional)
				{
					for (auto &lst_a : a_data_lst)
					{
						v_comb.push_back(lst_a);
					}
				}


				a.data_list = v_comb;
				
				a.optional = a.optional && b.optional; //se a e b forem optionais entao essa sequencia eh opticional tambem

				return a;
			}
			 
			CPredSequence operator||(CPredSequence a, CPredSequence  b)
			{
				for (auto &lst_b : b.data_list)
				{
					a.data_list.push_back(lst_b);
				}
				a.optional = a.optional || b.optional;

				return std::move(a);
			}

		}