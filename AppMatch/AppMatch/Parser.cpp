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

ParserResult CParser::parser_AssertionAction(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("ActionDescr"));
	predList.push_back(mk_HPredLiteral_OR("Verb", { "is"  }));
	//predList.push_back(mkHPredAtom("Verb", make_string("is")));
	predList.push_back(mkHPredList("actionDecl", { mk_HPredLiteral("an"), mk_HPredLiteral("action")  })); 
	MatchResult res = CMatch(lst, predList);
	if (res.result != Equals)
	{
		return  ParserResult(res);
	}
	CBlock *b = new CBlockAssertion( res.matchs["ActionDescr"] , mk_HPredLiteral("Action") );
	return std::move(ParserResult(res, b));
}

ParserResult CParser::parser_AssertionKind(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Object"));	 
	predList.push_back(mk_HPredLiteral_OR( "Verb", { "is","are" }));
	//predList.push_back(mkHPredAtom("Verb", make_string("is")));
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

CBlock* CParser::parseAssertionActionDeclare(HTerm term)
{
	
	{
		 
		// applying to one visible thing and requiring light
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("acDeclr", { mk_HPredLiteral("applying"), mk_HPredLiteral("to")  }));		
		predList.push_back(mkHPredAny("Noum1"));	
		predList.push_back(mk_HPredLiteral("and"));
		predList.push_back(mkHPredAny("Noum2"));
		 


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return  new CBlockActionApply(res.matchs["Noum1"]->repr() , res.matchs["Noum2"]->repr() );
		}
	}
	{
		// Hanging up is an action applying to one thing. 
		 
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("acDeclr", { mk_HPredLiteral("applying"), mk_HPredLiteral("to") }));
		predList.push_back(mkHPredAny("Noum1")); 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return  new CBlockActionApply(res.matchs["Noum1"]->repr() ,"Nothing" );
		}
	}

	return nullptr;

}

CBlock* CParser::parseAssertionSecondTerm(HTerm term)
{
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("kindpart", { mk_HPredLiteral("a"), mk_HPredLiteral("kind"), mk_HPredLiteral("of") }));
		predList.push_back(mkHPredAny("Kind"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return  new CBlockValue(res.matchs["Kind"]->repr());
		}		
	}


	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("actionpart", { mk_HPredLiteral("an"), mk_HPredLiteral("action")  }));
		predList.push_back(mkHPredAny("ActionApply"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return    parseAssertionActionDeclare(res.matchs["ActionApply"] );
		}
		 
	}
	return  new CBlockValue(term->repr()); //default return
	 
}

CBlock* CParser::parseAssertionFirstTerm(HTerm term)
{
	return new CBlockValue(term->repr());
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

	CBlock *definitionSecond = parseAssertionSecondTerm(res.matchs["Asserion"]);
	if (definitionSecond == nullptr) return ParserResult(res);
	CBlock *defintionFirst = parseAssertionFirstTerm(res.matchs["Object"]);
	if (defintionFirst == nullptr) return ParserResult(res);
	CBlock *b = new CBlockAssertion(defintionFirst, definitionSecond );
	return ParserResult(res, b); 
}

ParserResult CParser::parserAssertion(std::vector<HTerm> lst)
{
	/*{
		ParserResult rs_action = parser_AssertionAction(lst);
		if (rs_action.block != nullptr)  return rs_action;
	}
	{
		ParserResult rs1 = parser_AssertionKind(lst);
		if (rs1.block != nullptr)  return rs1;
	}*/
	{
		ParserResult rs2 = parser_SingleAssertion(lst);
		if (rs2.block != nullptr)  return rs2;
	}
	return ParserResult(MatchResult());
}

  
CBlock* CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	std::vector<HTerm>  lst = decompose(str);
	ParserResult res = parserAssertion( lst );
	
	std::string s = get_repr(res.result);
	printf("result:\n %s \n", s.c_str());

	return res.block;
}

void testeParser_1()
{
	std::string phase_1 = "(red  book)    is a kind of    thing  ";
	phase_1 = "(  book stone and ( metal bird ) )  is    a  thing  ";
	phase_1 = decompose_bracket(phase_1, "(");
	phase_1 = decompose_bracket(phase_1, ")");
	std::cout << phase_1 << std::endl;

	std::vector<HTerm>  lst = decompose(phase_1);
	CList* lst_ptr = mk_CList_Literal(lst);
	std::cout << lst_ptr->repr() << std::endl;
	MTermSetCombinatoriaList mlist = getCombinatorias(lst_ptr->asVector(), 3);
	std::cout << get_repr(mlist) <<std::endl;
}

void testeParser_2()
{
	CParser parse;	
	std::string phase_1 = "(  book  stone   ( metal bird))  are   things  "; 
	auto res = parse.parser(phase_1); 
	return;
}

void testeParser_3()
{
	CParser parse;
	{
		std::string phase_1 = "eat  is an action  applying to one thing ";
	//	auto res = parse.parser(phase_1);
	}
	{
		std::string           phase_1 = "cut  is (an action  applying to one thing and a Cutter) ";
		auto  res = parse.parser(phase_1);
	}
	return;
}

void testeParser_4()
{
	CParser parse;
	std::string phase_1 = "define one as a number";
	auto res = parse.parser(phase_1);
	return;
}


void testeParser ()
{
	 testeParser_1();
	testeParser_2();
	testeParser_3();
	testeParser_4();
}