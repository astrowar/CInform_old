// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;




HBlockAssertion_is NSParser::ParseAssertion::parse_AssertionVerb(CParser *p, std::vector<HTerm>&  term)
{
    
 
	{
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList ={};
		 
		{
			predList.push_back(mkHPredAny("N1"));
			predList.push_back(verb_IS_NOT());
			predList.push_back(p->verbList);
			predList.push_back(mkHPredAny("N2"));
		}

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
            HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
            return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
        }
    }

    {
        // and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList = {};
	 
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(p->verbList);
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
            HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
            return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);

        }
    }

    {
        // and action applying to [one visible thing and requiring light]
		std::vector<HPred> predList = {};
		 
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(verb_IS());
        predList.push_back(p->verbList);
        predList.push_back(mkHPredAny("N2"));

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
		std::vector<HPred> predList = {};
		 
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(p->verbList);
        predList.push_back(mkHPredAny("N2"));
		 
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			auto s1 = CtoString(res.matchs["N1"]);
			 
            HBlock n1 = Expression::parser_assertionTarger(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
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



HBlockMatchIsVerb  NSParser::ExpressionMatch::parserMatchIsConditionVerb(CParser* p,HTerm term)
{
 
	//Tambem pode ser um verbo definido
	{
		std::vector<HPred> predList = {};
	 
		predList.push_back(mkHPredAny("MatchBody"));
		predList.push_back(verb_IS());
		predList.push_back(p->verbList);
		predList.push_back(mkHPredAny("valueToCheck"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = ExpressionMatch::parser_MatchArgument(p,res.matchs["MatchBody"]);
			HBlockMatch value = ExpressionMatch::parser_MatchArgument(p,res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
				//return std::make_shared<CBlockAssertion_isDirectAssign>(body, value);
			}
		}
	}


	{
		std::vector<HPred> predList = {};
	 
		predList.push_back(mkHPredAny("MatchBody"));
		predList.push_back(p->verbList);
		predList.push_back(mkHPredAny("valueToCheck"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = ExpressionMatch::parser_MatchArgument(p,res.matchs["MatchBody"]);
			HBlockMatch value = ExpressionMatch::parser_MatchArgument(p,res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
			}
		}
	}
return nullptr;
}


HBlockVerbRelation NSParser::Statement::Verbal::STMT_verb_relation(CParser * p, HBlock a_verb, HTerm term)
{
	std::vector<HPred> predList = {};
	if (predList.empty())
	{
		predList.push_back(mk_HPredLiteral("reverse"));
		predList.push_back(mkHPredAny("Relation"));
	}
	MatchResult res = CMatch(term, predList);

	if (res.result == Equals) {
		// yes .. is an  reverse relation
		
		HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
		return   std::make_shared<CBlockVerbReverseRelation>(a_verb, a_relation);
		 
	}
	else
	{
		HBlockNoum a_relation = std::make_shared<CBlockNoum>(term->repr());
		return   std::make_shared<CBlockVerbDirectRelation>(a_verb, a_relation);
	}
	return nullptr;
}
 
HBlock NSParser::Statement::Verbal::STMT_verb_Assertion_N(CParser * p, std::vector<HTerm>&  term)
{
 
    {

		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("VerbList"));
			auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies"),
														  mkHPredBooleanOr("article", mk_HPredLiteral("a"),
																		   mk_HPredLiteral("an"), mk_HPredLiteral("the")) });
			predList.push_back(L_the_verb_1);
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HPred verbMatch;
            HBlock a_verb;
            //HBlockNoum a_relation_block = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
			 
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

                verbMatch = mkHPredList("VerbMatch", {});
                CPredList *cpList = reinterpret_cast<CPredList *>(verbMatch.get());

                for (auto ip : plist->lst) {
                    clist->push_back(std::make_shared<CBlockNoum>(ip->repr()));
                    cpList->plist.push_back(mk_HPredLiteral(ip->repr()));
                }
                a_verb = clist;

                p->verbList->blist.push_back(verbMatch);


				 
                return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);

            } else {
                //nao eh uma lista :-(
                return nullptr;
            }
        }

    }
    return nullptr;

}

HBlock NSParser::Statement::Verbal::STMT_verb_Assertion(CParser * p, std::vector<HTerm>&  term) 
{

 
    {

		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			predList.push_back(mkHPredAny("Aux"));

			auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies"),
														  mkHPredBooleanOr("article", mk_HPredLiteral("a"),
																		   mk_HPredLiteral("an"), mk_HPredLiteral("the")) });
			predList.push_back(L_the_verb_1);
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

			/*if (res.matchs["Aux"]->repr() =="of")
			{
				logError("verb of a relation cannot end with OF ");
				return nullptr;
			}*/
            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            //HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
			return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
        }

    }

    {

		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			predList.push_back(mkHPredAny("Aux"));
			predList.push_back(mk_HPredLiteral("implies"));
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

			/*if (res.matchs["Aux"]->repr() == "of")
			{
				logError("verb of a relation cannot end with OF ");
				return nullptr;
			}*/

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
			return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
        }

    }

    {
        //Teste de carga

		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies"),
														  mkHPredBooleanOr("article", mk_HPredLiteral("a"),
																		   mk_HPredLiteral("an"), mk_HPredLiteral("the")) });

			predList.push_back(L_the_verb_1);
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
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


           // HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
			return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);

        }

    }

    {
        //Teste de carga

		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			predList.push_back(mk_HPredLiteral("implies"));
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
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


            //HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            p->verbList->blist.push_back(verbMatch);
            //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
			return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);

        }

    }

    {
		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			auto L_the_verb_1 = mkHPredList("implies_a", { mk_HPredLiteral("implies"),
														  mkHPredBooleanOr("article", mk_HPredLiteral("a"),
																		   mk_HPredLiteral("an"), mk_HPredLiteral("the")) });

			predList.push_back(L_the_verb_1);
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                int nv = inList.size();

                //std::cout << res.matchs["Verb"]->repr() << std::endl;
                if (a_verb != nullptr) {

                    //HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    p->verbList->blist.push_back(verbMatch);
                    //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
					return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
                }
            } else {

                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
               // HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                p->verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
				return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
            }
        }

    }

    {
		std::vector<HPred> predList = {};
		if (predList.empty())
		{
			auto L_the_verb = mkHPredList("vinitial", { mk_HPredLiteral("the"), mk_HPredLiteral("verb") });
			auto L_verb = mk_HPredLiteral("verb");
			predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
			predList.push_back(mkHPredAny("Verb"));
			auto L_the_verb_4 = mk_HPredLiteral("implies");
			predList.push_back(L_the_verb_4);
			predList.push_back(mkHPredAny("Relation"));
			predList.push_back(mk_HPredLiteral("relation"));
		}
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                if (a_verb != nullptr) {
                   // HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    p->verbList->blist.push_back(verbMatch);
                    //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
					return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
                }
            } else {
                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
                //HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                p->verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                //return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
				return STMT_verb_relation(p,a_verb, res.matchs["Relation"]);
            }
        }

    }

    return nullptr;

}










