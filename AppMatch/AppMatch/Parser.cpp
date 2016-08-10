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


CParser::CParser()
{
}


CParser::~CParser()
{
}


 
CBlock* CParser::get_Noum(string named) const
{
	auto kv =  std::find_if(nregisters.begin(), nregisters.end(), [&](const NoumDefinition &a) {return   a.noum == named; });
 
	if (kv == nregisters.end()) return nullptr;
	return kv->definition ;
}

void CParser::set_Noum(NoumDefinition ndef)
{
	nregisters.push_back(ndef);
}

void CParser::set_Noum(NoumDefinitions ndef)
{
	nregisters.insert(nregisters.end(), ndef.begin(), ndef.end());
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
			return  new CBlockActionApply(new CBlockNoum( res.matchs["Noum1"]->removeArticle()->repr() ),new  CBlockNoum(res.matchs["Noum2"]->removeArticle()->repr() ));
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
			return  new CBlockActionApply(new CBlockNoum(res.matchs["Noum1"]->removeArticle()->repr()) , new CBlockNoum("Nothing" ));
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

HPred mk_What_Which()
{
	return mkHPredBooleanOr("what_TERM", mk_HPredLiteral("what"), mk_HPredLiteral("which"), mk_HPredLiteral("whether")  );
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
			if (get_Noum(res.matchs["Noum"]->removeArticle()->repr()) != nullptr)
			{
				throw res.matchs["Noum"]->removeArticle()->repr() + " ja existe ";
				return nullptr;
			}
			


			CBlockNoum  *noumAction = new CBlockNoum(res.matchs["Noum"]->removeArticle()->repr());



			CBlockAction  *anAction = new CBlockAction(noumAction);
			CBlockActionApply* act_apply = CParser::parseAssertionActionDeclare(res.matchs["ActionApply"]);


			 
			return  new CBlockAssertion_isActionOf(noumAction, anAction, act_apply);
		}

	}

	return nullptr;
}
 


CBlock* CParser::parseAssertion_isKindOf(std::vector<HTerm> term)
{

	//Derivade Kind Value
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		auto L_a_kind = mkHPredList("kindpart", { verb_IS(),undefinedArticle(), mk_HPredLiteral("kind") , mk_HPredLiteral("of"),mk_HPredLiteral("value") });		 
		
		predList.push_back(L_a_kind);


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//Noum is a compound list by Commas ???

			CBlockList *firstTerm = new CBlockList();
			firstTerm = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["Noum"], firstTerm);

			CBlockList* blcReturn = new CBlockList();

			for (auto cnoum : firstTerm->lista)
			{
				CBlockKindValue *noumKind = new CBlockKindValue(static_cast<CBlockNoum*>(cnoum)->named);
				if (get_Noum(res.matchs["Noum"]->removeArticle()->repr()) != nullptr)
				{
					throw res.matchs["Noum"]->removeArticle()->repr() + " ja existe ";
					return nullptr;
				}

				blcReturn->push_back(new CBlockAssertion_isKindOf(noumKind, new CBlockKindValue("Nothing")));
			}
			delete firstTerm;
			if (blcReturn->lista.size() == 1) return blcReturn->lista.front();
			return blcReturn;
		}
	}



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
			CBlockList* blcReturn = new CBlockList();
			//Noum is a compound list by Commas ???
			CBlockList *firstTerm = new CBlockList();
			firstTerm = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["Noum"], firstTerm);

			for (auto cnoum : firstTerm->lista  )
			{

				CBlockKind *noumKind = new CBlockKind( static_cast<CBlockNoum*>(cnoum)->named );
				if (get_Noum(res.matchs["Noum"]->removeArticle()->repr()) != nullptr)
				{
					throw res.matchs["Noum"]->removeArticle()->repr() + " ja existe ";
					return nullptr;
				}
				CBlockKind *baseKind = new CBlockKind(res.matchs["KindBase"]->removeArticle()->repr());
				blcReturn->push_back( new CBlockAssertion_isKindOf(noumKind, baseKind) );
			}
			delete firstTerm;
			if (blcReturn->lista.size() == 1) return blcReturn->lista.front();
			return blcReturn;
		}
	}

	//Kind WhiTout  Base Thing
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));

		auto L_a_kind  = mkHPredList("kindpart", { verb_IS(),undefinedArticle(), mk_HPredLiteral("kind")  });
		auto L_kinds  = mkHPredList("kindpart", { verb_IS(),mk_HPredLiteral("kinds")  });

		predList.push_back(mkHPredBooleanOr("kindpart", L_a_kind , L_kinds ));
		 
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			//Noum is a compound list by Commas ???
			 
			CBlockList *firstTerm = new CBlockList();
			firstTerm = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["Noum"], firstTerm);

			CBlockList* blcReturn = new CBlockList();

			for (auto cnoum : firstTerm->lista)
			{
				CBlockKind *noumKind = new CBlockKind(static_cast<CBlockNoum*>(cnoum)->named);
				if (get_Noum(res.matchs["Noum"]->removeArticle()->repr()) != nullptr)
				{
					throw res.matchs["Noum"]->removeArticle()->repr() + " ja existe ";
					return nullptr;
				}

				blcReturn->push_back(new CBlockAssertion_isKindOf(noumKind, new CBlockKind("Nothing")));
			}
			delete firstTerm;
			if (blcReturn->lista.size() == 1) return blcReturn->lista.front();
			return blcReturn;
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
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("valueKind"));
		predList.push_back(verb_IS());
		predList.push_back(mkHPredAny("valueNames"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			//KindValue must exist
			CBlock *valueKind = get_Noum(res.matchs["valueKind"]->removeArticle()->repr());
			if (CBlockKindValue* kindValue = dynamic_cast<CBlockKindValue*>(valueKind))
			{
				CBlockList *firstTerm = new CBlockList();
				firstTerm = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["valueNames"], firstTerm);

				CBlockList* blcReturn = new CBlockList();

				for (auto cnoum : firstTerm->lista)
				{
					CBlockNamedValue  *noumValue = new CBlockNamedValue(static_cast<CBlockNoum*>(cnoum)->named);
					blcReturn->lista.push_back(new CBlockAssertion_isNamedValueOf(noumValue, kindValue));
				}
				if (blcReturn->lista.size() == 1) return blcReturn->lista.front();
				return blcReturn;
			}


		}
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
			CBlock *valueKind = get_Noum(res.matchs["valueName"]->removeArticle()->repr());
			if (CBlockKindValue* kindValue = dynamic_cast<CBlockKindValue*>(valueKind))
			{
				CBlockList *firstTerm = new CBlockList();
				firstTerm = CParser::parseAssertionFirstTerm_COMMA_AND(res.matchs["valueName"], firstTerm);

				CBlockList* blcReturn = new CBlockList();

				for (auto cnoum : firstTerm->lista)
				{
					CBlockNamedValue  *noumValue = new CBlockNamedValue(static_cast<CBlockNoum*>(cnoum)->named);
					blcReturn->lista.push_back(new CBlockAssertion_isNamedValueOf(noumValue, kindValue));
				}
				if (blcReturn->lista.size() == 1) return blcReturn->lista.front();
				return blcReturn;
			}


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
	
	{
		// is a kind definition ??
		std::vector<HPred> predList;


		//predList.push_back(mkHPredList("initial_part", { mk_HPredLiteral("to") , mk_HPredLiteral("decide") , mk_What_Which() }));

		predList.push_back(mk_HPredLiteral("to"));
		predList.push_back(mk_HPredLiteral("decide"));
		predList.push_back(mk_What_Which());		
		
		predList.push_back(mkHPredAny("KindToReturn"));


		   auto L_is_the = mkHPredList("verb", { verb_IS(), mk_HPredLiteral("the") });
		   auto L_is = mkHPredList("verb", { verb_IS() });
		
		   predList.push_back(mkHPredBooleanOr("verb_part", verb_IS(), L_is_the));
		predList.push_back(mkHPredAny("ValueToDecide"));	
		predList.push_back(mk_HPredLiteral(":"));
		predList.push_back(mkHPredAny("RemainBody"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			CBlockMatch * noumVariable = new CBlockMatch(parseAssertion_DecideWhat( res.matchs["ValueToDecide"] ) );
			CBlockKind*         baseKind = new CBlockKind(res.matchs["KindToReturn"]->removeArticle()->repr());

			CBlock *   body =   new CBlockNoum(res.matchs["RemainBody"]->removeArticle()->repr());

			return  new CBlockToDefine(baseKind, noumVariable , body);
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
			if (get_Noum(res.matchs["VariableNoum"]->removeArticle()->repr()) != nullptr)
			{
				throw res.matchs["VariableNoum"]->removeArticle()->repr() + " ja existe ";
				return nullptr;
			}
			CBlockVariable * noumVariable = new CBlockVariable(res.matchs["VariableNoum"]->removeArticle()->repr());
			CBlockKind*         baseKind = new CBlockKind(res.matchs["KindBase"]->removeArticle()->repr());

		 


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
			CBlock* noumInstance = new CBlockNoum(res.matchs["Noum"]->removeArticle()->repr());
			CBlock* baseKind = new CBlockNoum(res.matchs["Value"]->removeArticle()->repr());
			return  new CBlockAssertion_isDirectAssign(noumInstance, baseKind);
		}
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


	CList->push_back(new CBlockNoum(term->removeArticle()->repr()));
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
	CBlock* assert_variable = CParser::parseAssertion_isVariable(lst);
	if (assert_variable != nullptr)
	{
		return assert_variable;
	}

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

	CBlock* assert_values = CParser::parseAssertion_valuesOf(lst);
	if (assert_values != nullptr)
	{
		return assert_values;
	}


	CBlock* assert_Instance = CParser::parseAssertion_isInstanceOf(lst);
	if (assert_Instance != nullptr)
	{
		return assert_Instance;
	}

	CBlock* assert_Assign = CParser::parseAssertion_DirectAssign(lst);
	if (assert_Assign != nullptr)
	{
		return assert_Assign;
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


	CBlockNoum* object_Name = new CBlockNoum(res.matchs["obj"]->removeArticle()->repr());
	return new CBlockProperty(res.matchs["property"]->removeArticle()->repr(), object_Name);
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

	CBlockNoum  *defintionFirst_Noum = new CBlockNoum(res.matchs["Target"]->removeArticle()->repr());
	if (defintionFirst_Noum != nullptr)
	{
		return   new CBlockAssertion_Noum_canBe(defintionFirst_Noum, definitionSecond);
	}

	return nullptr;
}

CBlockInstanceVariable* CParser::CProperty_called(HTerm term)
{
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kindName"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("propName"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)  
		{
			return new CBlockInstanceVariable(new CBlockNoum(res.matchs["kindName"]->removeArticle()->repr()), new CBlockNoum(res.matchs["propName"]->repr()));
		}
	
	}


	return new CBlockInstanceVariable(new CBlockNoum(term->removeArticle()->repr()), new CBlockNoum(term->removeArticle()->repr()));

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
	 
	CBlockNoum  *defintionFirst_KindOrInstance = new CBlockNoum(res.matchs["Target"]->removeArticle()->repr());
	return  new CBlockAssertion_InstanceVariable (defintionFirst_KindOrInstance,  definitionProperty_kindAndName);
}

 

  
CBlock* CParser::parser_only(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	


	std::vector<HTerm>  lst = decompose(str);

	CBlock *rblock_decide_1 = (parser_Decide_Assertion(lst));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;
	 

	CBlock *rblock_assert_1 = (parser_Declaration_Assertion (lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;

	CBlock *rblock_assert_hasA = (parser_hasAn_Assertion(lst));
	if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

	CBlock *rblock_assert_2 = (parser_canBe_Assertion(lst));
	if (rblock_assert_2 != nullptr) return rblock_assert_2;

	return nullptr;
 
}

CBlock* CParser::parser(std::string str)
{
	CBlock* block = parser_only(str);
	if (block == nullptr) return nullptr;

	auto nlist = block->noumDefinitions();
	for(auto n : nlist)
	{
		std::cout <<"NOUM :" << n.noum << std::endl;
	}
	set_Noum(nlist);

	return block;

}
