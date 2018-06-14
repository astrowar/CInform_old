// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "dynamicCast.hpp"
 


namespace CBlocking
{
	namespace DynamicCasting
	{



		 
		//CBlockKind* asCBlockKind(CBlock* c)
		//{
		//	if (c->type() == BlockType::BlockKind)
		//		return static_cast<CBlockKind*>(c);
		//	return nullptr;
		//}
		CUnresolved* asCBlockUnresolved(CBlock* c)
		{
			if (c->type() == BlockType::Unresolved)
				return static_cast<CUnresolved*>(c);
			return nullptr;
		}
		CBlockKindOf* asCBlockKindOf(CBlock* c)
		{
			if (c->type() == BlockType::BlockKindOf)
				return static_cast<CBlockKindOf*>(c);
			return nullptr;
		}
		CBlockKindAction* asCBlockKindAction(CBlock* c)
		{
			if (c->type() == BlockType::BlockKindAction)
				return static_cast<CBlockKindAction*>(c);
			return nullptr;
		}
		CBlockKindValue* asCBlockKindValue(CBlock* c)
		{
			if (c->type() == BlockType::BlockKindValue)
				return static_cast<CBlockKindValue*>(c);
			return nullptr;
		}
	 
		CBlockNamedValue* asCBlockNamedValue(CBlock* c)
		{
			if (c->type() == BlockType::BlockNamedValue)
				return static_cast<CBlockNamedValue*>(c);
			return nullptr;
		}
	 
		CBlockInstanceVariable* asCBlockInstanceVariable(CBlock* c)
		{
			if (c->type() == BlockType::BlockInstanceVariable)
				return static_cast<CBlockInstanceVariable*>(c);
			return nullptr;
		}
		CBlockList* asCBlockList(CBlock* c)
		{
			if (c->type() == BlockType::BlockList)
				return static_cast<CBlockList*>(c);
			return nullptr;
		}
		CBlockEnums* asCBlockEnums(CBlock* c)
		{
			if (c->type() == BlockType::BlockEnums)
				return static_cast<CBlockEnums*>(c);
			return nullptr;
		}
		CBlockProperty* asCBlockProperty(CBlock* c)
		{
			if (c->type() == BlockType::BlockProperty)
				return static_cast<CBlockProperty*>(c);
			return nullptr;
		}
		CBlockAssertion_isDefaultAssign* asCBlockAssertion_isDefaultAssign(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isDefaultAssign)
				return static_cast<CBlockAssertion_isDefaultAssign*>(c);
			return nullptr;
		}
		CBlockNoumStr* asCBlockNoumStr(CBlock* c)
		{
			if (c->type() == BlockType::BlockNoumStr)
				return static_cast<CBlockNoumStr*>(c);
			return nullptr;
		}
		CBlockKind_InstanceVariable* asCKind_InstanceVariable(CBlock* c)
		{
			if (c->type() == BlockType::BlockKind_InstanceVariable)
				return static_cast<CBlockKind_InstanceVariable*>(c);
			return nullptr;
		}
		CBlockAssertion_isDirectAssign* asCBlockAssertion_isDirectAssign(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isDirectAssign)
				return static_cast<CBlockAssertion_isDirectAssign*>(c);
			return nullptr;
		}
		CBlockAssertion_canBe* asCBlockAssertion_canBe(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_canBe)
				return static_cast<CBlockAssertion_canBe*>(c);
			return nullptr;
		}
		/*CBlockAssertion_is* asCBlockAssertion_is(CBlock* c )
		{
		   if ( c->type() == BlockType::BlockAssertion_is)
			 return static_cast<CBlockAssertion_is*>(c);
		   return nullptr;
		} */
		CBlockIsVerb* asCBlockIsVerb(CBlock* c)
		{
			if (c->type() == BlockType::BlockIsVerb)
				return static_cast<CBlockIsVerb*>(c);
			return nullptr;
		}
		//CBlockAssertion_isActionOf* asCBlockAssertion_isActionOf(CBlock* c)
		//{
		//	if (c->type() == BlockType::BlockAssertion_isActionOf)
		//		return static_cast<CBlockAssertion_isActionOf*>(c);
		//	return nullptr;
		//}
		CBlockIsNotVerb* asCBlockIsNotVerb(CBlock* c)
		{
			if (c->type() == BlockType::BlockIsNotVerb)
				return static_cast<CBlockIsNotVerb*>(c);
			return nullptr;
		}
		CBlockMatchAny* asCBlockMatchAny(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchAny)
				return static_cast<CBlockMatchAny*>(c);
			return nullptr;
		}
		CBlockMatchNamed* asCBlockMatchNamed(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchNamed)
				return static_cast<CBlockMatchNamed*>(c);
			return nullptr;
		}
		CBlockMatchList* asCBlockMatchList(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchList)
				return static_cast<CBlockMatchList*>(c);
			return nullptr;
		}
		CBlockMatchDirectIsNot* asCBlockMatchDirectIsNot(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchDirectIsNot)
				return static_cast<CBlockMatchDirectIsNot*>(c);
			return nullptr;
		}
		CBlockMatchKind* asCBlockMatchKind(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchKind)
				return static_cast<CBlockMatchKind*>(c);
			return nullptr;
		}
		CBlockMatchProperty* asCBlockMatchProperty(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchProperty)
				return static_cast<CBlockMatchProperty*>(c);
			return nullptr;
		}
		CBlockMatchBlock* asCBlockMatchBlock(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchBlock)
				return static_cast<CBlockMatchBlock*>(c);
			return nullptr;
		}
		CBlockMatchOR* asCBlockMatchOR(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchOR)
				return static_cast<CBlockMatchOR*>(c);
			return nullptr;
		}
		CBlockMatchAND* asCBlockMatchAND(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchAND)
				return static_cast<CBlockMatchAND*>(c);
			return nullptr;
		}
		CBlockMatchDirectIs* asCBlockMatchDirectIs(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchDirectIs)
				return static_cast<CBlockMatchDirectIs*>(c);
			return nullptr;
		}
		CBlockMatchIsVerb* asCBlockMatchIsVerb(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchIsVerb)
				return static_cast<CBlockMatchIsVerb*>(c);
			return nullptr;
		}
		CBlockMatchIsNotVerb* asCBlockMatchIsNotVerb(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchIsNotVerb)
				return static_cast<CBlockMatchIsNotVerb*>(c);
			return nullptr;
		}
		CBlockAssertion_isNotDirectAssign* asCBlockAssertion_isNotDirectAssign(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isNotDirectAssign)
				return static_cast<CBlockAssertion_isNotDirectAssign*>(c);
			return nullptr;
		}
		CBlockMatchNoum* asCBlockMatchNoum(CBlock* c)
		{
			if (c->type() == BlockType::BlockMatchNoum)
				return static_cast<CBlockMatchNoum*>(c);
			return nullptr;
		}
		CBlockBooleanAND* asCBlockBooleanAND(CBlock* c)
		{
			if (c->type() == BlockType::BlockBooleanAND)
				return static_cast<CBlockBooleanAND*>(c);
			return nullptr;
		}
		CBlockVerb* asCBlockVerb(CBlock* c)
		{
			if (c->type() == BlockType::BlockVerb)
				return static_cast<CBlockVerb*>(c);
			return nullptr;
		}
		CBlockBooleanOR* asCBlockBooleanOR(CBlock* c)
		{
			if (c->type() == BlockType::BlockBooleanOR)
				return static_cast<CBlockBooleanOR*>(c);
			return nullptr;
		}
		CBlockBooleanNOT* asCBlockBooleanNOT(CBlock* c)
		{
			if (c->type() == BlockType::BlockBooleanNOT)
				return static_cast<CBlockBooleanNOT*>(c);
			return nullptr;
		}
		CBlockSelector_All* asCBlockSelector_All(CBlock* c)
		{
			if (c->type() == BlockType::BlockSelector_All)
				return static_cast<CBlockSelector_All*>(c);
			return nullptr;
		}
		CBlockSelector_Any* asCBlockSelector_Any(CBlock* c)
		{
			if (c->type() == BlockType::BlockSelector_Any)
				return static_cast<CBlockSelector_Any*>(c);
			return nullptr;
		}
		CBlockStaticDispatch* asCBlockStaticDispatch(CBlock* c)
		{
			if (c->type() == BlockType::BlockStaticDispatch)
				return static_cast<CBlockStaticDispatch*>(c);
			return nullptr;
		}
		 
	 
		CBlockVariableNamed* asCBlockVariableNamed(CBlock* c)
		{
			if (c->type() == BlockType::BlockVariableNamed)
				return static_cast<CBlockVariableNamed*>(c);
			return nullptr;
		}
		CBlockUnderstandDynamic* asCBlockUnderstandDynamic(CBlock* c)
		{
			if (c->type() == BlockType::BlockUnderstandDynamic)
				return static_cast<CBlockUnderstandDynamic*>(c);
			return nullptr;
		}
		CBlockUnderstandStatic* asCBlockUnderstandStatic(CBlock* c)
		{
			if (c->type() == BlockType::BlockUnderstandStatic)
				return static_cast<CBlockUnderstandStatic*>(c);
			return nullptr;
		}
		CBlockToDecideWhether* asCBlockToDecideWhether(CBlock* c)
		{
			if (c->type() == BlockType::BlockToDecideWhether)
				return static_cast<CBlockToDecideWhether*>(c);
			return nullptr;
		}
		CBlockToDecideIf* asCBlockToDecideIf(CBlock* c)
		{
			if (c->type() == BlockType::BlockToDecideIf)
				return static_cast<CBlockToDecideIf*>(c);
			return nullptr;
		}
		CBlockToDecideWhat_FirstNoum* asCBlockToDecideWhat_FirstNoum(CBlock* c)
		{
			if (c->type() == BlockType::BlockToDecideWhat_FirstNoum)
				return static_cast<CBlockToDecideWhat_FirstNoum*>(c);
			return nullptr;
		}
		CBlockToDecideWhat* asCBlockToDecideWhat(CBlock* c)
		{
			if (c->type() == BlockType::BlockToDecideWhat)
				return static_cast<CBlockToDecideWhat*>(c);
			return nullptr;
		}
		CBlockToDecideOn* asCBlockToDecideOn(CBlock* c)
		{
			if (c->type() == BlockType::BlockToDecideOn)
				return static_cast<CBlockToDecideOn*>(c);
			return nullptr;
		}
		CBlockActionApply* asCBlockActionApply(CBlock* c)
		{
			if (c->type() == BlockType::BlockActionApply)
				return static_cast<CBlockActionApply*>(c);
			return nullptr;
		}
		CBlockKindOfName* asCBlockKindOfName(CBlock* c)
		{
			if (c->type() == BlockType::BlockKindOfName)
				return static_cast<CBlockKindOfName*>(c);
			return nullptr;
		}
		CBlockArgumentInput* asCBlockArgumentInput(CBlock* c)
		{
			if (c->type() == BlockType::BlockArgumentInput)
				return static_cast<CBlockArgumentInput*>(c);
			return nullptr;
		}
		CBlockText* asCBlockText(CBlock* c)
		{
			if (c->type() == BlockType::BlockText)
				return static_cast<CBlockText*>(c);
			return nullptr;
		}
		CBlockInstanceAnonymous* asCBlockInstanceAnonymous(CBlock* c)
		{
			if (c->type() == BlockType::BlockInstanceAnonymous)
				return static_cast<CBlockInstanceAnonymous*>(c);
			return nullptr;
		}
		CBlockSimetricRelation* asCBlockSimetricRelation(CBlock* c)
		{
			if (c->type() == BlockType::BlockSimetricRelation)
				return static_cast<CBlockSimetricRelation*>(c);
			return nullptr;
		}
		CBlockASimetricRelation* asCBlockASimetricRelation(CBlock* c)
		{
			if (c->type() == BlockType::BlockASimetricRelation)
				return static_cast<CBlockASimetricRelation*>(c);
			return nullptr;
		}
		CBlockRelationInstance* asCBlockRelationInstance(CBlock* c)
		{
			if (c->type() == BlockType::BlockRelationInstance)
				return static_cast<CBlockRelationInstance*>(c);
			return nullptr;
		}
		CBlockVerbRelation* asCBlockVerbDirectRelation(CBlock* c)
		{
			if (c->type() == BlockType::BlockVerbDirectRelation)
				return static_cast<CBlockVerbRelation*>(c);
			return nullptr;
		}

		CBlockVerbRelation* asCBlockVerbReverseRelation(CBlock* c)
		{
			if (c->type() == BlockType::BlockVerbReverseRelation)
				return static_cast<CBlockVerbRelation*>(c);
			return nullptr;
		}

		CBlockAssertion_isConstantAssign* asCBlockAssertion_isConstantAssign(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isConstantAssign)
				return static_cast<CBlockAssertion_isConstantAssign*>(c);
			return nullptr;
		}
		CBlockAssertion_isForbiddenAssign* asCBlockAssertion_isForbiddenAssign(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isForbiddenAssign)
				return static_cast<CBlockAssertion_isForbiddenAssign*>(c);
			return nullptr;
		}
		CBlockAssertion_isVariable* asCBlockAssertion_isVariable(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isVariable)
				return static_cast<CBlockAssertion_isVariable*>(c);
			return nullptr;
		}
		CBlockAssertion_isNamedValueOf* asCBlockAssertion_isNamedValueOf(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isNamedValueOf)
				return static_cast<CBlockAssertion_isNamedValueOf*>(c);
			return nullptr;
		}
		CBlockAssertion_InstanceVariable* asCBlockAssertion_InstanceVariable(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_InstanceVariable)
				return static_cast<CBlockAssertion_InstanceVariable*>(c);
			return nullptr;
		}
		CBlockAssertion_isInstanceOf* asCBlockAssertion_isInstanceOf(CBlock* c)
		{
			if (c->type() == BlockType::BlockAssertion_isInstanceOf)
				return static_cast<CBlockAssertion_isInstanceOf*>(c);
			return nullptr;
		}
		CBlockDinamicDispatch* asCBlockDinamicDispatch(CBlock* c)
		{
			if (c->type() == BlockType::BlockDinamicDispatch)
				return static_cast<CBlockDinamicDispatch*>(c);
			return nullptr;
		}
		CBlockNow* asCBlockNow(CBlock* c)
		{
			if (c->type() == BlockType::BlockNow)
				return static_cast<CBlockNow*>(c);
			return nullptr;
		}

	}

}

