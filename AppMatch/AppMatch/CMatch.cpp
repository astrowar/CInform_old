#include "CBase.h"
#include <vector>
#include "CMatch.h"
#include <iostream>
#include <memory>

std::string get_repr(MTermSet lst)
{
	std::string q;
	q += " [ ";
	for (auto tr = lst.begin(); tr != lst.end(); ++tr)
	{
		if (tr != lst.begin()) q += " , ";
		q += tr->get()->repr() ;
	}
	q += " ] ";
	return q;
}

//Obtem uma lista de M termos e quebra ela em Combinacoes de Sets de tamanho N
MTermSetCombinatoria cons(MTermSet& head, MTermSetCombinatoria& tail)
{
	MTermSetCombinatoria accTerms;
	accTerms.push_back(head);
	for (auto k = tail.begin(); k != tail.end(); ++k)
	{
		accTerms.push_back(*k);
	}
	return accTerms;
}

//cada termo eh um MTermSet
MTermSetCombinatoriaList getCombinatoriasUnitary(std::vector<HTerm> terms)
{
	MTermSetCombinatoria uniq;
	for (auto it = terms.begin(); it != terms.end(); ++it)
	{
		uniq.push_back({MTermSet({*it})});
	}
	return MTermSetCombinatoriaList({uniq});
}

//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
MTermSetCombinatoriaList getCombinatoriasGroup(std::vector<HTerm> terms)
{
	return MTermSetCombinatoriaList({MTermSetCombinatoria({terms})});
}


bool isListValid_single(MTermSetCombinatoria listComb)
{
	//para cada termo Simples, verifica se eh um "(" ou ")" isolado
	for (auto it = listComb.begin(); it != listComb.end(); ++it)
	{
		if (it->size() == 1)
		{
			if ((*it).front()->repr() == "(") return false;
			if ((*it).front()->repr() == ")") return false;
		}
	}
	return true;
}

bool isListValid_bounds(MTermSetCombinatoria listComb)
{
	//para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim
	for (auto it = listComb.begin(); it != listComb.end(); ++it)
	{
		if (it->size() > 1)
		{
			if ((*it).front()->repr() == ")") return false;
			if ((*it).back()->repr() == "(") return false;
		}
	}
	return true;
}

bool isListValid_count(MTermSetCombinatoria listComb)
{
	//para cada termo de lista, verifica se eh um "(" no inicio e obrigatoriamente um ")" no fim
	for (auto it = listComb.begin(); it != listComb.end(); ++it)
	{
		int cc_open = 0;
		int cc_close = 0;
		int ns = (it->size());
		 for(int j =0 ; j< ns ;++j)

		{
			if ((*it).at(j)->repr() == ")") cc_open++;
			if ((*it).at(j)->repr() == "(") cc_close++;			
		}
		 if (cc_open != cc_close) return false;
	}
	return true;
}

bool isListValid(MTermSetCombinatoria listComb)
{
	if (isListValid_single(listComb) == false) return false;
	if (isListValid_bounds(listComb) == false) return false;
	if (isListValid_count(listComb) == false) return false;
	return true;
}

MTermSetCombinatoriaList getCombinatoriasRec(std::vector<HTerm> terms, size_t n) //num termos que restam
{
	if (n == 1)
	{
		return getCombinatoriasGroup(terms); // apenas uma combinacao eh possivel 
	}
	size_t lsize = terms.size();
	if (n == lsize)
	{
		return getCombinatoriasUnitary(terms); //Agiliza o processamento
	}
	//particiona de 1 a (n-1)
	MTermSetCombinatoriaList accTerms;
	for (size_t j = 1; j <= lsize - n + 1; ++j)
	{
		MTermSet head(terms.begin(), terms.begin() + j);
		std::vector<HTerm> tail(terms.begin() + j, terms.end());
		auto tails = getCombinatoriasRec(tail, n - 1);
		for (auto c = tails.begin(); c != tails.end(); ++c)
		{
			MTermSetCombinatoria fullSet = cons(head, *c);

			if (isListValid(fullSet))
			{
				accTerms.push_back(fullSet);
			}
		}
	}
	return accTerms;
}

MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm> lst, size_t n)
{
	if (lst.size() < n)
	{
		return MTermSetCombinatoriaList(); // impossivel ..
	}
	if (lst.size() == n)
	{
		return MTermSetCombinatoriaList({MTermSetCombinatoria({lst})}); // apenas uma combinacao eh possivel 
	}
	return getCombinatoriasRec(lst, n);
}

std::string get_repr(MTermSetCombinatoriaList lst)
{
	std::string q = "{ ";
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		for (auto tt = it->begin(); tt != it->end(); ++tt)
		{
			q += " [ ";
			for (auto tr = tt->begin(); tr != tt->end(); ++tr)
			{
				if (tr != tt->begin())
				{
					q += "|";
				}
				q += tr->get()->repr() ;
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



std::string CPred::repr()
{
	return "Pred";
}

std::string CPredAtom::repr()
{
	return "Pred(" +this->h->repr() +")";
}

CPredAtom::CPredAtom(std::string _named, HTerm atom): CPred(_named), h(atom)
{
}

EqualsResul CPredAtom::match(MTermSet _h)
{
	if (_h.size() == 3)
	{
		if ((_h[0]->repr() == "(") &&  (_h[2]->repr() == ")"))
		{
			return equals(this->h.get(), _h[1].get());
		}
	}

	if (_h.size() == 1)
	{
		return equals(this->h.get(), _h[0].get());
	}
	return NotEquals;
}

EqualsResul CPredAtom::match(HTerm h)
{
	
	return equals(this->h.get(), h.get());
}

std::string CPredList::repr()
{
	std::string s = "";
	size_t n = plist.size();
	for (size_t j = 0; j < n; ++j)
	{
		if (j != 0) s += " ";
		s += plist[j]->repr();
	}
	return "PredList(" + s + ")";
}

CPredList::CPredList(std::string _named, std::initializer_list<HPred> _plist): CPred(_named), plist(_plist)
{
}

EqualsResul CPredList::match(MTermSet _h)
{

	if   ((_h.front()->repr() == "(") &&  (_h.back()->repr() == ")"))
	{
		size_t n = plist.size();
		if ((_h.size() - 2) != n)
		{
			return NotEquals;
		}
		for (size_t j = 0; j < n; ++j)
		{
			if (equals(this->plist[j].get(), _h[j+1].get()) != Equals)
			{
				return NotEquals;
			}
		}

	}
	
	{

		if (_h.size() != plist.size())
		{
			//std::cout << _h.size() << " !=  " << plist.size() << std::endl;
			return NotEquals;
		}
		size_t n = plist.size();
		for (size_t j = 0; j < n; ++j)
		{
			if ( this->plist[j]->match( _h[j]  ) != Equals)
			{
				//std::cout << "Diff   "<< this->plist[j]->repr() << " !=  " << _h[j]->repr()  << std::endl;
				return NotEquals;
			}
		}
	}
	return Equals;
}

EqualsResul CPredList::match(HTerm h)
{
	CList* lst =  dynamic_cast<CList* >(h.get());
	if (lst != nullptr)
	{
		return this->match(lst->asVector()); //chama o termo superior 
		
	}
	return NotEquals;
}

std::string CPredAny::repr()
{
	return "Pred(_)";
}

CPredAny::CPredAny(std::string _named): CPred(_named)
{
}

EqualsResul CPredAny::match(MTermSet _h)
{
	return Equals;
}

EqualsResul CPredAny::match(HTerm h)
{
	return Equals;
}

CPredBoolean::CPredBoolean(const std::string& _named): CPred(_named)
{
}

std::string CPredBooleanAnd::repr()
{
	 
	return "(" + b1->repr() + " AND "+ b1->repr()+ ")";
}

EqualsResul CPredBooleanAnd::match(MTermSet h)
{
	if ((this->b1->match(h) == Equals) && (this->b2->match(h) == Equals)) return Equals;
	return NotEquals;
}

EqualsResul CPredBooleanAnd::match(HTerm h)
{
	if ((this->b1->match(h) == Equals) && (this->b2->match(h) == Equals)) return Equals;
	return NotEquals;

}

CPredBooleanAnd::CPredBooleanAnd(const std::string& _named, const HPred& c_pred, const HPred& c_pred1): CPredBoolean(_named),
                                                                                                        b1(c_pred),
                                                                                                        b2(c_pred1)
{
}

std::string CPredBooleanOr::repr()
{
	return "(" + blist.front()->repr() + " OR " + blist.back()->repr() + ")";
}

CPredBooleanOr::CPredBooleanOr(const std::string& _named, const HPred& c_pred, const HPred& c_pred1): CPredBoolean(_named),blist({ c_pred ,c_pred1 })
                                                                                                      
{
}

CPredBooleanOr::CPredBooleanOr(const std::string& _named, std::list<HPred> plist): CPredBoolean(_named), blist(plist.begin(),plist.end())
{
}

EqualsResul CPredBooleanOr::match(MTermSet h)
{
	for(auto it = blist.begin(); it != blist.end();++it)
	{
		if ((*it)->match(h) == Equals) return Equals;
	}
	return NotEquals;
	
}

EqualsResul CPredBooleanOr::match(HTerm h)
{
	for (auto it = blist.begin(); it != blist.end(); ++it)
	{
		if ((*it)->match(h) == Equals) return Equals;
	}
	return NotEquals;
}

//===============================================
//Makes 
 


HPred mkHPredAtom(std::string _named, HTerm atom) {  return std::make_shared<CPredAtom>(_named, atom); };
HPred mkHPredList(std::string _named, std::initializer_list<HPred> plist) { return std::make_shared<CPredList>(_named, plist); };
HPred mkHPredAny(std::string _named) { return std::make_shared<CPredAny>(_named ); };
HPred mkHPredBooleanAnd(const std::string& _named, const HPred& c_pred, const HPred& c_pred1) { return std::make_shared<CPredBooleanAnd>(_named, c_pred, c_pred1); };
HPred mkHPredBooleanOr(const std::string& _named, const HPred& c_pred, const HPred& c_pred1) { return std::make_shared<CPredBooleanOr>(_named, c_pred, c_pred1); };


//======================================


void MatchResult::setValue(std::string named, HTerm value)
{
	this->matchs[named] = value;
}

HTerm MatchResult::getValue(std::string named)
{
	return this->matchs[named];
}

void MatchResult::insert(MatchResult& other)
{
	for (auto kv = other.matchs.begin(); kv != other.matchs.end(); ++kv)
	{
		this->setValue(kv->first, kv->second);
	}
}

bool isFullListBracket(MTermSet m)
{
	//alista so tem 1 par de () e eles estao nas bordas ?
	int cc_open = 0;
	int cc_close = 0;
	if (m.front()->repr() != "(") return false;
	if (m.back()->repr() != ")") return false;

	for(auto it = m.begin() ; it!= m.end();++it)
	{
		if ((*it)->repr() == "(") cc_open++;
		if ((*it)->repr() == ")") cc_close++;
	}
	if (cc_open == 1 && cc_close == 1)
	{
		return  true;
	}
	return false;
}

MTermSet remove_boundaryListMark(MTermSet m)
{
	if (isFullListBracket(m) == false)return m;

	MTermSet mnext;
	int n = m.size();
	for (int j =1 ; j< n-1;++j )
	{
		mnext.push_back(m[j]);
	}
	return mnext;
}

HTerm convertToTerm(MTermSet m)
{
	if (m.size() == 1)
	{
		return m[0];
	}
	else
	{		
		//m = remove_boundaryListMark(m);
		CList* lst_ptr = new CList();		
		lst_ptr->lst.insert(lst_ptr->lst.end(), m.begin(), m.end());		
		return HTerm(lst_ptr);
	}
}

 

MatchResult makeMatch(std::string named, HTerm value)
{
	MatchResult m;
	m.result = Equals;
	m.setValue(named, value);
	return m;
}




MatchResult CMatch_j(MTermSet termo, HPred predicate)
{
	//std::cout << "Query              " << predicate->repr() << " >> " << get_repr(termo) << std::endl;
	bool has_match = (predicate->match(termo) == Equals);
	if (has_match ) 
	{
	//	std::cout << "   " << predicate->repr() << " == " << get_repr(termo) << std::endl;
	}
	else
	{
	//	std::cout << "   " << predicate->repr() << " !! " << get_repr(termo) << std::endl;
	}
	if (has_match )
	{

		return makeMatch(predicate->named, convertToTerm(termo));
	}


	return MatchResult();
}

MatchResult CMatch_i(MTermSetCombinatoria& termos, std::vector<HPred> predicates)
{
	size_t n = predicates.size();
	if (termos.size() != n)
	{
		return MatchResult();
	}
	MatchResult mm;
	mm.result = Equals; // inicia com tudo OK
	for (size_t i = 0; i < n; ++i)
	{
		MatchResult mj = CMatch_j(termos[i], predicates[i]);		 
		if (mj.result != Equals) return MatchResult();
		mm.insert(mj);
	}
	return mm;
}

 



MatchResult CMatch(std::vector<HTerm> lst, std::vector<HPred> predicates)
{
	size_t npred = predicates.size();
	MTermSetCombinatoriaList comb = getCombinatorias(lst, npred);
	for (auto it = comb.begin(); it != comb.end(); ++it)
	{
		//std::cout <<  std::endl;
		MatchResult mm = CMatch_i(*it, predicates);
		if (mm.result == Equals)
		{
			return mm;
		}
	}
	return MatchResult();
}

MatchResult CMatch(HTerm term, std::vector<HPred> predicates)
{
	if(predicates.size() ==1  )
	{
		if (predicates.front()->match(term) == Equals)
		{
			return makeMatch(predicates.front()->named,  term);
		}
		return  MatchResult();
	}



	CList* lst = dynamic_cast<CList* >(term.get());
	if (lst != nullptr)
	{		 
		return CMatch(lst->asVector() , predicates ); // trata como uma lista
	}
	return MatchResult();;
}


std::string get_repr(MatchResult r)
{
	std::string s;
	for (auto kv = r.matchs.begin(); kv != r.matchs.end(); ++kv)
	{
		s += kv->first + ":";
		s += kv->second->repr();
		s += "\n";
	}
	return s;
};

