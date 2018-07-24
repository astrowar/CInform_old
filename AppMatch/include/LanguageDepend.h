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
	virtual bool is_det(HBlockNoum noum) = 0;
    virtual HBlockKind metaKind(string kind) = 0;
    //virtual bool isSameString(const string &a, const string &b) = 0;
	virtual bool isSameNoum(const HBlockNoum a, const HBlockNoum b) = 0;
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


	virtual HBlockNoum   get_plural_of(string s) = 0;
	virtual HBlockNoum  get_singular_of(string s) = 0 ;

	virtual string text_matching_subexpression(int i) = 0;
};



 

class LanguageEn : public LanguageDepend
{
    HBlockBooleanValue asBoolean(HBlockNoum noum) override ;
    bool is_nothing(HBlockNoum noum) override ;
	bool is_det(HBlockNoum noum) override;
	 
      HBlockKind metaKind(string kind) override ;
	   bool isSameString(const string &a, const string &b)  ;
	    bool isSameNoum(const HBlockNoum a, const HBlockNoum b) override;

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


	    HBlockNoum   get_plural_of(string s) override;
	    HBlockNoum  get_singular_of(string s) override;

		string text_matching_subexpression(int i) override;
};

#endif //CINFORM_LANGUAGEDEPEND_H
