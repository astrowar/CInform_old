//
// Created by eraldo.rangel on 28/06/2018.
//

#include "LanguageDepend.h"
#include "parser/ParserPlural.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;
bool LanguageEn::is_nothing(HBlockNoum noum)
{

    if (noum->named() == "nothing") return true;
    if (noum->named() == "none") return true;
    if (noum->named() == "nil") return true;
    return false;
}

bool LanguageEn::is_det(HBlockNoum noum)
{

	string s = noum->named();
	if (s.empty()) return false;
	s[0] = tolower(s[0]);

	const string det_list[] = { "the", "a", "an", "some", "my", "your", "his", "her", "our", "their" };
	if (std::find(std::begin(det_list), std::end(det_list), s) != std::end(det_list))
		return true;
	return false;
}
 


HBlockBooleanValue LanguageEn::asBoolean(HBlockNoum noum) 
{
	string s = noum->named();
	if (s.empty())   return nullptr;
	s[0] = tolower(s[0]);

	const string yes_list[] = { "true", "yes" } ;
	if (std::find(std::begin(yes_list), std::end(yes_list), s) != std::end(yes_list))
		return std::make_shared<CBlockBooleanValue>(true);;

	const string no_list[] = { "false", "no" };
	if (std::find(std::begin(yes_list), std::end(yes_list), s) != std::end(yes_list))
		return std::make_shared<CBlockBooleanValue>(false);

 
    return nullptr;
}

bool LanguageEn::isSameNoum(  HBlockNoum n1, HBlockNoum n2)
{
	if (n1 == n2) return true;


	if (HBlockNoumStrDet d1 = DynamicCasting::asHBlockNoumStrDet(n1))
	{
		return isSameNoum(d1, n1);
	}

	if (HBlockNoumStrDet d2 = DynamicCasting::asHBlockNoumStrDet(n2))
	{
		return isSameNoum(n1, d2);
	}

	string s1 = n1->named();
	string s2 = n2->named();

	return isSameString(s1, s2);
}


bool LanguageEn::isSameString(const string &s1, const string& s2)
{
	if (s1 == s2) return true;
	if ((s1.size() == s2.size()) && (tolower(s1[0]) == tolower(s2[0])))
	{
		int n = s1.size();
		for (int j = 0; j< n; ++j)
		{
			if (tolower(s1[j]) != tolower(s2[j])) return false;
		}
		return true;
	}
	return false;
}

HBlockKind LanguageEn::metaKind(string n)
{

        if (isSameString( n , "text")) {
            return  std::make_shared<CBlockKindValue>("text");
        }

        if (isSameString(n, "number")) {
            return  std::make_shared<CBlockKindValue>("number");
        }

        if (isSameString(n, "action"))
        {
            return  std::make_shared<CBlockKindEntity>("action");
        }

        if (isSameString(n, "relation"))
        {
            return  std::make_shared<CBlockKindEntity>("relation");
        }

    return nullptr;

}

string  LanguageEn::getNothing (){ return   "nothing";}
string  LanguageEn::getAnything(){ return   "anything";}
string  LanguageEn::getMetaKind (){ return   "kind";}
string  LanguageEn::getMetaKindRelation(){ return   "relation";}
string  LanguageEn::getMetaKindPhrase (){ return  "phrase";}
string  LanguageEn::getMetaKindEntity (){ return   "entity";}
string  LanguageEn::getMetaKindBoolean (){ return   "boolean";}
string  LanguageEn::getMetaKindAction (){ return   "action";}
string  LanguageEn::getMetaKindList (){ return  "list";}
string  LanguageEn::getMetaKindText (){ return   "text";}
string  LanguageEn::getMetaKindAny (){ return   "any";}




PLURALTABLE plura_tableEn(); // obtem a tabela de plurals para ingles

HBlockNoum  LanguageEn::get_plural_of(string s)
{ 
	static PLURALTABLE plural_tab = plura_tableEn();
	auto pPlural = plural_of(s, &plural_tab);
	if (!pPlural.empty())
	{
		return std::make_shared<CBlockNoumStr>(pPlural);
	}
	return nullptr;
}


HBlockNoum  LanguageEn::get_singular_of(string s)
{ 
	static PLURALTABLE plural_tab = plura_tableEn();
	auto pSingle = singular_of(s, &plural_tab);
	if (!pSingle.empty())
	{
		return std::make_shared<CBlockNoumStr>(pSingle);
	}
	return nullptr;
}



string LanguageEn::text_matching_subexpression(int i)
{
	string base = "matching subexpression";
	if (i == 0) return "matching expression";
	if (i == 1) return base+ " 1";
	if (i == 2) return base + " 2";
	if (i == 3) return base + " 3";
	if (i == 4) return base + " 4";
	if (i == 5) return base + " 5";
	if (i == 6) return base + " 6";
	if (i == 7) return base + " 7";
	if (i == 8) return base + " 8";
	if (i == 9) return base + " 9";
	
}