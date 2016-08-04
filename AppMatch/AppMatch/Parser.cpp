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
	//CBlock *b = new CBlockAssertion( res.matchs["ActionDescr"] , mk_HPredLiteral("Action") );
	//return std::move(ParserResult(res, b));
	return ParserResult(res);
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
	//CBlock *b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
	return std::move(ParserResult(res));
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
			return  new CBlockActionApply(new CBlockValue( res.matchs["Noum1"]->repr() ),new  CBlockValue(res.matchs["Noum2"]->repr() ));
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
			return  new CBlockActionApply(new CBlockValue(res.matchs["Noum1"]->repr()) , new CBlockValue("Nothing" ));
		}
	}

	return nullptr;

}

HPred undefinedArticle()
{
	return mkHPredBooleanOr("_", mk_HPredLiteral("a"), mk_HPredLiteral("an"));
}

CBlock* CParser::parseAssertionSecondTerm(HTerm term)
{



	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("actionpart", { undefinedArticle(), mk_HPredLiteral("action") }));
		predList.push_back(mkHPredAny("ActionApply"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return    parseAssertionActionDeclare(res.matchs["ActionApply"]);
		}

	}

	//Derivade Kind
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		auto L_a_kind_of = mkHPredList("kindpart", { undefinedArticle(), mk_HPredLiteral("kind"), mk_HPredLiteral("of") });		
		auto L_kinds_of = mkHPredList("kindpart", {  mk_HPredLiteral("kinds"), mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindpart",  L_a_kind_of , L_kinds_of ));
		predList.push_back(mkHPredAny("KindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return  new CBlockValue(res.matchs["KindBase"]->repr());
		}
	}

	//Base Kind
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredList("kindpart", { undefinedArticle(), mk_HPredLiteral("kind")  }));
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return  new CBlockValue( "Kind" );
		}
	}


	return  new CBlockValue(term->repr()); //default return

}


 
CBlockList* CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList *CList )
{
	std::vector<HPred> predList;	 
	predList.push_back(mkHPredAny("N1"));
	predList.push_back(mkHPredBooleanOr( "sep", mk_HPredLiteral(",") , mk_HPredLiteral("and")));
	predList.push_back(mkHPredAny("N2"));

	 
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		 
		CList = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["N1"], CList);
		CList = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["N2"], CList);
		
		return CList;
	}
	 
	 
	CList->push_back(new CBlockValue(term->repr())  );
	return CList;
}



CBlock* CParser::parseAssertionFirstTerm_Compose(HTerm term )
{
	CBlockList *c_list = new CBlockList();
	c_list = CParser::parseAssertionFirstTerm_COMMA_AND(term, c_list);
	if ( c_list->lista.size() == 1 )
	{
		CBlock  *rt;
		std::swap(rt, c_list->lista.front());
		delete c_list;
		return rt;
	}
	return c_list;
}


CBlock* CParser::parseAssertionFirstTerm(HTerm term)
{
	return parseAssertionFirstTerm_Compose(term);
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
		if (rs2.block != nullptr)
		{
			return rs2;
		}
	}
	return ParserResult(MatchResult());
}

  
CBlock* CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	

	std::vector<HTerm>  lst = decompose(str);
	ParserResult res = parserAssertion( lst );
	
	std::string s = get_repr(res.result);
	printf("result:\n %s \n", s.c_str());
	CBlock* retBlock = nullptr;
	std::swap(res.block, retBlock);
	return retBlock;
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
	{
		CParser parse;
		std::string phase_1 = "( book,  stone and  ( metal bird))  are   things  ";
		//auto res = parse.parser(phase_1);
		//res->dump("");
	}

	 

	{
		CParser parse;
		std::string phase_1 = "( iron, silver, chopper)  are kinds of metal  ";
		 auto res = parse.parser(phase_1);
		 res->dump("");
	}

	{
		CParser parse;
		std::string phase_1 = "metal  is a kind   ";
		auto res = parse.parser(phase_1);
		res->dump("");
	}

	return;
}

void testeParser_3()
{
	CParser parse;
	{
		std::string phase_1 = "eat  is (an action  applying to (one thing ))";
	 	auto res = parse.parser(phase_1);
		res->dump("");
	}
	{
		std::string           phase_1 = "(cut ) is    an action   applying to (one thing) and (a Cutter)   ";
		auto  res = parse.parser(phase_1);
		res->dump("");
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
	// testeParser_1();
	 testeParser_2();
	testeParser_3();
	//testeParser_4();
}