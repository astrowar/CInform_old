// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "parser/Parser.hpp"
#include <sharedCast.hpp>
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


#include <algorithm>


bool is_backet_balanced(std::vector<HTerm> terms)
{
	int k = 0;
	for (auto x : terms)
	{
		if (x->is_openBracket())  k++;
		if (x->is_closeBracket())  k--;
		if (k < 0) return false;
	}
	return (k == 0);
}


bool is_full_bracket(std::vector<HTerm> term)
{ 
	 
	{
		HTerm h1 = term.front();
		HTerm h2 = term.back();
		if (h1->is_openBracket())
			if (h2->is_closeBracket())
			{
				int m = 0;
				for (auto x : term)
				{
					if (x->is_closeBracket() || x->is_openBracket()) m++;
				}
				//count open and close 

				if ((m == 2)) return true;
			}
	}

	return false;

}

bool is_full_bracket(HTerm term)
{
	auto clist = asCList(term.get());
	if (clist != nullptr)
	{
		HTerm h1 = clist->lst.front();
		HTerm h2 = clist->lst.back();
		if(h1->is_openBracket())
			if (h2->is_closeBracket())
			{
				int m = 0;
				for (auto x : clist->lst)
				{
					if (x->is_closeBracket() || x->is_openBracket()) m ++;
				}
				//count open and close 
				
				if ((m == 2)) return true;
			}
	}

	return false;
}

HBlockMatch NSParser::ExpressionMatch::parser_MatchArgument_kind_item(CParser *p , string sNoum)
{
	if (sNoum == "text")
	{
		return std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text"));
	}

	if (sNoum == "number")
	{
		return std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("number"));
	}

	auto c1 = parser_expression_match_noum(p, make_string(sNoum));
	 
	return c1;
}


HBlockMatchKind NSParser::ExpressionMatch::parser_MatchKind(CParser *p, HTerm term)
{
	//compose kind ?

	CPredSequence predList = pLiteral("relation") << pLiteral("of") << pAny("var_named1") << pLiteral("by") << pAny("var_named2");
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		return std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>("relation")));
	}
	return nullptr;
}



//componente eh um noum OU uma variavel
HBlockMatch NSParser::ExpressionMatch::parser_MatchComponentePhase(CParser *p, HTerm term)
{

	auto arg_only = parser_MatchArgument_only(p, term);

	if (arg_only != nullptr) return arg_only;


	if (false)
	{

		{
			CPredSequence predList = pAny("ListKind") << pLiteral("called") << pAny("var_named");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{

				//is compose type ?
				HBlockMatch mcompose = parser_MatchKind(p, res.matchs["var_named"]);
				if (mcompose != nullptr) return mcompose;

				CTerm* cterm = res.matchs["ListKind"]->removeArticle();
				//cterm eh uma lista ??
				if (CList* clist = asCList(cterm))
				{
					HBlockMatchAND mmlist = std::make_shared<CBlockMatchAND>(std::list<HBlockMatch>());
					for (auto &ci : clist->lst)
					{
						string  str_i = ci->removeArticle()->repr();
						HBlockMatch mi = parser_MatchArgument_kind_item(p, str_i);
						mmlist->matchList.push_back(mi);
					}
					HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->removeArticle()->repr(), mmlist);
					return n1;
				}
			}
		}
		{
			CPredSequence predList = pAny("kind") << pLiteral("called") << pAny("var_named");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());
				auto noum_var_named = parse_match_SigleNoum(p, res.matchs["var_named"]);
				if (noum_var_named != nullptr)
				{
					HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(noum_var_named->inner->named(), c1);
					return n1;
				}
			}
		}

		{
			CPredSequence predList = pAny("kind") << pLiteral("-") << pAny("var_named");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) {
				HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
				return n1;
			}
		}
	}
	{
		CPredSequence predList = pWord("var_named");

		auto tList = asCList(term.get());
		if (tList == nullptr)
		{
			
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			 
			string a = res.matchs["var_named"]->removeArticle()->repr();
			if (a.size() == 1)
			{
				if (isalpha(a[0]))
				{
					if (toupper(a[0]) == a[0])
					{
						return  std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), std::make_shared<CBlockMatchAny>());
					}
				}
			}
		}
	}



	{
		
		HBlockMatchNoum c1 = parser_expression_match_noum(p, term);
		if (c1 != nullptr)
		{

			if (c1->inner->named().find('/') != string::npos)
			{
				//matchs OR

				auto vstr = split_string(c1->inner->named(), "/");
				std::list<HBlockMatch> or_list;
				for (auto v : vstr)
				{
					HBlockMatchNoum ci = parser_expression_match_noum(p, make_string(v));
					if (ci == nullptr) return nullptr;
					or_list.push_back(ci);
				}
				return std::make_shared<CBlockMatchOR>(or_list);
			}

			return c1;
		}
		
	}


	return nullptr;

}


 


HBlockMatch NSParser::ExpressionMatch::parser_MatchVariableDeclare(CParser *p, HTerm term)
{

	{
		CPredSequence predList = pAny("ListKind") << pLiteral("called") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CTerm* cterm = res.matchs["ListKind"]->removeArticle();
			//cterm eh uma lista ??
			if (CList* clist = asCList(cterm))
			{
				HBlockMatchAND mmlist = std::make_shared<CBlockMatchAND>(std::list<HBlockMatch>());
				for (auto &ci : clist->lst)
				{
					string  str_i = ci->removeArticle()->repr();

					HBlockMatch mi = parser_MatchArgument_kind_item(p, str_i);

					mmlist->matchList.push_back(mi);
				}
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->removeArticle()->repr(), mmlist);
				return n1;
			}
		}
	}
	{
		CPredSequence predList = pAny("kind") << pLiteral("called") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {


			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			auto noum_var_named = parse_match_SigleNoum(p, res.matchs["var_named"]);
			if (noum_var_named != nullptr)
			{
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(noum_var_named->inner->named(), c1);
				return n1;
			}
		}
	}

	{
		CPredSequence predList = pAny("kind") << pLiteral("-") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			HBlockNoum var_noum = Expression::parser_noum_expression(p, res.matchs["var_named"]);
			if (var_noum != nullptr)
			{
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(var_noum->named(), c1);
				return n1;
			}
		}
	}
	return nullptr;

}

HBlockMatch NSParser::ExpressionMatch::parser_MatchArgument_only(CParser *p, HTerm term)
{
	{
		CPredSequence predList = pAny("ListKind") << pLiteral("called") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CTerm* cterm = res.matchs["ListKind"]->removeArticle();
			//cterm eh uma lista ??
			if (CList* clist = asCList(cterm))
			{
				HBlockMatchAND mmlist = std::make_shared<CBlockMatchAND>(std::list<HBlockMatch>());
				for (auto &ci : clist->lst)
				{
					string  str_i = ci->removeArticle()->repr();

					HBlockMatch mi = parser_MatchArgument_kind_item(p, str_i);

					mmlist->matchList.push_back(mi);
				}
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->removeArticle()->repr(), mmlist);
				return n1;
			}
		}
	}


	{
		CPredSequence predList = pAny("kind") << pLiteral("called") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {


			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			auto noum_var_named = parse_match_SigleNoum(p, res.matchs["var_named"]);
			if (noum_var_named != nullptr)
			{
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(noum_var_named->inner->named(), c1);
				return n1;
			}
		}
	}

	{
		CPredSequence predList = pAny("kind") << pLiteral("-") << pAny("var_named");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}
	}



	return nullptr;
}

HBlockMatch NSParser::ExpressionMatch::parser_MatchArgument(CParser *p, HTerm term)
{

	{
		CPredSequence predList = pAny("PropName") << pLiteral("of") << pAny("Object");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			 		

			HBlockMatch c1 = parser_expression_match_noum(p, res.matchs["PropName"]);
			if (c1 != nullptr)
			{
				HBlockMatch c2 = parser_MatchArgument(p, res.matchs["Object"]);
				if (c2 != nullptr)
				{
					return  std::make_shared<CBlockMatchProperty>(c1, c2);
				}
			}
		}
	}



	{
		  CPredSequence predList = pAny("ListKind")	<<pLiteral("called")<<pAny("var_named");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CTerm* cterm = res.matchs["ListKind"]->removeArticle();
			//cterm eh uma lista ??
			if (CList* clist = asCList(cterm))
			{
				HBlockMatchAND mmlist = std::make_shared<CBlockMatchAND>(std::list<HBlockMatch>());
				for (auto &ci : clist->lst)
				{
					string  str_i = ci->removeArticle()->repr();
					 
					HBlockMatch mi = parser_MatchArgument_kind_item(p, str_i);

					mmlist->matchList.push_back(mi);
				}
				 	HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->removeArticle()->repr(), mmlist);
				return n1;
			}
		}
	}


	{
		  CPredSequence predList =  pAny("kind")<<pLiteral("called")	<<pAny("var_named");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {


		 	HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			auto noum_var_named =  parse_match_SigleNoum(p, res.matchs["var_named"]);
			if (noum_var_named != nullptr)
			{
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(noum_var_named->inner->named() , c1);
				return n1;
			}
		}
	}

	{
		CPredSequence predList = pAny("kind")	<<pLiteral("-")	<<pAny("var_named");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
		 
			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}
	}


	{
		CPredSequence predList = pLiteral("(") << pWord("VAR") << pLiteral(")");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			string str = res.matchs["VAR"]->repr();
			if (isupper(str[0]) && str.size() < 2)
			{
				HBlockMatch c1 = std::make_shared<CBlockMatchAny>();
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(str, c1);
				return n1;
			}
		}
	}


	//remove artigos
	{
		CPredSequence predList = undefinedArticle() << pWord("W1")  ;

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			auto w1 = parser_MatchArgument(p, res.matchs["W1"]);
			if (w1 != nullptr)
			{
				return w1;
			}
		}
	}


	{
		CPredSequence predList = pWord("W1") << pAny("W2") << pAny("W3") << pAny("W4");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			auto w1 = parser_MatchArgument(p, res.matchs["W1"]);
			if (w1 != nullptr)
			{
				auto w2 = parser_MatchArgument(p, res.matchs["W2"]);
				if (w2 != nullptr)
				{
					auto w3 = parser_MatchArgument(p, res.matchs["W3"]);
					if (w3 != nullptr)
					{
						auto w4 = parser_MatchArgument(p, res.matchs["W4"]);
						if (w4 != nullptr)
						{
							return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ w1, w2, w3 , w4 }));
						}
					}
				}
			}
		}
	}


	{
		CPredSequence predList = pWord("W1") << pAny("W2") << pAny("W3");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			auto w1 = parser_MatchArgument(p, res.matchs["W1"]);
			if (w1 != nullptr)
			{
				auto w2 = parser_MatchArgument(p, res.matchs["W2"]);
				if (w2 != nullptr)
				{
					auto w3 = parser_MatchArgument(p, res.matchs["W3"]);
					if (w3 != nullptr)
					{
						return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>( { w1, w2, w3 }));
					}
				}
			}
		}
	}

	{
		CPredSequence predList = pWord("W1") <<  pAny("W2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			auto w1 = parser_MatchArgument(p, res.matchs["W1"]);
			if (w1 != nullptr)
			{
				auto w2 = parser_MatchArgument(p, res.matchs["W2"]);
				if (w2 != nullptr)
				{
					 
					 
					{
						return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ w1, w2  }));
					}
				}
			}
		}
	}





	//std::cout << "Argument:  " <<  (term)->repr() << std::endl;
	string sNoum =  CtoString(expandBract(term)->removeArticle());
	if (sNoum == "not")
	{
		return nullptr;
	}


	 
	if (isupper(sNoum[0]) && sNoum.size() < 2)
	{
		HBlockMatch c1 = std::make_shared<CBlockMatchAny>();
		HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(sNoum, c1);
		return n1;
	}

	return parser_expression_match_noum(p, term);	
	 
}



HBlockMatch NSParser::ExpressionMatch::parser_MatchArgument(CParser *p, std::vector<HTerm>&  term)
{
	{
		static CPredSequence predList = pAny("kind")	<<pLiteral("called")	<<pAny("var_named");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlockMatch c1 = parser_MatchArgument_kind_item(p, res.matchs["kind"]->removeArticle()->repr());

			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}
	}

	{
		CPredSequence predList = pAny("kind") << pLiteral("-") <<  pAny("var_named");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlockMatch c1 = parser_MatchArgument_kind_item(p, CtoString(expandBract(res.matchs["kind"])));
			if (c1 != nullptr)
			{
				auto sNoum = CtoString(expandBract(res.matchs["var_named"]));
				//auto snoum = Expression::parser_noum_expression(p, res.matchs["var_named"]);

				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(sNoum, c1);
				return n1;
			}
		}
	}


	return nullptr;
}




HBlockMatchIs NSParser::ExpressionMatch::parserMatchIsCondition(CParser *p, HTerm term)
{
	// Funcao Complexa ... determina todos os tipos de condicoes, tipo um Regex 
	//Default is a direct Asign

	{
		CPredSequence predList = undefinedArticle() << pAny("MatchBody") << verb_IS() << pAny("valueToCheck");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			
			HBlockMatch body = parser_MatchArgument(p, res.matchs["MatchBody"]);
			//HBlockMatchNamed mbody = std::make_shared<CBlockMatchNamed>("it", body);
			HBlockMatch value = parser_MatchArgument(p, res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				return std::make_shared<CBlockMatchDirectIs>(body, value);
			}
		}
	}



	{
		CPredSequence predList = pAny("MatchBody")<< verb_IS()	<<pAny("valueToCheck");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = parser_MatchArgument(p,res.matchs["MatchBody"]);
			HBlockMatch value = parser_MatchArgument(p,res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				return std::make_shared<CBlockMatchDirectIs>(body, value);
			}
		}
	}



	return nullptr;
}



HBlockMatchProperty  NSParser::ExpressionMatch::parse_PropertyOf_Match(CParser *p, std::vector<HTerm>&  term)
{
	{

		  CPredSequence predList = pAny("property")	<<pLiteral("of") <<pAny("obj");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock a = Expression::parser_expression(p,res.matchs["property"]);
			if (a != nullptr) {
				HBlockMatch b = parser_expression_match(p,res.matchs["obj"]);
				if (b != nullptr) {					 
					return std::make_shared<CBlockMatchProperty>(a, b);
				}
			}
		}
	}
	return nullptr;
}

HBlockMatchNoum NSParser::ExpressionMatch::parse_match_SigleNoum(CParser *p, HTerm  term) 
{
 
	return parser_expression_match_noum(p, term);
		 
	 
	 
}


 
HBlockMatch NSParser::ExpressionMatch::parse_match_muteVariable(CParser *p, std::vector<HTerm>&  term)
{

	{
		CPredSequence predList = CPredSequence(pWord("VAR"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			string str = res.matchs["VAR"]->repr();
			if (isupper(str[0]) && str.size() < 2)
			{
				HBlockMatch c1 = std::make_shared<CBlockMatchAny>();
				HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(str, c1);
				return n1;
			}
		}
	}

	return nullptr;

}

HBlockMatch NSParser::ExpressionMatch::parse_match_noum(CParser *p, std::vector<HTerm> term) {
	
	{

		CPredSequence predList_det = mk_HPredLiteral_OR("det", { "A","a","An","an", "The","the" }) << pAny("Noum");
		MatchResult res_det = CMatch(term, predList_det);
		if (res_det.result == Equals)
		{
			HTerm rdet = res_det.matchs["det"];
			HTerm rnoum = res_det.matchs["Noum"];

			

	/*		string nstr = CtoString(res_det.matchs["Noum"]->removeArticle());
			if ((nstr.find("where") != std::string::npos) || (nstr.find("called") != std::string::npos) || (nstr.find("which") != std::string::npos))
			{
				return nullptr;
			} 	*/				 	
			auto p_noum = Expression::parser_noum_expression(p,res_det.matchs["Noum"]);
			if (p_noum != nullptr)
			{
				return std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStrDet>(rdet->repr(), p_noum));
			}
		}


	}

	if (term.size() == 1)
	{
		if (auto text = asCLiteral(term[0].get()))
		{
			return std::make_shared<CBlockMatchText>(std::make_shared<CBlockText>(text->val));
		}

	}

	if(term.size() == 1) return parser_expression_match_noum(p, term[0]);
		
	
	HBlockNoum p_noum_s = Expression::parser_noum_expression(p,  make_list( term ) );
	if (p_noum_s == nullptr) return nullptr;

	return std::make_shared<CBlockMatchNoum>(p_noum_s);

	{
		CPredSequence predList = pAny("Noum");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			string nstr = CtoString(res.matchs["Noum"]->removeArticle());

			if (nstr.find(" or ") != std::string::npos) return nullptr;
			if (nstr.find("or ") == 0) return nullptr;
			if (nstr.find(" and ") != std::string::npos) return nullptr;
			if (nstr.find("and ") == 0) return nullptr;


			if ((nstr.find("where") != std::string::npos) || (nstr.find("called") != std::string::npos) || (nstr.find("which") != std::string::npos))
			{
				return nullptr;
			}
		 

			return parser_expression_match_noum(p, nstr);
			 
		}
	}
	return nullptr;
}

HBlockMatch NSParser::ExpressionMatch::parse_Which_Verb_Match(CParser *p, std::vector<HTerm>&  term) 
{
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1") <<mk_What_Which()<<verb_IS_NOT()	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					//return std::make_shared<CBlockMatchIsNotVerb>(vrepr, n1, n2);
					auto ww = std::make_shared<CBlockMatchWhichNot>(vrepr, n1, n2);
					return ww;
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<mk_What_Which()<<pLiteral("not")	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					auto ww = std::make_shared<CBlockMatchWhichNot>(vrepr, n1, n2);
					return  ww;
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<mk_What_Which()	<<verb_IS()	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					auto ww = std::make_shared<CBlockMatchWhich>(vrepr, n1, n2);
					return ww;
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<mk_What_Which()	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					auto ww = std::make_shared<CBlockMatchWhich>(vrepr, n1, n2);
					return ww;
				}
			}

		}
	}

	return nullptr;
}


 

HBlockMatch NSParser::ExpressionMatch::parse_AssertionAdverb_Match(CParser *p, std::vector<HTerm>&  term)
{
	// and action applying to [one visible thing and requiring light]
	CPredSequence predList = pAny("N1") << verb_IS() << pAny("ADV") << pLiteral("than") << pAny("N2");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) {
		HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
		if (n1 != nullptr)
		{
			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				auto vrepr = CtoString(expandBract(res.matchs["ADV"]));
				return std::make_shared<CBlockMatchIsAdverbialComparasion>(vrepr, n1, n2);

			}
		}
	}

	return nullptr;
}



HBlockMatch NSParser::ExpressionMatch::parse_AssertionVerb_Match(CParser *p, std::vector<HTerm>&  term) 
{
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS_NOT()	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockMatchIsNotVerb>(vrepr, n1, n2);
					
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1") <<pLiteral("not")	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockMatchIsNotVerb>(vrepr, n1, n2);
					
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS()	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockMatchIsVerb>(vrepr, n1, n2);
					
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<p->verbList	<<pAny("N2");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockMatchIsVerb>(vrepr, n1, n2);
					
				}
			}
		}
	}

	return nullptr;
}



HBlockMatch   NSParser::ExpressionMatch::parse_Which_DirectAssign_Match(CParser *p, std::vector<HTerm>&  term) {
	{
		// is a kind definition ??

		  CPredSequence predList =  pAny("Noum")	<<mk_What_Which()	<<verb_IS_NOT() <<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlockMatch noum = parser_expression_match(p,res.matchs["Noum"]);
			if (noum != nullptr)
			{
				HBlockMatch value = parser_expression_match(p,res.matchs["Value"]);
				if (value != nullptr)
				{
					//return std::make_shared<CBlockMatchDirectIsNot>(noum, value);
					auto ww = std::make_shared<CBlockMatchWhichNot>("is", noum, value);
					return  ww;
				}
			}
		}
	}
	{
		// is a kind definition ??
		  CPredSequence predList = pAny("Noum")	<<mk_What_Which()	<<verb_IS() <<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlockMatch value = parser_expression_match(p,res.matchs["Value"]);
			if (value != nullptr) 

			{
				HBlockMatch noum = parser_expression_match(p,res.matchs["Noum"]);
				if (noum != nullptr)
				{
					//return std::make_shared<CBlockMatchDirectIs>(noum, value);
					auto ww = std::make_shared<CBlockMatchWhich>("is", noum, value);
					return  ww;
				}
			}

		}
	}

	return nullptr;

}



HBlockMatch   NSParser::ExpressionMatch::parse_AssertionDirectAssign_Match(CParser *p, std::vector<HTerm>&  term) {
	{
		// is a kind definition ??
	 
 
		  CPredSequence predList = pAny("Noum")	<<verb_IS_NOT()	<<pAny("Value");
	 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlockMatch noum = parser_expression_match(p,res.matchs["Noum"]);
			if (noum != nullptr)
			{
				HBlockMatch value = parser_expression_match(p,res.matchs["Value"]);
				if (value != nullptr)
				{
					 return std::make_shared<CBlockMatchDirectIsNot>(noum, value);
					 
				}
			}
		}
	}
	{
		// is a kind definition ??
		  CPredSequence predList = pAny("Noum")	<<verb_IS()	<<pAny("Value");
	 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlockMatch value = parser_expression_match(p,res.matchs["Value"]);
			if (value != nullptr) 
			{
				HBlockMatch noum = parser_expression_match(p,res.matchs["Noum"]);
				if (noum != nullptr)
				{
					return std::make_shared<CBlockMatchDirectIs>(noum, value);
				}
				
			}

		}
	}

	return nullptr;

}




HBlockMatch   NSParser::ExpressionMatch::parser_Verb_Match(CParser *p, std::vector<HTerm>&  term)
{

	HBlockMatch aDVerb = parse_AssertionAdverb_Match(p, term);
	if (aDVerb != nullptr)
	{
		return aDVerb;
	}

	HBlockMatch aWVerb = parse_Which_Verb_Match(p,term);
	if (aWVerb != nullptr)
	{
		return aWVerb;
	}

	HBlockMatch aWDirect = parse_Which_DirectAssign_Match (p,term);
	if (aWDirect != nullptr)
	{
		return aWDirect;
	}


	HBlockMatch aVerb = parse_AssertionVerb_Match(p,term);
	if (aVerb != nullptr)
	{
		return aVerb;
	}

	HBlockMatch aDirect = parse_AssertionDirectAssign_Match(p,term);
	if (aDirect != nullptr)
	{
		return aDirect;
	}

	return nullptr;
}

std::vector<string> noum_split(const string& s, const char& c)
{
	string buff{ "" };
	std::vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

HBlockMatchNoum NSParser::ExpressionMatch::parser_expression_match_noum(CParser *p, string sNoum)
{
	if (sNoum == "(") return nullptr;
	if (sNoum == ")") return nullptr;
	if (sNoum == "where")
	{
		return nullptr;
	}
	if (sNoum == "which")
	{
		return nullptr;
	}

	if (sNoum == "or")
	{
		return nullptr;
	}
	if (sNoum == "and")
	{
		return nullptr;
	}

	if (sNoum == "to")
	{
		return nullptr;
	}
	if (sNoum == "not")
	{
		return nullptr;
	}
	if (sNoum == "the")
	{
		return nullptr;
	}
	if (sNoum == "a")
	{
		return nullptr;
	}
	if (sNoum == "an")
	{
		return nullptr;
	}
	if (sNoum == "of")
	{
		return nullptr;
	}
	if (sNoum == "if")
	{
		return nullptr;
	}
	if (sNoum == "is")
	{
		return nullptr;
	}
	if (sNoum == ",")
	{
		return nullptr;
	}

	

	auto nn = std::make_shared<CBlockNoumStr>(sNoum);
	return std::make_shared<CBlockMatchNoum>(nn);
}

HBlockMatchNoum NSParser::ExpressionMatch::parser_expression_match_noum(CParser *p, HTerm term)
{
	string sNoum = CtoString(term);

	if (sNoum == "(") return nullptr;
	if (sNoum == ")") return nullptr;


	if (sNoum.find(' ') != string::npos)
	{
		//string composta
		std::vector<string> v_noums = noum_split(sNoum, ' ');
		auto nn = Expression::parser_noum_expression(p, v_noums);
		if (nn == nullptr)
		{
			return nullptr;
		}
		return std::make_shared<CBlockMatchNoum>(nn);
	}

	auto noum = Expression::parser_noum_expression(p, term);
	if (noum == nullptr)
	{
		return nullptr;
	}
	return std::make_shared<CBlockMatchNoum>(noum);
}



HBlock  NSParser::ExpressionMatch::parser_expression_or_match(CParser *p, HTerm  term)
{
	auto ex = NSParser::Expression::parser_expression(p, term);
	if (ex != nullptr) return ex;

	return NSParser::ExpressionMatch::parser_expression_match(p, term);
	 
}
HBlockMatch NSParser::ExpressionMatch::parser_expression_match(CParser *p, HTerm  term)
{

	if (CList *vlist = asCList(term.get()))
	{
		if (is_full_bracket(term))
		{
			std::list<HTerm> nlist = vlist->lst;
			nlist.pop_back();
			nlist.pop_front();
			auto hlist = make_list(std::vector<HTerm>( nlist.begin(),nlist.end()));
			auto r = parser_expression_match(p, hlist);
			auto plist = std::list<HBlockMatch>();
			plist.push_back(r);
			return std::make_shared<CBlockMatchList>(plist);
		}
	}

	if (CList *vlist = asCList(term.get())) 
	{
		auto v = vlist->asVector();		
		auto r = parser_expression_match(p,v);	
		return r;
	}

	if (CLiteral *vtext = asCLiteral(term.get()))
	{
		std::string LS = term->repr();
		if (LS[0] == '"')  LS = LS.substr(1, LS.size() - 1);
		if (LS.back() == '"')  LS = LS.substr(0, LS.size() - 1);		
		return std::make_shared<CBlockMatchText>(std::make_shared<CBlockText>(LS));		
	}



	return parser_expression_match_noum(p, term);
}

std::list<HBlockMatch> NSParser::ExpressionMatch::ToMatchListMatc(CParser *p, std::vector<HPred> pvector, MatchResult result)
{
	std::list<HBlockMatch> vlist;
	for (size_t j = 0; j< pvector.size(); ++j)
	{
		if (CPredAtom* vAtom = asPredAtom(pvector[j].get()))
		{
			auto mm = parser_expression_match_noum(p, vAtom->h);
			if (mm == nullptr) logError("string error");
			vlist.push_back(mm);

			
		}
		else if (CPredAny * vAny = asPredAny(pvector[j].get()))
		{
			HBlockMatch n1 = parser_expression_match(p,result.matchs[vAny->named]);
			vlist.push_back(n1);
		}
		else
		{
			logError("error");
			
		}
	}
	return vlist;
}


HBlockMatch NSParser::ExpressionMatch::DynamicDispatch_action_match(CParser *p, std::vector<HTerm>&  term) {

	for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it)
	{

		MatchResult res_action = CMatch(term, it->matchPhase);
		if (res_action.result == Equals)
		{			 
			std::list<HBlockMatch> resList = ToMatchListMatc(p,it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockMatchList>(resList);
			return 	clistResults;
		}

	}
	return nullptr;
}

HBlockMatchList NSParser::ExpressionMatch::parse_match_comma_list(CParser *p, HTerm  term)
{
	if (CList *vlist = asCList(term.get())) 
	{
		auto v = vlist->asVector();
		auto r = parse_match_comma_list(p, v);
		return r;
	}
	return nullptr;
}

 
HBlockMatchOR NSParser::ExpressionMatch::parse_match_or_list(CParser *p, std::vector<HTerm>&  term)
{
	CPredSequence predList = pAny("N1") << pLiteral("or") << pAny("N2");


	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		HBlockMatchList n1s = parse_match_comma_list(p, res.matchs["N1"]);
		if (n1s != nullptr)
		{		 
			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				auto mlist = n1s->matchList;
				mlist.push_back(n2);
				//n1s->matchList.push_back(n2);
				return std::make_shared<CBlockMatchOR>(mlist);
			}
		}



		HBlockMatch  n1 = parser_expression_match(p, res.matchs["N1"]);
		if (n1 != nullptr)
		{ 
			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				return  std::make_shared<CBlockMatchOR>(std::list<HBlockMatch>{ n1, n2 });
			}
		}
	}
	return nullptr;

}


HBlockMatchOR NSParser::ExpressionMatch::parse_match_or_list(CParser *p, HTerm  term)
{
	if (CList *vlist = asCList(term.get()))
	{
		auto v = vlist->asVector();
		auto r = parse_match_or_list(p, v);
		return r;
	}
	return nullptr;
}



HBlockMatchList NSParser::ExpressionMatch::parse_match_comma_list(CParser *p, std::vector<HTerm>&  term)
{
	  CPredSequence predList = pAny("N1")<<pLiteral(",")<<pAny("N2");		
	 

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		HBlockMatchList n1s = parse_match_comma_list(p, res.matchs["N1"]);
		if (n1s != nullptr)
		{
			HBlockMatchList n2s = parse_match_comma_list(p, res.matchs["N2"]);
			if (n2s != nullptr)
			{
				auto mlist = n2s->matchList;
				for (auto nn : n2s->matchList)
				{
					mlist.push_back(nn);
				}
				//return n1s;
				return std::make_shared<CBlockMatchList>(mlist);
			}


			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				auto mlist = n1s->matchList;
				mlist.push_back(n2);
				//n1s->matchList.push_back(n2);
				return std::make_shared<CBlockMatchList>(mlist);
			}
		}



		HBlockMatch  n1 = parser_expression_match(p, res.matchs["N1"]);
		if (n1 != nullptr)
		{
			HBlockMatchList n2s = parse_match_comma_list(p, res.matchs["N2"]);
			if (n2s != nullptr)
			{
				//n2s->matchList.push_front(n1);
				//return n2s;
				auto mlist = n2s->matchList;
				mlist.push_back(n1);
				return std::make_shared<CBlockMatchList>(mlist);
			}

			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2 });
			}
		}
	}
	return nullptr;

}


std::vector<HTerm>  group_terms(std::vector<HTerm>    vterm)
{
	std::list<HTerm> term = std::list<HTerm>(vterm.begin(), vterm.end());

	std::list<HTerm> ret  ;

	int i = 0;
	size_t n = term.size();


	auto it = term.begin();

	label_init :

	auto start = it;
 
	while (it != term.end())
	{
		if ((*it)->is_openBracket())
		{
			start = it;
		}
		if ((*it)->is_closeBracket())
		{
			//compress
			HTerm sub = make_list(std::vector<HTerm>(start, std::next(it)));
			//remove o range
			it = term.erase(start, std::next(it));
			term.insert(it, sub);
			it = term.begin();
			goto label_init;
		}
		++it;
		
	}
	return std::vector<HTerm>(term.begin(), term.end());

}

HBlockMatchList NSParser::ExpressionMatch::parse_match_list(CParser *p, std::vector<HTerm>&     term_in)
{
	auto mlist = parse_match_list_inn(p, term_in);
	return mlist;


	if (mlist != nullptr)
	{
		// concatena  list of match noum as noumcomposte
		if (mlist->matchList.size() == 1)
		{
			auto mfist = mlist->matchList.front();
			if (HBlockMatchList mmlist = DynamicCasting::asHBlockMatchList(mfist))
			{
				return mmlist;
			}
		}
	}


	return mlist;

}
HBlockMatchList NSParser::ExpressionMatch::parse_match_list_inn(CParser *p, std::vector<HTerm>&     term_in)
{


	if (term_in.size() == 1)
	{
		auto plist = std::list<HBlockMatch>();
		if (CList* listterm = asCList(term_in[0].get()))
		{
			return parse_match_list(p, listterm->asVector());
		}
	}


	if ( term_in.front()->is_openBracket() )
		if (term_in.back()->is_closeBracket())
		{
			if (is_backet_balanced(term_in))
			{
				auto res = std::vector<HTerm>(std::next(term_in.begin()), std::prev(term_in.end()));
				auto mlist = parse_match_list(p, res);
				if (mlist != nullptr)
				{
					auto plist = std::list<HBlockMatch>();
					plist.push_back(mlist);
					return  std::make_shared<CBlockMatchList>(plist);
				}
			}
		}

	/*auto term = group_terms(term_in);
	if (is_full_bracket(term))
	{
		auto mlist = parse_match_list(p, term);
		if (mlist != nullptr)
		{
			auto plist = std::list<HBlockMatch>();
			plist.push_back(mlist);
			return  std::make_shared<CBlockMatchList>(plist);
		}
		return nullptr;
	}*/


	//if (term_in.size() == 0)
	//{
	//	auto plist = std::list<HBlockMatch>();
	//	if (CList* listterm = asCList(term_in[0].get()))
	//	{
	//		return parse_match_list(p, listterm->asVector());
	//	}
	//}


	 //auto term = group_terms(term_in);
	 auto  term = term_in;

	//if (term.size() == 0)
	//{
	//	auto plist = std::list<HBlockMatch>();
	//	if (CList* listterm = asCList(term[0].get()))
	//	{
	//		auto mlist = parse_match_list(p, listterm->asVector());
	//		plist.push_back(mlist);
	//		return  std::make_shared<CBlockMatchList>(plist); 
	//	}
	//	else
	//	{
	//		auto mlist = parser_expression_match(p, term[0] );
	//		plist.push_back(mlist);
	//		return  std::make_shared<CBlockMatchList>(plist);
	//	} 
	//}


	
	// if (is_full_bracket(term))
	// {
	//	 auto mlist = parse_match_list(p, term);
	//	 if (mlist != nullptr)
	//	 {
	//		 auto plist = std::list<HBlockMatch>();
	//		 plist.push_back(mlist);
	//		 return  std::make_shared<CBlockMatchList>(plist);
	//	 }
	//	 return nullptr;
	//}


	{
		CPredSequence predList_det = mk_HPredLiteral_OR("det", { "A","a","An","an", "The","the" }) << pAny("NS");
		MatchResult res_det = CMatch(term, predList_det); 
		if (res_det.result == Equals)
		{
			HBlockMatch m1 = parser_expression_match(p, res_det.matchs["NS"]);
			if (m1 != nullptr)
			{
			//	return m1;
			}
		}
	}


	 

	{
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pWord("N1") << pWord("N2") << pWord("N3") << pWord("N4") << pAny("N5");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				plist.push_back(n1);
				HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					plist.push_back(n2);
					HBlockMatch n3 = parser_expression_match(p, res.matchs["N3"]);
					if (n3 != nullptr)
					{
						plist.push_back(n3);

						HBlockMatch n4 = parser_expression_match(p, res.matchs["N4"]);
						if (n4 != nullptr)
						{
							plist.push_back(n4);

							std::vector<HTerm> vlist = { res.matchs["N5"] };
							HBlockMatchList n5 = parse_match_list(p, vlist);
							if (n5 != nullptr)
							{
								plist.insert(plist.end(), n5->matchList.begin(), n5->matchList.end());
								return  std::make_shared<CBlockMatchList>(plist);
							}
						}
					}
				}
			}
		}
	}


	


	{		 
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pWord("N1") << pWord("N2") << pAny("N3") ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				plist.push_back(n1);
				HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					plist.push_back(n2);
					std::vector<HTerm> vlist = { res.matchs["N3"] };
					HBlockMatchList n3 = parse_match_list(p, vlist);
					if (n3 != nullptr)
					{
						plist.insert(plist.end(), n3->matchList.begin(), n3->matchList.end() );
						return  std::make_shared<CBlockMatchList>(plist);
					}
				}
			}
		}
	}



	{
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pWord("N1") <<    pAny("N2");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
				if (n1 != nullptr)
				{
					plist.push_back(n1);
					std::vector<HTerm> vlist = { res.matchs["N2"] };
					HBlockMatchList n2 = parse_match_list(p, vlist);
					if (n2 != nullptr)
					{
						plist.insert(plist.end(), n2->matchList.begin(), n2->matchList.end());
						return  std::make_shared<CBlockMatchList>(plist);
					}
				}
		}
	}

	{
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pAny("N2") << pWord("N1");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				plist.push_back(n1);
				std::vector<HTerm> vlist = { res.matchs["N2"] };
				HBlockMatchList n2 = parse_match_list(p, vlist);
				if (n2 != nullptr)
				{
					plist.insert(plist.end(), n2->matchList.begin(), n2->matchList.end());
					return  std::make_shared<CBlockMatchList>(plist);
				}
			}
		}
	}



	//=================================================


	if (false) {
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pAny("N1")	<<pAny("N2")	<<pAny("N3")	<<pAny("N4"); 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				if (auto list1 = DynamicCasting::asHBlockMatchList(n1))
				{
					plist.insert(plist.end(), list1->matchList.begin(), list1->matchList.end());
				}
				else
				{
					plist.push_back(n1);
				}


				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (auto list2 = DynamicCasting::asHBlockMatchList(n2))
					{
						plist.insert(plist.end(), list2->matchList.begin(), list2->matchList.end());
					}
					else
					{
						plist.push_back(n2);
					}

					HBlockMatch n3 = parser_expression_match(p,res.matchs["N3"]);
					if (n3 != nullptr)
					{
						if (auto list3 = DynamicCasting::asHBlockMatchList(n3))
						{
							plist.insert(plist.end(), list3->matchList.begin(), list3->matchList.end());
						}
						else
						{
							plist.push_back(n3);
						}

						HBlockMatch n4 = parser_expression_match(p,res.matchs["N4"]);
						if (n4 != nullptr)
						{
							if (auto list4 = DynamicCasting::asHBlockMatchList(n4))
							{
								plist.insert(plist.end(), list4->matchList.begin(), list4->matchList.end());								
							}
							else
							{
								plist.push_back(n4);
							}
							//return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2, n3, n4});
							return  std::make_shared<CBlockMatchList>(plist);
						}
					}

					
				}
			}

		}
	}

	if(false){
		auto plist = std::list<HBlockMatch>();
		CPredSequence predList = pAny("N1") << pAny("N2") << pAny("N3")  ;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				if (res.matchs["N1"]->type() == TermString)
				{
					if (auto list1 = DynamicCasting::asHBlockMatchList(n1))
					{
						plist.insert(plist.end(), list1->matchList.begin(), list1->matchList.end());
					}
				}
				else
				{
					plist.push_back(n1);
				}


				HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (auto list2 = DynamicCasting::asHBlockMatchList(n2))
					{
						plist.insert(plist.end(), list2->matchList.begin(), list2->matchList.end());
					}
					else
					{
						plist.push_back(n2);
					}

					HBlockMatch n3 = parser_expression_match(p, res.matchs["N3"]);
					if (n3 != nullptr)
					{
						if (auto list3 = DynamicCasting::asHBlockMatchList(n3))
						{
							plist.insert(plist.end(), list3->matchList.begin(), list3->matchList.end());
						}
						else
						{
							plist.push_back(n3);
						} 
						return  std::make_shared<CBlockMatchList>(plist);						 
					} 
				}
			}

		}
	}


	{ 
	    CPredSequence predList = pAny("N1")<<pAny("N2")<<pAny("N3");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					HBlockMatch n3 = parser_expression_match(p,res.matchs["N3"]);					
					if (n3 != nullptr)
					{
						return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2, n3 });
					}
				}
			}

		}
	}


	{
		 
		CPredSequence predList = pAny("N1")	<< pAny("N2");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			
			HBlockMatch n1 = parser_expression_match(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlockMatch n2 = parser_expression_match(p,res.matchs["N2"]);
				if (n2 != nullptr)
					return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, n2 });
			}
		
		}
	}
	return nullptr;
}

HBlockMatch NSParser::ExpressionMatch::parse_APreposition(CParser *p, std::vector<HTerm>&     term)
{
	CPredSequence predList = pAny("N1") <<  pPreposition("prep") <<  pAny("N2");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) {

		auto s1 = res.matchs["N1"]->repr();
		auto s2 = res.matchs["N2"]->repr();
		printf("%s P %s\n", s1.c_str(), s2.c_str());

		HBlockMatch n1 = parser_expression_match(p, res.matchs["N1"]);
		if (n1 != nullptr)
		{
			HBlockMatch n2 = parser_expression_match(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				auto vrepr = CtoString(expandBract(res.matchs["prep"]));				
				auto mPP = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr>(vrepr));

				return  std::make_shared<CBlockMatchList>(std::list<HBlockMatch>{ n1, mPP, n2 });
			}
		}
	}
	return nullptr;
}
 

 
HBlockMatch NSParser::ExpressionMatch::parser_expression_match(CParser *p, std::vector<HTerm>&    lst)
{

 

	HBlockMatch  rblock_dynamicEntry_1 = (DynamicDispatch_action_match(p,lst));
	if (rblock_dynamicEntry_1 != nullptr) return rblock_dynamicEntry_1;

 

	HBlockMatch rblock_assert_1 = (parser_Verb_Match(p,lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;


	HBlockMatch noum_propOF = parse_PropertyOf_Match(p,lst);
	if (noum_propOF != nullptr) {
		return noum_propOF;
	}

 
	//HBlockMatch maprep = parse_APreposition(p, lst);
	//if (maprep != nullptr) {
	//	return maprep;
	//}

	HBlockMatch arg_Assign = parser_MatchArgument(p,lst);
	if (arg_Assign != nullptr) {
		return arg_Assign;
	}

	HBlockMatch list_or_Assign = parse_match_or_list(p, lst);
	if (list_or_Assign != nullptr) {
		return list_or_Assign;
	}

	HBlockMatch list_c_Assign = parse_match_comma_list(p, lst);
	if (list_c_Assign != nullptr) {
		return list_c_Assign;
	}

	HBlockMatch list_Assign = parse_match_list(p,lst);
	if (list_Assign != nullptr) {
		return list_Assign;
	}

	HBlockMatch muteVariable_Assign = parse_match_muteVariable(p, lst);
	if (muteVariable_Assign != nullptr) {
		return muteVariable_Assign;
	}

	HBlockMatch noum_Assign = parse_match_noum(p,lst);
	if (noum_Assign != nullptr) {
		return noum_Assign;
	}

	return nullptr;

}







//=====================================================================================================================


std::list<std::list<HBlock > > getPartition_fn_n(int order, std::vector<HTerm>& vs, int ia, std::function<HBlock(HTerm)> func);
 



std::list<std::list<HBlock > > getBiPartition_fn(std::vector<HTerm> & vs, std::function<HBlock(HTerm)> func)
{
	 
	{
	 
		if (vs.size() > 1)
		{
			return getPartition_fn_n(2, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}



std::list<std::list<HBlock > > getTriPartition_fn(std::vector<HTerm> & vs, std::function<HBlock(HTerm)> func)
{ 
	{
 
		if (vs.size() > 2)
		{
			return getPartition_fn_n(3, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}

std::list<std::list<HBlock > > getQuadPartition_fn(std::vector<HTerm> & vs, std::function<HBlock(HTerm)> func)
{
 
	{
 
		if (vs.size() > 3)
		{
			return getPartition_fn_n(4, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}



std::list<std::list<HBlock > > getQuiPartition_fn(std::vector<HTerm> & vs, std::function<HBlock(HTerm)> func)
{
	 
	{
 
		if (vs.size() > 4)
		{
			return getPartition_fn_n(5, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}

std::list<std::list<HBlock > > getHexPartition_fn(std::vector<HTerm> & vs, std::function<HBlock(HTerm)> func)
{
	 
		if (vs.size() > 5)
		{
			return 	getPartition_fn_n(6, vs, 0, func);
		}
 
		return	std::list<std::list<HBlock > >();
	 
}








HBlock  NSParser::Expression::parser_ComponentePhase(CParser *p, HTerm    term_in)
{
	if (CList* listterm = asCList(term_in.get()))
	{
		auto r =  parser_phrase_literal(p, listterm->asVector());
		if (r == nullptr)
		{
			return nullptr;
		}
		return r;
	}
	 

	auto ri =  Expression::parser_noum_expression(p, term_in);
	if (ri == nullptr)
	{
		return nullptr;
	}
	return ri;
}


void add_item(std::list<HBlock > &plist, HBlock h)
{
	if (auto nn = DynamicCasting::asHBlockList(h))
	{
		plist.insert(plist.end(), nn->lista.begin(), nn->lista.end());

	}
	else
	{
		plist.push_back(h);
	}
}


std::vector<CBlocking::HBlock  >   NSParser::Expression::getTriPartition_phase_item(CParser *p, std::vector<HTerm> & vs    )
{
	//if (vs.front()->is_openBracket() || (vs.back()->is_closeBracket()))
	{

		if (is_backet_balanced(vs) == false)
		{
			return  std::vector<CBlocking::HBlock  >();
		}
	}


	std::list<std::vector<HBlock  > > ret;
	size_t n = vs.size();

	for (size_t i1 = 1; i1 < n - 1; ++i1)
	{
		std::vector<HTerm> p1(vs.begin(), vs.begin() + i1);
		
		HBlock b1 =  parser_phrase_literal(p, p1);
		if (b1 == nullptr) continue;

		for (size_t i2 = i1 + 1; i2 < n; ++i2)
		{

			std::vector<HTerm> p2(vs.begin() + i1, vs.begin() + i2);
			std::vector<HTerm> p3(vs.begin() + i2, vs.end());
			HBlock b2 = parser_phrase_literal(p, p2);
			if (b2 == nullptr) continue;

			HBlock b3 = parser_phrase_literal(p, p3);
			if (b3 == nullptr) continue;


			std::vector<HBlock >  arr  = { b1 , b2 , b3 };
			return arr;
		}
	}
	
	return std::vector<HBlock >();
}


HBlockList  NSParser::Expression::parser_phrase_literal_entry(CParser *p, std::vector<HTerm>&    term_in)
{
	HBlockList r = parser_phrase_literal(p, term_in);
	if (r == nullptr)
	{
		return nullptr;
	}

	if (r->lista.size() == 1)
	{
		if (auto nlist = DynamicCasting::asHBlockList(r->lista.front()))
		{
			return nlist;
		}
	}

	if (r != nullptr) return r;
	return nullptr;
}

HBlockList  NSParser::Expression::parser_phrase_literal(CParser *p, std::vector<HTerm>&    term_in)
{



	if (term_in.size() == 1)
	{
		HBlock r =  parser_noum_expression(p, term_in.front());
		if (r == nullptr) return nullptr;

		auto plist = std::list<HBlock >();
		plist.push_back( r);
		return  std::make_shared<CBlockList>(plist);
	}



	if (is_backet_balanced(term_in) == false) return nullptr;

	if (term_in.front()->is_openBracket() && (term_in.back()->is_closeBracket()))
	{	
		bool tem_par_intern = false;
		for (auto h = std::next(term_in.begin()); h != std::prev(term_in.end()); ++h)
		{
			if ((*h)->is_closeBracket() || (*h)->is_openBracket())
			{
				tem_par_intern = true;
				break;
			}
		} 
		 
			 if (tem_par_intern ==false)
			{
				auto res = std::vector<HTerm>(std::next(term_in.begin()), std::prev(term_in.end()));
				auto mlist = parser_phrase_literal(p, res);
				if (mlist != nullptr)
				{
					//return mlist;
					auto plist = std::list<HBlock >();
					plist.push_back(mlist);
					return  std::make_shared<CBlockList>(plist);
				}
			}
			
	}



	//{				
	//	auto tlist = getTriPartition_phase_item(p,term_in);
	//	if (tlist.empty() == false)
	//	{
	//		auto plist = std::list<HBlock >();
	//		add_item(plist, tlist[0]);
	//		add_item(plist, tlist[1]);
	//		add_item(plist, tlist[2]); 
	//		auto r =   std::make_shared<CBlockList>(plist);
	//		r->dump("");
	//		return r;
	//	}	 
	//}


	{
		auto plist = std::list<HBlock >();
		CPredSequence predList = pWord("N1") << pWord("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlock  n1 = parser_ComponentePhase(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				add_item(plist, n1);
				 
				HBlock  n2 = parser_ComponentePhase(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					add_item(plist, n2);
					return  std::make_shared<CBlockList>(plist);
				}
			}
		}
	}

 







	{
		auto plist = std::list<HBlock >();
		CPredSequence predList = pWord("N1") << pAny("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlock  n1 = parser_ComponentePhase(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				add_item(plist, n1);
			 
				HBlock  n2 = parser_ComponentePhase(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					add_item(plist, n2);
					return  std::make_shared<CBlockList>(plist);
				}
			}
		}
	}



	{
		auto plist = std::list<HBlock >();
		CPredSequence predList = pAny("N1") << pWord("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlock  n1 = parser_ComponentePhase(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
			
				add_item(plist, n1); 

				HBlock  n2 = parser_ComponentePhase(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{	
					add_item(plist, n2);
					return  std::make_shared<CBlockList>(plist);
				}
			}
		}
	}


	{
		 
		CPredSequence predList = pAny("N1") << pAny("N2");
		MatchResult res = CMatch(term_in, predList);
		if (res.result == Equals)
		{
			HBlock  n1 = parser_ComponentePhase(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				 

				HBlock  n2 = parser_ComponentePhase(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto plist = std::list<HBlock >();
					add_item(plist, n1);
					add_item(plist, n2);
					return  std::make_shared<CBlockList>(plist);
				}
			}
		}
	}

	return nullptr;

	{
		HTerm  term_i =  make_list({ term_in });
		HBlock  n1 = parser_ComponentePhase(p, term_i);
		if (n1 != nullptr)
		{
			auto plist = std::list<HBlock >(); 
			add_item(plist, n1);
			return  std::make_shared<CBlockList>(plist);
		}
	}
	 

	return nullptr;
}
 