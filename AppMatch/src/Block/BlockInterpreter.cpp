// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "BlockInterpreter.hpp"
 
#include "CblockAssertion.hpp"
#include "CBlockMatch.hpp"
#include "CBlockControlFlux.hpp"
#include <cstdlib>
#include <cassert>
#include <cstring>

using namespace std;
using namespace CBlocking;

void logWarring(std::string str)
{
	printf("#Warring %s\n", str.c_str());
	printf("\n");
}

void logError(std::string str)
{
	printf("LErr: %s\n", str.c_str());
	printf("\n" );
}
void logMessage(std::string str)
{
	printf("Log %s\n", str.c_str());
}


NoumDefinitions CBlocking::noum_nothing() {
    return NoumDefinitions();
}


NoumDefinitions CBlocking::single_definitions(string noun, CBlock *block) {
    return NoumDefinitions({NoumDefinition(noun, block)});
}

NoumDefinitions CBlocking::join_definitions(NoumDefinitions a, NoumDefinitions b) {
    NoumDefinitions ab(a.begin(), a.end());
    ab.insert(ab.end(), b.begin(), b.end());
    return ab;
}

void *CBlock::operator new(size_t size) {

	
    return malloc(size);

}

CUnresolved::CUnresolved(string _contents) : contents(_contents) 
{
}

CBlockNoum::CBlockNoum( )  
{
	
}

CBlockNoumStrDet::CBlockNoumStrDet(string _det, HBlockNoum _noum) :noum(_noum), det(_det) 
{ 
	assert(det.size() > 0);

	assert(_noum != nullptr); 
};

 

CBlockNoumStr::CBlockNoumStr(string _value) :noum(_value) {
    
	assert(_value != "not");
	assert(_value != "the");
	assert(_value != "which");
	
	assert(strchr(_value.c_str(), ',') == 0);
	assert(strncmp(_value.c_str(), "the", 3) != 0);
	assert(strncmp(_value.c_str(), "the", 3) != 0);
	assert(strncmp(_value.c_str(), "to ", 3) != 0);

    assert(noum[0] != '[');
	assert(noum[0] != '(');

	if (_value.size() == 1)
	{
		assert(_value[0] != '!');
	}

	if ((noum[0] == 'A') && (noum[1] == ' '))
	{
		_value[0] = 'a';
	}
	if (_value.find('\t') != std::string::npos)
	{
		assert(_value.find('\t') == std::string::npos);
		assert(_value.find('\n') == std::string::npos);
	}

	assert(_value.find(' ') == std::string::npos);
}


CBlockEnums::CBlockEnums(vector<HBlockNoum> _values) : values(_values) {

}

bool CBlockEnums::contains(string cs) {
    for (vector<shared_ptr<CBlockNoum>>::value_type& n : values)
	{
		if (n->named() == cs) return true;
	}
    return false;
}


CBlockNamedValue::CBlockNamedValue(string _named) : named(_named) {
    assert(_named[0] != '[');
}

 


CBlockProperty::CBlockProperty(CBlocking::HBlock _prop, CBlocking::HBlock _obj) : prop((_prop)), obj((_obj))
{
    if (_prop != nullptr)
    {
        prop = _prop;
    }
}

CBlockInstanceVariable::CBlockInstanceVariable(HBlockNoum _kind_name, HBlockNoum _property_name) : property_name(_property_name),
                                                                                            kind_name((_kind_name)) {
}

 

void CBlockCollection::push_back(HBlock c_block_value)
{
	    lista.push_back((c_block_value));
}
 

 
CBlockControlIF::CBlockControlIF(CBlocking::HBlock _block_if, CBlocking::HBlock _block_then, CBlocking::HBlock _block_else)	: block_if(_block_if), block_then(_block_then), block_else(_block_else)
{
	block_if = _block_if;
}

 

CBlockActionApply::CBlockActionApply(CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) : noum1((_noum1)), noum2((_noum2)) {
}



//  define  ((Person:A) eat (thing:B)) is a Action.  -> first noum, second noum
//  define ((action:A) is in the presence of (other:B) ) if (( location of (first noum of A) ) is same (location B)).
//  eating something in the presence of Lady Bracknell

 


 

CBlocking::HBlock CBlockAssertion_canBe::get_obj() {
    return obj;
}


CBlockAssertion_canBe::CBlockAssertion_canBe(CBlocking::HBlock _obj, HBlockEnums _definition) : definition(_definition),
                                                                                     obj(_obj) {
}

//CBlocking::HBlock CBlockAssertion_isKindOf::get_obj() {   return noum;}

 

//CBlocking::HBlock CBlockAssertion_isKindOf::get_definition() { return baseKind; }

CBlocking::HBlock CBlockAssertion_isInstanceOf::get_obj() {
    return noum;
}

CBlocking::HBlock CBlockAssertion_isInstanceOf::get_definition() {
    return baseKind;
}

CBlocking::HBlock CBlockAssertion_isNamedValueOf::get_obj() {
    return this->noum;
}

CBlocking::HBlock CBlockAssertion_isNamedValueOf::get_definition() {
    return this->baseKind;
}

CBlocking::HBlock CBlockAssertion_isVariable::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isVariable::get_definition() {
    return baseKind;
}

CBlocking::HBlock CBlockAssertion_isLocalVariable::get_obj()
{
	return variableName;
}

CBlocking::HBlock CBlocking::CBlockAssertion_isLocalVariable::get_definition()
{
	return valueExpression;
}



CBlocking::HBlock CBlockAssertion_isDefaultAssign::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isDefaultAssign::get_definition() {
    return value;
}

CBlocking::HBlock CBlockAssertion_isConstantAssign::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isConstantAssign::get_definition() {
    return value;
}

CBlocking::HBlock CBlockAssertion_isForbiddenAssign::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isForbiddenAssign::get_definition() {
    return value;
}

CBlocking::HBlock CBlockAssertion_isDirectAssign::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isDirectAssign::get_definition() {
    return value;
}

CBlocking::HBlock CBlockAssertion_isNotDirectAssign::get_obj() {
    return variable;
}

CBlocking::HBlock CBlockAssertion_isNotDirectAssign::get_definition() {
    return value;
}

CBlocking::HBlock CBlockIsVerb::get_obj()
{
	return n1;
}

CBlocking::HBlock CBlockIsVerb::get_definition()
{
	return n2;
}
CBlocking::HBlock CBlockIsNotVerb::get_obj()
{
	return n1;
}

CBlocking::HBlock CBlockIsNotVerb::get_definition()
{
	return n2;
}

CBlocking::HBlock CBlockIsAdverbialComparasion::get_obj()
{
	return n1;
}

CBlocking::HBlock CBlockIsAdverbialComparasion::get_definition()
{
	return n2;
}



