
#include "BlockInterpreter.hpp"
#include "CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"

// std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
//Funcao que calcula todos os values possiveis do primeiro termo e chama a funcao proxima
HBlock  CBlockInterpreter::evaluate_values(HBlock c_block, HRunLocalScope localsEntry, QueryStack stk , std::function< HBlock(HBlock, HRunLocalScope , QueryStack) > isSuitable  )
{
	// vai chamando a funcao ate que retorne um valor nao NULL

	if (HBlockNoum nnoum = asHBlockNoum(c_block))
	{
		HBlock resolved = resolve_noum(nnoum, localsEntry);
		if (resolved)
		{
			return isSuitable(resolved, localsEntry, stk );
		}
	}
	if (HBlockInstance cinst1 = asHBlockInstance(c_block))
	{
		return isSuitable(cinst1, localsEntry, stk );
	}
	 

	if (HBlockList_OR  orList = asHBlockList_OR(c_block))
	{
		for (auto &item : orList->lista)
		{
			auto r = isSuitable(item, localsEntry, stk);
			if (r != nullptr) return r;
		}
	}

	for (auto dct : decides_what) {
		auto dctValueWrap = getDecidedValueOf(c_block, dct, localsEntry, stk);
		if (dctValueWrap != nullptr)
		{
			return  evaluate_values(dctValueWrap,  localsEntry, stk,isSuitable);  
		}
	}


 
		if (HBlockKind akind = asHBlockKind(c_block)) 
		{
			return isSuitable(akind, localsEntry, stk);
		}


		if (HVariableNamed nvar1 = asHVariableNamed(c_block))
		{
			if (nvar1->value != nullptr)
			{
				return  evaluate_values(nvar1->value, localsEntry, stk, isSuitable);
			}
		}
		if (HBlockProperty cproperty = asHBlockProperty(c_block))
		{
			if (HBlockNoum property_noum = asHBlockNoum(cproperty->prop))
			{
				if (HBlockNoum object_named = asHBlockNoum(cproperty->obj))
				{
					auto object = resolve_noum(object_named, localsEntry);

					if (object != nullptr)
					{
						if (HBlockInstance cinst = asHBlockInstance(object))
						{
							HVariableNamed pvar = cinst->get_property(property_noum->named);
							if (pvar != nullptr)
							{
								return evaluate_values(pvar, localsEntry, stk, isSuitable);
							}
						}
					}
					else
					{
						//pode ser uma relacao 
						for (auto &rr : relInstances)
						{
							if (rr->relation->input_B->named == property_noum->named) //Ok, this is 
							{
								QueryResul query_inst = query_relation_instance(rr, c_block, value, localsEntry, stk);
								if (query_inst != QUndefined) return query_inst;
							}

							if (rr->relation->input_A->named == property_noum->named) //Ok, this is 
							{
								QueryResul query_inst = query_relation_instance(rr, value, c_block, localsEntry, stk);//reverse the property
								if (query_inst != QUndefined) return query_inst;
							}

						}

					}
				}
			}

		}
		 
		for (auto it = assertions.begin(); it != assertions.end(); ++it) 
		{
			if (HBlockAssertion_is qdef = asHBlockAssertion_is(*it)) {
				auto r = evaluate_values(qdef->get_obj(), localsEntry, stk, isSuitable);
				if (r != nullptr) return r;				
			}
		}

	return nullptr;

}