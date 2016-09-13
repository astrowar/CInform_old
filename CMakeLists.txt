cmake_minimum_required(VERSION 3.6)
project(AppMatch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES
        AppMatch/AppMatch/AppMatch.cpp
        AppMatch/AppMatch/AssertationEngine.cpp
        AppMatch/AppMatch/BlockInterpreter.cpp
        AppMatch/AppMatch/BlockInterpreter.h
        AppMatch/AppMatch/CAssertionDefinition.h
        AppMatch/AppMatch/CBase.cpp
        AppMatch/AppMatch/CBase.h
        AppMatch/AppMatch/CblockAssertion.h
        AppMatch/AppMatch/CBlockBoolean.h
        AppMatch/AppMatch/CBlockInterpreterRuntime.h
        AppMatch/AppMatch/CBlockMatch.h
        AppMatch/AppMatch/CInterpreter.cpp
        AppMatch/AppMatch/CInterpreter.h
        AppMatch/AppMatch/CMatch.cpp
        AppMatch/AppMatch/CMatch.h
        AppMatch/AppMatch/CObjectDefinitions.h
        AppMatch/AppMatch/ConstDefinitions.h
        AppMatch/AppMatch/CProperties.h
        AppMatch/AppMatch/CpropertiesFunctions.cpp
        AppMatch/AppMatch/CreateInstanceInterpreter.cpp
        AppMatch/AppMatch/CRelations.cpp
        AppMatch/AppMatch/CRelations.h
        AppMatch/AppMatch/CValueDefinitions.h
        AppMatch/AppMatch/CVariableDefinition.h
        AppMatch/AppMatch/Equality.cpp
        AppMatch/AppMatch/EqualsResult.h
        AppMatch/AppMatch/FEnviroment.cpp
        AppMatch/AppMatch/FEnviroment.h
        AppMatch/AppMatch/CInterpreterResolve.cpp
        AppMatch/AppMatch/AssertionValues.cpp
        AppMatch/AppMatch/Parser.cpp
        AppMatch/AppMatch/Parser.h
        AppMatch/AppMatch/RepresentationFunctions.cpp
        AppMatch/AppMatch/CVariableGlobals.cpp
        AppMatch/AppMatch/InterpreterQuery.cpp
        AppMatch/AppMatch/ParseRelation.cpp
        AppMatch/AppMatch/stdafx.cpp
        AppMatch/AppMatch/stdafx.h
        AppMatch/AppMatch/targetver.h
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
        AppMatch/AppMatch/testes_decide.cpp
        AppMatch/AppMatch/teste_action.cpp
        AppMatch/AppMatch/AssertationVerbRelation.cpp
        AppMatch/AppMatch/ParserSelectorFunctional.cpp
        AppMatch/AppMatch/InterpreterListedFunctions.cpp

        AppMatch/AppMatch/InterpFunctionsCallcpp.cpp
        AppMatch/AppMatch/ParserTextEntry.cpp
        AppMatch/AppMatch/Parser_expression_match.cpp
        AppMatch/AppMatch/Parser_Decide.cpp
        AppMatch/AppMatch/ParserDynamicDispatch.cpp
        AppMatch/AppMatch/InterpreterMatch.cpp
        AppMatch/AppMatch/InterpExecute.cpp
        AppMatch/AppMatch/CResultMatch.cpp
        AppMatch/AppMatch/CInterpreterRelation.cpp
        AppMatch/AppMatch/dynamicCast.cpp
        AppMatch/AppMatch/sharedCast.cpp
        AppMatch/AppMatch/testes_Relation.cpp
        AppMatch/AppMatch/InterpreterRelationEngine.cpp



        AppMatch/AppMatch/ParseDictionary.cpp AppMatch/AppMatch/Parser_A.cpp AppMatch/AppMatch/StaticDispatchFunctions.cpp AppMatch/AppMatch/CParseAux.cpp AppMatch/AppMatch/testes_Relation.cpp AppMatch/AppMatch/InterpreterRelationEngine.cpp AppMatch/AppMatch/CBlockCommand.h)

add_executable(apx ${SOURCE_FILES} AppMatch/AppMatch/ParserDictionary.h)