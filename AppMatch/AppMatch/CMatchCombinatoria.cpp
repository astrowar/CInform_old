// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CBase.hpp"
#include <vector>
#include "CMatch.hpp"

#include <memory>
#include <functional>
#include "CMatchListValid.hpp"

using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

namespace NSTerm {
	namespace NSMatch {

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
				uniq.push_back({ MTermSet({*it}) });
			}
			return MTermSetCombinatoriaList({ uniq });
		}

		//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
		MTermSetCombinatoriaList getCombinatoriasGroup(const std::vector<HTerm> & terms) {
			return MTermSetCombinatoriaList({ MTermSetCombinatoria({terms}) });
		}



		MTermSetCombinatoriaList getCombinatoriasRec(std::vector<HTerm>& terms, size_t n) //num termos que restam
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

		MTermSetCombinatoria getUnicCombination(std::vector<HTerm>& lst) {
			MTermSetCombinatoria comb;
			for (auto it = lst.begin(); it != lst.end(); ++it) {
				comb.push_back({ *it });
			}
			return comb;
		}

		MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm>& lst, size_t n) {
			if (lst.size() < n) {
				return MTermSetCombinatoriaList(); // impossivel ..
			}
			if (lst.size() == n) {

				return MTermSetCombinatoriaList({ getUnicCombination(lst) }); // apenas uma combinacao eh possivel
			}
			return getCombinatoriasRec(lst, n);
		}


		//cada termo eh um MTermSet
		bool applyCombinatoriasUnitary(MTermSetCombinatoria &partial_in, std::vector<HTerm>& terms, FuncCombinatoria &func) {
			MTermSetCombinatoria uniq(partial_in.begin(), partial_in.end());
			for (auto it = terms.begin(); it != terms.end(); ++it) {
				if (!isListValid(uniq)) return false;
				uniq.push_back({ MTermSet({*it}) });
			}
			return func(uniq);
		}


		bool applyCombinatoriasUnitary_range(MTermSetCombinatoria &partial_in, std::vector<HTerm>::iterator terms_begin, std::vector<HTerm>::iterator terms_end, FuncCombinatoria &func) {
			MTermSetCombinatoria uniq(partial_in.begin(), partial_in.end());
			for (auto it = terms_begin; it != terms_end; ++it) {
				if (!isListValid(uniq)) return false;
				uniq.push_back({ MTermSet({ *it }) });
			}
			return func(uniq);
		}

		//todos os termos formam um MTermSet que forma um MTermSetCombinatoria que forma um MTermSetCombinatoriaList 
		bool applyCombinatoriasGroup(MTermSetCombinatoria &partial_in, std::vector<HTerm>& terms, FuncCombinatoria &func) {
			if (!isListValid(terms)) return false;
			partial_in.push_back(terms);
			bool hasFound = func(partial_in);
			partial_in.pop_back();
			return hasFound;
		}

		bool applyCombinatoriasRec(MTermSetCombinatoria &partial_in, std::vector<HTerm>& terms, size_t n,
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

		void applyCombinatorias(std::vector<HTerm>& lst, size_t n, FuncCombinatoria &func) {

			if (lst.size() < n) {
				return; // impossivel ..
			}

			if (lst.size() == n) {

				MTermSetCombinatoria unip = { getUnicCombination(lst) };
				func(unip); // apenas uma combinacao eh possivel
				return;
			}
			MTermSetCombinatoria partial;
			applyCombinatoriasRec(partial, lst, n, func);
		}

		//======================================================================


		bool
			applyCombinatoriasGroupSmart(MTermSetCombinatoria &partial_in, std::vector<HTerm>& terms, std::vector<CPred *> &preds,
				int pos, FuncCombinatoria &func) {
			if (preds[pos]->match(terms) != EqualResulting::NotEquals) {
				if (!isListValid(terms)) return false;
				partial_in.push_back(terms);
				bool hasFound = func(partial_in);
				partial_in.pop_back();
				return hasFound;
			}
			return false;
		}




		bool applyCombinatoriasRecSmart(MTermSetCombinatoria &partial_in, std::vector<HTerm>& terms, size_t n,
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

			for (size_t j = 1; j <= lsize - n + 1; ++j) {
				MTermSet head(terms.begin(), terms.begin() + j);
				if (preds[pos]->match(head) != EqualResulting::NotEquals) {
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


		bool applyCombinatoriasRecSmart_range(MTermSetCombinatoria &partial_in, std::vector<HTerm>::iterator terms_begin, std::vector<HTerm>::iterator terms_end, size_t n,
			std::vector<CPred *> &preds, int pos, FuncCombinatoria &func) //num termos que restam
		{

			if (n == 1) {
				auto vterm = std::vector<HTerm>(terms_begin, terms_end);
				return applyCombinatoriasGroup(partial_in, vterm, func); // apenas uma combinacao eh possivel

			}
			size_t lsize = (terms_end - terms_begin);
			if (n == lsize) {

				return applyCombinatoriasUnitary_range(partial_in, terms_begin, terms_end, func); //Agiliza o processamento

			}

			MTermSetCombinatoria partial = partial_in;//copy

													  //particiona de 1 a (n-1)

			for (size_t j = 1; j <= lsize - n + 1; ++j) {

				if (preds[pos]->match(terms_begin, terms_begin + j) != EqualResulting::NotEquals) {
					if (isListValid_range(terms_begin, terms_begin + j))
					{
						std::vector<HTerm>::iterator tail_begin = terms_begin + j;
						std::vector<HTerm>::iterator tail_end = terms_end;

						//MTermSet head(terms_begin, terms_begin + j);
						partial.push_back(MTermSet(terms_begin, terms_begin + j));
						bool hasFound = false;
						if (n > 2) hasFound = applyCombinatoriasRecSmart_range(partial, tail_begin, tail_end, n - 1, preds, pos + 1, func);
						else if (n == 2)
						{
							auto vtail = std::vector<HTerm>(tail_begin, tail_end);
							hasFound = applyCombinatoriasGroupSmart(partial, vtail, preds, pos + 1, func);
						}
						partial.pop_back();
						if (hasFound) {
							return true;
						}
					}
				}
			}
			return false;

		}




		void applyCombinatorias_smart(std::vector<HTerm>& lst, size_t n, std::vector<CPred *> preds, FuncCombinatoria &func)
		{

			if (lst.size() < n) {
				return; // impossivel ..
			}

			if (lst.size() == n) {

				MTermSetCombinatoria unip = { getUnicCombination(lst) };
				func(unip); // apenas uma combinacao eh possivel
				return;
			}
			MTermSetCombinatoria partial;
			//applyCombinatoriasRecSmart(partial, lst, n, preds, 0, func);
			applyCombinatoriasRecSmart_range(partial, lst.begin(), lst.end(), n, preds, 0, func);
		}

		MatchResult CMatch_j(MTermSet &termo, CPred *predicate) {
#ifdef CMLOG
			std::cout << "Query|   " << predicate->repr() << " >> " << get_repr(termo);
#endif
			bool has_match = (predicate->match(termo) == EqualResulting::Equals);

#ifdef CMLOG
			if (has_match) {
				std::cout << "   TRUE" << std::endl;
			}
			else {
				std::cout << "   FALSE" << std::endl;
			}
#endif
			if (has_match) {

				return makeMatch(predicate->named, convertToTerm(termo));
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
				// inicia com tudo OK
				for (size_t i = 0; i < tn; ++i) {
					CPred *term_i = predicates_ptr[i];
					if (CPredAtom *v = asPredAtom(term_i)) {

						MTermSet &termGroup = combinacao[i];
						MatchResult mj = CMatch_j(termGroup, term_i);
						if (mj.result != EqualResulting::Equals) {
							return MatchResult();
						}
					}

				}

			}

			//All Others
			{
				MatchResult mm;
				mm.result = EqualResulting::Equals; // inicia com tudo OK
				for (size_t i = 0; i < tn; ++i) {
					CPred *term_i = predicates_ptr[i];

					MTermSet &termGroup = combinacao[i];
					MatchResult mj = CMatch_j(termGroup, term_i);
					if (mj.result != EqualResulting::Equals) {
						return MatchResult();
					}
					mm.insert(mj);
				}
				return mm;
			}

		}


		void applyCombinatorias_smart_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend, size_t n, std::vector<CPred *> preds, FuncCombinatoria &func)
		{
			size_t isize = abs(vend - vbegin);

			if (isize < n)
			{
				return; // impossivel ..
			}

			if (isize == n) {

				auto vv = (std::vector<HTerm>(vbegin, vend));
				MTermSetCombinatoria unip = { getUnicCombination(vv) };
				func(unip); // apenas uma combinacao eh possivel
				return;
			}
			MTermSetCombinatoria partial;
			//applyCombinatoriasRecSmart(partial, lst, n, preds, 0, func);
			applyCombinatoriasRecSmart_range(partial, vbegin, vend, n, preds, 0, func);
		}

	}
}