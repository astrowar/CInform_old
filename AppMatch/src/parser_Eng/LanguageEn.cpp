//
// Created by eraldo.rangel on 28/06/2018.
//

#include "LanguageDepend.h"

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


