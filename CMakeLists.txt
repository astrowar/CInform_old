cmake_minimum_required(VERSION 3.6)
project(AppMatch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fno-exceptions -fno-rtti  ")

include_directories( AppMatch/AppMatch/include/ )

set(SOURCE_FILES

        AppMatch/AppMatch/AssertationEngine.cpp
        AppMatch/AppMatch/BlockInterpreter.cpp
        AppMatch/AppMatch/CBase.cpp

        AppMatch/AppMatch/CMatch.cpp
        AppMatch/AppMatch/CMatchCombinatoria.cpp
        AppMatch/AppMatch/CMatchListValid.cpp
        AppMatch/AppMatch/CreateInstanceInterpreter.cpp

        AppMatch/AppMatch/CInterpreterResolve.cpp
        AppMatch/AppMatch/AssertionValues.cpp
        AppMatch/AppMatch/Parser.cpp
        AppMatch/AppMatch/CVariableGlobals.cpp
        AppMatch/AppMatch/InterpreterQuery.cpp
        AppMatch/AppMatch/ParseRelation.cpp
        AppMatch/AppMatch/stdafx.cpp

        AppMatch/AppMatch/testesParser.cpp
        AppMatch/AppMatch/CInterpreterKindTree.cpp
        AppMatch/AppMatch/CBlockDumpValues.cpp
        AppMatch/AppMatch/BlockInstance.cpp
        AppMatch/AppMatch/CBlockInterpreterDecideBody.cpp
        AppMatch/AppMatch/ParseAssertationSecondary.cpp
        AppMatch/AppMatch/ParseListAux.cpp
        AppMatch/AppMatch/AssertationDefaultValue.cpp
        AppMatch/AppMatch/ParseRelationWhen.cpp
        AppMatch/AppMatch/QueryItem.cpp
        AppMatch/AppMatch/ParserStmt.cpp
        AppMatch/AppMatch/ParseVerbs.cpp
        AppMatch/AppMatch/testeLista.cpp
        AppMatch/AppMatch/testes_1.cpp
        AppMatch/AppMatch/testes_2.cpp
        AppMatch/AppMatch/testes_execute.cpp


        AppMatch/AppMatch/testes_decide.cpp
        AppMatch/AppMatch/teste_action.cpp
        AppMatch/AppMatch/testeSerialize.cpp
        AppMatch/AppMatch/AssertationVerbRelation.cpp
        AppMatch/AppMatch/ParserSelectorFunctional.cpp
        AppMatch/AppMatch/InterpreterListedFunctions.cpp
        AppMatch/AppMatch/Interpreter_Adapt_Text.cpp

        AppMatch/AppMatch/InterpFunctionsCallcpp.cpp
        AppMatch/AppMatch/ParserTextEntry.cpp
        AppMatch/AppMatch/Parser_expression_match.cpp
        AppMatch/AppMatch/Parser_Decide.cpp
        AppMatch/AppMatch/Parse_PhraseDeclare.cpp
        AppMatch/AppMatch/ParserDynamicDispatch.cpp
        AppMatch/AppMatch/InterpreterMatch.cpp
        AppMatch/AppMatch/InterpExecute.cpp
        AppMatch/AppMatch/CResultMatch.cpp
        AppMatch/AppMatch/CInterpreterRelation.cpp
        AppMatch/AppMatch/dynamicCast.cpp
        AppMatch/AppMatch/sharedCast.cpp
        AppMatch/AppMatch/testes_Relation.cpp
        AppMatch/AppMatch/InterpreterRelationEngine.cpp
        AppMatch/AppMatch/CBlockSerialize.cpp

        AppMatch/AppMatch/ParseDictionary.cpp
        AppMatch/AppMatch/Parser_A.cpp
        AppMatch/AppMatch/StaticDispatchFunctions.cpp
        AppMatch/AppMatch/CParseAux.cpp
        AppMatch/AppMatch/testes_Relation.cpp
        AppMatch/AppMatch/InterpreterRelationEngine.cpp
        AppMatch/AppMatch/BlockisSame.cpp
        AppMatch/AppMatch/CInterpreterEvaluate.cpp
        AppMatch/AppMatch/RuntimeErrors.cpp

        AppMatch/AppMatch/Parser_Plurals_En.cpp
        AppMatch/AppMatch/Parser_VerbTable_en.cpp
        AppMatch/AppMatch/CBlockInterpreter_Verb_En.cpp


        AppMatch/AppMatch/Parser_RegisterVerb.cpp
        AppMatch/AppMatch/teste_verb.cpp
        AppMatch/AppMatch/teste_selector.cpp
        AppMatch/AppMatch/teste_composition.cpp
        AppMatch/AppMatch/testeGM.cpp
        AppMatch/AppMatch/CDataMananger.cpp
        AppMatch/AppMatch/Parse_TokensGroup.cpp
        AppMatch/AppMatch/Parser_ControlFlux.cpp
        AppMatch/AppMatch/Parser_ActionControl.cpp
        AppMatch/AppMatch/CBlockInterpreterRuntime.cpp
        AppMatch/AppMatch/CInterpreterResolveMatchSeletor.cpp
        AppMatch/AppMatch/ParserPlural_table.cpp


        AppMatch/AppMatch/CBlockComposition.hpp)

add_executable(apx ${SOURCE_FILES} AppMatch/AppMatch/CBlockComposition.hpp)