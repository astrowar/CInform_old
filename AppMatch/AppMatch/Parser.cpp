#include "Parser.h"
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<HTerm> decompose(std::string phase);;
std::string  decompose_bracket(std::string phase, std::string dlm);
MTermSet remove_boundaryListMark(MTermSet& m);
HPred mk_HPredLiteral( std::string str )
{
	return mkHPredAtom("_", make_string(str ));
}

std::string get_repr(MTermSet lst);


std::string get_repr(std::vector<HPred> plist)
{
	std::string ret = "";
	for (auto p : plist)
	{
		ret += p->repr();
	}
	return ret;
}

HTerm expandBract(HTerm term)
{
	if (CList* clist = dynamic_cast<CList*>(term.get()))
	{
		if (clist->lst.front()->is_openBracket() && clist->lst.back()->is_closeBracket())
		{
			auto vlist = clist->asVector();
			vlist = remove_boundaryListMark(vlist);
			CList* cnew = new CList();
			cnew->lst = std::list<HTerm>(vlist.begin(), vlist.end());
			return std::shared_ptr<CList>(cnew);
		}
		else
		{
			return term;
		}
	}
	return term;
}

std::vector<HTerm> get_tail(std::vector<HTerm>& qlist)
{
	std::vector<HTerm> v;
	bool front = true;
	for(auto it = qlist.begin(); it!= qlist.end(); ++it)
	{
		if (front == false) { v.push_back(*it); }
		front = false;
	}
	return v;
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

HPred undefinedArticle()
{
	return mkHPredBooleanOr("_", mk_HPredLiteral("a"), mk_HPredLiteral("an") ) ;
}
HPred verb_IS()
{
	return mkHPredBooleanOr("is", mk_HPredLiteral("are"), mk_HPredLiteral("is"));
}

HPred verb_IS_NOT()
{
	return mkHPredBooleanOr("isnot", mkHPredList("isNotList",{ mk_HPredLiteral("is") , mk_HPredLiteral("not") })  , mk_HPredLiteral("arent"));
}

HPred mk_What_Which()
{
	return mkHPredBooleanOr("what_TERM", mk_HPredLiteral("what"), mk_HPredLiteral("which"), mk_HPredLiteral("whether")  );
}


staticDispatchEntry::staticDispatchEntry(CBlockMatchList* _argumentsMatch, CBlock* _action): entryArguments (_argumentsMatch), action(_action)
{

}
staticDispatchEntry::staticDispatchEntry( ) : entryArguments(nullptr), action(nullptr)
{

}

 

SentenceDispatchPredicate::SentenceDispatchPredicate(std::vector<HPred> _matchPhase, CBlockMatch* _matchPhaseDynamic, int _entryId): matchPhase(_matchPhase), _matchPhaseDynamic(_matchPhaseDynamic),  entryId(_entryId)
{

}

CParser::CParser(CBlockInterpreter* _interpreter)
{
	interpreter = _interpreter;
	{
		std::list<HPred> alist;
		verbList = std::make_shared<CPredBooleanOr>("verbList", alist);
		verbList->blist.push_back(mk_HPredLiteral("contains"));
	}

	{
		std::list<HPred> alist;
		actionPredList = std::make_shared<CPredBooleanOr>("actionList", alist);
		actionPredList->blist.push_back(mk_HPredLiteral("getting"));
	}


	{
		std::list<HPred> alist;
		//actionDinamicDispatch = std::make_shared<CPredBooleanOr>("actionList", alist);
		//actionDinamicDispatch->blist.push_back(mk_HPredLiteral("getting"));
	}
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

int CParser::registerStaticDispatch(int entry, CBlockMatchList* argumentMatch, CBlock* body)
{
	for (auto it = staticDispatch.begin(); it != staticDispatch.end(); ++it)
	{
		if (it->entryId == entry)
		{
			staticDispatchEntry sEntry(argumentMatch, body);
			it->entries.push_back(sEntry);
			return entry;
		}
	}
	//nao achei nenhum que ja existe 
 
	StaticDispatchArgument  sdisp( entry);
	sdisp.entries.push_back(staticDispatchEntry(argumentMatch, body));
	staticDispatch.push_back(sdisp);
	return entry;
}
 


int CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, CBlockMatch * entry  )
{

	//Verifica se ja tem a sentenceDispatch
	int maxID = 0;
	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it)
	{
		maxID = std::max(maxID, it->entryId);
		if (isSamePred(it->matchPhase, _matchPhase))
		{			
			return it->entryId;
		}
	}

	//nao tem nenhum ... Cria um novo
	SentenceDispatchPredicate sdisp(_matchPhase , entry , maxID +1 );
	sentenceDispatch.push_back(sdisp);

	sentenceDispatch.sort([](const SentenceDispatchPredicate & a, const SentenceDispatchPredicate & b) -> bool {return a.matchPhase.size()  > b.matchPhase.size();	});

	 
	std::cout << "Dynamic Registed " <<   std::endl;
	entry->dump("    ");
	 
	return  maxID + 1;
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
	//CBlock* b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
	return std::move(ParserResult(res));
}

UBlock CParser::parse_AssertionAction_ApplyngTo(HTerm term)
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
			UBlock n1 = parser(res.matchs["kind1"]);
			UBlock n2 = parser(res.matchs["kind2"]);
			return  std::make_unique<CBlockActionApply>(n1,n2 );
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
			UBlock n1 = parser(res.matchs["kind1"]);			 
			return  std::make_unique< CBlockActionApply> (n1, n1);
		}
	}


	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		//predList.push_back(mk_HPredLiteral("one"));
		predList.push_back(mkHPredAny("kind1"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock n1 = parser(res.matchs["kind1"]);
			return  new CBlockActionApply(n1, new CBlockNoum("Nothing") );
		}
	}

	return nullptr;
}


 
UBlock CParser::parse_AssertionVerb(std::vector<HTerm> term)
{
	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(verb_IS_NOT());
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock  n1 = parser(res.matchs["N1"]);
			UBlock  n2 = parser(res.matchs["N2"]);
			return  new CBlockIsNotVerb(res.matchs[verbList->named]->repr(), n1, n2);
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(mk_HPredLiteral("not")); 
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock  n1 = parser(res.matchs["N1"]);
			UBlock   n2 = parser(res.matchs["N2"]);
			return  new CBlockIsNotVerb(res.matchs[verbList->named]->repr(), n1, n2);

		}
	}


	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;		 
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(verb_IS());		 
		predList.push_back( verbList ); 
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock n1 = parser(res.matchs["N1"]);
			UBlock   n2 = parser(res.matchs["N2"]);
			return  new CBlockIsVerb(res.matchs[verbList->named ]->repr(), n1, n2);

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));		 
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock n1 = parser(res.matchs["N1"]);
			UBlock   n2 = parser(res.matchs["N2"]);
			return  new CBlockIsVerb(res.matchs[verbList->named]->repr(), n1, n2);

		}
	}

	return nullptr;
}


UBlock CParser::parserBoolean(std::vector<HTerm> term)
{
	{
		std::vector<HPred> predList;	
		predList.push_back(mk_HPredLiteral("not"));
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{			
			UBlock n2 = parserBoolean(res.matchs["N2"]);
			return new CBlockBooleanNOT( n2);
		}
	}


	{	
		std::vector<HPred> predList;		
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(mk_HPredLiteral("and"));
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock n1 = parserBoolean(res.matchs["N1"]);
			UBlock n2 = parserBoolean(res.matchs["N2"]);
			return new CBlockBooleanAND(n1, n2);		
		}
	}


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("N1"));
		predList.push_back(mk_HPredLiteral("or"));
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock n1 = parserBoolean(res.matchs["N1"]);
			UBlock n2 = parserBoolean(res.matchs["N2"]);
			return new CBlockBooleanOR(n1, n2);
		}
	}


	return nullptr;
}



UBlock CParser::parse_AssertionAction (std::vector<HTerm> term )
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
			CBlock* applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  new CBlockActionApply(new CBlockNoum( res.matchs["Noum1"]->removeArticle()->repr() ),new  CBlockNoum(res.matchs["Noum2"]->removeArticle()->repr() ));
			return  new CBlockActionKind("", applyTO);
		
		}
	}
	 

	return nullptr;

}



 
 


UBlock CParser::parseAssertion_isKindOf(std::vector<HTerm> term)
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





UBlock CParser::parseAssertion_valuesOf(std::vector<HTerm> term)
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
			

			UBlock valueName = parser(res.matchs["valueName"] );
			UBlock valueKind = parser(res.matchs["valueKind"] );
			return new CBlockAssertion_isNamedValueOf(valueName, valueKind);

			 


		}
	}
	return nullptr;
}


 
UBlock CParser::parser_What_Assertion(std::vector<HTerm> term)
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
			UBlock body = parser(res.matchs["RemainderQuery"]);
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
			UBlock AValue = parser(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			UBlock BValue = parser(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			 
			return  new CBlockMatch(new CBlockAssertion_isDirectAssign(AValue, BValue));
		}
	}
	 
	return nullptr;

}

UBlock CParser::parseAssertion_DecideWhat( HTerm  term)
{
	return new CBlockNoum(term->removeArticle()->repr());
}

UBlock CParser::parseAssertion_isDecide(std::vector<HTerm> term)
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

	//		CBlock*    body =   new CBlockNoum(res.matchs["RemainBody"]->removeArticle()->repr());

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
			UBlock a_match =  parser(res.matchs["Match"]);
			UBlock body = parser(res.matchs["RemainBody"] );

			return  new CBlockToDecide(a_match, body);
		}
	}


	return nullptr;
}

 

UBlock CParser::parser_Definition_Assertion(std::vector<HTerm> term)
{
	
	{
		std::vector<HPred> predList;
 

		auto c1 = mkHPredList("def_A", { mk_HPredLiteral("definition"),mk_HPredLiteral(":") });
		auto c2 = mk_HPredLiteral("definition:");
		predList.push_back(mkHPredBooleanOr("kindpart", c1, c2));

		predList.push_back(mkHPredAny("Match"));
		predList.push_back(mk_HPredLiteral("if"));
		predList.push_back(mkHPredAny("LogicalBody"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock a_match = parser(res.matchs["Match"]);
			UBlock body = parserBoolean(res.matchs["LogicalBody"]);

			return  new CBlockToDecideIf(a_match, body);
		}
	}
	return nullptr;
}


CBlockStaticDispatch* CParser::getStaticDispatchResolve( HTerm term ) //Determina se este termo esta na lista de dispatchs dynamicos
{

	 
	//Verifica se ja tem a matchPhase
	int maxID = 0;
	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it)
	{
		MatchResult res = CMatch(    term, it->matchPhase);
		if (res.result == Equals)
		{
			return  new CBlockStaticDispatch(it->entryId, new CBlockNoum(res.matchs["noum1"]->repr()), new CBlockNoum(res.matchs["noum2"]->repr()));
		}
	}
	return nullptr;


}



std::pair<CBlock* , HPred>   getVerbAndAux(   HTerm  term)
{
	 
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Verb"));
		predList.push_back(mkHPredAny("Aux"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockList* clist = new CBlockList();
			clist->push_back(new  CBlockNoum(res.matchs["Verb"]->repr()));
			clist->push_back(new  CBlockNoum(res.matchs["Aux"]->repr()));


			HPred verbMatch = (mkHPredList("VerbMatch", {
				mk_HPredLiteral(res.matchs["Verb"]->repr()),
				mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));
			return std::pair<CBlock*, HPred>(clist, verbMatch);
		}
	}

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Verb"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlock* clist = new  CBlockNoum(res.matchs["Verb"]->repr());
			HPred verbMatch = mk_HPredLiteral(res.matchs["Verb"]->repr());

			return std::pair<CBlock*, HPred>(clist, verbMatch);
		}

	}
	return std::pair<CBlock*, HPred>(nullptr, nullptr);
}

DispatchArguments  CParser::parser_buildMatchBlock_actionInput(HTerm term)
{
	if (CList* cterm = dynamic_cast<CList*>(term.get()))
	{
		std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
		auto kv =   parser_buildMatchBlock_actionInput(vterm);
		return kv;
	}	

	std::vector<HPred> replcList;
	replcList.push_back(mk_HPredLiteral(term->repr()));

	//return new CBlockMatch(new CBlockNoum(term->repr()));
	return DispatchArguments(replcList , nullptr ,  new CBlockMatch(new CBlockNoum(term->repr())) );
}

CBlockMatch* CParser::parser_MatchArgument(HTerm term)
{

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("var_named"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockMatch* c1 = new CBlockMatch(new CBlockNoum(res.matchs["kind"]->removeArticle()->repr()));
			CBlockMatchNamed* n1 = new CBlockMatchNamed(res.matchs["var_named"]->repr(), c1);
			return n1;
		}

	}


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind"));
		predList.push_back(mk_HPredLiteral("-"));
		predList.push_back(mkHPredAny("var_named"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockMatch* c1 = new CBlockMatch(new CBlockNoum(res.matchs["kind"]->removeArticle()->repr()));
			CBlockMatchNamed* n1 = new CBlockMatchNamed(res.matchs["var_named"]->repr(), c1);
			return n1;
		}

	}
    return  new CBlockMatch(new CBlockKind(term->removeArticle()->repr()));
	return nullptr;
}


DispatchArguments  CParser::parser_buildMatchBlock_actionInput(std::vector<HTerm> term)
{

	std::cout << "what:  " << get_repr(term) << std::endl;
	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("verb"));
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind1"));
		predList.push_back(mk_HPredLiteral("]"));
		predList.push_back(mkHPredAny("with_word"));
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind2"));
		predList.push_back(mk_HPredLiteral("]"));


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockMatch* c1 = new CBlockMatch(new CBlockNoum(res.matchs["verb"]->repr()));			 
			CBlockMatch* c2 = parser_MatchArgument(res.matchs["kind1"]);
			CBlockMatch* c3 = new CBlockMatch(new CBlockNoum(res.matchs["with_word"]->repr()));			 
			CBlockMatch* c4 = parser_MatchArgument(res.matchs["kind2"]);
			CBlockMatch* arg1 = new CBlockMatchNamed("noum1", new CBlockMatchAny());
			CBlockMatch* arg2 = new CBlockMatchNamed("noum2", new CBlockMatchAny());

			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
			replcList.push_back(mkHPredAny("noum2"));


			return  DispatchArguments(replcList, new CBlockMatchList({ c2, c4 }), new CBlockMatchList({ c1,arg1,c3,arg2 }));

		}
	}
	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("verb"));
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind1"));
		predList.push_back(mk_HPredLiteral("]"));		 
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind2"));
		predList.push_back(mk_HPredLiteral("]"));


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockMatch* c1 = new CBlockMatch(new CBlockNoum(res.matchs["verb"]->repr()));
			CBlockMatch* c2 = parser_MatchArgument(res.matchs["kind1"]);
			CBlockMatch* c3 = new CBlockMatch(new CBlockNoum(res.matchs["with_word"]->repr()));
			CBlockMatch* c4 = parser_MatchArgument(res.matchs["kind2"]);
			CBlockMatch* arg1 = new CBlockMatchNamed("noum1", new CBlockMatchAny());
			CBlockMatch* arg2 = new CBlockMatchNamed("noum2", new CBlockMatchAny());

			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
			replcList.push_back(mkHPredAny("noum2"));


			return  DispatchArguments(replcList, new CBlockMatchList({ c2, c4 }), new CBlockMatchList({ c1,arg1,c3,arg2 }));

		}
	}


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("verb"));
		predList.push_back(mk_HPredLiteral("["));
		predList.push_back(mkHPredAny("kind1"));
		predList.push_back(mk_HPredLiteral("]"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			CBlockMatch* c1 = new CBlockMatch(new CBlockNoum(res.matchs["verb"]->repr()));
			CBlockMatch* c2 = new CBlockMatch(new CBlockKind(res.matchs["kind1"]->repr()));
			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			return  DispatchArguments(replcList, new CBlockMatchList({ c2 }), new CBlockMatchList({ c1,c2 }));
			 
		}
	}

	return DispatchArguments(std::vector<HPred>(), nullptr, nullptr);
}


CBlock* CParser::parser_understand_Action_Assertion(std::vector<HTerm> term)
{
	 


	{
		std::vector<HPred> predList;
		predList.push_back(mk_HPredLiteral("understand"));
		predList.push_back(mk_HPredLiteral(":"));
		predList.push_back(mkHPredAny("What"));
		predList.push_back(mk_HPredLiteral("as"));
		predList.push_back(mkHPredAny("Subst"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{

			//auto input_noum =  new  CBlockNoum(res.matchs["What"]->repr());

			// existe uma action que Match com o Subst ???
			CBlock* output_noum = nullptr;
			CBlockMatch* sentence_match = nullptr;
			{
				auto sTerm = res.matchs["Subst"];				 
				{
					sTerm = expandBract(sTerm);
				}				
				//std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl; 
				std::vector<HPred> actionList;
				actionList.push_back(actionPredList);
				MatchResult res_action = CMatch(sTerm, actionList);
				if (res_action.result == Equals)
				{
					CBlockAction * output_action = new CBlockAction(new CBlockNoum( (sTerm)->repr()));
					output_noum = output_action;
					DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
					sentence_match = match_predicate.sentenceMatch  ;
					
					//std::cout << "predicate  " << get_repr( match_predicate.second ) << std::endl;
					
					actionUndestands.push_back(  UnderstandAction(match_predicate.staticPredicade , output_action) );
					
					CBlockUnderstandStatic *retBlock = new CBlockUnderstandStatic(  match_predicate.staticArgumentMatch, output_noum);

					int entryID = registerDynamicDispatch(match_predicate.staticPredicade, match_predicate.sentenceMatch );
					registerStaticDispatch( entryID,  match_predicate.staticArgumentMatch   , retBlock );
					 
					return retBlock;
				} 

				//is not a action registed
				{
					std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

					CBlockStaticDispatch* s_action = getStaticDispatchResolve(sTerm);
					if (s_action != nullptr )
					{
						 
						output_noum = s_action;
						auto match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
						sentence_match = match_predicate.sentenceMatch;
						
						actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, s_action));
						
						CBlockUnderstandStatic *retBlock = new CBlockUnderstandStatic(match_predicate.staticArgumentMatch,  s_action);

						int entryID = registerDynamicDispatch(match_predicate.staticPredicade, match_predicate.sentenceMatch);
						registerStaticDispatch(entryID, match_predicate.staticArgumentMatch, retBlock);

						return retBlock;
					}

				}
			} 
		} 
	}
	return nullptr;
}



//Uma das rotinas mais importantes. Ela altera  o proprio parser
UBlock CParser::parser_understand_Assertion(std::vector<HTerm> term)
{
	
	for(auto it = sentenceDispatch.begin() ; it != sentenceDispatch.end();++it)
	{
		
		MatchResult res_action = CMatch(term, it->matchPhase );
		if (res_action.result == Equals)
		{
			UBlock  n1 = parser(res_action.matchs["noum1"]);
			UBlock   n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end())
			{
				n2 = parser(res_action.matchs["noum2"]);
			}
			else
			{
				n2 = new CBlockNoum("Nothing");
			}
			return new CBlockStaticDispatch(it->entryId , n1, n2);


		}

	}
	//return nullptr;

	//replace assertions 

	/*for(auto e : actionUndestands)
	{
		MatchResult res_action = CMatch(term, e.matchPhase);
		if (res_action.result == Equals)
		{
			CBlock*  n1 = parser(res_action.matchs["noum1"]);
			CBlock*   n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end())
			{
				 n2 = parser(res_action.matchs["noum2"]);
			}
			else
			{
				n2 = new CBlockNoum("Nothing");
			}
			return new CBlockActionCall(e.matchAction, n1,n2 );			
		}
	}*/

	auto p_action = parser_understand_Action_Assertion(term);
	if (p_action != nullptr) return p_action;

	return nullptr;
}

HPred convert_to_predicate( CTerm* termo )
{

	if (CList* clist = dynamic_cast<CList*>(termo))
	{
		auto vlist = clist->asVector();
		vlist = remove_boundaryListMark( vlist );
		
		auto hpr = mkHPredList("predListing", {});		
		CPredList* predList = dynamic_cast<CPredList*>(hpr.get());


		
		for ( auto k : vlist )
		{
			predList->plist.push_back(convert_to_predicate(k.get()));
		}
		return hpr;
	}
	else
	{
		if (CString* css = dynamic_cast<CString*>(termo))
		{
			
			return mk_HPredLiteral(css->s);
		}

	}

	return mk_HPredLiteral( termo->repr());
}



UBlock CParser::parser_verb_Assertion(std::vector<HTerm> term)
{

	auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the") , mk_HPredLiteral("verb") });
	auto L_verb = mk_HPredLiteral("verb");


	{

		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		predList.push_back(mkHPredAny("Aux"));

		auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies") ,mkHPredBooleanOr("article", mk_HPredLiteral("a"), mk_HPredLiteral("an"), mk_HPredLiteral("the")) });
		predList.push_back(L_the_verb_1);
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{


			CBlockList* clist = new CBlockList();
			clist->push_back(new  CBlockNoum(res.matchs["Verb"]->repr()));
			clist->push_back(new  CBlockNoum(res.matchs["Aux"]->repr()));

			CBlock* a_verb = clist;
			CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());

			auto verbMatch = (mkHPredList("VerbMatch", {
				mk_HPredLiteral(res.matchs["Verb"]->repr()),
				mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));

			verbList->blist.push_back(verbMatch);
			return  new CBlockVerbRelation(a_verb, a_relation);
		}

	}


	{

		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		predList.push_back(mkHPredAny("Aux"));
		predList.push_back(mk_HPredLiteral("implies"));
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{


			CBlockList* clist = new CBlockList();
			clist->push_back(new  CBlockNoum(res.matchs["Verb"]->repr()));
			clist->push_back(new  CBlockNoum(res.matchs["Aux"]->repr()));

			CBlock* a_verb = clist;
			CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());

			auto verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(res.matchs["Verb"]->repr()),
						mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));

			verbList->blist.push_back(verbMatch);
			return  new CBlockVerbRelation(a_verb, a_relation);
		}

	}

	{
		//Teste de carga

		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies") ,mkHPredBooleanOr("article", mk_HPredLiteral("a"), mk_HPredLiteral("an"), mk_HPredLiteral("the")) });

		predList.push_back(L_the_verb_1);
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{

			auto vaux  = getVerbAndAux(res.matchs["Verb"]);
			CBlock* a_verb = vaux.first;
			HPred verbMatch = vaux.second;
			CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
			verbList->blist.push_back(verbMatch);
			return  new CBlockVerbRelation(a_verb, a_relation);

		}

	}


	{
		//Teste de carga

		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		predList.push_back(mk_HPredLiteral("implies"));
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{

			auto vaux = getVerbAndAux(res.matchs["Verb"]);
			CBlock* a_verb = vaux.first;
			HPred verbMatch = vaux.second;
			CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
			verbList->blist.push_back(verbMatch);
			return  new CBlockVerbRelation(a_verb, a_relation);

		}

	}

	


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies") ,mkHPredBooleanOr("article", mk_HPredLiteral("a"), mk_HPredLiteral("an"), mk_HPredLiteral("the")) });

		predList.push_back(L_the_verb_1);
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			if (CList* cverb = dynamic_cast<CList*>(res.matchs["Verb"].get()))
			{
				CBlock* a_verb = nullptr;
				HPred verbMatch = nullptr;
				MTermSet inList(cverb->lst.begin(), cverb->lst.end());
				inList= remove_boundaryListMark(inList);
				if (inList.size() == 2)
				{
					CBlockList* clist = new CBlockList();
					clist->push_back(new  CBlockNoum(inList.front()->repr()));
					clist->push_back(new  CBlockNoum(inList.back()->repr()));
					a_verb = clist;

					  verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(inList.front()->repr()),
						mk_HPredLiteral(inList.back()->repr()),
					}));


				}
				else if (inList.size() == 1)
				{
					a_verb = new  CBlockNoum(inList.front()->repr());
					verbMatch = mk_HPredLiteral(inList.front()->repr());
				}

				int nv = inList.size();

				//std::cout << res.matchs["Verb"]->repr() << std::endl;
				if (a_verb != nullptr)
				{
					 

					CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
					verbList->blist.push_back(verbMatch);
					return  new CBlockVerbRelation(a_verb, a_relation);
				}
			}
			else
			{

				CBlock* a_verb = new  CBlockNoum(res.matchs["Verb"]->repr());
				CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
				verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
				return  new CBlockVerbRelation(a_verb, a_relation);
			}
		}

	}


	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
		predList.push_back(mkHPredAny("Verb"));
		auto L_the_verb_4 = mk_HPredLiteral("implies");
		predList.push_back(L_the_verb_4);
		predList.push_back(mkHPredAny("Relation"));
		predList.push_back(mk_HPredLiteral("relation"));
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			if (CList* cverb = dynamic_cast<CList*>(res.matchs["Verb"].get()))
			{
				CBlock* a_verb = nullptr;
				HPred verbMatch = nullptr;
				MTermSet inList(cverb->lst.begin(), cverb->lst.end());
				inList = remove_boundaryListMark(inList);
				if (inList.size() == 2)
				{
					CBlockList* clist = new CBlockList();
					clist->push_back(new  CBlockNoum(inList.front()->repr()));
					clist->push_back(new  CBlockNoum(inList.back()->repr()));
					a_verb = clist;

					verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(inList.front()->repr()),
						mk_HPredLiteral(inList.back()->repr()),
					}));


				}
				else if (inList.size() == 1)
				{
					a_verb = new  CBlockNoum(inList.front()->repr());
					verbMatch = mk_HPredLiteral(inList.front()->repr());
				}

				if (a_verb != nullptr)
				{
					CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
					verbList->blist.push_back(verbMatch);
					return  new CBlockVerbRelation(a_verb, a_relation);
				}
			}
			else
			{
				CBlock* a_verb = new  CBlockNoum(res.matchs["Verb"]->repr());
				CBlock* a_relation = new  CBlockNoum(res.matchs["Relation"]->repr());
				verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
				return  new CBlockVerbRelation(a_verb, a_relation);
			}
		}

	}

	return nullptr;

}



UBlock CParser::parseAssertion_isVariable(std::vector<HTerm> term)
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
			 
			CBlock*  noumVariable = parser(res.matchs["VariableNoum"]  );
			CBlock*   baseKind = parser(res.matchs["KindBase"]  );
			return  new CBlockAssertion_isVariable(noumVariable, baseKind);
		}
	}
	return nullptr;

}
 
UBlock   CParser::parseAssertion_DefaultAssign(std::vector<HTerm> term)
{

	{
		// is a default ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS());
		predList.push_back(mk_HPredLiteral("usually"));
		predList.push_back(mkHPredAny("Value"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			CBlock* noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			CBlock* value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  new CBlockAssertion_isDefaultAssign (noum, value);
		}
	}

	{
		// is a always ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS());
		predList.push_back(mk_HPredLiteral("always"));
		predList.push_back(mkHPredAny("Value"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			CBlock* noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			CBlock* value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  new CBlockAssertion_isConstantAssign (noum, value);
		}
	}

	{
		// is never  ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS());
		predList.push_back(mk_HPredLiteral("never"));
		predList.push_back(mkHPredAny("Value"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			CBlock* noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			CBlock* value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  new CBlockAssertion_isForbiddenAssign (noum, value);
		}
	}


	return nullptr;

}


CBlockAssertion_is     * CParser::parseAssertion_DirectAssign(std::vector<HTerm> term)
{
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));
		predList.push_back(verb_IS_NOT());
		predList.push_back(mkHPredAny("Value"));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{
			CBlock* noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			CBlock* value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  new CBlockAssertion_isNotDirectAssign(noum, value);
		}
	}
	{
		// is a kind definition ??
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Noum"));		 
		predList.push_back( verb_IS());
		predList.push_back(mkHPredAny("Value")); 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals)
		{			 
			 
			CBlock* value = parser(res.matchs["Value"] );
			if (value == nullptr) return nullptr;

			if (CBlockActionKind* action = dynamic_cast<CBlockActionKind*>(value) )
			{
				auto sterm = expandBract(res.matchs["Noum"]);
				CBlock* _naction =  new CBlockAction( new CBlockNoum(sterm->repr()));
				 
				 
				HPred actionMatch = convert_to_predicate(sterm.get() );
			//	std::cout << "found " << actionMatch->repr()  << std::endl;
				actionPredList->blist.push_back(actionMatch);

				return  new CBlockAssertion_isDirectAssign(_naction, value);

			}
			else
			{
				CBlock* noum = parser(res.matchs["Noum"]);
				if (noum == nullptr) return nullptr;
				return  new CBlockAssertion_isDirectAssign(noum, value);
			}

		}
	} 

	return nullptr;

}
UBlock  CParser::parse_removeArticle(std::vector<HTerm> term)
{
	if (term.size() > 1)
	{

		if (mk_HPredLiteral("the")->match(term.front()) == Equals)
		{
			return parser_only(get_tail(term));
		}
	}
	return nullptr;
}
 
UBlock  CParser::parse_List_AND(std::vector<HTerm> term)
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

UBlock  CParser::parse_noum(std::vector<HTerm> term)
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

	UBlock ret = parser(term);
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


UBlock CParser::parseAssertionFirstTerm_Compose(HTerm term )
{
	CBlockList *c_list = new CBlockList();
	c_list = CParser::parseAssertionFirstTerm_COMMA_AND(term, c_list);
	if ( c_list->lista.size() == 1 )
	{
		CBlock* rt;
		std::swap(rt, c_list->lista.front());
		delete c_list;
		return rt;
	}
	return c_list;
}


UBlock CParser::parseAssertionFirstTerm(HTerm term)
{
	return parseAssertionFirstTerm_Compose(term);
}


UBlock CParser::parseAssertionEnumSecondTerm(HTerm term)
{
	CBlockList *c_list = new CBlockList();
	c_list = CParser::parseAssertionFirstTerm_COMMA_OR(term, c_list);
	if (c_list->lista.size() == 1)
	{
		CBlock* rt;
		std::swap(rt, c_list->lista.front());
		delete c_list;
		return rt;
	}
	return c_list;
}
UBlock CParser::parser_Decide_Assertion(std::vector<HTerm> lst)
{
	CBlock* assert_decide = CParser::parseAssertion_isDecide(lst);
	if (assert_decide != nullptr)
	{
		return assert_decide;
	}
	return nullptr;

}

 


UBlock CParser::parser_Declaration_Assertion(std::vector<HTerm> lst)
{


	UBlock verb_Assign = CParser::parse_AssertionVerb(lst);
	if (verb_Assign != nullptr)
	{
		return verb_Assign;
	}


	UBlock action_Assign = CParser::parse_AssertionAction (lst);
	if (action_Assign != nullptr)
	{
		return action_Assign;
	}

	

	UBlock assert_variable = CParser::parseAssertion_isVariable(lst);
	if (assert_variable != nullptr)
	{
		return assert_variable;
	}
	 

	UBlock assert_kindof= CParser::parseAssertion_isKindOf(lst);
	if (assert_kindof != nullptr)
	{
		return assert_kindof;
	}

	UBlock assert_values = CParser::parseAssertion_valuesOf(lst);
	if (assert_values != nullptr)
	{
		return assert_values;
	}


	UBlock assert_DefaultAssign = CParser::parseAssertion_DefaultAssign(lst);
	if (assert_DefaultAssign != nullptr)
	{
		return assert_DefaultAssign;
	}

	UBlock assert_Assign = CParser::parseAssertion_DirectAssign(lst);
	if (assert_Assign != nullptr)
	{
		return assert_Assign;
	}

	 



	return nullptr;
	 
}

CBlockProperty* CParser::parse_PropertyOf(std::vector<HTerm> term)
{
	{
	 
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("property"));
		predList.push_back(mk_HPredLiteral("of"));
		predList.push_back(mkHPredAny("obj"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			UBlock a = parser(res.matchs["property"]);
			if (a != nullptr)
			{
				UBlock b = parser(res.matchs["obj"]);
				if (b != nullptr)
				{
					//CBlockNoum* object_Name = new CBlockNoum(res.matchs["obj"]->removeArticle()->repr());
					return new CBlockProperty(a, b);
				}
			}
		}
	}




	//{
	//	std::cout << get_repr(term) << std::endl;
	//	std::vector<HPred> predList;
	//	predList.push_back(mk_HPredLiteral("the"));
	//	predList.push_back(mkHPredAny("property"));
	//	predList.push_back(mk_HPredLiteral("of"));
	//	predList.push_back(mkHPredAny("obj"));
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals)
	//	{
	//		CBlock* a = parser(res.matchs["property"]);
	//		if (a != nullptr)
	//		{
	//			CBlock* b = parser(res.matchs["obj"]);
	//			if (b != nullptr)
	//			{
	//				//CBlockNoum* object_Name = new CBlockNoum(res.matchs["obj"]->removeArticle()->repr());
	//				return new CBlockProperty(a, b);
	//			}
	//		}
	//	}
	//}
	return nullptr;
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

 

UBlock CParser::parser_canBe_Assertion(std::vector<HTerm> lst)
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

	UBlock defintionFirst_Noum = parser(res.matchs["Target"]);
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
			UBlock a = parser(res.matchs["kindName"]);
			UBlock b = parser(res.matchs["propName"]);
			return new CBlockInstanceVariable(a,b );
		}
	
	}


	// the torch has a brightness   ;  -> called brightness
	UBlock a = parser(term);
	return new CBlockInstanceVariable(a, a); 
	 

}


UBlock CParser::parser_hasAn_Assertion(std::vector<HTerm> lst)
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
	UBlock defintionFirst_KindOrInstance =  parser(res.matchs["Target"] );

	return  new CBlockAssertion_InstanceVariable (defintionFirst_KindOrInstance,  definitionProperty_kindAndName);
}

 
 
UBlock CParser::parser_only(std::vector<HTerm> lst)
{
	//str = decompose_bracket(str, "(");
	//str = decompose_bracket(str, ")");
	//str = decompose_bracket(str, ",");
	// 
	//std::vector<HTerm>  lst = decompose(str);


	UBlock rblock_understand_1 = (parser_understand_Assertion(lst));
	if (rblock_understand_1 != nullptr) return rblock_understand_1;
	 
	UBlock rblock_verb_1 = (parser_verb_Assertion(lst));
	if (rblock_verb_1 != nullptr) return rblock_verb_1;

	UBlock rblock_definition_1 = (parser_Definition_Assertion(lst));
	if (rblock_definition_1 != nullptr) return rblock_definition_1;

	UBlock rblock_decide_1 = (parser_Decide_Assertion(lst));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;
	 
	UBlock rblock_what_1 = (parser_What_Assertion(lst));
	if (rblock_what_1 != nullptr) return rblock_what_1;


	UBlock rblock_assert_1 = (parser_Declaration_Assertion (lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;

	UBlock rblock_assert_hasA = (parser_hasAn_Assertion(lst));
	if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

	UBlock rblock_assert_2 = (parser_canBe_Assertion(lst));
	if (rblock_assert_2 != nullptr) return rblock_assert_2;

 
	UBlock noum_propOF = CParser::parse_PropertyOf(lst);
	if (noum_propOF != nullptr)
	{
		return noum_propOF;
	}

 

	UBlock noumList_Assign = CParser::parse_List_AND(lst);
	if (noumList_Assign != nullptr)
	{
		return noumList_Assign;
	}

	UBlock detnoum_Assign = CParser::parse_removeArticle(lst);
	if (detnoum_Assign != nullptr)
	{
		return detnoum_Assign;
	}

	UBlock noum_Assign = CParser::parse_noum(lst);
	if (noum_Assign != nullptr)
	{
		return noum_Assign;
	}


	return nullptr;
 
}
UBlock CParser::parser(HTerm term)
{
	if (CList  * vlist = dynamic_cast<CList*>(term.get()))
	{
		auto r =  parser_only(vlist->asVector());
		/*if (r == nullptr)
			std::cout << term->repr() << std::endl;*/

		return r;
	}
	return new CBlockNoum(  term->removeArticle()->repr());
}

 

UBlock CParser::parserBoolean(HTerm term)
{
	if (CList  * vlist = dynamic_cast<CList*>(term.get()))
	{
		auto r = parserBoolean(vlist->asVector());
		if (r != nullptr)
		{
			return r;
		}			 
		else
		{
		//	std::cout << term->repr() << std::endl;
		}

	}
	return   parser(term);
}

UBlock CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");

	std::vector<HTerm>  lst = decompose(str);
	return  parser_only(lst);
	 

}
