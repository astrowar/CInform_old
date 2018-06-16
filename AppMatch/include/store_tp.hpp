#ifndef STORE_TP_HPP
#define STORE_TP_HPP
#include <string>
#include "BlockInterpreter.hpp"
#include <map>

class LoadContext
{
	std::string data;
	int cursor;

public:
	LoadContext(std::string _data);
	std::string   get_line();
	std::string   load_item();
	std::string   load_string();	 
	int  load_int();	 
	float  load_float();
	bool   load_bool();	 
	BlockType load_type();	 
	void new_line();	 
	bool end_file();	 
	std::map<int, CBlocking::HBlock> cache;
};

CBlocking::HBlock load_line(LoadContext *ctx);
CBlocking::HBlock load_file(LoadContext *ctx);

#endif // STORE_TP_HPP
