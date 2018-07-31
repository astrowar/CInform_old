
 
#include "CBlockBoolean.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockNumber.hpp"
#include "CBlockControlFlux.hpp"
#include "CBlockComposition.hpp"
#include "sharedCast.hpp"
 
 
#include "save_ctx.hpp"
#include <CblockAssertion.hpp>

using namespace CBlocking;

void SaveContext::write(string s)
{   
	data += s + " ";
	//sprintf(file ,"%s ", s.c_str());
}
void SaveContext::write(int i)
{
	data += std::to_string(i) + " ";
	//fprintf(file, "%d ", i);
}
void SaveContext::write(float x)
{
	data += std::to_string(x) + " ";
	//fprintf(file, "%f ", x);
}

void SaveContext::end_line()
{
	data += "\n";
	//fprintf(file, "\r\n");
}

int cached(CBlock *c, SaveContext *ctx)
{
	if (c->type() == BlockNoumStr)
	{
		for(auto kv : ctx->locals)
		{
			if(kv.first->type() == BlockNoumStr)
			{
				CBlockNoum  *b = static_cast<CBlockNoumStr*>(kv.first);
				CBlockNoum  *bn = static_cast<CBlockNoumStr*>(c);
				if (b->named() == bn->named()) return kv.second;
			}
		}
	}
	auto it = ctx->locals.find(c);
	if (it != ctx->locals.end()) return it->second;
	return -1;
}
int add_cached(int i , CBlock *c, SaveContext *ctx)
{
	ctx->locals[c] = i;
	return i;
}

void lock_ptr(CBlock *c, SaveContext *ctx)
{
	if(ctx->locked.find(c) != ctx->locked.end())
	{
		return;
	}
	ctx->locked.insert(c);
}

int  alloc_slot(CBlock *c ,SaveContext *ctx)
{
	ctx->locals[c] = ctx->current_id;
	ctx->current_id++;
	ctx->write(ctx->current_id - 1);
	return ctx->current_id-1;
 
}
void save_type( BlockType t, SaveContext *ctx)
{
	//ctx->write("T");
	ctx->write(static_cast<int>(t));
}; 
void save_id(int _value, SaveContext *ctx)
{	 
	ctx->write(static_cast<int>(_value));
};
void save_int(int _value, SaveContext *ctx)
{	 
	ctx->write(static_cast<int>(_value));
};
void save_float(float _value, SaveContext *ctx)
{
	ctx->write(_value);
};
void save_bool(bool _value, SaveContext *ctx)
{
	if (_value) { ctx->write("true"); }
	else { ctx->write("false"); }
};
void end_slot(CBlock *c, SaveContext *ctx)
{
	ctx->locked.erase(c);
	ctx->end_line(); 
};
void save_string(std::string s, SaveContext *ctx)
{
	ctx->write("'"+s+"'" );
};
void save_NoumLocation(NoumLocation v , SaveContext *ctx)
{
	//ctx->write("NL");
	ctx->write(static_cast<int>(v));
};
void save_EventHandleStage(EventHandleStage stage, SaveContext* ctx)
{
	//ctx->write("ES");
	ctx->write(static_cast<int>(stage));
}
void save_PhaseResultFlag(PhaseResultFlag flag, SaveContext* ctx)
{
	//ctx->write("PRF");
	ctx->write(static_cast<int>(flag));
}


int  save_CBlock(HBlock x, SaveContext * ctx);
 
template<typename T>  std::list< int  >  save_vector(std::vector<std::shared_ptr<T> > s, SaveContext *ctx)
{
	std::list< int  > q;
	for (auto si : s) q.push_back(save_CBlock(si,ctx));
	return q;
}
 
template<typename T>  std::list< int  >  save_list(std::list<std::shared_ptr<T> > s, SaveContext *ctx)
{
	std::list< int  > q;
	for (auto si : s) q.push_back(save_CBlock(si,ctx));
	return q;
}
 
void save_id_list(const std::list<int>& i_list, SaveContext* ctx)
{
	ctx->write(" ( ");	
	for(auto i : i_list)  save_int(i , ctx);
	ctx->write(" ) ");
}

void raiseError()
{
	printf("Some Error !\n");
};
 





 
 
 
  



 
 
 
 
 
	int  save_CBlockInstance_base(HBlockInstance x, SaveContext *ctx);
  int  save_CBlockInstance(HBlockInstance x, SaveContext *ctx);
  int  save_CBlockInstanceAnonymous(HBlockInstanceAnonymous x, SaveContext *ctx);
  int  save_CBlockInstanceNamed(HBlockInstanceNamed x, SaveContext *ctx);
  int  save_CBlockText(HBlockText x, SaveContext *ctx);
  int  save_CBlockTextSentence(HBlockTextSentence x, SaveContext *ctx);
  int  save_CBlockValue_base(HBlockValue x, SaveContext *ctx);
  int  save_CBlockValue(HBlockValue x, SaveContext *ctx);
  int  save_CBlockKindReference(HBlockKindReference x, SaveContext *ctx);
  int  save_CBlockNoum_base(HBlockNoum x, SaveContext *ctx);
  int  save_CBlockNoum(HBlockNoum x, SaveContext *ctx);
  int  save_CBlockNoumStr(HBlockNoumStr x, SaveContext *ctx);
  int  save_CBlockNoumStrDet(HBlockNoumStrDet x, SaveContext *ctx);
  int  save_CBlockNoumCompose(HBlockNoumCompose x, SaveContext *ctx); 
  int  save_CBlockNoumSupl(HBlockNoumSupl x, SaveContext *ctx);
  int  save_CBlockKindNamed(HBlockKindNamed x, SaveContext *ctx);
  int  save_CBlockNothing(HBlockNothing x, SaveContext *ctx);
  int  save_CBlockAnything(HBlockAnything x, SaveContext *ctx);
  int  save_CBlockKindOfName(HBlockKindOfName x, SaveContext *ctx);
  int  save_CBlockKindOf(HBlockKindOf x, SaveContext *ctx);
  int  save_CBlockActionApply(HBlockActionApply x, SaveContext *ctx);
  int  save_CBlockKindAction(HBlockKindAction x, SaveContext *ctx);
  int  save_CBlockKindValue(HBlockKindValue x, SaveContext *ctx);
  int  save_CBlockKindEntity(HBlockKindEntity x, SaveContext *ctx);
  int  save_CBlockNamedValue(HBlockNamedValue x, SaveContext *ctx);
  int  save_CBlockProperty(HBlockProperty x, SaveContext *ctx);
  int  save_CBlockInstanceVariable(HBlockInstanceVariable x, SaveContext *ctx);
  int  save_CBlockKind_InstanceVariable(HBlockKind_InstanceVariable x, SaveContext *ctx);
  int  save_CBlockCollection_base(HBlockCollection x, SaveContext *ctx);
  int  save_CBlockCollection(HBlockCollection x, SaveContext *ctx);
  int  save_CBlockList(HBlockList x, SaveContext *ctx);
  int  save_CBlockList_OR(HBlockList_OR x, SaveContext *ctx);
  int  save_CBlockList_AND(HBlockList_AND x, SaveContext *ctx);
  int  save_CBlockEnums(HBlockEnums x, SaveContext *ctx);
  int  save_CBlockVerbRelation_base(HBlockVerbRelation x, SaveContext *ctx);
  int  save_CBlockVerbRelation(HBlockVerbRelation x, SaveContext *ctx);
  int  save_CBlockVerbDirectRelation(HBlockVerbDirectRelation x, SaveContext *ctx);
  int  save_CBlockVerbReverseRelation(HBlockVerbReverseRelation x, SaveContext *ctx);
  int  save_CBlockFilterAtom(HBlockFilterAtom x, SaveContext *ctx);
  int  save_CBlockFilterList(HBlockFilterList x, SaveContext *ctx);
  int  save_CBlockDinamicDispatch(HBlockDinamicDispatch x, SaveContext *ctx);
  int  save_CBlockIF(HBlockIF x, SaveContext *ctx);
  int  save_CBlockSame(HBlockSame x, SaveContext *ctx);
  int  save_CBlockVerbConjugation(HBlockVerbConjugation x, SaveContext *ctx);
  int  save_CBlockVerb(HBlockVerb x, SaveContext *ctx);
  int  save_CBlockVerbAdapt(HBlockVerbAdapt x, SaveContext *ctx);
  int  save_CBlockVerbNegate(HBlockVerbNegate x, SaveContext *ctx);
  int  save_CBlockSelector_base(HBlockSelector x, SaveContext *ctx);
  int  save_CBlockSelector(HBlockSelector x, SaveContext *ctx);
  int  save_CBlockSelector_All(HBlockSelector_All x, SaveContext *ctx);
  int  save_CBlockSelector_Any(HBlockSelector_Any x, SaveContext *ctx);
  int  save_CBlockSelector_Where(HBlockSelector_Where x, SaveContext *ctx);
  int  save_CBlockAction_base(HBlockAction x, SaveContext *ctx);
  int  save_CBlockAction(HBlockAction x, SaveContext *ctx);
  int  save_CBlockActionInstance(HBlockActionInstance x, SaveContext *ctx);
  int  save_CBlockActionNamed(HBlockActionNamed x, SaveContext *ctx);
  int  save_CBlockActionNamed(HBlockActionNamed x, SaveContext *ctx);
  int  save_CBlockTryCall(HBlockTryCall x, SaveContext *ctx);
  int  save_CBlockActionCall_base(HBlockActionCall x, SaveContext *ctx);
  int  save_CBlockActionCall(HBlockActionCall x, SaveContext *ctx);
  int  save_CBlockActionCallNamed(HBlockActionCallNamed x, SaveContext *ctx);
  int  save_CBlockStaticDispatch(HBlockStaticDispatch x, SaveContext *ctx);
  int  save_CBlockAssertionBase_base(HBlockAssertionBase x, SaveContext *ctx);
  int  save_CBlockAssertionBase(HBlockAssertionBase x, SaveContext *ctx);
  int  save_CBlockAssertion_is_base(HBlockAssertion_is x, SaveContext *ctx);
  int  save_CBlockAssertion_is(HBlockAssertion_is x, SaveContext *ctx);
  int  save_CBlockAssertion_canBe(HBlockAssertion_canBe x, SaveContext *ctx);
  int  save_CBlockAssertion_isInstanceOf(HBlockAssertion_isInstanceOf x, SaveContext *ctx);
  int  save_CBlockAssertion_isNamedValueOf(HBlockAssertion_isNamedValueOf x, SaveContext *ctx);
  int  save_CBlockAssertion_isVariable(HBlockAssertion_isVariable x, SaveContext *ctx);
  int  save_CBlockAssertion_isLocalVariable(HBlockAssertion_isLocalVariable x, SaveContext *ctx);
  int  save_CBlockAssertion_isDefaultAssign(HBlockAssertion_isDefaultAssign x, SaveContext *ctx);
  int  save_CBlockAssertion_isConstantAssign(HBlockAssertion_isConstantAssign x, SaveContext *ctx);
  int  save_CBlockAssertion_isForbiddenAssign(HBlockAssertion_isForbiddenAssign x, SaveContext *ctx);
  int  save_CBlockAssertion_isDirectAssign(HBlockAssertion_isDirectAssign x, SaveContext *ctx);
  int  save_CBlockAssertion_isNotDirectAssign(HBlockAssertion_isNotDirectAssign x, SaveContext *ctx);
  int  save_CBlockIsVerb(HBlockIsVerb x, SaveContext *ctx);
  int  save_CBlockIsNotVerb(HBlockIsNotVerb x, SaveContext *ctx);
  int  save_CBlockIsAdverbialComparasion(HBlockIsAdverbialComparasion x, SaveContext *ctx);
  int  save_CBlockAssert(HBlockAssert x, SaveContext *ctx);
  int  save_CBlockAssertion_InstanceVariable(HBlockAssertion_InstanceVariable x, SaveContext *ctx);
  int  save_CBlockBooleanValue(HBlockBooleanValue x, SaveContext *ctx);
  int  save_CBlockBooleanAND(HBlockBooleanAND x, SaveContext *ctx);
  int  save_CBlockBooleanOR(HBlockBooleanOR x, SaveContext *ctx);
  int  save_CBlockBooleanNOT(HBlockBooleanNOT x, SaveContext *ctx);
  int  save_CBlockNow(HBlockNow x, SaveContext *ctx);
  int  save_CBlockEvery(HBlockEvery x, SaveContext *ctx);
  int  save_CBlockComandList(HBlockComandList x, SaveContext *ctx);
  int  save_CBlockEventHandle(HBlockEventHandle x, SaveContext *ctx);
  int  save_CBlockComposition_base(HBlockComposition x, SaveContext *ctx);
  int  save_CBlockComposition(HBlockComposition x, SaveContext *ctx);
  int  save_CBlockCompositionList(HBlockCompositionList x, SaveContext *ctx);
  int  save_CBlockCompositionRelation(HBlockCompositionRelation x, SaveContext *ctx);
  int  save_CBlockCompositionRulebook(HBlockCompositionRulebook x, SaveContext *ctx);
  int  save_CBlockCompositionPhrase(HBlockCompositionPhrase x, SaveContext *ctx);
  int  save_CBlockCompostionPhrase(HBlockCompostionPhrase x, SaveContext *ctx);
  int  save_CBlockControlToken(HBlockControlToken x, SaveContext *ctx);
  int  save_CBlockControlIF(HBlockControlIF x, SaveContext *ctx);
  int  save_CBlockControlUnless(HBlockControlUnless x, SaveContext *ctx);
  int  save_CBlockControlSelectItem(HBlockControlSelectItem x, SaveContext *ctx);
  int  save_CBlockControlSelect(HBlockControlSelect x, SaveContext *ctx);
  int  save_CBlockControlForEach(HBlockControlForEach x, SaveContext *ctx);
  int  save_CBlockExecutionResultFlag(HBlockExecutionResultFlag x, SaveContext *ctx);
  int  save_CBlockUnitInit(HBlockUnitInit x, SaveContext *ctx);
  int  save_CBlockUnitTest(HBlockUnitTest x, SaveContext *ctx);
  int  save_CBlockUnitAssert(HBlockUnitAssert x, SaveContext *ctx);
  int  save_CBlockToDecide_base(HBlockToDecide x, SaveContext *ctx);
  int  save_CBlockToDecide(HBlockToDecide x, SaveContext *ctx);
  int  save_CBlockToDecideIf(HBlockToDecideIf x, SaveContext *ctx);
  int  save_CBlockToDecideWhether(HBlockToDecideWhether x, SaveContext *ctx);
  int  save_CBlockToDecideWhat(HBlockToDecideWhat x, SaveContext *ctx);
  int  save_CBlockToDecideWhat_FirstNoum(HBlockToDecideWhat_FirstNoum x, SaveContext *ctx);
  int  save_CBlockToDecideOn(HBlockToDecideOn x, SaveContext *ctx);
  int  save_CBlockPhraseHeader(HBlockPhraseHeader x, SaveContext *ctx);
  int  save_CBlockPhraseDefine(HBlockPhraseDefine x, SaveContext *ctx);
  int  save_CBlockPhraseInvoke(HBlockPhraseInvoke x, SaveContext *ctx);
 
  int  save_CBlockMatch_base(HBlockMatch x, SaveContext *ctx);
  int  save_CBlockMatch(HBlockMatch x, SaveContext *ctx);
  int  save_CBlockMatchAny(HBlockMatchAny x, SaveContext *ctx);
  int  save_CBlockMatchNamed(HBlockMatchNamed x, SaveContext *ctx);
  int  save_CBlockMatchNoum(HBlockMatchNoum x, SaveContext *ctx);
  int  save_CBlockMatchText(HBlockMatchText x, SaveContext *ctx);
  int  save_CBlockMatchValue(HBlockMatchValue x, SaveContext *ctx);
  int  save_CBlockMatchKind(HBlockMatchKind x, SaveContext *ctx);
  int  save_CBlockMatchWith(HBlockMatchWith x, SaveContext *ctx);
  int  save_CBlockMatchList(HBlockMatchList x, SaveContext *ctx);
  int  save_CBlockMatchAND(HBlockMatchAND x, SaveContext *ctx);
  int  save_CBlockMatchNOT(HBlockMatchNOT x, SaveContext *ctx);
  int  save_CBlockMatchOR(HBlockMatchOR x, SaveContext *ctx);
  int  save_CBlockMatchActionCall(HBlockMatchActionCall x, SaveContext *ctx);
  int  save_CBlockMatchBlock(HBlockMatchBlock x, SaveContext *ctx);
  int  save_CBlockMatchIs_base(HBlockMatchIs x, SaveContext *ctx);
  int  save_CBlockMatchIs(HBlockMatchIs x, SaveContext *ctx);
  int  save_CBlockMatchDirectIs(HBlockMatchDirectIs x, SaveContext *ctx);
  int  save_CBlockMatchDirectIsNot(HBlockMatchDirectIsNot x, SaveContext *ctx);
  int  save_CBlockMatchIsVerb(HBlockMatchIsVerb x, SaveContext *ctx);
  int  save_CBlockMatchIsNotVerb(HBlockMatchIsNotVerb x, SaveContext *ctx);
  int  save_CBlockMatchIsAdverbialComparasion(HBlockMatchIsAdverbialComparasion x, SaveContext *ctx);
  int  save_CBlockMatchProperty(HBlockMatchProperty x, SaveContext *ctx);
  int  save_CBlockMatchWhich(HBlockMatchWhich x, SaveContext *ctx);
  int  save_CBlockMatchIsVerbComposition(HBlockMatchIsVerbComposition x, SaveContext *ctx);
  int  save_CBlockMatchWhichNot(HBlockMatchWhichNot x, SaveContext *ctx);
  int  save_CBlockVariableNamed(HBlockVariableNamed x, SaveContext *ctx);
  int  save_CBlockNumber_base(HBlockNumber x, SaveContext *ctx);
  int  save_CBlockNumber(HBlockNumber x, SaveContext *ctx);
  int  save_CBlockIntegerNumber(HBlockIntegerNumber x, SaveContext *ctx);
  int  save_CBlockFactionalNumber(HBlockFactionalNumber x, SaveContext *ctx);
  int  save_CBlockArgumentInput(HBlockArgumentInput x, SaveContext *ctx);
  int  save_CBlockRelationBase_base(HBlockRelationBase x, SaveContext *ctx);
  int  save_CBlockRelationBase(HBlockRelationBase x, SaveContext *ctx);
  int  save_CBlockSimetricRelation(HBlockSimetricRelation x, SaveContext *ctx);
  int  save_CBlockASimetricRelation(HBlockASimetricRelation x, SaveContext *ctx);
  int  save_CBlockRelationInstance(HBlockRelationInstance x, SaveContext *ctx);
  int  save_CBlockConditionalRelation(HBlockConditionalRelation x, SaveContext *ctx);
  int  save_CBlockRelationLookup(HBlockRelationLookup x, SaveContext *ctx);
  int  save_CBlockVerbLookup(HBlockVerbLookup x, SaveContext *ctx);
  int  save_CBlockRelationArguments(HBlockRelationArguments x, SaveContext *ctx);
  int  save_CBlockSelectorAND(HBlockSelectorAND x, SaveContext *ctx);
  int  save_CBlockExecution(HBlockExecution x, SaveContext *ctx);
  int  save_CBlockUnderstand(HBlockUnderstand x, SaveContext *ctx);
  int  save_CBlockUnderstandStatic(HBlockUnderstandStatic x, SaveContext *ctx);
  int  save_CBlockUnderstandDynamic(HBlockUnderstandDynamic x, SaveContext *ctx);
  int   save_CBlockNumber(HBlockNumber x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockIntegerNumber) return save_CBlockIntegerNumber(std::static_pointer_cast < CBlockIntegerNumber > (x), ctx);
	  if (t == BlockType::BlockFactionalNumber) return save_CBlockFactionalNumber(std::static_pointer_cast < CBlockFactionalNumber > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockMatchIs(HBlockMatchIs x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockMatchDirectIs) return save_CBlockMatchDirectIs(std::static_pointer_cast < CBlockMatchDirectIs > (x), ctx);
	  if (t == BlockType::BlockMatchDirectIsNot) return save_CBlockMatchDirectIsNot(std::static_pointer_cast < CBlockMatchDirectIsNot > (x), ctx);
	  if (t == BlockType::BlockMatchIsVerb) return save_CBlockMatchIsVerb(std::static_pointer_cast < CBlockMatchIsVerb > (x), ctx);
	  if (t == BlockType::BlockMatchIsNotVerb) return save_CBlockMatchIsNotVerb(std::static_pointer_cast < CBlockMatchIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockMatchIsAdverbialComparasion) return save_CBlockMatchIsAdverbialComparasion(std::static_pointer_cast < CBlockMatchIsAdverbialComparasion > (x), ctx);
	  if (t == BlockType::BlockMatchWhich) return save_CBlockMatchWhich(std::static_pointer_cast < CBlockMatchWhich > (x), ctx);
	  if (t == BlockType::BlockMatchWhichNot) return save_CBlockMatchWhichNot(std::static_pointer_cast < CBlockMatchWhichNot > (x), ctx);

	  if (t == BlockType::BlockMatchIsVerbComposition) return save_CBlockMatchIsVerbComposition(std::static_pointer_cast < CBlockMatchIsVerbComposition > (x), ctx);
	  raiseError();
	  return -1;
  }

  int   save_CBlockNoum(HBlockNoum x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockNoumStr) return save_CBlockNoumStr(std::static_pointer_cast < CBlockNoumStr > (x), ctx);
	  if (t == BlockType::BlockNoumStrDet) return save_CBlockNoumStrDet(std::static_pointer_cast < CBlockNoumStrDet > (x), ctx);
	  if (t == BlockType::BlockNoumSupl) return save_CBlockNoumSupl(std::static_pointer_cast < CBlockNoumSupl > (x), ctx);
	  if (t == BlockType::BlockNoumCompose) return save_CBlockNoumCompose(std::static_pointer_cast < CBlockNoumCompose > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockSelector(HBlockSelector x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockSelector_All) return save_CBlockSelector_All(std::static_pointer_cast < CBlockSelector_All > (x), ctx);
	  if (t == BlockType::BlockSelector_Any) return save_CBlockSelector_Any(std::static_pointer_cast < CBlockSelector_Any > (x), ctx);
	  if (t == BlockType::BlockSelector_Where) return save_CBlockSelector_Where(std::static_pointer_cast < CBlockSelector_Where > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockFilter(HBlockFilter x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();

	  raiseError();
	  return -1;
  }

  int   save_CBlockComposition(HBlockComposition x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockCompositionList) return save_CBlockCompositionList(std::static_pointer_cast < CBlockCompositionList > (x), ctx);
	  if (t == BlockType::BlockCompositionRelation) return save_CBlockCompositionRelation(std::static_pointer_cast < CBlockCompositionRelation > (x), ctx);
	  if (t == BlockType::BlockCompositionPhrase) return save_CBlockCompositionPhrase(std::static_pointer_cast < CBlockCompositionPhrase > (x), ctx);
	  if (t == BlockType::BlockCompositionRulebook) return save_CBlockCompositionRulebook(std::static_pointer_cast < CBlockCompositionRulebook > (x), ctx);
	  raiseError();
	  return -1;
  }

  int   save_CBlockRelationBase(HBlockRelationBase x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockSimetricRelation) return save_CBlockSimetricRelation(std::static_pointer_cast < CBlockSimetricRelation > (x), ctx);
	  if (t == BlockType::BlockASimetricRelation) return save_CBlockASimetricRelation(std::static_pointer_cast < CBlockASimetricRelation > (x), ctx);
	  if (t == BlockType::BlockConditionalRelation) return save_CBlockConditionalRelation(std::static_pointer_cast < CBlockConditionalRelation > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockToDecide(HBlockToDecide x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockToDecideIf) return save_CBlockToDecideIf(std::static_pointer_cast < CBlockToDecideIf > (x), ctx);
	  if (t == BlockType::BlockToDecideWhether) return save_CBlockToDecideWhether(std::static_pointer_cast < CBlockToDecideWhether > (x), ctx);
	  if (t == BlockType::BlockToDecideWhat) return save_CBlockToDecideWhat(std::static_pointer_cast < CBlockToDecideWhat > (x), ctx);
	  if (t == BlockType::BlockToDecideWhat_FirstNoum) return save_CBlockToDecideWhat_FirstNoum(std::static_pointer_cast < CBlockToDecideWhat_FirstNoum > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockInstance(HBlockInstance x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockInstanceAnonymous) return save_CBlockInstanceAnonymous(std::static_pointer_cast < CBlockInstanceAnonymous > (x), ctx);
	  if (t == BlockType::BlockInstanceNamed) return save_CBlockInstanceNamed(std::static_pointer_cast < CBlockInstanceNamed > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockVerbRelation(HBlockVerbRelation x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockVerbDirectRelation) return save_CBlockVerbDirectRelation(std::static_pointer_cast < CBlockVerbDirectRelation > (x), ctx);
	  if (t == BlockType::BlockVerbReverseRelation) return save_CBlockVerbReverseRelation(std::static_pointer_cast < CBlockVerbReverseRelation > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockAssertion_is(HBlockAssertion_is x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockAssertion_isInstanceOf) return save_CBlockAssertion_isInstanceOf(std::static_pointer_cast < CBlockAssertion_isInstanceOf > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNamedValueOf) return save_CBlockAssertion_isNamedValueOf(std::static_pointer_cast < CBlockAssertion_isNamedValueOf > (x), ctx);
	  if (t == BlockType::BlockAssertion_isVariable) return save_CBlockAssertion_isVariable(std::static_pointer_cast < CBlockAssertion_isVariable > (x), ctx);
	  if (t == BlockType::BlockAssertion_isLocalVariable) return save_CBlockAssertion_isLocalVariable(std::static_pointer_cast < CBlockAssertion_isLocalVariable > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDefaultAssign) return save_CBlockAssertion_isDefaultAssign(std::static_pointer_cast < CBlockAssertion_isDefaultAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isConstantAssign) return save_CBlockAssertion_isConstantAssign(std::static_pointer_cast < CBlockAssertion_isConstantAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isForbiddenAssign) return save_CBlockAssertion_isForbiddenAssign(std::static_pointer_cast < CBlockAssertion_isForbiddenAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDirectAssign) return save_CBlockAssertion_isDirectAssign(std::static_pointer_cast < CBlockAssertion_isDirectAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNotDirectAssign) return save_CBlockAssertion_isNotDirectAssign(std::static_pointer_cast < CBlockAssertion_isNotDirectAssign > (x), ctx);
	  if (t == BlockType::BlockIsVerb) return save_CBlockIsVerb(std::static_pointer_cast < CBlockIsVerb > (x), ctx);
	  if (t == BlockType::BlockIsNotVerb) return save_CBlockIsNotVerb(std::static_pointer_cast < CBlockIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockIsAdverbialComparasion) return save_CBlockIsAdverbialComparasion(std::static_pointer_cast < CBlockIsAdverbialComparasion > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockMatch(HBlockMatch x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockMatchActionCall) return save_CBlockMatchActionCall(std::static_pointer_cast < CBlockMatchActionCall > (x), ctx);
	  if (t == BlockType::BlockMatchIsAdverbialComparasion) return save_CBlockMatchIsAdverbialComparasion(std::static_pointer_cast < CBlockMatchIsAdverbialComparasion > (x), ctx);
	  if (t == BlockType::BlockMatchValue) return save_CBlockMatchValue(std::static_pointer_cast < CBlockMatchValue > (x), ctx);
	  if (t == BlockType::BlockMatchText) return save_CBlockMatchText(std::static_pointer_cast < CBlockMatchText > (x), ctx);
	  if (t == BlockType::BlockMatchNoum) return save_CBlockMatchNoum(std::static_pointer_cast < CBlockMatchNoum > (x), ctx);
	  if (t == BlockType::BlockMatchKind) return save_CBlockMatchKind(std::static_pointer_cast < CBlockMatchKind > (x), ctx);
	  if (t == BlockType::BlockMatchIsVerb) return save_CBlockMatchIsVerb(std::static_pointer_cast < CBlockMatchIsVerb > (x), ctx);
	  if (t == BlockType::BlockMatchDirectIsNot) return save_CBlockMatchDirectIsNot(std::static_pointer_cast < CBlockMatchDirectIsNot > (x), ctx);
	  if (t == BlockType::BlockMatchAny) return save_CBlockMatchAny(std::static_pointer_cast < CBlockMatchAny > (x), ctx);
	  if (t == BlockType::BlockMatchNamed) return save_CBlockMatchNamed(std::static_pointer_cast < CBlockMatchNamed > (x), ctx);
	  if (t == BlockType::BlockMatchAND) return save_CBlockMatchAND(std::static_pointer_cast < CBlockMatchAND > (x), ctx);
	  if (t == BlockType::BlockMatchBlock) return save_CBlockMatchBlock(std::static_pointer_cast < CBlockMatchBlock > (x), ctx);
	  if (t == BlockType::BlockMatchDirectIs) return save_CBlockMatchDirectIs(std::static_pointer_cast < CBlockMatchDirectIs > (x), ctx);
	  if (t == BlockType::BlockMatchProperty) return save_CBlockMatchProperty(std::static_pointer_cast < CBlockMatchProperty > (x), ctx);
	  if (t == BlockType::BlockMatchWhich) return save_CBlockMatchWhich(std::static_pointer_cast < CBlockMatchWhich > (x), ctx);
	  if (t == BlockType::BlockMatchIsNotVerb) return save_CBlockMatchIsNotVerb(std::static_pointer_cast < CBlockMatchIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockMatchOR) return save_CBlockMatchOR(std::static_pointer_cast < CBlockMatchOR > (x), ctx);
	  if (t == BlockType::BlockMatchNOT) return save_CBlockMatchNOT(std::static_pointer_cast < CBlockMatchNOT > (x), ctx);
	  if (t == BlockType::BlockMatchList) return save_CBlockMatchList(std::static_pointer_cast < CBlockMatchList > (x), ctx);
	  if (t == BlockType::BlockMatchWhichNot) return save_CBlockMatchWhichNot(std::static_pointer_cast < CBlockMatchWhichNot > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockActionCall(HBlockActionCall x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockActionCallNamed) return save_CBlockActionCallNamed(std::static_pointer_cast < CBlockActionCallNamed > (x), ctx);
	  if (t == BlockType::BlockStaticDispatch) return save_CBlockStaticDispatch(std::static_pointer_cast < CBlockStaticDispatch > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlock(HBlock x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockIsVerb) return save_CBlockIsVerb(std::static_pointer_cast < CBlockIsVerb > (x), ctx);
	  if (t == BlockType::BlockKindOfName) return save_CBlockKindOfName(std::static_pointer_cast < CBlockKindOfName > (x), ctx);
	  if (t == BlockType::BlockList) return save_CBlockList(std::static_pointer_cast < CBlockList > (x), ctx);
	  if (t == BlockType::BlockAssertion_isConstantAssign) return save_CBlockAssertion_isConstantAssign(std::static_pointer_cast < CBlockAssertion_isConstantAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNotDirectAssign) return save_CBlockAssertion_isNotDirectAssign(std::static_pointer_cast < CBlockAssertion_isNotDirectAssign > (x), ctx);
	  if (t == BlockType::BlockIsNotVerb) return save_CBlockIsNotVerb(std::static_pointer_cast < CBlockIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockMatchBlock) return save_CBlockMatchBlock(std::static_pointer_cast < CBlockMatchBlock > (x), ctx);
	  if (t == BlockType::BlockControlIF) return save_CBlockControlIF(std::static_pointer_cast < CBlockControlIF > (x), ctx);
	  if (t == BlockType::BlockInstanceVariable) return save_CBlockInstanceVariable(std::static_pointer_cast < CBlockInstanceVariable > (x), ctx);
	  if (t == BlockType::BlockKindValue) return save_CBlockKindValue(std::static_pointer_cast < CBlockKindValue > (x), ctx);
	  if (t == BlockType::BlockRelationArguments) return save_CBlockRelationArguments(std::static_pointer_cast < CBlockRelationArguments > (x), ctx);
	  if (t == BlockType::BlockAssert) return save_CBlockAssert(std::static_pointer_cast < CBlockAssert > (x), ctx);
	  if (t == BlockType::BlockMatchList) return save_CBlockMatchList(std::static_pointer_cast < CBlockMatchList > (x), ctx);
	  if (t == BlockType::BlockVerbReverseRelation) return save_CBlockVerbReverseRelation(std::static_pointer_cast < CBlockVerbReverseRelation > (x), ctx);
	  if (t == BlockType::BlockMatchWhichNot) return save_CBlockMatchWhichNot(std::static_pointer_cast < CBlockMatchWhichNot > (x), ctx);
	  if (t == BlockType::BlockKind_InstanceVariable) return save_CBlockKind_InstanceVariable(std::static_pointer_cast < CBlockKind_InstanceVariable > (x), ctx);
	  if (t == BlockType::BlockProperty) return save_CBlockProperty(std::static_pointer_cast < CBlockProperty > (x), ctx);
	  if (t == BlockType::BlockControlToken) return save_CBlockControlToken(std::static_pointer_cast < CBlockControlToken > (x), ctx);
	  if (t == BlockType::BlockNothing) return save_CBlockNothing(std::static_pointer_cast < CBlockNothing > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDefaultAssign) return save_CBlockAssertion_isDefaultAssign(std::static_pointer_cast < CBlockAssertion_isDefaultAssign > (x), ctx);
	  if (t == BlockType::BlockMatchProperty) return save_CBlockMatchProperty(std::static_pointer_cast < CBlockMatchProperty > (x), ctx);
	  if (t == BlockType::BlockAssertion_isForbiddenAssign) return save_CBlockAssertion_isForbiddenAssign(std::static_pointer_cast < CBlockAssertion_isForbiddenAssign > (x), ctx);
	  if (t == BlockType::BlockBooleanAND) return save_CBlockBooleanAND(std::static_pointer_cast < CBlockBooleanAND > (x), ctx);
	  if (t == BlockType::BlockUnderstandDynamic) return save_CBlockUnderstandDynamic(std::static_pointer_cast < CBlockUnderstandDynamic > (x), ctx);
	  if (t == BlockType::BlockPhraseInvoke) return save_CBlockPhraseInvoke(std::static_pointer_cast < CBlockPhraseInvoke > (x), ctx);
	  if (t == BlockType::BlockNow) return save_CBlockNow(std::static_pointer_cast < CBlockNow > (x), ctx);
	  if (t == BlockType::BlockControlSelect) return save_CBlockControlSelect(std::static_pointer_cast < CBlockControlSelect > (x), ctx);
	  if (t == BlockType::BlockVerbLookup) return save_CBlockVerbLookup(std::static_pointer_cast < CBlockVerbLookup > (x), ctx);
	  if (t == BlockType::BlockKindEntity) return save_CBlockKindEntity(std::static_pointer_cast < CBlockKindEntity > (x), ctx);
	  if (t == BlockType::BlockAssertion_isInstanceOf) return save_CBlockAssertion_isInstanceOf(std::static_pointer_cast < CBlockAssertion_isInstanceOf > (x), ctx);
	  if (t == BlockType::BlockBooleanValue) return save_CBlockBooleanValue(std::static_pointer_cast < CBlockBooleanValue > (x), ctx);
	  if (t == BlockType::BlockPhraseHeader) return save_CBlockPhraseHeader(std::static_pointer_cast < CBlockPhraseHeader > (x), ctx);
	  if (t == BlockType::BlockRelationLookup) return save_CBlockRelationLookup(std::static_pointer_cast < CBlockRelationLookup > (x), ctx);
	  if (t == BlockType::BlockMatchIsAdverbialComparasion) return save_CBlockMatchIsAdverbialComparasion(std::static_pointer_cast < CBlockMatchIsAdverbialComparasion > (x), ctx);
	  if (t == BlockType::BlockTryCall) return save_CBlockTryCall(std::static_pointer_cast < CBlockTryCall > (x), ctx);
	  if (t == BlockType::BlockKindReference) return save_CBlockKindReference(std::static_pointer_cast < CBlockKindReference > (x), ctx);
	  if (t == BlockType::BlockAnything) return save_CBlockAnything(std::static_pointer_cast < CBlockAnything > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNamedValueOf) return save_CBlockAssertion_isNamedValueOf(std::static_pointer_cast < CBlockAssertion_isNamedValueOf > (x), ctx);
	  if (t == BlockType::BlockActionInstance) return save_CBlockActionInstance(std::static_pointer_cast < CBlockActionInstance > (x), ctx);
	  if (t == BlockType::BlockCompostionPhrase) return save_CBlockCompostionPhrase(std::static_pointer_cast < CBlockCompostionPhrase > (x), ctx);
	  if (t == BlockType::BlockNamedValue) return save_CBlockNamedValue(std::static_pointer_cast < CBlockNamedValue > (x), ctx);
	  if (t == BlockType::BlockList_OR) return save_CBlockList_OR(std::static_pointer_cast < CBlockList_OR > (x), ctx);
	  if (t == BlockType::BlockMatchKind) return save_CBlockMatchKind(std::static_pointer_cast < CBlockMatchKind > (x), ctx);	  
	  if (t == BlockType::BlockStaticDispatch) return save_CBlockStaticDispatch(std::static_pointer_cast < CBlockStaticDispatch > (x), ctx);
	  if (t == BlockType::BlockMatchIsNotVerb) return save_CBlockMatchIsNotVerb(std::static_pointer_cast < CBlockMatchIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockMatchNOT) return save_CBlockMatchNOT(std::static_pointer_cast < CBlockMatchNOT > (x), ctx);
	  if (t == BlockType::BlockSelector_All) return save_CBlockSelector_All(std::static_pointer_cast < CBlockSelector_All > (x), ctx);
	  if (t == BlockType::BlockMatchDirectIs) return save_CBlockMatchDirectIs(std::static_pointer_cast < CBlockMatchDirectIs > (x), ctx);
	  if (t == BlockType::BlockInstanceNamed) return save_CBlockInstanceNamed(std::static_pointer_cast < CBlockInstanceNamed > (x), ctx);
	  if (t == BlockType::BlockKindNamed) return save_CBlockKindNamed(std::static_pointer_cast < CBlockKindNamed > (x), ctx);
	  if (t == BlockType::BlockToDecideWhat_FirstNoum) return save_CBlockToDecideWhat_FirstNoum(std::static_pointer_cast < CBlockToDecideWhat_FirstNoum > (x), ctx);
	  if (t == BlockType::BlockActionNamed) return save_CBlockActionNamed(std::static_pointer_cast < CBlockActionNamed > (x), ctx);
	  if (t == BlockType::BlockVerbAdapt) return save_CBlockVerbAdapt(std::static_pointer_cast < CBlockVerbAdapt > (x), ctx);
	  if (t == BlockType::BlockSelectorAND) return save_CBlockSelectorAND(std::static_pointer_cast < CBlockSelectorAND > (x), ctx);
	  if (t == BlockType::BlockVerbDirectRelation) return save_CBlockVerbDirectRelation(std::static_pointer_cast < CBlockVerbDirectRelation > (x), ctx);
	  if (t == BlockType::BlockEventHandle) return save_CBlockEventHandle(std::static_pointer_cast < CBlockEventHandle > (x), ctx);
	  if (t == BlockType::BlockControlUnless) return save_CBlockControlUnless(std::static_pointer_cast < CBlockControlUnless > (x), ctx);
	  if (t == BlockType::BlockCompositionPhrase) return save_CBlockCompositionPhrase(std::static_pointer_cast < CBlockCompositionPhrase > (x), ctx);
	  if (t == BlockType::BlockMatchIsVerb) return save_CBlockMatchIsVerb(std::static_pointer_cast < CBlockMatchIsVerb > (x), ctx);
	  if (t == BlockType::BlockMatchAND) return save_CBlockMatchAND(std::static_pointer_cast < CBlockMatchAND > (x), ctx);
	  if (t == BlockType::BlockCompositionRelation) return save_CBlockCompositionRelation(std::static_pointer_cast < CBlockCompositionRelation > (x), ctx);
	  if (t == BlockType::BlockUnitInit) return save_CBlockUnitInit(std::static_pointer_cast < CBlockUnitInit > (x), ctx);
	  if (t == BlockType::BlockUnderstandStatic) return save_CBlockUnderstandStatic(std::static_pointer_cast < CBlockUnderstandStatic > (x), ctx);
	  if (t == BlockType::BlockNoumSupl) return save_CBlockNoumSupl(std::static_pointer_cast < CBlockNoumSupl > (x), ctx);
	  if (t == BlockType::BlockVerb) return save_CBlockVerb(std::static_pointer_cast < CBlockVerb > (x), ctx);
	  if (t == BlockType::BlockUnitTest) return save_CBlockUnitTest(std::static_pointer_cast < CBlockUnitTest > (x), ctx);
	  if (t == BlockType::BlockToDecideIf) return save_CBlockToDecideIf(std::static_pointer_cast < CBlockToDecideIf > (x), ctx);
	  if (t == BlockType::BlockEvery) return save_CBlockEvery(std::static_pointer_cast < CBlockEvery > (x), ctx);
	  if (t == BlockType::BlockTextSentence) return save_CBlockTextSentence(std::static_pointer_cast < CBlockTextSentence > (x), ctx);
	  if (t == BlockType::BlockToDecideWhether) return save_CBlockToDecideWhether(std::static_pointer_cast < CBlockToDecideWhether > (x), ctx);
	  if (t == BlockType::BlockMatchAny) return save_CBlockMatchAny(std::static_pointer_cast < CBlockMatchAny > (x), ctx);
	  if (t == BlockType::BlockAssertion_InstanceVariable) return save_CBlockAssertion_InstanceVariable(std::static_pointer_cast < CBlockAssertion_InstanceVariable > (x), ctx);
	  if (t == BlockType::BlockASimetricRelation) return save_CBlockASimetricRelation(std::static_pointer_cast < CBlockASimetricRelation > (x), ctx);
	  if (t == BlockType::BlockPhraseDefine) return save_CBlockPhraseDefine(std::static_pointer_cast < CBlockPhraseDefine > (x), ctx);
	  if (t == BlockType::BlockMatchText) return save_CBlockMatchText(std::static_pointer_cast < CBlockMatchText > (x), ctx);
	  if (t == BlockType::BlockMatchValue) return save_CBlockMatchValue(std::static_pointer_cast < CBlockMatchValue > (x), ctx);
	  if (t == BlockType::BlockAssertion_canBe) return save_CBlockAssertion_canBe(std::static_pointer_cast < CBlockAssertion_canBe > (x), ctx);
	  if (t == BlockType::BlockAssertion_isLocalVariable) return save_CBlockAssertion_isLocalVariable(std::static_pointer_cast < CBlockAssertion_isLocalVariable > (x), ctx);
	  if (t == BlockType::BlockRelationInstance) return save_CBlockRelationInstance(std::static_pointer_cast < CBlockRelationInstance > (x), ctx);
	  if (t == BlockType::BlockToDecideOn) return save_CBlockToDecideOn(std::static_pointer_cast < CBlockToDecideOn > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDirectAssign) return save_CBlockAssertion_isDirectAssign(std::static_pointer_cast < CBlockAssertion_isDirectAssign > (x), ctx);
	  if (t == BlockType::BlockBooleanOR) return save_CBlockBooleanOR(std::static_pointer_cast < CBlockBooleanOR > (x), ctx);
	  if (t == BlockType::BlockActionCallNamed) return save_CBlockActionCallNamed(std::static_pointer_cast < CBlockActionCallNamed > (x), ctx);
	  if (t == BlockType::BlockSelector_Any) return save_CBlockSelector_Any(std::static_pointer_cast < CBlockSelector_Any > (x), ctx);
	  if (t == BlockType::BlockCompositionList) return save_CBlockCompositionList(std::static_pointer_cast < CBlockCompositionList > (x), ctx);
	  if (t == BlockType::BlockDinamicDispatch) return save_CBlockDinamicDispatch(std::static_pointer_cast < CBlockDinamicDispatch > (x), ctx);
	  if (t == BlockType::BlockVariableNamed) return save_CBlockVariableNamed(std::static_pointer_cast < CBlockVariableNamed > (x), ctx);
	  if (t == BlockType::BlockMatchActionCall) return save_CBlockMatchActionCall(std::static_pointer_cast < CBlockMatchActionCall > (x), ctx);
	  if (t == BlockType::BlockEnums) return save_CBlockEnums(std::static_pointer_cast < CBlockEnums > (x), ctx);
	  if (t == BlockType::BlockToDecideWhat) return save_CBlockToDecideWhat(std::static_pointer_cast < CBlockToDecideWhat > (x), ctx);
	  if (t == BlockType::BlockMatchNamed) return save_CBlockMatchNamed(std::static_pointer_cast < CBlockMatchNamed > (x), ctx);
	  if (t == BlockType::BlockControlSelectItem) return save_CBlockControlSelectItem(std::static_pointer_cast < CBlockControlSelectItem > (x), ctx);
	  if (t == BlockType::BlockMatchOR) return save_CBlockMatchOR(std::static_pointer_cast < CBlockMatchOR > (x), ctx);
	  if (t == BlockType::BlockIntegerNumber) return save_CBlockIntegerNumber(std::static_pointer_cast < CBlockIntegerNumber > (x), ctx);
	  if (t == BlockType::BlockMatchNoum) return save_CBlockMatchNoum(std::static_pointer_cast < CBlockMatchNoum > (x), ctx);
	  if (t == BlockType::BlockSimetricRelation) return save_CBlockSimetricRelation(std::static_pointer_cast < CBlockSimetricRelation > (x), ctx);
	  if (t == BlockType::BlockControlForEach) return save_CBlockControlForEach(std::static_pointer_cast < CBlockControlForEach > (x), ctx);
	  if (t == BlockType::BlockExecutionResultFlag) return save_CBlockExecutionResultFlag(std::static_pointer_cast < CBlockExecutionResultFlag > (x), ctx);
	  if (t == BlockType::BlockVerbConjugation) return save_CBlockVerbConjugation(std::static_pointer_cast < CBlockVerbConjugation > (x), ctx);
	  if (t == BlockType::BlockFactionalNumber) return save_CBlockFactionalNumber(std::static_pointer_cast < CBlockFactionalNumber > (x), ctx);
	  if (t == BlockType::BlockSelector_Where) return save_CBlockSelector_Where(std::static_pointer_cast < CBlockSelector_Where > (x), ctx);
	  if (t == BlockType::BlockKindOf) return save_CBlockKindOf(std::static_pointer_cast < CBlockKindOf > (x), ctx);
	  if (t == BlockType::BlockIsAdverbialComparasion) return save_CBlockIsAdverbialComparasion(std::static_pointer_cast < CBlockIsAdverbialComparasion > (x), ctx);
	  if (t == BlockType::BlockText) return save_CBlockText(std::static_pointer_cast < CBlockText > (x), ctx);
	  if (t == BlockType::BlockActionApply) return save_CBlockActionApply(std::static_pointer_cast < CBlockActionApply > (x), ctx);
	  if (t == BlockType::BlockMatchDirectIsNot) return save_CBlockMatchDirectIsNot(std::static_pointer_cast < CBlockMatchDirectIsNot > (x), ctx);
	  if (t == BlockType::BlockAssertion_isVariable) return save_CBlockAssertion_isVariable(std::static_pointer_cast < CBlockAssertion_isVariable > (x), ctx);
	  if (t == BlockType::BlockConditionalRelation) return save_CBlockConditionalRelation(std::static_pointer_cast < CBlockConditionalRelation > (x), ctx);
	  if (t == BlockType::BlockVerbNegate) return save_CBlockVerbNegate(std::static_pointer_cast < CBlockVerbNegate > (x), ctx);
	  if (t == BlockType::BlockComandList) return save_CBlockComandList(std::static_pointer_cast < CBlockComandList > (x), ctx);
	  if (t == BlockType::BlockArgumentInput) return save_CBlockArgumentInput(std::static_pointer_cast < CBlockArgumentInput > (x), ctx);
	  if (t == BlockType::BlockBooleanNOT) return save_CBlockBooleanNOT(std::static_pointer_cast < CBlockBooleanNOT > (x), ctx);
	  if (t == BlockType::BlockUnitAssert) return save_CBlockUnitAssert(std::static_pointer_cast < CBlockUnitAssert > (x), ctx);
	  if (t == BlockType::BlockInstanceAnonymous) return save_CBlockInstanceAnonymous(std::static_pointer_cast < CBlockInstanceAnonymous > (x), ctx);
	  if (t == BlockType::BlockList_AND) return save_CBlockList_AND(std::static_pointer_cast < CBlockList_AND > (x), ctx);
	  if (t == BlockType::BlockNoumStr) return save_CBlockNoumStr(std::static_pointer_cast < CBlockNoumStr > (x), ctx);
	  if (t == BlockType::BlockNoumStrDet) return save_CBlockNoumStrDet(std::static_pointer_cast < CBlockNoumStrDet > (x), ctx);
	  if (t == BlockType::BlockNoumCompose) return save_CBlockNoumCompose(std::static_pointer_cast < CBlockNoumCompose > (x), ctx);
	  if (t == BlockType::BlockMatchWhich) return save_CBlockMatchWhich(std::static_pointer_cast < CBlockMatchWhich > (x), ctx);
	  if (t == BlockType::BlockKindAction) return save_CBlockKindAction(std::static_pointer_cast < CBlockKindAction > (x), ctx);
	  if (t == BlockType::BlockCompositionRulebook) return save_CBlockCompositionRulebook(std::static_pointer_cast < CBlockCompositionRulebook > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockBooleanResult(HBlockBooleanResult x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();

	  raiseError();
	  return -1;
  }

  int   save_CBlockCollection(HBlockCollection x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockList) return save_CBlockList(std::static_pointer_cast < CBlockList > (x), ctx);
	  if (t == BlockType::BlockList_OR) return save_CBlockList_OR(std::static_pointer_cast < CBlockList_OR > (x), ctx);
	  if (t == BlockType::BlockList_AND) return save_CBlockList_AND(std::static_pointer_cast < CBlockList_AND > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockValue(HBlockValue x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockIntegerNumber) return save_CBlockIntegerNumber(std::static_pointer_cast < CBlockIntegerNumber > (x), ctx);
	  if (t == BlockType::BlockKindReference) return save_CBlockKindReference(std::static_pointer_cast < CBlockKindReference > (x), ctx);
	  if (t == BlockType::BlockFactionalNumber) return save_CBlockFactionalNumber(std::static_pointer_cast < CBlockFactionalNumber > (x), ctx);
	  if (t == BlockType::BlockBooleanValue) return save_CBlockBooleanValue(std::static_pointer_cast < CBlockBooleanValue > (x), ctx);
	  if (t == BlockType::BlockNamedValue) return save_CBlockNamedValue(std::static_pointer_cast < CBlockNamedValue > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockAction(HBlockAction x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockActionInstance) return save_CBlockActionInstance(std::static_pointer_cast < CBlockActionInstance > (x), ctx);
	  if (t == BlockType::BlockActionNamed) return save_CBlockActionNamed(std::static_pointer_cast < CBlockActionNamed > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockKind(HBlockKind x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockCompositionPhrase) return save_CBlockCompositionPhrase(std::static_pointer_cast < CBlockCompositionPhrase > (x), ctx);
	  if (t == BlockType::BlockCompositionRulebook) return save_CBlockCompositionRulebook(std::static_pointer_cast < CBlockCompositionRulebook > (x), ctx);
	  if (t == BlockType::BlockKindEntity) return save_CBlockKindEntity(std::static_pointer_cast < CBlockKindEntity > (x), ctx);
	  if (t == BlockType::BlockKindNamed) return save_CBlockKindNamed(std::static_pointer_cast < CBlockKindNamed > (x), ctx);
	  if (t == BlockType::BlockKindValue) return save_CBlockKindValue(std::static_pointer_cast < CBlockKindValue > (x), ctx);
	  if (t == BlockType::BlockCompositionRelation) return save_CBlockCompositionRelation(std::static_pointer_cast < CBlockCompositionRelation > (x), ctx);
	  if (t == BlockType::BlockCompositionList) return save_CBlockCompositionList(std::static_pointer_cast < CBlockCompositionList > (x), ctx);
	  if (t == BlockType::BlockKindAction) return save_CBlockKindAction(std::static_pointer_cast < CBlockKindAction > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockAssertionBase(HBlockAssertionBase x, SaveContext * ctx)
  {
	  if (x == nullptr) return 0;
	  int cc = cached(x.get(), ctx); if (cc != -1) return  cc;
	  const BlockType t = x->type();
	  if (t == BlockType::BlockIsVerb) return save_CBlockIsVerb(std::static_pointer_cast < CBlockIsVerb > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNotDirectAssign) return save_CBlockAssertion_isNotDirectAssign(std::static_pointer_cast < CBlockAssertion_isNotDirectAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_canBe) return save_CBlockAssertion_canBe(std::static_pointer_cast < CBlockAssertion_canBe > (x), ctx);
	  if (t == BlockType::BlockAssertion_isLocalVariable) return save_CBlockAssertion_isLocalVariable(std::static_pointer_cast < CBlockAssertion_isLocalVariable > (x), ctx);
	  if (t == BlockType::BlockIsNotVerb) return save_CBlockIsNotVerb(std::static_pointer_cast < CBlockIsNotVerb > (x), ctx);
	  if (t == BlockType::BlockAssertion_isNamedValueOf) return save_CBlockAssertion_isNamedValueOf(std::static_pointer_cast < CBlockAssertion_isNamedValueOf > (x), ctx);
	  if (t == BlockType::BlockAssertion_isVariable) return save_CBlockAssertion_isVariable(std::static_pointer_cast < CBlockAssertion_isVariable > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDefaultAssign) return save_CBlockAssertion_isDefaultAssign(std::static_pointer_cast < CBlockAssertion_isDefaultAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isDirectAssign) return save_CBlockAssertion_isDirectAssign(std::static_pointer_cast < CBlockAssertion_isDirectAssign > (x), ctx);
	  if (t == BlockType::BlockAssertion_isInstanceOf) return save_CBlockAssertion_isInstanceOf(std::static_pointer_cast < CBlockAssertion_isInstanceOf > (x), ctx);
	  if (t == BlockType::BlockAssertion_isConstantAssign) return save_CBlockAssertion_isConstantAssign(std::static_pointer_cast < CBlockAssertion_isConstantAssign > (x), ctx);
	  if (t == BlockType::BlockIsAdverbialComparasion) return save_CBlockIsAdverbialComparasion(std::static_pointer_cast < CBlockIsAdverbialComparasion > (x), ctx);
	  if (t == BlockType::BlockAssertion_isForbiddenAssign) return save_CBlockAssertion_isForbiddenAssign(std::static_pointer_cast < CBlockAssertion_isForbiddenAssign > (x), ctx);

	  raiseError();
	  return -1;
  }

  int   save_CBlockNumber(HBlockNumber x, SaveContext * ctx);
  int   save_CBlockMatchIs(HBlockMatchIs x, SaveContext * ctx);
  int   save_CBlockNoum(HBlockNoum x, SaveContext * ctx);
  int   save_CBlockSelector(HBlockSelector x, SaveContext * ctx);
  int   save_CBlockFilter(HBlockFilter x, SaveContext * ctx);
  int   save_CBlockComposition(HBlockComposition x, SaveContext * ctx);
  int   save_CBlockRelationBase(HBlockRelationBase x, SaveContext * ctx);
  int   save_CBlockToDecide(HBlockToDecide x, SaveContext * ctx);
  int   save_CBlockInstance(HBlockInstance x, SaveContext * ctx);
  int   save_CBlockVerbRelation(HBlockVerbRelation x, SaveContext * ctx);
  int   save_CBlockAssertion_is(HBlockAssertion_is x, SaveContext * ctx);
  int   save_CBlockMatch(HBlockMatch x, SaveContext * ctx);
  int   save_CBlockActionCall(HBlockActionCall x, SaveContext * ctx);
  int   save_CBlock(HBlock x, SaveContext * ctx);
  int   save_CBlockBooleanResult(HBlockBooleanResult x, SaveContext * ctx);
  int   save_CBlockCollection(HBlockCollection x, SaveContext * ctx);
  int   save_CBlockValue(HBlockValue x, SaveContext * ctx);
  int   save_CBlockAction(HBlockAction x, SaveContext * ctx);
  int   save_CBlockKind(HBlockKind x, SaveContext * ctx);
  int   save_CBlockAssertionBase(HBlockAssertionBase x, SaveContext * ctx);
  int  save_CBlockIsVerb(HBlockIsVerb x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _n1 = save_CBlock(x->n1, ctx);
	  const int _n2 = save_CBlock(x->n2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_n1, ctx);
	  save_id(_n2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockCompositionPhrase(HBlockCompositionPhrase x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _fromKind = save_CBlockKind(x->fromKind, ctx);
	  const int _toKind = save_CBlockKind(x->toKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_fromKind, ctx);
	  save_id(_toKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchIsVerb(HBlockMatchIsVerb x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockKindOfName(HBlockKindOfName x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _baseClasseName = save_CBlockNoum(x->baseClasseName, ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_baseClasseName, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockList(HBlockList x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _lista = save_list<CBlock>(x->lista, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_lista, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockSimetricRelation(HBlockSimetricRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _input_A = save_CBlockArgumentInput(x->input_A, ctx);
	  const int _input_B = save_CBlockArgumentInput(x->input_B, ctx);


	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_id(_input_A, ctx);
	  save_id(_input_B, ctx);
	  save_bool(x->various_noum1, ctx);
	  save_bool(x->various_noum2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }

 

	  int  save_CBlockCompositionRulebook(HBlockCompositionRulebook x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _fromKind = save_CBlockKind(x->fromKind, ctx);
	  const int _toKind = save_CBlockKind(x->toKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_fromKind, ctx);
	  save_id(_toKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }

  int  save_CBlockCompositionRelation(HBlockCompositionRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _fromKind = save_CBlockKind(x->fromKind, ctx);
	  const int _toKind = save_CBlockKind(x->toKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_fromKind, ctx);
	  save_id(_toKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockNoumSupl(HBlockNoumSupl x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->noum, ctx);
	  save_string(x->number, ctx);
	  save_string(x->gender, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockControlUnless(HBlockControlUnless x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _block_if = save_CBlock(x->block_if, ctx);
	  const int _block_then = save_CBlock(x->block_then, ctx);
	  const int _block_else = save_CBlock(x->block_else, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_block_if, ctx);
	  save_id(_block_then, ctx);
	  save_id(_block_else, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockSelector_Where(HBlockSelector_Where x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _what = save_CBlock(x->what, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_what, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockToDecideIf(HBlockToDecideIf x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _queryToMatch = save_CBlockMatchIs(x->queryToMatch, ctx);
	  const int _decideBody = save_CBlock(x->decideBody, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_queryToMatch, ctx);
	  save_id(_decideBody, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockEvery(HBlockEvery x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _assertation = save_CBlock(x->assertation, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_assertation, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockSelectorAND(HBlockSelectorAND x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _value1 = save_CBlock(x->value1, ctx);
	  const int _value2 = save_CBlock(x->value2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_value1, ctx);
	  save_id(_value2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }




  int  save_CBlockAssertion_isNotDirectAssign(HBlockAssertion_isNotDirectAssign x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockIsNotVerb(HBlockIsNotVerb x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _n1 = save_CBlock(x->n1, ctx);
	  const int _n2 = save_CBlock(x->n2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_n1, ctx);
	  save_id(_n2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockNamedValue(HBlockNamedValue x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockTextSentence(HBlockTextSentence x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _contents = save_list<CBlock>(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockToDecideWhether(HBlockToDecideWhether x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _queryToMatch = save_CBlockMatch(x->queryToMatch, ctx);
	  const int _decideBody = save_CBlock(x->decideBody, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_queryToMatch, ctx);
	  save_id(_decideBody, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockControlIF(HBlockControlIF x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _block_if = save_CBlock(x->block_if, ctx);
	  const int _block_then = save_CBlock(x->block_then, ctx);
	  const int _block_else = save_CBlock(x->block_else, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_block_if, ctx);
	  save_id(_block_then, ctx);
	  save_id(_block_else, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockToDecideOn(HBlockToDecideOn x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _decideBody = save_CBlock(x->decideBody, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_decideBody, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockToDecideWhat(HBlockToDecideWhat x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _queryToMatch = save_CBlockMatch(x->queryToMatch, ctx);
	  const int _decideBody = save_CBlock(x->decideBody, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_queryToMatch, ctx);
	  save_id(_decideBody, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_InstanceVariable(HBlockAssertion_InstanceVariable x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _noum = save_CBlock(x->noum, ctx);
	  const int _instance_variable = save_CBlockInstanceVariable(x->instance_variable, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_noum, ctx);
	  save_id(_instance_variable, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockASimetricRelation(HBlockASimetricRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _input_A = save_CBlockArgumentInput(x->input_A, ctx);
	  const int _input_B = save_CBlockArgumentInput(x->input_B, ctx);


	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_id(_input_A, ctx);
	  save_id(_input_B, ctx);
	  save_bool(x->various_noum1, ctx);
	  save_bool(x->various_noum2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchBlock(HBlockMatchBlock x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _inner = save_CBlock(x->inner, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_inner, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockInstanceVariable(HBlockInstanceVariable x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _kind_name = save_CBlockNoum(x->kind_name, ctx);
	  const int _property_name = save_CBlockNoum(x->property_name, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_kind_name, ctx);
	  save_id(_property_name, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockPhraseDefine(HBlockPhraseDefine x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _header = save_CBlockPhraseHeader(x->header, ctx);
	  const int _body = save_CBlock(x->body, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_header, ctx);
	  save_id(_body, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }

 
  int  save_CBlockMatchText(HBlockMatchText x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _inner = save_CBlockText(x->inner, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_inner, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchValue(HBlockMatchValue x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _inner = save_CBlock(x->inner, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_inner, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isLocalVariable(HBlockAssertion_isLocalVariable x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variableName = save_CBlockNoum(x->variableName, ctx);
	  const int _valueExpression = save_CBlock(x->valueExpression, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variableName, ctx);
	  save_id(_valueExpression, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockSelector_Any(HBlockSelector_Any x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _what = save_CBlock(x->what, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_what, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockKindValue(HBlockKindValue x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockRelationArguments(HBlockRelationArguments x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _value1 = save_CBlock(x->value1, ctx);
	  const int _value2 = save_CBlock(x->value2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_value1, ctx);
	  save_id(_value2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isDirectAssign(HBlockAssertion_isDirectAssign x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockBooleanOR(HBlockBooleanOR x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _input_A = save_CBlock(x->input_A, ctx);
	  const int _input_B = save_CBlock(x->input_B, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_input_A, ctx);
	  save_id(_input_B, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockActionCallNamed(HBlockActionCallNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _action = save_CBlockActionNamed(x->action, ctx);
	  const int _noum1 = save_CBlock(x->noum1, ctx);
	  const int _noum2 = save_CBlock(x->noum2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_action, ctx);
	  save_id(_noum1, ctx);
	  save_id(_noum2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockCompositionList(HBlockCompositionList x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _itemKind = save_CBlockKind(x->itemKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_itemKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssert(HBlockAssert x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _expression = save_CBlock(x->expression, ctx);
	  const int _result = save_CBlock(x->result, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_expression, ctx);
	  save_id(_result, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchAND(HBlockMatchAND x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _matchList = save_list<CBlockMatch>(x->matchList, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_matchList, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockDinamicDispatch(HBlockDinamicDispatch x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _commandList = save_CBlockList(x->commandList, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_commandList, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchList(HBlockMatchList x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _matchList = save_list<CBlockMatch>(x->matchList, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_matchList, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerbReverseRelation(HBlockVerbReverseRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _verbNoum = save_CBlock(x->verbNoum, ctx);
	  const int _relationNoum = save_CBlockNoum(x->relationNoum, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_verbNoum, ctx);
	  save_id(_relationNoum, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchActionCall(HBlockMatchActionCall x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _action = save_CBlockMatch(x->action, ctx);
	  const int _argument1 = save_CBlockMatch(x->argument1, ctx);
	  const int _argument2 = save_CBlockMatch(x->argument2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_action, ctx);
	  save_id(_argument1, ctx);
	  save_id(_argument2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockKind_InstanceVariable(HBlockKind_InstanceVariable x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _kind = save_CBlockKind(x->kind, ctx);
	  const int _variableNamed = save_CBlockInstanceVariable(x->variableNamed, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_kind, ctx);
	  save_id(_variableNamed, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockEnums(HBlockEnums x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _values = save_vector<CBlockNoum>(x->values, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_values, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockProperty(HBlockProperty x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _prop = save_CBlock(x->prop, ctx);
	  const int _obj = save_CBlock(x->obj, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_prop, ctx);
	  save_id(_obj, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockControlToken(HBlockControlToken x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _contents = save_CBlock(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->token, ctx);
	  save_id(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockMatchNamed(HBlockMatchNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _matchInner = save_CBlockMatch(x->matchInner, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_id(_matchInner, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isDefaultAssign(HBlockAssertion_isDefaultAssign x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockControlSelectItem(HBlockControlSelectItem x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _block_seletor = save_CBlock(x->block_seletor, ctx);
	  const int _block_execute = save_CBlock(x->block_execute, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_block_seletor, ctx);
	  save_id(_block_execute, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchProperty(HBlockMatchProperty x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _prop = save_CBlock(x->prop, ctx);
	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_prop, ctx);
	  save_id(_obj, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockBooleanNOT(HBlockBooleanNOT x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _input_A = save_CBlock(x->input_A, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_input_A, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isForbiddenAssign(HBlockAssertion_isForbiddenAssign x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchOR(HBlockMatchOR x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _matchList = save_list<CBlockMatch>(x->matchList, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_matchList, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockText(HBlockText x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockBooleanAND(HBlockBooleanAND x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _input_A = save_CBlock(x->input_A, ctx);
	  const int _input_B = save_CBlock(x->input_B, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_input_A, ctx);
	  save_id(_input_B, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockUnderstandDynamic(HBlockUnderstandDynamic x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _input_n = save_CBlockMatch(x->input_n, ctx);
	  const int _argument_n = save_CBlockMatchList(x->argument_n, ctx);
	  const int _output_n = save_CBlock(x->output_n, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_input_n, ctx);
	  save_id(_argument_n, ctx);
	  save_id(_output_n, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isConstantAssign(HBlockAssertion_isConstantAssign x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockPhraseInvoke(HBlockPhraseInvoke x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _header = save_CBlockPhraseHeader(x->header, ctx);
	  const int _arg1 = save_CBlock(x->arg1, ctx);
	  const int _arg2 = save_CBlock(x->arg2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_header, ctx);
	  save_id(_arg1, ctx);
	  save_id(_arg2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockMatchNoum(HBlockMatchNoum x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _inner = save_CBlockNoum(x->inner, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_inner, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockNow(HBlockNow x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _assertation = save_CBlockAssertion_is(x->assertation, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_assertation, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockControlForEach(HBlockControlForEach x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _block_variable = save_CBlock(x->block_variable, ctx);
	  const int _block_body = save_CBlock(x->block_body, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_block_variable, ctx);
	  save_id(_block_body, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockControlSelect(HBlockControlSelect x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _block_seletor = save_CBlock(x->block_seletor, ctx);
	  const std::list<int> _block_selectList = save_list<CBlockControlSelectItem>(x->block_selectList, ctx);
	  const int _block_else = save_CBlock(x->block_else, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_block_seletor, ctx);
	  save_id_list(_block_selectList, ctx);
	  save_id(_block_else, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockKindEntity(HBlockKindEntity x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockRelationInstance(HBlockRelationInstance x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _relation = save_CBlockRelationBase(x->relation, ctx);
	  const int _value1 = save_CBlock(x->value1, ctx);
	  const int _value2 = save_CBlock(x->value2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_relation, ctx);
	  save_id(_value1, ctx);
	  save_id(_value2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockNothing(HBlockNothing x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isInstanceOf(HBlockAssertion_isInstanceOf x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _noum = save_CBlockInstance(x->noum, ctx);
	  const int _baseKind = save_CBlockKind(x->baseKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_noum, ctx);
	  save_id(_baseKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_canBe(HBlockAssertion_canBe x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _obj = save_CBlock(x->obj, ctx);
	  const int _definition = save_CBlockEnums(x->definition, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_obj, ctx);
	  save_id(_definition, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockBooleanValue(HBlockBooleanValue x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_bool(x->state, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockExecutionResultFlag(HBlockExecutionResultFlag x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _contents = save_CBlock(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_PhaseResultFlag(x->flag, ctx);
	  save_id(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchIsAdverbialComparasion(HBlockMatchIsAdverbialComparasion x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->adverb, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockTryCall(HBlockTryCall x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _sentence = save_CBlock(x->sentence, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_sentence, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockKindReference(HBlockKindReference x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _kind = save_CBlockKind(x->kind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_kind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchAny(HBlockMatchAny x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAnything(HBlockAnything x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockVerbConjugation(HBlockVerbConjugation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);


	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->word, ctx);
	  save_string(x->tense, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockUnitInit(HBlockUnitInit x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _contents = save_CBlock(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockFactionalNumber(HBlockFactionalNumber x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_float(x->value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockActionInstance(HBlockActionInstance x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _base_kind = save_CBlockKindAction(x->base_kind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_int(x->id, ctx);
	  save_id(_base_kind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchDirectIs(HBlockMatchDirectIs x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockKindOf(HBlockKindOf x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _baseClasse = save_CBlockKind(x->baseClasse, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_baseClasse, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockIsAdverbialComparasion(HBlockIsAdverbialComparasion x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _n1 = save_CBlock(x->n1, ctx);
	  const int _n2 = save_CBlock(x->n2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->adverb, ctx);
	  save_id(_n1, ctx);
	  save_id(_n2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockCompostionPhrase(HBlockCompostionPhrase x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerbLookup(HBlockVerbLookup x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _value1 = save_CBlockMatch(x->value1, ctx);
	  const int _value2 = save_CBlockMatch(x->value2, ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_value1, ctx);
	  save_id(_value2, ctx);
	  save_NoumLocation(x->term_to_query, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchDirectIsNot(HBlockMatchDirectIsNot x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockMatchKind(HBlockMatchKind x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _kind = save_CBlockKind(x->kind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_kind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockPhraseHeader(HBlockPhraseHeader x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _verb = save_CBlockNoum(x->verb, ctx);
	  const int _pred1 = save_CBlockNoum(x->pred1, ctx);
	  const int _pred2 = save_CBlockNoum(x->pred2, ctx);
	  const int _arg1 = save_CBlockMatch(x->arg1, ctx);
	  const int _arg2 = save_CBlockMatch(x->arg2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_verb, ctx);
	  save_id(_pred1, ctx);
	  save_id(_pred2, ctx);
	  save_id(_arg1, ctx);
	  save_id(_arg2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockActionApply(HBlockActionApply x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _noum1 = save_CBlock(x->noum1, ctx);
	  const int _noum2 = save_CBlock(x->noum2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_noum1, ctx);
	  save_id(_noum2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockList_OR(HBlockList_OR x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _lista = save_list<CBlock>(x->lista, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_lista, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockRelationLookup(HBlockRelationLookup x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _value1 = save_CBlockMatch(x->value1, ctx);
	  const int _value2 = save_CBlockMatch(x->value2, ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->relation, ctx);
	  save_id(_value1, ctx);
	  save_id(_value2, ctx);
	  save_NoumLocation(x->term_to_query, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockComposition_base(HBlockComposition x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockStaticDispatch(HBlockStaticDispatch x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _noum1 = save_CBlock(x->noum1, ctx);
	  const int _noum2 = save_CBlock(x->noum2, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_int(x->staticEntryTable, ctx);
	  save_id(_noum1, ctx);
	  save_id(_noum2, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isVariable(HBlockAssertion_isVariable x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _variable = save_CBlock(x->variable, ctx);
	  const int _baseKind = save_CBlock(x->baseKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_variable, ctx);
	  save_id(_baseKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockIntegerNumber(HBlockIntegerNumber x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_int(x->value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockConditionalRelation(HBlockConditionalRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _relation = save_CBlockRelationBase(x->relation, ctx);
	  const int _coditional = save_CBlock(x->coditional, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_relation, ctx);
	  save_id(_coditional, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerbNegate(HBlockVerbNegate x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _verbAdapt = save_CBlockVerbAdapt(x->verbAdapt, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_verbAdapt, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockArgumentInput(HBlockArgumentInput x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _kind = save_CBlockKind(x->kind, ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_kind, ctx);
	  save_string(x->named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchIsNotVerb(HBlockMatchIsNotVerb x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockMatchNOT(HBlockMatchNOT x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _input = save_CBlockMatch(x->input, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_input, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockKindAction(HBlockKindAction x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _applyTo = save_CBlockActionApply(x->applyTo, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_applyTo, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockSelector_All(HBlockSelector_All x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _what = save_CBlock(x->what, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_what, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }

  
 int  save_CBlockMatchIsVerbComposition(HBlockMatchIsVerbComposition x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	   
	  const int _verbComp = save_CBlockMatchList(x->verbComp, ctx);
	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_verbComp, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchWhichNot(HBlockMatchWhichNot x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockUnitTest(HBlockUnitTest x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _contents = save_CBlock(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockInstanceNamed(HBlockInstanceNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);


	  const int _baseKind = save_CBlockKind(x->baseKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_int(x->id, ctx);
	  save_id(_baseKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockKindNamed(HBlockKindNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _named = save_CBlockNoum(x->named, ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_named, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockUnitAssert(HBlockUnitAssert x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _contents = save_CBlock(x->contents, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_contents, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockInstanceAnonymous(HBlockInstanceAnonymous x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _baseKind = save_CBlockKind(x->baseKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_int(x->id, ctx);
	  save_id(_baseKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockToDecideWhat_FirstNoum(HBlockToDecideWhat_FirstNoum x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _queryToMatch = save_CBlockMatchIs(x->queryToMatch, ctx);
	  const int _decideBody = save_CBlock(x->decideBody, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_queryToMatch, ctx);
	  save_id(_decideBody, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockList_AND(HBlockList_AND x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _lista = save_list<CBlock>(x->lista, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_lista, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockAssertion_isNamedValueOf(HBlockAssertion_isNamedValueOf x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _noum = save_CBlock(x->noum, ctx);
	  const int _baseKind = save_CBlock(x->baseKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_noum, ctx);
	  save_id(_baseKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVariableNamed(HBlockVariableNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _name = save_CBlockNoum(x->name, ctx);
	  const int _kind = save_CBlockKind(x->kind, ctx);
	  const int _value = save_CBlock(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_name, ctx);
	  save_id(_kind, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



  int  save_CBlockNoumStr(HBlockNoumStr x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->noum, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


int  save_CBlockNoumStrDet(HBlockNoumStrDet x, SaveContext *ctx)
{
	if (x == nullptr) return 0;
	lock_ptr(x.get(), ctx);	
	const int _noum = save_CBlockNoum(x->noum, ctx);
    const int slot = alloc_slot(x.get(), ctx);
	save_type(x->type(), ctx);
	save_string(x->det, ctx);
	save_id(_noum, ctx);
	end_slot(x.get(), ctx);
	return  slot;

}




int  save_CBlockNoumCompose(HBlockNoumCompose x, SaveContext *ctx)
{
	if (x == nullptr) return 0;
	lock_ptr(x.get(), ctx);
	const std::list<int> _lista = save_vector(x->noums, ctx);
	const int slot = alloc_slot(x.get(), ctx);
	save_type(x->type(), ctx);
	save_id_list(_lista, ctx);
	end_slot(x.get(), ctx);
	return  slot;

}


  int  save_CBlockActionNamed(HBlockActionNamed x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _actionKind = save_CBlockKindAction(x->actionKind, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_id(_actionKind, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockMatchWhich(HBlockMatchWhich x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _obj = save_CBlockMatch(x->obj, ctx);
	  const int _value = save_CBlockMatch(x->value, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_id(_obj, ctx);
	  save_id(_value, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerbAdapt(HBlockVerbAdapt x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);



	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->verb, ctx);
	  save_string(x->tense, ctx);
	  save_string(x->viewPoint, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerbDirectRelation(HBlockVerbDirectRelation x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const int _verbNoum = save_CBlock(x->verbNoum, ctx);
	  const int _relationNoum = save_CBlockNoum(x->relationNoum, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id(_verbNoum, ctx);
	  save_id(_relationNoum, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockVerb(HBlockVerb x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const std::list<int> _conjugations = save_list<CBlockVerbConjugation>(x->conjugations, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_string(x->named, ctx);
	  save_id_list(_conjugations, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockUnderstandStatic(HBlockUnderstandStatic x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _argument_match = save_CBlockMatchList(x->argument_match, ctx);
	  const int _output_n = save_CBlock(x->output_n, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_int(x->entryID, ctx);
	  save_id(_argument_match, ctx);
	  save_id(_output_n, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockEventHandle(HBlockEventHandle x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);

	  const int _eventToObserve = save_CBlockMatchActionCall(x->eventToObserve, ctx);
	  const int _body = save_CBlockComandList(x->body, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_EventHandleStage(x->stage, ctx);
	  save_id(_eventToObserve, ctx);
	  save_id(_body, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }


  int  save_CBlockComandList(HBlockComandList x, SaveContext *ctx)
  {
	  if (x == nullptr) return 0;
	  lock_ptr(x.get(), ctx);
	  const std::list<int> _lista = save_list<CBlock>(x->lista, ctx);
	  const int slot = alloc_slot(x.get(), ctx);
	  save_type(x->type(), ctx);
	  save_id_list(_lista, ctx);
	  end_slot(x.get(), ctx);
	  return  slot;

  }



 
