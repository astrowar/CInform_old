
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


MTermSetCombinatoriaList getCombinatoriasRec(std::vector<HTerm> terms, int n ) //num termos que restam
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
	for(int j = 1 ; j<= lsize - n +1  ;++j)
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


MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm> lst, int n)
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

CPredAtom::CPredAtom(std::string _named, HTerm atom): CPred(_named), h(atom)
{
}

EqualsResul CPredAtom::match(HTerm _h) 
{
	return equals(this->h.get(), _h.get());
}

CPredAny::CPredAny(std::string _named): CPred(_named)
{}

EqualsResul CPredAny::match(HTerm _h)
{
	return Equals;
}

CPredBoolean::CPredBoolean(const std::string& _named): CPred(_named)
{
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

EqualsResul CMatch(std::vector<HTerm> lst , std::vector<HPred> precadtes )
{

	return Undefined;
};
