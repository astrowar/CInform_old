#include "BlockInterpreter.h"
#include <iostream>

using namespace std;

NoumDefinitions noum_nothing()
{
	return NoumDefinitions();
}

NoumDefinitions single_definitions(string noun, CBlock* block)
{
	return 	NoumDefinitions({ NoumDefinition(noun, block) });
}

NoumDefinitions join_definitions(NoumDefinitions a, NoumDefinitions b)
{
	NoumDefinitions ab(a.begin(), a.end());
	ab.insert(ab.end(), b.begin(), b.end());
	return ab;
}

void CUnresolved::dump(std::string ident)
{
	cout << ident << "UNRESOLVED: " << this->contents << endl;
}

CUnresolved::CUnresolved(string _contents): contents(_contents)
{
}

void CBlockNoum::dump(std::string ident)
{
	cout << ident << this->named << endl;
}

CBlockNoum::CBlockNoum(std::string _value)
{
	named = _value;
	//assert(named[0] != '[');
}

 
void CBlockEnums::dump(std::string ident)
{
	cout << ident << "Enum:" << endl;
	for (auto e =  values.begin(); e != values.end(); ++e)
	{
		(*e)->dump(ident + "   ");
	}
}

CBlockEnums::CBlockEnums(std::vector<CBlockNoum*> _values): values(_values)
{
	 
}

void CBlockKind::dump(std::string ident)
{
	cout << ident << "Kind: "<< named << endl;
}

void CBlockKindOf::dump(std::string ident)
{
	cout << ident << "Kind Of:  " << baseClasseName << endl;
}

void CBlockActionKind::dump(std::string ident)
{
	cout << ident << "Action applying to:  " << baseClasseName << endl;
	this->applyTo->dump(ident + "   ");
}

void CBlockKindValue::dump(std::string ident)
{
	cout << ident << "Kind Value: " << named << endl;
}

void CBlockInstance::dump(std::string ident)
{
	cout << ident << "Instance: " << named << endl;
}

CBlockInstance::CBlockInstance(string _named) : named(_named)
{
	assert(_named[0] != '[');
}

void CBlockNamedValue::dump(std::string ident)
{
	cout << ident << "Named Value: " << named << endl;
}

CBlockNamedValue::CBlockNamedValue(string _named) : named(_named)
{
	assert(_named[0] != '[');
}

void CBlockVariable::dump(std::string ident)
{
	cout << ident << "Variable: " << named << endl;
}

CBlockVariable::CBlockVariable(string _named) : named(_named)
{
	assert(_named[0] != '[');
}

void CBlockProperty::dump(std::string ident)
{
	cout  << ident << "Property:" << endl;
	prop->dump(ident + "          ");
	cout  << ident << "      of:" << endl; 	
	obj->dump(ident + "          ");
}

 

CBlockProperty::CBlockProperty(CBlock* _prop, CBlock* _obj): prop(_prop), obj(_obj)
{
	 
}

void CBlockInstanceVariable::dump(std::string ident)
{

	cout << ident << "Property:" << endl;
	kind_name->dump(ident + "          ");
	cout << ident << "   called:" << endl;
   property_name->dump(ident + "          ");
}

CBlockInstanceVariable::CBlockInstanceVariable(CBlock* _kind_name, CBlock* _called) : property_name(_called), kind_name(_kind_name)
{
}

 

void  CBlockList::dump(std::string  ident)
{ 
	cout <<ident << "List: " << endl;
	 for(auto e = lista.begin() ; e!= lista.end();++e)
	 {
		 (*e)->dump(ident + "   ");
	 }
}

void CBlockList::push_back(CBlock * c_block_value)
{
	lista.push_back(c_block_value);
}

NoumDefinitions CBlockList::noumDefinitions()
{
	NoumDefinitions nd = noum_nothing();
	for(auto i : lista)
	{
		nd = join_definitions(nd, i->noumDefinitions());
	}
	return nd;
}

void CBlockAssertion_is::dump(std::string ident)
{
	cout << ident << "Assert: " << endl;

	this->obj->dump(ident + "     ");
	cout << ident << "is_____ " << endl;
	this->definition->dump(ident + "     ");
}

 

 

void CBlockMatch::dump(std::string ident)
{
	cout << ident << "Match " << endl;
	{
		this->matchInner->dump(ident + "       ");
	}
}

void CBlockMatchKind::dump(std::string ident)
{
	cout << ident << "Match Kind: " << endl;
	{
		this->kind->dump(ident + "       ");
	}
}

void CBlockMatchList::dump(std::string ident)
{
	cout << ident << "Match List [" << endl;
	{
		for (auto i : matchList)
		{
			i->dump(ident + "       ");
		} 
	}
	cout << ident << "          ]" << endl;
}

void CBlockActionApply::dump(std::string ident)
{
	cout << ident << "Action applyTo " << endl;	
	{
		this->noum1->dump(ident + "       ");
		cout << ident << "With " << endl;
		this->noum2->dump(ident + "       ");

	}
}

CBlockActionApply::CBlockActionApply(CBlock* _noum1, CBlock* _noum2): noum1(_noum1), noum2(_noum2)
{
}

void CBlockAction::dump(std::string ident)
{
	cout << ident << "Action " << endl;
	{
		this->input->dump(ident + "       ");
	}

}

void CBlockToDecide::dump(std::string ident)
{
	cout << ident << "To Decide " << endl;
	{
		 
		this->queryToMatch->dump(ident + "       ");

		cout << ident << "Decide for " << endl;
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideIf::dump(std::string ident)
{
	cout << ident << "Define " << endl;
	{

		this->queryToMatch->dump(ident + "       ");

		cout << ident << "IF " << endl;
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockBooleanAND::dump(std::string ident)
{
	cout << ident << "Boolean " << endl;
	{
		this->input_A->dump(ident + "       ");
		cout << ident << "AND " << endl;
		this->input_B->dump(ident + "       ");
	}

}

void CBlockBooleanOR::dump(std::string ident)
{
	cout << ident << "Boolean NOT" << endl;
	{
		this->input_A->dump(ident + "       ");		 
	}
}

void CBlockBooleanNOT::dump(std::string ident)
{
}

CBlockInterpreter::CBlockInterpreter()
{
	 
}


CBlockInterpreter::~CBlockInterpreter()
{
}

void CBlockActionCall::dump(std::string ident)
{
	cout << ident << "Call " << endl;
	{
		this->action->dump(ident + "       ");
		cout << ident << "Args: " << endl;
		this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
}

void CBlockAssertion_isActionOf::dump(std::string ident)
{
	cout << ident << "Action " << endl;
}



//  define  ((Person:A) eat (thing:B)) is a Action.  -> first noum, second noum
//  define ((action:A) is in the presence of (other:B) ) if (( location of (first noum of A) ) is same (location B)).
//  eating something in the presence of Lady Bracknell

void eatExample()
{
	/*CBlockAssertion(CBlockAction( CBlockNoum("Person"), "eat", CBlockNoum("Thing")));

	CBlockAssertionCond(CBlockAssertion(CBlockAction("Action","A"), "in presence of", CBlockNoum("Person", "other")),
	CBlockSame(CBlockProp(CBlockNoum("location"), CBlockProp(CBlockNoum("first noum"), CBlockNoum("A")),
	CBlockProp(CBlockNoum("location"), CBlockNoum("other")))));

	CBlockMatchAction((CBlockAction("eat"), CBlockNoum("something")), "in presence of", CBlockNoum("Lady Bracknell"));
	*/


}


void CBlockAssertion_canBe::dump(std::string ident)
{
	cout << ident << "Can Be " << endl;
	{
		this->obj->dump(ident + "       ");
		cout << ident << "Values: " << endl;
		this->definition->dump(ident + "       ");

	}
}

CBlockAssertion_canBe::CBlockAssertion_canBe(CBlock* _obj, CBlockEnums* _definition) : CBlockAssertionBase(_obj), definition(_definition)
{
}

NoumDefinitions CBlockAssertion_isKindOf::noumDefinitions()
{	
	return  single_definitions(this->noum->named, this->definition);	
}

void CBlockAssertion_isKindOf::dump(std::string ident)
{
	cout << ident << "is Kind Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isInstanceOf::dump(std::string ident)
{
	cout << ident << "is Instance Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isNamedValueOf::dump(std::string ident)
{
	cout << ident << "is Named Value Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isVariable::dump(std::string ident)
{
	cout << ident << "is Variable Of  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isDefaultAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Usually " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isConstantAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Always " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isForbiddenAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Never " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isDirectAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isNotDirectAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is NOT" << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_InstanceVariable::dump(std::string ident)
{
	cout << ident << "Instance  " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Has " << endl;
	this->instance_variable->dump(ident + "       ");

}

void CBlockIsVerb::dump(std::string ident)
{
	cout << ident << "Is     " << verb << endl;
	this->n1->dump(ident + "       ");
	cout << ident << "related " << endl;
	this->n2->dump(ident + "       "); 
}

void CBlockIsNotVerb::dump(std::string ident)
{
	cout << ident << "Is  NOT " << verb << endl;
	this->n1->dump(ident + "       ");
	cout << ident << "related " << endl;
	this->n2->dump(ident + "       ");
}

void CBlockVerbRelation::dump(std::string ident)
{
	cout << ident << "Verb  " << endl;
	this->verbNoum->dump(ident + "       ");
	cout << ident << "Implies " << endl;
	this->relation->dump(ident + "       ");
}

void CBlockUnderstand::dump(std::string ident)
{
	cout << ident << "Understand  " << endl;
	this->input_n->dump(ident + "       ");
	cout << ident << "As " << endl;
	this->output_n->dump(ident + "       ");

}
