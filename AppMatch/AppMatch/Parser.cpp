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

std::string get_repr(MTermSet lst);


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

HPred undefinedArticle()
{
	return mkHPredBooleanOr("_", mk_HPredLiteral("a"), mk_HPredLiteral("an"));
}
HPred verb_IS()
{
	return mkHPredBooleanOr("is", mk_HPredLiteral("are"), mk_HPredLiteral("is"));
}

HPred mk_What_Which()
{
	return mkHPredBooleanOr("what_TERM", mk_HPredLiteral("what"), mk_HPredLiteral("which"), mk_HPredLiteral("whether")  );
}
 


CParser::CParser(CBlockInterpreter* _interpreter)
{
	interpreter = _interpreter;
}

CParser::~CParser()
{
}


// 
//CBlock* CParser::get_Noum(string named) const
//{
//	auto kv =  std::find_if(nregisters.begin(), nregisters.end(), [&](const NoumDefinition &a) {return   a.noum == named; });
// 
//	if (kv == nregisters.end()) return nullptr;
//	return kv->definition ;
//}

void CParser::set_Noum(NoumDefinition ndef)
{
	nregisters.push_back(ndef);
}

void CParser::set_Noum(NoumDefinitions ndef)
{
	nregisters.insert(nregisters.end(), ndef.begin(), ndef.end());
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

CBlock* CParser::parse_AssertionAction_ApplyngTo(HTerm term)
{
	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind1"));
		predList.push_back(mk_HPredLiteral("and"));
		predList.push_back(mkHPredAny("kind2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock *n1 = parser(res.matchs["kind1"]);
			CBlock *n2 = parser(res.matchs["kind2"]);
			return  new CBlockActionApply(n1,n2 );
		}
	}


	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("two"));
		predList.push_back(mkHPredAny("kind1"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock *n1 = parser(res.matchs["kind1"]);			 
			return  new CBlockActionApply(n1, n1);
		}
	}


	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("one"));
		predList.push_back(mkHPredAny("kind1"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock *n1 = parser(res.matchs["kind1"]);
			return  new CBlockActionApply(n1, new CBlockNoum("Nothing") );
		}
	}

	return nullptr;
}

CBlock* CParser::parse_AssertionAction (std::vector<HTerm> term )
{
	
	{		 
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(undefinedArticle()); 
		predList.push_back(mk_HPredLiteral("action"));
		predList.push_back(mk_HPredLiteral("applying"));
		predList.push_back(mk_HPredLiteral("to")); 
		predList.push_back(mkHPredAny("ApplyRemainder"));	

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock *applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  new CBlockActionApply(new CBlockNoum( res.matchs["Noum1"]->removeArticle()->repr() ),new  CBlockNoum(res.matchs["Noum2"]->removeArticle()->repr() ));
			return  new CBlockActionKind("", applyTO);
		
		}
	}
	 

	return nullptr;

}



 
 


CBlock* CParser::parseAssertion_isKindOf(std::vector<HTerm> term)
{
	{
		std::vector<HPred> predList;	 
		auto a_1 = mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind") ,  mk_HPredLiteral("of") });;
		auto a_2 = mkHPredList("kindDef", { mk_HPredLiteral("kind") ,  mk_HPredLiteral("of") });
		auto a_3 = mkHPredList("kindDef", { mk_HPredLiteral("kinds") ,  mk_HPredLiteral("of") });

		predList.push_back(mkHPredBooleanOr("kindBase_l", a_1,a_2,a_3 ));

		predList.push_back(mkHPredAny("kindBase"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{		 

			return new CBlockKindOf(  res.matchs["kindBase"]->removeArticle()->repr());
		}
	}


	{
		std::vector<HPred> predList;	 
		predList.push_back(mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind")   }));
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return new CBlockKindOf(""); // no Base

		}
	}

	return nullptr;

}





CBlock* CParser::parseAssertion_valuesOf(std::vector<HTerm> term)
{
	
	// The colors are blue, green, yellow, and red.
	// The textures are rough, stubbly and smooth. 
	// Price is a kind of value.  $1.99 specifies a price.
	{
		 
	}


	// $1.99 specifies a price.
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("valueName")); 

		auto L_single = mkHPredList("spc", { mk_HPredLiteral("specifies"), undefinedArticle() });
		auto L_plural = mkHPredList("spc", { mk_HPredLiteral("specifies") });		 

		predList.push_back(mkHPredBooleanOr("spc_part", L_single , L_plural));

		predList.push_back(mkHPredAny("valueKind"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			//KindValue must exist
			

			CBlock *valueName = parser(res.matchs["valueName"] );
			CBlock *valueKind = parser(res.matchs["valueKind"] );
			return new CBlockAssertion_isNamedValueOf(valueName, valueKind);

			 


		}
	}
	return nullptr;
}


 
CBlock* CParser::parser_What_Assertion(std::vector<HTerm> term)
{
	{
		std::vector<HPred> predList;
		predList.push_back(mk_What_Which() ); 
		predList.push_back(mkHPredAny("kindReturn"));
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("RemainderQuery"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{	 
			CBlock* body = parser(res.matchs["RemainderQuery"]);
			if (body != nullptr)
			{
				return  new CBlockMatch(body);
			}
		}
	}



	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("if"));
		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock* AValue = parser(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			CBlock* BValue = parser(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			 
			return  new CBlockMatch(new CBlockAssertion_isDirectAssign(AValue, BValue));
		}
	}
	 
	return nullptr;

}

CBlock* CParser::parseAssertion_DecideWhat( HTerm  term)
{
	return new CBlockNoum(term->removeArticle()->repr());
}

CBlock* CParser::parseAssertion_isDecide(std::vector<HTerm> term)
{

	//{
	//	// is a kind definition ??
	//	std::vector<HPred> predList;


	//	//predList.push_back(mkHPredList("initial_part", { mk_HPredLiteral("to") , mk_HPredLiteral("decide") , mk_What_Which() }));

	//	predList.push_back(mk_HPredLiteral("to"));
	//	predList.push_back(mk_HPredLiteral("decide"));
	//	predList.push_back(mk_What_Which());		
	//	
	//	predList.push_back(mkHPredAny("KindToReturn"));


	//	   auto L_is_the = mkHPredList("verb", { verb_IS(), mk_HPredLiteral("the") });
	//	   auto L_is = mkHPredList("verb", { verb_IS() });		
	//	   predList.push_back(mkHPredBooleanOr("verb_part", verb_IS(), L_is_the));


	//	predList.push_back(mkHPredAny("ValueToDecide"));	
	//	predList.push_back(mk_HPredLiteral(":"));
	//	predList.push_back(mkHPredAny("RemainBody"));
	//	MatchResult res = CMatch(term, predList);

	//	if (res.result == Equals)
	//	{
	//		CBlockMatch * noumVariable = new CBlockMatch(parseAssertion_DecideWhat( res.matchs["ValueToDecide"] ) );
	//		CBlockKind*         baseKind = new CBlockKind(res.matchs["KindToReturn"]->removeArticle()->repr());

	//		CBlock *   body =   new CBlockNoum(res.matchs["RemainBody"]->removeArticle()->repr());

	//		return  new CBlockToDefine(baseKind, noumVariable , body);
	//	}
	//}

	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mk_HPredLiteral("decide"));
		predList.push_back(mkHPredAny("Match"));
		predList.push_back(mk_HPredLiteral(":"));
		predList.push_back(mkHPredAny("RemainBody"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock* a_match =  parser(res.matchs["Match"]);
			CBlock* body = parser(res.matchs["RemainBody"] );

			return  new CBlockToDecide(a_match, body);
		}
	}


	return nullptr;
}

CBlock* CParser::parseAssertion_isVariable(std::vector<HTerm> term)
{

	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("VariableNoum"));

		auto L_a_an_kind = mkHPredList("kindpart", { verb_IS(), undefinedArticle() });
		auto L_are_kinds = mkHPredList("kindpart", { verb_IS() });

		predList.push_back(mkHPredBooleanOr("kindpart", L_a_an_kind, L_are_kinds));

		predList.push_back(mkHPredAny("KindBase"));
		predList.push_back(mkHPredList("variable", { mk_HPredLiteral("that"), mk_HPredLiteral("varies") })); 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			 
			CBlock * noumVariable = parser(res.matchs["VariableNoum"]  );
			CBlock*   baseKind = parser(res.matchs["KindBase"]  );
			return  new CBlockAssertion_isVariable(noumVariable, baseKind);
		}
	}
	return nullptr;

}

 
CBlockAssertion_isDirectAssign   * CParser::parseAssertion_DirectAssign(std::vector<HTerm> term)
{

	 


	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		auto L_a_an_kind = mkHPredList("verb", { verb_IS()  });  
		predList.push_back(L_a_an_kind);
		predList.push_back(mkHPredAny("Value"));


		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{			 
			CBlock* noum = parser(res.matchs["Noum"] );
			if (noum == nullptr) return nullptr;
			CBlock* value = parser(res.matchs["Value"] );
			if (value == nullptr) return nullptr;
			return  new CBlockAssertion_isDirectAssign(noum, value);
		}
	}
	return nullptr;

}

 
CBlock*  CParser::parse_List_AND(std::vector<HTerm> term)
{
	{
		auto sep = mk_HPredLiteral("and");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockList *cList = new CBlockList();
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
			return cList;
		}
	}

	{
		auto sep = mk_HPredLiteral("or");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return nullptr;
		}
	}
	{
		auto sep = mk_HPredLiteral(",");
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(sep);
		predList.push_back(mkHPredAny("N2"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockList *cList = new CBlockList();
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
			return cList;
		}
	}



	return nullptr;

}

CBlock*  CParser::parse_noum(std::vector<HTerm> term)
{
	std::vector<HPred> predList;
	
	



	//predList.push_back(undefinedArticle());
	predList.push_back(mkHPredAny("Noum"));
	MatchResult res = CMatch(term, predList);

	if (res.result == Equals)
	{
		return new CBlockNoum("*" + res.matchs["Noum"]->removeArticle()->repr());
	}
	return nullptr;
}

CBlockAssertion_isInstanceOf  * CParser::parseAssertion_isInstanceOf(std::vector<HTerm> term)  
{
	//Injstance is Alwares derivadefrom a Kind
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));

		auto L_a_an_kind = mkHPredList("kindpart", { verb_IS(), undefinedArticle()  });	
		auto L_are_kinds = mkHPredList("kindpart", { verb_IS() });

		//predList.push_back(mkHPredBooleanOr("kindpart", L_a_an_kind, L_are_kinds));
		predList.push_back(L_a_an_kind);

		predList.push_back(mkHPredAny("KindBase"));
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			/*if (get_Noum(res.matchs["Noum"]->repr()) != nullptr)
			{
				throw res.matchs["Noum"]->repr() + " ja existe ";
				return nullptr;
			}
			*/
			CBlockInstance* noumInstance = new CBlockInstance (res.matchs["Noum"]->removeArticle()->repr());
			CBlockKind*         baseKind = new CBlockKind(res.matchs["KindBase"]->removeArticle()->repr());
		 
			return  new CBlockAssertion_isInstanceOf(noumInstance, baseKind);
		}
	}
	return nullptr;

}
 
 

 
CBlockList* CParser::parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep )
{
	
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("N1"));
	predList.push_back(sep);
	predList.push_back(mkHPredAny("N2"));
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		CBlockList *cList = new CBlockList();
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
		return cList;
	}
	return nullptr;
}
CBlockList* CParser::parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, CBlockList *cList)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("N1"));
	predList.push_back(mkHPredBooleanOr("sep", mk_HPredLiteral(","), sep));
	predList.push_back(mkHPredAny("N2"));


	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep,cList);
		return cList;
	}

	CBlock *ret = parser(term);
	cList->push_back(ret);
	//cList->push_back(new CBlockNoum(  term->removeArticle()->repr()));
	return cList;
}
 
CBlockList* CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, CBlockList *CList )
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("and"), CList);
}

CBlockList* CParser::parseAssertionFirstTerm_COMMA_OR(HTerm term, CBlockList *CList)
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("or"), CList); 
}

CBlockList* CParser::parse_Strict_COMMA_AND(HTerm term )
{
	return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("and") );
}

CBlockList* CParser::parse_Strict_COMMA_OR(HTerm term )
{
	return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("or") );
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
CBlock* CParser::parser_Decide_Assertion(std::vector<HTerm> lst)
{
	CBlock* assert_decide = CParser::parseAssertion_isDecide(lst);
	if (assert_decide != nullptr)
	{
		return assert_decide;
	}
	return nullptr;

}
CBlock* CParser::parser_Declaration_Assertion(std::vector<HTerm> lst)
{

	CBlock* action_Assign = CParser::parse_AssertionAction (lst);
	if (action_Assign != nullptr)
	{
		return action_Assign;
	}


	CBlock* assert_variable = CParser::parseAssertion_isVariable(lst);
	if (assert_variable != nullptr)
	{
		return assert_variable;
	}

	 

	CBlock* assert_kindof= CParser::parseAssertion_isKindOf(lst);
	if (assert_kindof != nullptr)
	{
		return assert_kindof;
	}

	CBlock* assert_values = CParser::parseAssertion_valuesOf(lst);
	if (assert_values != nullptr)
	{
		return assert_values;
	}


	 

	CBlock* assert_Assign = CParser::parseAssertion_DirectAssign(lst);
	if (assert_Assign != nullptr)
	{
		return assert_Assign;
	}

	 



	return nullptr;
	 
}

CBlockProperty* CParser::parse_PropertyOf(std::vector<HTerm> term)
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

	CBlock *a =   parser( res.matchs["property"]  );
	if (a == nullptr) return nullptr;
	CBlock *b = parser( res.matchs["obj"]  );
	if (b == nullptr) return nullptr;
 



	//CBlockNoum* object_Name = new CBlockNoum(res.matchs["obj"]->removeArticle()->repr());
	return new CBlockProperty(a, b);
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

	/*CBlockProperty  *defintionFirst_property = parseAssertion_PropertyFirstTerm(res.matchs["Target"]);
	if (defintionFirst_property != nullptr)
	{
		return  new CBlockAssertion_property_canBe(defintionFirst_property, definitionSecond);
	}*/

	//CBlockNoum  *defintionFirst_Noum = new CBlockNoum(res.matchs["Target"]->removeArticle()->repr());

	CBlock* defintionFirst_Noum = parser(res.matchs["Target"]);
	if (defintionFirst_Noum != nullptr)
	{
		return   new CBlockAssertion_canBe(defintionFirst_Noum, definitionSecond);
	}

	return nullptr;
}

CBlockInstanceVariable* CParser::CProperty_called(HTerm term)
{
	{
		// the torch has a brightness called brightnessLevel ;
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kindName"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("propName"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  
		{
			CBlock *a = parser(res.matchs["kindName"]);
			CBlock *b = parser(res.matchs["propName"]);
			return new CBlockInstanceVariable(a,b );
		}
	
	}


	// the torch has a brightness   ;  -> called brightness
	CBlock *a = parser(term);	 
	return new CBlockInstanceVariable(a, a); 
	 

}


CBlock* CParser::parser_hasAn_Assertion(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Target"));	
	predList.push_back(mk_HPredLiteral("has"));
	predList.push_back(undefinedArticle() );
	predList.push_back(mkHPredAny("KindAndName"));
	MatchResult res = CMatch(lst, predList);

	if (res.result != Equals)
	{
		return nullptr;
	}

	CBlockInstanceVariable  *  definitionProperty_kindAndName = CProperty_called(res.matchs["KindAndName"]);
	if (definitionProperty_kindAndName == nullptr)
	{
		return nullptr;
	}	

	//CBlockNoum  *defintionFirst_KindOrInstance = new CBlockNoum( res.matchs["Target"]->removeArticle()->repr());
	CBlock   *defintionFirst_KindOrInstance =  parser(res.matchs["Target"] );

	return  new CBlockAssertion_InstanceVariable (defintionFirst_KindOrInstance,  definitionProperty_kindAndName);
}

 
 
CBlock* CParser::parser_only(std::vector<HTerm> lst)
{
	//str = decompose_bracket(str, "(");
	//str = decompose_bracket(str, ")");
	//str = decompose_bracket(str, ",");
	// 
	//std::vector<HTerm>  lst = decompose(str);

	CBlock *rblock_decide_1 = (parser_Decide_Assertion(lst));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;
	 
	CBlock *rblock_what_1 = (parser_What_Assertion(lst));
	if (rblock_what_1 != nullptr) return rblock_what_1;


	CBlock *rblock_assert_1 = (parser_Declaration_Assertion (lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;

	CBlock *rblock_assert_hasA = (parser_hasAn_Assertion(lst));
	if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

	CBlock *rblock_assert_2 = (parser_canBe_Assertion(lst));
	if (rblock_assert_2 != nullptr) return rblock_assert_2;

 
	CBlock* noum_propOF = CParser::parse_PropertyOf(lst);
	if (noum_propOF != nullptr)
	{
		return noum_propOF;
	}

 

	CBlock* noumList_Assign = CParser::parse_List_AND(lst);
	if (noumList_Assign != nullptr)
	{
		return noumList_Assign;
	}



	CBlock* noum_Assign = CParser::parse_noum(lst);
	if (noum_Assign != nullptr)
	{
		return noum_Assign;
	}


	return nullptr;
 
}
CBlock* CParser::parser(HTerm term)
{
	if (CList  * vlist = dynamic_cast<CList*>(term.get()))
	{
		auto r =  parser_only(vlist->asVector());
		if (r == nullptr)
			std::cout << term->repr() << std::endl;

		return r;
	}

	return new CBlockNoum(  term->removeArticle()->repr());
	
	
}

CBlock* CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");

	std::vector<HTerm>  lst = decompose(str);
	return  parser_only(lst);
	 

}
