

#include "CBlockAction.hpp"
using namespace std;
using namespace CBlocking;


CBlockActionNamed::CBlockActionNamed(std::string _named, HBlockKindAction _actionKind) : named(_named),
actionKind(_actionKind)
{
	if (_actionKind == nullptr)
	{
		printf("??");
	}
}


CBlockActionNamed::CBlockActionNamed(std::string _named) : named(_named)
{
	actionKind = nullptr;
}