// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Parser\Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

HBlockAssertion_is NSParser::ParseAssertion::parse_AssertionAdverb(CParser *p, std::vector<HTerm>&  term)
{
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1") << verb_IS() << pAny("ADV") << pLiteral("than")  << pAny("N2");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_assertionTarger(p, res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p, res.matchs["N2"]);
				if (n2 != nullptr)
				{
					auto vrepr = CtoString(expandBract(res.matchs["ADV"]));
					return std::make_shared<CBlockIsAdverbialComparasion>(vrepr, n1, n2);
				}
			}
		}
	}
	return nullptr;
}


HBlockAssertion_is NSParser::ParseAssertion::parse_AssertionVerb(CParser *p, std::vector<HTerm>&  term)
{
    
 
    {
        // and action applying to [one visible thing and requiring light]
        CPredSequence predList = pAny("N1")	<<verb_IS_NOT()	<<p->verbList	<<pAny("N2");
         

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
            if (n1 != nullptr)
            {
                HBlock n2 = Expression::parser_expression(p, res.matchs["N2"]);
                if (n2 != nullptr)
                {
                    auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
                    return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
                }
            }
        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        CPredSequence predList = pAny("N1") <<pLiteral("not") <<p->verbList <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
            if (n1 != nullptr)
            {
                HBlock n2 = Expression::parser_expression(p, res.matchs["N2"]);
                if (n2 != nullptr)
                {
                    auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
                    return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
                }
            }

        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        CPredSequence predList = pAny("N1")     <<verb_IS() <<p->verbList <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
        {
            
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
            if (n1 != nullptr)
            {
                HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
                if (n2 != nullptr)
                {
                    auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
                    return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
                }
            }

        }
	}

	{
	// and action applying to [one visible thing and requiring light]
	CPredSequence predList = pAny("N1") << p->verbList << pAny("N2");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals) {

		auto s1 = CtoString(res.matchs["N1"]);

		HBlock n1 = Expression::parser_assertionTarger(p, res.matchs["N1"]);
		if (n1 != nullptr)
		{
			HBlock n2 = Expression::parser_expression(p, res.matchs["N2"]);
			if (n2 != nullptr)
			{
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				auto r = std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				return r;
			}
			//eh um match ?
			HBlock m2 = Expression::parser_expression(p, res.matchs["N2"]);
			if (m2 != nullptr)
			{
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				auto r = std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				return r;
			}

		}

	}

	}
	//logMessage( verbList->repr() );


	//logMessage( get_repr(term) );
	return nullptr;
}



HBlockMatchIsVerb  NSParser::ExpressionMatch::parserMatchIsConditionVerb(CParser* p, HTerm term)
{

	//Tambem pode ser um verbo definido
	{
		CPredSequence predList = pAny("MatchBody") << verb_IS() << p->verbList << pAny("valueToCheck");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = ExpressionMatch::parser_MatchArgument(p, res.matchs["MatchBody"]);
			HBlockMatch value = ExpressionMatch::parser_MatchArgument(p, res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
				//return std::make_shared<CBlockAssertion_isDirectAssign>(body, value);
			}
		}
	}


	{
		CPredSequence predList = pAny("MatchBody") << p->verbList << pAny("valueToCheck");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = ExpressionMatch::parser_MatchArgument(p, res.matchs["MatchBody"]);
			HBlockMatch value = ExpressionMatch::parser_MatchArgument(p, res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
			}
		}
	}
	return nullptr;
}


HBlockVerbRelation NSParser::Statement::Verbal::STMT_verb_relation(CParser * p, HBlock a_verb, HTerm term,   ErrorInfo *err)
{
	//CPredSequence predList = pLiteral("reverse") << pAny("Relation");
	CPredSequence predList = pOr("reverseLiteral", pLiteral("reverse"), pLiteral("reversed")) << pAny("Relation");


	MatchResult res = CMatch(term, predList);

	if (res.result == Equals) {
		// yes .. is an  reverse relation

		HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
		return   std::make_shared<CBlockVerbReverseRelation>(a_verb, a_relation);

	}
	else
	{
		auto relation_named = term->repr();
		if (relation_named[0] == '[')
		{
			err->setError("relation name must be single noun");
			return nullptr;
		}
        HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(term->repr());
        return   std::make_shared<CBlockVerbDirectRelation>(a_verb, a_relation);
    }
    return nullptr;
}
 
HBlock NSParser::Statement::Verbal::STMT_verb_Assertion_N(CParser * p, std::vector<HTerm>&  term, ErrorInfo *err)
{
 
    {

        
         
            auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
            auto L_verb = pLiteral("verb");
            auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
                                                          pOr("article", pLiteral("a"),
                                                                           pLiteral("an"), pLiteral("the")) });
            CPredSequence predList = (pOr("kindpart", L_the_verb, L_verb))	<<pAny("VerbList")	<<L_the_verb_1	<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HPred verbMatch;
            HBlock a_verb;
            //HBlockNoum a_relation_block = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
             
            if (CList *plist = asCList(res.matchs["VerbList"].get())) {
                //eh uma lista

                HTerm listExpand =  expandBract(res.matchs["VerbList"]);
                plist = asCList(listExpand.get());

                /*if (  plist->lst.back()->repr() =="of" )
                {
                    logError("verb of a relation cannot end with OF ");
                    return nullptr;
                }*/

                HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());

                verbMatch = pList("VerbMatch", {});
                auto cpList = reinterpret_cast<CPredList *>(verbMatch.get());

                for ( auto ip : plist->lst) {
                    clist->push_back(std::make_shared<CBlockNoumStr>(ip->repr()));
                    cpList->plist.push_back(pLiteral(ip->repr()));
                }
                a_verb = clist;

                p->verbList->blist.push_back(verbMatch);


                 
                return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);

            } else {
                //nao eh uma lista :-(
                return nullptr;
            }
        }

    }
    return nullptr;

}

HBlock NSParser::Statement::Verbal::STMT_verb_Assertion(CParser * p, std::vector<HTerm>&  term,  ErrorInfo *err)
{ 
 
    {
 
            auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
            auto L_verb = pLiteral("verb");
            auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
                                                          pOr("article", pLiteral("a"),pLiteral("an"), pLiteral("the")) });
            CPredSequence predList = (pOr("kindpart", L_the_verb, L_verb))	<<pAny("Verb")	<<pAny("Aux")	<<L_the_verb_1	<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            /*if (res.matchs["Aux"]->repr() =="of")
            {
                logError("verb of a relation cannot end with OF ");
                return nullptr;
            }*/
            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            //HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());

            auto verbMatch = (pList("VerbMatch", {
                    pLiteral(res.matchs["Verb"]->repr()),
                    pLiteral(res.matchs["Aux"]->repr()),
            }));

            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
        }

    }

    {
        auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
        auto L_verb = pLiteral("verb");
        
        CPredSequence predList = (pOr("kindpart", L_the_verb, L_verb))	<<pAny("Verb")	<<pAny("Aux")<<pLiteral("implies")	<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());

            /*if (res.matchs["Aux"]->repr() == "of")
            {
                logError("verb of a relation cannot end with OF ");
                return nullptr;
            }*/

            auto verbMatch = (pList("VerbMatch", {
                    pLiteral(res.matchs["Verb"]->repr()),
                    pLiteral(res.matchs["Aux"]->repr()),
            }));

            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
        }

    }

    {
        //Teste de carga

        
         
        auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
        auto L_verb = pLiteral("verb");
        auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
                                                          pOr("article", pLiteral("a"),
                                                                           pLiteral("an"), pLiteral("the")) });

        CPredSequence predList = pOr("kindpart", L_the_verb, L_verb)<<pAny("Verb")	<<L_the_verb_1	<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;

            /*if (vaux.second->repr() == "of")
            {
                logError("verb of a relation cannot end with OF ");
                return nullptr;
            }*/


           // HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);

        }

    }

    {
        //Teste de carga
            auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
            auto L_verb = pLiteral("verb");

        CPredSequence predList = pOr("kindpart", L_the_verb, L_verb)<<pAny("Verb")	<<pLiteral("implies")<<pAny("Relation") <<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;

        /*	if (vaux.second->repr() == "of")
            {
                logError("verb of a relation cannot end with OF ");
                return nullptr;
            }*/


            //HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);

        }

    }

    {
        
         
        auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
        auto L_verb = pLiteral("verb");
        auto L_the_verb_1 = pList("implies_a", { pLiteral("implies"),
                                                          pOr("article", pLiteral("a"),
                                                                           pLiteral("an"), pLiteral("the")) });

        CPredSequence predList = pOr("kindpart", L_the_verb, L_verb)<<pAny("Verb")<<L_the_verb_1<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoumStr>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoumStr>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (pList("VerbMatch", {
                            pLiteral(inList.front()->repr()),
                            pLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoumStr>(inList.front()->repr());
                    verbMatch = pLiteral(inList.front()->repr());
                }

                size_t nv = inList.size();

                //std::cout << res.matchs["Verb"]->repr() << std::endl;
                if (a_verb != nullptr) {

                    //HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
                    p->verbList->blist.push_back(verbMatch);
                    //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                    return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
                }
            } else {

                HBlock a_verb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
               // HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
                p->verbList->blist.push_back(pLiteral(res.matchs["Verb"]->repr()));
                //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
            }
        }

    }

    {
    
         
       auto L_the_verb = pList("vinitial", { pLiteral("the"), pLiteral("verb") });
       auto L_verb = pLiteral("verb");
       auto L_the_verb_4 = pLiteral("implies");

       CPredSequence predList = pOr("kindpart", L_the_verb, L_verb)<<pAny("Verb")<<L_the_verb_4<<pAny("Relation")	<<pLiteral("relation");
         
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoumStr>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoumStr>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (pList("VerbMatch", {
                            pLiteral(inList.front()->repr()),
                            pLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoumStr>(inList.front()->repr());
                    verbMatch = pLiteral(inList.front()->repr());
                }

                if (a_verb != nullptr) {
                   // HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
                    p->verbList->blist.push_back(verbMatch);
                    //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                    return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
                }
            } else {
                HBlock a_verb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
                //HBlockNoum a_relation = std::make_shared<CBlockNoumStr>(res.matchs["Relation"]->repr());
                p->verbList->blist.push_back(pLiteral(res.matchs["Verb"]->repr()));
                //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                return STMT_verb_relation(p,a_verb, res.matchs["Relation"],err);
            }
        }

    }

    return nullptr;

}










