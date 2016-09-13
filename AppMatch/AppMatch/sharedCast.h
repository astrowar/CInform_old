
#include "BlockInterpreter.h"
#include "CBlockAction.h"
#include "CBlockUndestand.h"
#include "CBlockDecideIf.h"
#include "CBlockRelation.h"
#include "BlockInstance.h"
#include "CBlockDumpValues.h"
#include "CBlockCommand.h"
#include "CBlockBoolean.h"

HBlockEnums asHBlockEnums(HBlock* c ); 
HBlockKind asHBlockKind(HBlock* c ); 
HUnresolved asHUnresolved(HBlock* c ); 
HBlockKindOf asHBlockKindOf(HBlock* c ); 
HBlockKindAction asHBlockKindAction(HBlock* c ); 
HBlockKindValue asHBlockKindValue(HBlock* c ); 
HBlockListOfKind asHBlockListOfKind(HBlock* c ); 
HBlockNamedValue asHBlockNamedValue(HBlock* c ); 
HBlockVariable asHBlockVariable(HBlock* c ); 
HBlockInstanceVariable asHBlockInstanceVariable(HBlock* c ); 
HBlockList asHBlockList(HBlock* c ); 
HBlockEnums asHBlockEnums(HBlock* c ); 
HBlockProperty asHBlockProperty(HBlock* c ); 
HBlockAssertion_isDefaultAssign asHBlockAssertion_isDefaultAssign(HBlock* c ); 
HBlockNoum asHBlockNoum(HBlock* c ); 
HBlockKind_InstanceVariable asHBlockKind_InstanceVariable(HBlock* c ); 
HBlockAssertion_isDirectAssign asHBlockAssertion_isDirectAssign(HBlock* c ); 
HBlockAssertion_canBe asHBlockAssertion_canBe(HBlock* c ); 
HBlockAssertion_is asHBlockAssertion_is(HBlock* c ); 
HBlockIsVerb asHBlockIsVerb(HBlock* c ); 
HBlockAssertion_isActionOf asHBlockAssertion_isActionOf(HBlock* c ); 
HBlockIsNotVerb asHBlockIsNotVerb(HBlock* c ); 
HBlockMatchAny asHBlockMatchAny(HBlock* c ); 
HBlockMatchNamed asHBlockMatchNamed(HBlock* c ); 
HBlockMatchList asHBlockMatchList(HBlock* c ); 
HBlockMatchDirectIsNot asHBlockMatchDirectIsNot(HBlock* c ); 
HBlockMatchKind asHBlockMatchKind(HBlock* c ); 
HBlockMatchProperty asHBlockMatchProperty(HBlock* c ); 
HBlockMatchBlock asHBlockMatchBlock(HBlock* c ); 
HBlockMatchOR asHBlockMatchOR(HBlock* c ); 
HBlockMatchAND asHBlockMatchAND(HBlock* c ); 
HBlockMatchDirectIs asHBlockMatchDirectIs(HBlock* c ); 
HBlockMatchIsVerb asHBlockMatchIsVerb(HBlock* c ); 
HBlockMatchIsNotVerb asHBlockMatchIsNotVerb(HBlock* c ); 
HBlockAssertion_isNotDirectAssign asHBlockAssertion_isNotDirectAssign(HBlock* c ); 
HBlockMatchNoum asHBlockMatchNoum(HBlock* c ); 
HBlockBooleanAND asHBlockBooleanAND(HBlock* c ); 
HBlockVerb asHBlockVerb(HBlock* c ); 
HBlockBooleanOR asHBlockBooleanOR(HBlock* c ); 
HBlockBooleanNOT asHBlockBooleanNOT(HBlock* c ); 
HBlockSelector_All asHBlockSelector_All(HBlock* c ); 
HBlockSelector_Any asHBlockSelector_Any(HBlock* c ); 
HBlockStaticDispatch asHBlockStaticDispatch(HBlock* c ); 
HBlockAction asHBlockAction(HBlock* c ); 
HBlockActionCall asHBlockActionCall(HBlock* c ); 
HVariableNamed asHVariableNamed(HBlock* c ); 
HBlockUnderstandDynamic asHBlockUnderstandDynamic(HBlock* c ); 
HBlockUnderstandStatic asHBlockUnderstandStatic(HBlock* c ); 
HBlockToDecideWhether asHBlockToDecideWhether(HBlock* c ); 
HBlockToDecideIf asHBlockToDecideIf(HBlock* c ); 
HBlockToDecideWhat_FirstNoum asHBlockToDecideWhat_FirstNoum(HBlock* c ); 
HBlockToDecideWhat asHBlockToDecideWhat(HBlock* c ); 
HBlockToDecideOn asHBlockToDecideOn(HBlock* c ); 
HBlockActionApply asHBlockActionApply(HBlock* c ); 
HBlockKindOfName asHBlockKindOfName(HBlock* c ); 
HBlockArgumentInput asHBlockArgumentInput(HBlock* c ); 
HBlockText asHBlockText(HBlock* c ); 
HBlockInstance asHBlockInstance(HBlock* c ); 
HBlockSimetricRelation asHBlockSimetricRelation(HBlock* c ); 
HBlockASimetricRelation asHBlockASimetricRelation(HBlock* c ); 
HBlockRelationInstance asHBlockRelationInstance(HBlock* c ); 
HBlockVerbRelation asHBlockVerbRelation(HBlock* c ); 
HBlockAssertion_isConstantAssign asHBlockAssertion_isConstantAssign(HBlock* c ); 
HBlockAssertion_isForbiddenAssign asHBlockAssertion_isForbiddenAssign(HBlock* c ); 
HBlockAssertion_isVariable asHBlockAssertion_isVariable(HBlock* c ); 
HBlockAssertion_isNamedValueOf asHBlockAssertion_isNamedValueOf(HBlock* c ); 
HBlockAssertion_InstanceVariable asHBlockAssertion_InstanceVariable(HBlock* c ); 
HBlockAssertion_isInstanceOf asHBlockAssertion_isInstanceOf(HBlock* c ); 
HBlockDinamicDispatch asHBlockDinamicDispatch(HBlock* c ); 
HBlockNow asHBlockNow(HBlock* c ); 
