
#include "CBlockInterpreterRuntime.hpp"
#include "CBlockBoolean.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockNumber.hpp"
#include "CBlockControlFlux.hpp"
#include "CBlockComposition.hpp"


using namespace  CBlocking;
 
int load_type()
{
	return 0;
}
std::string load_string()
{
	return "";
}

int load_int()
{
	return 0;
}

int load_float()
{
	return 0.0;
}
bool load_bool() {return false; }

template<typename T>  std::list<std::shared_ptr<T> > load_list(  )
{
	return std::list<std::shared_ptr<T> >();
}

template<typename T>  std::vector<std::shared_ptr<T> > load_vector()
{
	return std::vector<std::shared_ptr<T> >();
}

NoumLocation  load_NoumLocation() { return NoumLocation::FirstNoum; }

EventHandleStage   load_EventHandleStage() {return EventHandleStage::StageAfter;}

PhaseResultFlag  load_PhaseResultFlag() { return PhaseResultFlag::actionContinue; }

void cmp_type(int tp, BlockType t)
{
	
}
 


 
	
 
	HBlockInstance  load_CBlockInstance(int tp);
  HBlockInstanceNamed  load_CBlockInstanceNamed(int tp);
  HBlockText  load_CBlockText(int tp);
  HBlockTextSentence  load_CBlockTextSentence(int tp);
  HBlockValue  load_CBlockValue(int tp);
  HBlockKindReference  load_CBlockKindReference(int tp);
  HBlockNoum  load_CBlockNoum(int tp);
  HBlockNoum  load_CBlockNoum(int tp);
  HBlockNoumSupl  load_CBlockNoumSupl(int tp);
  HBlockKindNamed  load_CBlockKindNamed(int tp);
  HBlockNothing  load_CBlockNothing(int tp);
  HBlockAnything  load_CBlockAnything(int tp);
  HBlockKindOfName  load_CBlockKindOfName(int tp);
  HBlockKindOf  load_CBlockKindOf(int tp);
  HBlockActionApply  load_CBlockActionApply(int tp);
  HBlockKindAction  load_CBlockKindAction(int tp);
  HBlockKindValue  load_CBlockKindValue(int tp);
  HBlockKindEntity  load_CBlockKindEntity(int tp);
  HBlockNamedValue  load_CBlockNamedValue(int tp);
  HBlockProperty  load_CBlockProperty(int tp);
  HBlockInstanceVariable  load_CBlockInstanceVariable(int tp);
  HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable(int tp);
  HBlockList  load_CBlockList(int tp);
  HBlockList_OR  load_CBlockList_OR(int tp);
  HBlockList_AND  load_CBlockList_AND(int tp);
  HBlockEnums  load_CBlockEnums(int tp);
  HBlockVerbRelation  load_CBlockVerbRelation(int tp);
  HBlockVerbDirectRelation  load_CBlockVerbDirectRelation(int tp);
  HBlockVerbReverseRelation  load_CBlockVerbReverseRelation(int tp);
  HBlockDinamicDispatch  load_CBlockDinamicDispatch(int tp);
  HBlockIF  load_CBlockIF(int tp);
  HBlockSame  load_CBlockSame(int tp);
  HBlockVerbConjugation  load_CBlockVerbConjugation(int tp);
  HBlockVerb  load_CBlockVerb(int tp);
  HBlockVerbAdapt  load_CBlockVerbAdapt(int tp);
  HBlockVerbNegate  load_CBlockVerbNegate(int tp);
  HBlockSelector  load_CBlockSelector(int tp);
  HBlockSelector_All  load_CBlockSelector_All(int tp);
  HBlockSelector_Any  load_CBlockSelector_Any(int tp);
  HBlockSelector_Where  load_CBlockSelector_Where(int tp);
  HBlockAction  load_CBlockAction(int tp);
  HBlockActionInstance  load_CBlockActionInstance(int tp);
  HBlockActionNamed  load_CBlockActionNamed(int tp);
  HBlockActionNamed  load_CBlockActionNamed(int tp);
  HBlockTryCall  load_CBlockTryCall(int tp);
  HBlockActionCall  load_CBlockActionCall(int tp);
  HBlockActionCallNamed  load_CBlockActionCallNamed(int tp);
  HBlockStaticDispatch  load_CBlockStaticDispatch(int tp);
  HBlockAssertionBase  load_CBlockAssertionBase(int tp);
  HBlockAssertion_is  load_CBlockAssertion_is(int tp);
  HBlockAssertion_canBe  load_CBlockAssertion_canBe(int tp);
  HBlockAssertion_isKindOf  load_CBlockAssertion_isKindOf(int tp);
  HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf(int tp);
  HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf(int tp);
  HBlockAssertion_isVariable  load_CBlockAssertion_isVariable(int tp);
  HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable(int tp);
  HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign(int tp);
  HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign(int tp);
  HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign(int tp);
  HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign(int tp);
  HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign(int tp);
  HBlockIsVerb  load_CBlockIsVerb(int tp);
  HBlockIsNotVerb  load_CBlockIsNotVerb(int tp);
  HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion(int tp);
  HBlockAssert  load_CBlockAssert(int tp);
  HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable(int tp);
  HBlockBooleanValue  load_CBlockBooleanValue(int tp);
  HBlockBooleanAND  load_CBlockBooleanAND(int tp);
  HBlockBooleanOR  load_CBlockBooleanOR(int tp);
  HBlockBooleanNOT  load_CBlockBooleanNOT(int tp);
  HBlockNow  load_CBlockNow(int tp);
  HBlockEvery  load_CBlockEvery(int tp);
  HBlockComandList  load_CBlockComandList(int tp);
  HBlockEventHandle  load_CBlockEventHandle(int tp);
  HBlockComposition  load_CBlockComposition(int tp);
  HBlockCompositionList  load_CBlockCompositionList(int tp);
  HBlockCompositionRelation  load_CBlockCompositionRelation(int tp);
  HBlockCompositionPhrase  load_CBlockCompositionPhrase(int tp);
  HBlockCompostionPhrase  load_CBlockCompostionPhrase(int tp);
  HBlockControlToken  load_CBlockControlToken(int tp);
  HBlockControlIF  load_CBlockControlIF(int tp);
  HBlockControlUnless  load_CBlockControlUnless(int tp);
  HBlockControlSelectItem  load_CBlockControlSelectItem(int tp);
  HBlockControlSelect  load_CBlockControlSelect(int tp);
  HBlockControlForEach  load_CBlockControlForEach(int tp);
  HBlockExecutionResultFlag  load_CBlockExecutionResultFlag(int tp);
  HBlockUnitInit  load_CBlockUnitInit(int tp);
  HBlockUnitTest  load_CBlockUnitTest(int tp);
  HBlockUnitAssert  load_CBlockUnitAssert(int tp);
  HBlockToDecide  load_CBlockToDecide(int tp);
  HBlockToDecideIf  load_CBlockToDecideIf(int tp);
  HBlockToDecideOn  load_CBlockToDecideOn(int tp);
  HBlockPhraseHeader  load_CBlockPhraseHeader(int tp);
  HBlockPhraseDefine  load_CBlockPhraseDefine(int tp);
  HBlockPhraseInvoke  load_CBlockPhraseInvoke(int tp);
  HBlockInterpreter  load_CBlockInterpreter(int tp);
  HBlockMatch  load_CBlockMatch(int tp);
  HBlockMatchAny  load_CBlockMatchAny(int tp);
  HBlockMatchNamed  load_CBlockMatchNamed(int tp);
  HBlockMatchNoum  load_CBlockMatchNoum(int tp);
  HBlockMatchValue  load_CBlockMatchValue(int tp);
  HBlockMatchKind  load_CBlockMatchKind(int tp);
  HBlockMatchWith  load_CBlockMatchWith(int tp);
  HBlockMatchList  load_CBlockMatchList(int tp);
  HBlockMatchAND  load_CBlockMatchAND(int tp);
  HBlockMatchNOT  load_CBlockMatchNOT(int tp);
  HBlockMatchOR  load_CBlockMatchOR(int tp);
  HBlockMatchActionCall  load_CBlockMatchActionCall(int tp);
  HBlockMatchBlock  load_CBlockMatchBlock(int tp);
  HBlockMatchIs  load_CBlockMatchIs(int tp);
  HBlockMatchDirectIs  load_CBlockMatchDirectIs(int tp);
  HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot(int tp);
  HBlockMatchIsVerb  load_CBlockMatchIsVerb(int tp);
  HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb(int tp);
  HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion(int tp);
  HBlockMatchProperty  load_CBlockMatchProperty(int tp);
  HBlockMatchWhich  load_CBlockMatchWhich(int tp);
  HBlockMatchWhichNot  load_CBlockMatchWhichNot(int tp);
  HBlockVariableNamed  load_CBlockVariableNamed(int tp);
  HBlockNumber  load_CBlockNumber(int tp);
  HBlockIntegerNumber  load_CBlockIntegerNumber(int tp);
  HBlockFactionalNumber  load_CBlockFactionalNumber(int tp);
  HBlockArgumentInput  load_CBlockArgumentInput(int tp);
  HBlockRelationBase  load_CBlockRelationBase(int tp);
  HBlockSimetricRelation  load_CBlockSimetricRelation(int tp);
  HBlockASimetricRelation  load_CBlockASimetricRelation(int tp);
  HBlockRelationInstance  load_CBlockRelationInstance(int tp);
  HBlockConditionalRelation  load_CBlockConditionalRelation(int tp);
  HBlockRelationLookup  load_CBlockRelationLookup(int tp);
  HBlockVerbLookup  load_CBlockVerbLookup(int tp);
  HBlockRelationArguments  load_CBlockRelationArguments(int tp);
  HBlockSelectorAND  load_CBlockSelectorAND(int tp);
  HBlockExecution  load_CBlockExecution(int tp);
  HBlockUnderstand  load_CBlockUnderstand(int tp);
  HBlockUnderstandStatic  load_CBlockUnderstandStatic(int tp);
  HBlockUnderstandDynamic  load_CBlockUnderstandDynamic(int tp);
  HBlockRelationBase  load_CBlockRelationBase(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockSimetricRelation) return load_CBlockSimetricRelation(tp);
	  if (tp == BlockType::BlockASimetricRelation) return load_CBlockASimetricRelation(tp);
	  if (tp == BlockType::BlockConditionalRelation) return load_CBlockConditionalRelation(tp);
	  return nullptr;
  }

  HBlockNumber  load_CBlockNumber(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockFactionalNumber) return load_CBlockFactionalNumber(tp);
	  return nullptr;
  }

  HBlockKind  load_CBlockKind(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockKindNamed) return load_CBlockKindNamed(tp);
	  if (tp == BlockType::BlockKindAction) return load_CBlockKindAction(tp);
	  if (tp == BlockType::BlockKindValue) return load_CBlockKindValue(tp);
	  if (tp == BlockType::BlockKindEntity) return load_CBlockKindEntity(tp);
	  if (tp == BlockType::BlockComposition) return load_CBlockComposition(tp);
	  return nullptr;
  }

  HBlockValue  load_CBlockValue(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockKindReference) return load_CBlockKindReference(tp);
	  { auto x = load_CBlockBooleanResult(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockNamedValue) return load_CBlockNamedValue(tp);
	  if (tp == BlockType::BlockBooleanValue) return load_CBlockBooleanValue(tp);
	  return nullptr;
  }

  HBlockMatchIs  load_CBlockMatchIs(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockMatchDirectIs) return load_CBlockMatchDirectIs(tp);
	  if (tp == BlockType::BlockMatchDirectIsNot) return load_CBlockMatchDirectIsNot(tp);
	  if (tp == BlockType::BlockMatchIsVerb) return load_CBlockMatchIsVerb(tp);
	  if (tp == BlockType::BlockMatchIsNotVerb) return load_CBlockMatchIsNotVerb(tp);
	  if (tp == BlockType::BlockMatchIsAdverbialComparasion) return load_CBlockMatchIsAdverbialComparasion(tp);
	  if (tp == BlockType::BlockMatchWhich) return load_CBlockMatchWhich(tp);
	  if (tp == BlockType::BlockMatchWhichNot) return load_CBlockMatchWhichNot(tp);
	  return nullptr;
  }

  HBlockVerbRelation  load_CBlockVerbRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockVerbDirectRelation) return load_CBlockVerbDirectRelation(tp);
	  if (tp == BlockType::BlockVerbReverseRelation) return load_CBlockVerbReverseRelation(tp);
	  return nullptr;
  }

  HBlockAction  load_CBlockAction(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockActionInstance) return load_CBlockActionInstance(tp);
	  if (tp == BlockType::BlockActionNamed) return load_CBlockActionNamed(tp);
	  return nullptr;
  }

  HBlockInstance  load_CBlockInstance(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockInstanceNamed) return load_CBlockInstanceNamed(tp);
	  return nullptr;
  }

  HBlockAssertion_is  load_CBlockAssertion_is(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockAssertion_isKindOf) return load_CBlockAssertion_isKindOf(tp);
	  if (tp == BlockType::BlockAssertion_isInstanceOf) return load_CBlockAssertion_isInstanceOf(tp);
	  if (tp == BlockType::BlockAssertion_isNamedValueOf) return load_CBlockAssertion_isNamedValueOf(tp);
	  if (tp == BlockType::BlockAssertion_isVariable) return load_CBlockAssertion_isVariable(tp);
	  if (tp == BlockType::BlockAssertion_isLocalVariable) return load_CBlockAssertion_isLocalVariable(tp);
	  if (tp == BlockType::BlockAssertion_isDefaultAssign) return load_CBlockAssertion_isDefaultAssign(tp);
	  if (tp == BlockType::BlockAssertion_isConstantAssign) return load_CBlockAssertion_isConstantAssign(tp);
	  if (tp == BlockType::BlockAssertion_isForbiddenAssign) return load_CBlockAssertion_isForbiddenAssign(tp);
	  if (tp == BlockType::BlockAssertion_isDirectAssign) return load_CBlockAssertion_isDirectAssign(tp);
	  if (tp == BlockType::BlockAssertion_isNotDirectAssign) return load_CBlockAssertion_isNotDirectAssign(tp);
	  if (tp == BlockType::BlockIsVerb) return load_CBlockIsVerb(tp);
	  if (tp == BlockType::BlockIsNotVerb) return load_CBlockIsNotVerb(tp);
	  if (tp == BlockType::BlockIsAdverbialComparasion) return load_CBlockIsAdverbialComparasion(tp);
	  return nullptr;
  }

  HBlockMatch  load_CBlockMatch(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockMatchAny) return load_CBlockMatchAny(tp);
	  if (tp == BlockType::BlockMatchNamed) return load_CBlockMatchNamed(tp);
	  if (tp == BlockType::BlockMatchNoum) return load_CBlockMatchNoum(tp);
	  if (tp == BlockType::BlockMatchValue) return load_CBlockMatchValue(tp);
	  if (tp == BlockType::BlockMatchKind) return load_CBlockMatchKind(tp);
	  { auto x = load_CBlockMatchWith(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockMatchList) return load_CBlockMatchList(tp);
	  if (tp == BlockType::BlockMatchAND) return load_CBlockMatchAND(tp);
	  if (tp == BlockType::BlockMatchNOT) return load_CBlockMatchNOT(tp);
	  if (tp == BlockType::BlockMatchOR) return load_CBlockMatchOR(tp);
	  if (tp == BlockType::BlockMatchActionCall) return load_CBlockMatchActionCall(tp);
	  if (tp == BlockType::BlockMatchBlock) return load_CBlockMatchBlock(tp);
	  { auto x = load_CBlockMatchIs(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockMatchProperty) return load_CBlockMatchProperty(tp);
	  return nullptr;
  }

  HBlockActionCall  load_CBlockActionCall(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockActionCallNamed) return load_CBlockActionCallNamed(tp);
	  if (tp == BlockType::BlockStaticDispatch) return load_CBlockStaticDispatch(tp);
	  return nullptr;
  }

  HBlockBooleanResult  load_CBlockBooleanResult(int tp)
  {
	  if (tp == -1) tp = load_type();
	  { auto x = load_CBlockSame(tp); if (x != nullptr) return x; };
	  return nullptr;
  }

  HBlockNoum  load_CBlockNoum(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockNoumSupl) return load_CBlockNoumSupl(tp);
	  return nullptr;
  }

  HBlockToDecide  load_CBlockToDecide(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockToDecideIf) return load_CBlockToDecideIf(tp);
	  if (tp == BlockType::BlockToDecideWhether) return load_CBlockToDecideWhether(tp);
	  if (tp == BlockType::BlockToDecideWhat) return load_CBlockToDecideWhat(tp);
	  if (tp == BlockType::BlockToDecideWhat_FirstNoum) return load_CBlockToDecideWhat_FirstNoum(tp);
	  return nullptr;
  }

  HBlock  load_CBlock(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockInstance) return load_CBlockInstance(tp);
	  if (tp == BlockType::BlockText) return load_CBlockText(tp);
	  if (tp == BlockType::BlockTextSentence) return load_CBlockTextSentence(tp);
	  { auto x = load_CBlockKind(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockValue(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockNoum) return load_CBlockNoum(tp);
	  if (tp == BlockType::BlockNothing) return load_CBlockNothing(tp);
	  if (tp == BlockType::BlockAnything) return load_CBlockAnything(tp);
	  if (tp == BlockType::BlockKindOfName) return load_CBlockKindOfName(tp);
	  if (tp == BlockType::BlockKindOf) return load_CBlockKindOf(tp);
	  if (tp == BlockType::BlockActionApply) return load_CBlockActionApply(tp);
	  if (tp == BlockType::BlockProperty) return load_CBlockProperty(tp);
	  if (tp == BlockType::BlockInstanceVariable) return load_CBlockInstanceVariable(tp);
	  if (tp == BlockType::BlockKind_InstanceVariable) return load_CBlockKind_InstanceVariable(tp);
	  if (tp == BlockType::BlockList) return load_CBlockList(tp);
	  if (tp == BlockType::BlockEnums) return load_CBlockEnums(tp);
	  { auto x = load_CBlockVerbRelation(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockFilter(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockDinamicDispatch) return load_CBlockDinamicDispatch(tp);
	  { auto x = load_CBlockTransform(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockIF(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockProp(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockVerbConjugation) return load_CBlockVerbConjugation(tp);
	  if (tp == BlockType::BlockVerb) return load_CBlockVerb(tp);
	  if (tp == BlockType::BlockVerbAdapt) return load_CBlockVerbAdapt(tp);
	  if (tp == BlockType::BlockVerbNegate) return load_CBlockVerbNegate(tp);
	  { auto x = load_CBlockSelector(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockAction) return load_CBlockAction(tp);
	  if (tp == BlockType::BlockTryCall) return load_CBlockTryCall(tp);
	  if (tp == BlockType::BlockActionCall) return load_CBlockActionCall(tp);
	  { auto x = load_CBlockAssertionBase(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockAssertion_InstanceVariable) return load_CBlockAssertion_InstanceVariable(tp);
	  { auto x = load_CBlockAssertionCond(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockBooleanAND) return load_CBlockBooleanAND(tp);
	  if (tp == BlockType::BlockBooleanOR) return load_CBlockBooleanOR(tp);
	  if (tp == BlockType::BlockBooleanNOT) return load_CBlockBooleanNOT(tp);
	  if (tp == BlockType::BlockNow) return load_CBlockNow(tp);
	  if (tp == BlockType::BlockEvery) return load_CBlockEvery(tp);
	  if (tp == BlockType::BlockComandList) return load_CBlockComandList(tp);
	  if (tp == BlockType::BlockEventHandle) return load_CBlockEventHandle(tp);
	  if (tp == BlockType::BlockCompostionPhrase) return load_CBlockCompostionPhrase(tp);
	  if (tp == BlockType::BlockControlIF) return load_CBlockControlIF(tp);
	  if (tp == BlockType::BlockControlUnless) return load_CBlockControlUnless(tp);
	  if (tp == BlockType::BlockControlSelectItem) return load_CBlockControlSelectItem(tp);
	  if (tp == BlockType::BlockControlSelect) return load_CBlockControlSelect(tp);
	  if (tp == BlockType::BlockControlForEach) return load_CBlockControlForEach(tp);
	  { auto x = load_CBlockToDecide(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockToDecideOn) return load_CBlockToDecideOn(tp);
	  if (tp == BlockType::BlockPhraseHeader) return load_CBlockPhraseHeader(tp);
	  if (tp == BlockType::BlockPhraseDefine) return load_CBlockPhraseDefine(tp);
	  if (tp == BlockType::BlockPhraseInvoke) return load_CBlockPhraseInvoke(tp);
	  if (tp == BlockType::BlockMatch) return load_CBlockMatch(tp);
	  if (tp == BlockType::BlockArgumentInput) return load_CBlockArgumentInput(tp);
	  { auto x = load_CBlockRelationBase(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockRelationInstance) return load_CBlockRelationInstance(tp);
	  if (tp == BlockType::BlockRelationLookup) return load_CBlockRelationLookup(tp);
	  if (tp == BlockType::BlockVerbLookup) return load_CBlockVerbLookup(tp);
	  if (tp == BlockType::BlockRelationArguments) return load_CBlockRelationArguments(tp);
	  if (tp == BlockType::BlockSelectorAND) return load_CBlockSelectorAND(tp);
	  { auto x = load_CBlockUnderstand(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockUnderstandStatic) return load_CBlockUnderstandStatic(tp);
	  if (tp == BlockType::BlockUnderstandDynamic) return load_CBlockUnderstandDynamic(tp);
	  return nullptr;
  }

  HBlockSelector  load_CBlockSelector(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockSelector_All) return load_CBlockSelector_All(tp);
	  if (tp == BlockType::BlockSelector_Any) return load_CBlockSelector_Any(tp);
	  if (tp == BlockType::BlockSelector_Where) return load_CBlockSelector_Where(tp);
	  return nullptr;
  }

  HBlockAssertionBase  load_CBlockAssertionBase(int tp)
  {
	  if (tp == -1) tp = load_type();
	  { auto x = load_CBlockAssertion_is(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockAssertion_property_canBe(tp); if (x != nullptr) return x; };
	  if (tp == BlockType::BlockAssertion_canBe) return load_CBlockAssertion_canBe(tp);
	  return nullptr;
  }

  HBlockFilter  load_CBlockFilter(int tp)
  {
	  if (tp == -1) tp = load_type();
	  { auto x = load_CBlockFilterAtom(tp); if (x != nullptr) return x; };
	  { auto x = load_CBlockFilterList(tp); if (x != nullptr) return x; };
	  return nullptr;
  }

  HBlockComposition  load_CBlockComposition(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockCompositionList) return load_CBlockCompositionList(tp);
	  if (tp == BlockType::BlockCompositionRelation) return load_CBlockCompositionRelation(tp);
	  if (tp == BlockType::BlockCompositionPhrase) return load_CBlockCompositionPhrase(tp);
	  return nullptr;
  }

  HBlockList  load_CBlockList(int tp)
  {
	  if (tp == -1) tp = load_type();
	  if (tp == BlockType::BlockList_OR) return load_CBlockList_OR(tp);
	  if (tp == BlockType::BlockList_AND) return load_CBlockList_AND(tp);
	  return nullptr;
  }

  HBlockMatchProperty  load_CBlockMatchProperty(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchProperty);
	  HBlock _prop = load_CBlock(-1);
	  HBlockMatch b = load_CBlockMatch(-1);
	  CBlockMatchProperty* ret = new CBlockMatchProperty(_prop, b);
	  return  std::shared_ptr<CBlockMatchProperty>(ret);

  }



  HBlockExecutionResultFlag  load_CBlockExecutionResultFlag(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockExecutionResultFlag);
	  PhaseResultFlag _flag = load_PhaseResultFlag();
	  HBlock _contents = load_CBlock(-1);
	  CBlockExecutionResultFlag* ret = new CBlockExecutionResultFlag(_flag, _contents);
	  return  std::shared_ptr<CBlockExecutionResultFlag>(ret);

  }


  HBlockEventHandle  load_CBlockEventHandle(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockEventHandle);
	  EventHandleStage _stage = load_EventHandleStage();
	  HBlockMatchActionCall _eventToObserve = load_CBlockMatchActionCall(-1);
	  HBlockComandList _body = load_CBlockComandList(-1);
	  CBlockEventHandle* ret = new CBlockEventHandle(_stage, _eventToObserve, _body);
	  return  std::shared_ptr<CBlockEventHandle>(ret);

  }


  HBlockActionNamed  load_CBlockActionNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockActionNamed);
	  std::string _named = load_string();
	  HBlockKindAction _act = load_CBlockKindAction(-1);
	  CBlockActionNamed* ret = new CBlockActionNamed(_named, _act);
	  return  std::shared_ptr<CBlockActionNamed>(ret);

  }


  HBlockNothing  load_CBlockNothing(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockNothing);
	  string _named = load_string();
	  CBlockNothing* ret = new CBlockNothing(_named);
	  return  std::shared_ptr<CBlockNothing>(ret);

  }


  HBlockMatchWhichNot  load_CBlockMatchWhichNot(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchWhichNot);
	  string _verb = load_string();
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchWhichNot* ret = new CBlockMatchWhichNot(_verb, _obj, _value);
	  return  std::shared_ptr<CBlockMatchWhichNot>(ret);

  }


  HBlockAnything  load_CBlockAnything(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAnything);
	  string _named = load_string();
	  CBlockAnything* ret = new CBlockAnything(_named);
	  return  std::shared_ptr<CBlockAnything>(ret);

  }


  HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isNotDirectAssign);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockAssertion_isNotDirectAssign* ret = new CBlockAssertion_isNotDirectAssign(_variable, _value);
	  return  std::shared_ptr<CBlockAssertion_isNotDirectAssign>(ret);

  }


  HBlockVerbAdapt  load_CBlockVerbAdapt(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbAdapt);
	  string _verb = load_string();
	  string _tense = load_string();
	  string _viewPoint = load_string();
	  CBlockVerbAdapt* ret = new CBlockVerbAdapt(_verb, _tense, _viewPoint);
	  return  std::shared_ptr<CBlockVerbAdapt>(ret);

  }


  HBlockNow  load_CBlockNow(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockNow);
	  HBlockAssertion_is _n = load_CBlockAssertion_is(-1);
	  CBlockNow* ret = new CBlockNow(_n);
	  return  std::shared_ptr<CBlockNow>(ret);

  }


  HBlockVerbConjugation  load_CBlockVerbConjugation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbConjugation);
	  string _word = load_string();
	  string _tense = load_string();
	  CBlockVerbConjugation* ret = new CBlockVerbConjugation(_word, _tense);
	  return  std::shared_ptr<CBlockVerbConjugation>(ret);

  }


  HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchIsAdverbialComparasion);
	  string _adverb = load_string();
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchIsAdverbialComparasion* ret = new CBlockMatchIsAdverbialComparasion(_adverb, _obj, _value);
	  return  std::shared_ptr<CBlockMatchIsAdverbialComparasion>(ret);

  }


  HBlockControlSelect  load_CBlockControlSelect(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlSelect);
	  HBlock _block_seletor = load_CBlock(-1);
	  std::list<HBlockControlSelectItem> _block_selectList = load_list<CBlockControlSelectItem>();
	  HBlock _block_else = load_CBlock(-1);
	  CBlockControlSelect* ret = new CBlockControlSelect(_block_seletor, _block_selectList, _block_else);
	  return  std::shared_ptr<CBlockControlSelect>(ret);

  }


  HBlockControlSelectItem  load_CBlockControlSelectItem(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlSelectItem);
	  HBlock _block_seletor = load_CBlock(-1);
	  HBlock _block_execute = load_CBlock(-1);
	  CBlockControlSelectItem* ret = new CBlockControlSelectItem(_block_seletor, _block_execute);
	  return  std::shared_ptr<CBlockControlSelectItem>(ret);

  }


  HBlockList_AND  load_CBlockList_AND(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockList_AND);
	  std::list<HBlock> _lista = load_list<CBlock>();
	  CBlockList_AND* ret = new CBlockList_AND(_lista);
	  return  std::shared_ptr<CBlockList_AND>(ret);

  }


  HBlockConditionalRelation  load_CBlockConditionalRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockConditionalRelation);
	  HBlockRelationBase _relation = load_CBlockRelationBase(-1);
	  HBlock _coditional = load_CBlock(-1);
	  CBlockConditionalRelation* ret = new CBlockConditionalRelation(_relation, _coditional);
	  return  std::shared_ptr<CBlockConditionalRelation>(ret);

  }


  HBlockKindEntity  load_CBlockKindEntity(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindEntity);
	  string _named = load_string();
	  CBlockKindEntity* ret = new CBlockKindEntity(_named);
	  return  std::shared_ptr<CBlockKindEntity>(ret);

  }


  HBlockMatchWhich  load_CBlockMatchWhich(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchWhich);
	  string _verb = load_string();
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchWhich* ret = new CBlockMatchWhich(_verb, _obj, _value);
	  return  std::shared_ptr<CBlockMatchWhich>(ret);

  }


  HBlockControlForEach  load_CBlockControlForEach(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlForEach);
	  HBlock _block_variable = load_CBlock(-1);
	  HBlock _block_body = load_CBlock(-1);
	  CBlockControlForEach* ret = new CBlockControlForEach(_block_variable, _block_body);
	  return  std::shared_ptr<CBlockControlForEach>(ret);

  }


  HBlockMatchKind  load_CBlockMatchKind(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchKind);
	  HBlockKind _kindInnter = load_CBlockKind(-1);
	  CBlockMatchKind* ret = new CBlockMatchKind(_kindInnter);
	  return  std::shared_ptr<CBlockMatchKind>(ret);

  }


  HBlockBooleanValue  load_CBlockBooleanValue(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockBooleanValue);
	  bool _state = load_bool();
	  CBlockBooleanValue* ret = new CBlockBooleanValue(_state);
	  return  std::shared_ptr<CBlockBooleanValue>(ret);

  }


  HBlockText  load_CBlockText(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockText);
	  std::string _contents = load_string();
	  CBlockText* ret = new CBlockText(_contents);
	  return  std::shared_ptr<CBlockText>(ret);

  }


  HBlockInstanceVariable  load_CBlockInstanceVariable(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockInstanceVariable);
	  HBlockNoum _kind_name = load_CBlockNoum(-1);
	  HBlockNoum _property_name = load_CBlockNoum(-1);
	  CBlockInstanceVariable* ret = new CBlockInstanceVariable(_kind_name, _property_name);
	  return  std::shared_ptr<CBlockInstanceVariable>(ret);

  }


  HBlockMatchIsVerb  load_CBlockMatchIsVerb(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchIsVerb);
	  string _verb = load_string();
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchIsVerb* ret = new CBlockMatchIsVerb(_verb, _obj, _value);
	  return  std::shared_ptr<CBlockMatchIsVerb>(ret);

  }


  HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isNamedValueOf);
	  HBlock _noum = load_CBlock(-1);
	  HBlock _baseKind = load_CBlock(-1);
	  CBlockAssertion_isNamedValueOf* ret = new CBlockAssertion_isNamedValueOf(_noum, _baseKind);
	  return  std::shared_ptr<CBlockAssertion_isNamedValueOf>(ret);

  }


  HBlockKindOfName  load_CBlockKindOfName(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindOfName);
	  string _baseClasseName = load_string();
	  CBlockKindOfName* ret = new CBlockKindOfName(_baseClasseName);
	  return  std::shared_ptr<CBlockKindOfName>(ret);

  }


  HBlockFactionalNumber  load_CBlockFactionalNumber(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockFactionalNumber);
	  float _value = load_float();
	  CBlockFactionalNumber* ret = new CBlockFactionalNumber(_value);
	  return  std::shared_ptr<CBlockFactionalNumber>(ret);

  }


  HBlockMatchNoum  load_CBlockMatchNoum(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchNoum);
	  HBlockNoum _inner = load_CBlockNoum(-1);
	  CBlockMatchNoum* ret = new CBlockMatchNoum(_inner);
	  return  std::shared_ptr<CBlockMatchNoum>(ret);

  }


  HBlockUnitAssert  load_CBlockUnitAssert(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockUnitAssert);
	  HBlock _contents = load_CBlock(-1);
	  CBlockUnitAssert* ret = new CBlockUnitAssert(_contents);
	  return  std::shared_ptr<CBlockUnitAssert>(ret);

  }


  HBlockVerb  load_CBlockVerb(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerb);
	  string _named = load_string();
	  std::list<HBlockVerbConjugation> _conjugations = load_list<CBlockVerbConjugation>();
	  CBlockVerb* ret = new CBlockVerb(_named, _conjugations);
	  return  std::shared_ptr<CBlockVerb>(ret);

  }


  HBlockPhraseDefine  load_CBlockPhraseDefine(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockPhraseDefine);
	  HBlockPhraseHeader _header = load_CBlockPhraseHeader(-1);
	  HBlock _body = load_CBlock(-1);
	  CBlockPhraseDefine* ret = new CBlockPhraseDefine(_header, _body);
	  return  std::shared_ptr<CBlockPhraseDefine>(ret);

  }


  HBlockBooleanNOT  load_CBlockBooleanNOT(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockBooleanNOT);
	  HBlock input_a = load_CBlock(-1);
	  CBlockBooleanNOT* ret = new CBlockBooleanNOT(input_a);
	  return  std::shared_ptr<CBlockBooleanNOT>(ret);

  }


  HBlockTextSentence  load_CBlockTextSentence(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockTextSentence);
	  std::list<HBlock> _contents = load_list<CBlock>();
	  CBlockTextSentence* ret = new CBlockTextSentence(_contents);
	  return  std::shared_ptr<CBlockTextSentence>(ret);

  }


  HBlockCompositionRelation  load_CBlockCompositionRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockCompositionRelation);
	  HBlockKind _fromKind = load_CBlockKind(-1);
	  HBlockKind _toKind = load_CBlockKind(-1);
	  CBlockCompositionRelation* ret = new CBlockCompositionRelation(_fromKind, _toKind);
	  return  std::shared_ptr<CBlockCompositionRelation>(ret);

  }


  HBlockKindNamed  load_CBlockKindNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindNamed);
	  string _named = load_string();
	  CBlockKindNamed* ret = new CBlockKindNamed(_named);
	  return  std::shared_ptr<CBlockKindNamed>(ret);

  }



  HBlockToDecideIf  load_CBlockToDecideIf(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockToDecideIf);
	  HBlockMatchIs _queryToMatch = load_CBlockMatchIs(-1);
	  HBlock _decideBody = load_CBlock(-1);
	  CBlockToDecideIf* ret = new CBlockToDecideIf(_queryToMatch, _decideBody);
	  return  std::shared_ptr<CBlockToDecideIf>(ret);

  }


  HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockIsAdverbialComparasion);
	  string _adverb = load_string();
	  HBlock _n1 = load_CBlock(-1);
	  HBlock _n2 = load_CBlock(-1);
	  CBlockIsAdverbialComparasion* ret = new CBlockIsAdverbialComparasion(_adverb, _n1, _n2);
	  return  std::shared_ptr<CBlockIsAdverbialComparasion>(ret);

  }


  HBlockEvery  load_CBlockEvery(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockEvery);
	  HBlock _n = load_CBlock(-1);
	  CBlockEvery* ret = new CBlockEvery(_n);
	  return  std::shared_ptr<CBlockEvery>(ret);

  }


  HBlockKindAction  load_CBlockKindAction(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindAction);
	  HBlockActionApply _applyTo = load_CBlockActionApply(-1);
	  CBlockKindAction* ret = new CBlockKindAction(_applyTo);
	  return  std::shared_ptr<CBlockKindAction>(ret);

  }


  HBlockMatchList  load_CBlockMatchList(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchList);
	  std::list<HBlockMatch> _matchList = load_list<CBlockMatch>();
	  CBlockMatchList* ret = new CBlockMatchList(_matchList);
	  return  std::shared_ptr<CBlockMatchList>(ret);

  }


  HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchIsNotVerb);
	  string _verb = load_string();
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchIsNotVerb* ret = new CBlockMatchIsNotVerb(_verb, _obj, _value);
	  return  std::shared_ptr<CBlockMatchIsNotVerb>(ret);

  }


  HBlockMatchDirectIs  load_CBlockMatchDirectIs(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchDirectIs);
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchDirectIs* ret = new CBlockMatchDirectIs(_obj, _value);
	  return  std::shared_ptr<CBlockMatchDirectIs>(ret);

  }


  HBlockUnitTest  load_CBlockUnitTest(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockUnitTest);
	  HBlock _contents = load_CBlock(-1);
	  CBlockUnitTest* ret = new CBlockUnitTest(_contents);
	  return  std::shared_ptr<CBlockUnitTest>(ret);

  }


  HBlockUnitInit  load_CBlockUnitInit(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockUnitInit);
	  HBlock _contents = load_CBlock(-1);
	  CBlockUnitInit* ret = new CBlockUnitInit(_contents);
	  return  std::shared_ptr<CBlockUnitInit>(ret);

  }


  HBlockRelationInstance  load_CBlockRelationInstance(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockRelationInstance);
	  HBlockRelationBase _relation = load_CBlockRelationBase(-1);
	  HBlock _value1 = load_CBlock(-1);
	  HBlock _value2 = load_CBlock(-1);
	  CBlockRelationInstance* ret = new CBlockRelationInstance(_relation, _value1, _value2);
	  return  std::shared_ptr<CBlockRelationInstance>(ret);

  }


  HBlockSelector_Where  load_CBlockSelector_Where(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockSelector_Where);
	  HBlock _what = load_CBlock(-1);
	  CBlockSelector_Where* ret = new CBlockSelector_Where(_what);
	  return  std::shared_ptr<CBlockSelector_Where>(ret);

  }


  HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isLocalVariable);
	  HBlockNoum _variableName = load_CBlockNoum(-1);
	  HBlock _valueExpression = load_CBlock(-1);
	  CBlockAssertion_isLocalVariable* ret = new CBlockAssertion_isLocalVariable(_variableName, _valueExpression);
	  return  std::shared_ptr<CBlockAssertion_isLocalVariable>(ret);

  }


  HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isInstanceOf);
	  HBlockInstance _noum = load_CBlockInstance(-1);
	  HBlockKind _baseKind = load_CBlockKind(-1);
	  CBlockAssertion_isInstanceOf* ret = new CBlockAssertion_isInstanceOf(_noum, _baseKind);
	  return  std::shared_ptr<CBlockAssertion_isInstanceOf>(ret);

  }


  HBlockControlIF  load_CBlockControlIF(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlIF);
	  HBlock _block_if = load_CBlock(-1);
	  HBlock _block_then = load_CBlock(-1);
	  HBlock _block_else = load_CBlock(-1);
	  CBlockControlIF* ret = new CBlockControlIF(_block_if, _block_then, _block_else);
	  return  std::shared_ptr<CBlockControlIF>(ret);

  }


  HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_InstanceVariable);
	  HBlock _noum = load_CBlock(-1);
	  HBlockInstanceVariable _instance_variable = load_CBlockInstanceVariable(-1);
	  CBlockAssertion_InstanceVariable* ret = new CBlockAssertion_InstanceVariable(_noum, _instance_variable);
	  return  std::shared_ptr<CBlockAssertion_InstanceVariable>(ret);

  }


  HBlockAssertion_isKindOf  load_CBlockAssertion_isKindOf(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isKindOf);
	  HBlockKind _noum = load_CBlockKind(-1);
	  HBlockKind _baseKind = load_CBlockKind(-1);
	  CBlockAssertion_isKindOf* ret = new CBlockAssertion_isKindOf(_noum, _baseKind);
	  return  std::shared_ptr<CBlockAssertion_isKindOf>(ret);

  }


  HBlockKindReference  load_CBlockKindReference(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindReference);
	  HBlockKind k = load_CBlockKind(-1);
	  CBlockKindReference* ret = new CBlockKindReference(k);
	  return  std::shared_ptr<CBlockKindReference>(ret);

  }


  HBlockIsVerb  load_CBlockIsVerb(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockIsVerb);
	  string _verb = load_string();
	  HBlock _n1 = load_CBlock(-1);
	  HBlock _n2 = load_CBlock(-1);
	  CBlockIsVerb* ret = new CBlockIsVerb(_verb, _n1, _n2);
	  return  std::shared_ptr<CBlockIsVerb>(ret);

  }


  HBlockActionInstance  load_CBlockActionInstance(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockActionInstance);
	  int _id = load_int();
	  HBlockKindAction _base_kind = load_CBlockKindAction(-1);
	  CBlockActionInstance* ret = new CBlockActionInstance(_id, _base_kind);
	  return  std::shared_ptr<CBlockActionInstance>(ret);

  }


  HBlockKindValue  load_CBlockKindValue(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindValue);
	  string _named = load_string();
	  CBlockKindValue* ret = new CBlockKindValue(_named);
	  return  std::shared_ptr<CBlockKindValue>(ret);

  }


  HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isDirectAssign);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockAssertion_isDirectAssign* ret = new CBlockAssertion_isDirectAssign(_variable, _value);
	  return  std::shared_ptr<CBlockAssertion_isDirectAssign>(ret);

  }


  HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isConstantAssign);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockAssertion_isConstantAssign* ret = new CBlockAssertion_isConstantAssign(_variable, _value);
	  return  std::shared_ptr<CBlockAssertion_isConstantAssign>(ret);

  }


  HBlockActionApply  load_CBlockActionApply(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockActionApply);
	  HBlock _noum1 = load_CBlock(-1);
	  HBlock _noum2 = load_CBlock(-1);
	  CBlockActionApply* ret = new CBlockActionApply(_noum1, _noum2);
	  return  std::shared_ptr<CBlockActionApply>(ret);

  }


  HBlockCompostionPhrase  load_CBlockCompostionPhrase(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockCompostionPhrase);
	  CBlockCompostionPhrase* ret = new CBlockCompostionPhrase();
	  return  std::shared_ptr<CBlockCompostionPhrase>(ret);

  }


  HBlockVariableNamed  load_CBlockVariableNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVariableNamed);
	  HBlockNoum _name = load_CBlockNoum(-1);
	  HBlockKind _kind = load_CBlockKind(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockVariableNamed* ret = new CBlockVariableNamed(_name, _kind, _value);
	  return  std::shared_ptr<CBlockVariableNamed>(ret);

  }


  HBlockActionCallNamed  load_CBlockActionCallNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockActionCallNamed);
	  HBlockActionNamed _action = load_CBlockActionNamed(-1);
	  HBlock _noum1 = load_CBlock(-1);
	  HBlock _noum2 = load_CBlock(-1);
	  CBlockActionCallNamed* ret = new CBlockActionCallNamed(_action, _noum1, _noum2);
	  return  std::shared_ptr<CBlockActionCallNamed>(ret);

  }


  HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isForbiddenAssign);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockAssertion_isForbiddenAssign* ret = new CBlockAssertion_isForbiddenAssign(_variable, _value);
	  return  std::shared_ptr<CBlockAssertion_isForbiddenAssign>(ret);

  }



  HBlockControlToken  load_CBlockControlToken(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlToken);
	  string _token = load_string();
	  HBlock _contents = load_CBlock(-1);
	  CBlockControlToken* ret = new CBlockControlToken(_token, _contents);
	  return  std::shared_ptr<CBlockControlToken>(ret);

  }



  HBlockSelector_Any  load_CBlockSelector_Any(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockSelector_Any);
	  HBlock _what = load_CBlock(-1);
	  CBlockSelector_Any* ret = new CBlockSelector_Any(_what);
	  return  std::shared_ptr<CBlockSelector_Any>(ret);

  }


  HBlockTryCall  load_CBlockTryCall(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockTryCall);
	  HBlock _sentence = load_CBlock(-1);
	  CBlockTryCall* ret = new CBlockTryCall(_sentence);
	  return  std::shared_ptr<CBlockTryCall>(ret);

  }


  HBlockSelectorAND  load_CBlockSelectorAND(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockSelectorAND);
	  HBlock _value1 = load_CBlock(-1);
	  HBlock _value2 = load_CBlock(-1);
	  CBlockSelectorAND* ret = new CBlockSelectorAND(_value1, _value2);
	  return  std::shared_ptr<CBlockSelectorAND>(ret);

  }


  HBlockEnums  load_CBlockEnums(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockEnums);
	  std::vector<HBlockNoum> _values = load_vector<CBlockNoum>();
	  CBlockEnums* ret = new CBlockEnums(_values);
	  return  std::shared_ptr<CBlockEnums>(ret);

  }



  HBlockPhraseHeader  load_CBlockPhraseHeader(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockPhraseHeader);
	  HBlockNoum _verb = load_CBlockNoum(-1);
	  HBlockNoum _pred1 = load_CBlockNoum(-1);
	  HBlockNoum _pred2 = load_CBlockNoum(-1);
	  HBlockMatch _arg1 = load_CBlockMatch(-1);
	  HBlockMatch _arg2 = load_CBlockMatch(-1);
	  CBlockPhraseHeader* ret = new CBlockPhraseHeader(_verb, _pred1, _pred2, _arg1, _arg2);
	  return  std::shared_ptr<CBlockPhraseHeader>(ret);

  }


  HBlockMatchBlock  load_CBlockMatchBlock(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchBlock);
	  HBlock _inner = load_CBlock(-1);
	  CBlockMatchBlock* ret = new CBlockMatchBlock(_inner);
	  return  std::shared_ptr<CBlockMatchBlock>(ret);

  }


  HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKind_InstanceVariable);
	  HBlockKind _kind = load_CBlockKind(-1);
	  HBlockInstanceVariable _variableNamed = load_CBlockInstanceVariable(-1);
	  CBlockKind_InstanceVariable* ret = new CBlockKind_InstanceVariable(_kind, _variableNamed);
	  return  std::shared_ptr<CBlockKind_InstanceVariable>(ret);

  }


  HBlockAssertion_canBe  load_CBlockAssertion_canBe(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_canBe);
	  HBlock _obj = load_CBlock(-1);
	  HBlockEnums _definition = load_CBlockEnums(-1);
	  CBlockAssertion_canBe* ret = new CBlockAssertion_canBe(_obj, _definition);
	  return  std::shared_ptr<CBlockAssertion_canBe>(ret);

  }


  HBlockStaticDispatch  load_CBlockStaticDispatch(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockStaticDispatch);
	  int _staticEntryTable = load_int();
	  HBlock _noum1 = load_CBlock(-1);
	  HBlock _noum2 = load_CBlock(-1);
	  CBlockStaticDispatch* ret = new CBlockStaticDispatch(_staticEntryTable, _noum1, _noum2);
	  return  std::shared_ptr<CBlockStaticDispatch>(ret);

  }


  HBlockUnderstandStatic  load_CBlockUnderstandStatic(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockUnderstandStatic);
	  int _entryID = load_int();
	  HBlockMatchList _argument_match = load_CBlockMatchList(-1);
	  HBlock _output_n = load_CBlock(-1);
	  CBlockUnderstandStatic* ret = new CBlockUnderstandStatic(_entryID, _argument_match, _output_n);
	  return  std::shared_ptr<CBlockUnderstandStatic>(ret);

  }


  HBlockSelector_All  load_CBlockSelector_All(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockSelector_All);
	  HBlock _what = load_CBlock(-1);
	  CBlockSelector_All* ret = new CBlockSelector_All(_what);
	  return  std::shared_ptr<CBlockSelector_All>(ret);

  }


  HBlockVerbReverseRelation  load_CBlockVerbReverseRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbReverseRelation);
	  HBlock _noum = load_CBlock(-1);
	  HBlockNoum _relationNoum = load_CBlockNoum(-1);
	  CBlockVerbReverseRelation* ret = new CBlockVerbReverseRelation(_noum, _relationNoum);
	  return  std::shared_ptr<CBlockVerbReverseRelation>(ret);

  }


  HBlockIntegerNumber  load_CBlockIntegerNumber(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockIntegerNumber);
	  int _value = load_int();
	  CBlockIntegerNumber* ret = new CBlockIntegerNumber(_value);
	  return  std::shared_ptr<CBlockIntegerNumber>(ret);

  }


  HBlockControlUnless  load_CBlockControlUnless(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockControlUnless);
	  HBlock _block_if = load_CBlock(-1);
	  HBlock _block_then = load_CBlock(-1);
	  HBlock _block_else = load_CBlock(-1);
	  CBlockControlUnless* ret = new CBlockControlUnless(_block_if, _block_then, _block_else);
	  return  std::shared_ptr<CBlockControlUnless>(ret);

  }


  HBlockCompositionList  load_CBlockCompositionList(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockCompositionList);
	  HBlockKind _itemKind = load_CBlockKind(-1);
	  CBlockCompositionList* ret = new CBlockCompositionList(_itemKind);
	  return  std::shared_ptr<CBlockCompositionList>(ret);

  }


  HBlockBooleanAND  load_CBlockBooleanAND(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockBooleanAND);
	  HBlock input_a = load_CBlock(-1);
	  HBlock input_b = load_CBlock(-1);
	  CBlockBooleanAND* ret = new CBlockBooleanAND(input_a, input_b);
	  return  std::shared_ptr<CBlockBooleanAND>(ret);

  }


  HBlockToDecideOn  load_CBlockToDecideOn(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockToDecideOn);
	  HBlock _decideBody = load_CBlock(-1);
	  CBlockToDecideOn* ret = new CBlockToDecideOn(_decideBody);
	  return  std::shared_ptr<CBlockToDecideOn>(ret);

  }


  HBlockRelationLookup  load_CBlockRelationLookup(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockRelationLookup);
	  string _relation = load_string();
	  HBlockMatch _value1 = load_CBlockMatch(-1);
	  HBlockMatch _value2 = load_CBlockMatch(-1);
	  NoumLocation _term_to_query = load_NoumLocation();
	  CBlockRelationLookup* ret = new CBlockRelationLookup(_relation, _value1, _value2, _term_to_query);
	  return  std::shared_ptr<CBlockRelationLookup>(ret);

  }


  HBlockBooleanOR  load_CBlockBooleanOR(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockBooleanOR);
	  HBlock input_a = load_CBlock(-1);
	  HBlock input_b = load_CBlock(-1);
	  CBlockBooleanOR* ret = new CBlockBooleanOR(input_a, input_b);
	  return  std::shared_ptr<CBlockBooleanOR>(ret);

  }



  HBlockList_OR  load_CBlockList_OR(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockList_OR);
	  std::list<HBlock> _lista = load_list<CBlock>();
	  CBlockList_OR* ret = new CBlockList_OR(_lista);
	  return  std::shared_ptr<CBlockList_OR>(ret);

  }


  HBlockInstanceNamed  load_CBlockInstanceNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockInstanceNamed);
	  string _named = load_string();
	  int _id = load_int();
	  HBlockKind _base = load_CBlockKind(-1);
	  CBlockInstanceNamed* ret = new CBlockInstanceNamed(_named, _id, _base);
	  return  std::shared_ptr<CBlockInstanceNamed>(ret);

  }


  HBlockNoumSupl  load_CBlockNoumSupl(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockNoumSupl);
	  string _named = load_string();
	  string _number = load_string();
	  string _gender = load_string();
	  CBlockNoumSupl* ret = new CBlockNoumSupl(_named, _number, _gender);
	  return  std::shared_ptr<CBlockNoumSupl>(ret);

  }


  HBlockPhraseInvoke  load_CBlockPhraseInvoke(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockPhraseInvoke);
	  HBlockPhraseHeader _header = load_CBlockPhraseHeader(-1);
	  HBlock _arg1 = load_CBlock(-1);
	  HBlock _arg2 = load_CBlock(-1);
	  CBlockPhraseInvoke* ret = new CBlockPhraseInvoke(_header, _arg1, _arg2);
	  return  std::shared_ptr<CBlockPhraseInvoke>(ret);

  }


  HBlockASimetricRelation  load_CBlockASimetricRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockASimetricRelation);
	  std::string _named = load_string();
	  HBlockArgumentInput input_a = load_CBlockArgumentInput(-1);
	  HBlockArgumentInput input_b = load_CBlockArgumentInput(-1);
	  bool _various_1 = load_bool();
	  bool _various_2 = load_bool();
	  CBlockASimetricRelation* ret = new CBlockASimetricRelation(_named, input_a, input_b, _various_1, _various_2);
	  return  std::shared_ptr<CBlockASimetricRelation>(ret);

  }


  HBlockMatchOR  load_CBlockMatchOR(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchOR);
	  std::list<HBlockMatch> _matchList = load_list<CBlockMatch>();
	  CBlockMatchOR* ret = new CBlockMatchOR(_matchList);
	  return  std::shared_ptr<CBlockMatchOR>(ret);

  }


  HBlockArgumentInput  load_CBlockArgumentInput(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockArgumentInput);
	  HBlockKind _kind = load_CBlockKind(-1);
	  string _named = load_string();
	  CBlockArgumentInput* ret = new CBlockArgumentInput(_kind, _named);
	  return  std::shared_ptr<CBlockArgumentInput>(ret);

  }


  HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isDefaultAssign);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _value = load_CBlock(-1);
	  CBlockAssertion_isDefaultAssign* ret = new CBlockAssertion_isDefaultAssign(_variable, _value);
	  return  std::shared_ptr<CBlockAssertion_isDefaultAssign>(ret);

  }


  HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchDirectIsNot);
	  HBlockMatch _obj = load_CBlockMatch(-1);
	  HBlockMatch _value = load_CBlockMatch(-1);
	  CBlockMatchDirectIsNot* ret = new CBlockMatchDirectIsNot(_obj, _value);
	  return  std::shared_ptr<CBlockMatchDirectIsNot>(ret);

  }


  HBlockVerbNegate  load_CBlockVerbNegate(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbNegate);
	  HBlockVerbAdapt _verbAdapt = load_CBlockVerbAdapt(-1);
	  CBlockVerbNegate* ret = new CBlockVerbNegate(_verbAdapt);
	  return  std::shared_ptr<CBlockVerbNegate>(ret);

  }


  HBlockAssertion_isVariable  load_CBlockAssertion_isVariable(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssertion_isVariable);
	  HBlock _variable = load_CBlock(-1);
	  HBlock _baseKind = load_CBlock(-1);
	  CBlockAssertion_isVariable* ret = new CBlockAssertion_isVariable(_variable, _baseKind);
	  return  std::shared_ptr<CBlockAssertion_isVariable>(ret);

  }


  HBlockVerbLookup  load_CBlockVerbLookup(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbLookup);
	  string _verb = load_string();
	  HBlockMatch _value1 = load_CBlockMatch(-1);
	  HBlockMatch _value2 = load_CBlockMatch(-1);
	  NoumLocation _term_to_query = load_NoumLocation();
	  CBlockVerbLookup* ret = new CBlockVerbLookup(_verb, _value1, _value2, _term_to_query);
	  return  std::shared_ptr<CBlockVerbLookup>(ret);

  }


  HBlockRelationArguments  load_CBlockRelationArguments(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockRelationArguments);
	  HBlock _value1 = load_CBlock(-1);
	  HBlock _value2 = load_CBlock(-1);
	  CBlockRelationArguments* ret = new CBlockRelationArguments(_value1, _value2);
	  return  std::shared_ptr<CBlockRelationArguments>(ret);

  }


  HBlockProperty  load_CBlockProperty(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockProperty);
	  HBlock _prop = load_CBlock(-1);
	  HBlock _obj = load_CBlock(-1);
	  CBlockProperty* ret = new CBlockProperty(_prop, _obj);
	  return  std::shared_ptr<CBlockProperty>(ret);

  }


  HBlockSimetricRelation  load_CBlockSimetricRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockSimetricRelation);
	  std::string _named = load_string();
	  HBlockArgumentInput input_a = load_CBlockArgumentInput(-1);
	  HBlockArgumentInput input_b = load_CBlockArgumentInput(-1);
	  bool _various_1 = load_bool();
	  bool _various_2 = load_bool();
	  CBlockSimetricRelation* ret = new CBlockSimetricRelation(_named, input_a, input_b, _various_1, _various_2);
	  return  std::shared_ptr<CBlockSimetricRelation>(ret);

  }


  HBlockMatchAny  load_CBlockMatchAny(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchAny);
	  CBlockMatchAny* ret = new CBlockMatchAny();
	  return  std::shared_ptr<CBlockMatchAny>(ret);

  }


  HBlockMatchNamed  load_CBlockMatchNamed(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchNamed);
	  string _named = load_string();
	  HBlockMatch _matchInner = load_CBlockMatch(-1);
	  CBlockMatchNamed* ret = new CBlockMatchNamed(_named, _matchInner);
	  return  std::shared_ptr<CBlockMatchNamed>(ret);

  }


  HBlockUnderstandDynamic  load_CBlockUnderstandDynamic(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockUnderstandDynamic);
	  HBlockMatch _input_n = load_CBlockMatch(-1);
	  HBlockMatchList _argumentMatchs = load_CBlockMatchList(-1);
	  HBlock _output_n = load_CBlock(-1);
	  CBlockUnderstandDynamic* ret = new CBlockUnderstandDynamic(_input_n, _argumentMatchs, _output_n);
	  return  std::shared_ptr<CBlockUnderstandDynamic>(ret);

  }


  HBlockMatchActionCall  load_CBlockMatchActionCall(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchActionCall);
	  HBlockMatch _action = load_CBlockMatch(-1);
	  HBlockMatch _argument1 = load_CBlockMatch(-1);
	  HBlockMatch _argument2 = load_CBlockMatch(-1);
	  CBlockMatchActionCall* ret = new CBlockMatchActionCall(_action, _argument1, _argument2);
	  return  std::shared_ptr<CBlockMatchActionCall>(ret);

  }


  HBlockCompositionPhrase  load_CBlockCompositionPhrase(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockCompositionPhrase);
	  HBlockKind _fromKind = load_CBlockKind(-1);
	  HBlockKind _toKind = load_CBlockKind(-1);
	  CBlockCompositionPhrase* ret = new CBlockCompositionPhrase(_fromKind, _toKind);
	  return  std::shared_ptr<CBlockCompositionPhrase>(ret);

  }


  HBlockDinamicDispatch  load_CBlockDinamicDispatch(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockDinamicDispatch);
	  HBlockList _command = load_CBlockList(-1);
	  CBlockDinamicDispatch* ret = new CBlockDinamicDispatch(_command);
	  return  std::shared_ptr<CBlockDinamicDispatch>(ret);

  }


  HBlockAssert  load_CBlockAssert(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockAssert);
	  HBlock _expression = load_CBlock(-1);
	  HBlock _result = load_CBlock(-1);
	  CBlockAssert* ret = new CBlockAssert(_expression, _result);
	  return  std::shared_ptr<CBlockAssert>(ret);

  }


  HBlockMatchNOT  load_CBlockMatchNOT(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchNOT);
	  HBlockMatch _input = load_CBlockMatch(-1);
	  CBlockMatchNOT* ret = new CBlockMatchNOT(_input);
	  return  std::shared_ptr<CBlockMatchNOT>(ret);

  }


  HBlockKindOf  load_CBlockKindOf(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockKindOf);
	  HBlockKind _baseClasse = load_CBlockKind(-1);
	  CBlockKindOf* ret = new CBlockKindOf(_baseClasse);
	  return  std::shared_ptr<CBlockKindOf>(ret);

  }


  HBlockComandList  load_CBlockComandList(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockComandList);
	  std::list<HBlock> _lista = load_list<CBlock>();
	  CBlockComandList* ret = new CBlockComandList(_lista);
	  return  std::shared_ptr<CBlockComandList>(ret);

  }


  HBlockNamedValue  load_CBlockNamedValue(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockNamedValue);
	  string _named = load_string();
	  CBlockNamedValue* ret = new CBlockNamedValue(_named);
	  return  std::shared_ptr<CBlockNamedValue>(ret);

  }


  HBlockIsNotVerb  load_CBlockIsNotVerb(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockIsNotVerb);
	  string _verb = load_string();
	  HBlock _n1 = load_CBlock(-1);
	  HBlock _n2 = load_CBlock(-1);
	  CBlockIsNotVerb* ret = new CBlockIsNotVerb(_verb, _n1, _n2);
	  return  std::shared_ptr<CBlockIsNotVerb>(ret);

  }


  HBlockVerbDirectRelation  load_CBlockVerbDirectRelation(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockVerbDirectRelation);
	  HBlock _noum = load_CBlock(-1);
	  HBlockNoum _relationNoum = load_CBlockNoum(-1);
	  CBlockVerbDirectRelation* ret = new CBlockVerbDirectRelation(_noum, _relationNoum);
	  return  std::shared_ptr<CBlockVerbDirectRelation>(ret);

  }


  HBlockMatchValue  load_CBlockMatchValue(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchValue);
	  HBlock _inner = load_CBlock(-1);
	  CBlockMatchValue* ret = new CBlockMatchValue(_inner);
	  return  std::shared_ptr<CBlockMatchValue>(ret);

  }


  HBlockMatchAND  load_CBlockMatchAND(int tp)
  {
	  if (tp == -1) tp = load_type();
	  cmp_type(tp, BlockType::BlockMatchAND);
	  std::list<HBlockMatch> _matchList = load_list<CBlockMatch>();
	  CBlockMatchAND* ret = new CBlockMatchAND(_matchList);
	  return  std::shared_ptr<CBlockMatchAND>(ret);

  }



 
