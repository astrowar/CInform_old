 
#include "CBlockInterpreterRuntime.hpp"
#include "sharedCast.hpp"
 
#include "sharedCast.hpp"
using namespace std;


pair<HBlockKind, HBlockKind>
CBlockInterpreter::create_derivadeKind(string called, string baseClasseName) {

    HBlockKind b = nullptr;
    HBlockKind bup = nullptr;

    if (baseClasseName == "value") {
        b = make_shared<CBlockKindValue>(called);

    } else if (baseClasseName == "") {
        b = make_shared<CBlockKindThing>(called);  //Default
    } else {
        // o que eh a baseclass ???
        HBlock r = resolve_string(baseClasseName,nullptr);

        if (HBlockKindThing kt = asHBlockKindThing(r)) {
            b = make_shared<CBlockKindThing>(called);
            bup = kt;
        } else if (HBlockKindValue ktv = asHBlockKindValue(r)) {
            b = make_shared<CBlockKindValue>(called);
            bup = ktv;
        } else {
			logError("What ?? " + baseClasseName);
            return pair<HBlockKind, HBlockKind>(nullptr, nullptr);;
        }

    }
    return pair<HBlockKind, HBlockKind>(b, bup);

}






bool CBlockInterpreter::assert_it_Value(HBlock obj, HBlock value, HRunLocalScope localsEntry)
{
	execute_set(obj, value,localsEntry);

    if (HBlockNoum nbase = asHBlockNoum(obj)) {
        HBlock nobj = resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_Value(nobj, value,localsEntry);
		 
        }
     
    }

    if (HBlockInstance nInst = asHBlockInstance(obj)) {
        if (HBlockNoum nbase = asHBlockNoum(value)) {
            HBlock nobj = resolve_noum(nbase,localsEntry);
            if (nobj == nullptr) 
			{
                nInst->set(nbase);
                return true;
            }
        }
    }

 



    if (HBlockProperty prop_n = asHBlockProperty(obj)) {
        HBlock propNamed = prop_n->prop;
        HBlock destination = prop_n->obj;
        return assert_it_property(propNamed, destination, value,localsEntry);
    }

	if (HVariableNamed  var_n = asHVariableNamed(obj)) {
		 
		HBlock destination = var_n->value;
		if (value_can_be_assign_to(value , var_n->kind,localsEntry))
		{
            if (HBlockList   val_list = asHBlockList(value))
            {
                //list is passed as copy
                HBlockList lcopy = make_shared<CBlockList> (std::list<HBlock>());
                lcopy->lista = val_list->lista;
                var_n->value = lcopy;

            }
            else {
                var_n->value = value;
            }
			return true;
		}
		//return assert_it_property(propNamed, destination, value);
	}


    return false;

}


bool CBlockInterpreter::assert_it_action(HBlock obj, HBlock value) 
{
	if (HBlockKindAction   act = asHBlockKindAction(value)) {
		if (HBlockAction abase = asHBlockAction(obj)) { 
			actions_header.push_back(abase);
			return true;
		}
	}


	if (HBlockKindAction   act = asHBlockKindAction(value)) {
		if (HBlockNoum nbase = asHBlockNoum(obj)) {

			auto haction = make_shared<CBlockAction >(nbase->named);
			//actions_header.push_back(haction);
			return assert_it_action(haction, value);
		}
	}



	return false;
}

bool CBlockInterpreter::assert_it_kind(HBlock obj, HBlock value,HRunLocalScope localsEntry) {
    if (HBlockKindOfName k = asHBlockKindOfName(value)) {
        if (HBlockNoum nbase = asHBlockNoum(obj)) {

            auto b_up = create_derivadeKind(nbase->named, k->baseClasseName);
            HBlockKind b = b_up.first;

            if (b_up.second != nullptr) {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                     make_shared<CBlockKindOf>(
                                                                                                             b_up.second));
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

            {

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbase, b);
                kindDefinitions.push_back(newDefi);
                assertions.push_back(newDefi);
            }

			logMessage("new Kind add " + nbase->named);
            return true;
        }

            //Processa a lista
        else if (HBlockList nList = asHBlockList(obj)) {
            for (auto nObj : nList->lista) {
                if (HBlockNoum nbasei = asHBlockNoum(nObj)) {
                    auto b_up = create_derivadeKind(nbasei->named, k->baseClasseName);
                    HBlockKind b = b_up.first;
                    if (b_up.second != nullptr) {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
                                                                                                             make_shared<CBlockKindOf>(
                                                                                                                     b_up.second));
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }

                    {

                        HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbasei, b);
                        kindDefinitions.push_back(newDefi);
                        assertions.push_back(newDefi);
                    }
					logMessage("new Kind add");
                }
            }
            return true;

        }

    }
   
	
	
	
	return false;

}



bool CBlockInterpreter::assert_it_instance(HBlock obj, HBlock baseKind, HRunLocalScope localsEntry) {

	if (HBlockNoum nbaseKind = asHBlockNoum(baseKind))
	{
		HBlock bbase = resolve_noum(nbaseKind, localsEntry);
		if (bbase != nullptr)
		{
			return assert_it_instance(obj, bbase, localsEntry);
		}
		else
		{
			logError("Kind not found " + nbaseKind->named);
			return false;
		}
	}

	if (HBlockList nobjList = asHBlockList(obj))
	{
		for (auto &e : nobjList->lista) {
			assert_it_instance(e, baseKind, localsEntry);
		}
		return true;
	}
    
 
        if (HBlockNoum nobj = asHBlockNoum(obj)) 
		{
           
            if (HBlockKind k = asHBlockKind(baseKind)) 
			{
                //HBlockInstance binstance = make_shared<CBlockInstance>(nobj->named);

                HBlockInstance binstance = new_Instance(nobj->named, k);

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(obj, binstance);
                HBlockAssertion_isInstanceOf newInst = make_shared<CBlockAssertion_isInstanceOf>(binstance, k);
                assertions.push_back(newDefi);
                assertions.push_back(newInst);
                 
				logMessage("new Instance add " + (nobj->named)  +" as "+  k->named );
                return true;
            }
           
        }

          
        

    

    return false;
}



bool CBlockInterpreter::assert_it_valuesDefinitions(HBlock c_block, HBlock value, HRunLocalScope localsEntry) {
    // Value Kind , is , list of Noums

    if (HBlockList vlist = asHBlockList(value)) // segundo argumento eh uma lista
        if (HBlockNoum nn = asHBlockNoum(c_block)) //primeiro eh um noum
        {
            // nn eh um value Kind ??
            HBlock nobj = resolve_noum(nn,localsEntry);
            if (HBlockKind nkind = asHBlockKind( nobj)) //mas na verdade o primeiro eh um kind ja definido
            {
                for (auto &v : vlist->lista) {
                    assert_it_instance(v, nkind,localsEntry);
                }
                return true;
            }

        }
    return false;
}

bool CBlockInterpreter::assert_newUnderstand(HBlockUnderstandDynamic value)
{
	dynamic_understand.push_back(value);
	return true;
}
