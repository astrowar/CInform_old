#include "Parser.hpp"
#include "CBlockControlFlux.hpp"
#include "sharedCast.hpp"

using namespace CBlocking;


struct Token
{
	string named;
	Token(string _named) :named(_named) {}
};

struct AnySequence
{
	string named;
	AnySequence(string _named) :named(_named) {}
	 
};

bool isToken(Token tk1 , std::vector<HBlock>::iterator  b)
{
	if (HBlockControlToken token = DynamicCasting::aHBlockControlToken( *b ))
	{
		if (token->token == tk1.named )
		{
			return true;
		}
	}
	return false;
}



HBlock setCombinatoriaToken_2( std::vector<HBlock>  lst , std::function<HBlock(std::vector<HBlock> , std::vector<HBlock> )> func_2)
{
	unsigned int  n = lst.size();
	if (n < 2) return nullptr;
	for(unsigned int  i = 1; i< n ;++i )
	{
		std::vector<HBlock> a = std::vector<HBlock>(lst.begin(), lst.begin() + i);
		std::vector<HBlock> b = std::vector<HBlock>(lst.begin()+i, lst.end() );
		auto ret = func_2(a, b);
		if (ret != nullptr)
		{
			return ret;
		}
	}
	return nullptr;
}

HBlock setCombinatoriaToken_1S1(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend, Token tk1, AnySequence tk2, Token tk3, std::function<HBlock(Token, std::vector<HBlock>, Token)> func_1S1)
{
	auto n = (vend - vbegin);
	if (n < 3) return nullptr;

	if (isToken(tk1, vbegin + 0))
		if (isToken(tk3, vbegin + (n - 1)))
		{

			std::vector<HBlock> s2 = std::vector<HBlock>(vbegin + 1, vbegin + (n - 1));
			return func_1S1(tk1, s2, tk3);
		}

	return nullptr;
}


HBlock setCombinatoriaToken_1S1S(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend,  Token tk1, AnySequence S2, Token tk3, AnySequence S3, std::function<HBlock(Token, std::vector<HBlock>, Token , std::vector<HBlock>)> func_1S1S)
{
	auto n = (vend - vbegin);
	if (n < 4) return nullptr;

	if (isToken(tk1, vbegin + 0))
	{
		for (int i = 1; i< n - 1; ++i) // onde esta o segundo token ?
		{
			if (isToken(tk3, vbegin + i ))
			{
				// ok ..achamos o segund token	
				std::vector<HBlock> s2 = std::vector<HBlock>(vbegin + 1, vbegin + i);
				std::vector<HBlock> s4 = std::vector<HBlock>(vbegin + (i + 1), vend );
				auto h = func_1S1S(tk1, s2, tk3, s4);
				if (h != nullptr) return h;
			}
		}
	}
	return nullptr;
}

// if then end
HBlock setCombinatoriaToken_1S1S1(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend, Token tk1, AnySequence S2, Token tk3, AnySequence S3, Token tk5, std::function<HBlock(Token, std::vector<HBlock>, Token, std::vector<HBlock> , Token)> func_1S1S1)
{
	auto n = (vend - vbegin);
	if (n < 3) return nullptr;

	if (isToken(tk1, vbegin + 0 ))
		if (isToken(tk5, vbegin + (n -1 ) )) // confirma a delimitacao
	{
		for (int i = 1; i< n - 1; ++i) // onde esta o segundo token ?
		{
			if (isToken(tk3, vbegin + i))
			{
				// ok ..achamos o segund token	
				std::vector<HBlock> s2 = std::vector<HBlock>(vbegin +   1, vbegin + i);
				std::vector<HBlock> s4 = std::vector<HBlock>(vbegin +   (i + 1), vbegin + (n - 1));
				auto h = func_1S1S1(tk1, s2, tk3, s4 , tk5);
				if (h != nullptr) return h;
			}
		}
	}
	return nullptr;
}

// if then end remanden
HBlock setCombinatoriaToken_1S1S1S(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend, Token tk1, AnySequence S2, Token tk3, AnySequence S3, Token tk5, AnySequence S6, std::function<HBlock(Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token, std::vector<HBlock>)> func_1S1S1S)
{
	auto n = (vend - vbegin);
	if (n < 3) return nullptr;

	if (isToken(tk1, vbegin + 0))
	{
		for (int i = 1; i < n - 2; ++i) // onde esta o segundo token ?
		{
			if (isToken(tk3, vbegin + i))
			{
				for (int j = i + 1; j < n - 1; ++j) // onde esta o terceiro token ?
				{
					if (isToken(tk5, vbegin + j))
					{
						// ok ..achamos o segund token	
						std::vector<HBlock> s2 = std::vector<HBlock>(vbegin + 1, vbegin + i);
						std::vector<HBlock> s4 = std::vector<HBlock>(vbegin + (i + 1), vbegin + j );
						std::vector<HBlock> s6 = std::vector<HBlock>(vbegin + (j + 1), vbegin + (n - 1));
						auto h = func_1S1S1S(tk1, s2, tk3, s4, tk5, s6);
						if (h != nullptr) return h;
					}
				}
			}
		}
	}
	return nullptr;
}


// if then else end

HBlock setCombinatoriaToken_1S1S1S1(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend, Token tk1, AnySequence S2, Token tk3, AnySequence S3, Token tk5, AnySequence S6 , Token tk7, std::function<HBlock(Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token,std::vector<HBlock>, Token )> func_1S1S1S1)
{
	auto n = (vend - vbegin);
	if (n < 4) return nullptr;

	if (isToken(tk1, vbegin + 0)) // confirma o primeiro token
		if (isToken(tk7, vbegin + (n - 1))) // confirma a delimitacao do ultimo token
		{
			for (int i = 1; i< n - 2; ++i) // onde esta o segundo token ?
			{
				if (isToken(tk3, vbegin + i)) 
				{
					for (int j = i + 1; j < n - 1; ++j) // onde esta o terceiro token ?
					{
						if (isToken(tk5, vbegin + j))
						{
							std::vector<HBlock> s2 = std::vector<HBlock>(vbegin + 1, vbegin + i);
							std::vector<HBlock> s4 = std::vector<HBlock>(vbegin + (i + 1), vbegin + j);
							std::vector<HBlock> s6 = std::vector<HBlock>(vbegin + (j + 1), vbegin + (n - 1));

							auto h = func_1S1S1S1(tk1, s2, tk3, s4, tk5, s6, tk7);
							if (h != nullptr) return h;
						}
					}
				}
			}
		}
	return nullptr;
}
 
// if then else end remaiden
HBlock setCombinatoriaToken_1S1S1S1S(std::vector<HBlock>::iterator  vbegin, std::vector<HBlock>::iterator  vend, Token tk1, AnySequence S2, Token tk3, AnySequence S3, Token tk5, AnySequence S6, Token tk7, AnySequence S8, std::function<HBlock(Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token, std::vector<HBlock>)> func_1S1S1S1S)
{
	auto n = (vend - vbegin);
	if (n < 4) return nullptr;

	if (isToken(tk1, vbegin + 0)) // confirma o primeiro token		 
	{
		for (int i = 1; i < n - 3; ++i) // onde esta o segundo token ?
		{
			if (isToken(tk3, vbegin + i))
			{
				for (int j = i + 1; j < n - 2; ++j) // onde esta o terceiro token ?
				{
					if (isToken(tk5, vbegin + j))
					{

						for (int k = j + 1; k < n - 1; ++k) // onde esta o quarto token ?
						{
							if (isToken(tk7, vbegin + k))
							{
								std::vector<HBlock> s2 = std::vector<HBlock>(vbegin + 1, vbegin + i);
								std::vector<HBlock> s4 = std::vector<HBlock>(vbegin + (i + 1), vbegin + j);
								std::vector<HBlock> s6 = std::vector<HBlock>(vbegin + (j + 1), vbegin + k);
								std::vector<HBlock> s8 = std::vector<HBlock>(vbegin + (k + 1), vbegin + (n - 1));

								auto h = func_1S1S1S1S(tk1, s2, tk3, s4, tk5, s6, tk7, s8);
								if (h != nullptr) return h;
							}
						}
					}
				}
			}
		}
	}
	return nullptr;
}


std::list<HBlock> scan_token_any(std::vector<HBlock>::iterator  vbegin , std::vector<HBlock>::iterator  vend )
{
	std::list<HBlock> retList;
	auto pos = vbegin;
	while( pos != vend)
	{
		if ( HBlockControlToken token = DynamicCasting::aHBlockControlToken( *pos )  )
		{
		  if (token->token == "if" )
		  {
			  //ok ,estamos iniciando um token
			  std::function<HBlock(Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token, std::vector<HBlock>, Token, std::vector<HBlock>)> func_1S1S1S1S;
			  HBlock ret = setCombinatoriaToken_1S1S1S1S(pos, vend, Token("if"), AnySequence("condition" ), Token("then"), AnySequence("seq_then"), Token("else"), AnySequence("seq_end"), Token("end"), AnySequence("seq_remainden"), func_1S1S1S1S);
			  if (ret != nullptr)
			  {
				  retList.insert(retList.end(), ret );
			  }
		  }
		}
	}
	return  retList;
}




std::list<HBlock> goupe_non_tokens(std::list<HBlock> lst)
{
	HBlockList current_block = std::make_shared<CBlockList>(std::list<HBlock>());
	std::list<HBlock> retList;
	for( auto &v : lst )
	{
		if (v->type() == BlockControlToken ) {
			if (!current_block->lista.empty()) //so add se tiver algo
			{
				retList.push_back(current_block);
				current_block = std::make_shared<CBlockList>(std::list<HBlock>());
			}
			retList.push_back(v);
		}
			else
		{
			current_block->lista.push_back(v);
		}

	}
	//add os que restaram
	if (!current_block->lista.empty())
	{
		retList.push_back(current_block);		 
	}
	return retList; //ret list agora tem dois tipos de blocos, Tokens e Listas

}

 

//vai percorrend os next ate achar alguem
std::list<NSParser::HGroupLines>::iterator  find_next_level( int ident ,std::list<NSParser::HGroupLines>::iterator  gbegin, std::list<NSParser::HGroupLines>::iterator  gend)
{
	for (auto it = gbegin; it != gend; ++it)
	{
		if ((*it)->identarion == ident) return it;
	}
	return gend;
}
NSParser::HGroupLines make_hierarchical_tree_it(std::list<NSParser::HGroupLines>::iterator  gbegin, std::list<NSParser::HGroupLines>::iterator  gend )
{
	NSParser::HGroupLines pivot = *gbegin;
	pivot->next = nullptr;	
	pivot->inner = nullptr;
		
	for (auto it = gbegin; it != gend; ++it)
	{
		if (*it != pivot)
		{
			if ((*it)->identarion > pivot->identarion)
			{
				auto pnext =  find_next_level(pivot->identarion, it, gend);
				pivot->inner = make_hierarchical_tree_it(it, gend);
				if (pnext == gend)
				{
					pivot->next = nullptr;
					return pivot;
				}
				else
				{
					pivot->next = *pnext;
					pivot = pivot->next;
				}
			}
			else if ((*it)->identarion > pivot->identarion)
			{
				
			}

		}

	}
	return pivot;
	
}
std::list<NSParser::HGroupLines> make_hierarchical_tree(  std::list<NSParser::HGroupLines>  buffer, NSParser::ErrorInfo *err)
{
	 
	  
	for (auto it = buffer.begin(); it != buffer.end(); ++it)
	{
		int identLevel = (*it)->identarion;
		auto inext = std::next(it);
		if (inext != buffer.end())		
		{
			(*it)->inner = nullptr;
			(*it)->next = nullptr;
			//o proximo esta no nivel abaixo ?
			int lvMin = identLevel; //para validar regiao invalida
			if ((*inext)->identarion > identLevel)
			{
				(*it)->inner = *inext; 
				lvMin = (*inext)->identarion;
			}
		


			//acha o proximo do mesmo nivel
			for (auto jt = inext; jt != buffer.end(); ++jt)
			{
				int lv = (*jt)->identarion;
				if ( lv > identLevel && lv < lvMin)
				{
					auto lineGroup = (*jt);
					err->setError("Identation Error at " + std::to_string(lineGroup->lines.front().linenumber));
					logMessage("Identation Error at " + std::to_string( lineGroup->lines.front().linenumber ));
					
					return std::list<NSParser::HGroupLines>();
				}
				if (lv == identLevel)
				{
					(*it)->next = *jt;
					break;
				}
				else if (lv < identLevel)
				{				
					break; //nao tem .... nivel igual.. apenas maior
				}
			}
			
		}


	}
	return buffer;
	 
		

	 
}

void logGroupLines(NSParser::HGroupLines   pivot , string offset )
{
	printf("{\n");
	while (pivot != nullptr)
	{
		for (auto &s : (pivot)->lines)
		{
			logMessage(  s.line );
		}
		if (pivot->inner != nullptr)
		{
			
			logGroupLines(pivot->inner, offset + "   ");
			
		}
		pivot = pivot->next;
		
	}
	printf("}\n");
}


NSParser::HGroupLines  NSParser::ParseText::get_identation_groups(CParser *p, string filename,  std::vector<string> vlines, ErrorInfo *err)
{
	std::list<HGroupLines> buffer;
	
	int lineNumber = 0;
	for(auto &v : vlines)
	{
		lineNumber++;
		if (v.find_first_not_of(' ') != std::string::npos)
		{
			 
			int ns = v.size();
			int i = 0;
			for (i = 0; i < ns; ++i)
			{
				if (v[i] != ' ') break;
			}


			HGroupLines g = std::make_shared<GroupLines>();
			g->identarion = i;
			g->lines.push_back(SourceLine( filename, lineNumber, v));
			g->inner = nullptr;
			g->next = nullptr;
			buffer.push_back(g);
		}

	}
	buffer = make_hierarchical_tree(buffer,err);
	if (buffer.empty()) return nullptr;
	/*printf("------------------------------------------------\n");
	logGroupLines(buffer.front(), "");
	printf("------------------------------------------------\n");*/

	/*printf("\n");
	for (auto it = buffer.begin(); it != buffer.end(); ++it)
	{
		printf("%i \n", (*it)->identarion);
		for (auto &s : (*it)->lines)
		{
			logMessage(s.line);
		}
	}*/
	//return std::vector<HGroupLines>(buffer.begin(), buffer.end());
	return buffer.front();

}