//
// Created by eraldo on 26/06/2018.
//

#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "BlockInterpreter.hpp"
#include "CBlockInterpreterBase.hpp"

Interpreter::CBlockInterpreter::CBlockInterpreter(LanguageDepend* language )
{
    this->language = language;
	instancia_id = 0;
	Nothing = std::make_shared<CBlockNothing>(language->getNothing());
	Anything = std::make_shared<CBlockAnything>(language->getAnything());
	MetaKind = std::make_shared<CBlockKindNamed>(language->getMetaKind());
	MetaKindRelation = std::make_shared<CBlockKindNamed>(language->getMetaKindRelation());
	MetaKindPhrase = std::make_shared<CBlockKindNamed>(language->getMetaKindPhrase());
	MetaKindEntity = std::make_shared<CBlockKindNamed>(language->getMetaKindEntity());
	MetaKindBoolean = std::make_shared<CBlockKindNamed>(language->getMetaKindBoolean());
	MetaKindAction = std::make_shared<CBlockKindNamed>(language->getMetaKindAction());
	MetaKindList = std::make_shared<CBlockKindNamed>(language->getMetaKindList());
	MetaKindText = std::make_shared<CBlockKindNamed>(language->getMetaKindText());
	MetaKindAny = std::make_shared<CBlockKindNamed>(language->getMetaKindAny());



	symbols.emplace_back(language->getMetaKind(), MetaKind);
	symbols.emplace_back(language->getMetaKindRelation(), MetaKindRelation );
	symbols.emplace_back(language->getMetaKindPhrase(), MetaKindPhrase );
	symbols.emplace_back(language->getMetaKindEntity(), MetaKindEntity);
	symbols.emplace_back(language->getMetaKindText(), MetaKindText);
 

	symbols.emplace_back(language->getAnything(), Anything);
	symbols.emplace_back(language->getNothing(), Nothing);
 

}

Interpreter::CBlockInterpreter::~CBlockInterpreter() {
}


Interpreter::CBlockInterpreter   Interpreter::CBlockInterpreter::clone()
{
	return Interpreter::CBlockInterpreter(this->language);
}