//
// Created by Eraldo Rangel on 12/10/16.
//
#include "Parser.hpp"
#include "CBlockControlFlux.hpp"
#include "sharedCast.hpp"
 
HBlock   CParser::parser_if_condition(HTerm term  )
{
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("or"));
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_if_condition(res.matchs["AValue"]  );
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_if_condition(res.matchs["BValue"] );
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockBooleanOR>(AValue, BValue);
        }
    }
	 

	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(mk_HPredLiteral("not"));
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

			HBlock AValue = parser_expression(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = parser_expression_match(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);

		}
	}
	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

			HBlock AValue = parser_expression(res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = parser_expression_match(res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
		}
	}

  

   
 {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = parser_expression_match(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
       
        }
    }
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));

            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = parser_expression_match(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }


    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_expression_match(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            auto vbool =  std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
        }
    }



	   {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_expression(res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_expression_match(res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }

	 
    return parser_expression ( term); //default ...

    return nullptr;

}

HBlock   CParser::parser_control_else(std::vector<HTerm>& term,   HGroupLines inner, ErrorInfo *err) {
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral_OR("else", { "else" , "otherwise" }));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			

			HBlock ABody = parser_stmt(res.matchs["body"], inner, err);
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
        static std::vector<HPred> predList = {};
        if (predList.empty()) {
			predList.push_back(mk_HPredLiteral_OR("else", { "else" , "otherwise" }));
			predList.push_back(mk_HPredLiteral(":"));
 
        }
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
           
			 
			HBlock executeBlock = parser_stmt_inner(inner, err);
			if (executeBlock == nullptr)  return nullptr;
			auto token_else = std::make_shared<CBlockControlToken >("else",executeBlock);
			return token_else;

           // return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
        }
    }
	 

    return nullptr;
}


HBlock   CParser::parser_control_end(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	//{
	//	static std::vector<HPred> predList = {};
	//	if (predList.empty()) {
	//		predList.push_back(mk_HPredLiteral("end"));

	//	}
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals) {

	//		auto token_else = std::make_shared<CBlockControlToken >("end");
	//		return std::make_shared<CBlockList  >(std::list<HBlock>({ token_else }));
	//	}
	//}
	return nullptr;
}


HBlock  CParser::parser_control_if(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err) 
{
	if(inner == nullptr)
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{


			HBlock ACondition = parser_if_condition(res.matchs["Condition"] );

			HBlock ABody = parser_stmt(res.matchs["body"], nullptr, err); // aqui tem erro
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
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
        {
			HBlock ACondition = parser_if_condition(res.matchs["Condition"]);
			HBlock executeBlock = parser_stmt_inner(inner, err);
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
HBlock  CParser::parser_control_unless(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("unless"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = parser_if_condition(res.matchs["Condition"]);
			HBlock executeBlock = parser_stmt_inner(inner, err);
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
std::list<HBlockControlSelectItem> CParser::get_CBlockControlSelectItem(HBlockComandList cmdList, ErrorInfo* err)
{
	std::list<HBlockControlSelectItem> ret;
	for(auto e: cmdList->lista)
	{
		if (auto eitem = aHBlockControlSelectItem(e))
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

HBlockControlSelect  CParser::parser_control_select(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	 


	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("object"));
			predList.push_back(mk_HPredLiteral("is"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = parser_expression(res.matchs["object"] );

			HBlockComandList executeBlockRaw = parser_stmt_inner(inner, err);

			if (executeBlockRaw == nullptr)
			{
				err->setError("missing if block  ");
				return nullptr;
			}
			// Convert execute block to Select Item

			auto  executeBlock = get_CBlockControlSelectItem(  executeBlockRaw, err);
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



HBlockControlSelectItem  CParser::parser_control_select_item(std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("--"));
			predList.push_back(mkHPredAny("object"));			
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			
			HBlock ABody = parser_stmt (  res.matchs["body"] , inner , err);
			if (ABody == nullptr || inner != nullptr)
			{
				logMessage( res.matchs["body"]->repr());				 
				err->setError("error on Select Item ");
				return nullptr;
			}
			HBlock ASeletor = parser_expression(res.matchs["object"]);
			return  std::make_shared<CBlockControlSelectItem  >(ASeletor, ABody );			
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("--"));
			predList.push_back(mkHPredAny("object"));
			predList.push_back(mk_HPredLiteral(":"));
			 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ASeletor = parser_expression(res.matchs["object"]);
			
			HBlockComandList ABody = parser_stmt_inner(inner, err);
			if (ABody == nullptr)
			{
				err->setError("missing if block  ");
				return nullptr;
			}
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



HBlock  CParser::STMT_control_flux(std::vector<HTerm>& term ,   HGroupLines inner, ErrorInfo *err)
{

//identifica os IF, then ,else, while ,case , select da vida

	 


	HBlock rblock_select = (parser_control_select(term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select != nullptr) return rblock_select;


	HBlock rblock_select_item = (parser_control_select_item (term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select_item != nullptr) return rblock_select_item;


	HBlock rblock_if = (parser_control_if(term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_if != nullptr) return rblock_if;
	

	 
	 
		HBlock rblock_else = (parser_control_else(term,  inner, err));
		if (rblock_else != nullptr) return rblock_else;
	 

	//HBlock rblock_end = (parser_control_end(term, inner, err));
    //if (rblock_end != nullptr) return rblock_end;



    return nullptr;
}

std::list<HBlock >   CParser::post_process_tokens(std::list< HBlock  >  lst, ErrorInfo* err)
{
	 
	// junta comandos que vem de varias linhas em um unico

	bool is_first = true;
	for(auto it = lst.begin() ; it != lst.end();++it)
	{		
		is_first = (it == lst.begin());
		{
			if (HBlockControlToken tk = aHBlockControlToken(*it))
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
					if (HBlockControlIF controlIF = aHBlockControlIF(*iprev))
					{
						controlIF->block_else = tk->contents;
						it = lst.erase(it);
						it = lst.begin(); // reinicia 
					}
					else if (HBlockControlSelect controlSelect = aHBlockControlSelect(*iprev))
					{
						controlSelect->block_else = tk->contents;
						it = lst.erase(it);
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
