#include "Parser.h"
#include <iostream>
#include <algorithm>
 
#include "CBlockInterpreterRuntime.h"
#include "CBlockMatch.h"
#include "CBlockBoolean.h"
#include "CblockAssertion.h"

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


staticDispatchEntry::staticDispatchEntry(HBlockMatchList  _argumentsMatch, HBlock _action): entryArguments (_argumentsMatch), action(_action)
{

}
staticDispatchEntry::staticDispatchEntry( ) : entryArguments(nullptr), action(nullptr)
{

}

 

SentenceDispatchPredicate::SentenceDispatchPredicate(std::vector<HPred> _matchPhase, HBlockMatch _matchPhaseDynamic, int _entryId): matchPhase(_matchPhase), _matchPhaseDynamic(_matchPhaseDynamic),  entryId(_entryId)
{

}

CParser::CParser(HBlockInterpreter  _interpreter)
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
//HBlock CParser::get_Noum(string named) const
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

int CParser::registerStaticDispatch(int entry, HBlockMatchList  argumentMatch, HBlock body)
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
 


int CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch   entry  )
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
	//HBlock b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
	return std::move(ParserResult(res));
}

HBlock CParser::parse_AssertionAction_ApplyngTo(HTerm term)
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
			HBlock n1 = parser(res.matchs["kind1"]);
			HBlock n2 = parser(res.matchs["kind2"]);
			return  std::make_shared<CBlockActionApply>(n1,n2 );
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
			HBlock n1 = parser(res.matchs["kind1"]);			 
			return  std::make_shared<CBlockActionApply>  (n1, n1);
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
			HBlock n1 = parser(res.matchs["kind1"]);
			return    std::make_shared<CBlockActionApply>(n1, std::make_shared<CBlockNoum>("Nothing") );
		}
	}

	return nullptr;
}


 
HBlock CParser::parse_AssertionVerb(std::vector<HTerm> term)
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
			HBlock  n1 = parser(res.matchs["N1"]);
			HBlock  n2 = parser(res.matchs["N2"]);
			return   std::make_shared<CBlockIsNotVerb>(res.matchs[verbList->named]->repr(), n1, n2);
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
			HBlock  n1 = parser(res.matchs["N1"]);
			HBlock   n2 = parser(res.matchs["N2"]);
			return  std::make_shared<CBlockIsNotVerb>(res.matchs[verbList->named]->repr(), n1, n2);

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
			HBlock n1 = parser(res.matchs["N1"]);
			HBlock   n2 = parser(res.matchs["N2"]);
			return   std::make_shared<CBlockIsVerb>(res.matchs[verbList->named ]->repr(), n1, n2);

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
			HBlock n1 = parser(res.matchs["N1"]);
			HBlock   n2 = parser(res.matchs["N2"]);
			return  std::make_shared<CBlockIsVerb>(res.matchs[verbList->named]->repr(), n1, n2);

		}
	}

	return nullptr;
}


HBlock CParser::parserBoolean(std::vector<HTerm> term)
{
	{
		std::vector<HPred> predList;	
		predList.push_back(mk_HPredLiteral("not"));
		predList.push_back(mkHPredAny("N2"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{			
			HBlock n2 = parserBoolean(res.matchs["N2"]);
			return std::make_shared<CBlockBooleanNOT>( n2);
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
			HBlock n1 = parserBoolean(res.matchs["N1"]);
			HBlock n2 = parserBoolean(res.matchs["N2"]);
			return std::make_shared<CBlockBooleanAND>(n1, n2);		
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
			HBlock n1 = parserBoolean(res.matchs["N1"]);
			HBlock n2 = parserBoolean(res.matchs["N2"]);
			return std::make_shared<CBlockBooleanOR>(n1, n2);
		}
	}


	return nullptr;
}



HBlock CParser::parse_AssertionAction (std::vector<HTerm> term )
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
			HBlock applyTO = parse_AssertionAction_ApplyngTo(res.matchs["ApplyRemainder"]);
			//return  std::make_shared<CBlockActionApply>(std::make_shared<CBlockNoum>( res.matchs["Noum1"]->removeArticle()->repr() ),std::make_shared<CBlockNoum>(res.matchs["Noum2"]->removeArticle()->repr() ));
			return  std::make_shared<CBlockKindAction>("", applyTO);
		
		}
	}
	 

	return nullptr;

}



 
 


HBlock CParser::parseAssertion_isKindOf(std::vector<HTerm> term)
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

			return std::make_shared<CBlockKindOfName>(  res.matchs["kindBase"]->removeArticle()->repr() );
		}
	}


	{
		std::vector<HPred> predList;	 
		predList.push_back(mkHPredList("kindDef", { undefinedArticle(), mk_HPredLiteral("kind")   }));
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return std::make_shared<CBlockKindOfName>(""); // no Base

		}
	}

	return nullptr;

}





HBlock CParser::parseAssertion_valuesOf(std::vector<HTerm> term)
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
			

			HBlock valueName = parser(res.matchs["valueName"] );
			HBlock valueKind = parser(res.matchs["valueKind"] );
			return std::make_shared<CBlockAssertion_isNamedValueOf>(valueName, valueKind);

			 


		}
	}
	return nullptr;
}


 
HBlock CParser::parser_What_Assertion(std::vector<HTerm> term)
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
			HBlock body = parser(res.matchs["RemainderQuery"]);
			if (body != nullptr)
			{
				return  std::make_shared<CBlockMatch>(body);
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
			HBlock AValue = parser(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock BValue = parser(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			 
			return  std::make_shared<CBlockMatch>(std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue));
		}
	}
	 
	return nullptr;

}

HBlock CParser::parseAssertion_DecideWhat( HTerm  term)
{
	return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
}

HBlock CParser::parseAssertion_isDecide(std::vector<HTerm> term)
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
	//		HBlockMatch   noumVariable = std::make_shared<CBlockMatch>(parseAssertion_DecideWhat( res.matchs["ValueToDecide"] ) );
	//		HBlockKind          baseKind = std::make_shared<CBlockKind>(res.matchs["KindToReturn"]->removeArticle()->repr());

	//		HBlock    body =   std::make_shared<CBlockNoum>(res.matchs["RemainBody"]->removeArticle()->repr());

	//		return  std::make_shared<CBlockToDefine>(baseKind, noumVariable , body);
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
			HBlock a_match =  parser(res.matchs["Match"]);
			HBlock body = parser(res.matchs["RemainBody"] );

			return  std::make_shared<CBlockToDecide>(a_match, body);
		}
	}


	return nullptr;
}

 

HBlock CParser::parser_Definition_Assertion(std::vector<HTerm> term)
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
			HBlock a_match = parser(res.matchs["Match"]);
			HBlock body = parserBoolean(res.matchs["LogicalBody"]);

			return  std::make_shared<CBlockToDecideIf>(a_match, body);
		}
	}
	return nullptr;
}


HBlockStaticDispatch  CParser::getStaticDispatchResolve( HTerm term ) //Determina se este termo esta na lista de dispatchs dynamicos
{

	 
	//Verifica se ja tem a matchPhase
	int maxID = 0;
	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it)
	{
		MatchResult res = CMatch(    term, it->matchPhase);
		if (res.result == Equals)
		{
			return  std::make_shared<CBlockStaticDispatch>(it->entryId, std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr()), std::make_shared<CBlockNoum>(res.matchs["noum2"]->repr()));
		}
	}
	return nullptr;


}



std::pair<HBlock , HPred>   getVerbAndAux(   HTerm  term)
{
	 
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Verb"));
		predList.push_back(mkHPredAny("Aux"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockList  clist = std::make_shared<CBlockList>();
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));


			HPred verbMatch = (mkHPredList("VerbMatch", {
				mk_HPredLiteral(res.matchs["Verb"]->repr()),
				mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));
			return std::pair<HBlock, HPred>(clist, verbMatch);
		}
	}

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("Verb"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock clist = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
			HPred verbMatch = mk_HPredLiteral(res.matchs["Verb"]->repr());

			return std::pair<HBlock, HPred>(clist, verbMatch);
		}

	}
	return std::pair<HBlock, HPred>(nullptr, nullptr);
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

	//return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr()));
	return DispatchArguments(replcList , nullptr ,  std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr())) );
}

HBlockMatch  CParser::parser_MatchArgument(HTerm term)
{

	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("kind"));
		predList.push_back(mk_HPredLiteral("called"));
		predList.push_back(mkHPredAny("var_named"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch  c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
			HBlockMatchNamed n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
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
			HBlockMatch  c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind"]->removeArticle()->repr()));
			HBlockMatchNamed  n1 = std::make_shared<CBlockMatchNamed>(res.matchs["var_named"]->repr(), c1);
			return n1;
		}

	}
    return  std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->removeArticle()->repr()));
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
			HBlockMatch  c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));			 
			HBlockMatch  c2 = parser_MatchArgument(res.matchs["kind1"]);
			HBlockMatch  c3 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));			 
			HBlockMatch  c4 = parser_MatchArgument(res.matchs["kind2"]);
			HBlockMatch  arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			HBlockMatch  arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
			replcList.push_back(mkHPredAny("noum2"));

			
			auto mlist1 = std::make_shared<CBlockMatchList>( std::list<HBlockMatch>({ c2, c4 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1,arg1,c3,arg2 }));
			return  DispatchArguments(replcList, mlist1, mlist2 );

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
			HBlockMatch  c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch  c2 = parser_MatchArgument(res.matchs["kind1"]);
			HBlockMatch  c3 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));
			HBlockMatch  c4 = parser_MatchArgument(res.matchs["kind2"]);
			HBlockMatch  arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			HBlockMatch  arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
			replcList.push_back(mkHPredAny("noum2"));

			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2, c4 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1,arg1,c3,arg2 }));
			return  DispatchArguments(replcList, mlist1, mlist2); 

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
			HBlockMatch  c1 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch  c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2  }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1,c2 }));
			return  DispatchArguments(replcList, mlist1, mlist2);
		}
	}

	return DispatchArguments(std::vector<HPred>(), nullptr, nullptr);
}


HBlock CParser::parser_understand_Action_Assertion(std::vector<HTerm> term)
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

			//auto input_noum =  std::make_shared<CBlockNoum>(res.matchs["What"]->repr());

			// existe uma action que Match com o Subst ???
			HBlock output_noum = nullptr;
			HBlockMatch  sentence_match = nullptr;
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
					HBlockAction   output_action = std::make_shared<CBlockAction>(std::make_shared<CBlockNoum>( (sTerm)->repr()));
					output_noum = output_action;
					DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
					sentence_match = match_predicate.sentenceMatch  ;
					
					//std::cout << "predicate  " << get_repr( match_predicate.second ) << std::endl;
					
					actionUndestands.push_back(  UnderstandAction(match_predicate.staticPredicade , output_action) );
					
					HBlockUnderstandStatic  retBlock = std::make_shared<CBlockUnderstandStatic>(  match_predicate.staticArgumentMatch, output_noum);

					int entryID = registerDynamicDispatch(match_predicate.staticPredicade, match_predicate.sentenceMatch );
					registerStaticDispatch( entryID,  match_predicate.staticArgumentMatch   , retBlock );
					 
					return retBlock;
				} 

				//is not a action registed
				{
					std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

					HBlockStaticDispatch  s_action = getStaticDispatchResolve(sTerm);
					if (s_action != nullptr )
					{
						 
						output_noum = s_action;
						auto match_predicate = parser_buildMatchBlock_actionInput(res.matchs["What"]);
						sentence_match = match_predicate.sentenceMatch;
						
						actionUndestands.push_back(UnderstandAction(match_predicate.staticPredicade, s_action));
						
						HBlockUnderstandStatic  retBlock = std::make_shared<CBlockUnderstandStatic>(match_predicate.staticArgumentMatch,  s_action);

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
HBlock CParser::parser_understand_Assertion(std::vector<HTerm> term)
{
	
	for(auto it = sentenceDispatch.begin() ; it != sentenceDispatch.end();++it)
	{
		
		MatchResult res_action = CMatch(term, it->matchPhase );
		if (res_action.result == Equals)
		{
			HBlock  n1 = parser(res_action.matchs["noum1"]);
			HBlock   n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end())
			{
				n2 = parser(res_action.matchs["noum2"]);
			}
			else
			{
				n2 = std::make_shared<CBlockNoum>("Nothing");
			}
			return std::make_shared<CBlockStaticDispatch>(it->entryId , n1, n2);


		}

	}
	//return nullptr;

	//replace assertions 

	/*for(auto e : actionUndestands)
	{
		MatchResult res_action = CMatch(term, e.matchPhase);
		if (res_action.result == Equals)
		{
			HBlock  n1 = parser(res_action.matchs["noum1"]);
			HBlock   n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end())
			{
				 n2 = parser(res_action.matchs["noum2"]);
			}
			else
			{
				n2 = std::make_shared<CBlockNoum>("Nothing");
			}
			return std::make_shared<CBlockActionCall>(e.matchAction, n1,n2 );			
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



HBlock CParser::parser_verb_Assertion(std::vector<HTerm> term)
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


			HBlockList  clist = std::make_shared<CBlockList>();
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

			HBlock a_verb = clist;
			HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

			auto verbMatch = (mkHPredList("VerbMatch", {
				mk_HPredLiteral(res.matchs["Verb"]->repr()),
				mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));

			verbList->blist.push_back(verbMatch);
			return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
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


			HBlockList  clist = std::make_shared<CBlockList>();
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
			clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

			HBlock a_verb = clist;
			HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

			auto verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(res.matchs["Verb"]->repr()),
						mk_HPredLiteral(res.matchs["Aux"]->repr()),
			}));

			verbList->blist.push_back(verbMatch);
			return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
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
			HBlock a_verb = vaux.first;
			HPred verbMatch = vaux.second;
			HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
			verbList->blist.push_back(verbMatch);
			return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

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
			HBlock a_verb = vaux.first;
			HPred verbMatch = vaux.second;
			HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
			verbList->blist.push_back(verbMatch);
			return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

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
				HBlock a_verb = nullptr;
				HPred verbMatch = nullptr;
				MTermSet inList(cverb->lst.begin(), cverb->lst.end());
				inList= remove_boundaryListMark(inList);
				if (inList.size() == 2)
				{
					HBlockList  clist = std::make_shared<CBlockList>();
					clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
					clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
					a_verb = clist;

					  verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(inList.front()->repr()),
						mk_HPredLiteral(inList.back()->repr()),
					}));


				}
				else if (inList.size() == 1)
				{
					a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
					verbMatch = mk_HPredLiteral(inList.front()->repr());
				}

				int nv = inList.size();

				//std::cout << res.matchs["Verb"]->repr() << std::endl;
				if (a_verb != nullptr)
				{
					 

					HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
					verbList->blist.push_back(verbMatch);
					return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
				}
			}
			else
			{

				HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
				HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
				verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
				return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
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
				HBlock a_verb = nullptr;
				HPred verbMatch = nullptr;
				MTermSet inList(cverb->lst.begin(), cverb->lst.end());
				inList = remove_boundaryListMark(inList);
				if (inList.size() == 2)
				{
					HBlockList  clist = std::make_shared<CBlockList>();
					clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
					clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
					a_verb = clist;

					verbMatch = (mkHPredList("VerbMatch", {
						mk_HPredLiteral(inList.front()->repr()),
						mk_HPredLiteral(inList.back()->repr()),
					}));


				}
				else if (inList.size() == 1)
				{
					a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
					verbMatch = mk_HPredLiteral(inList.front()->repr());
				}

				if (a_verb != nullptr)
				{
					HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
					verbList->blist.push_back(verbMatch);
					return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
				}
			}
			else
			{
				HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
				HBlock a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
				verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
				return  std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
			}
		}

	}

	return nullptr;

}



HBlock CParser::parseAssertion_isVariable(std::vector<HTerm> term)
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
			 
			HBlock  noumVariable = parser(res.matchs["VariableNoum"]  );
			HBlock   baseKind = parser(res.matchs["KindBase"]  );
			return  std::make_shared<CBlockAssertion_isVariable>(noumVariable, baseKind);
		}
	}
	return nullptr;

}
 
HBlock   CParser::parseAssertion_DefaultAssign(std::vector<HTerm> term)
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
			HBlock noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  std::make_shared<CBlockAssertion_isDefaultAssign> (noum, value);
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
			HBlock noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  std::make_shared<CBlockAssertion_isConstantAssign> (noum, value);
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
			HBlock noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  std::make_shared<CBlockAssertion_isForbiddenAssign> (noum, value);
		}
	}


	return nullptr;

}


HBlockAssertion_is   CParser::parseAssertion_DirectAssign(std::vector<HTerm> term)
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
			HBlock noum = parser(res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = parser(res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return  std::make_shared<CBlockAssertion_isNotDirectAssign>(noum, value);
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
			 
			HBlock value = parser(res.matchs["Value"] );
			if (value == nullptr) return nullptr;

			if (HBlockKindAction  action = std::dynamic_pointer_cast<CBlockKindAction >(value) )
			{
				auto sterm = expandBract(res.matchs["Noum"]);
				HBlock _naction =  std::make_shared<CBlockAction>( std::make_shared<CBlockNoum>(sterm->repr()));
				 
				 
				HPred actionMatch = convert_to_predicate(sterm.get() );
			//	std::cout << "found " << actionMatch->repr()  << std::endl;
				actionPredList->blist.push_back(actionMatch);

				return  std::make_shared<CBlockAssertion_isDirectAssign>(_naction, value);

			}
			else
			{
				HBlock noum = parser(res.matchs["Noum"]);
				if (noum == nullptr) return nullptr;
				return  std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
			}

		}
	} 

	return nullptr;

}
HBlock  CParser::parse_removeArticle(std::vector<HTerm> term)
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
 
HBlock  CParser::parse_List_AND(std::vector<HTerm> term)
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
			HBlockList  cList = std::make_shared<CBlockList>();
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
			HBlockList  cList = std::make_shared<CBlockList>();
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
			cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
			return cList;
		}
	}



	return nullptr;

}

HBlock  CParser::parse_noum(std::vector<HTerm> term)
{
	std::vector<HPred> predList;
	
	



	//predList.push_back(undefinedArticle());
	predList.push_back(mkHPredAny("Noum"));
	MatchResult res = CMatch(term, predList);

	if (res.result == Equals)
	{
		return std::make_shared<CBlockNoum>(  res.matchs["Noum"]->removeArticle()->repr());
	}
	return nullptr;
}

HBlockAssertion_isInstanceOf   CParser::parseAssertion_isInstanceOf(std::vector<HTerm> term)  
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
			//HBlockInstance  noumInstance = std::make_shared<CBlockInstance> (res.matchs["Noum"]->removeArticle()->repr());
			//HBlockNoum           baseKind = std::make_shared<CBlockNoum>(res.matchs["KindBase"]->removeArticle()->repr());
		 
			//return  std::make_shared<CBlockAssertion_isInstanceOf>(noumInstance, baseKind);
		}
	}
	return nullptr;

}
 
 

 
HBlockList  CParser::parseAssertion_Strict_COMMA_Supl(HTerm term, HPred sep )
{
	
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("N1"));
	predList.push_back(sep);
	predList.push_back(mkHPredAny("N2"));
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		HBlockList  cList = std::make_shared<CBlockList>();
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N1"], sep, cList);
		cList = CParser::parseAssertionFirstTerm_COMMA_Supl(res.matchs["N2"], sep, cList);
		return cList;
	}
	return nullptr;
}
HBlockList  CParser::parseAssertionFirstTerm_COMMA_Supl(HTerm term, HPred sep, HBlockList  cList)
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

	HBlock ret = parser(term);
	cList->push_back(ret);
	//cList->push_back(std::make_shared<CBlockNoum>(  term->removeArticle()->repr()));
	return cList;
}
 
HBlockList  CParser::parseAssertionFirstTerm_COMMA_AND(HTerm term, HBlockList  CList )
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("and"), CList);
}

HBlockList  CParser::parseAssertionFirstTerm_COMMA_OR(HTerm term, HBlockList  CList)
{
	return parseAssertionFirstTerm_COMMA_Supl(term, mk_HPredLiteral("or"), CList); 
}

HBlockList  CParser::parse_Strict_COMMA_AND(HTerm term )
{
	return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("and") );
}

HBlockList  CParser::parse_Strict_COMMA_OR(HTerm term )
{
	return parseAssertion_Strict_COMMA_Supl(term, mk_HPredLiteral("or") );
}


HBlock CParser::parseAssertionFirstTerm_Compose(HTerm term )
{
	HBlockList  c_list = std::make_shared<CBlockList>();
	c_list = CParser::parseAssertionFirstTerm_COMMA_AND(term, c_list);
	if ( c_list->lista.size() == 1 )
	{
		HBlock rt;
		std::swap(rt, c_list->lista.front());
		//delete c_list;
		return rt;
	}
	return c_list;
}


HBlock CParser::parseAssertionFirstTerm(HTerm term)
{
	return parseAssertionFirstTerm_Compose(term);
}


HBlock CParser::parseAssertionEnumSecondTerm(HTerm term)
{
	HBlockList  c_list = std::make_shared<CBlockList>();
	c_list = CParser::parseAssertionFirstTerm_COMMA_OR(term, c_list);
	if (c_list->lista.size() == 1)
	{
		HBlock rt;
		std::swap(rt, c_list->lista.front());
		//delete c_list;
		return rt;
	}
	return c_list;
}
HBlock CParser::parser_Decide_Assertion(std::vector<HTerm> lst)
{
	HBlock assert_decide = CParser::parseAssertion_isDecide(lst);
	if (assert_decide != nullptr)
	{
		return assert_decide;
	}
	return nullptr;

}

 


HBlock CParser::parser_Declaration_Assertion(std::vector<HTerm> lst)
{


	HBlock verb_Assign = CParser::parse_AssertionVerb(lst);
	if (verb_Assign != nullptr)
	{
		return verb_Assign;
	}


	HBlock action_Assign = CParser::parse_AssertionAction (lst);
	if (action_Assign != nullptr)
	{
		return action_Assign;
	}

	

	HBlock assert_variable = CParser::parseAssertion_isVariable(lst);
	if (assert_variable != nullptr)
	{
		return assert_variable;
	}
	 

	HBlock assert_kindof= CParser::parseAssertion_isKindOf(lst);
	if (assert_kindof != nullptr)
	{
		return assert_kindof;
	}

	HBlock assert_values = CParser::parseAssertion_valuesOf(lst);
	if (assert_values != nullptr)
	{
		return assert_values;
	}


	HBlock assert_DefaultAssign = CParser::parseAssertion_DefaultAssign(lst);
	if (assert_DefaultAssign != nullptr)
	{
		return assert_DefaultAssign;
	}

	HBlock assert_Assign = CParser::parseAssertion_DirectAssign(lst);
	if (assert_Assign != nullptr)
	{
		return assert_Assign;
	}

	 



	return nullptr;
	 
}

HBlockProperty  CParser::parse_PropertyOf(std::vector<HTerm> term)
{
	{
	 
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("property"));
		predList.push_back(mk_HPredLiteral("of"));
		predList.push_back(mkHPredAny("obj"));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock a = parser(res.matchs["property"]);
			if (a != nullptr)
			{
				HBlock b = parser(res.matchs["obj"]);
				if (b != nullptr)
				{
					//HBlockNoum  object_Name = std::make_shared<CBlockNoum>(res.matchs["obj"]->removeArticle()->repr());
					return std::make_shared<CBlockProperty>(a, b);
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
	//		HBlock a = parser(res.matchs["property"]);
	//		if (a != nullptr)
	//		{
	//			HBlock b = parser(res.matchs["obj"]);
	//			if (b != nullptr)
	//			{
	//				//HBlockNoum  object_Name = std::make_shared<CBlockNoum>(res.matchs["obj"]->removeArticle()->repr());
	//				return std::make_shared<CBlockProperty>(a, b);
	//			}
	//		}
	//	}
	//}
	return nullptr;
}



HBlockEnums  CParser::parseAssertion_EnumTerms( HTerm  enumList )
{

	HBlockList   elist = std::make_shared<CBlockList>();
	elist = parseAssertionFirstTerm_COMMA_OR(enumList, elist );
	if (elist->lista.empty())
	{
		return nullptr;
	}

	std::vector<HBlockNoum > nlist;
	std::for_each(elist->lista.begin(), elist->lista.end(),   [&nlist](HBlock c) { nlist.push_back( std::dynamic_pointer_cast<CBlockNoum>(c)); });
	return std::make_shared<CBlockEnums>(nlist);

}

 

HBlock CParser::parser_canBe_Assertion(std::vector<HTerm> lst)
{
	std::vector<HPred> predList;
	predList.push_back(mkHPredAny("Target")); 
	predList.push_back(mk_HPredLiteral("can"));
	predList.push_back(mk_HPredLiteral("be"));
	predList.push_back(mkHPredAny("EnumValues"));
	MatchResult res = CMatch(lst, predList);

	if (res.result != Equals) return nullptr ;

	HBlockEnums  definitionSecond = parseAssertion_EnumTerms(res.matchs["EnumValues"]);
	if (definitionSecond == nullptr)
	{
		return nullptr;
	}

	/*HBlockProperty  defintionFirst_property = parseAssertion_PropertyFirstTerm(res.matchs["Target"]);
	if (defintionFirst_property != nullptr)
	{
		return  std::make_shared<CBlockAssertion_property_canBe>(defintionFirst_property, definitionSecond);
	}*/

	//HBlockNoum  defintionFirst_Noum = std::make_shared<CBlockNoum>(res.matchs["Target"]->removeArticle()->repr());

	HBlock defintionFirst_Noum = parser(res.matchs["Target"]);
	if (defintionFirst_Noum != nullptr)
	{
		return   std::make_shared<CBlockAssertion_canBe>(defintionFirst_Noum, definitionSecond);
	}

	return nullptr;
}

HBlockInstanceVariable  CParser::CProperty_called(HTerm term)
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
			HBlockNoum  a = std::make_shared<CBlockNoum>(res.matchs["kindName"]->repr());
			HBlockNoum  b = std::make_shared<CBlockNoum>(  res.matchs["propName"]->repr()  );
			return std::make_shared<CBlockInstanceVariable>(a,b );
		}
	
	}

	{
		// the torch has a brightness   ;  -> called brightness
		HBlockNoum  a = std::make_shared<CBlockNoum>(term->repr());
		HBlockNoum  b = std::make_shared<CBlockNoum>(term->repr());
		return std::make_shared<CBlockInstanceVariable>(a, b);
	}

}


HBlock CParser::parser_hasAn_Assertion(std::vector<HTerm> lst)
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

	HBlockInstanceVariable    definitionProperty_kindAndName = CProperty_called(res.matchs["KindAndName"]);
	if (definitionProperty_kindAndName == nullptr)
	{
		return nullptr;
	}	

	//HBlockNoum  defintionFirst_KindOrInstance = std::make_shared<CBlockNoum>( res.matchs["Target"]->removeArticle()->repr());
	HBlock defintionFirst_KindOrInstance =  parser(res.matchs["Target"] );

	return  std::make_shared<CBlockAssertion_InstanceVariable> (defintionFirst_KindOrInstance,  definitionProperty_kindAndName);
}

 
 
HBlock CParser::parser_only(std::vector<HTerm> lst)
{
	//str = decompose_bracket(str, "(");
	//str = decompose_bracket(str, ")");
	//str = decompose_bracket(str, ",");
	// 
	//std::vector<HTerm>  lst = decompose(str);


	HBlock rblock_understand_1 = (parser_understand_Assertion(lst));
	if (rblock_understand_1 != nullptr) return rblock_understand_1;
	 
	HBlock rblock_verb_1 = (parser_verb_Assertion(lst));
	if (rblock_verb_1 != nullptr) return rblock_verb_1;

	HBlock rblock_definition_1 = (parser_Definition_Assertion(lst));
	if (rblock_definition_1 != nullptr) return rblock_definition_1;

	HBlock rblock_decide_1 = (parser_Decide_Assertion(lst));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;
	 
	HBlock rblock_what_1 = (parser_What_Assertion(lst));
	if (rblock_what_1 != nullptr) return rblock_what_1;


	HBlock rblock_assert_1 = (parser_Declaration_Assertion (lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;

	HBlock rblock_assert_hasA = (parser_hasAn_Assertion(lst));
	if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

	HBlock rblock_assert_2 = (parser_canBe_Assertion(lst));
	if (rblock_assert_2 != nullptr) return rblock_assert_2;

 
	HBlock noum_propOF = CParser::parse_PropertyOf(lst);
	if (noum_propOF != nullptr)
	{
		return noum_propOF;
	}

 

	HBlock noumList_Assign = CParser::parse_List_AND(lst);
	if (noumList_Assign != nullptr)
	{
		return noumList_Assign;
	}

	HBlock detnoum_Assign = CParser::parse_removeArticle(lst);
	if (detnoum_Assign != nullptr)
	{
		return detnoum_Assign;
	}

	HBlock noum_Assign = CParser::parse_noum(lst);
	if (noum_Assign != nullptr)
	{
		return noum_Assign;
	}


	return nullptr;
 
}
HBlock CParser::parser(HTerm term)
{
	if (CList  * vlist = dynamic_cast<CList*>(term.get()))
	{
		auto r =  parser_only(vlist->asVector());
		/*if (r == nullptr)
			std::cout << term->repr() << std::endl;*/

		return r;
	}
	return std::make_shared<CBlockNoum>(  term->removeArticle()->repr());
}

 

HBlock CParser::parserBoolean(HTerm term)
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

HBlock CParser::parser(std::string str)
{
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");

	std::vector<HTerm>  lst = decompose(str);
	return  parser_only(lst);
	 

}
