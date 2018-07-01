//
// Created by eraldo on 30/06/2018.
//

#ifndef CINFORM_PREDICATES_EN_H
#define CINFORM_PREDICATES_EN_H
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


// Language terms to undestand English  CInform




#include <parser/Predicates.hpp>
#include <parser/Parser.hpp>

class LanguageEnglish : public  LanguageModule
{

public:

    NSParser::CParser *p;
      LanguageEnglish(NSParser::CParser *_p ): p(_p)
    {
    }
    CPredSequence parse_AssertionAction_secondPart(tokenIdent ApplyRemainder )  override ;
    CPredSequence parse_ActionCompositionName(tokenIdent ActionName, tokenIdent pred, tokenIdent pred_aux)  override ;
    CPredSequence parse_AssertionAction(tokenIdent ActionName, tokenIdent ApplyRemainder)  override ;
    CPredSequence parse_AssertionIsLocalValue(tokenIdent VarName, tokenIdent VarValue)  override ;
    CPredSequence parse_AssertionIsVariable(tokenIdent VariableNoum, tokenIdent KindBase)  override ;
    CPredSequence parse_KindOf(tokenIdent kindBase )  override ;
    CPredSequence parse_CompositionOf(tokenIdent kindBase , tokenIdent kindDst)  override ;
    CPredSequence parse_CompositionOf_b(tokenIdent kindBase, tokenIdent kindDst)  override ;
    CPredSequence parse_CompositionOf_b(tokenIdent kindBase )  override ;
    CPredSequence parse_AssertionIsCompositionOf(tokenIdent Noum, tokenIdent CompDef)  override ;
    CPredSequence parse_AssertionIsKindOf(tokenIdent Noum, tokenIdent KindDef)  override ;
    CPredSequence parse_AssertionValuesOf(tokenIdent valueName, tokenIdent valueKind)  override ;
    CPredSequence parse_AssertionDefaultAssign(tokenIdent Noum, tokenIdent Value)  override ;
    CPredSequence parse_AssertionDefaultAssign_always(tokenIdent Noum, tokenIdent Value)  override ;
    CPredSequence parse_AssertionDefaultAssign_never(tokenIdent Noum, tokenIdent Value)  override ;
    CPredSequence parserAssertionDirectAssign_isNot(tokenIdent Noum ,tokenIdent Value)  override ;
    CPredSequence parserAssertionDirectAssign_is(tokenIdent Noum, tokenIdent Value)  override ;
    CPredSequence parse_AssertionVerb_is_not(tokenIdent N1, tokenIdent N2)  override ;
    CPredSequence parse_AssertionVerb_not(tokenIdent N1, tokenIdent N2)  override ;
    CPredSequence parse_AssertionVerb_is(tokenIdent N1, tokenIdent N2)  override ;
    CPredSequence parse_AssertionVerb(tokenIdent N1, tokenIdent N2)  override ;
    CPredSequence parser_MatchIsConditionVerb_is(tokenIdent MatchBody, tokenIdent valueToCheck)  override ;
    CPredSequence parser_MatchIsConditionVerb(tokenIdent MatchBody, tokenIdent valueToCheck)  override ;
    CPredSequence STMT_verb_relation(tokenIdent Relation )  override ;
    // the verb V implies a R relation
    // verb V implies a R relation
    CPredSequence STMT_verb_Assertion_N(tokenIdent VerbList, tokenIdent Relation)  override ;
    // (the verb|verb) V Aux implies (a|an|the) R relation
    // the verb NEXT TO imples an PROXIMITY relation
    CPredSequence STMT_verb_Assertion(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation)  override ;
    CPredSequence STMT_verb_Assertion_b(tokenIdent Verb, tokenIdent Aux, tokenIdent Relation)  override ;
    CPredSequence STMT_verb_Assertion_c(tokenIdent Verb,  tokenIdent Relation)  override ;
    CPredSequence STMT_verb_Assertion_d(tokenIdent Verb, tokenIdent Relation)  override ;
    CPredSequence STMT_verb_Assertion_e(tokenIdent Verb, tokenIdent Relation)  override ;
    CPredSequence STMT_canBe_Assertion(tokenIdent Target, tokenIdent EnumValues)  override ;
    CPredSequence CProperty_called(tokenIdent kindName , tokenIdent propName)  override ;
    CPredSequence STMT_hasAn_Assertion(tokenIdent Target, tokenIdent KindAndName)  override ;
    CPredSequence parserBooleanNot(tokenIdent N )  override ;;
    CPredSequence parserBooleanAnd(tokenIdent n1, tokenIdent n2)  override ;;
};


#endif //CINFORM_PREDICATESEN_H
