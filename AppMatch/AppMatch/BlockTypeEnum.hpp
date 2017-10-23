//
// Created by Eraldo Rangel on 01/10/16.
//

#ifndef APPMATCH_BLOCKTYPEENUM_HPP
#define APPMATCH_BLOCKTYPEENUM_HPP

enum BlockType {
	BlockKind,
	Unresolved,
	BlockKindOf,
	BlockKindNamed,
	BlockKindAction,
	BlockKindThing,
	BlockKindValue,
	BlockListOfKind,
	BlockNamedValue,
	BlockVariable,
	BlockInstanceVariable,
	BlockList,
	BlockList_OR,
	BlockList_AND,
	BlockEnums,
	BlockProperty,
	BlockAssertion_isDefaultAssign,
	BlockKindReference,
	BlockNoum,
	BlockKind_InstanceVariable,
	BlockAssertion_isDirectAssign,
	BlockAssertion_canBe,
	BlockAssertion_isKindOf,
	BlockIsVerb,
	BlockAssertion_isActionOf,
	BlockIsNotVerb,
	BlockMatchAny,
	BlockMatchNamed,
	BlockMatchList,
	BlockMatchDirectIsNot,
	BlockMatchKind,
	BlockMatchProperty,
	BlockMatchBlock,
	BlockMatchOR,
	BlockMatchAND,
	BlockMatchDirectIs,
	BlockMatchIsVerb,
	BlockMatchIsNotVerb,
	BlockAssertion_isNotDirectAssign,
	BlockMatchNoum,
	BlockBooleanAND,
	BlockVerb,
	BlockBooleanOR,
	BlockBooleanNOT,
	BlockSelector_All,
	BlockSelector_Any,
	BlockStaticDispatch,
	BlockAction,
	BlockActionNamed,
	BlockActionInstance,
	BlockActionCall,
	VariableNamed,
	BlockUnderstandDynamic,
	BlockUnderstandStatic,
	BlockToDecideWhether,
	BlockToDecideIf,
	BlockToDecideWhat_FirstNoum,
	BlockToDecideWhat,
	BlockToDecideOn,
	BlockActionApply,
	BlockKindOfName,
	BlockArgumentInput,
	BlockText,
	BlockInstance,
	BlockSimetricRelation,
	BlockASimetricRelation,
	BlockRelationInstance,
	BlockVerbDirectRelation,
	BlockVerbReverseRelation,
	BlockAssertion_isConstantAssign,
	BlockAssertion_isForbiddenAssign,
	BlockAssertion_isVariable,
	BlockAssertion_isNamedValueOf,
	BlockAssertion_InstanceVariable,
	BlockAssertion_isInstanceOf,
	BlockDinamicDispatch,
	BlockNow,
	BlockControlIF,
	BlockControlToken,
	BlockComandList,
	BlockControlSelect,
	BlockControlSelectItem,
	BlockConditionalRelation,
	BlockMatchNOT,
	BlockMatchWhich,
	BlockMatchWhichNot,
	BlockBooleanValue,
	BlockRelationLookup,
	BlockVerbLookup,
	BlockSelector_Where,
	BlockEvery,
	BlockVerbConjugation,
	BlockVerbAdapt,
	BlockMatchActionCall,
	BlockEventHandle, 
	BlockIntegerNumber,
	BlockFactionalNumber,
	BlockExecutionResultFlag,
	BlockControlForEach,
	BlockAssertion_isLocalVariable,
	BlockRelationArguments,
	BlockSelectorAND,
	BlockAssert,
	BlockComposition,
	BlockCompositionList,
	BlockCompositionPhrase,
	BlockCompositionRelation,
	BlockNothing
};
#endif //APPMATCH_BLOCKTYPEENUM_HPP
