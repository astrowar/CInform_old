// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "sharedCast.hpp"
#include "CBlockNumber.hpp"


namespace CBlocking
{
	namespace DynamicCasting
	{




		HBlockEnums asHBlockEnums(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockEnums)
				return  std::static_pointer_cast<CBlockEnums>(c);
			return nullptr;
		}
		HBlockKind asHBlockKind(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;

			auto t = c->type();
			if (t == BlockType::BlockKindValue ||
				t == BlockType::BlockKindThing ||
				t == BlockType::BlockListOfKind)
				return std::static_pointer_cast<CBlockKind>(c);
			if (HBlockComposition comp = asHBlockComposition(c))
			{
				return comp;
			}
			return nullptr;
		}
		HUnresolved asHUnresolved(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::Unresolved)
				return std::static_pointer_cast<CUnresolved>(c);
			return nullptr;
		}
		HBlockKindOf asHBlockKindOf(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindOf)
				return std::static_pointer_cast<CBlockKindOf>(c);
			return nullptr;
		}
		HBlockKindAction asHBlockKindAction(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindAction)
				return std::static_pointer_cast<CBlockKindAction>(c);
			return nullptr;
		}
		HBlockKindValue asHBlockKindValue(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindValue)
				return std::static_pointer_cast<CBlockKindValue>(c);
			return nullptr;
		}
	 
		HBlockNamedValue asHBlockNamedValue(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockNamedValue)
				return std::static_pointer_cast<CBlockNamedValue>(c);
			return nullptr;
		}
	 

		
		HBlockAssertion_isLocalVariable asHBlockAssertion_isLocalVariable(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isLocalVariable)
				return std::static_pointer_cast<CBlockAssertion_isLocalVariable>(c);
			return nullptr;
		}

		HBlockInstanceVariable asHBlockInstanceVariable(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockInstanceVariable)
				return std::static_pointer_cast<CBlockInstanceVariable>(c);
			return nullptr;
		}


		HBlockList_AND asHBlockList_AND(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockList_AND)
				return std::static_pointer_cast<CBlockList_AND>(c);
			return nullptr;
		}

		HBlockList asHBlockList(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockList)
				return std::static_pointer_cast<CBlockList>(c);
			return nullptr;
		}

		
 

		HBlockList_OR asHBlockList_OR(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockList_OR)
				return std::static_pointer_cast<CBlockList_OR>(c);
			return nullptr;
		}

		HBlockProperty asHBlockProperty(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockProperty)
				return std::static_pointer_cast<CBlockProperty>(c);
			return nullptr;
		}
		HBlockAssertion_isDefaultAssign asHBlockAssertion_isDefaultAssign(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isDefaultAssign)
				return std::static_pointer_cast<CBlockAssertion_isDefaultAssign>(c);
			return nullptr;
		}

		 
		HBlockNothing asHBlockNothing(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockNothing)
				return std::static_pointer_cast<CBlockNothing>(c);
			return nullptr;
		}

 
		HBlockComposition asHBlockComposition(CBlocking::HBlock c)
		{
			if (c != nullptr && (c->type() == BlockType::BlockCompositionList || c->type() == BlockType::BlockCompositionPhrase || c->type() == BlockType::BlockCompositionRelation ) )
				return std::static_pointer_cast<CBlockComposition>(c);
			return nullptr;
		}

		HBlockCompositionList asHBlockCompositionList(CBlocking::HBlock c)
		{
			if (c != nullptr && (c->type() == BlockType::BlockCompositionList  ))
				return std::static_pointer_cast<CBlockCompositionList>(c);
			return nullptr;
		}

		HBlockCompositionPhrase asHBlockCompositionPhrase(CBlocking::HBlock c)
		{
			if (c != nullptr && (  c->type() == BlockType::BlockCompositionPhrase))
				return std::static_pointer_cast<CBlockCompositionPhrase>(c);
			return nullptr;
		}

		HBlockCompositionRelation asHBlockCompositionRelation(CBlocking::HBlock c)
		{
			if (c != nullptr && (  c->type() == BlockType::BlockCompositionRelation))
				return std::static_pointer_cast<CBlockCompositionRelation>(c);
			return nullptr;
		}

		HBlockKindNamed  asHBlockKindNamed(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindNamed)
				return std::static_pointer_cast<CBlockKindNamed>(c);
			return nullptr;
		}

		HBlockNoum asHBlockNoum(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockNoum)
				return std::static_pointer_cast<CBlockNoum>(c);
			return nullptr;
		}
		HBlockKind_InstanceVariable asHBlockKind_InstanceVariable(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKind_InstanceVariable)
				return std::static_pointer_cast<CBlockKind_InstanceVariable>(c);
			return nullptr;
		}
		HBlockAssertion_isDirectAssign asHBlockAssertion_isDirectAssign(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isDirectAssign)
				return std::static_pointer_cast<CBlockAssertion_isDirectAssign>(c);
			return nullptr;
		}
		HBlockAssertion_canBe asHBlockAssertion_canBe(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_canBe)
				return std::static_pointer_cast<CBlockAssertion_canBe>(c);
			return nullptr;
		}
		HBlockAssertion_is asHBlockAssertion_is(CBlocking::HBlock c) {
			if (c == nullptr) return nullptr;
			auto t = c->type();

			if (t == BlockType::BlockAssertion_canBe ||
				t == BlockType::BlockAssertion_isKindOf ||
				t == BlockType::BlockAssertion_isInstanceOf ||

				t == BlockType::BlockAssertion_isNamedValueOf ||
				t == BlockType::BlockAssertion_isDefaultAssign ||
				t == BlockType::BlockAssertion_isConstantAssign ||
				t == BlockType::BlockAssertion_isForbiddenAssign ||
				t == BlockType::BlockAssertion_isDirectAssign ||
				t == BlockType::BlockAssertion_isNotDirectAssign ||
				t == BlockType::BlockAssertion_isActionOf ||
				t == BlockType::BlockIsVerb ||
				t == BlockType::BlockIsNotVerb)
				return std::static_pointer_cast<CBlockAssertion_is>(c);
			return nullptr;
		}


		HBlockIsVerb asHBlockIsVerb(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockIsVerb)
				return std::static_pointer_cast<CBlockIsVerb>(c);
			return nullptr;
		}
		HBlockAssertion_isActionOf asHBlockAssertion_isActionOf(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isActionOf)
				return std::static_pointer_cast<CBlockAssertion_isActionOf>(c);
			return nullptr;
		}
		HBlockIsNotVerb asHBlockIsNotVerb(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockIsNotVerb)
				return std::static_pointer_cast<CBlockIsNotVerb>(c);
			return nullptr;
		}
		HBlockMatchAny asHBlockMatchAny(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchAny)
				return std::static_pointer_cast<CBlockMatchAny>(c);
			return nullptr;
		}
		HBlockMatchNamed asHBlockMatchNamed(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchNamed)
				return std::static_pointer_cast<CBlockMatchNamed>(c);
			return nullptr;
		}
		HBlockMatchList asHBlockMatchList(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchList)
				return std::static_pointer_cast<CBlockMatchList>(c);
			return nullptr;
		}
		HBlockMatchDirectIsNot asHBlockMatchDirectIsNot(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchDirectIsNot)
				return std::static_pointer_cast<CBlockMatchDirectIsNot>(c);
			return nullptr;
		}
		HBlockMatchKind asHBlockMatchKind(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchKind)
				return std::static_pointer_cast<CBlockMatchKind>(c);
			return nullptr;
		}
		HBlockMatchProperty asHBlockMatchProperty(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchProperty)
				return std::static_pointer_cast<CBlockMatchProperty>(c);
			return nullptr;
		}
		HBlockMatchBlock asHBlockMatchBlock(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchBlock)
				return std::static_pointer_cast<CBlockMatchBlock>(c);
			return nullptr;
		}
		HBlockMatchOR asHBlockMatchOR(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchOR)
				return std::static_pointer_cast<CBlockMatchOR>(c);
			return nullptr;
		}
		HBlockMatchAND asHBlockMatchAND(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchAND)
				return std::static_pointer_cast<CBlockMatchAND>(c);
			return nullptr;
		}

		HBlockMatchNOT asHBlockMatchNOT(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchNOT)
				return std::static_pointer_cast<CBlockMatchNOT>(c);
			return nullptr;
		}

		HBlockMatch asHBlockMatch(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();

			if (t == BlockType::BlockMatchAny ||
				t == BlockType::BlockMatchAND ||
				t == BlockType::BlockMatchOR ||
				t == BlockType::BlockMatchBlock ||
				t == BlockType::BlockMatchDirectIs ||
				t == BlockType::BlockMatchDirectIsNot ||
				t == BlockType::BlockMatchIsNotVerb ||
				t == BlockType::BlockMatchIsVerb ||
				t == BlockType::BlockMatchKind ||
				t == BlockType::BlockMatchList ||
				t == BlockType::BlockMatchNamed ||
				t == BlockType::BlockMatchNoum ||
				t == BlockType::BlockMatchWhich ||
				t == BlockType::BlockMatchWhichNot ||			 
				t == BlockType::BlockMatchProperty)
				return std::static_pointer_cast<CBlockMatch>(c);
			return nullptr;
		}

		HBlockMatchDirectIs asHBlockMatchDirectIs(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchDirectIs)
				return std::static_pointer_cast<CBlockMatchDirectIs>(c);
			return nullptr;
		}

		HBlockMatchWhich asHBlockMatchWhich(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchWhich)
				return std::static_pointer_cast<CBlockMatchWhich>(c);
			return nullptr;
		}

		HBlockMatchWhichNot asHBlockMatchWhichNot(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchWhichNot)
				return std::static_pointer_cast<CBlockMatchWhichNot>(c);
			return nullptr;
		}


		HBlockMatchIsVerb asHBlockMatchIsVerb(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchIsVerb)
				return std::static_pointer_cast<CBlockMatchIsVerb>(c);
			return nullptr;
		}
		HBlockMatchIsNotVerb asHBlockMatchIsNotVerb(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchIsNotVerb)
				return std::static_pointer_cast<CBlockMatchIsNotVerb>(c);
			return nullptr;
		}
		HBlockAssertion_isNotDirectAssign asHBlockAssertion_isNotDirectAssign(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isNotDirectAssign)
				return std::static_pointer_cast<CBlockAssertion_isNotDirectAssign>(c);
			return nullptr;
		}
		HBlockMatchNoum asHBlockMatchNoum(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockMatchNoum)
				return std::static_pointer_cast<CBlockMatchNoum>(c);
			return nullptr;
		}
		HBlockBooleanAND asHBlockBooleanAND(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockBooleanAND)
				return std::static_pointer_cast<CBlockBooleanAND>(c);
			return nullptr;
		}
		HBlockVerb asHBlockVerb(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockVerb)
				return std::static_pointer_cast<CBlockVerb>(c);
			return nullptr;
		}
		HBlockVerbAdapt asHBlockVerbAdapt(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockVerbAdapt)
				return std::static_pointer_cast<CBlockVerbAdapt>(c);
			return nullptr;
		}

		HBlockEventHandle asHBlockEventHandle(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockEventHandle)
				return std::static_pointer_cast<CBlockEventHandle>(c);
			return nullptr;
		}





		HBlockBooleanOR asHBlockBooleanOR(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockBooleanOR)
				return std::static_pointer_cast<CBlockBooleanOR>(c);
			return nullptr;
		}
		HBlockBooleanNOT asHBlockBooleanNOT(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockBooleanNOT)
				return std::static_pointer_cast<CBlockBooleanNOT>(c);
			return nullptr;
		}
		HBlockSelector_All asHBlockSelector_All(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockSelector_All)
				return std::static_pointer_cast<CBlockSelector_All>(c);
			return nullptr;
		}
		HBlockSelector_Any asHBlockSelector_Any(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockSelector_Any)
				return std::static_pointer_cast<CBlockSelector_Any>(c);
			return nullptr;
		}
		HBlockStaticDispatch asHBlockStaticDispatch(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockStaticDispatch)
				return std::static_pointer_cast<CBlockStaticDispatch>(c);
			return nullptr;
		}
		HBlockAction asHBlockAction(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();

			if (t == BlockType::BlockAction || t == BlockType::BlockActionInstance || t == BlockType::BlockActionNamed)
			{
				return std::static_pointer_cast<CBlockAction>(c);
			}
			return nullptr;
		}

		HBlockActionInstance asHBlockActionInstance(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockActionInstance)
				return std::static_pointer_cast<CBlockActionInstance>(c);
			return nullptr;
		}

		HBlockActionNamed asHBlockActionNamed(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockActionNamed)
				return std::static_pointer_cast<CBlockActionNamed>(c);
			return nullptr;
		}

		HBlockActionCall asHBlockActionCall(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockActionCall)
				return std::static_pointer_cast<CBlockActionCall>(c);
			return nullptr;
		}

		HBlockActionCallNamed asHBlockActionCallNamed(CBlocking::HBlock c)
		{
					if (c != nullptr && c->type() == BlockType::BlockActionCallNamed )
						return std::static_pointer_cast<CBlockActionCallNamed>(c);
					return nullptr;
				}


		HVariableNamed asHVariableNamed(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::VariableNamed)
				return std::static_pointer_cast<CVariableNamed>(c);
			return nullptr;
		}
		HBlockUnderstandDynamic asHBlockUnderstandDynamic(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockUnderstandDynamic)
				return std::static_pointer_cast<CBlockUnderstandDynamic>(c);
			return nullptr;
		}
		HBlockUnderstandStatic asHBlockUnderstandStatic(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockUnderstandStatic)
				return std::static_pointer_cast<CBlockUnderstandStatic>(c);
			return nullptr;
		}
		HBlockToDecideWhether asHBlockToDecideWhether(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockToDecideWhether)
				return std::static_pointer_cast<CBlockToDecideWhether>(c);
			return nullptr;
		}
		HBlockToDecideIf asHBlockToDecideIf(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockToDecideIf)
				return std::static_pointer_cast<CBlockToDecideIf>(c);
			return nullptr;
		}
		HBlockToDecideWhat_FirstNoum asHBlockToDecideWhat_FirstNoum(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockToDecideWhat_FirstNoum)
				return std::static_pointer_cast<CBlockToDecideWhat_FirstNoum>(c);
			return nullptr;
		}
		HBlockToDecideWhat asHBlockToDecideWhat(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockToDecideWhat)
				return std::static_pointer_cast<CBlockToDecideWhat>(c);
			return nullptr;
		}
		HBlockToDecideOn asHBlockToDecideOn(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockToDecideOn)
				return std::static_pointer_cast<CBlockToDecideOn>(c);
			return nullptr;
		}

		HBlockBooleanValue asHBlockBooleanValue(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockBooleanValue)
				return std::static_pointer_cast<CBlockBooleanValue>(c);
			return nullptr;
		}


		HBlockNumber asHBlockNumber(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();
			if (t == BlockType::BlockIntegerNumber ||
				t == BlockType::BlockFactionalNumber)
				return std::static_pointer_cast<CBlockNumber>(c);
			return nullptr;
		}
		HBlockToDecide asHBlockToDecide(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();
			if (t == BlockType::BlockToDecideIf ||
				t == BlockType::BlockToDecideOn ||
				t == BlockType::BlockToDecideWhat ||
				t == BlockType::BlockToDecideWhat_FirstNoum ||
				t == BlockType::BlockToDecideWhether)
				return std::static_pointer_cast<CBlockToDecide>(c);
			return nullptr;
		}
		HBlockActionApply asHBlockActionApply(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockActionApply)
				return std::static_pointer_cast<CBlockActionApply>(c);
			return nullptr;
		}
		HBlockKindOfName asHBlockKindOfName(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindOfName)
				return std::static_pointer_cast<CBlockKindOfName>(c);
			return nullptr;
		}
		HBlockKindThing asHBlockKindThing(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockKindThing)
				return std::static_pointer_cast<CBlockKindThing>(c);
			return nullptr;
		}

		HBlockArgumentInput asHBlockArgumentInput(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockArgumentInput)
				return std::static_pointer_cast<CBlockArgumentInput>(c);
			return nullptr;
		}
		HBlockText asHBlockText(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockText)
				return std::static_pointer_cast<CBlockText>(c);
			return nullptr;
		}
		HBlockInstance asHBlockInstance(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockInstance)
				return std::static_pointer_cast<CBlockInstance>(c);
			return nullptr;
		}

		HBlockRelationBase asHBlockRelationBase(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();

			if (t == BlockType::BlockSimetricRelation ||
				t == BlockType::BlockASimetricRelation  )
				return std::static_pointer_cast<CBlockRelationBase>(c);
			return nullptr;

		}
		HBlockSimetricRelation asHBlockSimetricRelation(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockSimetricRelation)
				return std::static_pointer_cast<CBlockSimetricRelation>(c);
			return nullptr;
		}
		HBlockASimetricRelation asHBlockASimetricRelation(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockASimetricRelation)
				return std::static_pointer_cast<CBlockASimetricRelation>(c);
			return nullptr;
		}
		HBlockRelationInstance asHBlockRelationInstance(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockRelationInstance)
				return std::static_pointer_cast<CBlockRelationInstance>(c);
			return nullptr;
		}

		HBlockRelationArguments  asHBlockRelationArguments(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockRelationArguments )
				return std::static_pointer_cast<CBlockRelationArguments>(c);
			return nullptr;
		}

		HBlockVerbDirectRelation asHBlockVerbDirectRelation(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockVerbDirectRelation)
				return std::static_pointer_cast<CBlockVerbDirectRelation>(c);
			return nullptr;
		}

		HBlockVerbReverseRelation asHBlockVerbReverseRelation(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockVerbReverseRelation)
				return std::static_pointer_cast<CBlockVerbReverseRelation>(c);
			return nullptr;
		}

		HBlockVerbRelation asHBlockVerbRelation(CBlocking::HBlock c)
		{
			if (c == nullptr) return nullptr;
			auto t = c->type();

			if (t == BlockType::BlockVerbDirectRelation ||
				t == BlockType::BlockVerbReverseRelation)
				return std::static_pointer_cast<CBlockVerbRelation>(c);
			return nullptr;
		}



		HBlockAssertion_isConstantAssign asHBlockAssertion_isConstantAssign(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isConstantAssign)
				return std::static_pointer_cast<CBlockAssertion_isConstantAssign>(c);
			return nullptr;
		}
		HBlockAssertion_isForbiddenAssign asHBlockAssertion_isForbiddenAssign(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isForbiddenAssign)
				return std::static_pointer_cast<CBlockAssertion_isForbiddenAssign>(c);
			return nullptr;
		}
		HBlockAssertion_isVariable asHBlockAssertion_isVariable(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isVariable)
				return std::static_pointer_cast<CBlockAssertion_isVariable>(c);
			return nullptr;
		}
		HBlockAssertion_isNamedValueOf asHBlockAssertion_isNamedValueOf(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isNamedValueOf)
				return std::static_pointer_cast<CBlockAssertion_isNamedValueOf>(c);
			return nullptr;
		}
		HBlockAssertion_InstanceVariable asHBlockAssertion_InstanceVariable(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_InstanceVariable)
				return std::static_pointer_cast<CBlockAssertion_InstanceVariable>(c);
			return nullptr;
		}
		HBlockAssertion_isInstanceOf asHBlockAssertion_isInstanceOf(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockAssertion_isInstanceOf)
				return std::static_pointer_cast<CBlockAssertion_isInstanceOf>(c);
			return nullptr;
		}
		HBlockDinamicDispatch asHBlockDinamicDispatch(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockDinamicDispatch)
				return std::static_pointer_cast<CBlockDinamicDispatch>(c);
			return nullptr;
		}
		HBlockNow asHBlockNow(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockNow)
				return std::static_pointer_cast<CBlockNow>(c);
			return nullptr;
		}

		HBlockEvery asHBlockEvery(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockEvery)
				return std::static_pointer_cast<CBlockEvery>(c);
			return nullptr;
		}

		HBlockControlToken asHBlockControlToken(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockControlToken)
				return std::static_pointer_cast<CBlockControlToken>(c);
			return nullptr;
		}

	 

		HBlockControlSelect asHBlockControlSelect(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockControlSelect)
				return std::static_pointer_cast<CBlockControlSelect>(c);
			return nullptr;
		}


		HBlockControlSelectItem asHBlockControlSelectItem(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockControlSelectItem)
				return std::static_pointer_cast<CBlockControlSelectItem>(c);
			return nullptr;
		}

		HBlockComandList asHBlockComandList(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockComandList)
				return std::static_pointer_cast<CBlockComandList>(c);
			return nullptr;
		}
		HBlockControlIF asHBlockControlIF(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockControlIF)
				return std::static_pointer_cast<CBlockControlIF>(c);
			return nullptr;
		}

	 
		HBlockControlForEach asHBlockControlForEach(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockControlForEach )
				return std::static_pointer_cast<CBlockControlForEach>(c);
			return nullptr;
		}

		HBlockRelationLookup asHBlockRelationLookup(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockRelationLookup)
				return std::static_pointer_cast<CBlockRelationLookup>(c);
			return nullptr;
		}

		HBlockVerbLookup asHBlockVerbLookup(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockVerbLookup)
				return std::static_pointer_cast<CBlockVerbLookup>(c);
			return nullptr;
		}
		HBlockSelectorAND asHBlockSelectorAND(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockSelectorAND)
				return std::static_pointer_cast<CBlockSelectorAND>(c);
			return nullptr;
		}
		

		HBlockSelector_Where asHBlockSelector_Where(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockSelector_Where)
				return std::static_pointer_cast<CBlockSelector_Where>(c);
			return nullptr;
		}




		HBlockExecutionResultFlag asHBlockExecutionResultFlag(CBlocking::HBlock c)
		{
			if (c != nullptr && c->type() == BlockType::BlockExecutionResultFlag)
				return std::static_pointer_cast<CBlockExecutionResultFlag>(c);
			return nullptr;
		}


		HVariableSlotEnum  asHVariableSlotEnum(HVariableSlot c)
		{
			if (c != nullptr && c->type() == VarSlotType::EnumSlot)
				return std::static_pointer_cast<CVariableSlotEnum>(c);
			return nullptr;
		}

		HVariableSlotBool  asHVariableSlotBool(HVariableSlot c)
		{
			if (c != nullptr && c->type() == VarSlotType::BoolSlot)
				return std::static_pointer_cast<CVariableSlotBool>(c);
			return nullptr;
		}


	}
}

 
