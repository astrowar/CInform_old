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
        AppMatch/AppMatch/InterpreterExecute.cpp
        AppMatch/AppMatch/Parser.cpp
        AppMatch/AppMatch/Parser.h
        AppMatch/AppMatch/RepresentationFunctions.cpp
        AppMatch/AppMatch/stdafx.cpp
        AppMatch/AppMatch/stdafx.h
        AppMatch/AppMatch/targetver.h
        AppMatch/AppMatch/testesParser.cpp
        AppMatch/AppMatch/CInterpreterKindTree.cpp
        AppMatch/AppMatch/CBlockDumpValues.cpp

        AppMatch/AppMatch/UBlock.hpp)

add_executable(apx ${SOURCE_FILES})