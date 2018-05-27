// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Eraldo Rangel on 12/10/16.
//
#include "Parser.hpp"
#include "CBlockControlFlux.hpp"
#include "sharedCast.hpp"


using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

 

HBlock NSParser::ControlFlux::stmt_resultflag(CParser *p, std::vector<HTerm>&   term)
{
	{
		 CPredSequence predList  = pLiteral("stop")	<<pLiteral("the")	<<pLiteral("action")	<<pLiteral("with")	  <<pAny("BValue");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock BValue = Expression::parser_expression(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockExecutionResultFlag>( PhaseResultFlag::actionStop , BValue);
		}
	}

	{
		CPredSequence predList = pLiteral("stop")<<pLiteral("the")	<<pLiteral("action");
		 
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return std::make_shared<CBlockExecutionResultFlag>(PhaseResultFlag::actionStop, nullptr);
		}
	}

	{
		  CPredSequence predList = pLiteral("continue")	<<pLiteral("the")	<<pLiteral("action");
	 

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return std::make_shared<CBlockExecutionResultFlag>(PhaseResultFlag::actionContinue, nullptr);
		}
	}
	return nullptr;

}


HBlock   NSParser::ControlFlux::parser_if_condition(CParser *p, HTerm term  )
{

 	 

    {
        CPredSequence predList = pAny("AValue") <<pLiteral("or") <<pAny("BValue");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_if_condition(p,res.matchs["AValue"]  );
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_if_condition(p,res.matchs["BValue"] );
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockBooleanOR>(AValue, BValue);
        }
    }
	 

	{
		CPredSequence predList = pAny("AValue")	<<pLiteral("and")	<<pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock AValue = parser_if_condition(p, res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock BValue = parser_if_condition(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockBooleanAND>(AValue, BValue);
		}
	}

	{
		CPredSequence predList = pAny("AValue") << verb_IS() << pAny("ADV") << pLiteral("than")  << pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs["ADV"]));

			HBlock AValue = Expression::parser_expression(p, res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = ExpressionMatch::parser_expression_match(p, res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			return std::make_shared<CBlockIsAdverbialComparasion >(vrepr, AValue, BValue);		 

		}
	}

	{
		CPredSequence predList = pAny("AValue") <<verb_IS()	<<pLiteral("not")<<( p->verbList)	<<pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[ p->verbList->named]));

			HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);

		}
	}
	{
		CPredSequence predList = pAny("AValue")	<<verb_IS()	<<p->verbList	<<pAny("BValue");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

			HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
		}
	}

  

   
 {
        CPredSequence predList = pAny("AValue") <<pLiteral("not") <<p->verbList <<pAny("BValue");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
       
        }
    }
    {
        CPredSequence predList = pAny("AValue") <<p->verbList <<pAny("BValue");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }


    {
        CPredSequence predList = pAny("AValue")    <<verb_IS()	<<pLiteral("not") <<pAny("BValue");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            auto vbool =  std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
        }
    }



	   {
        CPredSequence predList = pAny("AValue")      <<verb_IS() <<pAny("BValue");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }

	 
    return Expression::parser_expression (p, term); //default ...

    return nullptr;

}

HBlock   NSParser::ControlFlux::parser_control_else(CParser *p, std::vector<HTerm>& term,   HGroupLines inner, ErrorInfo *err) {
	{
		  CPredSequence predList =  mk_HPredLiteral_OR("else", { "else" , "otherwise" })<<pLiteral(":")<<pAny("body");

	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			

			HBlock ABody = Statement::parser_stmt(p,res.matchs["body"], inner, err);
			if (ABody == nullptr || inner != nullptr)
			{
				err->setError("error on Select Item ");
				return nullptr;
			}
			auto token_else = std::make_shared<CBlockControlToken >("else", ABody);
			return token_else;

			// return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
		}
	}
	
	{
        CPredSequence predList = mk_HPredLiteral_OR("else", { "else" , "otherwise" })<<pLiteral(":");
 
        
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
           
			 
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)  return nullptr;
			auto token_else = std::make_shared<CBlockControlToken >("else",executeBlock);
			return token_else;

           // return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
        }
    }
	 

    return nullptr;
}


HBlock   NSParser::ControlFlux::parser_control_end(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	//{
	//	static CPredSequence predList = {};
	//	if (predList.empty()) {
	// <<pLiteral("end");

	//	}
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals) {

	//		auto token_else = std::make_shared<CBlockControlToken >("end");
	//		return std::make_shared<CBlockList  >(std::list<HBlock>({ token_else }));
	//	}
	//}
	return nullptr;
}


 
HBlock  NSParser::ControlFlux::parser_control_for_loop(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if (inner != nullptr)
	{
	 CPredSequence predList = pLiteral("for")	<<pLiteral("each")	<<pAny("Condition")	<<pLiteral(":");			 
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch ill_variable = ExpressionMatch::parser_MatchArgument(p, res.matchs["Condition"]);
			HBlock executeBlock = Statement::parser_stmt_inner(p, inner, err);
			if (executeBlock == nullptr)
			{
				err->setError("missing Body loop block ");
				return nullptr;
			}
			auto control_forLoop = std::make_shared<CBlockControlForEach >(ill_variable, executeBlock );
			return control_forLoop;
		}
	
	}

	return nullptr;
}

HBlock  NSParser::ControlFlux::parser_control_if(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if(inner == nullptr)
	{
		CPredSequence predList = pLiteral("if")  <<pAny("Condition") <<pLiteral(":")  <<pAny("body");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{


			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"] );

			HBlock ABody = Statement::parser_stmt(p, res.matchs["body"], nullptr, err); // aqui tem erro
			if (ABody == nullptr  )
			{
				logError(res.matchs["body"]->repr());
				err->setError("error on body   ");
				return nullptr;
			} 
			auto control_if = std::make_shared<CBlockControlIF >(ACondition, ABody, nullptr);
			return control_if;
		}

	}
	else 
    {
		  CPredSequence predList = pLiteral("if")	<<pAny("Condition")	<<pLiteral(":");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
        {
			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"]);
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)
			{
				err->setError("missing IF block ");
				return nullptr;
			}
			auto control_if = std::make_shared<CBlockControlIF >(ACondition, executeBlock ,nullptr);
			return control_if;
		}
	}
	return nullptr;
}
HBlock  NSParser::ControlFlux::parser_control_unless(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	{
		  CPredSequence predList   = pLiteral("unless")	<<pAny("Condition")	<<pLiteral(":");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"]);
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)
			{
				err->setError("missing Unless block ");
				return nullptr;
			}
			auto control_if = std::make_shared<CBlockControlUnless >(ACondition, executeBlock, nullptr);
			return control_if;
		}
	}
	return nullptr;
}
std::list<HBlockControlSelectItem> NSParser::ControlFlux::get_CBlockControlSelectItem(CParser *p, HBlockComandList cmdList, ErrorInfo* err)
{
	std::list<HBlockControlSelectItem> ret;
	for(auto e: cmdList->lista)
	{
		if (auto eitem = DynamicCasting::asHBlockControlSelectItem(e))
		{			
			ret.push_back(eitem);
		}
		else
		{
			err->setError("Parser Error on If Selector ");
			return std::list<HBlockControlSelectItem>();
		}
	}
	return ret;
}

HBlockControlSelect  NSParser::ControlFlux::parser_control_select(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	 


	{
		  CPredSequence predList = pLiteral("if")	<<pAny("object")<<pLiteral("is")<<pLiteral(":");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = Expression::parser_expression(p,res.matchs["object"] );

			HBlockComandList executeBlockRaw = Statement::parser_stmt_inner(p,inner, err);

			if (executeBlockRaw == nullptr)
			{
				err->setError("missing if block  ");
				return nullptr;
			}
			// Convert execute block to Select Item

			auto  executeBlock = get_CBlockControlSelectItem(p,  executeBlockRaw, err);
			if (err->hasError)
			{
				return nullptr;
			}

			auto control_select = std::make_shared<CBlockControlSelect >(ACondition, executeBlock, nullptr);
			return control_select;
		}
	}

	 
	return nullptr;

}



HBlockControlSelectItem  NSParser::ControlFlux::parser_control_select_item(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	{
		  CPredSequence predList = pLiteral("--")	<<pAny("object")<<pLiteral(":")	<<pAny("body");
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			
			HBlock ABody = Statement::parser_stmt ( p,  res.matchs["body"] , inner , err);
			if (ABody == nullptr || inner != nullptr)
			{
				logMessage( res.matchs["body"]->repr());				 
				err->setError("error on Select Item ");
				return nullptr;
			}
			HBlock ASeletor = Expression::parser_expression(p,res.matchs["object"]);
			return  std::make_shared<CBlockControlSelectItem  >(ASeletor, ABody );			
		}
	}

	{
		CPredSequence predList = pLiteral("--")	<<pAny("object") <<pLiteral(":");
			 
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ASeletor = Expression::parser_expression(p,res.matchs["object"]);
			
			HBlockComandList ABody = Statement::parser_stmt_inner(p,inner, err);
			 
			if (ABody == nullptr)
			{
				err->setError("error on Select Item ");
				return nullptr;
			}
			return  std::make_shared<CBlockControlSelectItem  >(ASeletor, ABody);
		}
	}


	return nullptr;

}



HBlock  NSParser::ControlFlux::STMT_control_flux(CParser *p, std::vector<HTerm>& term ,   HGroupLines inner, ErrorInfo *err)
{

//identifica os IF, then ,else, while ,case , select da vida

	HBlock rblock_flagreturn = (stmt_resultflag(p,term ));
	if (err->hasError) return nullptr;
	if (rblock_flagreturn != nullptr) return rblock_flagreturn;


	HBlock rblock_select = (parser_control_select(p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select != nullptr) return rblock_select;


	HBlock rblock_select_item = (parser_control_select_item (p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select_item != nullptr) return rblock_select_item;


	HBlock rblock_if = (parser_control_if(p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_if != nullptr) return rblock_if;
	

	 
	 
	HBlock rblock_else = (parser_control_else(p,term,  inner, err));
	if (rblock_else != nullptr) return rblock_else;


	HBlock rblock_for_loop = (parser_control_for_loop(p, term, inner, err));
	if (rblock_for_loop != nullptr) return rblock_for_loop;
	 

	//HBlock rblock_end = (parser_control_end(term, inner, err));
    //if (rblock_end != nullptr) return rblock_end;



    return nullptr;
}


 
HBlock  NSParser::ControlFlux::STMT_pass(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	CPredSequence predList = pLiteral("pass");
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		return   std::make_shared<CBlockNothing>("nothing");
	}
	return nullptr;
}

HBlock  NSParser::ControlFlux::STMT_unit_test(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	//unity init ?
	{
		CPredSequence predList = pLiteral("unit") << pLiteral("init") << pLiteral(":");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			if (inner != nullptr)
			{
				HBlock executeBlock = nullptr;
				executeBlock = Statement::parser_stmt_inner(p, inner, err);
				if (executeBlock == nullptr)
				{
					err->setError("missing unity init block ");
					return nullptr;
				}
				HBlockUnitInit unit_init = std::make_shared<CBlockUnitInit>(executeBlock);
				return unit_init;
			}
		}
	}


	{
		CPredSequence predList = pLiteral("unit") << pLiteral("test") << pLiteral(":");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			if (inner != nullptr)
			{
				HBlock executeBlock = nullptr;
				executeBlock = Statement::parser_stmt_inner(p, inner, err);
				if (executeBlock == nullptr)
				{
					err->setError("missing unity test block ");
					return nullptr;
				}
				
				HBlockUnitTest unit_init = std::make_shared<CBlockUnitTest>(executeBlock);
				return unit_init;
			}
		}
	}



	{
		CPredSequence predList = pLiteral("assert") <<   pLiteral(":") << pAny("result");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			if (inner == nullptr)
			{
				 

				HBlock executeBlock =  Expression::parser_expression(p, res.matchs["result"]  );
				if (executeBlock == nullptr)
				{
					err->setError("missing unity expect value ");
					return nullptr;
				}

				HBlockUnitAssert unit_init = std::make_shared<CBlockUnitAssert>(executeBlock);
				return unit_init;
			}
			else
			{
				err->setError("idention error");
			}
		}
	}



	return nullptr;
}


std::list<HBlock >   NSParser::ControlFlux::post_process_tokens(CParser *p,  std::list<HBlock>  lst, ErrorInfo* err)
{
	 
	// junta comandos que vem de varias linhas em um unico

	bool is_first = true;
	for(auto it = lst.begin() ; it != lst.end();++it)
	{		
		is_first = (it == lst.begin());
		{
			if (HBlockControlToken tk = DynamicCasting::asHBlockControlToken(*it))
			{
				// Entao o anterior deve ser um Comando que aceita tokens

				if (tk->token == "else")
				{  
					if (is_first )
					{
						err->setError("else without if  ");
						return std::list< HBlock  >();
					}
					auto iprev = std::prev(it);
					if (HBlockControlIF controlIF = DynamicCasting::asHBlockControlIF(*iprev))
					{
						controlIF->block_else = tk->contents;
						 lst.erase(it);
						it = lst.begin(); // reinicia 
					}
					else if (HBlockControlSelect controlSelect = DynamicCasting::asHBlockControlSelect(*iprev))
					{
						controlSelect->block_else = tk->contents;
						 lst.erase(it);
						it = lst.begin(); // reinicia 
					}
					else
					{
						err->setError("else without if  ");
					}
				}
			}
		}
	}


	return  lst;
}
