
 
#include "CBlockBoolean.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockNumber.hpp"
#include "CBlockControlFlux.hpp"
#include "CBlockComposition.hpp"
#include "sharedCast.hpp"
#include <algorithm>
#include <cctype>
#include <locale>

/*


*   CBlockInstance  CBlock
*   CBlockInstanceNamed  CBlockInstance
*   CBlockText  CBlock
*   CBlockTextSentence  CBlock
CBlockKind  CBlock
CBlockValue  CBlock
*   CBlockKindReference  CBlockValue
CBlockBooleanResult  CBlockValue
*   CBlockNoum  CBlock
*   CBlockNoumSupl  CBlockNoum
*   CBlockKindNamed  CBlockKind
*   CBlockNothing  CBlock
*   CBlockAnything  CBlock
*   CBlockKindOfName  CBlock
*   CBlockKindOf  CBlock
*   CBlockActionApply  CBlock
*   CBlockKindAction  CBlockKind
*   CBlockKindValue  CBlockKind
*   CBlockKindEntity  CBlockKind
*   CBlockNamedValue  CBlockValue
*   CBlockProperty  CBlock
*   CBlockInstanceVariable  CBlock
*   CBlockKind_InstanceVariable  CBlock
*   CBlockList  CBlock
*   CBlockList_OR  CBlockList
*   CBlockList_AND  CBlockList
*   CBlockEnums  CBlock
CBlockVerbRelation  CBlock
*   CBlockVerbDirectRelation  CBlockVerbRelation
*   CBlockVerbReverseRelation  CBlockVerbRelation
CBlockFilter  CBlock
CBlockFilterAtom  CBlockFilter
CBlockFilterList  CBlockFilter
*   CBlockDinamicDispatch  CBlock
CBlockIF  CBlock
CBlockSame  CBlockBooleanResult
*   CBlockVerbConjugation  CBlock
*   CBlockVerb  CBlock
*   CBlockVerbAdapt  CBlock
*   CBlockVerbNegate  CBlock
CBlockSelector  CBlock
*   CBlockSelector_All  CBlockSelector
*   CBlockSelector_Any  CBlockSelector
*   CBlockSelector_Where  CBlockSelector
*   CBlockAction  CBlock
*   CBlockActionInstance  CBlockAction
*   CBlockActionNamed  CBlockAction
*   CBlockTryCall  CBlock
*   CBlockActionCall  CBlock
*   CBlockActionCallNamed  CBlockActionCall
*   CBlockStaticDispatch  CBlockActionCall
CBlockAssertionBase  CBlock
CBlockAssertion_is  CBlockAssertionBase
*   CBlockAssertion_canBe  CBlockAssertionBase
*   CBlockAssertion_isInstanceOf  CBlockAssertion_is
*   CBlockAssertion_isNamedValueOf  CBlockAssertion_is
*   CBlockAssertion_isVariable  CBlockAssertion_is
*   CBlockAssertion_isLocalVariable  CBlockAssertion_is
*   CBlockAssertion_isDefaultAssign  CBlockAssertion_is
*   CBlockAssertion_isConstantAssign  CBlockAssertion_is
*   CBlockAssertion_isForbiddenAssign  CBlockAssertion_is
*   CBlockAssertion_isDirectAssign  CBlockAssertion_is
*   CBlockAssertion_isNotDirectAssign  CBlockAssertion_is
*   CBlockIsVerb  CBlockAssertion_is
*   CBlockIsNotVerb  CBlockAssertion_is
*   CBlockIsAdverbialComparasion  CBlockAssertion_is
*   CBlockAssert  CBlock
*   CBlockAssertion_InstanceVariable  CBlock
*   CBlockBooleanValue  CBlockValue
*   CBlockBooleanAND  CBlock
*   CBlockBooleanOR  CBlock
*   CBlockBooleanNOT  CBlock
*   CBlockNow  CBlock
*   CBlockEvery  CBlock
*   CBlockComandList  CBlock
*   CBlockEventHandle  CBlock
*   CBlockComposition  CBlockKind
*   CBlockCompositionList  CBlockComposition
*   CBlockCompositionRelation  CBlockComposition
*   CBlockCompositionPhrase  CBlockComposition
*   CBlockCompostionPhrase  CBlock
*   CBlockControlToken  CBlock
*   CBlockControlIF  CBlock
*   CBlockControlUnless  CBlock
*   CBlockControlSelectItem  CBlock
*   CBlockControlSelect  CBlock
*   CBlockControlForEach  CBlock
*   CBlockExecutionResultFlag  CBlock
CBlockToDecide  CBlock
*   CBlockToDecideIf  CBlockToDecide
*   CBlockToDecideWhether  CBlockToDecide
*   CBlockToDecideWhat  CBlockToDecide
*   CBlockToDecideWhat_FirstNoum  CBlockToDecide
*   CBlockToDecideOn  CBlock
*   CBlockPhraseHeader  CBlock
*   CBlockPhraseDefine  CBlock
*   CBlockPhraseInvoke  CBlock
CBlockMatch  CBlock
*   CBlockMatchAny  CBlockMatch
*   CBlockMatchNamed  CBlockMatch
*   CBlockMatchNoum  CBlockMatch
*   CBlockMatchValue  CBlockMatch
*   CBlockMatchKind  CBlockMatch
CBlockMatchWith  CBlockMatch
*   CBlockMatchList  CBlockMatch
*   CBlockMatchAND  CBlockMatch
*   CBlockMatchNOT  CBlockMatch
*   CBlockMatchOR  CBlockMatch
*   CBlockMatchActionCall  CBlockMatch
*   CBlockMatchBlock  CBlockMatch
CBlockMatchIs  CBlockMatch
*   CBlockMatchDirectIs  CBlockMatchIs
*   CBlockMatchDirectIsNot  CBlockMatchIs
*   CBlockMatchIsVerb  CBlockMatchIs
*   CBlockMatchIsNotVerb  CBlockMatchIs
*   CBlockMatchIsAdverbialComparasion  CBlockMatchIs
*   CBlockMatchProperty  CBlockMatch
*   CBlockMatchWhich  CBlockMatchIs
*   CBlockMatchWhichNot  CBlockMatchIs
CBlockNumber  CBlockValue
*   CBlockIntegerNumber  CBlockNumber
*   CBlockFactionalNumber  CBlockNumber
*   CBlockArgumentInput  CBlock
CBlockRelationBase  CBlock
*   CBlockSimetricRelation  CBlockRelationBase
*   CBlockASimetricRelation  CBlockRelationBase
*   CBlockRelationInstance  CBlock
*   CBlockConditionalRelation  CBlockRelationBase
*   CBlockRelationLookup  CBlock
*   CBlockVerbLookup  CBlock
*   CBlockRelationArguments  CBlock
*   CBlockSelectorAND  CBlock
CBlockUnderstand  CBlock
*   CBlockUnderstandStatic  CBlock
*   CBlockUnderstandDynamic  CBlock



*/
using namespace  CBlocking;
 
class LoadContext
{
	std::string data;
	size_t cursor;
	
public:
	LoadContext(string _data);

	std::string   get_line()
	{
		size_t scursor = cursor; //nao varia o cursor
		for(size_t i = scursor; i < data.size();++i)
		{
			if ((data[i] == '\n') || (data[i] == '\r'))
			{ 
				auto ret = data.substr(scursor, i - scursor);

			    return ret;
			}
		}
		return  data.substr(scursor, data.size() - scursor);
	};

	bool is_empty_line()
	{
		if (cursor >= data.size()) return true;
		std::string s = get_line();
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {	return !std::isspace(ch); }));
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {	return !std::isspace(ch);}).base(), s.end());
		return s.size() == 0;
	}


	std::string   load_item()
	{
       printf("item %.10s \n", data.c_str()+cursor);
		while (data[cursor] == ' ') cursor++;
		for (size_t i = cursor; i < data.size(); ++i)
		{
			//if ((data[i] == ' ')||(data[i] == '\n')||(data[i] == '\r')||(data[i] == '\t') )
			if (data[i] == ' ') 
			{
				auto ret = data.substr(cursor, i - cursor);
				cursor = i + 1;
				return ret;
			}
		}
		return "ERRRRR";
	}

	std::string   load_string()
	{
		while (data[cursor] != '\'') cursor++;
		cursor++;
		for (size_t i = cursor; i < data.size(); ++i)
		{
			if (data[i] == '\'')
			{
				auto ret = data.substr(cursor, i - cursor);
				cursor = i + 2;
				return ret;
			}
		}
		return  data.substr(cursor, data.size() - cursor);
	}
	int  load_int()
	{
		auto s = load_item();
		return stoi(s);
	};
	float  load_float() {
		auto s = load_item();
		return stof(s);
	};
	bool   load_bool()
	{
		auto s = load_item();
		if (s == "true") return true;
		if (s == "false") return false;
		return false;
	}; 
	BlockType load_type()
	{
		return static_cast<BlockType>(load_int());
	};
	void new_line()
	{
		if (cursor >= data.size()) return;
		while (data[cursor] != '\n')
		{
			cursor++;
			if (cursor >= data.size()) return;
		}
		cursor++; //posicao na proxima linha
	};
	bool end_file() 
	{
		return cursor >= data.size();
	}
	 std::map<int, HBlock> cache;
};


 

int load_type(  LoadContext *ctx)
{
	return ctx->load_type();
}
std::string load_string(LoadContext *ctx)
{
	return ctx->load_string();
}

int load_int(LoadContext *ctx)
{
	return ctx->load_int();
}

 


float load_float(LoadContext *ctx)
{
	  return ctx->load_float();
}
bool load_bool(LoadContext *ctx) { return ctx->load_bool(); }


HBlock load_CBlock_slot(int slot_id, LoadContext *ctx);


template<typename T>  std::list<std::shared_ptr<T> > load_list(LoadContext *ctx)
{
	std::list<std::shared_ptr<T> > ret;
	auto s = ctx->load_item(); //open curl
	if (s != "(")
	{
		printf("ERROR\n");
	}
	while (s != ")" && s != "\n")
	{
		s = ctx->load_item();
		if (s == ")") break;

		const int slot = stoi(s);
		ret.push_back(  std::static_pointer_cast<T>(load_CBlock_slot(slot,ctx)));
		
	}
	return ret;
}

template<typename T>  std::vector<std::shared_ptr<T> > load_vector(LoadContext *ctx)
{
	std::vector<std::shared_ptr<T> > ret;
	auto s = ctx->load_item();
	if (s != "(")
	{
		printf("ERROR\n");
	}

	while (s != ")" && s != "\n")
	{		s = ctx->load_item(); 
		if (s == ")") break;
		const int slot = stoi(s);
		ret.push_back(std::static_pointer_cast<T>(load_CBlock_slot(slot, ctx)));

	}
	return ret;
}

NoumLocation  load_NoumLocation(LoadContext *ctx) { return static_cast<NoumLocation>(load_int(ctx)); }

EventHandleStage   load_EventHandleStage(LoadContext *ctx) { return static_cast<EventHandleStage>(load_int(ctx)); }

PhaseResultFlag  load_PhaseResultFlag(LoadContext *ctx) { return static_cast<PhaseResultFlag>(load_int(ctx)); }

void cmp_type(int tp, BlockType t)
{
	if (tp != t)
	{
		printf("ErrorCMP");
	}

}
 
 
 
HBlock load_CBlock(int tp, LoadContext *ctx);

 

    void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
    void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
    void trim(std::string &s) {
    ltrim(s);
	rtrim(s);
}



HBlock load_line(LoadContext *ctx)
{
	HBlock _b = nullptr;
	auto s = ctx->get_line(); 
	trim(s);
	printf("Line:|%s|\n", s.c_str());
	if (s.empty() == false)
	{
		const int slot_id = load_int(ctx);
		_b = load_CBlock(-1, ctx);
		ctx->cache[slot_id] = _b;
		//_b->dump("L   ");
	}
	ctx->new_line(); //le o new line do arquivo
	while (ctx->is_empty_line())
	{
		ctx->new_line();
		if (ctx->end_file()) break;
	}
	return _b;
}

HBlock load_file(LoadContext *ctx)
{
	HBlock last = nullptr;

	while (ctx->end_file() ==false )
	{
		last = load_line(ctx);
		

	}
	return last;
}

int load_id(LoadContext *ctx)
{
	return load_int(ctx);
}

LoadContext::LoadContext(string _data): data(_data), cursor(0)
{
}

HBlock load_CBlock_slot(int slot_id, LoadContext *ctx)
{
	if (slot_id == 0) return nullptr;
	return ctx->cache[slot_id];
}



 


 


 //invalidos

HBlockFilterAtom  load_CBlockFilterAtom(int tp, LoadContext *ctx) { return nullptr; }
HBlockFilterList load_CBlockFilterList(int tp, LoadContext *ctx) { return nullptr; }
HBlockSame load_CBlockSame(int tp, LoadContext *ctx) { return nullptr; }
HBlockMatchWith load_CBlockMatchWith(int tp, LoadContext *ctx) { return nullptr; }
HBlockUnderstand load_CBlockUnderstand(int tp, LoadContext *ctx) { return nullptr; }
HBlockIF load_CBlockIF(int tp, LoadContext *ctx) { return nullptr; }
 
 
 
 
 
 
 





 



HBlockInstance  load_CBlockInstance(int tp, LoadContext *ctx);
HBlockInstanceAnonymous  load_CBlockInstanceAnonymous(int tp, LoadContext *ctx);
HBlockInstanceNamed  load_CBlockInstanceNamed(int tp, LoadContext *ctx);
HBlockText  load_CBlockText(int tp, LoadContext *ctx);
HBlockTextSentence  load_CBlockTextSentence(int tp, LoadContext *ctx);
HBlockValue  load_CBlockValue(int tp, LoadContext *ctx);
HBlockKindReference  load_CBlockKindReference(int tp, LoadContext *ctx);
HBlockNoum  load_CBlockNoum(int tp, LoadContext *ctx);
HBlockNoumStr  load_CBlockNoumStr(int tp, LoadContext *ctx);
HBlockNoumStrDet  load_CBlockNoumStrDet(int tp, LoadContext *ctx);
HBlockNoumCompose  load_CBlockNoumCompose(int tp, LoadContext *ctx);
HBlockNoumSupl  load_CBlockNoumSupl(int tp, LoadContext *ctx);
HBlockKindNamed  load_CBlockKindNamed(int tp, LoadContext *ctx);
HBlockNothing  load_CBlockNothing(int tp, LoadContext *ctx);
HBlockAnything  load_CBlockAnything(int tp, LoadContext *ctx);
HBlockKindOfName  load_CBlockKindOfName(int tp, LoadContext *ctx);
HBlockKindOf  load_CBlockKindOf(int tp, LoadContext *ctx);
HBlockActionApply  load_CBlockActionApply(int tp, LoadContext *ctx);
HBlockKindAction  load_CBlockKindAction(int tp, LoadContext *ctx);
HBlockKindValue  load_CBlockKindValue(int tp, LoadContext *ctx);
HBlockKindEntity  load_CBlockKindEntity(int tp, LoadContext *ctx);
HBlockNamedValue  load_CBlockNamedValue(int tp, LoadContext *ctx);
HBlockProperty  load_CBlockProperty(int tp, LoadContext *ctx);
HBlockInstanceVariable  load_CBlockInstanceVariable(int tp, LoadContext *ctx);
HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable(int tp, LoadContext *ctx);
HBlockCollection  load_CBlockCollection(int tp, LoadContext *ctx);
HBlockList  load_CBlockList(int tp, LoadContext *ctx);
HBlockList_OR  load_CBlockList_OR(int tp, LoadContext *ctx);
HBlockList_AND  load_CBlockList_AND(int tp, LoadContext *ctx);
HBlockEnums  load_CBlockEnums(int tp, LoadContext *ctx);
HBlockVerbRelation  load_CBlockVerbRelation(int tp, LoadContext *ctx);
HBlockVerbDirectRelation  load_CBlockVerbDirectRelation(int tp, LoadContext *ctx);
HBlockVerbReverseRelation  load_CBlockVerbReverseRelation(int tp, LoadContext *ctx);
HBlockFilterAtom  load_CBlockFilterAtom(int tp, LoadContext *ctx);
HBlockFilterList  load_CBlockFilterList(int tp, LoadContext *ctx);
HBlockDinamicDispatch  load_CBlockDinamicDispatch(int tp, LoadContext *ctx);
HBlockIF  load_CBlockIF(int tp, LoadContext *ctx);
HBlockSame  load_CBlockSame(int tp, LoadContext *ctx);
HBlockVerbConjugation  load_CBlockVerbConjugation(int tp, LoadContext *ctx);
HBlockVerb  load_CBlockVerb(int tp, LoadContext *ctx);
HBlockVerbAdapt  load_CBlockVerbAdapt(int tp, LoadContext *ctx);
HBlockVerbNegate  load_CBlockVerbNegate(int tp, LoadContext *ctx);
HBlockSelector  load_CBlockSelector(int tp, LoadContext *ctx);
HBlockSelector_All  load_CBlockSelector_All(int tp, LoadContext *ctx);
HBlockSelector_Any  load_CBlockSelector_Any(int tp, LoadContext *ctx);
HBlockSelector_Where  load_CBlockSelector_Where(int tp, LoadContext *ctx);
HBlockAction  load_CBlockAction(int tp, LoadContext *ctx);
HBlockActionInstance  load_CBlockActionInstance(int tp, LoadContext *ctx);
HBlockActionNamed  load_CBlockActionNamed(int tp, LoadContext *ctx);
HBlockActionNamed  load_CBlockActionNamed(int tp, LoadContext *ctx);
HBlockTryCall  load_CBlockTryCall(int tp, LoadContext *ctx);
HBlockActionCall  load_CBlockActionCall(int tp, LoadContext *ctx);
HBlockActionCallNamed  load_CBlockActionCallNamed(int tp, LoadContext *ctx);
HBlockStaticDispatch  load_CBlockStaticDispatch(int tp, LoadContext *ctx);
HBlockAssertionBase  load_CBlockAssertionBase(int tp, LoadContext *ctx);
HBlockAssertion_is  load_CBlockAssertion_is(int tp, LoadContext *ctx);
HBlockAssertion_canBe  load_CBlockAssertion_canBe(int tp, LoadContext *ctx);
HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf(int tp, LoadContext *ctx);
HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf(int tp, LoadContext *ctx);
HBlockAssertion_isVariable  load_CBlockAssertion_isVariable(int tp, LoadContext *ctx);
HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable(int tp, LoadContext *ctx);
HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign(int tp, LoadContext *ctx);
HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign(int tp, LoadContext *ctx);
HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign(int tp, LoadContext *ctx);
HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign(int tp, LoadContext *ctx);
HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign(int tp, LoadContext *ctx);
HBlockIsVerb  load_CBlockIsVerb(int tp, LoadContext *ctx);
HBlockIsNotVerb  load_CBlockIsNotVerb(int tp, LoadContext *ctx);
HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion(int tp, LoadContext *ctx);
HBlockAssert  load_CBlockAssert(int tp, LoadContext *ctx);
HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable(int tp, LoadContext *ctx);
HBlockBooleanValue  load_CBlockBooleanValue(int tp, LoadContext *ctx);
HBlockBooleanAND  load_CBlockBooleanAND(int tp, LoadContext *ctx);
HBlockBooleanOR  load_CBlockBooleanOR(int tp, LoadContext *ctx);
HBlockBooleanNOT  load_CBlockBooleanNOT(int tp, LoadContext *ctx);
HBlockNow  load_CBlockNow(int tp, LoadContext *ctx);
HBlockEvery  load_CBlockEvery(int tp, LoadContext *ctx);
HBlockComandList  load_CBlockComandList(int tp, LoadContext *ctx);
HBlockEventHandle  load_CBlockEventHandle(int tp, LoadContext *ctx);
HBlockComposition  load_CBlockComposition(int tp, LoadContext *ctx);
HBlockCompositionList  load_CBlockCompositionList(int tp, LoadContext *ctx);
HBlockCompositionRulebook  load_CBlockCompositionRulebook(int tp, LoadContext *ctx);
HBlockCompositionRelation  load_CBlockCompositionRelation(int tp, LoadContext *ctx);
HBlockCompositionPhrase  load_CBlockCompositionPhrase(int tp, LoadContext *ctx);
HBlockCompostionPhrase  load_CBlockCompostionPhrase(int tp, LoadContext *ctx);
HBlockControlToken  load_CBlockControlToken(int tp, LoadContext *ctx);
HBlockControlIF  load_CBlockControlIF(int tp, LoadContext *ctx);
HBlockControlUnless  load_CBlockControlUnless(int tp, LoadContext *ctx);
HBlockControlSelectItem  load_CBlockControlSelectItem(int tp, LoadContext *ctx);
HBlockControlSelect  load_CBlockControlSelect(int tp, LoadContext *ctx);
HBlockControlForEach  load_CBlockControlForEach(int tp, LoadContext *ctx);
HBlockExecutionResultFlag  load_CBlockExecutionResultFlag(int tp, LoadContext *ctx);
HBlockUnitInit  load_CBlockUnitInit(int tp, LoadContext *ctx);
HBlockUnitTest  load_CBlockUnitTest(int tp, LoadContext *ctx);
HBlockUnitAssert  load_CBlockUnitAssert(int tp, LoadContext *ctx);
HBlockToDecide  load_CBlockToDecide(int tp, LoadContext *ctx);
HBlockToDecideIf  load_CBlockToDecideIf(int tp, LoadContext *ctx);
HBlockToDecideWhether  load_CBlockToDecideWhether(int tp, LoadContext *ctx);
HBlockToDecideWhat  load_CBlockToDecideWhat(int tp, LoadContext *ctx);
HBlockToDecideWhat_FirstNoum  load_CBlockToDecideWhat_FirstNoum(int tp, LoadContext *ctx);
HBlockToDecideOn  load_CBlockToDecideOn(int tp, LoadContext *ctx);
HBlockPhraseHeader  load_CBlockPhraseHeader(int tp, LoadContext *ctx);
HBlockPhraseDefine  load_CBlockPhraseDefine(int tp, LoadContext *ctx);
HBlockPhraseInvoke  load_CBlockPhraseInvoke(int tp, LoadContext *ctx);

HBlockBody   load_CBlockBody(int tp, LoadContext *ctx);
 
HBlockMatch  load_CBlockMatch(int tp, LoadContext *ctx);
HBlockMatchAny  load_CBlockMatchAny(int tp, LoadContext *ctx);
HBlockMatchNamed  load_CBlockMatchNamed(int tp, LoadContext *ctx);
HBlockMatchNoum  load_CBlockMatchNoum(int tp, LoadContext *ctx);
HBlockMatchKind  load_CBlockMatchKind(int tp, LoadContext *ctx);
HBlockMatchText  load_CBlockMatchText(int tp, LoadContext *ctx);
HBlockMatchValue  load_CBlockMatchValue(int tp, LoadContext *ctx);
HBlockMatchKind  load_CBlockMatchKind(int tp, LoadContext *ctx);
HBlockMatchWith  load_CBlockMatchWith(int tp, LoadContext *ctx);
HBlockMatchList  load_CBlockMatchList(int tp, LoadContext *ctx);
HBlockMatchAND  load_CBlockMatchAND(int tp, LoadContext *ctx);
HBlockMatchNOT  load_CBlockMatchNOT(int tp, LoadContext *ctx);
HBlockMatchOR  load_CBlockMatchOR(int tp, LoadContext *ctx);
HBlockMatchActionCall  load_CBlockMatchActionCall(int tp, LoadContext *ctx);
HBlockMatchBlock  load_CBlockMatchBlock(int tp, LoadContext *ctx);
HBlockMatchIs  load_CBlockMatchIs(int tp, LoadContext *ctx);
HBlockMatchDirectIs  load_CBlockMatchDirectIs(int tp, LoadContext *ctx);
HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot(int tp, LoadContext *ctx);
HBlockMatchIsVerb  load_CBlockMatchIsVerb(int tp, LoadContext *ctx);
HBlockMatchIsVerbComposition  load_CBlockMatchIsVerbComposition(int tp, LoadContext *ctx);
HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb(int tp, LoadContext *ctx);
HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion(int tp, LoadContext *ctx);
HBlockMatchProperty  load_CBlockMatchProperty(int tp, LoadContext *ctx);
HBlockMatchWhich  load_CBlockMatchWhich(int tp, LoadContext *ctx);
HBlockMatchWhichNot  load_CBlockMatchWhichNot(int tp, LoadContext *ctx);
HBlockVariableNamed  load_CBlockVariableNamed(int tp, LoadContext *ctx);
HBlockNumber  load_CBlockNumber(int tp, LoadContext *ctx);
HBlockIntegerNumber  load_CBlockIntegerNumber(int tp, LoadContext *ctx);
HBlockFactionalNumber  load_CBlockFactionalNumber(int tp, LoadContext *ctx);
HBlockArgumentInput  load_CBlockArgumentInput(int tp, LoadContext *ctx);
HBlockRelationBase  load_CBlockRelationBase(int tp, LoadContext *ctx);
HBlockSimetricRelation  load_CBlockSimetricRelation(int tp, LoadContext *ctx);
HBlockASimetricRelation  load_CBlockASimetricRelation(int tp, LoadContext *ctx);
HBlockRelationInstance  load_CBlockRelationInstance(int tp, LoadContext *ctx);
HBlockConditionalRelation  load_CBlockConditionalRelation(int tp, LoadContext *ctx);
HBlockRelationLookup  load_CBlockRelationLookup(int tp, LoadContext *ctx);
HBlockVerbLookup  load_CBlockVerbLookup(int tp, LoadContext *ctx);
HBlockRelationArguments  load_CBlockRelationArguments(int tp, LoadContext *ctx);
HBlockSelectorAND  load_CBlockSelectorAND(int tp, LoadContext *ctx);
HBlockExecution  load_CBlockExecution(int tp, LoadContext *ctx);
HBlockUnderstand  load_CBlockUnderstand(int tp, LoadContext *ctx);
HBlockUnderstandStatic  load_CBlockUnderstandStatic(int tp, LoadContext *ctx);
HBlockUnderstandDynamic  load_CBlockUnderstandDynamic(int tp, LoadContext *ctx);
HBlockVerbRelation  load_CBlockVerbRelation(int tp, LoadContext *ctx);
HBlockCollection  load_CBlockCollection(int tp, LoadContext *ctx);
HBlockMatch  load_CBlockMatch(int tp, LoadContext *ctx);
HBlockAssertionBase  load_CBlockAssertionBase(int tp, LoadContext *ctx);
HBlock  load_CBlock(int tp, LoadContext *ctx);
HBlockAction  load_CBlockAction(int tp, LoadContext *ctx);
HBlockAssertion_is  load_CBlockAssertion_is(int tp, LoadContext *ctx);
HBlockActionCall  load_CBlockActionCall(int tp, LoadContext *ctx);
HBlockKind  load_CBlockKind(int tp, LoadContext *ctx);
HBlockSelector  load_CBlockSelector(int tp, LoadContext *ctx);
HBlockNumber  load_CBlockNumber(int tp, LoadContext *ctx);
HBlockToDecide  load_CBlockToDecide(int tp, LoadContext *ctx);
HBlockRelationBase  load_CBlockRelationBase(int tp, LoadContext *ctx);
HBlockInstance  load_CBlockInstance(int tp, LoadContext *ctx);
HBlockValue  load_CBlockValue(int tp, LoadContext *ctx);
HBlockFilter  load_CBlockFilter(int tp, LoadContext *ctx);
HBlockBooleanResult  load_CBlockBooleanResult(int tp, LoadContext *ctx);
HBlockComposition  load_CBlockComposition(int tp, LoadContext *ctx);
HBlockMatchIs  load_CBlockMatchIs(int tp, LoadContext *ctx);
HBlockNoum  load_CBlockNoum(int tp, LoadContext *ctx);
HBlockInstance  load_CBlockInstance_slot(int tp, LoadContext *ctx);
HBlockInstanceAnonymous  load_CBlockInstanceAnonymous_slot(int tp, LoadContext *ctx);
HBlockInstanceNamed  load_CBlockInstanceNamed_slot(int tp, LoadContext *ctx);
HBlockText  load_CBlockText_slot(int tp, LoadContext *ctx);
HBlockTextSentence  load_CBlockTextSentence_slot(int tp, LoadContext *ctx);
HBlockValue  load_CBlockValue_slot(int tp, LoadContext *ctx);
HBlockKindReference  load_CBlockKindReference_slot(int tp, LoadContext *ctx);
HBlockNoum  load_CBlockNoum_slot(int tp, LoadContext *ctx);
HBlockNoumStr  load_CBlockNoumStr_slot(int tp, LoadContext *ctx);
HBlockNoumSupl  load_CBlockNoumSupl_slot(int tp, LoadContext *ctx);
HBlockKindNamed  load_CBlockKindNamed_slot(int tp, LoadContext *ctx);
HBlockNothing  load_CBlockNothing_slot(int tp, LoadContext *ctx);
HBlockAnything  load_CBlockAnything_slot(int tp, LoadContext *ctx);
HBlockKindOfName  load_CBlockKindOfName_slot(int tp, LoadContext *ctx);
HBlockKindOf  load_CBlockKindOf_slot(int tp, LoadContext *ctx);
HBlockActionApply  load_CBlockActionApply_slot(int tp, LoadContext *ctx);
HBlockKindAction  load_CBlockKindAction_slot(int tp, LoadContext *ctx);
HBlockKindValue  load_CBlockKindValue_slot(int tp, LoadContext *ctx);
HBlockKindEntity  load_CBlockKindEntity_slot(int tp, LoadContext *ctx);
HBlockNamedValue  load_CBlockNamedValue_slot(int tp, LoadContext *ctx);
HBlockProperty  load_CBlockProperty_slot(int tp, LoadContext *ctx);
HBlockInstanceVariable  load_CBlockInstanceVariable_slot(int tp, LoadContext *ctx);
HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable_slot(int tp, LoadContext *ctx);
HBlockCollection  load_CBlockCollection_slot(int tp, LoadContext *ctx);
HBlockList  load_CBlockList_slot(int tp, LoadContext *ctx);
HBlockList_OR  load_CBlockList_OR_slot(int tp, LoadContext *ctx);
HBlockList_AND  load_CBlockList_AND_slot(int tp, LoadContext *ctx);
HBlockEnums  load_CBlockEnums_slot(int tp, LoadContext *ctx);
HBlockVerbRelation  load_CBlockVerbRelation_slot(int tp, LoadContext *ctx);
HBlockVerbDirectRelation  load_CBlockVerbDirectRelation_slot(int tp, LoadContext *ctx);
HBlockVerbReverseRelation  load_CBlockVerbReverseRelation_slot(int tp, LoadContext *ctx);
HBlockFilterAtom  load_CBlockFilterAtom_slot(int tp, LoadContext *ctx);
HBlockFilterList  load_CBlockFilterList_slot(int tp, LoadContext *ctx);
HBlockDinamicDispatch  load_CBlockDinamicDispatch_slot(int tp, LoadContext *ctx);
HBlockIF  load_CBlockIF_slot(int tp, LoadContext *ctx);
HBlockSame  load_CBlockSame_slot(int tp, LoadContext *ctx);
HBlockVerbConjugation  load_CBlockVerbConjugation_slot(int tp, LoadContext *ctx);
HBlockVerb  load_CBlockVerb_slot(int tp, LoadContext *ctx);
HBlockVerbAdapt  load_CBlockVerbAdapt_slot(int tp, LoadContext *ctx);
HBlockVerbNegate  load_CBlockVerbNegate_slot(int tp, LoadContext *ctx);
HBlockSelector  load_CBlockSelector_slot(int tp, LoadContext *ctx);
HBlockSelector_All  load_CBlockSelector_All_slot(int tp, LoadContext *ctx);
HBlockSelector_Any  load_CBlockSelector_Any_slot(int tp, LoadContext *ctx);
HBlockSelector_Where  load_CBlockSelector_Where_slot(int tp, LoadContext *ctx);
HBlockAction  load_CBlockAction_slot(int tp, LoadContext *ctx);
HBlockActionInstance  load_CBlockActionInstance_slot(int tp, LoadContext *ctx);
HBlockActionNamed  load_CBlockActionNamed_slot(int tp, LoadContext *ctx);
HBlockActionNamed  load_CBlockActionNamed_slot(int tp, LoadContext *ctx);
HBlockTryCall  load_CBlockTryCall_slot(int tp, LoadContext *ctx);
HBlockActionCall  load_CBlockActionCall_slot(int tp, LoadContext *ctx);
HBlockActionCallNamed  load_CBlockActionCallNamed_slot(int tp, LoadContext *ctx);
HBlockStaticDispatch  load_CBlockStaticDispatch_slot(int tp, LoadContext *ctx);
HBlockAssertionBase  load_CBlockAssertionBase_slot(int tp, LoadContext *ctx);
HBlockAssertion_is  load_CBlockAssertion_is_slot(int tp, LoadContext *ctx);
HBlockAssertion_canBe  load_CBlockAssertion_canBe_slot(int tp, LoadContext *ctx);
HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf_slot(int tp, LoadContext *ctx);
HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf_slot(int tp, LoadContext *ctx);
HBlockAssertion_isVariable  load_CBlockAssertion_isVariable_slot(int tp, LoadContext *ctx);
HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable_slot(int tp, LoadContext *ctx);
HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign_slot(int tp, LoadContext *ctx);
HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign_slot(int tp, LoadContext *ctx);
HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign_slot(int tp, LoadContext *ctx);
HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign_slot(int tp, LoadContext *ctx);
HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign_slot(int tp, LoadContext *ctx);
HBlockIsVerb  load_CBlockIsVerb_slot(int tp, LoadContext *ctx);
HBlockIsNotVerb  load_CBlockIsNotVerb_slot(int tp, LoadContext *ctx);
HBlockMatchIsVerbComposition  load_CBlockMatchIsVerbComposition_slot(int tp, LoadContext *ctx); 
HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion_slot(int tp, LoadContext *ctx);
HBlockAssert  load_CBlockAssert_slot(int tp, LoadContext *ctx);
HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable_slot(int tp, LoadContext *ctx);
HBlockBooleanValue  load_CBlockBooleanValue_slot(int tp, LoadContext *ctx);
HBlockBooleanAND  load_CBlockBooleanAND_slot(int tp, LoadContext *ctx);
HBlockBooleanOR  load_CBlockBooleanOR_slot(int tp, LoadContext *ctx);
HBlockBooleanNOT  load_CBlockBooleanNOT_slot(int tp, LoadContext *ctx);
HBlockNow  load_CBlockNow_slot(int tp, LoadContext *ctx);
HBlockEvery  load_CBlockEvery_slot(int tp, LoadContext *ctx);
HBlockComandList  load_CBlockComandList_slot(int tp, LoadContext *ctx);
HBlockEventHandle  load_CBlockEventHandle_slot(int tp, LoadContext *ctx);
HBlockComposition  load_CBlockComposition_slot(int tp, LoadContext *ctx);
HBlockCompositionList  load_CBlockCompositionList_slot(int tp, LoadContext *ctx);
HBlockCompositionRelation  load_CBlockCompositionRelation_slot(int tp, LoadContext *ctx);
HBlockCompositionPhrase  load_CBlockCompositionPhrase_slot(int tp, LoadContext *ctx);
HBlockCompostionPhrase  load_CBlockCompostionPhrase_slot(int tp, LoadContext *ctx);
HBlockControlToken  load_CBlockControlToken_slot(int tp, LoadContext *ctx);
HBlockControlIF  load_CBlockControlIF_slot(int tp, LoadContext *ctx);
HBlockControlUnless  load_CBlockControlUnless_slot(int tp, LoadContext *ctx);
HBlockControlSelectItem  load_CBlockControlSelectItem_slot(int tp, LoadContext *ctx);
HBlockControlSelect  load_CBlockControlSelect_slot(int tp, LoadContext *ctx);
HBlockControlForEach  load_CBlockControlForEach_slot(int tp, LoadContext *ctx);
HBlockExecutionResultFlag  load_CBlockExecutionResultFlag_slot(int tp, LoadContext *ctx);
HBlockUnitInit  load_CBlockUnitInit_slot(int tp, LoadContext *ctx);
HBlockUnitTest  load_CBlockUnitTest_slot(int tp, LoadContext *ctx);
HBlockUnitAssert  load_CBlockUnitAssert_slot(int tp, LoadContext *ctx);
HBlockToDecide  load_CBlockToDecide_slot(int tp, LoadContext *ctx);
HBlockToDecideIf  load_CBlockToDecideIf_slot(int tp, LoadContext *ctx);
HBlockToDecideWhether  load_CBlockToDecideWhether_slot(int tp, LoadContext *ctx);
HBlockToDecideWhat  load_CBlockToDecideWhat_slot(int tp, LoadContext *ctx);
HBlockToDecideWhat_FirstNoum  load_CBlockToDecideWhat_FirstNoum_slot(int tp, LoadContext *ctx);
HBlockToDecideOn  load_CBlockToDecideOn_slot(int tp, LoadContext *ctx);
HBlockPhraseHeader  load_CBlockPhraseHeader_slot(int tp, LoadContext *ctx);
HBlockPhraseDefine  load_CBlockPhraseDefine_slot(int tp, LoadContext *ctx);
HBlockPhraseInvoke  load_CBlockPhraseInvoke_slot(int tp, LoadContext *ctx);
 
HBlockMatch  load_CBlockMatch_slot(int tp, LoadContext *ctx);
HBlockMatchAny  load_CBlockMatchAny_slot(int tp, LoadContext *ctx);
HBlockMatchNamed  load_CBlockMatchNamed_slot(int tp, LoadContext *ctx);
HBlockMatchNoum  load_CBlockMatchNoum_slot(int tp, LoadContext *ctx);
HBlockMatchValue  load_CBlockMatchValue_slot(int tp, LoadContext *ctx);
HBlockMatchKind  load_CBlockMatchKind_slot(int tp, LoadContext *ctx);
HBlockMatchWith  load_CBlockMatchWith_slot(int tp, LoadContext *ctx);
HBlockMatchList  load_CBlockMatchList_slot(int tp, LoadContext *ctx);
HBlockMatchAND  load_CBlockMatchAND_slot(int tp, LoadContext *ctx);
HBlockMatchNOT  load_CBlockMatchNOT_slot(int tp, LoadContext *ctx);
HBlockMatchOR  load_CBlockMatchOR_slot(int tp, LoadContext *ctx);
HBlockMatchActionCall  load_CBlockMatchActionCall_slot(int tp, LoadContext *ctx);
HBlockMatchBlock  load_CBlockMatchBlock_slot(int tp, LoadContext *ctx);
HBlockMatchIs  load_CBlockMatchIs_slot(int tp, LoadContext *ctx);
HBlockMatchDirectIs  load_CBlockMatchDirectIs_slot(int tp, LoadContext *ctx);
HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot_slot(int tp, LoadContext *ctx);
HBlockMatchIsVerb  load_CBlockMatchIsVerb_slot(int tp, LoadContext *ctx);
HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb_slot(int tp, LoadContext *ctx);
HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion_slot(int tp, LoadContext *ctx);
HBlockMatchProperty  load_CBlockMatchProperty_slot(int tp, LoadContext *ctx);
HBlockMatchWhich  load_CBlockMatchWhich_slot(int tp, LoadContext *ctx);
HBlockMatchWhichNot  load_CBlockMatchWhichNot_slot(int tp, LoadContext *ctx);
HBlockVariableNamed  load_CBlockVariableNamed_slot(int tp, LoadContext *ctx);
HBlockNumber  load_CBlockNumber_slot(int tp, LoadContext *ctx);
HBlockIntegerNumber  load_CBlockIntegerNumber_slot(int tp, LoadContext *ctx);
HBlockFactionalNumber  load_CBlockFactionalNumber_slot(int tp, LoadContext *ctx);
HBlockArgumentInput  load_CBlockArgumentInput_slot(int tp, LoadContext *ctx);
HBlockRelationBase  load_CBlockRelationBase_slot(int tp, LoadContext *ctx);
HBlockSimetricRelation  load_CBlockSimetricRelation_slot(int tp, LoadContext *ctx);
HBlockASimetricRelation  load_CBlockASimetricRelation_slot(int tp, LoadContext *ctx);
HBlockRelationInstance  load_CBlockRelationInstance_slot(int tp, LoadContext *ctx);
HBlockConditionalRelation  load_CBlockConditionalRelation_slot(int tp, LoadContext *ctx);
HBlockRelationLookup  load_CBlockRelationLookup_slot(int tp, LoadContext *ctx);
HBlockVerbLookup  load_CBlockVerbLookup_slot(int tp, LoadContext *ctx);
HBlockRelationArguments  load_CBlockRelationArguments_slot(int tp, LoadContext *ctx);
HBlockSelectorAND  load_CBlockSelectorAND_slot(int tp, LoadContext *ctx);
HBlockExecution  load_CBlockExecution_slot(int tp, LoadContext *ctx);
HBlockUnderstand  load_CBlockUnderstand_slot(int tp, LoadContext *ctx);
HBlockUnderstandStatic  load_CBlockUnderstandStatic_slot(int tp, LoadContext *ctx);
HBlockUnderstandDynamic  load_CBlockUnderstandDynamic_slot(int tp, LoadContext *ctx);
HBlockVerbRelation  load_CBlockVerbRelation_slot(int tp, LoadContext *ctx);
HBlockCollection  load_CBlockCollection_slot(int tp, LoadContext *ctx);
HBlockMatch  load_CBlockMatch_slot(int tp, LoadContext *ctx);
HBlockAssertionBase  load_CBlockAssertionBase_slot(int tp, LoadContext *ctx);
HBlock  load_CBlock_slot(int tp, LoadContext *ctx);
HBlockAction  load_CBlockAction_slot(int tp, LoadContext *ctx);
HBlockAssertion_is  load_CBlockAssertion_is_slot(int tp, LoadContext *ctx);
HBlockActionCall  load_CBlockActionCall_slot(int tp, LoadContext *ctx);
HBlockKind  load_CBlockKind_slot(int tp, LoadContext *ctx);
HBlockSelector  load_CBlockSelector_slot(int tp, LoadContext *ctx);
HBlockNumber  load_CBlockNumber_slot(int tp, LoadContext *ctx);
HBlockToDecide  load_CBlockToDecide_slot(int tp, LoadContext *ctx);
HBlockRelationBase  load_CBlockRelationBase_slot(int tp, LoadContext *ctx);
HBlockInstance  load_CBlockInstance_slot(int tp, LoadContext *ctx);
HBlockValue  load_CBlockValue_slot(int tp, LoadContext *ctx);
HBlockFilter  load_CBlockFilter_slot(int tp, LoadContext *ctx);
HBlockBooleanResult  load_CBlockBooleanResult_slot(int tp, LoadContext *ctx);
HBlockComposition  load_CBlockComposition_slot(int tp, LoadContext *ctx);
HBlockMatchIs  load_CBlockMatchIs_slot(int tp, LoadContext *ctx);
HBlockNoum  load_CBlockNoum_slot(int tp, LoadContext *ctx);
HBlockVerbRelation  load_CBlockVerbRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbRelation(load_CBlock_slot(slot, ctx));
}

HBlockVerbRelation  load_CBlockVerbRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockVerbDirectRelation) return load_CBlockVerbDirectRelation(tp, ctx);
	if (tp == BlockType::BlockVerbReverseRelation) return load_CBlockVerbReverseRelation(tp, ctx);
	return nullptr;
}

HBlockCollection  load_CBlockCollection_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockCollection(load_CBlock_slot(slot, ctx));
}

HBlockCollection  load_CBlockCollection(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockList) return load_CBlockList(tp, ctx);
	if (tp == BlockType::BlockList_OR) return load_CBlockList_OR(tp, ctx);
	if (tp == BlockType::BlockList_AND) return load_CBlockList_AND(tp, ctx);
	return nullptr;
}

HBlockMatch  load_CBlockMatch_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatch(load_CBlock_slot(slot, ctx));
}

HBlockMatch  load_CBlockMatch(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockMatchAny) return load_CBlockMatchAny(tp, ctx);
	if (tp == BlockType::BlockMatchNamed) return load_CBlockMatchNamed(tp, ctx);
	if (tp == BlockType::BlockMatchNoum) return load_CBlockMatchNoum(tp, ctx);
	if (tp == BlockType::BlockMatchText) return load_CBlockMatchText(tp, ctx);
	if (tp == BlockType::BlockMatchValue) return load_CBlockMatchValue(tp, ctx);
	if (tp == BlockType::BlockMatchKind) return load_CBlockMatchKind(tp, ctx);
	{ auto x = load_CBlockMatchWith(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockMatchList) return load_CBlockMatchList(tp, ctx);
	if (tp == BlockType::BlockMatchAND) return load_CBlockMatchAND(tp, ctx);
	if (tp == BlockType::BlockMatchNOT) return load_CBlockMatchNOT(tp, ctx);
	if (tp == BlockType::BlockMatchOR) return load_CBlockMatchOR(tp, ctx);
	if (tp == BlockType::BlockMatchActionCall) return load_CBlockMatchActionCall(tp, ctx);
	if (tp == BlockType::BlockMatchBlock) return load_CBlockMatchBlock(tp, ctx);
	{ auto x = load_CBlockMatchIs(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockMatchProperty) return load_CBlockMatchProperty(tp, ctx);
	return nullptr;
}

HBlockAssertionBase  load_CBlockAssertionBase_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertionBase(load_CBlock_slot(slot, ctx));
}

HBlockAssertionBase  load_CBlockAssertionBase(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	{ auto x = load_CBlockAssertion_is(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockAssertion_canBe) return load_CBlockAssertion_canBe(tp, ctx);
	return nullptr;
}

 

HBlock  load_CBlock(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	{ auto x = load_CBlockInstance(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockText) return load_CBlockText(tp, ctx);
	if (tp == BlockType::BlockTextSentence) return load_CBlockTextSentence(tp, ctx);
	{ auto x = load_CBlockKind(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockValue(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockNoum(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockNothing) return load_CBlockNothing(tp, ctx);
	if (tp == BlockType::BlockAnything) return load_CBlockAnything(tp, ctx);
	if (tp == BlockType::BlockKindOfName) return load_CBlockKindOfName(tp, ctx);
	if (tp == BlockType::BlockKindOf) return load_CBlockKindOf(tp, ctx);
	if (tp == BlockType::BlockActionApply) return load_CBlockActionApply(tp, ctx);
	if (tp == BlockType::BlockProperty) return load_CBlockProperty(tp, ctx);
	if (tp == BlockType::BlockInstanceVariable) return load_CBlockInstanceVariable(tp, ctx);
	if (tp == BlockType::BlockKind_InstanceVariable) return load_CBlockKind_InstanceVariable(tp, ctx);
	{ auto x = load_CBlockCollection(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockEnums) return load_CBlockEnums(tp, ctx);
	{ auto x = load_CBlockVerbRelation(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockFilter(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockDinamicDispatch) return load_CBlockDinamicDispatch(tp, ctx);
	{ auto x = load_CBlockIF(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockVerbConjugation) return load_CBlockVerbConjugation(tp, ctx);
	if (tp == BlockType::BlockVerb) return load_CBlockVerb(tp, ctx);
	if (tp == BlockType::BlockVerbAdapt) return load_CBlockVerbAdapt(tp, ctx);
	if (tp == BlockType::BlockVerbNegate) return load_CBlockVerbNegate(tp, ctx);
	{ auto x = load_CBlockSelector(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockAction(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockTryCall) return load_CBlockTryCall(tp, ctx);
	{ auto x = load_CBlockActionCall(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockAssertionBase(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockAssert) return load_CBlockAssert(tp, ctx);
	if (tp == BlockType::BlockAssertion_InstanceVariable) return load_CBlockAssertion_InstanceVariable(tp, ctx);
	if (tp == BlockType::BlockBooleanAND) return load_CBlockBooleanAND(tp, ctx);
	if (tp == BlockType::BlockBooleanOR) return load_CBlockBooleanOR(tp, ctx);
	if (tp == BlockType::BlockBooleanNOT) return load_CBlockBooleanNOT(tp, ctx);
	if (tp == BlockType::BlockNow) return load_CBlockNow(tp, ctx);
	if (tp == BlockType::BlockEvery) return load_CBlockEvery(tp, ctx);
	if (tp == BlockType::BlockComandList) return load_CBlockComandList(tp, ctx);
	if (tp == BlockType::BlockEventHandle) return load_CBlockEventHandle(tp, ctx);
	if (tp == BlockType::BlockCompostionPhrase) return load_CBlockCompostionPhrase(tp, ctx);
	if (tp == BlockType::BlockControlToken) return load_CBlockControlToken(tp, ctx);
	if (tp == BlockType::BlockControlIF) return load_CBlockControlIF(tp, ctx);
	if (tp == BlockType::BlockControlUnless) return load_CBlockControlUnless(tp, ctx);
	if (tp == BlockType::BlockControlSelectItem) return load_CBlockControlSelectItem(tp, ctx);
	if (tp == BlockType::BlockControlSelect) return load_CBlockControlSelect(tp, ctx);
	if (tp == BlockType::BlockControlForEach) return load_CBlockControlForEach(tp, ctx);
	if (tp == BlockType::BlockExecutionResultFlag) return load_CBlockExecutionResultFlag(tp, ctx);
	if (tp == BlockType::BlockUnitInit) return load_CBlockUnitInit(tp, ctx);
	if (tp == BlockType::BlockUnitTest) return load_CBlockUnitTest(tp, ctx);
	if (tp == BlockType::BlockUnitAssert) return load_CBlockUnitAssert(tp, ctx);
	{ auto x = load_CBlockToDecide(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockToDecideOn) return load_CBlockToDecideOn(tp, ctx);
	if (tp == BlockType::BlockPhraseHeader) return load_CBlockPhraseHeader(tp, ctx);
	if (tp == BlockType::BlockPhraseDefine) return load_CBlockPhraseDefine(tp, ctx);
	if (tp == BlockType::BlockPhraseInvoke) return load_CBlockPhraseInvoke(tp, ctx);
	{ auto x = load_CBlockMatch(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockArgumentInput) return load_CBlockArgumentInput(tp, ctx);
	{ auto x = load_CBlockRelationBase(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockRelationInstance) return load_CBlockRelationInstance(tp, ctx);
	if (tp == BlockType::BlockRelationLookup) return load_CBlockRelationLookup(tp, ctx);
	if (tp == BlockType::BlockVerbLookup) return load_CBlockVerbLookup(tp, ctx);
	if (tp == BlockType::BlockRelationArguments) return load_CBlockRelationArguments(tp, ctx);
	if (tp == BlockType::BlockSelectorAND) return load_CBlockSelectorAND(tp, ctx);
	{ auto x = load_CBlockUnderstand(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockUnderstandStatic) return load_CBlockUnderstandStatic(tp, ctx);
	if (tp == BlockType::BlockUnderstandDynamic) return load_CBlockUnderstandDynamic(tp, ctx);
	{auto x = load_CBlockComposition(tp, ctx); if (x != nullptr) return x; }
	 
	if (tp == BlockType::BlockBody) return load_CBlockBody(tp, ctx);

	return nullptr;
}

HBlockAction  load_CBlockAction_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAction(load_CBlock_slot(slot, ctx));
}

HBlockAction  load_CBlockAction(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockActionInstance) return load_CBlockActionInstance(tp, ctx);
	if (tp == BlockType::BlockActionNamed) return load_CBlockActionNamed(tp, ctx);
	return nullptr;
}

HBlockAssertion_is  load_CBlockAssertion_is_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_is(load_CBlock_slot(slot, ctx));
}

HBlockAssertion_is  load_CBlockAssertion_is(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockAssertion_isInstanceOf) return load_CBlockAssertion_isInstanceOf(tp, ctx);
	if (tp == BlockType::BlockAssertion_isNamedValueOf) return load_CBlockAssertion_isNamedValueOf(tp, ctx);
	if (tp == BlockType::BlockAssertion_isVariable) return load_CBlockAssertion_isVariable(tp, ctx);
	if (tp == BlockType::BlockAssertion_isLocalVariable) return load_CBlockAssertion_isLocalVariable(tp, ctx);
	if (tp == BlockType::BlockAssertion_isDefaultAssign) return load_CBlockAssertion_isDefaultAssign(tp, ctx);
	if (tp == BlockType::BlockAssertion_isConstantAssign) return load_CBlockAssertion_isConstantAssign(tp, ctx);
	if (tp == BlockType::BlockAssertion_isForbiddenAssign) return load_CBlockAssertion_isForbiddenAssign(tp, ctx);
	if (tp == BlockType::BlockAssertion_isDirectAssign) return load_CBlockAssertion_isDirectAssign(tp, ctx);
	if (tp == BlockType::BlockAssertion_isNotDirectAssign) return load_CBlockAssertion_isNotDirectAssign(tp, ctx);
	if (tp == BlockType::BlockIsVerb) return load_CBlockIsVerb(tp, ctx);
	if (tp == BlockType::BlockIsNotVerb) return load_CBlockIsNotVerb(tp, ctx);	 
	if (tp == BlockType::BlockIsAdverbialComparasion) return load_CBlockIsAdverbialComparasion(tp, ctx);
	return nullptr;
}

HBlockActionCall  load_CBlockActionCall_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockActionCall(load_CBlock_slot(slot, ctx));
}

HBlockActionCall  load_CBlockActionCall(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockActionCallNamed) return load_CBlockActionCallNamed(tp, ctx);
	if (tp == BlockType::BlockStaticDispatch) return load_CBlockStaticDispatch(tp, ctx);
	return nullptr;
}

HBlockKind  load_CBlockKind_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKind(load_CBlock_slot(slot, ctx));
}

HBlockKind  load_CBlockKind(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockKindNamed) return load_CBlockKindNamed(tp, ctx);
	if (tp == BlockType::BlockKindAction) return load_CBlockKindAction(tp, ctx);
	if (tp == BlockType::BlockKindValue) return load_CBlockKindValue(tp, ctx);
	if (tp == BlockType::BlockKindEntity) return load_CBlockKindEntity(tp, ctx);
	{auto x = load_CBlockComposition(tp, ctx);  if (x != nullptr) return x; }
	return nullptr;
}

HBlockSelector  load_CBlockSelector_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSelector(load_CBlock_slot(slot, ctx));
}

HBlockSelector  load_CBlockSelector(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockSelector_All) return load_CBlockSelector_All(tp, ctx);
	if (tp == BlockType::BlockSelector_Any) return load_CBlockSelector_Any(tp, ctx);
	if (tp == BlockType::BlockSelector_Where) return load_CBlockSelector_Where(tp, ctx);
	return nullptr;
}

HBlockNumber  load_CBlockNumber_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNumber(load_CBlock_slot(slot, ctx));
}

HBlockNumber  load_CBlockNumber(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockIntegerNumber) return load_CBlockIntegerNumber(tp, ctx);
	if (tp == BlockType::BlockFactionalNumber) return load_CBlockFactionalNumber(tp, ctx);
	return nullptr;
}

HBlockToDecide  load_CBlockToDecide_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecide(load_CBlock_slot(slot, ctx));
}

HBlockToDecide  load_CBlockToDecide(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockToDecideIf) return load_CBlockToDecideIf(tp, ctx);
	if (tp == BlockType::BlockToDecideWhether) return load_CBlockToDecideWhether(tp, ctx);
	if (tp == BlockType::BlockToDecideWhat) return load_CBlockToDecideWhat(tp, ctx);
	if (tp == BlockType::BlockToDecideWhat_FirstNoum) return load_CBlockToDecideWhat_FirstNoum(tp, ctx);
	return nullptr;
}

HBlockRelationBase  load_CBlockRelationBase_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockRelationBase(load_CBlock_slot(slot, ctx));
}

HBlockRelationBase  load_CBlockRelationBase(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockSimetricRelation) return load_CBlockSimetricRelation(tp, ctx);
	if (tp == BlockType::BlockASimetricRelation) return load_CBlockASimetricRelation(tp, ctx);
	if (tp == BlockType::BlockConditionalRelation) return load_CBlockConditionalRelation(tp, ctx);
	return nullptr;
}

HBlockInstance  load_CBlockInstance_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockInstance(load_CBlock_slot(slot, ctx));
}

HBlockInstance  load_CBlockInstance(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockInstanceAnonymous) return load_CBlockInstanceAnonymous(tp, ctx);
	if (tp == BlockType::BlockInstanceNamed) return load_CBlockInstanceNamed(tp, ctx);
	return nullptr;
}

HBlockValue  load_CBlockValue_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockValue(load_CBlock_slot(slot, ctx));
}

HBlockValue  load_CBlockValue(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockKindReference) return load_CBlockKindReference(tp, ctx);
	{ auto x = load_CBlockBooleanResult(tp, ctx); if (x != nullptr) return x; };
	if (tp == BlockType::BlockNamedValue) return load_CBlockNamedValue(tp, ctx);
	if (tp == BlockType::BlockBooleanValue) return load_CBlockBooleanValue(tp, ctx);
	{ auto x = load_CBlockNumber(tp, ctx); if (x != nullptr) return x; };
	return nullptr;
}

HBlockFilter  load_CBlockFilter_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockFilter(load_CBlock_slot(slot, ctx));
}

HBlockFilter  load_CBlockFilter(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	{ auto x = load_CBlockFilterAtom(tp, ctx); if (x != nullptr) return x; };
	{ auto x = load_CBlockFilterList(tp, ctx); if (x != nullptr) return x; };
	return nullptr;
}

HBlockBooleanResult  load_CBlockBooleanResult_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockBooleanResult(load_CBlock_slot(slot, ctx));
}

HBlockBooleanResult  load_CBlockBooleanResult(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	{ auto x = load_CBlockSame(tp, ctx); if (x != nullptr) return x; };
	return nullptr;
}

HBlockComposition  load_CBlockComposition_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockComposition(load_CBlock_slot(slot, ctx));
}

HBlockComposition  load_CBlockComposition(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockCompositionList) return load_CBlockCompositionList(tp, ctx);
	if (tp == BlockType::BlockCompositionRelation) return load_CBlockCompositionRelation(tp, ctx);
	if (tp == BlockType::BlockCompositionPhrase) return load_CBlockCompositionPhrase(tp, ctx);
	if (tp == BlockType::BlockCompositionRulebook) return load_CBlockCompositionRulebook(tp, ctx);
	return nullptr;
}

HBlockMatchIs  load_CBlockMatchIs_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchIs(load_CBlock_slot(slot, ctx));
}

HBlockMatchIs  load_CBlockMatchIs(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockMatchDirectIs) return load_CBlockMatchDirectIs(tp, ctx);
	if (tp == BlockType::BlockMatchDirectIsNot) return load_CBlockMatchDirectIsNot(tp, ctx);
	if (tp == BlockType::BlockMatchIsVerb) return load_CBlockMatchIsVerb(tp, ctx);
	if (tp == BlockType::BlockMatchIsNotVerb) return load_CBlockMatchIsNotVerb(tp, ctx);
	if (tp == BlockType::BlockMatchIsVerbComposition) return load_CBlockMatchIsVerbComposition(tp, ctx);
	if (tp == BlockType::BlockMatchIsAdverbialComparasion) return load_CBlockMatchIsAdverbialComparasion(tp, ctx);
	if (tp == BlockType::BlockMatchWhich) return load_CBlockMatchWhich(tp, ctx);
	if (tp == BlockType::BlockMatchWhichNot) return load_CBlockMatchWhichNot(tp, ctx);
	return nullptr;
}

HBlockNoum  load_CBlockNoum_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNoum(load_CBlock_slot(slot, ctx));
}

HBlockNoum  load_CBlockNoum(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	if (tp == BlockType::BlockNoumStr) return load_CBlockNoumStr(tp, ctx);
	if (tp == BlockType::BlockNoumStrDet) return load_CBlockNoumStrDet(tp, ctx);
	if (tp == BlockType::BlockNoumSupl) return load_CBlockNoumSupl(tp, ctx);
	if (tp == BlockType::BlockNoumCompose) return load_CBlockNoumCompose(tp, ctx);
	 
	return nullptr;
}

// BASE CBlockVerbRelation
HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isForbiddenAssign(load_CBlock_slot(slot, ctx));

}


HBlockControlSelectItem  load_CBlockControlSelectItem_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlSelectItem(load_CBlock_slot(slot, ctx));

}


HBlockMatchAND  load_CBlockMatchAND_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchAND(load_CBlock_slot(slot, ctx));

}


HBlockToDecideWhat_FirstNoum  load_CBlockToDecideWhat_FirstNoum_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecideWhat_FirstNoum(load_CBlock_slot(slot, ctx));

}


HBlockMatchOR  load_CBlockMatchOR_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchOR(load_CBlock_slot(slot, ctx));

}


HBlockToDecideWhat  load_CBlockToDecideWhat_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecideWhat(load_CBlock_slot(slot, ctx));

}


HBlockCompositionPhrase  load_CBlockCompositionPhrase_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockCompositionPhrase(load_CBlock_slot(slot, ctx));

}


HBlockMatchBlock  load_CBlockMatchBlock_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchBlock(load_CBlock_slot(slot, ctx));

}


HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchIsAdverbialComparasion(load_CBlock_slot(slot, ctx));

}


HBlockVerbReverseRelation  load_CBlockVerbReverseRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbReverseRelation(load_CBlock_slot(slot, ctx));

}


HBlockNamedValue  load_CBlockNamedValue_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNamedValue(load_CBlock_slot(slot, ctx));

}


HBlockCompostionPhrase  load_CBlockCompostionPhrase_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockCompostionPhrase(load_CBlock_slot(slot, ctx));

}


HBlockTryCall  load_CBlockTryCall_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockTryCall(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isLocalVariable(load_CBlock_slot(slot, ctx));

}


HBlockInstanceNamed  load_CBlockInstanceNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockInstanceNamed(load_CBlock_slot(slot, ctx));

}


// BASE CBlockNumber
HBlockExecution  load_CBlockExecution_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockExecution(load_CBlock_slot(slot, ctx));

}


HBlockArgumentInput  load_CBlockArgumentInput_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockArgumentInput(load_CBlock_slot(slot, ctx));

}


HBlockList_OR  load_CBlockList_OR_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockList_OR(load_CBlock_slot(slot, ctx));

}


HBlockPhraseInvoke  load_CBlockPhraseInvoke_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockPhraseInvoke(load_CBlock_slot(slot, ctx));

}


HBlockVerbDirectRelation  load_CBlockVerbDirectRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbDirectRelation(load_CBlock_slot(slot, ctx));

}


// BASE CBlockCollection
// BASE CBlockNoum
HBlockPhraseDefine  load_CBlockPhraseDefine_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockPhraseDefine(load_CBlock_slot(slot, ctx));

}


HBlockVerbConjugation  load_CBlockVerbConjugation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbConjugation(load_CBlock_slot(slot, ctx));

}


HBlockProperty  load_CBlockProperty_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockProperty(load_CBlock_slot(slot, ctx));

}


HBlockSimetricRelation  load_CBlockSimetricRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSimetricRelation(load_CBlock_slot(slot, ctx));

}


HBlockList_AND  load_CBlockList_AND_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockList_AND(load_CBlock_slot(slot, ctx));

}


HBlockSame  load_CBlockSame_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSame(load_CBlock_slot(slot, ctx));

}


HBlockMatchNamed  load_CBlockMatchNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchNamed(load_CBlock_slot(slot, ctx));

}


HBlockMatchIsVerb  load_CBlockMatchIsVerb_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchIsVerb(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isNotDirectAssign(load_CBlock_slot(slot, ctx));

}


HBlockVerbAdapt  load_CBlockVerbAdapt_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbAdapt(load_CBlock_slot(slot, ctx));

}


HBlockFilterAtom  load_CBlockFilterAtom_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockFilterAtom(load_CBlock_slot(slot, ctx));

}


// BASE CBlockMatchIs
HBlockSelector_Any  load_CBlockSelector_Any_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSelector_Any(load_CBlock_slot(slot, ctx));

}


HBlockKindOfName  load_CBlockKindOfName_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindOfName(load_CBlock_slot(slot, ctx));

}


HBlockUnderstandDynamic  load_CBlockUnderstandDynamic_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnderstandDynamic(load_CBlock_slot(slot, ctx));

}


HBlockFilterList  load_CBlockFilterList_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockFilterList(load_CBlock_slot(slot, ctx));

}


HBlockControlToken  load_CBlockControlToken_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlToken(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_InstanceVariable(load_CBlock_slot(slot, ctx));

}


HBlockVerbLookup  load_CBlockVerbLookup_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbLookup(load_CBlock_slot(slot, ctx));

}


HBlockSelector_All  load_CBlockSelector_All_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSelector_All(load_CBlock_slot(slot, ctx));

}


HBlockKindAction  load_CBlockKindAction_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindAction(load_CBlock_slot(slot, ctx));

}


HBlockControlSelect  load_CBlockControlSelect_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlSelect(load_CBlock_slot(slot, ctx));

}


// BASE CBlockValue
HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isInstanceOf(load_CBlock_slot(slot, ctx));

}


 

HBlockControlIF  load_CBlockControlIF_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlIF(load_CBlock_slot(slot, ctx));

}


HBlockActionNamed  load_CBlockActionNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockActionNamed(load_CBlock_slot(slot, ctx));

}


HBlockMatchNOT  load_CBlockMatchNOT_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchNOT(load_CBlock_slot(slot, ctx));

}


HBlockRelationInstance  load_CBlockRelationInstance_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockRelationInstance(load_CBlock_slot(slot, ctx));

}


HBlockVariableNamed  load_CBlockVariableNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVariableNamed(load_CBlock_slot(slot, ctx));

}


HBlockNothing  load_CBlockNothing_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNothing(load_CBlock_slot(slot, ctx));

}


HBlockMatchDirectIs  load_CBlockMatchDirectIs_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchDirectIs(load_CBlock_slot(slot, ctx));

}


HBlockMatchAny  load_CBlockMatchAny_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchAny(load_CBlock_slot(slot, ctx));

}


HBlockRelationArguments  load_CBlockRelationArguments_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockRelationArguments(load_CBlock_slot(slot, ctx));

}


HBlockIF  load_CBlockIF_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockIF(load_CBlock_slot(slot, ctx));

}


HBlockStaticDispatch  load_CBlockStaticDispatch_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockStaticDispatch(load_CBlock_slot(slot, ctx));

}


HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockIsAdverbialComparasion(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isDefaultAssign(load_CBlock_slot(slot, ctx));

}


HBlockRelationLookup  load_CBlockRelationLookup_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockRelationLookup(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isVariable  load_CBlockAssertion_isVariable_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isVariable(load_CBlock_slot(slot, ctx));

}


HBlockMatchNoum  load_CBlockMatchNoum_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchNoum(load_CBlock_slot(slot, ctx));

}


HBlockKindValue  load_CBlockKindValue_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindValue(load_CBlock_slot(slot, ctx));

}


HBlockEventHandle  load_CBlockEventHandle_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockEventHandle(load_CBlock_slot(slot, ctx));

}


HBlockMatchWhich  load_CBlockMatchWhich_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchWhich(load_CBlock_slot(slot, ctx));

}


HBlockAnything  load_CBlockAnything_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAnything(load_CBlock_slot(slot, ctx));

}


HBlockUnitTest  load_CBlockUnitTest_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnitTest(load_CBlock_slot(slot, ctx));

}


HBlockTextSentence  load_CBlockTextSentence_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockTextSentence(load_CBlock_slot(slot, ctx));

}


HBlockAssert  load_CBlockAssert_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssert(load_CBlock_slot(slot, ctx));

}


HBlockKindOf  load_CBlockKindOf_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindOf(load_CBlock_slot(slot, ctx));

}


// BASE CBlockSelector
HBlockEnums  load_CBlockEnums_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockEnums(load_CBlock_slot(slot, ctx));

}


HBlockMatchKind  load_CBlockMatchKind_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchKind(load_CBlock_slot(slot, ctx));

}


HBlockMatchValue  load_CBlockMatchValue_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchValue(load_CBlock_slot(slot, ctx));

}


HBlockText  load_CBlockText_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockText(load_CBlock_slot(slot, ctx));

}


HBlockUnitAssert  load_CBlockUnitAssert_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnitAssert(load_CBlock_slot(slot, ctx));

}


// BASE CBlockInstance
HBlockUnderstandStatic  load_CBlockUnderstandStatic_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnderstandStatic(load_CBlock_slot(slot, ctx));

}


HBlockMatchActionCall  load_CBlockMatchActionCall_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchActionCall(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_canBe  load_CBlockAssertion_canBe_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_canBe(load_CBlock_slot(slot, ctx));

}


HBlockExecutionResultFlag  load_CBlockExecutionResultFlag_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockExecutionResultFlag(load_CBlock_slot(slot, ctx));

}


HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchDirectIsNot(load_CBlock_slot(slot, ctx));

}


HBlockMatchWhichNot  load_CBlockMatchWhichNot_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchWhichNot(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isNamedValueOf(load_CBlock_slot(slot, ctx));

}


HBlockNow  load_CBlockNow_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNow(load_CBlock_slot(slot, ctx));

}


// BASE CBlockAssertionBase
HBlockBooleanAND  load_CBlockBooleanAND_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockBooleanAND(load_CBlock_slot(slot, ctx));

}


// BASE CBlockAssertion_is
// BASE CBlockComposition
HBlockControlForEach  load_CBlockControlForEach_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlForEach(load_CBlock_slot(slot, ctx));

}


// BASE CBlockToDecide
HBlockNoumStr  load_CBlockNoumStr_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNoumStr(load_CBlock_slot(slot, ctx));

}


HBlockBooleanValue  load_CBlockBooleanValue_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockBooleanValue(load_CBlock_slot(slot, ctx));

}


HBlockPhraseHeader  load_CBlockPhraseHeader_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockPhraseHeader(load_CBlock_slot(slot, ctx));

}


HBlockUnitInit  load_CBlockUnitInit_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnitInit(load_CBlock_slot(slot, ctx));

}


HBlockBooleanOR  load_CBlockBooleanOR_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockBooleanOR(load_CBlock_slot(slot, ctx));

}


HBlockVerb  load_CBlockVerb_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerb(load_CBlock_slot(slot, ctx));

}


HBlockIntegerNumber  load_CBlockIntegerNumber_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockIntegerNumber(load_CBlock_slot(slot, ctx));

}


HBlockMatchList  load_CBlockMatchList_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchList(load_CBlock_slot(slot, ctx));

}


HBlockVerbNegate  load_CBlockVerbNegate_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockVerbNegate(load_CBlock_slot(slot, ctx));

}


HBlockActionInstance  load_CBlockActionInstance_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockActionInstance(load_CBlock_slot(slot, ctx));

}


HBlockMatchProperty  load_CBlockMatchProperty_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchProperty(load_CBlock_slot(slot, ctx));

}


HBlockCompositionRelation  load_CBlockCompositionRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockCompositionRelation(load_CBlock_slot(slot, ctx));

}


HBlockInstanceAnonymous  load_CBlockInstanceAnonymous_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockInstanceAnonymous(load_CBlock_slot(slot, ctx));

}


HBlockToDecideOn  load_CBlockToDecideOn_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecideOn(load_CBlock_slot(slot, ctx));

}


HBlockKindReference  load_CBlockKindReference_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindReference(load_CBlock_slot(slot, ctx));

}


HBlockComandList  load_CBlockComandList_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockComandList(load_CBlock_slot(slot, ctx));

}


HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchIsNotVerb(load_CBlock_slot(slot, ctx));

}


HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKind_InstanceVariable(load_CBlock_slot(slot, ctx));

}


// BASE CBlockMatch
HBlockASimetricRelation  load_CBlockASimetricRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockASimetricRelation(load_CBlock_slot(slot, ctx));

}


HBlockToDecideIf  load_CBlockToDecideIf_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecideIf(load_CBlock_slot(slot, ctx));

}


HBlockFactionalNumber  load_CBlockFactionalNumber_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockFactionalNumber(load_CBlock_slot(slot, ctx));

}


HBlockCompositionList  load_CBlockCompositionList_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockCompositionList(load_CBlock_slot(slot, ctx));

}


HBlockSelector_Where  load_CBlockSelector_Where_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSelector_Where(load_CBlock_slot(slot, ctx));

}


HBlockIsNotVerb  load_CBlockIsNotVerb_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockIsNotVerb(load_CBlock_slot(slot, ctx));

}

HBlockMatchIsVerbComposition load_CBlockMatchIsVerbComposition_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchIsVerbComposition(load_CBlock_slot(slot, ctx));

}

HBlockToDecideWhether  load_CBlockToDecideWhether_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockToDecideWhether(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isConstantAssign(load_CBlock_slot(slot, ctx));

}


HBlockEvery  load_CBlockEvery_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockEvery(load_CBlock_slot(slot, ctx));

}


HBlockActionApply  load_CBlockActionApply_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockActionApply(load_CBlock_slot(slot, ctx));

}


HBlockConditionalRelation  load_CBlockConditionalRelation_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockConditionalRelation(load_CBlock_slot(slot, ctx));

}


HBlockControlUnless  load_CBlockControlUnless_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockControlUnless(load_CBlock_slot(slot, ctx));

}


HBlockDinamicDispatch  load_CBlockDinamicDispatch_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockDinamicDispatch(load_CBlock_slot(slot, ctx));

}


HBlockMatchWith  load_CBlockMatchWith_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockMatchWith(load_CBlock_slot(slot, ctx));

}


// BASE CBlockRelationBase
HBlockSelectorAND  load_CBlockSelectorAND_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockSelectorAND(load_CBlock_slot(slot, ctx));

}


HBlockNoumSupl  load_CBlockNoumSupl_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockNoumSupl(load_CBlock_slot(slot, ctx));

}


HBlockBooleanNOT  load_CBlockBooleanNOT_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockBooleanNOT(load_CBlock_slot(slot, ctx));

}


HBlockInstanceVariable  load_CBlockInstanceVariable_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockInstanceVariable(load_CBlock_slot(slot, ctx));

}


// BASE CBlockAction
HBlockIsVerb  load_CBlockIsVerb_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockIsVerb(load_CBlock_slot(slot, ctx));

}


HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockAssertion_isDirectAssign(load_CBlock_slot(slot, ctx));

}


// BASE CBlockActionCall
HBlockKindEntity  load_CBlockKindEntity_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindEntity(load_CBlock_slot(slot, ctx));

}


HBlockActionCallNamed  load_CBlockActionCallNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockActionCallNamed(load_CBlock_slot(slot, ctx));

}


HBlockUnderstand  load_CBlockUnderstand_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockUnderstand(load_CBlock_slot(slot, ctx));

}


HBlockKindNamed  load_CBlockKindNamed_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockKindNamed(load_CBlock_slot(slot, ctx));

}


HBlockList  load_CBlockList_slot(int slot, LoadContext *ctx)
{
	return DynamicCasting::asHBlockList(load_CBlock_slot(slot, ctx));

}


// BASE CBlockVerbRelation
HBlockAssertion_isForbiddenAssign  load_CBlockAssertion_isForbiddenAssign(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isForbiddenAssign);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isForbiddenAssign* ret = new CBlockAssertion_isForbiddenAssign(_variable, _value);
	return  std::shared_ptr<CBlockAssertion_isForbiddenAssign>(ret);

}


HBlockControlSelectItem  load_CBlockControlSelectItem(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlSelectItem);
	const HBlock _block_seletor = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_execute = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlSelectItem* ret = new CBlockControlSelectItem(_block_seletor, _block_execute);
	return  std::shared_ptr<CBlockControlSelectItem>(ret);

}


HBlockMatchAND  load_CBlockMatchAND(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchAND);
	const std::list<HBlockMatch> _matchList = load_list<CBlockMatch>(ctx);
	CBlockMatchAND* ret = new CBlockMatchAND(_matchList);
	return  std::shared_ptr<CBlockMatchAND>(ret);

}


HBlockToDecideWhat_FirstNoum  load_CBlockToDecideWhat_FirstNoum(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockToDecideWhat_FirstNoum);
	const HBlockMatchIs _queryToMatch = load_CBlockMatchIs_slot(load_id(ctx), ctx);
	const HBlock _decideBody = load_CBlock_slot(load_id(ctx), ctx);
	CBlockToDecideWhat_FirstNoum* ret = new CBlockToDecideWhat_FirstNoum(_queryToMatch, _decideBody);
	return  std::shared_ptr<CBlockToDecideWhat_FirstNoum>(ret);

}


HBlockMatchOR  load_CBlockMatchOR(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchOR);
	const std::list<HBlockMatch> _matchList = load_list<CBlockMatch>(ctx);
	CBlockMatchOR* ret = new CBlockMatchOR(_matchList);
	return  std::shared_ptr<CBlockMatchOR>(ret);

}


HBlockToDecideWhat  load_CBlockToDecideWhat(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockToDecideWhat);
	const HBlockMatch _queryToMatch = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlock _decideBody = load_CBlock_slot(load_id(ctx), ctx);
	CBlockToDecideWhat* ret = new CBlockToDecideWhat(_queryToMatch, _decideBody);
	return  std::shared_ptr<CBlockToDecideWhat>(ret);

}


HBlockCompositionPhrase  load_CBlockCompositionPhrase(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockCompositionPhrase);
	const HBlockKind _fromKind = load_CBlockKind_slot(load_id(ctx), ctx);
	const HBlockKind _toKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockCompositionPhrase* ret = new CBlockCompositionPhrase(_fromKind, _toKind);
	return  std::shared_ptr<CBlockCompositionPhrase>(ret);

}


HBlockMatchBlock  load_CBlockMatchBlock(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchBlock);
	const HBlock _inner = load_CBlock_slot(load_id(ctx), ctx);
	CBlockMatchBlock* ret = new CBlockMatchBlock(_inner);
	return  std::shared_ptr<CBlockMatchBlock>(ret);

}


HBlockMatchIsAdverbialComparasion  load_CBlockMatchIsAdverbialComparasion(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchIsAdverbialComparasion);
	const string _adverb = load_string(ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchIsAdverbialComparasion* ret = new CBlockMatchIsAdverbialComparasion(_adverb, _obj, _value);
	return  std::shared_ptr<CBlockMatchIsAdverbialComparasion>(ret);

}


HBlockVerbReverseRelation  load_CBlockVerbReverseRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbReverseRelation);
	const HBlock _verbNoum = load_CBlock_slot(load_id(ctx), ctx);
	const HBlockNoum _relationNoum = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockVerbReverseRelation* ret = new CBlockVerbReverseRelation(_verbNoum, _relationNoum);
	return  std::shared_ptr<CBlockVerbReverseRelation>(ret);

}


HBlockNamedValue  load_CBlockNamedValue(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNamedValue);
	const string _named = load_string(ctx);
	CBlockNamedValue* ret = new CBlockNamedValue(_named);
	return  std::shared_ptr<CBlockNamedValue>(ret);

}


HBlockCompostionPhrase  load_CBlockCompostionPhrase(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockCompostionPhrase);
	CBlockCompostionPhrase* ret = new CBlockCompostionPhrase();
	return  std::shared_ptr<CBlockCompostionPhrase>(ret);

}


HBlockTryCall  load_CBlockTryCall(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockTryCall);
	const HBlock _sentence = load_CBlock_slot(load_id(ctx), ctx);
	CBlockTryCall* ret = new CBlockTryCall(_sentence);
	return  std::shared_ptr<CBlockTryCall>(ret);

}


HBlockAssertion_isLocalVariable  load_CBlockAssertion_isLocalVariable(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isLocalVariable);
	const HBlockNoum _variableName = load_CBlockNoum_slot(load_id(ctx), ctx);
	const HBlock _valueExpression = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isLocalVariable* ret = new CBlockAssertion_isLocalVariable(_variableName, _valueExpression);
	return  std::shared_ptr<CBlockAssertion_isLocalVariable>(ret);

}


HBlockInstanceNamed  load_CBlockInstanceNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockInstanceNamed);
	const string _named = load_string(ctx);
	const int _id = load_int(ctx);
	const HBlockKind _baseKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockInstanceNamed* ret = new CBlockInstanceNamed(_named, _id, _baseKind);
	return  std::shared_ptr<CBlockInstanceNamed>(ret);

}


// BASE CBlockNumber

HBlockArgumentInput  load_CBlockArgumentInput(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockArgumentInput);
	const HBlockKind _kind = load_CBlockKind_slot(load_id(ctx), ctx);
	const string _named = load_string(ctx);
	CBlockArgumentInput* ret = new CBlockArgumentInput(_kind, _named);
	return  std::shared_ptr<CBlockArgumentInput>(ret);

}


HBlockList_OR  load_CBlockList_OR(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockList_OR);
	const std::list<HBlock> _lista = load_list<CBlock>(ctx);
	CBlockList_OR* ret = new CBlockList_OR(_lista);
	return  std::shared_ptr<CBlockList_OR>(ret);

}


HBlockPhraseInvoke  load_CBlockPhraseInvoke(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockPhraseInvoke);
	const HBlockNoum _name = load_CBlockNoum_slot(load_id(ctx), ctx);
	const HBlockList _args = load_CBlockList_slot(load_id(ctx), ctx); 
	CBlockPhraseInvoke* ret = new CBlockPhraseInvoke(_name, _args);
	return  std::shared_ptr<CBlockPhraseInvoke>(ret);

}


HBlockBody   load_CBlockBody(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockBody );
	HBlock _body = load_CBlock_slot(load_id(ctx), ctx);	
	CBlockBody* ret = new CBlockBody(_body);
	return  std::shared_ptr<CBlockBody>(ret);

}




HBlockVerbDirectRelation  load_CBlockVerbDirectRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbDirectRelation);
	const HBlock _verbNoum = load_CBlock_slot(load_id(ctx), ctx);
	const HBlockNoum _relationNoum = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockVerbDirectRelation* ret = new CBlockVerbDirectRelation(_verbNoum, _relationNoum);
	return  std::shared_ptr<CBlockVerbDirectRelation>(ret);

}


// BASE CBlockCollection
// BASE CBlockNoum
HBlockPhraseDefine  load_CBlockPhraseDefine(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockPhraseDefine);
	const HBlockPhraseHeader _header = load_CBlockPhraseHeader_slot(load_id(ctx), ctx);
	const HBlock _body = load_CBlock_slot(load_id(ctx), ctx);
	CBlockPhraseDefine* ret = new CBlockPhraseDefine(_header, _body);
	return  std::shared_ptr<CBlockPhraseDefine>(ret);

}


HBlockVerbConjugation  load_CBlockVerbConjugation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbConjugation);
	const string _word = load_string(ctx);
	const string _tense = load_string(ctx);
	CBlockVerbConjugation* ret = new CBlockVerbConjugation(_word, _tense);
	return  std::shared_ptr<CBlockVerbConjugation>(ret);

}


HBlockProperty  load_CBlockProperty(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockProperty);
	const HBlock _prop = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _obj = load_CBlock_slot(load_id(ctx), ctx);
	CBlockProperty* ret = new CBlockProperty(_prop, _obj);
	return  std::shared_ptr<CBlockProperty>(ret);

}


HBlockSimetricRelation  load_CBlockSimetricRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockSimetricRelation);
	const std::string _named = load_string(ctx);
	const HBlockArgumentInput input_A = load_CBlockArgumentInput_slot(load_id(ctx), ctx);
	const HBlockArgumentInput input_B = load_CBlockArgumentInput_slot(load_id(ctx), ctx);
	const bool _various_noum1 = load_bool(ctx);
	const bool _various_noum2 = load_bool(ctx);
	CBlockSimetricRelation* ret = new CBlockSimetricRelation(_named, input_A, input_B, _various_noum1, _various_noum2);
	return  std::shared_ptr<CBlockSimetricRelation>(ret);

}


HBlockList_AND  load_CBlockList_AND(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockList_AND);
	const std::list<HBlock> _lista = load_list<CBlock>(ctx);
	CBlockList_AND* ret = new CBlockList_AND(_lista);
	return  std::shared_ptr<CBlockList_AND>(ret);

}



HBlockMatchNamed  load_CBlockMatchNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchNamed);
	const string _named = load_string(ctx);
	const HBlockMatch _matchInner = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchNamed* ret = new CBlockMatchNamed(_named, _matchInner);
	return  std::shared_ptr<CBlockMatchNamed>(ret);

}


HBlockMatchIsVerb  load_CBlockMatchIsVerb(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchIsVerb);
	const string _verb = load_string(ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchIsVerb* ret = new CBlockMatchIsVerb(_verb, _obj, _value);
	return  std::shared_ptr<CBlockMatchIsVerb>(ret);

}

 
HBlockMatchIsVerbComposition  load_CBlockMatchIsVerbComposition(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchIsVerbComposition);	
	const HBlockMatchList _verbComp = load_CBlockMatchList_slot(load_id(ctx), ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchIsVerbComposition* ret = new CBlockMatchIsVerbComposition(_verbComp, _obj, _value);
	return  std::shared_ptr<CBlockMatchIsVerbComposition>(ret);

}

HBlockAssertion_isNotDirectAssign  load_CBlockAssertion_isNotDirectAssign(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isNotDirectAssign);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isNotDirectAssign* ret = new CBlockAssertion_isNotDirectAssign(_variable, _value);
	return  std::shared_ptr<CBlockAssertion_isNotDirectAssign>(ret);

}


HBlockVerbAdapt  load_CBlockVerbAdapt(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbAdapt);
	const string _verb = load_string(ctx);
	const string _tense = load_string(ctx);
	const string _viewPoint = load_string(ctx);
	CBlockVerbAdapt* ret = new CBlockVerbAdapt(_verb, _tense, _viewPoint);
	return  std::shared_ptr<CBlockVerbAdapt>(ret);

}



// BASE CBlockMatchIs
HBlockSelector_Any  load_CBlockSelector_Any(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockSelector_Any);
	const HBlock _what = load_CBlock_slot(load_id(ctx), ctx);
	CBlockSelector_Any* ret = new CBlockSelector_Any(_what);
	return  std::shared_ptr<CBlockSelector_Any>(ret);

}


HBlockKindOfName  load_CBlockKindOfName(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindOfName);	 
	const HBlockNoum _baseClasseName = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockKindOfName* ret = new CBlockKindOfName(_baseClasseName);
	return  std::shared_ptr<CBlockKindOfName>(ret);

}


HBlockUnderstandDynamic  load_CBlockUnderstandDynamic(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockUnderstandDynamic);
	const HBlockMatch _input_n = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatchList _argument_n = load_CBlockMatchList_slot(load_id(ctx), ctx);
	const HBlock _output_n = load_CBlock_slot(load_id(ctx), ctx);
	CBlockUnderstandDynamic* ret = new CBlockUnderstandDynamic(_input_n, _argument_n, _output_n);
	return  std::shared_ptr<CBlockUnderstandDynamic>(ret);

}



HBlockControlToken  load_CBlockControlToken(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlToken);
	const string _token = load_string(ctx);
	const HBlock _contents = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlToken* ret = new CBlockControlToken(_token, _contents);
	return  std::shared_ptr<CBlockControlToken>(ret);

}


HBlockAssertion_InstanceVariable  load_CBlockAssertion_InstanceVariable(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_InstanceVariable);
	const HBlock _noum = load_CBlock_slot(load_id(ctx), ctx);
	const HBlockInstanceVariable _instance_variable = load_CBlockInstanceVariable_slot(load_id(ctx), ctx);
	CBlockAssertion_InstanceVariable* ret = new CBlockAssertion_InstanceVariable(_noum, _instance_variable);
	return  std::shared_ptr<CBlockAssertion_InstanceVariable>(ret);

}


HBlockVerbLookup  load_CBlockVerbLookup(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbLookup);
	const string _verb = load_string(ctx);
	const HBlockMatch _value1 = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value2 = load_CBlockMatch_slot(load_id(ctx), ctx);
	const NoumLocation _term_to_query = load_NoumLocation(ctx);
	CBlockVerbLookup* ret = new CBlockVerbLookup(_verb, _value1, _value2, _term_to_query);
	return  std::shared_ptr<CBlockVerbLookup>(ret);

}


HBlockSelector_All  load_CBlockSelector_All(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockSelector_All);
	const HBlock _what = load_CBlock_slot(load_id(ctx), ctx);
	CBlockSelector_All* ret = new CBlockSelector_All(_what);
	return  std::shared_ptr<CBlockSelector_All>(ret);

}


HBlockKindAction  load_CBlockKindAction(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindAction);
	const HBlockActionApply _applyTo = load_CBlockActionApply_slot(load_id(ctx), ctx);
	CBlockKindAction* ret = new CBlockKindAction(_applyTo);
	return  std::shared_ptr<CBlockKindAction>(ret);

}


HBlockControlSelect  load_CBlockControlSelect(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlSelect);
	const HBlock _block_seletor = load_CBlock_slot(load_id(ctx), ctx);
	const std::list<HBlockControlSelectItem> _block_selectList = load_list<CBlockControlSelectItem>(ctx);
	const HBlock _block_else = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlSelect* ret = new CBlockControlSelect(_block_seletor, _block_selectList, _block_else);
	return  std::shared_ptr<CBlockControlSelect>(ret);

}


// BASE CBlockValue
HBlockAssertion_isInstanceOf  load_CBlockAssertion_isInstanceOf(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isInstanceOf);
	const HBlockInstance _noum = load_CBlockInstance_slot(load_id(ctx), ctx);
	const HBlockKind _baseKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockAssertion_isInstanceOf* ret = new CBlockAssertion_isInstanceOf(_noum, _baseKind);
	return  std::shared_ptr<CBlockAssertion_isInstanceOf>(ret);

}



HBlockControlIF  load_CBlockControlIF(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlIF);
	const HBlock _block_if = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_then = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_else = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlIF* ret = new CBlockControlIF(_block_if, _block_then, _block_else);
	return  std::shared_ptr<CBlockControlIF>(ret);

}


HBlockActionNamed  load_CBlockActionNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockActionNamed);
	const std::string _named = load_string(ctx);
	const HBlockKindAction _actionKind = load_CBlockKindAction_slot(load_id(ctx), ctx);
	CBlockActionNamed* ret = new CBlockActionNamed(_named, _actionKind);
	return  std::shared_ptr<CBlockActionNamed>(ret);

}


HBlockMatchNOT  load_CBlockMatchNOT(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchNOT);
	const HBlockMatch _input = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchNOT* ret = new CBlockMatchNOT(_input);
	return  std::shared_ptr<CBlockMatchNOT>(ret);

}


HBlockRelationInstance  load_CBlockRelationInstance(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockRelationInstance);
	const HBlockRelationBase _relation = load_CBlockRelationBase_slot(load_id(ctx), ctx);
	const HBlock _value1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockRelationInstance* ret = new CBlockRelationInstance(_relation, _value1, _value2);
	return  std::shared_ptr<CBlockRelationInstance>(ret);

}


HBlockVariableNamed  load_CBlockVariableNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVariableNamed);
	const HBlockNoum _name = load_CBlockNoum_slot(load_id(ctx), ctx);
	const HBlockKind _kind = load_CBlockKind_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockVariableNamed* ret = new CBlockVariableNamed(_name, _kind, _value);
	return  std::shared_ptr<CBlockVariableNamed>(ret);

}


HBlockNothing  load_CBlockNothing(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNothing);
	const string _named = load_string(ctx);
	CBlockNothing* ret = new CBlockNothing(_named);
	return  std::shared_ptr<CBlockNothing>(ret);

}


HBlockMatchDirectIs  load_CBlockMatchDirectIs(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchDirectIs);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchDirectIs* ret = new CBlockMatchDirectIs(_obj, _value);
	return  std::shared_ptr<CBlockMatchDirectIs>(ret);

}


HBlockMatchAny  load_CBlockMatchAny(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchAny);
	CBlockMatchAny* ret = new CBlockMatchAny();
	return  std::shared_ptr<CBlockMatchAny>(ret);

}


HBlockRelationArguments  load_CBlockRelationArguments(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockRelationArguments);
	const HBlock _value1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockRelationArguments* ret = new CBlockRelationArguments(_value1, _value2);
	return  std::shared_ptr<CBlockRelationArguments>(ret);

}



HBlockStaticDispatch  load_CBlockStaticDispatch(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockStaticDispatch);
	const int _staticEntryTable = load_int(ctx);
	const HBlock _noum1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _noum2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockStaticDispatch* ret = new CBlockStaticDispatch(_staticEntryTable, _noum1, _noum2);
	return  std::shared_ptr<CBlockStaticDispatch>(ret);

}


HBlockIsAdverbialComparasion  load_CBlockIsAdverbialComparasion(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockIsAdverbialComparasion);
	const string _adverb = load_string(ctx);
	const HBlock _n1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _n2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockIsAdverbialComparasion* ret = new CBlockIsAdverbialComparasion(_adverb, _n1, _n2);
	return  std::shared_ptr<CBlockIsAdverbialComparasion>(ret);

}


HBlockAssertion_isDefaultAssign  load_CBlockAssertion_isDefaultAssign(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isDefaultAssign);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isDefaultAssign* ret = new CBlockAssertion_isDefaultAssign(_variable, _value);
	return  std::shared_ptr<CBlockAssertion_isDefaultAssign>(ret);

}


HBlockRelationLookup  load_CBlockRelationLookup(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockRelationLookup);
	const string _relation = load_string(ctx);
	const HBlockMatch _value1 = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value2 = load_CBlockMatch_slot(load_id(ctx), ctx);
	const NoumLocation _term_to_query = load_NoumLocation(ctx);
	CBlockRelationLookup* ret = new CBlockRelationLookup(_relation, _value1, _value2, _term_to_query);
	return  std::shared_ptr<CBlockRelationLookup>(ret);

}


HBlockAssertion_isVariable  load_CBlockAssertion_isVariable(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isVariable);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _baseKind = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isVariable* ret = new CBlockAssertion_isVariable(_variable, _baseKind);
	return  std::shared_ptr<CBlockAssertion_isVariable>(ret);

}


HBlockMatchNoum  load_CBlockMatchNoum(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchNoum);
	const HBlockNoum _inner = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockMatchNoum* ret = new CBlockMatchNoum(_inner);
	return  std::shared_ptr<CBlockMatchNoum>(ret);

}


HBlockKindValue  load_CBlockKindValue(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindValue);
	const string _named = load_string(ctx);
	CBlockKindValue* ret = new CBlockKindValue(_named);
	return  std::shared_ptr<CBlockKindValue>(ret);

}


HBlockEventHandle  load_CBlockEventHandle(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockEventHandle);
	const EventHandleStage _stage = load_EventHandleStage(ctx);
	const HBlockMatchActionCall _eventToObserve = load_CBlockMatchActionCall_slot(load_id(ctx), ctx);
	const HBlock  _body = load_CBlock_slot(load_id(ctx), ctx);
	CBlockEventHandle* ret = new CBlockEventHandle(_stage, _eventToObserve, _body);
	return  std::shared_ptr<CBlockEventHandle>(ret);

}


HBlockMatchWhich  load_CBlockMatchWhich(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchWhich);
	const string _verb = load_string(ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchWhich* ret = new CBlockMatchWhich(_verb, _obj, _value);
	return  std::shared_ptr<CBlockMatchWhich>(ret);

}


HBlockAnything  load_CBlockAnything(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAnything);
	const string _named = load_string(ctx);
	CBlockAnything* ret = new CBlockAnything(_named);
	return  std::shared_ptr<CBlockAnything>(ret);

}


HBlockUnitTest  load_CBlockUnitTest(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockUnitTest);
	const HBlock _contents = load_CBlock_slot(load_id(ctx), ctx);
	CBlockUnitTest* ret = new CBlockUnitTest(_contents);
	return  std::shared_ptr<CBlockUnitTest>(ret);

}


HBlockTextSentence  load_CBlockTextSentence(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockTextSentence);
	const std::list<HBlock> _contents = load_list<CBlock>(ctx);
	CBlockTextSentence* ret = new CBlockTextSentence(_contents);
	return  std::shared_ptr<CBlockTextSentence>(ret);

}


HBlockAssert  load_CBlockAssert(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssert);
	const HBlock _expression = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _result = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssert* ret = new CBlockAssert(_expression, _result);
	return  std::shared_ptr<CBlockAssert>(ret);

}


HBlockKindOf  load_CBlockKindOf(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindOf);
	const HBlockKind _baseClasse = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockKindOf* ret = new CBlockKindOf(_baseClasse);
	return  std::shared_ptr<CBlockKindOf>(ret);

}


// BASE CBlockSelector
HBlockEnums  load_CBlockEnums(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockEnums);
	const std::vector<HBlockNoum> _values = load_vector<CBlockNoum>(ctx);
	CBlockEnums* ret = new CBlockEnums(_values);
	return  std::shared_ptr<CBlockEnums>(ret);

}


HBlockMatchKind  load_CBlockMatchKind(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchKind);
	const HBlockKind _kind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockMatchKind* ret = new CBlockMatchKind(_kind);
	return  std::shared_ptr<CBlockMatchKind>(ret);

}


HBlockMatchValue  load_CBlockMatchValue(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchValue);
	const HBlock _inner = load_CBlock_slot(load_id(ctx), ctx);
	CBlockMatchValue* ret = new CBlockMatchValue(_inner);
	return  std::shared_ptr<CBlockMatchValue>(ret);

}

//  CBlockMatchText
HBlockMatchText  load_CBlockMatchText(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchText);
	int id = load_id(ctx);
	const HBlockText _inner = load_CBlockText_slot(id, ctx);
	CBlockMatchText* ret = new CBlockMatchText(_inner);
	return  std::shared_ptr<CBlockMatchText>(ret);

}



HBlockText  load_CBlockText(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockText);
	const std::string _contents = load_string(ctx);
	CBlockText* ret = new CBlockText(_contents);
	return  std::shared_ptr<CBlockText>(ret);

}


HBlockUnitAssert  load_CBlockUnitAssert(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockUnitAssert);
	const HBlock _contents = load_CBlock_slot(load_id(ctx), ctx);
	CBlockUnitAssert* ret = new CBlockUnitAssert(_contents);
	return  std::shared_ptr<CBlockUnitAssert>(ret);

}


// BASE CBlockInstance
HBlockUnderstandStatic  load_CBlockUnderstandStatic(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockUnderstandStatic);
	const int _entryID = load_int(ctx);
	const HBlockMatchList _argument_match = load_CBlockMatchList_slot(load_id(ctx), ctx);
	const HBlock _output_n = load_CBlock_slot(load_id(ctx), ctx);
	CBlockUnderstandStatic* ret = new CBlockUnderstandStatic(_entryID, _argument_match, _output_n);
	return  std::shared_ptr<CBlockUnderstandStatic>(ret);

}


HBlockMatchActionCall  load_CBlockMatchActionCall(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchActionCall);
	const HBlockMatch _action = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _argument1 = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _argument2 = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchActionCall* ret = new CBlockMatchActionCall(_action, _argument1, _argument2);
	return  std::shared_ptr<CBlockMatchActionCall>(ret);

}


HBlockAssertion_canBe  load_CBlockAssertion_canBe(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_canBe);
	const HBlock _obj = load_CBlock_slot(load_id(ctx), ctx);
	const HBlockEnums _definition = load_CBlockEnums_slot(load_id(ctx), ctx);
	CBlockAssertion_canBe* ret = new CBlockAssertion_canBe(_obj, _definition);
	return  std::shared_ptr<CBlockAssertion_canBe>(ret);

}


HBlockExecutionResultFlag  load_CBlockExecutionResultFlag(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockExecutionResultFlag);
	const PhaseResultFlag _flag = load_PhaseResultFlag(ctx);
	const HBlock _contents = load_CBlock_slot(load_id(ctx), ctx);
	CBlockExecutionResultFlag* ret = new CBlockExecutionResultFlag(_flag, _contents);
	return  std::shared_ptr<CBlockExecutionResultFlag>(ret);

}


HBlockMatchDirectIsNot  load_CBlockMatchDirectIsNot(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchDirectIsNot);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchDirectIsNot* ret = new CBlockMatchDirectIsNot(_obj, _value);
	return  std::shared_ptr<CBlockMatchDirectIsNot>(ret);

}


HBlockMatchWhichNot  load_CBlockMatchWhichNot(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchWhichNot);
	const string _verb = load_string(ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchWhichNot* ret = new CBlockMatchWhichNot(_verb, _obj, _value);
	return  std::shared_ptr<CBlockMatchWhichNot>(ret);

}


HBlockAssertion_isNamedValueOf  load_CBlockAssertion_isNamedValueOf(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isNamedValueOf);
	const HBlock _noum = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _baseKind = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isNamedValueOf* ret = new CBlockAssertion_isNamedValueOf(_noum, _baseKind);
	return  std::shared_ptr<CBlockAssertion_isNamedValueOf>(ret);

}


HBlockNow  load_CBlockNow(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNow);
	const HBlockAssertion_is _assertation = load_CBlockAssertion_is_slot(load_id(ctx), ctx);
	CBlockNow* ret = new CBlockNow(_assertation);
	return  std::shared_ptr<CBlockNow>(ret);

}


// BASE CBlockAssertionBase
HBlockBooleanAND  load_CBlockBooleanAND(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockBooleanAND);
	const HBlock input_A = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock input_B = load_CBlock_slot(load_id(ctx), ctx);
	CBlockBooleanAND* ret = new CBlockBooleanAND(input_A, input_B);
	return  std::shared_ptr<CBlockBooleanAND>(ret);

}


// BASE CBlockAssertion_is
// BASE CBlockComposition
HBlockControlForEach  load_CBlockControlForEach(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlForEach);
	const HBlock _block_variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_body = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlForEach* ret = new CBlockControlForEach(_block_variable, _block_body);
	return  std::shared_ptr<CBlockControlForEach>(ret);

}


// BASE CBlockToDecide
HBlockNoumStr  load_CBlockNoumStr(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNoumStr);
	const string _named = load_string(ctx);
	CBlockNoumStr* ret = new CBlockNoumStr(_named);
	return  std::shared_ptr<CBlockNoumStr>(ret);

}

 

HBlockNoumCompose  load_CBlockNoumCompose(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNoumCompose);
	const std::vector<HBlockNoum> _values = load_vector<CBlockNoum>(ctx);
	CBlockNoumCompose* ret = new CBlockNoumCompose(_values);
	return  std::shared_ptr<CBlockNoumCompose>(ret);
}


HBlockNoumStrDet  load_CBlockNoumStrDet(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNoumStrDet);
	const string _det = load_string(ctx);	 
	const HBlockNoum _named = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockNoumStrDet* ret = new CBlockNoumStrDet(_det,_named);
	return  std::shared_ptr<CBlockNoumStrDet>(ret);
}


HBlockBooleanValue  load_CBlockBooleanValue(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockBooleanValue);
	const bool _state = load_bool(ctx);
	CBlockBooleanValue* ret = new CBlockBooleanValue(_state);
	return  std::shared_ptr<CBlockBooleanValue>(ret);

}


HBlockPhraseHeader  load_CBlockPhraseHeader(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockPhraseHeader);
	const HBlockNoum _name = load_CBlockNoum_slot(load_id(ctx), ctx);
	const HBlockMatchList _matchPhrase = load_CBlockMatchList_slot(load_id(ctx), ctx);
	const HBlockMatchList _matchArgs = load_CBlockMatchList_slot(load_id(ctx), ctx);
	CBlockPhraseHeader* ret = new CBlockPhraseHeader(_name, _matchPhrase , _matchArgs );
	return  std::shared_ptr<CBlockPhraseHeader>(ret);

}


HBlockUnitInit  load_CBlockUnitInit(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockUnitInit);
	const HBlock _contents = load_CBlock_slot(load_id(ctx), ctx);
	CBlockUnitInit* ret = new CBlockUnitInit(_contents);
	return  std::shared_ptr<CBlockUnitInit>(ret);

}


HBlockBooleanOR  load_CBlockBooleanOR(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockBooleanOR);
	const HBlock input_A = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock input_B = load_CBlock_slot(load_id(ctx), ctx);
	CBlockBooleanOR* ret = new CBlockBooleanOR(input_A, input_B);
	return  std::shared_ptr<CBlockBooleanOR>(ret);

}


HBlockVerb  load_CBlockVerb(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerb);
	const string _named = load_string(ctx);
	const std::list<HBlockVerbConjugation> _conjugations = load_list<CBlockVerbConjugation>(ctx);
	CBlockVerb* ret = new CBlockVerb(_named, _conjugations);
	return  std::shared_ptr<CBlockVerb>(ret);

}


HBlockIntegerNumber  load_CBlockIntegerNumber(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockIntegerNumber);
	const int _value = load_int(ctx);
	CBlockIntegerNumber* ret = new CBlockIntegerNumber(_value);
	return  std::shared_ptr<CBlockIntegerNumber>(ret);

}


HBlockMatchList  load_CBlockMatchList(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchList);
	const std::list<HBlockMatch> _matchList = load_list<CBlockMatch>(ctx);
	CBlockMatchList* ret = new CBlockMatchList(_matchList);
	return  std::shared_ptr<CBlockMatchList>(ret);

}


HBlockVerbNegate  load_CBlockVerbNegate(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockVerbNegate);
	const HBlockVerbAdapt _verbAdapt = load_CBlockVerbAdapt_slot(load_id(ctx), ctx);
	CBlockVerbNegate* ret = new CBlockVerbNegate(_verbAdapt);
	return  std::shared_ptr<CBlockVerbNegate>(ret);

}


HBlockActionInstance  load_CBlockActionInstance(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockActionInstance);
	const int _id = load_int(ctx);
	const HBlockKindAction _base_kind = load_CBlockKindAction_slot(load_id(ctx), ctx);
	CBlockActionInstance* ret = new CBlockActionInstance(_id, _base_kind);
	return  std::shared_ptr<CBlockActionInstance>(ret);

}


HBlockMatchProperty  load_CBlockMatchProperty(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchProperty);
	const HBlock _prop = load_CBlock_slot(load_id(ctx), ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchProperty* ret = new CBlockMatchProperty(_prop, _obj);
	return  std::shared_ptr<CBlockMatchProperty>(ret);

}

 
HBlockCompositionRulebook  load_CBlockCompositionRulebook(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockCompositionRulebook);
	const HBlockKind _fromKind = load_CBlockKind_slot(load_id(ctx), ctx);
	const HBlockKind _toKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockCompositionRulebook* ret = new CBlockCompositionRulebook(_fromKind, _toKind);
	return  std::shared_ptr<CBlockCompositionRulebook>(ret);

}



HBlockCompositionRelation  load_CBlockCompositionRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockCompositionRelation);
	const HBlockKind _fromKind = load_CBlockKind_slot(load_id(ctx), ctx);
	const HBlockKind _toKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockCompositionRelation* ret = new CBlockCompositionRelation(_fromKind, _toKind);
	return  std::shared_ptr<CBlockCompositionRelation>(ret);

}


HBlockInstanceAnonymous  load_CBlockInstanceAnonymous(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockInstanceAnonymous);
	const int _id = load_int(ctx);
	const HBlockKind _baseKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockInstanceAnonymous* ret = new CBlockInstanceAnonymous(_id, _baseKind);
	return  std::shared_ptr<CBlockInstanceAnonymous>(ret);

}


HBlockToDecideOn  load_CBlockToDecideOn(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockToDecideOn);
	const HBlock _decideBody = load_CBlock_slot(load_id(ctx), ctx);
	CBlockToDecideOn* ret = new CBlockToDecideOn(_decideBody);
	return  std::shared_ptr<CBlockToDecideOn>(ret);

}


HBlockKindReference  load_CBlockKindReference(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindReference);
	const HBlockKind _kind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockKindReference* ret = new CBlockKindReference(_kind);
	return  std::shared_ptr<CBlockKindReference>(ret);

}


HBlockComandList  load_CBlockComandList(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockComandList);
	const std::list<HBlock> _lista = load_list<CBlock>(ctx);
	CBlockComandList* ret = new CBlockComandList(_lista);
	return  std::shared_ptr<CBlockComandList>(ret);

}


HBlockMatchIsNotVerb  load_CBlockMatchIsNotVerb(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockMatchIsNotVerb);
	const string _verb = load_string(ctx);
	const HBlockMatch _obj = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlockMatch _value = load_CBlockMatch_slot(load_id(ctx), ctx);
	CBlockMatchIsNotVerb* ret = new CBlockMatchIsNotVerb(_verb, _obj, _value);
	return  std::shared_ptr<CBlockMatchIsNotVerb>(ret);

}


HBlockKind_InstanceVariable  load_CBlockKind_InstanceVariable(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKind_InstanceVariable);
	const HBlockKind _kind = load_CBlockKind_slot(load_id(ctx), ctx);
	const HBlockInstanceVariable _variableNamed = load_CBlockInstanceVariable_slot(load_id(ctx), ctx);
	CBlockKind_InstanceVariable* ret = new CBlockKind_InstanceVariable(_kind, _variableNamed);
	return  std::shared_ptr<CBlockKind_InstanceVariable>(ret);

}


// BASE CBlockMatch
HBlockASimetricRelation  load_CBlockASimetricRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockASimetricRelation);
	const std::string _named = load_string(ctx);
	const HBlockArgumentInput input_A = load_CBlockArgumentInput_slot(load_id(ctx), ctx);
	const HBlockArgumentInput input_B = load_CBlockArgumentInput_slot(load_id(ctx), ctx);
	const bool _various_noum1 = load_bool(ctx);
	const bool _various_noum2 = load_bool(ctx);
	CBlockASimetricRelation* ret = new CBlockASimetricRelation(_named, input_A, input_B, _various_noum1, _various_noum2);
	return  std::shared_ptr<CBlockASimetricRelation>(ret);

}


HBlockToDecideIf  load_CBlockToDecideIf(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockToDecideIf);
	int slot_id = load_id(ctx);
	const HBlockMatchIs _queryToMatch = load_CBlockMatchIs_slot(slot_id, ctx);
	const HBlock _decideBody = load_CBlock_slot(load_id(ctx), ctx);
	CBlockToDecideIf* ret = new CBlockToDecideIf(_queryToMatch, _decideBody);
	return  std::shared_ptr<CBlockToDecideIf>(ret);

}


HBlockFactionalNumber  load_CBlockFactionalNumber(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockFactionalNumber);
	const float _value = load_float(ctx);
	CBlockFactionalNumber* ret = new CBlockFactionalNumber(_value);
	return  std::shared_ptr<CBlockFactionalNumber>(ret);

}


HBlockCompositionList  load_CBlockCompositionList(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockCompositionList);
	const HBlockKind _itemKind = load_CBlockKind_slot(load_id(ctx), ctx);
	CBlockCompositionList* ret = new CBlockCompositionList(_itemKind);
	return  std::shared_ptr<CBlockCompositionList>(ret);

}


HBlockSelector_Where  load_CBlockSelector_Where(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockSelector_Where);
	const HBlock _what = load_CBlock_slot(load_id(ctx), ctx);
	CBlockSelector_Where* ret = new CBlockSelector_Where(_what);
	return  std::shared_ptr<CBlockSelector_Where>(ret);

}


HBlockIsNotVerb  load_CBlockIsNotVerb(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockIsNotVerb);
	const string _verb = load_string(ctx);
	const HBlock _n1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _n2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockIsNotVerb* ret = new CBlockIsNotVerb(_verb, _n1, _n2);
	return  std::shared_ptr<CBlockIsNotVerb>(ret);

}


HBlockToDecideWhether  load_CBlockToDecideWhether(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockToDecideWhether);
	const HBlockMatch _queryToMatch = load_CBlockMatch_slot(load_id(ctx), ctx);
	const HBlock _decideBody = load_CBlock_slot(load_id(ctx), ctx);
	CBlockToDecideWhether* ret = new CBlockToDecideWhether(_queryToMatch, _decideBody);
	return  std::shared_ptr<CBlockToDecideWhether>(ret);

}


HBlockAssertion_isConstantAssign  load_CBlockAssertion_isConstantAssign(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isConstantAssign);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isConstantAssign* ret = new CBlockAssertion_isConstantAssign(_variable, _value);
	return  std::shared_ptr<CBlockAssertion_isConstantAssign>(ret);

}


HBlockEvery  load_CBlockEvery(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockEvery);
	const HBlock _assertation = load_CBlock_slot(load_id(ctx), ctx);
	CBlockEvery* ret = new CBlockEvery(_assertation);
	return  std::shared_ptr<CBlockEvery>(ret);

}


HBlockActionApply  load_CBlockActionApply(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockActionApply);
	const HBlock _noum1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _noum2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockActionApply* ret = new CBlockActionApply(_noum1, _noum2);
	return  std::shared_ptr<CBlockActionApply>(ret);

}


HBlockConditionalRelation  load_CBlockConditionalRelation(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockConditionalRelation);
	const HBlockRelationBase _relation = load_CBlockRelationBase_slot(load_id(ctx), ctx);
	const HBlock _coditional = load_CBlock_slot(load_id(ctx), ctx);
	CBlockConditionalRelation* ret = new CBlockConditionalRelation(_relation, _coditional);
	return  std::shared_ptr<CBlockConditionalRelation>(ret);

}


HBlockControlUnless  load_CBlockControlUnless(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockControlUnless);
	const HBlock _block_if = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_then = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _block_else = load_CBlock_slot(load_id(ctx), ctx);
	CBlockControlUnless* ret = new CBlockControlUnless(_block_if, _block_then, _block_else);
	return  std::shared_ptr<CBlockControlUnless>(ret);

}


HBlockDinamicDispatch  load_CBlockDinamicDispatch(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockDinamicDispatch);
	const HBlockList _commandList = load_CBlockList_slot(load_id(ctx), ctx);
	CBlockDinamicDispatch* ret = new CBlockDinamicDispatch(_commandList);
	return  std::shared_ptr<CBlockDinamicDispatch>(ret);

}



// BASE CBlockRelationBase
HBlockSelectorAND  load_CBlockSelectorAND(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockSelectorAND);
	const HBlock _value1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockSelectorAND* ret = new CBlockSelectorAND(_value1, _value2);
	return  std::shared_ptr<CBlockSelectorAND>(ret);

}


HBlockNoumSupl  load_CBlockNoumSupl(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockNoumSupl);
	const string _named = load_string(ctx);
	const string _number = load_string(ctx);
	const string _gender = load_string(ctx);
	CBlockNoumSupl* ret = new CBlockNoumSupl(_named, _number, _gender);
	return  std::shared_ptr<CBlockNoumSupl>(ret);

}


HBlockBooleanNOT  load_CBlockBooleanNOT(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockBooleanNOT);
	const HBlock input_A = load_CBlock_slot(load_id(ctx), ctx);
	CBlockBooleanNOT* ret = new CBlockBooleanNOT(input_A);
	return  std::shared_ptr<CBlockBooleanNOT>(ret);

}


HBlockInstanceVariable  load_CBlockInstanceVariable(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockInstanceVariable);
	const HBlockNoum _kind_name = load_CBlockNoum_slot(load_id(ctx), ctx);
	const HBlockNoum _property_name = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockInstanceVariable* ret = new CBlockInstanceVariable(_kind_name, _property_name);
	return  std::shared_ptr<CBlockInstanceVariable>(ret);

}


// BASE CBlockAction
HBlockIsVerb  load_CBlockIsVerb(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockIsVerb);
	const string _verb = load_string(ctx);
	const HBlock _n1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _n2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockIsVerb* ret = new CBlockIsVerb(_verb, _n1, _n2);
	return  std::shared_ptr<CBlockIsVerb>(ret);

}


HBlockAssertion_isDirectAssign  load_CBlockAssertion_isDirectAssign(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockAssertion_isDirectAssign);
	const HBlock _variable = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _value = load_CBlock_slot(load_id(ctx), ctx);
	CBlockAssertion_isDirectAssign* ret = new CBlockAssertion_isDirectAssign(_variable, _value);
	return  std::shared_ptr<CBlockAssertion_isDirectAssign>(ret);

}


// BASE CBlockActionCall
HBlockKindEntity  load_CBlockKindEntity(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindEntity);
	const string _named = load_string(ctx);
	CBlockKindEntity* ret = new CBlockKindEntity(_named);
	return  std::shared_ptr<CBlockKindEntity>(ret);

}


HBlockActionCallNamed  load_CBlockActionCallNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockActionCallNamed);
	const HBlockActionNamed _action = load_CBlockActionNamed_slot(load_id(ctx), ctx);
	const HBlock _noum1 = load_CBlock_slot(load_id(ctx), ctx);
	const HBlock _noum2 = load_CBlock_slot(load_id(ctx), ctx);
	CBlockActionCallNamed* ret = new CBlockActionCallNamed(_action, _noum1, _noum2);
	return  std::shared_ptr<CBlockActionCallNamed>(ret);

}



HBlockKindNamed  load_CBlockKindNamed(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockKindNamed);	
	const HBlockNoum _named = load_CBlockNoum_slot(load_id(ctx), ctx);
	CBlockKindNamed* ret = new CBlockKindNamed(_named);
	return  std::shared_ptr<CBlockKindNamed>(ret);

}


HBlockList  load_CBlockList(int tp, LoadContext *ctx)
{
	if (tp == -1) tp = load_type(ctx);
	cmp_type(tp, BlockType::BlockList);
	const std::list<HBlock> _lista = load_list<CBlock>(ctx);
	CBlockList* ret = new CBlockList(_lista);
	return  std::shared_ptr<CBlockList>(ret);

}




