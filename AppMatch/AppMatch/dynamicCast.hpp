#include "BlockInterpreter.hpp"
#include "CBlockAction.hpp"
#include "CBlockUndestand.hpp"
#include "CBlockDecideIf.hpp"
#include "CBlockRelation.hpp"
#include "BlockInstance.hpp"
#include "CBlockDumpValues.hpp"
#include "CBlockCommand.hpp"
#include "CBlockBoolean.hpp"

namespace CBlocking
{
	namespace DynamicCasting
	{

		CBlockEnums* asCBlockEnum(CBlock* c);
		CBlockKind* asCBlockKind(CBlock* c);
		CUnresolved* asCBlockUnresolved(CBlock* c);
		CBlockKindOf* asCBlockKindOf(CBlock* c);
		CBlockKindAction* asCBlockKindAction(CBlock* c);
		CBlockKindValue* asCBlockKindValue(CBlock* c);
		 
		CBlockNamedValue* asCBlockNamedValue(CBlock* c);
	 
		CBlockInstanceVariable* asCBlockInstanceVariable(CBlock* c);
		CBlockList* asCBlockList(CBlock* c);
		CBlockEnums* asCBlockEnums(CBlock* c);
		CBlockProperty* asCBlockProperty(CBlock* c);
		CBlockAssertion_isDefaultAssign* asCBlockAssertion_isDefaultAssign(CBlock* c);
		CBlockNoum* asCBlockNoum(CBlock* c);
		CBlockKind_InstanceVariable* asCKind_InstanceVariable(CBlock* c);
		CBlockAssertion_isDirectAssign* asCBlockAssertion_isDirectAssign(CBlock* c);
		CBlockAssertion_canBe* asCBlockAssertion_canBe(CBlock* c);
		CBlockAssertion_is* asCBlockAssertion_is(CBlock* c);
		CBlockIsVerb* asCBlockIsVerb(CBlock* c);
//		CBlockAssertion_isActionOf* asCBlockAssertion_isActionOf(CBlock* c);
		CBlockIsNotVerb* asCBlockIsNotVerb(CBlock* c);
		CBlockMatchAny* asCBlockMatchAny(CBlock* c);
		CBlockMatchNamed* asCBlockMatchNamed(CBlock* c);
		CBlockMatchList* asCBlockMatchList(CBlock* c);
		CBlockMatchDirectIsNot* asCBlockMatchDirectIsNot(CBlock* c);
		CBlockMatchKind* asCBlockMatchKind(CBlock* c);
		CBlockMatchProperty* asCBlockMatchProperty(CBlock* c);
		CBlockMatchBlock* asCBlockMatchBlock(CBlock* c);
		CBlockMatchOR* asCBlockMatchOR(CBlock* c);
		CBlockMatchAND* asCBlockMatchAND(CBlock* c);
		CBlockMatchDirectIs* asCBlockMatchDirectIs(CBlock* c);
		CBlockMatchIsVerb* asCBlockMatchIsVerb(CBlock* c);
		CBlockMatchIsNotVerb* asCBlockMatchIsNotVerb(CBlock* c);
		CBlockAssertion_isNotDirectAssign* asCBlockAssertion_isNotDirectAssign(CBlock* c);
		CBlockMatchNoum* asCBlockMatchNoum(CBlock* c);
		CBlockBooleanAND* asCBlockBooleanAND(CBlock* c);
		CBlockVerb* asCBlockVerb(CBlock* c);
		CBlockBooleanOR* asCBlockBooleanOR(CBlock* c);
		CBlockBooleanNOT* asCBlockBooleanNOT(CBlock* c);
		CBlockSelector_All* asCBlockSelector_All(CBlock* c);
		CBlockSelector_Any* asCBlockSelector_Any(CBlock* c);
		CBlockStaticDispatch* asCBlockStaticDispatch(CBlock* c);
		CBlockAction* asCBlockAction(CBlock* c);
		CBlockActionCall* asCBlockActionCall(CBlock* c);
		CBlockVariableNamed* asCBlockVariableNamed(CBlock* c);
		CBlockUnderstandDynamic* asCBlockUnderstandDynamic(CBlock* c);
		CBlockUnderstandStatic* asCBlockUnderstandStatic(CBlock* c);
		CBlockToDecideWhether* asCBlockToDecideWhether(CBlock* c);
		CBlockToDecideIf* asCBlockToDecideIf(CBlock* c);
		CBlockToDecideWhat_FirstNoum* asCBlockToDecideWhat_FirstNoum(CBlock* c);
		CBlockToDecideWhat* asCBlockToDecideWhat(CBlock* c);
		CBlockToDecideOn* asCBlockToDecideOn(CBlock* c);
		CBlockActionApply* asCBlockActionApply(CBlock* c);
		CBlockKindOfName* asCBlockKindOfName(CBlock* c);
		CBlockArgumentInput* asCBlockArgumentInput(CBlock* c);
		CBlockText* asCBlockText(CBlock* c);
		CBlockInstance* asCBlockInstance(CBlock* c);
		CBlockSimetricRelation* asCBlockSimetricRelation(CBlock* c);
		CBlockASimetricRelation* asCBlockASimetricRelation(CBlock* c);
		CBlockRelationInstance* asCBlockRelationInstance(CBlock* c);
		CBlockVerbRelation* asCBlockVerbRelation(CBlock* c);
		CBlockAssertion_isConstantAssign* asCBlockAssertion_isConstantAssign(CBlock* c);
		CBlockAssertion_isForbiddenAssign* asCBlockAssertion_isForbiddenAssign(CBlock* c);
		CBlockAssertion_isVariable* asCBlockAssertion_isVariable(CBlock* c);
		CBlockAssertion_isNamedValueOf* asCBlockAssertion_isNamedValueOf(CBlock* c);
		CBlockAssertion_InstanceVariable* asCBlockAssertion_InstanceVariable(CBlock* c);
		CBlockAssertion_isInstanceOf* asCBlockAssertion_isInstanceOf(CBlock* c);
		CBlockDinamicDispatch* asCBlockDinamicDispatch(CBlock* c);
		CBlockNow* asCBlockNow(CBlock* c);


	}
}