// PVS
// PVQ
 
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "interpreter/QueryStack.hpp"
#include "CResultMatch.hpp"

#include <algorithm>

#include "sharedCast.hpp"
#include <cstring>
using namespace std;

using namespace CBlocking; 
using namespace Interpreter;
using namespace QueryStacking;


//retorn  o primeiro termo
CBlocking::HBlock  CBlockInterpreter::lookup_relation_X_Y_1(const string & relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value,  HRunLocalScope localsEntry, QueryStack *stk_in)
{
 
	if (HBlockMatch mvalue = DynamicCasting::asHBlockMatch(value))
	{
		auto rst = Resolve_Selector(mvalue, localsEntry);
		value = rst;
	}
	
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{	 

			{
				QueryStack *stk = nullptr;
				QueryResultContext r1 = query_is(rr->value1, c_block, localsEntry, stk);
				if (r1.result != QEquals) continue;

 

				QueryResultContext r2 = query_is(rr->value2, value, localsEntry, stk);
				if (r2.result != QEquals) continue;
				return rr->value1;
			}

		}
	}
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			if (rr->relation->is_symetric()) 
			{
				{
					QueryStack *stk = nullptr;
					QueryResultContext r1 = query_is(rr->value2, c_block, localsEntry, stk);
					if (r1.result != QEquals) continue;

					QueryResultContext r2 = query_is(rr->value1, value, localsEntry, stk);
					if (r2.result != QEquals) continue;
					return rr->value2;
				}
			}
		}
	}

	return nullptr;
}

//retorn  o segundo termo
CBlocking::HBlock  CBlockInterpreter::lookup_relation_X_Y_2(const string &  relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk_in)
{

 

	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			{
				QueryStack *stk = nullptr;
 
				QueryResultContext r1 = query_is(rr->value1, c_block, localsEntry, stk);
				if (r1.result != QEquals) continue;

 

				QueryResultContext r2 = query_is(rr->value2, value, localsEntry, stk);
				if (r2.result != QEquals) continue;
				return rr->value2;
			}
		}
	}
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			if (rr->relation->is_symetric())
			{
				{
					QueryStack *stk = nullptr;
					QueryResultContext r1 = query_is(rr->value2, c_block, localsEntry, stk);
					if (r1.result != QEquals) continue;

					QueryResultContext r2 = query_is(rr->value1, value, localsEntry, stk);
					if (r2.result != QEquals) continue;
					return rr->value1;
				}
			}
		}
	}


	return nullptr;
}


//retorn  o primeiro termo
CBlocking::HBlock  CBlockInterpreter::lookup_relation_XS_Y_1(const string &  relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk_in)
{
	std::list<CBlocking::HBlock> lst;
 


	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			{
				QueryStack *stk = nullptr;
				QueryResultContext r1 = query_is(rr->value1, c_block, localsEntry, stk);
				if (r1.result != QEquals) continue;

				QueryResultContext r2 = query_is(rr->value2, value, localsEntry, stk);
				if (r2.result != QEquals) continue;
				lst.push_back(rr->value1);
			}
		}
	}
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			if (rr->relation->is_symetric())
			{
				{
					QueryStack *stk = nullptr;
					QueryResultContext r1 = query_is(rr->value2, c_block, localsEntry, stk);
					if (r1.result != QEquals) continue;

					QueryResultContext r2 = query_is(rr->value1, value, localsEntry, stk);
					if (r2.result != QEquals) continue;
					lst.push_back(rr->value2);
				}
			}
		}
	}

	return std::make_shared<CBlockList>(lst);
}

//retorn  o segundo termo
CBlocking::HBlock  CBlockInterpreter::lookup_relation_X_YS_2(const string &  relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk_in)
{
	 
	std::list<CBlocking::HBlock> lst;
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)
		{
			{
				QueryStack *stk = nullptr;
				QueryResultContext r1 = query_is(rr->value1, c_block, localsEntry, stk);
				if (r1.result != QEquals) continue;

				QueryResultContext r2 = query_is(rr->value2, value, localsEntry, stk);
				if (r2.result != QEquals) continue;
				lst.push_back(rr->value2);
			}

		}
	}
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == relationNamed)

		{
			if (rr->relation->is_symetric())
			{
				{
					QueryStack *stk = nullptr;
					QueryResultContext r1 = query_is(rr->value2, c_block, localsEntry, stk);
					if (r1.result != QEquals) continue;

					QueryResultContext r2 = query_is(rr->value1, value, localsEntry, stk);
					if (r2.result != QEquals) continue;
					lst.push_back(rr->value1);
				}
			}
		}
	}


	return std::make_shared<CBlockList>(lst);
}

//retorna uma propriedade por relacao

CBlocking::HBlock CBlockInterpreter::get_property_by_relation(HBlockNoum  propNamed, HBlock obj, HRunLocalScope localsEntry, QueryStack *stk)
{

	for (auto &rr : relInstances)
	{		
		if (rr->relation->input_A->named == propNamed->named())
		{
			if (query_is(obj, rr->value2, localsEntry, stk).result == QEquals)
			{
				return rr->value1;
			}
		}
		else if (rr->relation->input_B->named == propNamed->named())
		{
			if (query_is(obj, rr->value1, localsEntry, stk).result == QEquals)
			{
				return rr->value2;
			}
		}
	} 
	return nullptr; 
}

 


 
//Esta funcao pode retornar um elemento Ou uma lista .. depende do tipo de relacao

CBlocking::HBlock CBlockInterpreter::lookup_relation(HBlockRelationLookup  rLookup,   HRunLocalScope localsEntry, QueryStack *stk)
{

	auto arg1 = resolve_argument_match(rLookup->value1,localsEntry,stk);
	auto arg2 = resolve_argument_match(rLookup->value2, localsEntry, stk);

	auto rel_find = this->staticRelation.find(rLookup->relation);
	if (rel_find != this->staticRelation.end())
	{
		auto rel = rel_find->second;
		if (rLookup->term_to_query == FirstNoum)
		{
			if (rel->is_various_noum1()) return lookup_relation_XS_Y_1(rLookup->relation, arg1, arg2, localsEntry,stk);
			return lookup_relation_X_Y_1(rLookup->relation, arg1, arg2, localsEntry,stk);

		}
		if (rLookup->term_to_query == SecondNoum)
		{
			if (rel->is_various_noum2()) return lookup_relation_X_YS_2(rLookup->relation, arg1, arg2, localsEntry,stk);
			return lookup_relation_X_Y_2(rLookup->relation, arg1, arg2, localsEntry,stk);
		} 
	} 
	printf("%s \n", rLookup->relation.c_str()); 
	return nullptr;

}


QueryResultContext CBlockInterpreter::query_lookup_relation(HBlock value, HBlockRelationLookup  rLookup, HRunLocalScope localsEntry, QueryStack *stk)
{
	auto arg1 = resolve_argument_match(rLookup->value1, localsEntry, stk);
	auto arg2 = resolve_argument_match(rLookup->value2, localsEntry, stk);

	auto rel_find = this->staticRelation.find(rLookup->relation);
	if (rel_find != this->staticRelation.end())
	{
		auto rel = rel_find->second;
		if (rLookup->term_to_query == FirstNoum)
		{
			auto r1 = query_relation(rel, value, arg2 , localsEntry,stk);
			if (r1.result == QEquals)
			{
				return r1;
			}
			//if (rel->is_various_noum1()) return query_lookup_relation_XS_Y_1(value , rLookup->relation, arg1, arg2, localsEntry, stk);
			//return query_lookup_relation_X_Y_1(value, rLookup->relation, arg1, arg2, localsEntry, stk);

		}
		if (rLookup->term_to_query == SecondNoum)
		{
			auto r2 = query_relation(rel, arg1, value, localsEntry, stk);
			if (r2.result == QEquals)
			{
				return r2;
			}
		}
	}
	printf("%s \n", rLookup->relation.c_str());
	return QNotEquals ;


}
 

void add_if_unique(std::list<HBlock>& lst, HBlock x)
{	
	for (auto q : lst)
	{
		if (CBlock::isSame(q.get(), x.get()))
		{
			return;
		}
	}
	lst.push_back(x);
}


 
CBlocking::HBlock CBlockInterpreter::lookup_intersection(HBlock v1, HBlock v2,  HRunLocalScope localsEntry, QueryStack *stk)
{
	if (v1 == nullptr || CBlock::isSame( v1.get(), Nothing.get())) return  Nothing;
	if (v2 == nullptr || CBlock::isSame(v2.get(), Nothing.get())) return  Nothing;

	std::vector<HBlock> p1;
	std::vector<HBlock> p2;

	
	if (auto vs1 = DynamicCasting::asHBlockList(v1))	
	{
		p1 = std::vector<HBlock>(vs1->lista.begin(), vs1->lista.end());
	}
	else
	{	
		p1.push_back(v1);
	}

	if (auto vs2 = DynamicCasting::asHBlockList(v2))
	{
		p2 = std::vector<HBlock>(vs2->lista.begin(), vs2->lista.end());
	}
	else
	{
		p2.push_back(v2);
	}

	HBlockList lista_ret = std::make_shared<CBlockList>(std::list<HBlock>());
	for (size_t i1 = 0; i1 < p1.size(); ++i1)
	{
		bool exist = false;
		for (size_t i2 = 0; i2 < p2.size(); ++i2)
		{
			if (CBlock::isSame(p1[i1].get(), p2[i2].get()))
			{
				exist = true;
				break;
			}
		}
		if (exist)
			add_if_unique(lista_ret->lista, p1[i1]);
	}

 
	return lista_ret;
}


CBlocking::HBlock CBlockInterpreter::lookup_union(HBlock v1, HBlock v2, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (v1 == nullptr || CBlock::isSame(v1.get(), Nothing.get())) return  v2;
	if (v2 == nullptr || CBlock::isSame(v2.get(), Nothing.get())) return  v1;

	HBlockList lista1 = std::make_shared<CBlockList>( std::list<HBlock>());
	if (auto vs1 = DynamicCasting::asHBlockList(v1))
	{
		for (auto x : vs1->lista)
		{
			add_if_unique(lista1->lista, x);
		}
	}
	else
	{
		add_if_unique(lista1->lista, v1);
	}

	 

	if (auto vs1 = DynamicCasting::asHBlockList(v1))
	{
		for (auto x : vs1->lista)
		{
			add_if_unique(lista1->lista, x);
		}
	}
	else
	{
		add_if_unique(lista1->lista, v1);
	}
	return lista1;

}



//Este sjuito sempre retorna uma lista ....
CBlocking::HBlock CBlockInterpreter::lookup_verb(HBlockVerbLookup vLookup, HRunLocalScope localsEntry ,QueryStack *stk  )
{

	auto val1 = resolve_argument_match( vLookup->value1 , localsEntry , stk);
	auto val2 = resolve_argument_match(vLookup->value2, localsEntry, stk);

	for (auto & rv : verbRelationAssoc)
	{

		//printf("%s  ==? %s \n", rv.first.c_str(), vLookup->verb.c_str());
		if (rv.first == vLookup->verb )
		{
			//tem uma relacao com esse verbo

			const string relation_name = rv.second->relationNoum->named();
			{
				const map<basic_string<char>, shared_ptr<CBlockRelationBase>>::iterator rel_find = this->staticRelation.
				                                                                                   find(relation_name);
				if (rel_find != this->staticRelation.end())
				{
					HBlockRelationBase rel = rel_find->second;

			 


					if (rv.second->type() == BlockVerbReverseRelation)
					{
						std::swap(val1, val2);
						if (vLookup->term_to_query == FirstNoum) { vLookup->term_to_query = SecondNoum; }
						else if (vLookup->term_to_query == SecondNoum) { vLookup->term_to_query = FirstNoum; }
					}


					if (vLookup->term_to_query == FirstNoum)
					{
						if (rel->is_various_noum1())
						{
							return lookup_relation_XS_Y_1(relation_name, val1, val2, localsEntry, stk);
						}
						else
						{
							return lookup_relation_X_Y_1(relation_name, val1, val2, localsEntry, stk);
						}

					}
					if (vLookup->term_to_query == SecondNoum)
					{
						if (rel->is_various_noum2()) return lookup_relation_X_YS_2(relation_name, val1, val2, localsEntry, stk);
						return lookup_relation_X_Y_2(relation_name, val1, val2, localsEntry, stk);
					}

				}

			}

			return nullptr; // retorna aqui quando existe uma relacao deste tipo
		}
	}
	 
	return lookup_verb_List(vLookup, localsEntry, stk );

	return nullptr;

}


CBlocking::HBlockList CBlockInterpreter::lookup_value_by_Selector(HBlockMatch valueToMatch, HRunLocalScope localsEntry, QueryStack *stk)
{
	if (HBlockMatchNamed mNamed  = DynamicCasting::asHBlockMatchNamed( valueToMatch ))
	{
		return lookup_value_by_Selector(mNamed->matchInner, localsEntry,stk);
	}


	// busca dentro desses matchs alguem que � um kind de algum tipo	 

	HBlockMatch resolvedMatch = Resolve_Selector(valueToMatch, localsEntry); 
	 
	std::list<HBlock> retList =  getInstancesFromSelector(resolvedMatch, localsEntry);
	return  make_shared<CBlockList>(retList);

	
}

CBlocking::HBlockList CBlockInterpreter::lookup_verb_List(HBlockVerbLookup vLookup, HRunLocalScope localsEntry, QueryStack *stk)
{
	HBlockMatch val1 = vLookup->value1;
	auto val2 = vLookup->value2;
	std::list<HBlock > wList;

	 

	// faz uma lista de todos os objetos do tipo vLookup value1 ... supondo ser um tipo
	HBlockList  objList = lookup_value_by_Selector(val1,   localsEntry, stk);
	
	if (objList == nullptr) return nullptr; //nada retorna nada

	// para cada tipo ... testa a relacao verbal com o value2 ...

	string verbString = vLookup->verb;
	if ( isSameString(verbString,"is"))
	{
		for (auto &o : objList->lista)
		{ 
			QueryResultContext rr = query_is(  o, val2, localsEntry, stk);
			if (rr.result == QEquals)
			{
				wList.push_back(o);
			}
		}
		return std::make_shared<CBlockList>(wList);
	}
	else
	{
		for (auto &o : objList->lista)
		{

			// se positivo inclua na lista
			QueryResultContext rrcstm = get_system_verbs(verbString, o, val2, localsEntry, stk); // "listed in" , "size of"
			if (rrcstm.result == QEquals)
			{
				wList.push_back(o);
			}
			else
			{
				QueryResultContext rr = query_user_verbs(verbString, o, val2, localsEntry, stk);
				if (rr.result == QEquals)
				{
					wList.push_back(o);
				}
			}
		}
	}

	return std::make_shared<CBlockList>(wList);
}



bool CBlockInterpreter::exist_relation(string relationNamed, CBlocking::HBlock c_block, CBlocking::HBlock value , HRunLocalScope localsEntry, QueryStack *stk)
{
    for (auto &rr : relInstances)
    {
        if (rr->relation->named == relationNamed)
        {
            {
            
				QueryResultContext r1 = query_is(rr->value1, c_block, localsEntry, stk );
                if (r1.result != QEquals) continue;

				QueryResultContext r2 = query_is(rr->value2, value, localsEntry, stk);
                if (r2.result != QEquals) continue;

                return true;
            }
        }
    }
//verifica com simetria
    for (auto &rr : relInstances)
    {
        if(rr->relation->is_symetric()) {
            if (rr->relation->named == relationNamed) {
                {
                   
					QueryResultContext r1 = query_is(rr->value2, c_block, localsEntry, stk);
                    if (r1.result != QEquals) continue;

					QueryResultContext r2 = query_is(rr->value1, value, localsEntry, stk);
                    if (r2.result != QEquals) continue;

                    return true;
                }
            }
        }
    }
    return false ;
}
bool CBlockInterpreter::setVerbRelation(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry , QueryStack *stk )
        {

                for (auto & rv : verbRelationAssoc)
                {
                    if (rv.first == vb)
                    {
                        //tem uma relacao com esse verbo

                        auto relation_name = rv.second->relationNoum->named();
                        if (relation_name != "dynamic")
                        {
                            auto rel_find = this->staticRelation.find(relation_name);
                            if (rel_find != this->staticRelation.end())
                            {
                                HBlockRelationBase rel = rel_find->second;

                                bool ex = exist_relation( relation_name, c_block, value , localsEntry  ,stk );
                                if (ex == false )
                                {
//bool set_relation(HBlockRelationBase relation, CBlocking::HBlock n1, CBlocking::HBlock n2, HRunLocalScope localsEntry);

                                    set_relation(rel, c_block, value, localsEntry ,stk );
                                }
                                return true ;
                            }

                        }
                        else {
                            return false; //relacoes dinamicas nao podem ser SETADAS
                        }
                    }

                }
            return false;
        }

bool CBlockInterpreter::setVerb(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value,HRunLocalScope localsEntry,   QueryStack *stk)
{

    bool q = setVerbRelation(vb, c_block, value, localsEntry,stk);
    if (q) return true ;



	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		logMessage("verb  |" + vb + "| is not defined");
		return false;
	}


	{
		std::list<HBlockAssertion_is> &decList = alist->second;
		for(auto &c_is : decList)
		{
			if ((c_is->get_obj() == c_block) && (c_is->get_definition() == value))
			{
				return true; // ja existe
			}
		}
		//decList.push_back(make_shared<CBlockAssertion_isDirectAssign>(c_block, value));

		decList.push_back( make_shared<CBlockIsVerb>( vb,  c_block, value));
		return true ;
	}

}
 
QueryResultContext CBlockInterpreter::query_relation_instance(HBlockRelationInstance  rr, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{

 

	QueryResul query_2 = QUndefined;
	QueryResultContext qc1 = query_is(c_block, rr->value1, localsEntry, stk);
	if (QEquals == qc1.result)
	{

		

		QueryResultContext qc2 = query_is(rr->value2, value, localsEntry, stk);
		if (QEquals == qc2.result)
		{
 
			return qc2;
		}

		query_2 = QNotEquals;
		if (rr->relation->is_various_noum2() == false)
		{
			return QNotEquals;
		}
	}
	else if (QUndefined == query_2)
	{
		QueryResultContext qc3 = query_is(rr->value2, value, localsEntry, stk);
		if (QEquals == qc3.result)
		{
			QueryResultContext qc4 = query_is(c_block, rr->value1, localsEntry, stk);
			if (QEquals == qc4.result)
			{
				return qc4;
			}
			if (rr->relation->is_various_noum1() == false)
			{
				return QNotEquals;
			}
		}
	}


	if (rr->relation->is_symetric()) // Trocado
	{
		QueryResultContext qcc1 = query_is(rr->value2, c_block, localsEntry, stk);
		if (QEquals == qcc1.result)
		{
			QueryResultContext qcc2 = query_is(value, rr->value1, localsEntry, stk);
			if (QEquals == qcc2.result)
			{
				return qcc2;
			}
			if (rr->relation->is_various_noum2() == false)
			{
				return QNotEquals;
			}
		}
	}

	return QUndefined;
}

QueryResultContext CBlockInterpreter::query_relation_property(HBlockNoum property_noum, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
 

	// procupara pela relacao que tem um called que eh compativel com o property_noum
	for (auto &rr : relInstances)
	{
		if (rr->relation->input_B->named == property_noum->named()) //Ok, this is 
		{
			QueryResultContext query_inst = query_relation_instance(rr, c_block, value, localsEntry, stk);
			if (query_inst.result == QEquals) return query_inst;
		}

		if (rr->relation->input_A->named == property_noum->named()) //Ok, this is 
		{
			CBlocking::HBlock arg1 = c_block;
			CBlocking::HBlock arg2 = value;
			 
			QueryResultContext query_inst = query_relation_instance(rr, arg2, arg1,   localsEntry, stk);//reverse the property
			if (query_inst.result == QEquals ) return query_inst;
		}

	}
 return QUndefined;
}

QueryResultContext CBlockInterpreter::query_relation(HBlockRelationBase rel, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk)
{
	// Percorre todos e retorna o valor
	for (auto &rr : relInstances)
	{
		if (rr->relation->named == rel->named)
		{
			QueryResultContext query_inst = query_relation_instance(rr, c_block, value, localsEntry, stk);
			if (query_inst.result == QEquals) return query_inst;
		}  
	}
	// nao eh um teste de instancia ...
 


	return QUndefined;
}

QueryResultContext CBlockInterpreter::query_user_verbs(string vb, CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk_in)
{
	 
	std::unique_ptr<QueryStack> stk_unique = nullptr;
	if (stk_in != nullptr)
	{
		if (stk_in->isQuery(vb, c_block, value)) return QUndefined;
		stk_unique = std::make_unique<QueryStack>(*stk_in); 		 
	}
	else
	{
		stk_unique = std::make_unique<QueryStack>( );
	}
	QueryStack *stk   = stk_unique.get();
	stk->addQuery(vb, c_block, value);


	 


	// Tem alguma relacao associada ??
	for (auto & rv : verbRelationAssoc)
	{
		if (isSameString(rv.first , vb))
		{
			auto relation_name = rv.second->relationNoum->named();
			if (relation_name != "dynamic")
			{
				auto rel_find = this->staticRelation.find(relation_name);
				if (rel_find != this->staticRelation.end())
				{
					HBlockRelationBase rel = rel_find->second;

					if (rv.second->type() == BlockVerbDirectRelation)
					{
						QueryResultContext rel_query = this->query_relation(rel, c_block, value, localsEntry, stk);
						if (rel_query.result == QEquals) return  rel_query;
						return QNotEquals;
					}
					else if (rv.second->type() == BlockVerbReverseRelation)
					{
						// inverte a busca aqui
						CBlocking::HBlock arg1 = c_block;
			            CBlocking::HBlock arg2 = value;
						QueryResultContext rel_query = this->query_relation(rel, arg2 , arg1,   localsEntry, stk);
						if (rel_query.result == QEquals) return  rel_query;
						return QNotEquals;
					}
				}
			}
		}

	}


	



	auto alist = verbAssertation.find(vb);

	if (alist == verbAssertation.end())
	{
		return QueryResul::QUndefined;
	} 

	auto nn = decides_if.size();
	for (auto dctIF : decides_if)
	{
		if (HBlockMatchIsVerb  DctQueryVerbIS = DynamicCasting::asHBlockMatchIsVerb(dctIF->queryToMatch))
		{ 
			if (isSameString(DctQueryVerbIS->verb, vb))
			{

				std::unique_ptr<QueryStack>  next_stack = generateNextStack(stk, vb, DctQueryVerbIS, c_block, value);
				if (next_stack != nullptr)
				{
					auto value_1 = c_block;
					if (HBlockMatchNoum mvalue_1 = DynamicCasting::asHBlockMatchNoum(value_1)) value_1 = mvalue_1->inner;


					if (HBlockNoum nnoum_1 = DynamicCasting::asHBlockNoum(value_1))
					{
						HBlock resolved = resolve_noum(nnoum_1, localsEntry);
						if (resolved != nullptr)
						{
							value_1 = resolved;
						}
					}

					auto value_2 = value;
					if (HBlockMatchNoum mvalue_2 = DynamicCasting::asHBlockMatchNoum(value_2)) value_2 = mvalue_2->inner;
					if (HBlockNoum nnoum_2 = DynamicCasting::asHBlockNoum(value_2))
					{
						HBlock resolved = resolve_noum(nnoum_2, localsEntry);
						if (resolved != nullptr)
						{
							value_2 = resolved;
						}
					}

	 




					auto result = Match_DirectIs(DctQueryVerbIS->obj, DctQueryVerbIS->value, value_1, value_2, nullptr, next_stack.get());
					if (result.hasMatch == true)
					{
						auto localsNext = std::make_shared< CRunLocalScope >(nullptr, result.maptch);

			 
						auto r = getDecidedValue(dctIF->decideBody, localsNext, next_stack.get());
						return r;
					}
				}
			}
		}
	}


 
	// Match com o What

	for(auto &dct : decides_what)
	{
		if (HBlockMatchIsVerb qVerb = DynamicCasting::asHBlockMatchIsVerb(dct->queryToMatch)) {
			//cout << vb << " =?= " << qVerb->verb << endl;
			if (qVerb->verb == vb) {
				CBlocking::HBlock wvalued = getDecidedValueOf(value, dct, nullptr, stk);
				if (wvalued != nullptr) 
				{
					auto wresult = query_is(c_block, wvalued, nullptr, stk);
					return wresult;
				}
			}
		}
	}


	// Match com o primeiro Noum


	//Custom Define
	for (auto &v : decides_noum1)
	{
		if (HBlockMatchIsVerb qVerb_N1 = DynamicCasting::asHBlockMatchIsVerb(v->queryToMatch))
		{
			
			if (vb == qVerb_N1->verb)
			{
			//	cout << vb << " =?= " << qVerb_N1->verb << endl;
				CResultMatch  result_value = Match(qVerb_N1->value, value, localsEntry, stk); // o resto da match ??
				if (result_value.hasMatch)
				{
					auto  obj_resolved = v->decideBody;
 
					
					return query_is(c_block, obj_resolved,localsEntry,stk );
				}
			}
		}
	}



	std::list<HBlockAssertion_is> &decList = alist->second;
	for (auto &c_is : decList)
	{
		QueryResultContext a1 = query_is(c_block , c_is->get_obj() , localsEntry,stk );
		if (a1.result == QEquals)
		{
			QueryResultContext a2 = query_is(c_is->get_definition(), value,localsEntry,stk);
			if (a2.result == QEquals)
			{
				return a2;
			}
		}
	}
	return QueryResul::QUndefined;
}

static char const * reserved_words[] = {
	"nothing",
	"value",
	"true",
	"false",
	"entity",
	"kind",
	"relation",
	"list",
	"phase",	
	"yes",
	"no",
	"which",
	"what",
	"where",
	"verb",
	"the",
	"a",
	"an",
	0
};
 

bool CBlockInterpreter::isReservedWord(string cs)
{
	const char** w = reserved_words;
	while (*w)
	{
		if (strcmp(*w, cs.c_str()) == 0) return true;
		*w++;
	}
	return false;
}


bool CBlockInterpreter::assert_it_verbRelation( std::string verbNamed ,CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry, QueryStack *stk) {
	if (HBlockNoum nbase = DynamicCasting::asHBlockNoum(obj)) {
		CBlocking::HBlock nobj = resolve_noum(nbase,localsEntry);
		if (nobj != nullptr) {
			return assert_it_verbRelation(verbNamed , nobj, value, localsEntry,stk);
		}		
	}
	return setVerb(verbNamed, obj, value,localsEntry,stk );

	return false;
}

bool CBlockInterpreter::insert_newPhrase(HBlockPhraseDefine phrase_dec)
{

	phrases.push_back(phrase_dec);
	return true;
}



bool CBlockInterpreter::insert_newVerb(HBlockVerb verb_dec)
{
	// verifica se ja esxite esse verb

	auto vfind = std::find_if(verbs.begin(),verbs.end() ,
	[&verb_dec](const HBlockVerb& t) { return t->named == verb_dec->named; }
	);
	 
	if (vfind != verbs.end())
	{
		//throw  "Verb is Assigned";		
		logError("Verb is Registed");
		return false ;
	}
	//nao tem esse verbo
 
	verbs.push_back(verb_dec);

	symbols.add(verb_dec , verb_dec);

	return true;
}

bool Interpreter::CBlockInterpreter::existSymbol(string cs)
{
	return symbols.exist(this->language ,cs);
	//for (auto s : symbols) if (s.first == cs) return true;
	//return false;
}

void Interpreter::CBlockInterpreter::addSymbol(string cs, HBlock value)
{
	if (isReservedWord(cs))
	{
		printf("invalid Word %s \n", cs.c_str());
		logError("Invalid Word\n");
		return;
	}
	printf("new Symbol %s\n", cs.c_str());
	//value->dump("");
	symbols.add(cs, value);
}



bool CBlockInterpreter::assert_newVerb(HBlockVerbRelation value)
{
	HBlock   verb = value->verbNoum;
	if (HBlockList    v_list = DynamicCasting::asHBlockList(value->verbNoum))
	{
		if (v_list->lista.empty())
		{
			logError("Verb is empty ");
			return false;
		}
		//limpa os to be na frente
		while (v_list->lista.empty() == false && (HtoString(v_list->lista.front()) == "to")) v_list->lista.pop_front();
		while (v_list->lista.empty() == false && (HtoString(v_list->lista.front()) == "be")) v_list->lista.pop_front();
		
		verb = v_list ;
	}
	 

	std::string vstr = HtoString(verb);
	//verifica se ja existe esse verbo

	auto vfind = verbAssertation.find(vstr);
	if  (vfind != verbAssertation.end() )
	{
		//throw  "Verb is Assigned";
		logError( "Verb is Assigned");
		return false;
	}

	
	//cout << " new Verb |" <<vstr  <<"|"<< endl;
	verbAssertation[ vstr ] = std::list<HBlockAssertion_is>();

    // Existe essa relacao ??
	verbRelationAssoc[ vstr ] = value ;
 
	addSymbol(vstr, value);

	return true;
}


//Event Hanle

bool CBlockInterpreter::insert_newEventHandle(HBlockEventHandle event_handle)
{
	event_handles.push_back(event_handle);
	return true;
}
 