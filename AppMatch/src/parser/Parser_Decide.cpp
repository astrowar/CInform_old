// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include <memory>
#include "parser/Parser.hpp"
#include "CBlockDecideIf.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


HBlockMatch NSParser::ParseDecide::parser_What_Which_Assertion(CParser * p, HTerm term)
{
	{
		// which (Person) is (the targert) -> Enforce (Return Value) as Person
		CPredSequence predList = mk_What_Which()	<<pAny("kindReturn") <<verb_IS()<<pAny("RemainderQuery");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = ExpressionMatch::parser_expression_match(p,res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				return AdjetiveMatch;
				//return std::make_shared<CBlockMatchDirectIs>(c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);

				return nullptr;
			}
		}
	}
	return nullptr;
}

HBlockMatchIs NSParser::ParseDecide::parser_What_Which_Verb_Assertion(CParser * p, HTerm term)
{
	{// which (Person) is (the targert) -> Enforce (Return Value) as Person
		CPredSequence predList = mk_What_Which() <<pAny("kindReturn")	<<p->verbList	<<pAny("RemainderQuery");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));


			HBlockMatch  c1 = ExpressionMatch::parser_MatchArgument(p,res.matchs["kindReturn"]);
			HBlockMatch  AdjetiveMatch = ExpressionMatch::parser_expression_match(p,res.matchs["RemainderQuery"]);

			if (AdjetiveMatch != nullptr)
			{
				//auto adjBlockMatch = std::make_shared<CBlockMatchBlock >(AdjetiveMatch);
				//return AdjetiveMatch;
				return std::make_shared<CBlockMatchIsVerb>(vrepr, c1, AdjetiveMatch);
				//return std::make_shared<CBlockMatch>(body);


				return nullptr;
			}
		}
	}
	return nullptr;
}


HBlockMatchIs NSParser::ParseDecide::parser_Match_IF_Assertion(CParser * p, HTerm term )
{
    

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << verb_IS() << pAny("ADV") << pLiteral("than") << pAny("BValue");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			auto vrepr = CtoString(expandBract(res.matchs["ADV"]));

			return std::make_shared<CBlockMatchIsAdverbialComparasion>(vrepr, AValue, BValue);
		}
	}
	{
		CPredSequence predList = pLiteral("if")	<<pAny("AValue")<< p->verbList	<<pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchIsVerb >(vrepr, AValue, BValue);
		}
	}

	{
		CPredSequence predList = pLiteral("if")	<<pAny("AValue")	<<verb_IS()	<<pAny("BValue");


		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockMatchDirectIs>(AValue, BValue);
		}
	}

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1") << pWord("C2") << pWord("C3") << pWord("C4") << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					HBlockMatch NC3 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C3"]);
					HBlockMatch NC4 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C4"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) && (NC3 != nullptr) && (NC4 != nullptr))
					{
						std::list<HBlockMatch> _matchList = { NC1,NC2,NC3,NC4 };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}



	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1")<< pWord("C2")<< pWord("C3") << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					HBlockMatch NC3 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C3"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) && (NC3 != nullptr))
					{
						std::list<HBlockMatch> _matchList = {NC1,NC2,NC3};
						HBlockMatchList mlist =  std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}					
				}
			}
		}
	}

	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1") << pWord("C2")   << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);
					HBlockMatch NC2 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C2"]);
					if ((NC1 != nullptr) && (NC2 != nullptr) )
					{
						std::list<HBlockMatch> _matchList = { NC1,NC2  };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}


	{
		CPredSequence predList = pLiteral("if") << pAny("AValue") << pWord("C1")   << pAny("BValue");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
			if (AValue != nullptr)
			{
				HBlockMatch BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
				if (BValue != nullptr)
				{
					HBlockMatch NC1 = ExpressionMatch::parse_match_SigleNoum(p, res.matchs["C1"]);	
					if ((NC1 != nullptr)  )
					{
						std::list<HBlockMatch> _matchList = { NC1  };
						HBlockMatchList mlist = std::make_shared<CBlockMatchList >(_matchList);
						return std::make_shared<CBlockMatchIsVerbComposition >(mlist, AValue, BValue);
					}
				}
			}
		}
	}


    {
        CPredSequence predList = pLiteral("if") << pAny("AValue")  ;
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch AValue = ExpressionMatch::parser_expression_match(p, res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;
            auto r =  res.matchs["AValue"].get();
			
			//return std::make_shared<CBlockMatchIs>(AValue );
			logError(r->repr());
			return nullptr;
        }
    }

    return nullptr;

}



HBlock NSParser::ParseDecide::parseAssertion_isDecide_inLine(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{

   
	if (inner == nullptr)
	{
		{
			  CPredSequence predList = pLiteral("to") <<pLiteral("decide")<<pAny("Match")	<<pLiteral(":")	<<pAny("RemainBody");
		 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) {
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"] );
				if (a_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


				HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match)
				{

					HBlock body = Expression::parser_expression(p, res.matchs["RemainBody"]);
					return std::make_shared<CBlockToDecideWhat>(w_match, body);
				}


				 


			}
		}
	}

	if (inner != nullptr)
	{
		//Com bloco inner 
		{

			  CPredSequence predList = pLiteral("to")	<<pLiteral("decide")	<<pAny("Match") <<pLiteral(":");
 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) {
				HBlockMatchIs a_match = parser_Match_IF_Assertion(p, res.matchs["Match"]);
				if (a_match!=nullptr )
				{
					HBlockComandList body =   Statement::parser_stmt_list(p, false, inner, err);
					return std::make_shared<CBlockToDecideIf>(a_match, body);
				}

				HBlockMatchIs vb_match = parser_What_Which_Verb_Assertion(p, res.matchs["Match"]);
				if (vb_match != nullptr)
				{

					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					return std::make_shared<CBlockToDecideWhat_FirstNoum>(vb_match, body);
				}


				HBlockMatch w_match = parser_What_Which_Assertion(p, res.matchs["Match"]);
				if (w_match != nullptr)
				{
					 
					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					return std::make_shared<CBlockToDecideWhat>(w_match, body);
				}


			}
		}


	

		{
			// to doing somethig with another thing
			CPredSequence predList  = pLiteral("to") <<pWord("Verb") <<pAny("Match_arg1")	<<pPreposition("pred") <<pAny("Match_arg2")	<<pLiteral(":");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
				HBlockMatch  marg1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["Match_arg1"]);
				if (marg1 != nullptr)
				{
					HBlockMatch  marg2 = ExpressionMatch::parser_MatchArgument(p, res.matchs["Match_arg2"]);
					if (marg2 != nullptr)
					{

						HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
						if (body != nullptr)
						{
							HBlockNoum nVerb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
							HBlockNoum nPred = std::make_shared<CBlockNoumStr>(res.matchs["pred"]->repr());
							HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(nVerb,nullptr , nPred, marg1 , marg2);
							p->phrases.push_back(nheader);
							return std::make_shared<CBlockPhraseDefine>(nheader, body);
						}
					} 
				}
			}
		}

		 

		{
			//To say something
			CPredSequence predList = pLiteral("to") << pWord("Verb") << pAny("Match_arg1")  << pLiteral(":");
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatch  marg1 = ExpressionMatch::parser_MatchArgument(p, res.matchs["Match_arg1"]);
				if (marg1 != nullptr)
				{
					HBlockComandList body = Statement::parser_stmt_list(p, false, inner, err);
					if (body != nullptr)
					{
						HBlockNoum nVerb = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
						HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(nVerb, nullptr, nullptr, marg1, nullptr);
						p->phrases.push_back(nheader);
						return std::make_shared<CBlockPhraseDefine>(nheader, body);
					}

				}
			}
		}

	}


    return nullptr;
}


HBlock NSParser::ParseDecide::parseAssertion_isDecide (CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{
	return parseAssertion_isDecide_inLine(p, term, inner, err);
}


HBlock NSParser::ParseDecide::parseAssertion_DecideOn(CParser * p, std::vector<HTerm>&  term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{
		{
			  CPredSequence predList =  			pLiteral("decide") <<pLiteral("on")	<<pAny("ExpressionBody");
			 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals) 
			{
					logMessage((res.matchs["ExpressionBody"]->repr()));
					HBlock body = Expression::parser_expression(p, res.matchs["ExpressionBody"]);
					return std::make_shared<CBlockToDecideOn>( body);
			}
		}
	}
	 
		return nullptr;
	 


}

HBlock NSParser::ParseDecide::STMT_Definition_Assertion(CParser * p, std::vector<HTerm>&  term)
{

    {
		  auto c1 = pList({ pLiteral("definition"), pLiteral(":") });
		  auto c2 = pLiteral("definition:");

		  CPredSequence predList  = (pOr("kindpart", c1, c2))	<<pAny("Match") <<pLiteral("if")	<<pAny("LogicalBody");
		 

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			HBlockMatchIsVerb  v_match = ExpressionMatch::parserMatchIsConditionVerb (p,res.matchs["Match"]);
			if (v_match != nullptr)
			{
				HBlock body = Statement::parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(v_match, body);
			}

			HBlockMatchIs a_match = ExpressionMatch::parserMatchIsCondition(p,res.matchs["Match"]);
			if (a_match != nullptr)
			{
				HBlock body = Statement::parserBoolean(p, res.matchs["LogicalBody"]);
				return std::make_shared<CBlockToDecideIf>(a_match, body);
			}
			return nullptr;
        }
    }
    return nullptr;
}






HBlock NSParser::ParseDecide::parse_toDecide_Entry(CParser * p, std::vector<HTerm>&  term) 
{
    {
        CPredSequence predList = pLiteral("to") <<pLiteral("decide") <<pLiteral(":");
        return nullptr;
    }
}

HBlock NSParser::ParseDecide::parse_toDecide_Ret(CParser * p, std::vector<HTerm>&  term) {
    {
        CPredSequence predList = pLiteral("decide") <<pLiteral("on") <<pAny("Subst");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_expression(p,res.matchs["Subst"]);
            if (n1 == nullptr) return nullptr;
            return std::make_shared<CBlockToDecideOn>(n1);
        }
    }
    return nullptr;
}

HBlock NSParser::ParseDecide::parser_decides_Assertion(CParser * p, std::vector<HTerm>&  term) 
{

    HBlock verb_decideIn = parse_toDecide_Entry(p,term);
    if (verb_decideIn != nullptr) {
        return verb_decideIn;
    }

    HBlock verb_decideRet = parse_toDecide_Ret(p,term);
    if (verb_decideRet != nullptr) {
        return verb_decideRet;
    }

    return nullptr;


}





