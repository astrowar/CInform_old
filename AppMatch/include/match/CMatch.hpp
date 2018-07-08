#pragma once
#ifndef _CMATCH_H
#define _CMATCH_H

#include "base/CBase.hpp"

#include "base/EqualsResult.hpp"
#include <functional>
#include <vector>
#include <map>

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

			virtual EqualResulting::EqualsResul match(MTermSet &h) = 0;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) = 0;

			virtual EqualResulting::EqualsResul match(HTerm h) = 0;

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

			virtual EqualResulting::EqualsResul match(MTermSet &_h) override;

			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;

			virtual EqualResulting::EqualsResul match(HTerm h) override;
		};

		class CPredList : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredList; }

			std::vector<HPred> plist;

			CPredList(std::string _named, std::initializer_list<HPred> plist);

			virtual EqualResulting::EqualsResul match(MTermSet &_h) override;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualResulting::EqualsResul match(HTerm h) override;
		};

		class CPredAny : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredAny; }

			CPredAny(std::string _named);;

			virtual EqualResulting::EqualsResul match(MTermSet &_h) override;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualResulting::EqualsResul match(HTerm h) override;
		};

		class CPredWord : public CPred {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredWord; }

			CPredWord(std::string _named);;

			virtual EqualResulting::EqualsResul match(MTermSet &_h) override;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualResulting::EqualsResul match(HTerm h) override;
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

			virtual EqualResulting::EqualsResul match(MTermSet &h) override;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualResulting::EqualsResul match(HTerm h) override;

			CPredBooleanAnd(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		public:
			HPred b1, b2;
		};

		class CPredBooleanOr : public CPredBoolean {
		public:
			bool isSame(HTerm b) override;

			std::string repr() override;
			virtual TermType type() override { return TermType::PredBooleanOr; }

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2,	const HPred &c_pred3);

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2);

			CPredBooleanOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

			CPredBooleanOr(const std::string &_named, std::list<HPred> plist);

			virtual EqualResulting::EqualsResul match(MTermSet &h) override;
			virtual EqualResulting::EqualsResul match(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend) override;
			virtual EqualResulting::EqualsResul match(HTerm h) override;

		public:
			std::vector<HPred> blist;
		};


		bool isSamePred(std::vector<HPred> a, std::vector<HPred> b); 

		//==========================================

		//make hPreds
		HPred pAtom(std::string _named, HTerm atom);

		HPred pList(std::string _named, std::initializer_list<HPred> plist);
		HPred pList(std::initializer_list<HPred> plist);

		HPred pAny(std::string _named);

		HPred pWord(std::string _named);

		HPred pAnd(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		HPred pOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1);

		HPred pOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2);

		HPred pOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2,	const HPred &c_pred3);
		HPred pOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2, const HPred &c_pred3, const HPred &c_pred4 );
		HPred pOr(const std::string &_named, const HPred &c_pred, const HPred &c_pred1, const HPred &c_pred2, const HPred &c_pred3,const HPred &c_pred4, const HPred &c_pred5 );


		HPred  pPreposition(const std::string &_named);

		CPredAtom* asPredAtom(CTerm* c);
		CPredList* asPredList(CTerm* c);
		CPredAny* asPredAny(CTerm* c);
		CPredWord * asPredWord(CTerm* c);
		HTerm convertToTerm(MTermSet &m);





		//Classe que representa um conjunto de termos da Grmatica
		class CPredSequence
		{
		public:
			CPredSequence(std::vector<HPred> x) : data(std::move(x)) {}
			CPredSequence(HPred x) : data({ x }) {}
			std::vector<HPred> data;
		};

		using HTermSequence = std::shared_ptr<CPredSequence>;

		CPredSequence operator<<(HPred a, HPred b);		 
		CPredSequence operator<<(CPredSequence a, HPred b);
		CPredSequence operator<<(CPredSequence a, CPredSequence& b);
		 

		 






		namespace NSMatch
		{
			//==========================================
			class MatchResult {
			public:
				MatchResult() : result(EqualResulting::Undefined) {
				}

				std::map<std::string, HTerm> matchs;
				EqualResulting::EqualsResul result;

				void setValue(std::string named, HTerm value);

				HTerm getValue(std::string named);

				void insert(MatchResult &other);
			};


			MatchResult makeMatch(std::string named, HTerm value);
			MatchResult CMatch__(std::vector<HTerm>&   lst, const std::vector<HPred> &predicates);
			//MatchResult CMatch(std::vector<HTerm>& lst, std::vector<HPred> predicates);
			MatchResult CMatch__(HTerm term, const std::vector<HPred>& predicates);
			MatchResult  CMatch(std::vector<HTerm>&  seq, const CPredSequence   &predicates);
			MatchResult  CMatch(HTerm  seq, const CPredSequence   &predicates);
			std::string get_repr(MatchResult r);




		}
}

#endif

