#include "BlockInterpreter.h"



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