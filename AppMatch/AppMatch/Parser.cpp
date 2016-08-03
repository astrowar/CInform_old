#include "Parser.h"
#include <sstream>
#include <iostream>

std::vector<HTerm> decompose(std::string phase);;
std::string  decompose_bracket(std::string phase, std::string dlm);
HPred mk_HPredLiteral( std::string str )
{
	return mkHPredAtom("_", make_string(str ));
}


HPred mk_HPredLiteral_OR(std::string _named , std::initializer_list<std::string> alist )
{
	std::list<std::string> strList(alist);
	std::list<std::shared_ptr<CPred> > predlist;
	for(auto it = strList.begin(); it != strList.end();++it)
	{
		predlist.push_back( mkHPredAtom("_", make_string(*it)));
	}
	return std::make_shared<CPredBooleanOr>(_named, predlist ); 
}

CList*  mk_CList_Literal(std::vector<HTerm> strList )
{
	auto clist =   new CList( ) ;
	std::list<std::shared_ptr<CPred> > predlist;
	for (auto it = strList.begin(); it != strList.end(); ++it)
	{
		clist->push_back(  *it );
	}
	return clist;
}


CParser::CParser()
{
}


CParser::~CParser()
{
}



ParserResult CParser::parser_AssertionKind(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Object"));
	//predList.push_back(mkHPredAtom("Verb", make_string("is")));
	predList.push_back(mk_HPredLiteral_OR( "Verb", { "is","are" }));
	predList.push_back(mkHPredList("kindpart", { mk_HPredLiteral("a"), mk_HPredLiteral("kind"), mk_HPredLiteral("of")}));
	predList.push_back(mkHPredAny("Kind"));
	MatchResult res = CMatch(lst, predList);
	if (res.result != Equals)
	{
		return  ParserResult(res) ;
	}
	CBlock *b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
	return std::move(ParserResult(res, b));
}



ParserResult CParser::parser_SingleAssertion(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Object"));
	//predList.push_back(mkHPredAtom("Verb", make_string("is")));
	predList.push_back(mk_HPredLiteral_OR("Verb", { "is","are" }));
	predList.push_back(mkHPredAny("Asserion"));
	MatchResult res = CMatch(lst, predList);

	 


	if (res.result != Equals) return ParserResult(res);
	CBlock *b = new CBlockAssertion(res.matchs["Object"], res.matchs["Asserion"]);
	return ParserResult(res, b); 
}

ParserResult CParser::parserAssertion(std::vector<HTerm> lst)
{
	 
	ParserResult rs1 = parser_AssertionKind(lst);
	if (rs1.block != nullptr)  return rs1;

	ParserResult rs2 = parser_SingleAssertion(lst);
	if (rs2.block != nullptr)  return rs2;

	return ParserResult(MatchResult());
}

  
CBlock* CParser::parser(std::string str)
{
	std::vector<HTerm>  lst = decompose(str);
	ParserResult res = parserAssertion( lst );
	
	std::string s = get_repr(res.result);
	printf("result:\n %s \n", s.c_str());

	return res.block;
}



void testeParser()
{
	CParser parse;	
	std::string phase_1 = "(book  )is   kind   ";
	phase_1 = decompose_bracket(phase_1, "(");
	phase_1 = decompose_bracket(phase_1, ")");
	std::cout <<  phase_1  << std::endl;

	std::vector<HTerm>  lst = decompose(phase_1);
	CList* lst_ptr = mk_CList_Literal(lst);	 
	MTermSetCombinatoriaList mlist = getCombinatorias(lst_ptr->asVector(), 3);
	std::string s = get_repr(mlist);
	printf("Comb:\n %s \n", s.c_str());


	auto res = parse.parser(phase_1);

	return;
}
