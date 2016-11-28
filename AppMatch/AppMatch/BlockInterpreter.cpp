#include "BlockInterpreter.hpp"
 
#include "CblockAssertion.hpp"
#include "CBlockMatch.hpp"
#include <cstdlib>
#include <cassert>

using namespace std;
using namespace CBlocking;

void logError(std::string str)
{
	printf("%s\n", str.c_str());
}
void logMessage(std::string str)
{
	printf("%s\n", str.c_str());
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



CBlockNoum::CBlockNoum(string _value) : named(_value) {
    
   // assert(named[0] != '[');
	//assert(named[0] != '(');
}


CBlockEnums::CBlockEnums(vector<HBlockNoum> _values) : values(_values) {

}

bool CBlockEnums::contains(string cs) {
    for (auto &n : values) {
        if (n->named == cs) return true;
    }
    return false;
}


CBlockNamedValue::CBlockNamedValue(string _named) : named(_named) {
    assert(_named[0] != '[');
}

CBlockVariable::CBlockVariable(string _named) : named(_named) {
    assert(_named[0] != '[');
}


CBlockProperty::CBlockProperty(CBlocking::HBlock _prop, CBlocking::HBlock _obj) : prop((_prop)), obj((_obj)) {

}

CBlockInstanceVariable::CBlockInstanceVariable(HBlockNoum _kind_name, HBlockNoum _property_name) : property_name(_property_name),
                                                                                            kind_name((_kind_name)) {
}

 

void CBlockList::push_back(CBlocking::HBlock c_block_value) {
    lista.push_back((c_block_value));
}

NoumDefinitions CBlockList::noumDefinitions() {
    NoumDefinitions nd = noum_nothing();
    for (auto &i : lista) {
        nd = join_definitions(nd, i->noumDefinitions());
    }
    return nd;
}


 

CBlockActionApply::CBlockActionApply(CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) : noum1((_noum1)), noum2((_noum2)) {
}



//  define  ((Person:A) eat (thing:B)) is a Action.  -> first noum, second noum
//  define ((action:A) is in the presence of (other:B) ) if (( location of (first noum of A) ) is same (location B)).
//  eating something in the presence of Lady Bracknell

void eatExample() {
    /*CBlockAssertion(CBlockAction( CBlockNoum("Person"), "eat", CBlockNoum("Thing")));

    CBlockAssertionCond(CBlockAssertion(CBlockAction("Action","A"), "in presence of", CBlockNoum("Person", "other")),
    CBlockSame(CBlockProp(CBlockNoum("location"), CBlockProp(CBlockNoum("first noum"), CBlockNoum("A")),
    CBlockProp(CBlockNoum("location"), CBlockNoum("other")))));

    CBlockMatchAction((CBlockAction("eat"), CBlockNoum("something")), "in presence of", CBlockNoum("Lady Bracknell"));
    */


}


 

CBlocking::HBlock CBlockAssertion_canBe::get_obj() {
    return obj;
}


CBlockAssertion_canBe::CBlockAssertion_canBe(CBlocking::HBlock _obj, HBlockEnums _definition) : definition(_definition),
                                                                                     obj(_obj) {
}

CBlocking::HBlock CBlockAssertion_isKindOf::get_obj() {
    return noum;
}

NoumDefinitions CBlockAssertion_isKindOf::noumDefinitions() {
    return single_definitions(this->noum->named, this->get_definition().get());
}

CBlocking::HBlock CBlockAssertion_isKindOf::get_definition() { return baseKind; }

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
    return value;
}

CBlocking::HBlock CBlockAssertion_isForbiddenAssign::get_definition() {
    return variable;
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

  