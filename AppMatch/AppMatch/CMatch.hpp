#pragma once
#ifndef _CMATCH_H
#define _CMATCH_H

#include "CBase.hpp"
#include <vector>
#include <map>
#include "EqualsResult.hpp"
#include <functional>

namespace NSTerm
{
	 

		using MTermSet = std::vector<HTerm>;
		using MTermSetCombinatoria = std::vector<MTermSet>;
		using MTermSetCombinatoriaList = std::vector<MTermSetCombinatoria>;

		MTermSetCombinatoriaList getCombinatorias(std::vector<HTerm>& lst, size_t n);

		using FuncCombinatoria = std::function<bool(MTermSetCombinatoria &)>; //true == (please, stop)

		void applyCombinatorias(std::vector<HTerm>& lst, size_t n, FuncCombinatoria &func);

		std::string get_repr(MTermSetCombinatoriaList lst);

		std::string get_repr(MTermSetCombinatoria lst);

		//predicado do match
		//predicado pode ser: 
		//      um Atom que deve ser Equal
		//      um comparador que deve resultar em EqualsResul quando executado
		//      um Any que pode ser qualquer coisa
		class CPred : public CAtom {
		public:
			std::string repr() override;
			//virtual TermType type() override { return TermType::Pred; }

			std::string named;

			CPred(std::string _named) : named(std::move(_named)) 
			{
			};

			virtual EqualsResul match(MTermSet &h) = 0;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) = 0;

			virtual EqualsResul match(HTerm h) = 0;

			virtual bool isSame(HTerm b) = 0;

		};

		using HPred = std::shared_ptr<CPred>;

		class CPredAtom : public CPred {
		public:
			bool isSame(HTerm b) override;

			HTerm h;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredAtom; }

			CPredAtom(std::string _named, HTerm atom);

			virtual EqualsResul match(MTermSet &_h) override;

			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;

			virtual EqualsResul match(HTerm h) override;
		};

		class CPredList : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredList; }

			std::vector<HPred> plist;

			CPredList(std::string _named, std::initializer_list<HPred> plist);

			virtual EqualsResul match(MTermSet &_h) override;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualsResul match(HTerm h) override;
		};

		class CPredAny : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredAny; }

			CPredAny(std::string _named);;

			virtual EqualsResul match(MTermSet &_h) override;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualsResul match(HTerm h) override;
		};

		class CPredWord : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredWord; }

			CPredWord(std::string _named);;

			virtual EqualsResul match(MTermSet &_h) override;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualsResul match(HTerm h) override;
		};

		class CPredBoolean : public CPred {
		public:
			CPredBoolean(const std::string &_named);
		};

		class CPredBooleanAnd : public CPredBoolean {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredBooleanAnd; }

			virtual EqualsResul match(MTermSet &h) override;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualsResul match(HTerm h) override;

			CPredBooleanAnd(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		public:
			HPred b1, b2;
		};

		class CPredBooleanOr : public CPredBoolean {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredBooleanOr; }

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2,
				const HPred &c_pred3);

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2);

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

			CPredBooleanOr(const std::string &_named, std::list<HPred> plist);

			virtual EqualsResul match(MTermSet &h) override;
			virtual EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualsResul match(HTerm h) override;

		public:
			std::vector<HPred> blist;
		};


		bool isSamePred(std::vector<HPred> a, std::vector<HPred> b); 

		//==========================================

		//make hPreds
		HPred mkHPredAtom(std::string _named, HTerm atom);

		HPred mkHPredList(std::string _named, std::initializer_list<HPred> plist);

		HPred mkHPredAny(std::string _named);

		HPred mkHPredWord(std::string _named);

		HPred mkHPredBooleanAnd(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2);

		HPred mkHPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2,
			const HPred &c_pred3);

		CPredAtom* asPredAtom(CTerm* c);
		CPredList* asPredList(CTerm* c);
		CPredAny* asPredAny(CTerm* c);
		CPredWord * asPredWord(CTerm* c);
		HTerm convertToTerm(MTermSet &m);

		namespace NSMatch
		{
			//==========================================
			class MatchResult {
			public:
				MatchResult() : result(Undefined) {
				}

				std::map<std::string, HTerm> matchs;
				EqualsResul result;

				void setValue(std::string named, HTerm value);

				HTerm getValue(std::string named);

				void insert(MatchResult &other);
			};


			MatchResult makeMatch(std::string named, HTerm value);
			MatchResult CMatch(std::vector<HTerm>&   lst, const std::vector<HPred> &predicates);
			//MatchResult CMatch(std::vector<HTerm>& lst, std::vector<HPred> predicates);
			MatchResult CMatch(HTerm term, const std::vector<HPred>& predicates);
			std::string get_repr(MatchResult r);




		}
}

#endif

