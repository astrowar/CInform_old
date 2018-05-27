
#include "serialize_tp.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "CBlockBoolean.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockNumber.hpp"
#include "CBlockControlFlux.hpp"

void store_type(BlockType tp , ArchiveContext *ar)
{
	ar->process_id(tp);
}

void store_type(VarSlotType tp, ArchiveContext *ar)
{
	ar->process(tp);
}

void store_block_i(CBlockVariableNamed* b, ArchiveContext * ar)
{
	store_block(b->kind , ar);
	store_block(b->name, ar);
	store_block(b->value, ar);	
}

 
void store_block_i(const CBlockEventHandle* b, ArchiveContext * ar)
{
	ar->process(b->stage);
	store_block(b->body, ar);
	store_block(b->eventToObserve, ar);
}
void store_block_i(const CBlockEvery* b, ArchiveContext * ar)
{
	store_block(b->assertation, ar);	
}

void store_block_i(const CBlockExecutionResultFlag* b, ArchiveContext * ar)
{
	ar->process(b->flag);
	store_block(b->contents, ar);
}
void store_block_i(const CBlockFactionalNumber* b, ArchiveContext * ar)
{
	ar->process(b->value);
}
void store_block_i(const CBlockFilter* b, ArchiveContext * ar)
{	
}
void store_block_i(const CBlockFilterAtom* b, ArchiveContext * ar)
{	
}
void store_block_i(const CBlockFilterList* b, ArchiveContext * ar)
{	
}
void store_block_i(const CBlockIF* b, ArchiveContext * ar)
{	
}
void store_block_i(const CBlockInstance* b, ArchiveContext * ar)
{
	ar->process(b->id);
	store_block(b->baseKind, ar);
	store_block(b->anomimousSlots, ar);
	store_block(b->namedSlots, ar);
}
void store_block_i(const CBlockInstanceNamed* b, ArchiveContext * ar)
{
	ar->process(b->id); 
	ar->process(b->named);
	store_block(b->baseKind, ar);
	store_block(b->anomimousSlots, ar);
	store_block(b->namedSlots, ar);
}
void store_block_i(const CBlockInstanceVariable* b, ArchiveContext * ar)
{
	store_block(b->kind_name, ar);
	store_block(b->property_name, ar);
}
void store_block_i(const CBlockIntegerNumber* b, ArchiveContext * ar)
{
	ar->process(b->value); 
}

void store_block_i(const CBlockIsAdverbialComparasion* b, ArchiveContext * ar)
{
	ar->process(b->adverb);
	store_block(b->n1, ar);
	store_block(b->n2, ar);
}
void store_block_i(const CBlockIsNotVerb* b, ArchiveContext * ar)
{
	ar->process(b->verb); 
	store_block(b->n1, ar);
	store_block(b->n2, ar);
}
void store_block_i(const CBlockIsVerb* b, ArchiveContext * ar)
{
	ar->process(b->verb); 
	store_block(b->n1, ar);
	store_block(b->n2, ar);
}
void store_block_i(const CBlockKind* b, ArchiveContext * ar)
{
	
}
void store_block_i(const CBlockKind_InstanceVariable* b, ArchiveContext * ar)
{
	store_block(b->kind, ar);
	store_block(b->variableNamed, ar);
}


void store_block_i(const CBlockActionInstance* b, ArchiveContext * ar)
{
	ar->process(b->id);
	store_block(b->base_kind, ar);
	store_block(b->namedSlots, ar);
}
void store_block_i(const CBlockActionNamed* b, ArchiveContext * ar)
{
	ar->process(b->named);
	store_block(b->actionKind, ar);
}
void store_block_i(const CBlockAnything* b, ArchiveContext * ar)
{
	ar->process(b->named);
}
void store_block_i(const CBlockArgumentInput* b, ArchiveContext * ar)
{
	ar->process(b->named);
	store_block(b->kind, ar);
}
void store_block_i(const CBlockASimetricRelation* b, ArchiveContext * ar)
{
	ar->process(b->named);
	ar->process(b->various_noum1);
	ar->process(b->various_noum2);
	store_block(b->input_A, ar);
	store_block(b->input_B, ar);

}
void store_block_i(const CBlockAssert* b, ArchiveContext * ar)
{
	store_block(b->expression, ar);
	store_block(b->result, ar);
}
 

void store_block_i(const CBlockAssertion_canBe* b, ArchiveContext * ar)
{
	store_block(b->definition, ar);
	store_block(b->obj, ar);
}
void store_block_i(const CBlockAssertion_InstanceVariable* b, ArchiveContext * ar)
{
	store_block(b->noum, ar);
	store_block(b->instance_variable, ar);
}
void store_block_i(const CBlockAssertion_is* b, ArchiveContext * ar)
{
	
}
void store_block_i(const CBlockAssertion_isActionOf* b, ArchiveContext * ar)
{
	store_block(b->noum , ar);
	store_block(b->action, ar);
	store_block(b->application, ar);	
}
void store_block_i(const CBlockAssertion_isConstantAssign* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->value, ar);	
}
void store_block_i(const CBlockAssertion_isDefaultAssign* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->value, ar);
}
void store_block_i(const CBlockAssertion_isDirectAssign* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->value, ar);
}
void store_block_i(const CBlockAssertion_isForbiddenAssign* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->value, ar);
}
void store_block_i(const CBlockAssertion_isInstanceOf* b, ArchiveContext * ar)
{	
		store_block(b->baseKind, ar);
		store_block(b->noum, ar);		
}
void store_block_i(const CBlockAssertion_isKindOf* b, ArchiveContext * ar)
{
	store_block(b->baseKind, ar);
	store_block(b->noum, ar);
}
void store_block_i(const CBlockAssertion_isLocalVariable* b, ArchiveContext * ar)
{	
		store_block(b->variableName, ar);
		store_block(b->valueExpression, ar);	
}
void store_block_i(const CBlockAssertion_isNamedValueOf* b, ArchiveContext * ar)
{
	store_block(b->baseKind, ar);
	store_block(b->noum, ar);
}
void store_block_i(const CBlockAssertion_isNotDirectAssign* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->value, ar);
}
void store_block_i(const CBlockAssertion_isVariable* b, ArchiveContext * ar)
{
	store_block(b->variable, ar);
	store_block(b->baseKind, ar);
}
void store_block_i(const CBlockAssertionBase* b, ArchiveContext * ar)
{
	
}
void store_block_i(const CBlockAssertionCond* b, ArchiveContext * ar)
{
	store_block(b->cond, ar);	
}


void store_block_i(const CBlockAction* b, ArchiveContext * ar)
{
 
}
void store_block_i(const CBlockActionApply* b, ArchiveContext * ar)
{
	store_block(b->noum1, ar);
	store_block(b->noum2, ar);
}

void store_block_i(const CBlockActionCall* b, ArchiveContext * ar)
{
	store_block(b->noum1, ar);
	store_block(b->noum2, ar);
}

void store_block_i(const CBlockActionCallNamed* b, ArchiveContext * ar)
{
	store_block(b->action, ar);
	store_block(b->noum1, ar);
	store_block(b->noum2, ar);
}

//===============================================================================

void store_block_i(const CBlockBooleanAND* b, ArchiveContext * ar)
{
	store_block(b->input_A, ar);
	store_block(b->input_B, ar);
}

void store_block_i(const CBlockBooleanNOT* b, ArchiveContext * ar)
{
	store_block(b->input_A, ar);
	
}
void store_block_i(const CBlockBooleanOR* b, ArchiveContext * ar)
{
	store_block(b->input_A, ar);
	store_block(b->input_B, ar);
}
void store_block_i(const CBlockBooleanResult* b, ArchiveContext * ar)
{
	
}

void store_block_i(const CBlockBooleanValue* b, ArchiveContext * ar)
{
	ar->process(b->state ); 
}
void store_block_i(const CBlockComandList* b, ArchiveContext * ar)
{
	store_block(b->lista, ar);
}
void store_block_i(const CBlockCompostionPhrase* b, ArchiveContext * ar)
{
	
}
void store_block_i(const CBlockConditionalRelation* b, ArchiveContext * ar)
{
	store_block(b->coditional, ar);
	store_block(b->relation, ar);
}
void store_block_i(const CBlockControlForEach* b, ArchiveContext * ar)
{
	store_block(b->block_body, ar);
	store_block(b->block_variable, ar);
}
void store_block_i(const CBlockControlIF* b, ArchiveContext * ar)
{
	store_block(b->block_if, ar);
	store_block(b->block_then, ar);
	store_block(b->block_else, ar);
}
void store_block_i(const CBlockControlSelect* b, ArchiveContext * ar)
{
	store_block(b->block_seletor, ar);
	store_block(b->block_selectList, ar);
	store_block(b->block_else, ar);
}

void store_block_i(const CBlockControlSelectItem* b, ArchiveContext * ar)
{
	store_block(b->block_seletor, ar);
	store_block(b->block_execute, ar);	
}
void store_block_i(const CBlockControlToken* b, ArchiveContext * ar)
{
	ar->process(b->token);
	store_block(b->contents, ar);
}
void store_block_i(const CBlockControlUnless* b, ArchiveContext * ar)
{
	store_block(b->block_if, ar);
	store_block(b->block_then, ar);
	store_block(b->block_else, ar);
}
void store_block_i(const CBlockDinamicDispatch* b, ArchiveContext * ar)
{
	store_block(b->commandList, ar);	
}



//================================================================================





void store_block(CBlocking::HBlock  s, ArchiveContext *ar)
{
  const BlockType tp = s->type();

  store_type(tp,ar);

  if (tp == BlockAction) { const HBlockAction x = std::dynamic_pointer_cast < CBlockAction > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockActionApply) { const HBlockActionApply x = std::dynamic_pointer_cast < CBlockActionApply > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockActionCall) { const HBlockActionCall x = std::dynamic_pointer_cast < CBlockActionCall > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockActionCallNamed) { const HBlockActionCallNamed x = std::dynamic_pointer_cast < CBlockActionCallNamed > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockActionInstance) { const HBlockActionInstance x = std::dynamic_pointer_cast < CBlockActionInstance > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockActionNamed) { const HBlockActionNamed x = std::dynamic_pointer_cast < CBlockActionNamed > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAnything) { const HBlockAnything x = std::dynamic_pointer_cast < CBlockAnything > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockArgumentInput) { const HBlockArgumentInput x = std::dynamic_pointer_cast < CBlockArgumentInput > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockASimetricRelation) { const HBlockASimetricRelation x = std::dynamic_pointer_cast < CBlockASimetricRelation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssert) { const HBlockAssert x = std::dynamic_pointer_cast < CBlockAssert > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_canBe) { const HBlockAssertion_canBe x = std::dynamic_pointer_cast < CBlockAssertion_canBe > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_InstanceVariable) { const HBlockAssertion_InstanceVariable x = std::dynamic_pointer_cast < CBlockAssertion_InstanceVariable > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockAssertion_is) { const HBlockAssertion_is x = std::dynamic_pointer_cast < CBlockAssertion_is > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isActionOf) { const HBlockAssertion_isActionOf x = std::dynamic_pointer_cast < CBlockAssertion_isActionOf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isConstantAssign) { const HBlockAssertion_isConstantAssign x = std::dynamic_pointer_cast < CBlockAssertion_isConstantAssign > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isDefaultAssign) { const HBlockAssertion_isDefaultAssign x = std::dynamic_pointer_cast < CBlockAssertion_isDefaultAssign > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isDirectAssign) { const HBlockAssertion_isDirectAssign x = std::dynamic_pointer_cast < CBlockAssertion_isDirectAssign > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isForbiddenAssign) { const HBlockAssertion_isForbiddenAssign x = std::dynamic_pointer_cast < CBlockAssertion_isForbiddenAssign > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isInstanceOf) { const HBlockAssertion_isInstanceOf x = std::dynamic_pointer_cast < CBlockAssertion_isInstanceOf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isKindOf) { const HBlockAssertion_isKindOf x = std::dynamic_pointer_cast < CBlockAssertion_isKindOf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isLocalVariable) { const HBlockAssertion_isLocalVariable x = std::dynamic_pointer_cast < CBlockAssertion_isLocalVariable > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isNamedValueOf) { const HBlockAssertion_isNamedValueOf x = std::dynamic_pointer_cast < CBlockAssertion_isNamedValueOf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isNotDirectAssign) { const HBlockAssertion_isNotDirectAssign x = std::dynamic_pointer_cast < CBlockAssertion_isNotDirectAssign > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockAssertion_isVariable) { const HBlockAssertion_isVariable x = std::dynamic_pointer_cast < CBlockAssertion_isVariable > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockAssertionBase) { const HBlockAssertionBase x = std::dynamic_pointer_cast < CBlockAssertionBase > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockAssertionCond) { const HBlockAssertionCond x = std::dynamic_pointer_cast < CBlockAssertionCond > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockBooleanAND) { const HBlockBooleanAND x = std::dynamic_pointer_cast < CBlockBooleanAND > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockBooleanNOT) { const HBlockBooleanNOT x = std::dynamic_pointer_cast < CBlockBooleanNOT > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockBooleanOR) { const HBlockBooleanOR x = std::dynamic_pointer_cast < CBlockBooleanOR > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockBooleanResult) { const HBlockBooleanResult x = std::dynamic_pointer_cast < CBlockBooleanResult > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockBooleanValue) { const HBlockBooleanValue x = std::dynamic_pointer_cast < CBlockBooleanValue > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockComandList) { const HBlockComandList x = std::dynamic_pointer_cast < CBlockComandList > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockCompostionPhrase) { const HBlockCompostionPhrase x = std::dynamic_pointer_cast < CBlockCompostionPhrase > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockConditionalRelation) { const HBlockConditionalRelation x = std::dynamic_pointer_cast < CBlockConditionalRelation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockControlForEach) { const HBlockControlForEach x = std::dynamic_pointer_cast < CBlockControlForEach > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockControlIF) { const HBlockControlIF x = std::dynamic_pointer_cast < CBlockControlIF > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockControlSelect) { const HBlockControlSelect x = std::dynamic_pointer_cast < CBlockControlSelect > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockControlSelectItem) { const HBlockControlSelectItem x = std::dynamic_pointer_cast < CBlockControlSelectItem > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockControlToken) { const HBlockControlToken x = std::dynamic_pointer_cast < CBlockControlToken > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockControlUnless) { const HBlockControlUnless x = std::dynamic_pointer_cast < CBlockControlUnless > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockDinamicDispatch) { const HBlockDinamicDispatch x = std::dynamic_pointer_cast < CBlockDinamicDispatch > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockEnums) { const HBlockEnums x = std::dynamic_pointer_cast < CBlockEnums > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockEventHandle) { const HBlockEventHandle x = std::dynamic_pointer_cast < CBlockEventHandle > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockEvery) { const HBlockEvery x = std::dynamic_pointer_cast < CBlockEvery > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockExecutionResultFlag) { const HBlockExecutionResultFlag x = std::dynamic_pointer_cast < CBlockExecutionResultFlag > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockFactionalNumber) { const HBlockFactionalNumber x = std::dynamic_pointer_cast < CBlockFactionalNumber > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockFilter) { const HBlockFilter x = std::dynamic_pointer_cast < CBlockFilter > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockFilterAtom) { const HBlockFilterAtom x = std::dynamic_pointer_cast < CBlockFilterAtom > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockFilterList) { const HBlockFilterList x = std::dynamic_pointer_cast < CBlockFilterList > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockIF) { const HBlockIF x = std::dynamic_pointer_cast < CBlockIF > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockInstance) { const HBlockInstance x = std::dynamic_pointer_cast < CBlockInstance > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockInstanceNamed) { const HBlockInstanceNamed x = std::dynamic_pointer_cast < CBlockInstanceNamed > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockInstanceVariable) { const HBlockInstanceVariable x = std::dynamic_pointer_cast < CBlockInstanceVariable > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockIntegerNumber) { const HBlockIntegerNumber x = std::dynamic_pointer_cast < CBlockIntegerNumber > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockIsAdverbialComparasion) { const HBlockIsAdverbialComparasion x = std::dynamic_pointer_cast < CBlockIsAdverbialComparasion > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockIsNotVerb) { const HBlockIsNotVerb x = std::dynamic_pointer_cast < CBlockIsNotVerb > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockIsVerb) { const HBlockIsVerb x = std::dynamic_pointer_cast < CBlockIsVerb > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKind) { const HBlockKind x = std::dynamic_pointer_cast < CBlockKind > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKind_InstanceVariable) { const HBlockKind_InstanceVariable x = std::dynamic_pointer_cast < CBlockKind_InstanceVariable > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindAction) { const HBlockKindAction x = std::dynamic_pointer_cast < CBlockKindAction > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindEntity) { const HBlockKindEntity x = std::dynamic_pointer_cast < CBlockKindEntity > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindNamed) { const HBlockKindNamed x = std::dynamic_pointer_cast < CBlockKindNamed > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindOf) { const HBlockKindOf x = std::dynamic_pointer_cast < CBlockKindOf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindOfName) { const HBlockKindOfName x = std::dynamic_pointer_cast < CBlockKindOfName > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindReference) { const HBlockKindReference x = std::dynamic_pointer_cast < CBlockKindReference > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockKindValue) { const HBlockKindValue x = std::dynamic_pointer_cast < CBlockKindValue > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockList) { const HBlockList x = std::dynamic_pointer_cast < CBlockList > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockList_AND) { const HBlockList_AND x = std::dynamic_pointer_cast < CBlockList_AND > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockList_OR) { const HBlockList_OR x = std::dynamic_pointer_cast < CBlockList_OR > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockMatch) { const HBlockMatch x = std::dynamic_pointer_cast < CBlockMatch > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockMatchAction) { const HBlockMatchAction x = std::dynamic_pointer_cast < CBlockMatchAction > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchActionCall) { const HBlockMatchActionCall x = std::dynamic_pointer_cast < CBlockMatchActionCall > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchAND) { const HBlockMatchAND x = std::dynamic_pointer_cast < CBlockMatchAND > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchAny) { const HBlockMatchAny x = std::dynamic_pointer_cast < CBlockMatchAny > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchBlock) { const HBlockMatchBlock x = std::dynamic_pointer_cast < CBlockMatchBlock > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchDirectIs) { const HBlockMatchDirectIs x = std::dynamic_pointer_cast < CBlockMatchDirectIs > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchDirectIsNot) { const HBlockMatchDirectIsNot x = std::dynamic_pointer_cast < CBlockMatchDirectIsNot > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockMatchIs) { const HBlockMatchIs x = std::dynamic_pointer_cast < CBlockMatchIs > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchIsAdverbialComparasion) { const HBlockMatchIsAdverbialComparasion x = std::dynamic_pointer_cast < CBlockMatchIsAdverbialComparasion > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchIsNotVerb) { const HBlockMatchIsNotVerb x = std::dynamic_pointer_cast < CBlockMatchIsNotVerb > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchIsVerb) { const HBlockMatchIsVerb x = std::dynamic_pointer_cast < CBlockMatchIsVerb > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchKind) { const HBlockMatchKind x = std::dynamic_pointer_cast < CBlockMatchKind > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchList) { const HBlockMatchList x = std::dynamic_pointer_cast < CBlockMatchList > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchNamed) { const HBlockMatchNamed x = std::dynamic_pointer_cast < CBlockMatchNamed > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchNOT) { const HBlockMatchNOT x = std::dynamic_pointer_cast < CBlockMatchNOT > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchNoum) { const HBlockMatchNoum x = std::dynamic_pointer_cast < CBlockMatchNoum > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchOR) { const HBlockMatchOR x = std::dynamic_pointer_cast < CBlockMatchOR > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchProperty) { const HBlockMatchProperty x = std::dynamic_pointer_cast < CBlockMatchProperty > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchValue) { const HBlockMatchValue x = std::dynamic_pointer_cast < CBlockMatchValue > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchWhich) { const HBlockMatchWhich x = std::dynamic_pointer_cast < CBlockMatchWhich > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockMatchWhichNot) { const HBlockMatchWhichNot x = std::dynamic_pointer_cast < CBlockMatchWhichNot > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockMatchWith) { const HBlockMatchWith x = std::dynamic_pointer_cast < CBlockMatchWith > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockNamedValue) { const HBlockNamedValue x = std::dynamic_pointer_cast < CBlockNamedValue > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockNothing) { const HBlockNothing x = std::dynamic_pointer_cast < CBlockNothing > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockNoum) { const HBlockNoum x = std::dynamic_pointer_cast < CBlockNoum > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockNoumSupl) { const HBlockNoumSupl x = std::dynamic_pointer_cast < CBlockNoumSupl > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockNow) { const HBlockNow x = std::dynamic_pointer_cast < CBlockNow > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockNumber) { const HBlockNumber x = std::dynamic_pointer_cast < CBlockNumber > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockPhraseDefine) { const HBlockPhraseDefine x = std::dynamic_pointer_cast < CBlockPhraseDefine > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockPhraseHeader) { const HBlockPhraseHeader x = std::dynamic_pointer_cast < CBlockPhraseHeader > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockPhraseInvoke) { const HBlockPhraseInvoke x = std::dynamic_pointer_cast < CBlockPhraseInvoke > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockProperty) { const HBlockProperty x = std::dynamic_pointer_cast < CBlockProperty > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockRelationArguments) { const HBlockRelationArguments x = std::dynamic_pointer_cast < CBlockRelationArguments > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockRelationBase) { const HBlockRelationBase x = std::dynamic_pointer_cast < CBlockRelationBase > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockRelationInstance) { const HBlockRelationInstance x = std::dynamic_pointer_cast < CBlockRelationInstance > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockRelationLookup) { const HBlockRelationLookup x = std::dynamic_pointer_cast < CBlockRelationLookup > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockSame) { const HBlockSame x = std::dynamic_pointer_cast < CBlockSame > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockSelector) { const HBlockSelector x = std::dynamic_pointer_cast < CBlockSelector > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockSelector_All) { const HBlockSelector_All x = std::dynamic_pointer_cast < CBlockSelector_All > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockSelector_Any) { const HBlockSelector_Any x = std::dynamic_pointer_cast < CBlockSelector_Any > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockSelector_Where) { const HBlockSelector_Where x = std::dynamic_pointer_cast < CBlockSelector_Where > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockSelectorAND) { const HBlockSelectorAND x = std::dynamic_pointer_cast < CBlockSelectorAND > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockSimetricRelation) { const HBlockSimetricRelation x = std::dynamic_pointer_cast < CBlockSimetricRelation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockStaticDispatch) { const HBlockStaticDispatch x = std::dynamic_pointer_cast < CBlockStaticDispatch > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockText) { const HBlockText x = std::dynamic_pointer_cast < CBlockText > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockTextSentence) { const HBlockTextSentence x = std::dynamic_pointer_cast < CBlockTextSentence > (s); store_block_i(x.get(), ar); return; }
  //if (tp == BlockToDecide) { const HBlockToDecide x = std::dynamic_pointer_cast < CBlockToDecide > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockToDecideIf) { const HBlockToDecideIf x = std::dynamic_pointer_cast < CBlockToDecideIf > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockToDecideOn) { const HBlockToDecideOn x = std::dynamic_pointer_cast < CBlockToDecideOn > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockToDecideWhat) { const HBlockToDecideWhat x = std::dynamic_pointer_cast < CBlockToDecideWhat > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockToDecideWhat_FirstNoum) { const HBlockToDecideWhat_FirstNoum x = std::dynamic_pointer_cast < CBlockToDecideWhat_FirstNoum > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockToDecideWhether) { const HBlockToDecideWhether x = std::dynamic_pointer_cast < CBlockToDecideWhether > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockTransform) { const HBlockTransform x = std::dynamic_pointer_cast < CBlockTransform > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockTryCall) { const HBlockTryCall x = std::dynamic_pointer_cast < CBlockTryCall > (s); store_block_i(x.get(), ar); return; }
//  if (tp == BlockUnderstand) { const HBlockUnderstand x = std::dynamic_pointer_cast < CBlockUnderstand > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockUnderstandDynamic) { const HBlockUnderstandDynamic x = std::dynamic_pointer_cast < CBlockUnderstandDynamic > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockUnderstandStatic) { const HBlockUnderstandStatic x = std::dynamic_pointer_cast < CBlockUnderstandStatic > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockUnitAssert) { const HBlockUnitAssert x = std::dynamic_pointer_cast < CBlockUnitAssert > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockUnitInit) { const HBlockUnitInit x = std::dynamic_pointer_cast < CBlockUnitInit > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockUnitTest) { const HBlockUnitTest x = std::dynamic_pointer_cast < CBlockUnitTest > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockValue) { const HBlockValue x = std::dynamic_pointer_cast < CBlockValue > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerb) { const HBlockVerb x = std::dynamic_pointer_cast < CBlockVerb > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbAdapt) { const HBlockVerbAdapt x = std::dynamic_pointer_cast < CBlockVerbAdapt > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbConjugation) { const HBlockVerbConjugation x = std::dynamic_pointer_cast < CBlockVerbConjugation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbDirectRelation) { const HBlockVerbDirectRelation x = std::dynamic_pointer_cast < CBlockVerbDirectRelation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbLookup) { const HBlockVerbLookup x = std::dynamic_pointer_cast < CBlockVerbLookup > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbNegate) { const HBlockVerbNegate x = std::dynamic_pointer_cast < CBlockVerbNegate > (s); store_block_i(x.get(), ar); return; }
 // if (tp == BlockVerbRelation) { const HBlockVerbRelation x = std::dynamic_pointer_cast < CBlockVerbRelation > (s); store_block_i(x.get(), ar); return; }
  if (tp == BlockVerbReverseRelation) { const HBlockVerbReverseRelation x = std::dynamic_pointer_cast < CBlockVerbReverseRelation > (s); store_block_i(x.get(), ar); return; }
  //if (tp == BlockExecution) { const HBlockExecution x = std::dynamic_pointer_cast < CBlockExecution > (s); store_block_i(x.get(), ar); return; }
   
}



 void store_block_i(const CVariableSlotBool* b, ArchiveContext * ar)
{
	ar->process(b->value );
	store_block(b->valueDefinition, ar);	 
}


 void store_block_i(const CVariableSlotEnum* b, ArchiveContext * ar)
 { 
	 store_block(b->value, ar);
	 store_block(b->valueDefinition, ar);
 }


void store_block( HVariableSlot  s, ArchiveContext *ar)
{
	const VarSlotType tp = s->type ();

	store_type(tp, ar);

	if (tp == VarSlotType::BoolSlot ) { const HVariableSlotBool x = std::dynamic_pointer_cast <CVariableSlotBool> (s); store_block_i(x.get(), ar); return; }
	if (tp == VarSlotType::EnumSlot) { const HVariableSlotEnum x = std::dynamic_pointer_cast <CVariableSlotEnum> (s); store_block_i(x.get(), ar); return; }

}




 template<typename T>   void store_block(std::vector<T> s, ArchiveContext *ar)
{
	ar->process_flag("VECTOR", s.size());
	for(T &v: s) store_block(v, ar);
}

template< >   void store_block(std::vector<HBlock> s, ArchiveContext *ar)
{
	ar->process_flag("VECTOR", s.size());
	for (HBlock &v : s) store_block(v, ar);
}

template< >   void store_block(std::vector<HVariableSlot> s, ArchiveContext *ar)
{
	ar->process_flag("VECTOR", s.size());
	for (HVariableSlot &v : s) store_block(v , ar);
}

template<typename T>  void store_block(std::list<T> s, ArchiveContext *ar)
{
	ar->process_flag("LIST", s.size());
	for (T &v : s) store_block(v, ar);
}