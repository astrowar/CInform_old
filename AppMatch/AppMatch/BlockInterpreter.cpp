#include "BlockInterpreter.h"
#include <iostream>

using namespace std;

void CBlockNoum::dump(std::string ident)
{
	cout << ident << this->named << endl;
}

CBlockNoum::CBlockNoum(std::string _value)
{
	named = _value;
}

 
void CBlockEnums::dump(std::string ident)
{
}

CBlockEnums::CBlockEnums(std::vector<CBlockNoum*> _values): values(_values)
{

}

void CBlockKind::dump(std::string ident)
{
	cout << ident << "Kind: "<< named << endl;
}

void CBlockKindValue::dump(std::string ident)
{
	cout << ident << "Kind Value: " << named << endl;
}

void CBlockInstance::dump(std::string ident)
{
	cout << ident << "Instance: " << named << endl;
}

CBlockInstance::CBlockInstance(string _named)
{
}

 

void  CBlockList::dump(std::string  ident)
{ 
	cout <<ident << "List: " << endl;
	 for(auto e = lista.begin() ; e!= lista.end();++e)
	 {
		 (*e)->dump(ident + "   ");
	 }
}

void CBlockList::push_back(CBlockNoum* c_block_value)
{
	lista.push_back(c_block_value);
}

void CBlockAssertion_is::dump(std::string ident)
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
	/*CBlockAssertion(CBlockAction( CBlockNoum("Person"), "eat", CBlockNoum("Thing")));

	CBlockAssertionCond(CBlockAssertion(CBlockAction("Action","A"), "in presence of", CBlockNoum("Person", "other")),
	CBlockSame(CBlockProp(CBlockNoum("location"), CBlockProp(CBlockNoum("first noum"), CBlockNoum("A")),
	CBlockProp(CBlockNoum("location"), CBlockNoum("other")))));

	CBlockMatchAction((CBlockAction("eat"), CBlockNoum("something")), "in presence of", CBlockNoum("Lady Bracknell"));
	*/


}