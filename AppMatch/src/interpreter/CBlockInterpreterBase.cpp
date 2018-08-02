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


	MetaKind = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKind()));
	MetaKindRelation = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindRelation()));
	MetaKindPhrase = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindPhrase()));
	MetaKindEntity = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindEntity()));
	MetaKindBoolean = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindBoolean()));
	MetaKindAction = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindAction()));
	MetaKindList = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindList()));
	MetaKindAny = std::make_shared<CBlockKindNamed>(std::make_shared<CBlockNoumStr>(language->getMetaKindAny()));

   MetaKindText = std::make_shared<CBlockKindValue>(language->getMetaKindText());

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



void Interpreter::SymbolPool::add(HBlockNoum s , HBlock b)
{
	//verifica se ja existe
	for (auto j : this->_symbols)
	{
		if (j.first->named() == s->named())
		{
			printf("Duplicate !\n");
		}
	}
	this->_symbols.push_back(std::pair<HBlockNoum, HBlock>(s, b));
}

void Interpreter::SymbolPool::add(string s, HBlock b)
{
	this->add(std::make_shared<CBlockNoumStr>(s), b);
}


std::list< std::pair<HBlockNoum, HBlock> > Interpreter::SymbolPool::list()
{
	return this->_symbols;
}

bool Interpreter::SymbolPool::exist( LanguageDepend *p, HBlockNoum s)
{
	for (auto q : this->_symbols)
	{
		if (p->isSameNoum(q.first, s)) return true;
		
	}
	return false;
}
