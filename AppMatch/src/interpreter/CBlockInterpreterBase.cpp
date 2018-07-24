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
	MetaKindText = std::make_shared<CBlockKindValue>(language->getMetaKindText());
	MetaKindAny = std::make_shared<CBlockKindNamed>(language->getMetaKindAny());



	symbols.add(language->getMetaKind(), MetaKind);
	symbols.add(language->getMetaKindRelation(), MetaKindRelation );
	symbols.add(language->getMetaKindPhrase(), MetaKindPhrase );
	symbols.add(language->getMetaKindEntity(), MetaKindEntity);
	symbols.add(language->getMetaKindText(), MetaKindText);
 

	symbols.add(language->getAnything(), Anything);
	symbols.add(language->getNothing(), Nothing);
 

	{
		HBlockNoum nVerb = std::make_shared<CBlockNoumStr>("matches");
		HBlockNoum nPred = std::make_shared<CBlockNoumStr>("in");
		HBlockMatchNamed marg1 = std::make_shared<CBlockMatchNamed>("RGX", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));
		HBlockMatchNamed marg2 = std::make_shared<CBlockMatchNamed>("TXT", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));
		HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(nVerb, nullptr, nPred, marg1, marg2);
		this->system_phrases.push_back(nheader);
	}

}

Interpreter::CBlockInterpreter::~CBlockInterpreter() {
}


Interpreter::CBlockInterpreter   Interpreter::CBlockInterpreter::clone()
{
	return Interpreter::CBlockInterpreter(this->language);
}



void Interpreter::SymbolPool::add(string s , HBlock b)
{
	this->_symbols.push_back(std::pair<string, HBlock>(s, b));
}
std::list< std::pair<string, HBlock> > Interpreter::SymbolPool::list()
{
	return this->_symbols;
}

bool Interpreter::SymbolPool::exist( LanguageDepend *p, string s)
{
	for (auto q : this->_symbols)
	{
		if (p->isSameString(q.first, s)) return true;
		
	}
	return false;
}
