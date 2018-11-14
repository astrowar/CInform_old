cmake_minimum_required(VERSION 3.4)
project(CInform)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fno-exceptions -fno-rtti ")
set (CMAKE_CXX_STANDARD 14)

IF    (CMAKE_COMPILER_IS_GNUCC)
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++1y -fno-exceptions -fno-rtti")
ELSEIF(MSVC71 OR MSVC80)
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHc-")
ENDIF (CMAKE_COMPILER_IS_GNUCC)



include_directories( AppMatch/include/ )


set(SOURCE_FILES_PARSER

        AppMatch/src/parser/CParseAux.cpp
        AppMatch/src/parser/ParseAssertationSecondary.cpp
        AppMatch/src/parser/ParseDictionary.cpp
        AppMatch/src/parser/ParseListAux.cpp
        AppMatch/src/parser/Parser.cpp
        AppMatch/src/parser/ParserDynamicDispatch.cpp
        AppMatch/src/parser/ParseRelation.cpp
        AppMatch/src/parser/ParseRelationWhen.cpp
        AppMatch/src/parser/ParserSelectorFunctional.cpp
        AppMatch/src/parser/ParserStmt.cpp
        AppMatch/src/parser/ParserTextEntry.cpp
        AppMatch/src/parser/Parser_A.cpp
        AppMatch/src/parser/Parser_ActionControl.cpp
        AppMatch/src/parser/Parser_ControlFlux.cpp
        AppMatch/src/parser/Parser_Decide.cpp
        AppMatch/src/parser/ParseRules.cpp
        AppMatch/src/parser/Parser_expression_match.cpp
        AppMatch/src/parser_Eng/Parser_Plurals_En.cpp
        AppMatch/src/parser/Parser_RegisterVerb.cpp
        AppMatch/src/parser_Eng/Parser_VerbTable_en.cpp
        AppMatch/src/parser/ParseVerbs.cpp
        AppMatch/src/parser/Parse_PhraseDeclare.cpp
        AppMatch/src/parser/Parse_TokensGroup.cpp
        AppMatch/src/parser/Parse_verbArray_en.cpp
        AppMatch/src/parser/StaticDispatchFunctions.cpp
        AppMatch/src/parser_Eng/Predicates.cpp
        )


set(SOURCE_FILES_BLOCK
        AppMatch/src/Block/BlockInstance.cpp
        AppMatch/src/Block/BlockInterpreter.cpp
        AppMatch/src/Block/BlockisSame.cpp
        AppMatch/src/Block/BlockTypeEnum.cpp
        AppMatch/src/Block/CBlockAction.cpp
        AppMatch/src/Block/CBlockCommand.cpp
        AppMatch/src/Block/CBlockCompostion.cpp
        AppMatch/src/Block/CBlockDecideIf.cpp
        AppMatch/src/Block/CBlockDumpValues.cpp
        AppMatch/src/Block/CBlockNumber.cpp
        AppMatch/src/Block/CBlockSerialize.cpp
        AppMatch/src/Block/dynamicCast.cpp
        AppMatch/src/Block/save_ctx.cpp
        AppMatch/src/Block/sharedCast.cpp
        AppMatch/src/Block/store_tp.cpp

)


set(SOURCE_FILES_BASE
        AppMatch/src/base/CBase.cpp
        AppMatch/src/base/CMatch.cpp
        AppMatch/src/base/CMatchCombinatoria.cpp
        AppMatch/src/base/CMatchListValid.cpp
        )


set(SOURCE_FILES_COMPILER
          AppMatch/src/compiler/CInformCompiler.cpp 
)

set(SOURCE_FILES_INTERPRETER
        AppMatch/src/interpreterMain/CInformInterpreter.cpp
        AppMatch/src/parser/ParserPlural_table.cpp
        AppMatch/src/parser_Eng/Parser_Plurals_En.cpp
        AppMatch/src/parser_Eng/Parser_VerbTable_en.cpp
        )



set( SOURCE_FILES_INTERPRETERRUNTIME
        AppMatch/src/interpreter/AssertationDefaultValue.cpp
        AppMatch/src/interpreter/AssertationEngine.cpp
        AppMatch/src/interpreter/AssertationVerbRelation.cpp
        AppMatch/src/interpreter/AssertionValues.cpp
        AppMatch/src/interpreter/CBlockInterpreterBase.cpp
        AppMatch/src/interpreter/CBlockInterpreterDecideBody.cpp
        AppMatch/src/interpreter/CBlockInterpreterRuntime.cpp
        AppMatch/src/interpreter/CBlockInterpreter_Verb_En.cpp
        AppMatch/src/interpreter/CInterpreterEvaluate.cpp
        AppMatch/src/interpreter/CInterpreterKindTree.cpp
        AppMatch/src/interpreter/CInterpreterRelation.cpp
        AppMatch/src/interpreter/CInterpreterResolve.cpp
        AppMatch/src/interpreter/CInterpreterResolveMatchSeletor.cpp
        AppMatch/src/interpreter/CInterpreterRuntimeExecute.cpp
        AppMatch/src/interpreter/CreateInstanceInterpreter.cpp
        AppMatch/src/interpreter/CVariableGlobals.cpp
        AppMatch/src/interpreter/InterpExecute.cpp
        AppMatch/src/interpreter/InterpFunctionsCallcpp.cpp
        AppMatch/src/interpreter/InterpreterListedFunctions.cpp
        AppMatch/src/interpreter/InterpreterMatch.cpp
        AppMatch/src/interpreter/InterpreterQuery.cpp
        AppMatch/src/interpreter/InterpreterRelationEngine.cpp
        AppMatch/src/interpreter/Interpreter_Adapt_Text.cpp
        AppMatch/src/interpreter/QueryItem.cpp
        AppMatch/src/interpreter/RuntimeErrors.cpp
        AppMatch/src/interpreter/CResultMatch.cpp
        AppMatch/src/interpreter/PhaseResult_init.cpp
        AppMatch/src/interpreter/interpreterRegex.cpp
        AppMatch/src/parser_Eng/LanguageEn.cpp)


set(SOURCE_FILES

         

        AppMatch/AppMatch/AssertationDefaultValue.cpp
        AppMatch/AppMatch/AssertationEngine.cpp
        AppMatch/AppMatch/AssertationVerbRelation.cpp
        AppMatch/AppMatch/AssertionValues.cpp
        AppMatch/AppMatch/BlockInstance.cpp
        AppMatch/AppMatch/BlockInterpreter.cpp
        AppMatch/AppMatch/BlockisSame.cpp
        AppMatch/AppMatch/CBase.cpp
        AppMatch/AppMatch/CBlockAction.cpp
        AppMatch/AppMatch/CBlockCommand.cpp
        AppMatch/AppMatch/CBlockCompostion.cpp
        AppMatch/AppMatch/CBlockDecideIf.cpp
        AppMatch/AppMatch/CBlockDumpValues.cpp
        AppMatch/AppMatch/CBlockInterpreterDecideBody.cpp
        AppMatch/AppMatch/CBlockInterpreterRuntime.cpp
        AppMatch/AppMatch/CBlockInterpreter_Verb_En.cpp
        AppMatch/AppMatch/CBlockNumber.cpp
        AppMatch/AppMatch/CBlockSerialize.cpp
        AppMatch/AppMatch/CDataMananger.cpp
        AppMatch/AppMatch/CInterpreterEvaluate.cpp
        AppMatch/AppMatch/CInterpreterKindTree.cpp
        AppMatch/AppMatch/CInterpreterRelation.cpp
        AppMatch/AppMatch/CInterpreterResolve.cpp
        AppMatch/AppMatch/CInterpreterResolveMatchSeletor.cpp
        AppMatch/AppMatch/CMatch.cpp
        AppMatch/AppMatch/CMatchCombinatoria.cpp
        AppMatch/AppMatch/CMatchListValid.cpp
        AppMatch/AppMatch/CParseAux.cpp
        AppMatch/AppMatch/CResultMatch.cpp
        AppMatch/AppMatch/CVariableGlobals.cpp
        AppMatch/AppMatch/CreateInstanceInterpreter.cpp
        AppMatch/AppMatch/InterpExecute.cpp
        AppMatch/AppMatch/InterpFunctionsCallcpp.cpp
        AppMatch/AppMatch/InterpreterListedFunctions.cpp
        AppMatch/AppMatch/InterpreterMatch.cpp
        AppMatch/AppMatch/InterpreterQuery.cpp
        AppMatch/AppMatch/InterpreterRelationEngine.cpp
        AppMatch/AppMatch/Interpreter_Adapt_Text.cpp
        AppMatch/AppMatch/ParseAssertationSecondary.cpp
        AppMatch/AppMatch/ParseListAux.cpp
        AppMatch/AppMatch/ParseRelation.cpp
        AppMatch/AppMatch/ParseRelationWhen.cpp
        AppMatch/AppMatch/ParseVerbs.cpp
        AppMatch/AppMatch/Parse_PhraseDeclare.cpp
        AppMatch/AppMatch/Parse_TokensGroup.cpp
        AppMatch/AppMatch/Parser.cpp
        AppMatch/AppMatch/ParserDynamicDispatch.cpp
        AppMatch/AppMatch/ParserPlural_table.cpp
        AppMatch/AppMatch/ParserSelectorFunctional.cpp
        AppMatch/AppMatch/ParserStmt.cpp
        AppMatch/AppMatch/ParserTextEntry.cpp
        AppMatch/AppMatch/Parser_A.cpp
        AppMatch/AppMatch/Parser_ActionControl.cpp
        AppMatch/AppMatch/Parser_ControlFlux.cpp
        AppMatch/AppMatch/Parser_Decide.cpp
        AppMatch/AppMatch/Parser_Plurals_En.cpp
        AppMatch/AppMatch/Parser_RegisterVerb.cpp
        AppMatch/AppMatch/Parser_VerbTable_en.cpp
        AppMatch/AppMatch/Parser_expression_match.cpp
        AppMatch/AppMatch/QueryItem.cpp
        AppMatch/AppMatch/RuntimeErrors.cpp
        AppMatch/AppMatch/StaticDispatchFunctions.cpp
        AppMatch/AppMatch/dynamicCast.cpp
        AppMatch/AppMatch/load_ctx.cpp
        AppMatch/AppMatch/save_ctx.cpp
        AppMatch/AppMatch/serialize_tp.cpp
        AppMatch/AppMatch/sharedCast.cpp
        AppMatch/AppMatch/store_tp.cpp


        AppMatch/AppMatch/GrammarParseEn.cpp
        AppMatch/AppMatch/GrammarParser.cpp
        AppMatch/AppMatch/stdafx.cpp
        AppMatch/AppMatch/testeAdaptivePhases.cpp
        AppMatch/AppMatch/testeGM.cpp
        AppMatch/AppMatch/testeLista.cpp
        AppMatch/AppMatch/testeSerialize.cpp
        AppMatch/AppMatch/testesParser.cpp
        AppMatch/AppMatch/testes_1.cpp
        AppMatch/AppMatch/testes_2.cpp
        AppMatch/AppMatch/testes_decide.cpp
        AppMatch/AppMatch/testes_execute.cpp
        AppMatch/AppMatch/testes_Relation.cpp
        AppMatch/AppMatch/teste_action.cpp
        AppMatch/AppMatch/teste_composition.cpp
        AppMatch/AppMatch/teste_logical.cpp
        AppMatch/AppMatch/teste_phases.cpp
        AppMatch/AppMatch/teste_selector.cpp
        AppMatch/AppMatch/teste_values.cpp
        AppMatch/AppMatch/teste_verb.cpp
        AppMatch/AppMatch/unit_testes.cpp
        AppMatch/AppMatch/stdafx.cpp
        AppMatch/AppMatch/testesParser.cpp
        AppMatch/AppMatch/testes_1.cpp
        AppMatch/AppMatch/testes_2.cpp
        AppMatch/AppMatch/testes_decide.cpp
        AppMatch/AppMatch/testeLista.cpp
        AppMatch/AppMatch/GrammarParser.cpp
        AppMatch/AppMatch/GrammarParseEn.cpp
        AppMatch/AppMatch/teste_action.cpp
        AppMatch/AppMatch/testes_Relation.cpp
        AppMatch/AppMatch/testeSerialize.cpp
        AppMatch/AppMatch/testes_execute.cpp
        AppMatch/AppMatch/teste_selector.cpp
        AppMatch/AppMatch/teste_verb.cpp
        AppMatch/AppMatch/teste_values.cpp
        AppMatch/AppMatch/teste_logical.cpp
        AppMatch/AppMatch/unit_testes.cpp
        AppMatch/AppMatch/teste_composition.cpp
        AppMatch/AppMatch/teste_phases.cpp
        AppMatch/AppMatch/testeAdaptivePhases.cpp
        AppMatch/AppMatch/testeGM.cpp
        AppMatch/AppMatch/stdafx.cpp
        AppMatch/AppMatch/stdafx.cpp

        )



add_library(BaseLibrary  ${SOURCE_FILES_BASE})
add_library(BlockLibrary  ${SOURCE_FILES_BLOCK})
add_library(ParseLibrary  ${SOURCE_FILES_PARSER})
add_library(interpreterRuntimeLibrary   ${SOURCE_FILES_INTERPRETERRUNTIME})

#add_executable(CInformCompiler ${SOURCE_FILES}  )
add_executable(CInformCompiler ${SOURCE_FILES_COMPILER}   )
add_executable(CInformInterpreter ${SOURCE_FILES_INTERPRETER}    )


target_link_libraries (CInformCompiler    ParseLibrary BlockLibrary BaseLibrary)
target_link_libraries (CInformInterpreter     interpreterRuntimeLibrary BlockLibrary BaseLibrary)
