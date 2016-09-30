//
// Created by eraldo.rangel on 30/09/2016.
//

#include "CDataMananger.h"
#include "BlockInterpreter.h"
#include "serialRegister.h"
#include <fstream>


 
 void CDataManangerSave::type(BlockType tp )
{
	archive->operator()(tp);
}
 void CDataManangerSave::type(BlockType tp, string b1)
{
 
	archive->operator()(tp);
	archive->operator()(b1);
 
}

 void CDataManangerSave::type(BlockType tp, string b1 , HBlock b2, HBlock b3)
 {
	 int i2 = store(b2); 
	 int i3 = store(b3); 
 
	 archive->operator()(tp);
	 archive->operator()(b1);
	 archive->operator()(i2);
	 archive->operator()(i3);
 
 }

 void CDataManangerSave::type(BlockType tp, std::list<HBlock > b1)
{
	std::list<int > i1 = store(b1);
 
	archive->operator()(tp);
	archive->operator()(i1);
 
}

 void CDataManangerSave::type(BlockType tp, std::vector<HBlock > b1)
{
	std::vector<int > i1 = store(b1);
 
	archive->operator()(tp);
	archive->operator()(i1);
 
}


 void CDataManangerSave::type(BlockType tp, string b1 , HBlock b2 )
{
	int i2 = store(b2);
 
	archive->operator()(tp);
	archive->operator()(i2);
 
}


void CDataManangerSave::type(BlockType tp, HBlock b1 )
{
	int i1 = store(b1);
 
	archive->operator()(tp);
	archive->operator()(i1);
 
}
void CDataManangerSave::type(BlockType tp, HBlock b1, HBlock b2)
{
	int i1 = store(b1);
	int i2 = store(b2);
	 
	archive->operator()(tp);
	archive->operator()(i1);
	archive->operator()(i2);
	 
}
void CDataManangerSave::type(BlockType tp, HBlock b1, HBlock b2, HBlock b3)
{
	int i1 = store(b1);
	int i2 = store(b2);
	int i3 = store(b3);
	 
	archive->operator()(tp);
	archive->operator()(i1);
	archive->operator()(i2);
	archive->operator()(i3);
	 
}

void CDataManangerSave::store(std::string str)
{	 
	archive->operator()(str);
}
std::list< int > CDataManangerSave::store(std::list<HBlock > alist)
{
	std::list<int > refs;
	for(auto &b : alist )
	{
		int k = store(b);
		refs.push_back(k);
	}
	return refs;
}

std::vector< int > CDataManangerSave::store(std::vector<HBlock > alist)
{
	std::vector<int > refs;
	for (auto &b : alist)
	{
		int k = store(b);
		refs.push_back(k);
	}
	return refs;
}

int CDataManangerSave::store(HBlock h)
{	 

	auto p = blocks_saved.find(h.get() );
	if (p == blocks_saved.end())
	{
		id++;
		archive->operator()(id);

		blocks_saved[h.get() ] = id;
		blocks_loaded[id] = h;

		// nao esta salvo
		h->store(   this );

		return id;
	}
	else
	{
		return p->second;
	}
}

 


CDataManangerSave::CDataManangerSave()
{
	file = std::ofstream("out.xml");
	//archive = std::make_unique< cereal::XMLOutputArchive>(file);
	//cereal::BinaryOutputArchive
		archive = std::make_unique< cereal::BinaryOutputArchive>(file);
}

CDataManangerSave::~CDataManangerSave()
 {
	 archive = nullptr;
	 file.close();
 }

std::string CDataManangerLoad::loadString()
{
	std::string str;
	archive->operator()(str);
	return str;
}

std::vector<HBlock> CDataManangerLoad::loadList(std::vector<int> alist)
{
	std::vector<HBlock > refs;
	for (auto &b : alist)
	{
		auto k = loadBlock(b);
		refs.push_back(k);
	}
	return refs;
}



HBlock CDataManangerLoad::loadBlock(int i)
{
	auto p = blocks_loaded.find( i);
	if (p == blocks_loaded.end())
	{
		 
		archive->operator()(id);
		// techicamente os ids anteriores ja foram carregados
		HBlock h = loadBlockRaw();

		blocks_saved[h.get()] = id;
		blocks_loaded[id] = h;
		 

		return h;
	}
	else
	{
		return p->second;
	}


}

CDataManangerLoad::CDataManangerLoad()
{
	file = std::ifstream("out.xml");
	archive = std::make_unique< cereal::BinaryInputArchive>(file);
}

CDataManangerLoad::~CDataManangerLoad()
{
	archive = nullptr;
	file.close();
}


HBlock CDataManangerLoad::loadBlockRaw()
{
	BlockType tp;
	archive->operator()(tp);

	if (tp == BlockNoum)
	{
		string s = loadString();		
		return std::make_shared<CBlockNoum>(s);
	}

	 

	return nullptr;
	 
}