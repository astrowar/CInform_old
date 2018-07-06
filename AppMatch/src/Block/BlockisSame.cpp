// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include <cassert>
#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"
#include "CBlockDecideIf.hpp"
#include "CblockAssertion.hpp"
#include "CBlockComposition.hpp"
#include "CBlockRelation.hpp"

#include <algorithm>
using namespace CBlocking;

namespace Auxiliar
{
	bool  BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
}

namespace CBlocking {
	namespace Comparison {
		bool isSame(const CBlocking::HBlock &b1, const CBlocking::HBlock &b2)
		{
			return b1->isSame(b1.get(), b2.get());
		}

		bool isSame_BlockNoum(CBlockNoum* b1, CBlockNoum* b2)
		{
			return b1->named == b2->named;
		}


		bool isSame_BlockNothing(CBlockNothing* b1, CBlockNothing* b2)
		{
			return b1->named == b2->named;
		}


		bool isSame_list(std::list<HBlock>&  b1, std::list<HBlock>& b2)
		{
			if (b1.size() != b2.size()) return false;
			for (auto i1 : b1)
			{
				bool has_inList = false;
				for (auto i2 : b2)
				{
					if (CBlock::isSame(i1.get(), i2.get()))
					{
						has_inList = true; break;
					}
				}
				if (has_inList == false) return false;
			}
			return true;
		}

		bool isSame_BlockList(CBlockList* b1, CBlockList* b2)
		{
			return  isSame_list(b1->lista, b2->lista);
		}

		bool isSame_BlockCompositionList(CBlockCompositionList* b1, CBlockCompositionList* b2)
		{
			return  isSame(b1->itemKind, b2->itemKind);
		}

		bool isSame_BlockKindNamed(CBlockKindNamed* b1, CBlockKindNamed* b2)
		{
			return b1->named == b2->named;
		}




		bool isSame_BlockText(CBlockText* b1, CBlockText* b2)
		{
			if (b1->contents == b2->contents) return true;
			string a1 = b1->contents;
			string a2 = b2->contents;

			std::string::iterator aa1 = std::unique(a1.begin(), a1.end(), Auxiliar::BothAreSpaces); a1.erase(aa1, a1.end());
			std::string::iterator aa2 = std::unique(a2.begin(), a2.end(), Auxiliar::BothAreSpaces); a2.erase(aa2, a2.end());

			while (a1.size() > 1 && a1[0] == ' ') a1 = a1.substr(1, a1.size() - 1);
			while (a1.size() > 1 && a1.back() == ' ') a1 = a1.substr(0, a1.size() - 1);
			while (a2.size() > 1 && a2[0] == ' ') a2 = a2.substr(1, a2.size() - 1);
			while (a2.size() > 1 && a2.back() == ' ') a2 = a2.substr(0, a2.size() - 1);

			return a1 == a2;
		}


		bool isSame_BlockPhraseDefine(CBlockPhraseDefine* b1, CBlockPhraseDefine* b2)
		{
			if (CBlock::isSame(b1->header.get(), b2->header.get()) == false) return false;

			if (CBlock::isSame(b1->body.get(), b2->body.get()) == false) return false;

			return true;
		}


		bool   isSame_BlockMatchNamed(CBlockMatchNamed* b1, CBlockMatchNamed* b2) 
		{
			if (b1->named != b2->named) return false;
			if (CBlock::isSame(b1->matchInner.get(), b2->matchInner.get()) == false) return false;
			return true;
		}

		bool isSame_BlockMatchDirectIs(CBlockMatchDirectIs* b1, CBlockMatchDirectIs* b2)
		{
			if (CBlock::isSame(b1->obj.get(), b2->obj.get()) == false) return false;
			if (CBlock::isSame(b1->value.get(), b2->value.get()) == false) return false;
			return true;
		}


		bool isSame_BlockRelationArguments(CBlockRelationArguments* b1, CBlockRelationArguments* b2)
		{
			if (b1->value1 == nullptr && b2->value1 != nullptr) return false;
			if (b1->value1 != nullptr && b2->value1 == nullptr) return false;
			if (b1->value1 != nullptr && b2->value1 != nullptr)
			{
				if (CBlock::isSame(b1->value1.get(), b2->value1.get()) == false) return false;
			}

			if (b1->value2 == nullptr && b2->value2 != nullptr) return false;
			if (b1->value2 != nullptr && b2->value2 == nullptr) return false;
			if (b1->value2 != nullptr && b2->value2 != nullptr)
			{
				if (CBlock::isSame(b1->value2.get(), b2->value2.get()) == false) return false;
			}
			return true;
		}



		bool isSame_BlockPhraseHeader(CBlockPhraseHeader* b1, CBlockPhraseHeader* b2)
		{

			if (CBlock::isSame(b1->verb.get(), b2->verb.get()) == false) return false;

			if (b1->arg1.get() != nullptr && b2->arg1.get() != nullptr)
			{
				if (CBlock::isSame(b1->arg1.get(), b2->arg1.get()) == false) return false;
			}
			if (b1->arg2.get() != nullptr && b2->arg2.get() != nullptr)
			{
				if (CBlock::isSame(b1->arg2.get(), b2->arg2.get()) == false) return false;
			}

			if (b1->arg1.get() == nullptr && b2->arg1.get() != nullptr) return false;
			if (b1->arg1.get() != nullptr && b2->arg1.get() == nullptr) return false;
			if (b1->arg2.get() == nullptr && b2->arg2.get() != nullptr) return false;
			if (b1->arg2.get() != nullptr && b2->arg2.get() == nullptr) return false;

			if (b1->pred1.get() == nullptr && b2->pred1.get() != nullptr) return false;
			if (b1->pred1.get() != nullptr && b2->pred1.get() == nullptr) return false;
			if (b1->pred2.get() == nullptr && b2->pred2.get() != nullptr) return false;
			if (b1->pred2.get() != nullptr && b2->pred2.get() == nullptr) return false;


			if (CBlock::isSame(b1->pred1.get(), b2->pred1.get()) == false) return false;
			if (CBlock::isSame(b1->pred2.get(), b2->pred2.get()) == false) return false;

			return true;
		}


		bool isSame_BlockList_AND(CBlockList* b1, CBlockList* b2)
		{
			return  isSame_list(b1->lista, b2->lista);
		}
		bool isSame_BlockList_OR(CBlockList* b1, CBlockList* b2)
		{
			return  isSame_list(b1->lista, b2->lista);
		}

		bool isSame_BlockKindValue(CBlockKindValue* b1, CBlockKindValue* b2)
		{
			return (b1->named == b2->named);
		}

		bool isSame_BlockKindEntity(CBlockKindEntity* b1, CBlockKindEntity* b2)
		{
			return b1->named == b2->named;
		}
		bool isSame_BlockInstance(CBlockInstance* b1, CBlockInstance* b2)
		{
			//if (b1->named != b2->named) return false;

			if (b1->id == b2->id) return true;
			return false;
		}

		bool isSame_BlockInstanceNamed(CBlockInstanceNamed* b1, CBlockInstanceNamed* b2)
		{

			if (b1->id == b2->id) return true;
			return false;
		}


		bool isSame_BlockAction(CBlockAction * b1, CBlockAction* b2)
		{

			return b1 == b2;
		}

		bool isSame_BlockActionNamed(CBlockActionNamed * b1, CBlockActionNamed* b2)
		{

			return  (b1->named == b2->named);
		}
		bool isSame_BlockActionInstance(CBlockActionInstance * b1, CBlockActionInstance* b2)
		{

			return b1->id == b2->id;
		}



		bool isSame_BlockMatchNoum(CBlockMatchNoum* b1, CBlockMatchNoum* b2)
		{
			return isSame(b1->inner, b2->inner);
		}

		bool isSame_BlockMatchNoum(CBlockKind* b1, CBlockKind* b2)
		{
			return b1 == b2;
		}

		bool isSame_BlockProperty(CBlockProperty* b1, CBlockProperty* b2)
		{
			return isSame(b1->obj, b2->obj) && isSame(b1->prop, b2->prop);
		}
		bool isSame_BlockInstanceVariable(CBlockInstanceVariable * b1, CBlockInstanceVariable* b2)
		{
			return isSame(b1->kind_name, b2->kind_name) && isSame(b1->property_name, b2->property_name);
		}

		bool isSame_BlockToDecideWhat(CBlockToDecideWhat * b1, CBlockToDecideWhat* b2)
		{
			//return isSame(b1->decideBody, b2->decideBody) && isSame(b1->queryToMatch, b2->queryToMatch);
			return  isSame(b1->queryToMatch, b2->queryToMatch);
		}

		bool isSame_BlockAssertion_isDirectAssign(CBlockAssertion_isDirectAssign * b1, CBlockAssertion_isDirectAssign* b2)
		{
			return isSame(b1->value, b2->value) && isSame(b1->variable, b2->variable);
		}

		bool isSame_BlockAssertion_isNotDirectAssign(CBlockAssertion_isNotDirectAssign  * b1, CBlockAssertion_isNotDirectAssign* b2)
		{
			return isSame(b1->value, b2->value) && isSame(b1->variable, b2->variable);
		}

		bool isSame_BlockIsVerb(CBlockIsVerb  * b1, CBlockIsVerb* b2)
		{
			if (b1->verb == b2->verb)
			{
				if (isSame(b1->n1, b2->n1) && isSame(b1->n2, b2->n2)) return true;
			}
			return false;
		}


		bool isSame_BlockAssertion_isInstanceOf(CBlockAssertion_isInstanceOf  * b1, CBlockAssertion_isInstanceOf* b2)
		{
			if (isSame(b1->baseKind, b2->baseKind))
				if (isSame(b1->noum, b2->noum)) return true;

			return false;
		}

		
		bool isSame_BlockMatchText(CBlockMatchText  * b1, CBlockMatchText* b2)
		{
			return CBlock::isSame(b1->inner.get(), b2->inner.get());
		}


		bool isSame_BlockMatchValue(CBlockMatchValue  * b1, CBlockMatchValue* b2)
		{
			return CBlock::isSame(b1->inner.get(), b2->inner.get());
		}
		bool isSame_BlockMatchList(CBlockMatchList  * b1, CBlockMatchList* b2)
		{
			if (b1->matchList.size() == b2->matchList.size())
			{
				auto it1 = b1->matchList.begin();
				auto it2 = b2->matchList.begin();
				while (it1 != b1->matchList.end())
				{
					if (!isSame((*it1), (*it2))) return false;
					++it1;
					++it2;
				}
			}
			return false;
		}

	}
}

 bool CBlock::isSame(CBlock* b1, CBlock* b2)
{
	if (b1 == b2) return true;
	if (b1 == nullptr && b2 != nullptr) return false;
	if (b2 == nullptr && b1 != nullptr) return false;
	if (b1->type() != b2->type()) return false;


	if (b1->type() == BlockNoumStr)  return Comparison::isSame_BlockNoum(static_cast<CBlockNoumStr*>(b1), static_cast<CBlockNoumStr*>(b2));
	if (b1->type() == BlockInstanceAnonymous)  return Comparison::isSame_BlockInstance(static_cast<CBlockInstanceAnonymous*>(b1), static_cast<CBlockInstanceAnonymous*>(b2));
	if (b1->type() == BlockInstanceNamed)  return Comparison::isSame_BlockInstanceNamed(static_cast<CBlockInstanceNamed*>(b1), static_cast<CBlockInstanceNamed*>(b2));
	if (b1->type() == BlockActionNamed)  return Comparison::isSame_BlockActionNamed(static_cast<CBlockActionNamed*>(b1), static_cast<CBlockActionNamed*>(b2));
	if (b1->type() == BlockActionInstance)  return Comparison::isSame_BlockActionInstance(static_cast<CBlockActionInstance*>(b1), static_cast<CBlockActionInstance*>(b2));

	if (b1->type() == BlockKindEntity)  return Comparison::isSame_BlockKindEntity(static_cast<CBlockKindEntity*>(b1), static_cast<CBlockKindEntity*>(b2));
	if (b1->type() == BlockKindValue)  return Comparison::isSame_BlockKindValue(static_cast<CBlockKindValue*>(b1), static_cast<CBlockKindValue*>(b2));
	if (b1->type() == BlockMatchNoum)  return Comparison::isSame_BlockMatchNoum(static_cast<CBlockMatchNoum*>(b1), static_cast<CBlockMatchNoum*>(b2));
	if (b1->type() == BlockInstanceVariable)  return Comparison::isSame_BlockInstanceVariable(static_cast<CBlockInstanceVariable*>(b1), static_cast<CBlockInstanceVariable*>(b2));
	if (b1->type() == BlockToDecideWhat) return Comparison::isSame_BlockToDecideWhat(static_cast<CBlockToDecideWhat*>(b1), static_cast<CBlockToDecideWhat*>(b2));
	if (b1->type() == BlockAssertion_isDirectAssign) return Comparison::isSame_BlockAssertion_isDirectAssign(static_cast<CBlockAssertion_isDirectAssign*>(b1), static_cast<CBlockAssertion_isDirectAssign*>(b2));
	if (b1->type() == BlockAssertion_isNotDirectAssign) return Comparison::isSame_BlockAssertion_isNotDirectAssign(static_cast<CBlockAssertion_isNotDirectAssign*>(b1), static_cast<CBlockAssertion_isNotDirectAssign*>(b2));
	if (b1->type() == BlockIsVerb) return Comparison::isSame_BlockIsVerb(static_cast<CBlockIsVerb*>(b1), static_cast<CBlockIsVerb*>(b2));
	if (b1->type() == BlockProperty) return Comparison::isSame_BlockProperty(static_cast<CBlockProperty*>(b1), static_cast<CBlockProperty*>(b2));
	if (b1->type() == BlockMatchList) return Comparison::isSame_BlockMatchList(static_cast<CBlockMatchList*>(b1), static_cast<CBlockMatchList*>(b2));
	if (b1->type() == BlockMatchText) return Comparison::isSame_BlockMatchText(static_cast<CBlockMatchText*>(b1), static_cast<CBlockMatchText*>(b2));
	if (b1->type() == BlockMatchValue) return Comparison::isSame_BlockMatchValue(static_cast<CBlockMatchValue*>(b1), static_cast<CBlockMatchValue*>(b2));

	if (b1->type() == BlockAssertion_isInstanceOf) return Comparison::isSame_BlockAssertion_isInstanceOf(static_cast<CBlockAssertion_isInstanceOf*>(b1), static_cast<CBlockAssertion_isInstanceOf*>(b2));

	if (b1->type() == BlockNothing)  return Comparison::isSame_BlockNothing(static_cast<CBlockNothing*>(b1), static_cast<CBlockNothing*>(b2));
	if (b1->type() == BlockList)  return Comparison::isSame_BlockList(static_cast<CBlockList*>(b1), static_cast<CBlockList*>(b2));

	if (b1->type() == BlockCompositionList)  return Comparison::isSame_BlockCompositionList(static_cast<CBlockCompositionList*>(b1), static_cast<CBlockCompositionList*>(b2));
	if (b1->type() == BlockKindNamed)  return Comparison::isSame_BlockKindNamed(static_cast<CBlockKindNamed*>(b1), static_cast<CBlockKindNamed*>(b2));
	if (b1->type() == BlockKindOf)   return false;

	if (b1->type() == BlockText)   return Comparison::isSame_BlockText(static_cast<CBlockText*>(b1), static_cast<CBlockText*>(b2)); ;
	if (b1->type() == BlockPhraseDefine)   return Comparison::isSame_BlockPhraseDefine(static_cast<CBlockPhraseDefine*>(b1), static_cast<CBlockPhraseDefine*>(b2)); ;
	if (b1->type() == BlockPhraseHeader)   return Comparison::isSame_BlockPhraseHeader(static_cast<CBlockPhraseHeader*>(b1), static_cast<CBlockPhraseHeader*>(b2)); ;
	if (b1->type() == BlockRelationArguments)   return Comparison::isSame_BlockRelationArguments(static_cast<CBlockRelationArguments*>(b1), static_cast<CBlockRelationArguments*>(b2)); ;
	if (b1->type() == BlockMatchDirectIs)   return Comparison::isSame_BlockMatchDirectIs(static_cast<CBlockMatchDirectIs*>(b1), static_cast<CBlockMatchDirectIs*>(b2)); ;
	if (b1->type() == BlockMatchNamed)   return Comparison::isSame_BlockMatchNamed(static_cast<CBlockMatchNamed*>(b1), static_cast<CBlockMatchNamed*>(b2)); ;
	b1->dump("");
	b2->dump("");

	assert(false);
	return false;
}
