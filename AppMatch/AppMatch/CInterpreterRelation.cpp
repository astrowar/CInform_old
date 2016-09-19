

#include "CBlockInterpreterRuntime.h"





bool CBlockInterpreter::set_relation(HBlockRelationBase relation, HBlock n1, HBlock n2)
{
	
	if (relation->is_various_noum1() == false )
	{
       //remove todas as relacoes da entidade noum1
		for(auto it = relInstances.begin(); it != relInstances.end();++it)
		{
			auto & rel = *it;
			if (rel->relation ==  relation)
			{
				if (rel->value1 == n1)
				{
					relInstances.erase(it);
					if (it == relInstances.end()) break;
				}
			}
		}
	}


	{
		relInstances.push_back(std::make_shared<CBlockRelationInstance>(relation, n1, n2));
		return true;
	}

	return false;
}
