//
// Created by eraldo on 30/06/2018.
//

#ifndef CINFORM_PREDICATES_H
#define CINFORM_PREDICATES_H
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


// Language terms to undestand Any Language  CInform


#include <match/CMatch.hpp>
#include "BlockInterpreter.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


using tokenIdent = string;

class LanguageModule
{
public:

    virtual CPredSequence parse_AssertionAction_secondPart(tokenIdent ApplyRemainder ) =0;
    virtual CPredSequence parse_ActionCompositionName(tokenIdent ActionName, tokenIdent pred, tokenIdent pred_aux) =0 ;
    virtual CPredSequence parse_AssertionAction(tokenIdent ActionName, tokenIdent ApplyRemainder) =0 ;
    virtual CPredSequence parse_AssertionIsLocalValue(tokenIdent VarName, tokenIdent VarValue) =0 ;
    virtual CPredSequence parse_AssertionIsVariable(tokenIdent VariableNoum, tokenIdent KindBase) =0 ;
    virtual CPredSequence parse_KindOf(tokenIdent kindBase ) =0 ;
    virtual CPredSequence parse_CompositionOf(tokenIdent kindBase , tokenIdent kindDst) =0 ;
    virtual CPredSequence parse_CompositionOf_b(tokenIdent kindBase, tokenIdent kindDst) =0 ;
    virtual CPredSequence parse_CompositionOf_b(tokenIdent kindBase ) =0 ;
    virtual CPredSequence parse_AssertionIsCompositionOf(tokenIdent Noum, tokenIdent CompDef) =0 ;
    virtual CPredSequence parse_AssertionIsKindOf(tokenIdent Noum, tokenIdent KindDef) =0 ;
    virtual CPredSequence parse_AssertionValuesOf(tokenIdent valueName, tokenIdent valueKind) =0 ;
    virtual CPredSequence parse_AssertionDefaultAssign(tokenIdent Noum, tokenIdent Value) =0 ;
    virtual CPredSequence parse_AssertionDefaultAssign_always(tokenIdent Noum, tokenIdent Value) =0 ;
    virtual CPredSequence parse_AssertionDefaultAssign_never(tokenIdent Noum, tokenIdent Value) =0 ;
    virtual CPredSequence parserAssertionDirectAssign_isNot(tokenIdent Noum ,tokenIdent Value) =0 ;
    virtual CPredSequence parserAssertionDirectAssign_is(tokenIdent Noum, tokenIdent Value) =0 ;
    virtual CPredSequence parse_AssertionVerb_is_not(tokenIdent N1, tokenIdent N2) =0 ;
    virtual CPredSequence parse_AssertionVerb_not(tokenIdent N1, tokenIdent N2) =0 ;
    virtual CPredSequence parse_AssertionVerb_is(tokenIdent N1, tokenIdent N2) =0 ;
    virtual CPredSequence parse_AssertionVerb(tokenIdent N1, tokenIdent N2) =0 ;
    virtual CPredSequence parser_MatchIsConditionVerb_is(tokenIdent MatchBody, tokenIdent valueToCheck) =0 ;
    virtual CPredSequence parser_MatchIsConditionVerb(tokenIdent MatchBody, tokenIdent valueToCheck) =0 ;
    virtual CPredSequence STMT_verb_relation(tokenIdent Relation ) =0 ;
    // the verb V implies a R relation
    // verb V implies a R relation
    virtual CPredSequence STMT_verb_Assertion_N(tokenIdent VerbList, tokenIdent Relation) =0 ;
    // (the verb|verb) V Aux implies (a|an|the) R relation
    // the verb NEXT TO imples an PROXIMITY relation
    virtual CPredSequence STMT_verb_Assertion(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation) =0 ;
    virtual CPredSequence STMT_verb_Assertion_b(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation) =0 ;
    virtual CPredSequence STMT_verb_Assertion_c(tokenIdent Verb,  tokenIdent Relation) =0 ;
    virtual CPredSequence STMT_verb_Assertion_d(tokenIdent Verb, tokenIdent Relation) =0 ;
    virtual CPredSequence STMT_verb_Assertion_e(tokenIdent Verb, tokenIdent Relation) =0 ;
    virtual CPredSequence STMT_canBe_Assertion(tokenIdent Target, tokenIdent EnumValues) =0 ;
    virtual CPredSequence CProperty_called(tokenIdent kindName , tokenIdent propName) =0 ;
    virtual CPredSequence STMT_hasAn_Assertion(tokenIdent Target, tokenIdent KindAndName) =0 ;
    virtual CPredSequence parserBooleanNot(tokenIdent N ) =0 ;  
    virtual CPredSequence parserBooleanAnd(tokenIdent n1, tokenIdent n2) =0 ; 
};

#endif //CINFORM_PREDICATES_H
