//
// Created by eraldo.rangel on 30/09/2016.
//

#ifndef APPMATCH_CDATAMANANGER_H
#define APPMATCH_CDATAMANANGER_H



#include <map>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

enum BlockType;
class CBlock;
using HBlock = std::shared_ptr<CBlock>;


class CDataManangerSave {
	int id = 0;
    std::map<CBlock*,int> blocks_saved;
	std::map<int, HBlock> blocks_loaded;
	std::map<int, std::string> string_loaded;
	//std::unique_ptr< cereal::XMLOutputArchive>  archive;
	

	std::ofstream file; ;
public:
std::unique_ptr< cereal::BinaryOutputArchive >  archive;

	void type(BlockType tp);
	void type(BlockType tp, std::string b1);
	void type(BlockType tp, std::string b1, HBlock b2, HBlock b3);
	void type(BlockType tp, std::list<HBlock> b1);
	void type(BlockType tp, std::vector<HBlock> b1);
	void type(BlockType tp, std::string b1, HBlock b2);
	void type(BlockType tp, HBlock b1);
	void type(BlockType tp, HBlock b1, HBlock b2);
	void type(BlockType tp, HBlock b1, HBlock b2, HBlock b3);
 
	void store(std::string b);
	std::list<int> store(std::list<HBlock> alist);
	std::vector<int> store(std::vector<HBlock> alist);
	int store(HBlock b);
	CDataManangerSave();
	~CDataManangerSave();
};


class CDataManangerLoad {
	int id = 0;
	std::map<CBlock*, int> blocks_saved;
	std::map<int, HBlock> blocks_loaded;
	std::map<int, std::string> string_loaded;
	//std::unique_ptr< cereal::XMLOutputArchive>  archive;
	std::unique_ptr< cereal::BinaryInputArchive >  archive;

	std::ifstream file; ;
public:


 

	std::string loadString(); 
	std::vector<HBlock> loadList(std::vector<int> alist);
	HBlock loadBlockRaw();
	HBlock loadBlock(int i);

	CDataManangerLoad();
	~CDataManangerLoad();
};



#endif //APPMATCH_CDATAMANANGER_H
