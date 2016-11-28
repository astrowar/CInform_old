#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"
#include "CBlockDecideIf.hpp"
#include "CblockAssertion.hpp"

using namespace CBlocking;

bool isSame(CBlocking::HBlock b1, CBlocking::HBlock b2)
{
	return b1->isSame(b1.get(), b2.get());
}

bool isSame_BlockNoum( CBlockNoum* b1, CBlockNoum* b2)
{
	if (b1->named == b2->named) return true;
	return false;
}

bool isSame_BlockKindThing(CBlockKindThing* b1, CBlockKindThing* b2)
{
	if (b1->named == b2->named) return true;
	return false;
}
bool isSame_BlockInstance(CBlockInstance* b1, CBlockInstance* b2)
{
	if (b1->named != b2->named) return false;
	if (b1->id != b2->id) return false;
	return false;
}

bool isSame_BlockAction(CBlockAction * b1, CBlockAction* b2)
{
	if (b1->named == b2->named) return true;
	return false;
}


 
 
bool isSame_BlockMatchNoum(CBlockMatchNoum* b1, CBlockMatchNoum* b2)
{
	if ( isSame(b1->inner , b2->inner)) return true;
	return false;
}

bool isSame_BlockMatchNoum(CBlockKind* b1, CBlockKind* b2)
{
	if (b1->named == b2->named) return true;
	return false;
}

bool isSame_BlockProperty(CBlockProperty* b1, CBlockProperty* b2)
{
	if ( isSame(b1->obj ,b2->obj ) && isSame(b1->prop ,b2->prop )) return false;
	return false;
}
bool isSame_BlockInstanceVariable(CBlockInstanceVariable * b1, CBlockInstanceVariable* b2)
{
	if (isSame(b1->kind_name, b2->kind_name) && isSame(b1->property_name, b2->property_name)) return false;
	return false;
}

bool isSame_BlockToDecideWhat(CBlockToDecideWhat * b1, CBlockToDecideWhat* b2)
{
	if (isSame(b1->decideBody, b2->decideBody) && isSame(b1->queryToMatch, b2->queryToMatch)) return false;
	return false;
}

bool isSame_BlockAssertion_isDirectAssign(CBlockAssertion_isDirectAssign * b1, CBlockAssertion_isDirectAssign* b2)
{
	if (isSame(b1->value, b2->value) && isSame(b1->variable, b2->variable)) return false;
	return false;
}

bool isSame_BlockAssertion_isNotDirectAssign(CBlockAssertion_isNotDirectAssign  * b1, CBlockAssertion_isNotDirectAssign* b2)
{
	if (isSame(b1->value, b2->value) && isSame(b1->variable, b2->variable)) return false;
	return false;
}

bool isSame_BlockIsVerb(CBlockIsVerb  * b1, CBlockIsVerb* b2)
{
	if (b1->verb == b2->verb)
	{
		if (isSame(b1->n1, b2->n1) && isSame(b1->n2, b2->n2)) return false;
	}
	return false;
}



bool isSame_BlockMatchList(CBlockMatchList  * b1, CBlockMatchList* b2)
{
	if (b1->matchList.size()  == b2->matchList.size())
	{
		auto it1 = b1->matchList.begin();
		auto it2 = b2->matchList.begin();
		while (it1 != b1->matchList.end())
		{
			if (isSame((*it1), (*it2)) == false) return false;
			++it1;
			++it2;
		}
	}
	return false;
}


bool CBlock::isSame(CBlock* b1,CBlock* b2) const
{
	if (b1 == b2) return true;
	if (b1 == nullptr && b2 != nullptr) return false;
	if (b2 == nullptr && b1 != nullptr) return false;
	if (b1->type() != b2->type()) return false;


	if (b1->type() == BlockNoum)  return isSame_BlockNoum( static_cast<CBlockNoum*>(b1),  static_cast<CBlockNoum*>(b2));
	if (b1->type() == BlockInstance)  return isSame_BlockInstance(static_cast<CBlockInstance*>(b1), static_cast<CBlockInstance*>(b2));
	if (b1->type() == BlockAction)  return isSame_BlockAction(static_cast<CBlockAction*>(b1), static_cast<CBlockAction*>(b2));
	if (b1->type() == BlockKindThing)  return isSame_BlockKindThing(static_cast<CBlockKindThing*>(b1), static_cast<CBlockKindThing*>(b2));
	if (b1->type() == BlockMatchNoum)  return isSame_BlockMatchNoum(static_cast<CBlockMatchNoum*>(b1), static_cast<CBlockMatchNoum*>(b2));
	if (b1->type() == BlockInstanceVariable)  return isSame_BlockInstanceVariable(static_cast<CBlockInstanceVariable*>(b1), static_cast<CBlockInstanceVariable*>(b2));
	if (b1->type() == BlockToDecideWhat ) return isSame_BlockToDecideWhat(static_cast<CBlockToDecideWhat*>(b1), static_cast<CBlockToDecideWhat*>(b2));
	if (b1->type() == BlockAssertion_isDirectAssign) return isSame_BlockAssertion_isDirectAssign(static_cast<CBlockAssertion_isDirectAssign*>(b1), static_cast<CBlockAssertion_isDirectAssign*>(b2));
	if (b1->type() == BlockAssertion_isNotDirectAssign) return isSame_BlockAssertion_isNotDirectAssign(static_cast<CBlockAssertion_isNotDirectAssign*>(b1), static_cast<CBlockAssertion_isNotDirectAssign*>(b2));
	if (b1->type() == BlockIsVerb) return isSame_BlockIsVerb(static_cast<CBlockIsVerb*>(b1), static_cast<CBlockIsVerb*>(b2));
	if (b1->type() == BlockProperty) return isSame_BlockProperty(static_cast<CBlockProperty*>(b1), static_cast<CBlockProperty*>(b2));
	if (b1->type() == BlockMatchList) return isSame_BlockMatchList(static_cast<CBlockMatchList*>(b1), static_cast<CBlockMatchList*>(b2));

	 
	return false;
}
