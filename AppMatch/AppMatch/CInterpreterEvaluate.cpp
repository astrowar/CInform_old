
#include "BlockInterpreter.hpp"
#include "sharedCast.hpp"
#include "CBlockInterpreterRuntime.hpp"

HBlock  CBlockInterpreter::evaluate_relation_property(HBlock c_block, HBlockNoum property_noum, HRunLocalScope localsEntry, QueryStack stk, std::function< HBlock(HBlock, HRunLocalScope, QueryStack) > isSuitable)
{
	// procupara pela relacao que tem um called que eh compativel com o property_noum
	for (auto &rr : relInstances)
	{
		if (rr->relation->input_B->named == property_noum->named) //Ok, this is 
		{
			if (QEquals == query_is(c_block, rr->value1, localsEntry, stk))
			{
				return isSuitable(rr->value2, localsEntry, stk);
			}
		}
		if (rr->relation->input_A->named == property_noum->named) //Ok, this is 
		{
			if (QEquals == query_is(c_block, rr->value2, localsEntry, stk))
			{
				return isSuitable(rr->value1, localsEntry, stk);
			}
		}

	}
	return nullptr;
}

HBlock  CBlockInterpreter::evaluate_propertyValue(  HBlockProperty cproperty, HRunLocalScope localsEntry, QueryStack stk, std::function< HBlock(HBlock, HRunLocalScope, QueryStack) > isSuitable)
{
 
	{
		if (HBlockNoum property_noum = asHBlockNoum(cproperty->prop))
		{
			
			if (HBlockNoum object_named = asHBlockNoum(cproperty->obj))
			{
				HBlock object =  resolve_noum(object_named, localsEntry);

				if (object != nullptr)
				{
					if (HBlockInstance cinst = asHBlockInstance(object))
					{
						HVariableNamed pvar = cinst->get_property(property_noum->named);
						if (pvar != nullptr)
						{
							return evaluate_values(pvar->value, localsEntry, stk, isSuitable);
						}
					}
					return evaluate_relation_property(object, property_noum, localsEntry, stk, isSuitable);
				}			
				
				// pode ser o nome de uma relacao. 
				// return evaluate_relation_property(object, property_noum, localsEntry, stk, isSuitable);
				
			}
		}
		 
	}
	
	return nullptr;
}

// std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
//Funcao que calcula todos os values possiveis do primeiro termo e chama a funcao proxima
HBlock  CBlockInterpreter::evaluate_values(HBlock c_block, HRunLocalScope localsEntry, QueryStack stk , std::function< HBlock(HBlock, HRunLocalScope , QueryStack) > isSuitable  )
{
	if (c_block == nullptr) return nullptr;
	if (stk.isQuery("__evaluate", c_block, nullptr)) return nullptr;
	stk.addQuery("__evaluate", c_block, nullptr);
 
	// vai chamando a funcao ate que retorne um valor nao NULL

	if (HBlockNoum nnoum = asHBlockNoum(c_block))
	{
		HBlock resolved = resolve_noum(nnoum, localsEntry);
		if (resolved)
		{
			auto r = isSuitable(resolved, localsEntry, stk );
			if (r != nullptr) return r;
		}
	}
	if (HBlockInstance cinst1 = asHBlockInstance(c_block))
	{
		auto r = isSuitable(cinst1, localsEntry, stk );
		if (r != nullptr) return r;
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
			auto r = evaluate_values(dctValueWrap,  localsEntry, stk,isSuitable);
			if (r != nullptr) return r;
		}
	}


 
		if (HBlockKind akind = asHBlockKind(c_block)) 
		{
			auto r = isSuitable(akind, localsEntry, stk);
			if (r != nullptr) return r;
		}


		if (HVariableNamed nvar1 = asHVariableNamed(c_block))
		{
			if (nvar1->value != nullptr)
			{
				auto r = evaluate_values(nvar1->value, localsEntry, stk, isSuitable);
				if (r != nullptr) return r;
			}
		}
		if (HBlockProperty cproperty = asHBlockProperty(c_block))
		{
			auto r = evaluate_propertyValue(cproperty, localsEntry, stk, isSuitable);
			if (r != nullptr) return r;

		}
		 
		/*for (auto it = assertions.begin(); it != assertions.end(); ++it) 
		{
			if (HBlockAssertion_is qdef = asHBlockAssertion_is(*it)) {
				auto r = evaluate_values(qdef->get_obj(), localsEntry, stk, isSuitable);
				if (r != nullptr) return r;				
			}
		}*/

	return nullptr;

}

HBlock  CBlockInterpreter::evaluate_values(HBlock c_block )
{

	std::function< HBlock(HBlock, HRunLocalScope, QueryStack) > isSuitable = [](HBlock a , HRunLocalScope h, QueryStack stk ) {  return a ; };
	return evaluate_values(c_block, nullptr, QueryStack(), isSuitable);
}