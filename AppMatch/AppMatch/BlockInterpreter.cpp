#include "BlockInterpreter.h"
#include <iostream>

using namespace std;

void CBlockValue::dump(std::string ident)
{
	cout << ident << this->value  << endl;
}

CBlockValue::CBlockValue(std::string _value)
{
	value = _value;
}

void  CBlockList::dump(std::string  ident)
{ 
	cout <<ident << "List: " << endl;
	 for(auto e = lista.begin() ; e!= lista.end();++e)
	 {
		 (*e)->dump(ident + "   ");
	 }
}

void CBlockList::push_back(CBlockValue* c_block_value)
{
	lista.push_back(c_block_value);
}

void CBlockAssertion::dump(std::string ident)
{
	cout << ident << "Assert: " << endl;	
	
		this->obj->dump(ident + "     ");
	cout << ident << "is_____ " << endl;
		this->definition->dump(ident + "     ");
		
	
}


void CBlockActionApply::dump(std::string ident)
{
	cout << ident << "Action applyTo " << endl;	
	{
		this->noum1->dump(ident + "       ");
		cout << ident << "With " << endl;
		this->noum2->dump(ident + "       ");

	}
}

CBlockActionApply::CBlockActionApply(CBlock* _noum1, CBlock* _noum2): noum1(_noum1), noum2(_noum2)
{
}

CBlockInterpreter::CBlockInterpreter()
{
}


CBlockInterpreter::~CBlockInterpreter()
{
}



//  define  ((Person:A) eat (thing:B)) is a Action.  -> first noum, second noum
//  define ((action:A) is in the presence of (other:B) ) if (( location of (first noum of A) ) is same (location B)).
//  eating something in the presence of Lady Bracknell

void eatExample()
{
	/*CBlockAssertion(CBlockAction( CBlockValue("Person"), "eat", CBlockValue("Thing")));

	CBlockAssertionCond(CBlockAssertion(CBlockAction("Action","A"), "in presence of", CBlockValue("Person", "other")),
	CBlockSame(CBlockProp(CBlockValue("location"), CBlockProp(CBlockValue("first noum"), CBlockValue("A")),
	CBlockProp(CBlockValue("location"), CBlockValue("other")))));

	CBlockMatchAction((CBlockAction("eat"), CBlockValue("something")), "in presence of", CBlockValue("Lady Bracknell"));
	*/


}