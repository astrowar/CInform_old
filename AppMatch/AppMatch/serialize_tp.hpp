
#ifndef SERIALIZE_TP_HPP
#define SERIALIZE_TP_HPP
#include <string>
#include <vector>
 
#include "BlockInterpreter.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "CBlockBoolean.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockNumber.hpp"
#include "CBlockControlFlux.hpp"
#include <set>

// templates para dar save e load de cada tipo


 
 








class ArchiveContext
{
public:
	void process(std::string x);
	void process( float x) ;
	void process( int q);
	void process( bool q);
	void process_flag(const char* str, size_t vsize);
	void process_id(BlockType t);
};

 




void store_type(BlockType tp, ArchiveContext *ar);
void store_block(CBlocking::HBlock  s, ArchiveContext *ar);

void store_block_i(const CBlockAction* b, ArchiveContext * ar);
void store_block_i(const CBlockActionApply* b, ArchiveContext * ar);
void store_block_i(const CBlockActionCall* b, ArchiveContext * ar);
void store_block_i(const CBlockActionCallNamed* b, ArchiveContext * ar);
void store_block_i(const CBlockActionInstance* b, ArchiveContext * ar);
void store_block_i(const CBlockActionNamed* b, ArchiveContext * ar);
void store_block_i(const CBlockAnything* b, ArchiveContext * ar);
void store_block_i(const CBlockArgumentInput* b, ArchiveContext * ar);
void store_block_i(const CBlockASimetricRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockAssert* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_canBe* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_InstanceVariable* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_is* b, ArchiveContext * ar);
//void store_block_i(const CBlockAssertion_isActionOf* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isConstantAssign* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isDefaultAssign* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isDirectAssign* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isForbiddenAssign* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isInstanceOf* b, ArchiveContext * ar);
//void store_block_i(const CBlockAssertion_isKindOf* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isLocalVariable* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isNamedValueOf* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isNotDirectAssign* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertion_isVariable* b, ArchiveContext * ar);
void store_block_i(const CBlockAssertionBase* b, ArchiveContext * ar);
//void store_block_i(const CBlockAssertionCond* b, ArchiveContext * ar);
void store_block_i(const CBlockBooleanAND* b, ArchiveContext * ar);
void store_block_i(const CBlockBooleanNOT* b, ArchiveContext * ar);
void store_block_i(const CBlockBooleanOR* b, ArchiveContext * ar);
void store_block_i(const CBlockBooleanResult* b, ArchiveContext * ar);
void store_block_i(const CBlockBooleanValue* b, ArchiveContext * ar);
void store_block_i(const CBlockComandList* b, ArchiveContext * ar);
void store_block_i(const CBlockCompostionPhrase* b, ArchiveContext * ar);
void store_block_i(const CBlockConditionalRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockControlForEach* b, ArchiveContext * ar);
void store_block_i(const CBlockControlIF* b, ArchiveContext * ar);
void store_block_i(const CBlockControlSelect* b, ArchiveContext * ar);
void store_block_i(const CBlockControlSelectItem* b, ArchiveContext * ar);
void store_block_i(const CBlockControlToken* b, ArchiveContext * ar);
void store_block_i(const CBlockControlUnless* b, ArchiveContext * ar);
void store_block_i(const CBlockDinamicDispatch* b, ArchiveContext * ar);
void store_block_i(const CBlockEnums* b, ArchiveContext * ar);
void store_block_i(const CBlockEventHandle* b, ArchiveContext * ar);
void store_block_i(const CBlockEvery* b, ArchiveContext * ar);
void store_block_i(const CBlockExecutionResultFlag* b, ArchiveContext * ar);
void store_block_i(const CBlockFactionalNumber* b, ArchiveContext * ar);
void store_block_i(const CBlockFilter* b, ArchiveContext * ar);
void store_block_i(const CBlockFilterAtom* b, ArchiveContext * ar);
void store_block_i(const CBlockFilterList* b, ArchiveContext * ar);
void store_block_i(const CBlockIF* b, ArchiveContext * ar);
void store_block_i(const CBlockInstance* b, ArchiveContext * ar);
void store_block_i(const CBlockInstanceNamed* b, ArchiveContext * ar);
void store_block_i(const CBlockInstanceVariable* b, ArchiveContext * ar);
void store_block_i(const CBlockIntegerNumber* b, ArchiveContext * ar);
void store_block_i(const CBlockIsAdverbialComparasion* b, ArchiveContext * ar);
void store_block_i(const CBlockIsNotVerb* b, ArchiveContext * ar);
void store_block_i(const CBlockIsVerb* b, ArchiveContext * ar);
void store_block_i(const CBlockKind* b, ArchiveContext * ar);
void store_block_i(const CBlockKind_InstanceVariable* b, ArchiveContext * ar);
void store_block_i(const CBlockKindAction* b, ArchiveContext * ar);
void store_block_i(const CBlockKindEntity* b, ArchiveContext * ar);
void store_block_i(const CBlockKindNamed* b, ArchiveContext * ar);
void store_block_i(const CBlockKindOf* b, ArchiveContext * ar);
void store_block_i(const CBlockKindOfName* b, ArchiveContext * ar);
void store_block_i(const CBlockKindReference* b, ArchiveContext * ar);
void store_block_i(const CBlockKindValue* b, ArchiveContext * ar);
void store_block_i(const CBlockList* b, ArchiveContext * ar);
void store_block_i(const CBlockList_AND* b, ArchiveContext * ar);
void store_block_i(const CBlockList_OR* b, ArchiveContext * ar);
void store_block_i(const CBlockMatch* b, ArchiveContext * ar);
//void store_block_i(const CBlockMatchAction* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchActionCall* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchAND* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchAny* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchBlock* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchDirectIs* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchDirectIsNot* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchIs* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchIsAdverbialComparasion* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchIsNotVerb* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchIsVerb* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchKind* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchList* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchNamed* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchNOT* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchNoum* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchOR* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchProperty* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchValue* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchWhich* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchWhichNot* b, ArchiveContext * ar);
void store_block_i(const CBlockMatchWith* b, ArchiveContext * ar);
void store_block_i(const CBlockNamedValue* b, ArchiveContext * ar);
void store_block_i(const CBlockNothing* b, ArchiveContext * ar);
void store_block_i(const CBlockNoum* b, ArchiveContext * ar);
void store_block_i(const CBlockNoumSupl* b, ArchiveContext * ar);
void store_block_i(const CBlockNow* b, ArchiveContext * ar);
void store_block_i(const CBlockNumber* b, ArchiveContext * ar);
void store_block_i(const CBlockPhraseDefine* b, ArchiveContext * ar);
void store_block_i(const CBlockPhraseHeader* b, ArchiveContext * ar);
void store_block_i(const CBlockPhraseInvoke* b, ArchiveContext * ar);
void store_block_i(const CBlockProperty* b, ArchiveContext * ar);
void store_block_i(const CBlockRelationArguments* b, ArchiveContext * ar);
void store_block_i(const CBlockRelationBase* b, ArchiveContext * ar);
void store_block_i(const CBlockRelationInstance* b, ArchiveContext * ar);
void store_block_i(const CBlockRelationLookup* b, ArchiveContext * ar);
void store_block_i(const CBlockSame* b, ArchiveContext * ar);
void store_block_i(const CBlockSelector* b, ArchiveContext * ar);
void store_block_i(const CBlockSelector_All* b, ArchiveContext * ar);
void store_block_i(const CBlockSelector_Any* b, ArchiveContext * ar);
void store_block_i(const CBlockSelector_Where* b, ArchiveContext * ar);
void store_block_i(const CBlockSelectorAND* b, ArchiveContext * ar);
void store_block_i(const CBlockSimetricRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockStaticDispatch* b, ArchiveContext * ar);
void store_block_i(const CBlockText* b, ArchiveContext * ar);
void store_block_i(const CBlockTextSentence* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecide* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecideIf* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecideOn* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecideWhat* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecideWhat_FirstNoum* b, ArchiveContext * ar);
void store_block_i(const CBlockToDecideWhether* b, ArchiveContext * ar);
//void store_block_i(const CBlockTransform* b, ArchiveContext * ar);
void store_block_i(const CBlockTryCall* b, ArchiveContext * ar);
void store_block_i(const CBlockUnderstand* b, ArchiveContext * ar);
void store_block_i(const CBlockUnderstandDynamic* b, ArchiveContext * ar);
void store_block_i(const CBlockUnderstandStatic* b, ArchiveContext * ar);
void store_block_i(const CBlockUnitAssert* b, ArchiveContext * ar);
void store_block_i(const CBlockUnitInit* b, ArchiveContext * ar);
void store_block_i(const CBlockUnitTest* b, ArchiveContext * ar);
void store_block_i(const CBlockValue* b, ArchiveContext * ar);
void store_block_i(const CBlockVerb* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbAdapt* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbConjugation* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbDirectRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbLookup* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbNegate* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockVerbReverseRelation* b, ArchiveContext * ar);
void store_block_i(const CBlockExecution* b, ArchiveContext * ar);

template<typename T>   void store_block(std::vector<T> s, ArchiveContext *ar);
template< >   void store_block(std::vector<HBlock> s, ArchiveContext *ar);
template< >   void store_block(std::vector<HVariableSlot> s, ArchiveContext *ar);


template<typename T>  void store_block(std::list<T> s, ArchiveContext *ar);



#endif // SERIALIZE_TP_HPP
