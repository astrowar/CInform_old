#include "Parser.h"
#include <sstream>
#include <iostream>
#include <algorithm>

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

CBlockActionApply* CParser::parseAssertionActionDeclare( HTerm   term)
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
			return  new CBlockActionApply(new CBlockNoum( res.matchs["Noum1"]->repr() ),new  CBlockNoum(res.matchs["Noum2"]->repr() ));
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
			return  new CBlockActionApply(new CBlockNoum(res.matchs["Noum1"]->repr()) , new CBlockNoum("Nothing" ));
		}
	}

	return nullptr;

}

HPred undefinedArticle()
{
	return mkHPredBooleanOr("_", mk_HPredLiteral("a"), mk_HPredLiteral("an"));
}
HPred verb_IS()
{
	return mkHPredBooleanOr("is", mk_HPredLiteral("are"), mk_HPredLiteral("is"));
}

CBlockAssertion_isActionOf* CParser::parseAssertion_isAction(std::vector<HTerm> term)
{

	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(mkHPredList("actionpart", { verb_IS(),  undefinedArticle(), mk_HPredLiteral("action") }));
		predList.push_back(mkHPredAny("ActionApply"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockNoum  *noumAction = new CBlockNoum(res.matchs["Noum"]->repr());
			CBlockAction  *anAction = new CBlockAction(noumAction);
			CBlockActionApply* act_apply = CParser::parseAssertionActionDeclare(res.matchs["ActionApply"]);
			return  new CBlockAssertion_isActionOf(noumAction, anAction, act_apply);
		}

	}

	return nullptr;
}
 


CBlockAssertion_isKindOf * CParser::parseAssertion_isKindOf(std::vector<HTerm> term)
{
	//Derivade Kind
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));

		auto L_a_kind_of = mkHPredList("kindpart", { verb_IS(),undefinedArticle(), mk_HPredLiteral("kind"), mk_HPredLiteral("of") });
		auto L_kinds_of = mkHPredList("kindpart", { verb_IS(),mk_HPredLiteral("kinds"), mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindpart", L_a_kind_of, L_kinds_of));
		predList.push_back(mkHPredAny("KindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockKind *noumKind = new CBlockKind(res.matchs["Noum"]->repr());
			CBlockKind *baseKind = new CBlockKind(res.matchs["KindBase"]->repr());
			return  new CBlockAssertion_isKindOf(noumKind, baseKind);
		}
	}
	return nullptr;

}

CBlockAssertion_isInstanceOf  * CParser::parseAssertion_isInstanceOf(std::vector<HTerm> term) const
{
	//Derivade Kind
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));

		auto L_a_kind_of = mkHPredList("kindpart", { verb_IS(),undefinedArticle(), mk_HPredLiteral("kind"), mk_HPredLiteral("of") });
		auto L_kinds_of = mkHPredList("kindpart", { verb_IS(),mk_HPredLiteral("kinds"), mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindpart", L_a_kind_of, L_kinds_of));
		predList.push_back(mkHPredAny("KindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockInstance* noumInstance = new CBlockInstance (res.matchs["Noum"]->repr());
			CBlockKind*         baseKind = new CBlockKind(res.matchs["KindBase"]->repr());
			return  new CBlockAssertion_isInstanceOf(noumInstance, baseKind);
		}
	}
	return nullptr;

}
 
 



CBlockList* CParser::parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlockList *CList)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("N1"));
	predList.push_back(mkHPredBooleanOr("sep", mk_HPredLiteral(","), sep));
	predList.push_back(mkHPredAny("N2"));


	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{

		CList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, CList);
		CList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep,CList);

		return CList;
	}


	CList->push_back(new CBlockNoum(term->repr()));
	return CList;
}
 
CBlockList* CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList *CList )
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("and"), CList);
}

CBlockList* CParser::parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlockList *CList)
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("or"), CList); 
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


CBlock* CParser::parseAssertionEnumSecondTerm(HTerm term)
{
	CBlockList *c_list = new CBlockList();
	c_list = CParser::parseAssertionFirstTerm_COMMA_OR(term, c_list);
	if (c_list->lista.size() == 1)
	{
		CBlock  *rt;
		std::swap(rt, c_list->lista.front());
		delete c_list;
		return rt;
	}
	return c_list;
}

CBlock* CParser::parser_Declaration_Assertion(std::vector<HTerm> lst)
{
	 

	CBlock* assert_action = CParser::parseAssertion_isAction(lst);
	if (assert_action!= nullptr )
	{
		 return assert_action;
	}

	CBlock* assert_kindof= CParser::parseAssertion_isKindOf(lst);
	if (assert_kindof != nullptr)
	{
		return assert_kindof;
	}


	CBlock* assert_Instance = CParser::parseAssertion_isInstanceOf(lst);
	if (assert_Instance != nullptr)
	{
		return assert_Instance;
	}

	return nullptr;
	 
}

CBlockProperty* CParser::parseAssertion_PropertyFirstTerm(HTerm term)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("property"));
	predList.push_back(mk_HPredLiteral("of"));	
	predList.push_back(mkHPredAny("obj"));
	MatchResult res = CMatch(term, predList);
	if (res.result != Equals)
	{
		return nullptr;
	}


	CBlockNoum* object_Name = new CBlockNoum(res.matchs["obj"]->repr());
	return new CBlockProperty(res.matchs["property"]->repr(), object_Name);
}



CBlockEnums* CParser::parseAssertion_EnumTerms( HTerm  enumList )
{

	CBlockList*  elist = new CBlockList();
	elist = parseAssertionFirstTerm_COMMA_OR(enumList, elist );
	if (elist->lista.empty())
	{
		return nullptr;
	}

	std::vector<CBlockNoum*> nlist;
	std::for_each(elist->lista.begin(), elist->lista.end(),   [&nlist](CBlock* c) { nlist.push_back( dynamic_cast<CBlockNoum*>(c)); });
	return new CBlockEnums(nlist);

}

CBlock* CParser::parser_canBe_Assertion(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Target")); 
	predList.push_back(mk_HPredLiteral("can"));
	predList.push_back(mk_HPredLiteral("be"));
	predList.push_back(mkHPredAny("EnumValues"));
	MatchResult res = CMatch(lst, predList);

	if (res.result != Equals) return nullptr ;

	CBlockEnums *definitionSecond = parseAssertion_EnumTerms(res.matchs["EnumValues"]);
	if (definitionSecond == nullptr)
	{
		return nullptr;
	}

	CBlockProperty  *defintionFirst_property = parseAssertion_PropertyFirstTerm(res.matchs["Target"]);
	if (defintionFirst_property != nullptr)
	{
		return  new CBlockAssertion_property_canBe(defintionFirst_property, definitionSecond);
	}

	CBlockNoum  *defintionFirst_Noum = new CBlockNoum(res.matchs["Target"]->repr());
	if (defintionFirst_Noum != nullptr)
	{
		return   new CBlockAssertion_Noum_canBe(defintionFirst_Noum, definitionSecond);
	}

	return nullptr;
}

CBlock* CParser::CProperty_called(HTerm term)
{
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kindName"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("propName"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) return nullptr;
		{
			return new CBlockInstanceVariable(res.matchs["KindAndName"]->repr(), res.matchs["propName"]->repr());
		}
	}

	 
		return new CBlockInstanceVariable(term->repr(), term->repr());
	 


}


CBlock* CParser::parser_hasAn_Assertion(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Target"));	
	predList.push_back(mk_HPredLiteral("has"));
	predList.push_back(undefinedArticle() );
	predList.push_back(mkHPredAny("KindAndName"));
	MatchResult res = CMatch(lst, predList);

	if (res.result != Equals) return nullptr;

	CBlock  *  definitionProperty_kindAndName = CProperty_called(res.matchs["KindAndName"]);
	if (definitionProperty_kindAndName == nullptr) return nullptr;
	 
	CBlockNoum  *defintionFirst_KindOrInstance = new CBlockNoum(res.matchs["Target"]->repr());
	return  new CBlockAssertion_InstanceVariable (defintionFirst_KindOrInstance,  definitionProperty_kindAndName);
}

 

  
CBlock* CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	


	std::vector<HTerm>  lst = decompose(str);

	CBlock *rblock_assert_1 = (parser_Declaration_Assertion (lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;

	CBlock *rblock_assert_2 = (parser_canBe_Assertion(lst));
	if (rblock_assert_2 != nullptr) return rblock_assert_2;

	return nullptr;
 
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
	{
		std::string phase_1 = "A thing can be discovered or secret";
		auto res = parse.parser(phase_1);
		res->dump("");
	}

	{
		std::string phase_1 = "(size of Book ) can be normal , huge or  small";
		auto res = parse.parser(phase_1);
		res->dump("");
	}

	

	//"Brightness is a kind of value";
	//"The brightnesses are guttering, weak, radiant and blazing";
	//"The torch has a brightness";
	//	"The torch	is blazing";
	//"The torch is lit";
	return;
}


void testeParser ()
{
	// testeParser_1();
	// testeParser_2();
	//testeParser_3();
	 testeParser_4();
}