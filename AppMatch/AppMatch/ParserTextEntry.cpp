// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

 
#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;




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
				auto segment = Expression::Parser_Expression(p, s ,false );
				//blocos->contents.push_back(std::make_shared< CBlockText >(s));
				if (segment != nullptr)
				{
					blocos->contents.push_back(segment);
				}
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