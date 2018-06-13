#pragma once
#include <string>
#include <unordered_map>



enum VerbCj { VB, VBP,VBD,VBN, VBG , VBZ  };

typedef struct verbalConj
{
public:
	char const * verb;
	char const * base;
	VerbCj tempo;	
	//verbalConj(std::string s, VerbCj tp ) :base(s),tempo(tp){}
}verbalConj
;

enum noumCj { NN,NNS };
typedef struct noumConj
{
public:
	char const * noum;
	char const * base;
	noumCj modificador;
	 
}noumConj;


//Parser responsavel por decidir por coisas como composicoes verbais
class GrammarParser
{
public:
 


	GrammarParser();
	virtual ~GrammarParser();

	virtual void LoadVerbs() = 0 ;
	virtual void LoadNoums() = 0 ;

	virtual std::string pluralOf(std::string s) = 0 ;
	virtual std::string singularOf(std::string s) = 0 ;	 
	virtual std::string verb_concordance_time(std::string verbBase, std::string vnumber, std::string vtime) = 0;  //(single ,plural)  (past , present, future)
	virtual std::string det_concordance(std::string detBase, std::string vnumber   ) = 0;

};




class GrammarParserEn :public GrammarParser
{
public:
	GrammarParserEn() {
		GrammarParserEn::LoadVerbs();
		GrammarParserEn::LoadNoums();
	};

	virtual std::string pluralOf(std::string s)override;
	virtual std::string singularOf(std::string s) override;
private:
	virtual void LoadVerbs() override;
	virtual void LoadNoums() override;

	std::unordered_map<std::string, verbalConj> verb_map;
	std::unordered_map<std::string, noumConj> noum_map;
};