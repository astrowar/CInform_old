#include <memory>
#include "Parser.hpp"
#include "CBlockDecideIf.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;


HBlock NSParser::ParseAssertion::STMT_Declare_Phrase(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if (inner == nullptr)
	{
		{
			CPredSequence predList = pLiteral("to") << pWord("InitialWord") << pAny("Match") << pLiteral(":") << pAny("RemainBody");

			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{



			}
		}
	}
	

	if (inner != nullptr)
	{
		//Com bloco inner 
		{

			CPredSequence predList = pLiteral("to") << pWord("InitialWord") << pAny("Match") << pLiteral(":");

			MatchResult res = CMatch(term, predList);
			if (res.result == EqualResulting::Equals)
			{




			}
		}
	}




		return nullptr;


	}