// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

 
#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



bool _startWith(std::string str, std::string prefix)
{
	if (str.size() < prefix.size()) return false;
	while (str.size()>1 && str[0] == ' ') str = str.substr(1, str.size() - 1); //remove start spaces 
	if (str.substr(0, prefix.size()) == prefix) return true;


	return false;
}




std::list<HBlock> NSParser::Statement::Text_Sentence_bakret(CParser * p, std::string str)
{
	std::list<HBlock> ret;

	str = decompose_bracket(str, "(");
	str = decompose_bracket(str, ")");
	str = decompose_bracket(str, ",");
	str = decompose_bracket(str, "\"");
	str = decompose_bracket(str, ";");

	std::vector<HTerm> lst = decompose(str);
	auto term = convertToTerm(lst);


	{
		CPredSequence predList = pOr("Article", pLiteral("A"), pLiteral("An"), pLiteral("a"), pLiteral("an") , pLiteral("the"), pLiteral("The")  ) << pAny("Remainder");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			string  sArticle = CtoString(res.matchs["Article"]) +" ";
			return{ std::make_shared<CBlockText >(sArticle) , Expression::parser_expression(p, res.matchs["Remainder"]) };
		}
	}
	 

	auto segment = Expression::parser_expression(p, term);
	if (segment != nullptr)	ret.push_back(segment);
	return ret;
}

HBlock NSParser::Statement::Text_Sentence(CParser * p,  std::string text )
{
	// quebra o texto em parts divididas em [...]

	bool is_inner = false;
	string s = "";
	HBlockTextSentence blocos =   std::make_shared<CBlockTextSentence >( std::list<HBlock>() );  
	for (int i = 0; i < text.size(); ++i)
	{
		if (text[i] == '[')
		{
			if (is_inner) { 
				logError("mismatch brackes"); 
			return nullptr;
			}
			if (s.empty() == false)
			{
				blocos->contents.push_back(std::make_shared<CBlockText >( s ));
				s = "";
			}
			is_inner = true;
			continue;
		}
		if (text[i] == ']')
		{
			if (is_inner == false)
			{
				logError("mismatch brackes"); 
				return nullptr;
			}
			//is inner !
			if (s.empty() == false)
			{
				auto segments = Text_Sentence_bakret( p, s   );				
				for(auto si : segments)  blocos->contents.push_back(si);
				
				s = "";
			}
			is_inner = false;
			continue;
		}

		s = s + text[i];

	}

	if (is_inner)
	{
		logError("mismatch brackes"); 
		return nullptr;
	}
	if (s.empty() == false)blocos->contents.push_back(std::make_shared<CBlockText >(s));


	return blocos;
}



HBlock NSParser::Statement::text_entry(CParser * p, std::vector<HTerm>&  term)
{
	{		 
	    CPredSequence predList = pLiteral("text")<<pAny("Contents");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			string  ss = CtoString(res.matchs["Contents"]);
			return  std::make_shared<CBlockText >( ss );
			
		}
	}
	

	return nullptr;
}


 

HBlock NSParser::Statement::text_literal(CParser * p, std::vector<HTerm>&  term)
{
	{
		CPredSequence predList = pLiteral("\"") << pAny("Contents") << pLiteral("\"");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			string  ss = CtoString(res.matchs["Contents"]);
			return  Text_Sentence(p,ss);
		}
		 
	}


	return nullptr;
}