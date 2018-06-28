//
// Created by eraldo.rangel on 28/06/2018.
//

#include "LanguageDepend.h"
#include "Parser\ParserPlural.hpp"


using namespace CBlocking;
bool LanguageEn::is_nothing(HBlockNoum noum)
{

    if (noum->named == "nothing") return true;
    if (noum->named == "none") return true;
    if (noum->named == "nil") return true;
    return false;
}

HBlockBooleanValue LanguageEn::asBoolean(HBlockNoum noum) {
    if (isSameString(noum->named , "true")) return std::make_shared<CBlockBooleanValue>(true);
    if (isSameString(noum->named , "false")) return std::make_shared<CBlockBooleanValue>(false);
    if (isSameString(noum->named, "yes")) return std::make_shared<CBlockBooleanValue>(true);
    if (isSameString(noum->named , "no")) return std::make_shared<CBlockBooleanValue>(false);
    return nullptr;
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

