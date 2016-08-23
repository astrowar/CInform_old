//
// Created by Eraldo Rangel on 18/08/16.
//

#include "BlockInterpreter.h"
#include "CBlockMatch.h"
#include "CBlockBoolean.h"

#include "CBlockDumpValues.h"

#include <iostream>
using namespace std;


void CUnresolved::dump(string ident)
{
	cout << ident << "UNRESOLVED: " << this->contents << endl;
}

void CBlockNoum::dump(string ident)
{
	cout << ident << this->named << endl;
}

void CBlockEnums::dump(string ident)
{
	cout << ident << "Enum:" << endl;
	for (auto e =  values.begin(); e != values.end(); ++e)
	{
		(*e)->dump(ident + "   ");
	}
}

void CBlockKindOfName::dump(string ident)
{
	cout << ident << "Kind Named :  " << baseClasseName << endl;
}

void CBlockKindOf::dump(string ident)
{
	cout << ident << "Kind Of:  "  << endl;
	baseClasse->dump(ident + "   ");
}

void CBlockKindAction::dump(string ident)
{
	cout << ident << "Action applying to:  " << baseClasseName << endl;
	this->applyTo->dump(ident + "   ");
}

void CBlockKindValue::dump(string ident)
{
	cout << ident << "Kind Value: " << named << endl;
}

void CBlockKindThing::dump(string ident)
{
	cout << ident << "Kind Thing : " << named << endl;
}

void CBlockNamedValue::dump(string ident)
{
	cout << ident << "Named Value: " << named << endl;
}

void CBlockVariable::dump(string ident)
{
	cout << ident << "Variable: " << named << endl;
}

void CBlockProperty::dump(string ident)
{
	cout  << ident << "Property:" << endl;
	prop->dump(ident + "          ");
	cout  << ident << "      of:" << endl;
	obj->dump(ident + "          ");
}

void CBlockInstanceVariable::dump(string ident)
{

	cout << ident << "Property:" << endl;
	kind_name->dump(ident + "          ");
	cout << ident << "   called:" << endl;
   property_name->dump(ident + "          ");
}

void  CBlockList::dump(string  ident)
{
	cout <<ident << "List: " << endl;
	 for(auto e = lista.begin() ; e!= lista.end();++e)
	 {
		 (*e)->dump(ident + "   ");
	 }
}

void CBlockAssertion_is::dump(string ident)
{
	cout << ident << "Assert: " << endl;

	this->get_obj()->dump(ident + "     ");
	cout << ident << "is_____ " << endl;
	this->get_definition()->dump(ident + "     ");
}

void CBlockMatch::dump(string ident)
{
	cout << ident << "Match " << endl;
	{
		this->matchInner->dump(ident + "       ");
	}
}

void CBlockMatchAny::dump(string ident)
{
	cout << ident << "Match Any " << endl;

}

void CBlockMatchNamed::dump(string ident)
{
	cout << ident << "Match As " << named << endl;
	{
		this->matchInner->dump(ident + "       ");
	}
}

void CBlockMatchKind::dump(string ident)
{
	cout << ident << "Match Kind: " << endl;
	{
		this->kind->dump(ident + "       ");
	}
}

void CBlockMatchList::dump(string ident)
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

void CBlockActionApply::dump(string ident)
{
	cout << ident << "Action applyTo " << endl;
	{
		this->noum1->dump(ident + "       ");
		cout << ident << "With " << endl;
		this->noum2->dump(ident + "       ");

	}
}

void CBlockAction::dump(string ident)
{
	cout << ident << "Action " << endl;
	{
		this->input->dump(ident + "       ");
	}

}

void CBlockToDecide::dump(string ident)
{
	cout << ident << "To Decide " << endl;
	{

		this->queryToMatch->dump(ident + "       ");

		cout << ident << "Decide for " << endl;
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecidewhether::dump(std::string ident)
{
	cout << ident << "To Decide Whether (bool)" << endl;
	{
		this->queryToMatch->dump(ident + "       ");
		cout << ident << "Decide for " << endl;
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideIf::dump(string ident)
{
	cout << ident << "Define " << endl;
	{

		this->queryToMatch->dump(ident + "       ");

		cout << ident << "IF " << endl;
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideOn::dump(std::string ident)
{
	cout << ident << "DecideOn " << endl;
	{		 
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockBooleanAND::dump(string ident)
{
	cout << ident << "Boolean " << endl;
	{
		this->input_A->dump(ident + "       ");
		cout << ident << "AND " << endl;
		this->input_B->dump(ident + "       ");
	}

}

void CBlockBooleanOR::dump(string ident)
{
	cout << ident << "Boolean NOT" << endl;
	{
		this->input_A->dump(ident + "       ");
	}
}

void CBlockBooleanNOT::dump(string ident)
{
}

void CBlockActionCall::dump(string ident)
{
	cout << ident << "Call " << endl;
	{
		this->action->dump(ident + "       ");
		cout << ident << "Args: " << endl;
		this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
}

void CBlockAssertion_isActionOf::dump(string ident)
{
	cout << ident << "Action " << endl;
}

void CBlockDinamicDispatch::dump(string ident)
{
	cout << ident << "DinamicDispatch " << endl;
	{
		this->input->dump(ident + "       ");
	}
}

void CBlockStaticDispatch::dump(string ident)
{
	cout << ident << "StaticDispatch Entry:  " << this->staticEntryTable << endl;
	{

		cout << ident << "Args: " << endl;
		this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
}

void CBlockAssertion_canBe::dump(string ident)
{
	cout << ident << "Can Be " << endl;
	{
		this->get_obj()->dump(ident + "       ");
		cout << ident << "Values: " << endl;
		this->definition->dump(ident + "       ");

	}
}

void CBlockAssertion_isKindOf::dump(string ident)
{
	cout << ident << "is Kind Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isInstanceOf::dump(string ident)
{
	cout << ident << "is Instance Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isNamedValueOf::dump(string ident)
{
	cout << ident << "is Named Value Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isVariable::dump(string ident)
{
	cout << ident << "is Variable Of  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isDefaultAssign::dump(string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Usually " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isConstantAssign::dump(string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Always " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isForbiddenAssign::dump(string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Never " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isDirectAssign::dump(string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is " << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_isNotDirectAssign::dump(string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is NOT" << endl;
	this->value->dump(ident + "       ");
}

void CBlockAssertion_InstanceVariable::dump(string ident)
{
	cout << ident << "Instance  " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Has " << endl;
	this->instance_variable->dump(ident + "       ");

}

void CBlockIsVerb::dump(string ident)
{
	cout << ident << "Is     " << verb << endl;
	this->n1->dump(ident + "       ");
	cout << ident << "related " << endl;
	this->n2->dump(ident + "       ");
}

void CBlockIsNotVerb::dump(string ident)
{
	cout << ident << "Is  NOT " << verb << endl;
	this->n1->dump(ident + "       ");
	cout << ident << "related " << endl;
	this->n2->dump(ident + "       ");
}

void CBlockVerbRelation::dump(string ident)
{
	cout << ident << "Verb  " << endl;
	this->verbNoum->dump(ident + "       ");
	cout << ident << "Implies " << endl;
	this->relation->dump(ident + "       ");
}

void CBlockUnderstand::dump(string ident)
{
	cout << ident << "Understand  " << endl;
	this->input_n->dump(ident + "       ");
	cout << ident << "As " << endl;
	this->output_n->dump(ident + "       ");

}

void CBlockUnderstandStatic::dump(string ident)
{
	cout << ident << "Understand Static " << endl;
	this->argument_match->dump(ident + "       ");
	cout << ident << "As " << endl;
	this->output_n->dump(ident + "       ");
}