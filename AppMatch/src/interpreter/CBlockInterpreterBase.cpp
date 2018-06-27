//
// Created by eraldo on 26/06/2018.
//

#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "BlockInterpreter.hpp"
#include "CBlockInterpreterBase.h"

Interpreter::CBlockInterpreter::CBlockInterpreter() {
	instancia_id = 0;
	Nothing = std::make_shared<CBlockNothing>("nothing");
	Anything = std::make_shared<CBlockAnything>("anything");

	MetaKind = std::make_shared<CBlockKindNamed>("kind");
	MetaKindRelation = std::make_shared<CBlockKindNamed>("relation");
	MetaKindPhrase = std::make_shared<CBlockKindNamed>("phrase");
	MetaKindEntity = std::make_shared<CBlockKindNamed>("entity");
	 
	  MetaKindBoolean = std::make_shared<CBlockKindNamed>("boolean");
	  MetaKindAction = std::make_shared<CBlockKindNamed>("action");
	  MetaKindList = std::make_shared<CBlockKindNamed>("list");
	  MetaKindText = std::make_shared<CBlockKindNamed>("text");

	  MetaKindAny = std::make_shared<CBlockKindNamed>("any");



	symbols.emplace_back("kind", MetaKind);
	symbols.emplace_back("relation", MetaKindRelation );
	symbols.emplace_back("phrase", MetaKindPhrase );
	symbols.emplace_back("entity", MetaKindEntity);
	symbols.emplace_back("text", MetaKindText);
 

	symbols.emplace_back("anything", Anything);
	symbols.emplace_back("nothing", Nothing);
 

}

Interpreter::CBlockInterpreter::~CBlockInterpreter() {
}