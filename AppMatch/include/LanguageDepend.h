//
// Created by eraldo.rangel on 28/06/2018.
//

#ifndef CINFORM_LANGUAGEDEPEND_H
#define CINFORM_LANGUAGEDEPEND_H

#include "BlockInterpreter.hpp"
#include "CBlockBoolean.hpp"

using namespace CBlocking;

//rotinas que unificam o ponto de dependencia da linguagem no interpreter
class LanguageDepend
{
public:
    virtual HBlockBooleanValue asBoolean(HBlockNoum noum) = 0;
    virtual bool is_nothing(HBlockNoum noum) = 0 ;
    virtual HBlockKind metaKind(string kind) = 0;
    virtual bool isSameString(string a, string b) = 0;

    virtual  string   getNothing () = 0;
    virtual  string   getAnything()= 0;
    virtual  string   getMetaKind ()= 0;
    virtual  string   getMetaKindRelation()= 0;
    virtual   string  getMetaKindPhrase ()= 0;
    virtual  string   getMetaKindEntity ()= 0;
    virtual  string   getMetaKindBoolean ()= 0;
    virtual  string   getMetaKindAction ()= 0;
    virtual  string   getMetaKindList ()= 0;
    virtual  string   getMetaKindText ()= 0;
    virtual  string   getMetaKindAny ()= 0;

};



class LanguageEn : LanguageDepend
{
    HBlockBooleanValue asBoolean(HBlockNoum noum) override ;
    bool is_nothing(HBlockNoum noum) override ;
    virtual HBlockKind metaKind(string kind) override ;


       string   getNothing () override;
       string   getAnything()override;
       string   getMetaKind ()override;
       string   getMetaKindRelation()override;
        string  getMetaKindPhrase ()override;
       string   getMetaKindEntity ()override;
       string   getMetaKindBoolean ()override;
       string   getMetaKindAction ()override;
       string   getMetaKindList ()override;
       string   getMetaKindText ()override;
       string   getMetaKindAny ()override;

};

#endif //CINFORM_LANGUAGEDEPEND_H
