#include "CBase.h"
#include <vector>
#include "CMatch.h"
std::string get_repr(MTermSet lst)
{
	std::string q;
	q += " [ ";
	for (auto tr = lst.begin(); tr != lst.end(); ++tr)
	{
		q += tr->get()->repr() + " , ";
	}
	q += " ] ";
	return q;
}
//Obtem uma lista de M termos e quebra ela em Combinacoes de Sets de tamanho N
MTermSetCombinatoria cons(MTermSet &head, MTermSetCombinatoria &tail)
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
MTermSetCombinatoriaList getCombinatoriasUnitary(std::vector<HTerm> terms )
{
	MTermSetCombinatoria uniq;
	for (auto it = terms.begin(); it != terms.end(); ++it)
	{
		uniq.push_back({ MTermSet({ *it }) });	 
	}
	return MTermSetCombinatoriaList({ uniq });
}
//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
MTermSetCombinatoriaList getCombinatoriasGroup(std::vector<HTerm> terms)
{
	return MTermSetCombinatoriaList({ MTermSetCombinatoria({ terms }) });
}
MTermSetCombinatoriaList getCombinatoriasRec(std::vector<HTerm> terms, size_t n ) //num termos que restam
{
	if (n == 1)   
	{
		return getCombinatoriasGroup(terms);  // apenas uma combinacao eh possivel 
	}
	int lsize = terms.size();
	if (n == lsize)
	{
		return getCombinatoriasUnitary(terms); //Agiliza o processamento
	}
	//particiona de 1 a (n-1)
	MTermSetCombinatoriaList accTerms;
	for(size_t j = 1 ; j<= lsize - n +1  ;++j)
	{
		MTermSet  head(terms.begin() , terms.begin()  + j );		 
		std::vector<HTerm>  tail(terms.begin()+j, terms.end());
		auto tails = getCombinatoriasRec(tail, n - 1); 
		for (auto c = tails.begin(); c != tails.end(); ++c)
		{
			MTermSetCombinatoria  fullSet = cons(head, *c);
			accTerms.push_back(fullSet);
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
		return MTermSetCombinatoriaList({ MTermSetCombinatoria({ lst }) }); // apenas uma combinacao eh possivel 
	}
	return getCombinatoriasRec(lst, n);
}
std::string get_repr(MTermSetCombinatoriaList lst )
{
	std::string q = "{ ";
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		for (auto tt = it->begin(); tt != it->end(); ++tt)
		{
			q += " [ ";
			for (auto tr = tt->begin(); tr != tt->end(); ++tr)
			{
				q += tr->get()->repr() + " , ";
			}
			q += " ] ";
		}
		q += "\n";
	}
	q += "}";
	return q;
}
std::string CPred::repr()
{
	return "Pred";
}
CPredAtom::CPredAtom(std::string _named, HTerm atom): CPred(_named), h(atom)
{
}
EqualsResul CPredAtom::match(MTermSet _h)
{
	if (_h.size() != 1) return NotEquals;
	return equals(this->h.get(), _h[0].get() );
}
CPredList::CPredList(std::string _named, std::initializer_list<HPred> _plist):CPred(_named), plist(_plist)
{
}
EqualsResul CPredList::match(MTermSet _h)
{
	if (_h.size() != plist.size()) return NotEquals;
	int n = plist.size();
	for(int j =0 ; j> n;++j)
	{
		if (equals(this->plist[j].get() , _h[j].get()) != Equals)
		{
			return NotEquals;
		}
	}
	return Equals;
}
CPredAny::CPredAny(std::string _named): CPred(_named)
{}
EqualsResul CPredAny::match(MTermSet _h)
{
	return Equals;
}
CPredBoolean::CPredBoolean(const std::string& _named): CPred(_named)
{
}
EqualsResul CPredBooleanAnd::match(MTermSet h)
{
	if ((this->b1->match(h) == Equals) && (this->b2->match(h) == Equals)) return Equals;
	return NotEquals;
}
CPredBooleanAnd::CPredBooleanAnd(const std::string& _named, const HPred& c_pred, const HPred& c_pred1): CPredBoolean(_named),
                                                                                                        b1(c_pred),
                                                                                                        b2(c_pred1)
{
}
CPredBooleanOr::CPredBooleanOr(const std::string& _named, const HPred& c_pred, const HPred& c_pred1): CPredBoolean(_named),
                                                                                                      b1(c_pred),
                                                                                                      b2(c_pred1)
{
}
EqualsResul CPredBooleanOr::match(MTermSet h)
{
	if ((this->b1->match(h) == Equals) || (this->b2->match(h) == Equals)) return Equals;
	return NotEquals;
}
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
	for(auto kv = other.matchs.begin() ; kv!= other.matchs.end();++kv)
	{
		this->setValue(kv->first, kv->second);
	}
}
HTerm  convertToTerm( MTermSet m)
{
	if (m.size() == 1 )
	{
		return m[0];
	}
	else
	{
		CList *lst_ptr = new CList(  );
		lst_ptr->lst.insert(lst_ptr->lst.end(), m.begin(), m.end());
		return   HTerm(lst_ptr);		
	}
}
MatchResult makeMatch(std::string named, HTerm value)
{
	MatchResult m;
	m.result = Equals;
	m.setValue(named, value);
	return m;
}
MatchResult CMatch_j(MTermSet  termo,  HPred  predicate)
{
		if (predicate->match( termo ))
		{
			return makeMatch(predicate->named, convertToTerm( termo) );
		}
	return MatchResult();
}
MatchResult CMatch_i(MTermSetCombinatoria &termos, std::vector<HPred> predicates)
{
	int n = predicates.size();
	if (termos.size() != n)
	{
		return MatchResult();
	}
	MatchResult mm;
	mm.result = Equals; // inicia com tudo OK
	for (auto i = 0; i < n; ++i)
	{
		MatchResult mj =  CMatch_j( termos[i],  predicates[i]);
		if (mj.result != Equals ) return MatchResult();
		mm.insert(mj);
	}
	return mm;
}
MatchResult CMatch(std::vector<HTerm> lst , std::vector<HPred> predicates )
{
	int npred = predicates.size();
	MTermSetCombinatoriaList comb =  getCombinatorias(lst, npred);
	for (auto it = comb.begin(); it != comb.end(); ++it)
	{
		MatchResult mm = CMatch_i(*it, predicates);
		if (mm.result == Equals )
		{
			return mm;
		}
	}
	return MatchResult();
}
std::string get_repr(MatchResult r)
{
	std::string s;
	for (auto kv = r.matchs.begin(); kv != r.matchs.end(); ++kv)
	{
		s += kv->first + ":";
		s +=  kv->second->repr();
		s += "\n";
	}
	return s;
};
