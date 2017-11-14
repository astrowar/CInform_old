#include "PARSER.HPP"
// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Parser.hpp"
#include <list>

#include <algorithm>


#include "CBlockMatch.hpp"
 
#include "CblockAssertion.hpp"
#include "CBlockUndestand.hpp"
#include "CBlockCommand.hpp"
#include "sharedCast.hpp"
#include "CBlockComposition.hpp"


using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace NSTerm;
using namespace NSTerm::NSMatch;




NSParser::CParser::CParser( ) {
    
    {
        std::list<HPred> alist;
        verbList = std::make_shared<CPredBooleanOr>("verbList", alist);
        verbList->blist.push_back(pLiteral("contains"));
    }

    {
        std::list<HPred> alist;
        actionPredList = std::make_shared<CPredBooleanOr>("actionList", alist);
        actionPredList->blist.push_back(pLiteral("getting"));
    }

	{
		
		verbList->blist.push_back(pLiteral("relates"));
	}


    {
        //std::list<HPred> alist;
        //actionDinamicDispatch = std::make_shared<CPredBooleanOr>("actionList", alist);
        //actionDinamicDispatch->blist.push_back(pLiteral("getting"));
    }
}

 

NSParser::CParser::~CParser() {
}


// 
//HBlock NSParser::CParser::get_Noum(string named) const
//{
//	auto kv =  std::find_if(nregisters.begin(), nregisters.end(), [&](const NoumDefinition &a) {return   a.noum == named; });
// 
//	if (kv == nregisters.end()) return nullptr;
//	return kv->definition ;
//}

void NSParser::CParser::set_Noum(NoumDefinition ndef) {
    nregisters.push_back(ndef);
}

void NSParser::CParser::set_Noum(NoumDefinitions ndef) {
    nregisters.insert(nregisters.end(), ndef.begin(), ndef.end());
}



 


std::vector<HTerm> expandTerm( HTerm term)
{
    if (CList* clist =  asCList( term.get() ) )
    {
          return clist->asVector();
    }
    return {term};
}

HBlock NSParser::ParseAction::sys_say_action(CParser * p, std::vector<HTerm>&  term)
{
	CPredSequence predList = pLiteral("say")<<pAny("Body");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		//auto nterms = expandTerm(res.matchs["Body"]);
		//HBlock value = Expression::parser_expression_lst(p,nterms);	
		std::string ss =res.matchs["Body"]->repr();
		 

		HBlock value = Expression::parser_expression(p, res.matchs["Body"]);
		 
		HBlockActionNamed say_Action = std::make_shared<CBlockActionNamed>("say_text");
		return std::make_shared<CBlockActionCallNamed>(say_Action, value, nullptr);
	}
	return nullptr;
}

 

//parse a segunda parte do iterator
HBlockAssertion_is NSParser::ParseAssertion::parse_Loop_AssertionVerb(CParser * p, HTerm&  term , NoumLocation nlocation  )
{
 
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS_NOT()	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
		 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<pLiteral("not")	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS()	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				}
			}

		}

	}



	{
		// is a kind definition ??
		  CPredSequence predList = pAny("N1")	<<verb_IS_NOT() <<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				 
				 
					HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
					if (value != nullptr)
					{
						if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
						return std::make_shared<CBlockAssertion_isNotDirectAssign>(n1, value);
					}
				 
			}
		}
	}

	{
		// is a kind definition ??
		  CPredSequence predList = pAny("N1")	<<verb_IS()	<<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{ 
				HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
				if (value != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					return std::make_shared<CBlockAssertion_isDirectAssign>(n1, value);
				}

			}
		}
	}


	 

	return nullptr;


}

HBlock NSParser::ParseAssertion::sys_now_loop(CParser * p, std::vector<HTerm>&  term)
{
	
	// now every room is lighted
	// now every lamp is blazing	
	// now every good woman is in the Salon
	// now every thing carried by the player is in the impound


	// now the player carries every thing which is in the tomb
	// now the table supports every stripper who is in New Jersey
	// now Wilfred admires every woman

	  CPredSequence predList = pLiteral("now")	<<pLiteral("every")	<<pAny("Assertion");
		//<<verb_IS();
		//<<pAny("Seletor_B");
	 
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		//auto nterms = expandTerm(res.matchs["Assertion"]);
		//parse_AssertionVerb
		//parse_AssertionDirectAssign

		{
			HBlockAssertion_is now_verb = parse_Loop_AssertionVerb(p,res.matchs["Assertion"],FirstNoum);
			if (now_verb != nullptr)
			{
			 
				return std::make_shared<CBlockNow >(now_verb);
			}
		}


		 
	}

	return nullptr;
}

HBlock NSParser::ParseAssertion::sys_now_action(CParser * p, std::vector<HTerm>&  term)
{

	if ( auto nloop = sys_now_loop(p,term ))
	{
		return nloop;
	}

    {

		    // now every room is lighted
			// now every lamp is blazing
			// now Wilfred admires every woman
			// now every good woman is in the Salon
			// now everything carried by the player is in the impound
			// now the player carries every thing which is in the tomb
			// now the table supports every stripper who is in New Jersey





        CPredSequence predList = pLiteral("now") <<pAny("Assertion");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto nterms = expandTerm(res.matchs["Assertion"]);
            //parse_AssertionVerb
            //parse_AssertionDirectAssign

            {
                HBlockAssertion_is now_verb = parse_AssertionVerb(p,nterms);
                if (now_verb != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_verb);
                }
            }


            {
                HBlockAssertion_is now_is = parse_AssertionDirectAssign(p,nterms);
                if (now_is != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_is);
                }
            }
        }
    }
    return nullptr;
}



//Processa os smtm que sao do sistema
HBlock NSParser::ParseAssertion::STMT_system_Assertion(CParser * p, std::vector<HTerm>& term)
{
	auto d_say = (ParseAction::sys_say_action(p,term));
	if (d_say != nullptr) return d_say;


            auto d_now = (sys_now_action(p,term));
            if (d_now != nullptr) return d_now;

    return nullptr;
}

 



//Uma das rotinas mais importantes. Ela altera  o proprio parser
HBlock NSParser::ParseAssertion::STMT_understand_Assertion(CParser * p, std::vector<HTerm>&  term) {

    auto d_action = (DynamicDispatch::DynamicDispatch_action(p,term));
    if (d_action != nullptr) return d_action;
    

    auto p_action = DynamicDispatch::STMT_understand_Action_Assertion_static(p,term);
    if (p_action != nullptr) return p_action;

    return nullptr;
}


HBlock NSParser::ParseAssertion::parse_removeArticle(CParser * p, std::vector<HTerm>& term) {
    if (term.size() > 1) {

        if (pLiteral("the")->match(term.front()) == Equals) {
            auto gtail = get_tail(term);
            return Expression::parser_expression_lst(p,gtail);
        }
    }
    return nullptr;
}


HBlockNoum NSParser::ParseAssertion::parse_noum(CParser * p, std::vector<HTerm>& term)
{

	// anula se tiver uma palavra chave reservada
	


    CPredSequence predList= pAny("Noum");
     
 
    MatchResult res = CMatch(term, predList);

    if (res.result == Equals) 
	{
        string nstr = CtoString(res.matchs["Noum"]->removeArticle() );

		 
		if (nstr == "where")return nullptr;
		if (nstr == "called")return nullptr;
		if (nstr == "which")return nullptr;
		if (nstr == "and")return nullptr;
		if (nstr == "or")return nullptr;
		if (nstr == ",")return nullptr; 
		if (nstr == ".")return nullptr;

		if ((nstr.find("where") != std::string::npos) || (nstr.find("called") != std::string::npos) || (nstr.find("which") != std::string::npos))
		{
			return nullptr;
		}

		if ((nstr.find(",") != std::string::npos)  )
		{
			return nullptr;
		}

		if ((nstr.find("[") != std::string::npos))
		{
			return nullptr;
		}

		return std::make_shared<CBlockNoum>(nstr);
    }
    return nullptr;
}

HBlockAssertion_isInstanceOf NSParser::CParser::parseAssertion_isInstanceOf(std::vector<HTerm>& term) {
    //Injstance is Alwares derivadefrom a Kind
    {
        // is a kind definition ??
        auto L_a_an_kind = pList("kindpart", {verb_IS(), undefinedArticle()});
        auto L_are_kinds = pList("kindpart", {verb_IS()});

        CPredSequence predList = pAny("Noum") << L_a_an_kind <<pAny("KindBase");

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
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




HBlock NSParser::ParseAssertion::parseAssertionFirstTerm_Compose(CParser *p, HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = ParseList::parseAssertionFirstTerm_COMMA_AND(p,term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}


HBlock NSParser::ParseAssertion::parseAssertionFirstTerm(CParser *p, HTerm term) {
    return parseAssertionFirstTerm_Compose(p,term);
}


HBlock NSParser::ParseAssertion::parseAssertionEnumSecondTerm(CParser *p, HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = ParseList::parseAssertionFirstTerm_COMMA_OR(p,term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}

HBlock NSParser::ParseAssertion::STMT_Decide_Assertion(CParser * p, std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err)
{
    HBlock assert_decide = ParseDecide::parseAssertion_isDecide(p,lst,inner,err);
    if (assert_decide != nullptr) {
        return assert_decide;
    }

	HBlock assert_decide_on = ParseDecide::parseAssertion_DecideOn(p,lst, inner, err);
	if (assert_decide_on != nullptr)
	{
		return assert_decide_on;
	}

    return nullptr;

}


 
HBlock NSParser::ParseAssertion::parse_RelationArgument(CParser * p, std::vector<HTerm>& term)
{
	{
		CPredSequence predList = pAny("obj_s")<<pLiteral("to")	<<pAny("obj_d");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock a = Expression::parser_expression(p, res.matchs["obj_s"]);
			if (a != nullptr) {
				HBlock b = Expression::parser_expression(p, res.matchs["obj_d"]);
				if (b != nullptr)
				{
					return std::make_shared<CBlockRelationArguments>(a, b);
				}
			}
		}
	}
	return nullptr;


}



HBlock  NSParser::ParseAssertion::parse_PropertyOf(CParser * p, std::vector<HTerm>& term) {

	{
		CPredSequence predList = mk_HPredLiteral_OR("article", { "a", "an" }) <<pLiteral("list")<<pLiteral("of")<<pAny("kindBase");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind = Expression::parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				return  std::make_shared<CBlockCompositionList>(nkind);
			}
		}
	}

	{
			CPredSequence predList = pLiteral("list")<<pLiteral("of")	<<pAny("kindBase");

			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockKind nkind = Expression::parser_kind_specification(p, res.matchs["kindBase"]);
				if (nkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionList>(  nkind);
				}
			}
	}


	{

        CPredSequence predList = pAny("property") <<pLiteral("of") <<pAny("obj");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
            HBlock a = Expression::parser_expression(p,res.matchs["property"]);
            if (a != nullptr) {
                HBlock b = Expression::parser_expression(p,res.matchs["obj"]);
                if (b != nullptr) {
                    //HBlockNoum  object_Name = std::make_shared<CBlockNoum>(res.matchs["obj"]->removeArticle()->repr());
                    return std::make_shared<CBlockProperty>(a, b);
                }
            }
        }
    }




    //{
    //	std::cout << get_repr(term) << std::endl;
    //	CPredSequence predList;
    //	<<pLiteral("the");
    //	<<pAny("property");
    //	<<pLiteral("of");
    //	<<pAny("obj");
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


HBlockEnums NSParser::ParseAssertion::parseAssertion_EnumTerms(CParser * p, HTerm enumList) {

    HBlockList elist = std::make_shared<CBlockList>(std::list<HBlock>());
    elist = ParseList::parseAssertionFirstTerm_COMMA_OR(p,enumList, elist);
    if (elist->lista.empty()) {
        return nullptr;
    }

    std::vector<HBlockNoum> nlist;
    std::for_each(elist->lista.begin(), elist->lista.end(),
                  [&nlist](HBlock c) { nlist.push_back(DynamicCasting::asHBlockNoum(c)); });
    return std::make_shared<CBlockEnums>(nlist);

}


HBlock NSParser::ParseAssertion::STMT_canBe_Assertion(CParser * p, std::vector<HTerm>& lst) {
    
	CPredSequence predList =pAny("Target") <<pLiteral("can") <<pLiteral("be") <<pAny("EnumValues");

    MatchResult res = CMatch(lst, predList);

    if (res.result != Equals) return nullptr;

    HBlockEnums definitionSecond = parseAssertion_EnumTerms(p,res.matchs["EnumValues"]);
    if (definitionSecond == nullptr) {
        return nullptr;
    }

    

    HBlock defintionFirst_Noum = Expression::parser_assertionTarger(p,res.matchs["Target"]);
    if (defintionFirst_Noum != nullptr) {
        return std::make_shared<CBlockAssertion_canBe>(defintionFirst_Noum, definitionSecond);
    }

    return nullptr;
}

HBlockInstanceVariable NSParser::ParseAssertion::CProperty_called(CParser * p, HTerm term) {
    {
        // the torch has a brightness called brightnessLevel ;
        CPredSequence predList = pAny("kindName") <<pLiteral("called") <<pAny("propName");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockNoum a = std::make_shared<CBlockNoum>(res.matchs["kindName"]->repr());
            HBlockNoum b = std::make_shared<CBlockNoum>(res.matchs["propName"]->repr());
            return std::make_shared<CBlockInstanceVariable>(a, b);
        }

    }

    {
        // the torch has a brightness   ;  -> called brightness
        HBlockNoum a = std::make_shared<CBlockNoum>(term->repr());
        HBlockNoum b = std::make_shared<CBlockNoum>(term->repr());
        return std::make_shared<CBlockInstanceVariable>(a, b);
    }

}


HBlock NSParser::ParseAssertion::STMT_hasAn_Assertion(CParser * p, std::vector<HTerm>& lst) {
    CPredSequence predList = pAny("Target") <<pLiteral("has")  <<undefinedArticle() <<pAny("KindAndName");
    MatchResult res = CMatch(lst, predList);

    if (res.result != Equals) {
        return nullptr;
    }

    HBlockInstanceVariable definitionProperty_kindAndName = CProperty_called(p,res.matchs["KindAndName"]);
    if (definitionProperty_kindAndName == nullptr) {
        return nullptr;
    }

    //HBlockNoum  defintionFirst_KindOrInstance = std::make_shared<CBlockNoum>( res.matchs["Target"]->removeArticle()->repr());
    HBlock defintionFirst_KindOrInstance = Expression::parser_kind_or_instance(p,res.matchs["Target"]);

    return std::make_shared<CBlockAssertion_InstanceVariable>(defintionFirst_KindOrInstance,
                                                              definitionProperty_kindAndName);
}



HBlock NSParser::Statement::parser_stmt(CParser * p, HTerm term, HGroupLines inner, ErrorInfo *err) {
    if (CList *vlist = asCList(term.get())) {
        auto v = vlist->asVector();
        auto r = parser_stmt_inner(p,v,inner,err);
        /*if (r == nullptr)
            std::cout << term->repr() << std::endl;*/

        return r;
    }
    return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
}


 







HBlock NSParser::Statement::parser_stmt_str(CParser * p, string str, HGroupLines inner, ErrorInfo *err) {
    str = decompose_bracket(str, "(");
    str = decompose_bracket(str, ")");
    str = decompose_bracket(str, ",");
	str = decompose_bracket(str, "\"");
    std::vector<HTerm> lst = decompose(str);
    return Statement::parser_stmt_inner(p,lst,inner,err);
}


HBlock NSParser::Statement::Parser_Stmt(CParser * p, string str, bool dump )
{
	ErrorInfo err;
		return Statement::parser_stmt(p,str, dump, &err);
}

 


HBlock NSParser::Expression::Parser_Expression(CParser * p, string str, bool dump)
{
	ErrorInfo err;
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	str = decompose_bracket(str, "\"");
	str = decompose_bracket(str, ";");

	std::vector<HTerm> lst = decompose(str);
	auto term = convertToTerm(lst);
	auto b = Expression::parser_expression(p,term);
	if (dump)
	{
		b->dump(" ");
		printf("\n");
	}
	return b;
}



HBlock NSParser::CParser::Parser_Condition(string str, bool dump)
{
	ErrorInfo err;
	
	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	std::vector<HTerm> lst = decompose(str);
	auto term = convertToTerm(lst);
	auto b = ControlFlux::parser_if_condition(this,term);
	if (dump)
	{
		b->dump(" ");
		printf("\n");
	}
	return b;
}


HBlock NSParser::Statement::parser_stmt(CParser *p, string str,bool dump,ErrorInfo *err)
{
    HBlock b = Statement::parser_stmt_str(p,str,nullptr, err); //nao tem inner
    if (dump)
    {		
        b->dump("");  
        printf("\n");
    }
    return b;
}

std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(str.substr(prev));

	return strings;
}



std::vector<string>  split_new_lines(const string &str)   {

	return  split_string(str, "\n");
	 

    auto p1 = str.begin();
    auto p2 = str.begin();
    std::vector<string> sentences;
    while (p2 != str.end())
    {
        if (*p2 =='\n')
        {
            sentences.push_back( string(p1,p2));
            printf("%s\n", sentences.back().c_str());
            p1 = p2;
            ++p1;
            p2 = p1;
            if (p2 == str.end()) break;
        }
        ++p2;
    }
    if(p1 != p2 )
    {
        sentences.push_back( string(p1,p2));
        printf("%s\n", sentences.back().c_str());
    }
   return sentences;
}
 
 HBlock  NSParser::Statement::parser_GroupLine(CParser * p, std::string v , HGroupLines inner, ErrorInfo *err)
{
	auto vstr = decompose_bracket(v, "(");
	vstr = decompose_bracket(vstr, ")");
	vstr = decompose_bracket(vstr, "\"");
	vstr = decompose_bracket(vstr, ",");
	vstr = decompose_bracket(vstr, ":");
	std::vector<HTerm> lst = decompose(vstr);
	 
	HBlock  rblock_stmt = parser_stmt_inner (p,lst, inner , err);
	if (rblock_stmt ==nullptr)
	{
		logError("|" + vstr+"|");
		logError("parser Error :" + v );
	}
	if (err->hasError)
	{
		logError("parser Error :" + v);
		return nullptr;
	}
	return rblock_stmt;
}

 HBlockComandList NSParser::Statement::parser_stmt_inner(CParser * p, HGroupLines inner, ErrorInfo *err)
{
	std::list<HBlock> retBlocks;
	if (inner == nullptr)
	{
		return nullptr;
	}

	while (inner != nullptr)
	{
		for (auto it = inner->lines.begin(); it != inner->lines.end(); ++it)
		{
			HBlock blk;
			std::string rawLine = it->line;
			auto inext = std::next(it);
			HGroupLines _inner = nullptr;
			if (inext == inner->lines.end()) _inner = inner->inner;
			 
		 
			blk = parser_GroupLine(p,rawLine, _inner, err);
			if (blk == nullptr)
			{
			
				logError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				err->setError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				return nullptr;
			}

			if (err->hasError)
			{
				 
				logError(err->msg + " at line " + std::to_string(inner->lines.front().linenumber));
				return nullptr;
			}
			retBlocks.push_back(blk);

		}
		inner = inner->next;
		if (inner == nullptr) break;
	}

	retBlocks = ControlFlux::post_process_tokens(p,retBlocks ,  err );
	if (retBlocks.empty())
	{	 
		
			logError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
			err->msg = err->msg + "at line " + std::to_string(inner->lines.front().linenumber);
		
	 
		if (err->hasError)
		{
			logError(err->msg + " at line " + std::to_string(inner->lines.front().linenumber));
			return nullptr;
		}
	}

	return  std::make_shared< CBlockComandList >(retBlocks);

}
 
HBlock NSParser::ParseText::parser_text(CParser *p, string str , ErrorInfo *err)
{
	 
    // quebra o text  em linhas e processa as linhas separadamente
    auto vlist = split_new_lines(str);
	HGroupLines pivot =  get_identation_groups(p,"__FILE__",vlist,err);
	if (err->hasError)
	{
		return nullptr;
	}
	if (pivot == nullptr)
	{
		return nullptr;
	}
	 
    auto blist  = Statement::parser_stmt_inner(p,pivot,err); 
	if (err->hasError) return nullptr;
	return  blist;

	 

}


//interprete varias linhas de texto
HBlock NSParser::ParseText::parser_text(CParser *p, string str, bool dump )
{
	ErrorInfo err;
    HBlock b =  parser_text(p,str,&err);
    if (b) {
        if (dump) {
            b->dump("");
            printf("\n");
        }
    }
    else
    {
        printf("Parser Error\n");
    }
    return b;
}