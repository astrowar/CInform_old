#include "BlockInterpreter.h"
#include <iostream>
#include "CblockAssertion.h"
#include "CBlockMatch.h"
#include "CBlockBoolean.h"

using namespace std;

NoumDefinitions noum_nothing()
{
	return NoumDefinitions();
}

 

NoumDefinitions single_definitions(string noun, UBlock block)
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

bool CBlockEnums::contains(string cs)
{
	for(auto &n : values)
	{
		if (n->named == cs) return true;
	}
	return false;
}


void CBlockKindOfName::dump(std::string ident)
{
	cout << ident << "Kind Named :  " << baseClasseName << endl;
}

void CBlockKindOf::dump(std::string ident)
{
	cout << ident << "Kind Of:  "  << endl;
	baseClasse->dump(ident + "   ");
}

void CBlockKindAction::dump(std::string ident)
{
	cout << ident << "Action applying to:  " << baseClasseName << endl;
	this->applyTo->dump(ident + "   ");
}

void CBlockKindValue::dump(std::string ident)
{
	cout << ident << "Kind Value: " << named << endl;
}

void CBlockKindThing::dump(std::string ident)
{
	cout << ident << "Kind Thing : " << named << endl;
}

CVariableSlotEnum::CVariableSlotEnum(CBlockEnums* enums)
{
	this->valueDefinition = enums;
	this->value = enums->values.front();
}

CVariableSlotBool::CVariableSlotBool(CBlockNoum* valueDef)
{
	this->valueDefinition = valueDef;
	this->value = true;
}

CVariableNamed::CVariableNamed(CBlockNoum* _name, CBlockKind* _kind, CBlock* _value):value(_value),kind(_kind), name(_name)
{
}

void CBlockInstance::dump(std::string ident)
{
	cout << ident << "Instance: " << named << endl;
}

CBlockInstance::CBlockInstance(string _named) : named(_named)
{
	//assert(_named[0] != '[');
}

void CBlockInstance::newEnumVariableSlot(CBlockEnums* definition)
{
	this->anomimousSlots.push_back( new  CVariableSlotEnum(definition));

}

void CBlockInstance::newBoolVariableSlot(CBlockNoum * value)
{
	this->anomimousSlots.push_back(new CVariableSlotBool (value));
}

void CBlockInstance::newNamedVariable(CBlockNoum* called, CBlockKind* kind)
{
	this->namedSlots.push_back(new CVariableNamed(called, kind, nullptr));
	
}

void CBlockInstance::set(CBlockNoum* c_block)
{
	//Anonymous SET
	for(auto &va :	this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains( c_block->named ))
			{				
				venum->value = c_block;
				return;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == c_block->named )
			{
				vbool->value = true;
				return;
			}
		}
	}
}

void CBlockInstance::unset(CBlockNoum* c_block)
{
	//Anonymous SET
	for (auto &va : this->anomimousSlots)
	{
	 
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == c_block->named)
			{
				vbool->value = false;
				return;
			}
		}
	}
}

bool CBlockInstance::has_slot(CBlockNoum* value)
{

	for (auto &va : this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{				 
				return true ;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == value->named)
			{				 
				return true ;
			}
		}
	}
	return false;
}

CVariableNamed* CBlockInstance::get_property(string named)
{
	for (auto &va : this->namedSlots)
	{
		if (va->name->named == named)
		{
			return va;
		}
	}
	return nullptr;
}

void CBlockInstance::set_property(string cs, UBlock value)
{
	for (auto &va : this->namedSlots)
	{
		if (va->name->named == named)
		{
			va->value = value;
		}
	}
	return;
}

QueryResul CBlockInstance::is_set(CBlockNoum * value)
{
	for (auto &va : this->anomimousSlots)
	{
		if (CVariableSlotEnum * venum = dynamic_cast<CVariableSlotEnum*>(va))
		{
			if (venum->valueDefinition->contains(value->named))
			{
				if (venum->value->named == value->named) return QEquals;
				return QNotEquals;
			}
		}
		if (CVariableSlotBool * vbool = dynamic_cast<CVariableSlotBool*>(va))
		{
			if (vbool->valueDefinition->named == value->named)
			{
			 
				if (vbool->value) return QEquals;
				return QNotEquals;
			}
		}
	}
	return QUndefined;
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



CBlockProperty::CBlockProperty(UBlock _prop, UBlock _obj): prop(( _prop)), obj(( _obj))
{

}

void CBlockInstanceVariable::dump(std::string ident)
{

	cout << ident << "Property:" << endl;
	kind_name->dump(ident + "          ");
	cout << ident << "   called:" << endl;
   property_name->dump(ident + "          ");
}

CBlockInstanceVariable::CBlockInstanceVariable(CBlockNoum* _kind_name, CBlockNoum* _called) : property_name( _called), kind_name( (_kind_name))
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

void CBlockList::push_back(UBlock c_block_value)
{
	lista.push_back( (c_block_value));
}

NoumDefinitions CBlockList::noumDefinitions()
{
	NoumDefinitions nd = noum_nothing();
	for(auto &i : lista)
	{
		nd = join_definitions(nd, i->noumDefinitions());
	}
	return nd;
}

void CBlockAssertion_is::dump(std::string ident)
{
	cout << ident << "Assert: " << endl;

	this->get_obj()->dump(ident + "     ");
	cout << ident << "is_____ " << endl;
	this->get_definition()->dump(ident + "     ");
}





void CBlockMatch::dump(std::string ident)
{
	cout << ident << "Match " << endl;
	{
		this->matchInner->dump(ident + "       ");
	}
}

void CBlockMatchAny::dump(std::string ident)
{
	cout << ident << "Match Any " << endl;

}

void CBlockMatchNamed::dump(std::string ident)
{
	cout << ident << "Match As " << named << endl;
	{
		this->matchInner->dump(ident + "       ");
	}
}

bool CBlockMatchNamed::match()
{ return matchInner->match(); }

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

CBlockActionApply::CBlockActionApply(UBlock   _noum1, UBlock  _noum2): noum1((_noum1)), noum2((_noum2))
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

void CBlockDinamicDispatch::dump(std::string ident)
{
	cout << ident << "DinamicDispatch " << endl;
	{
		this->input->dump(ident + "       ");
	}
}

void CBlockStaticDispatch::dump(std::string ident)
{
	cout << ident << "StaticDispatch Entry:  " << this->staticEntryTable << endl;
	{

		cout << ident << "Args: " << endl;
		this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
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


CBlock* CBlockAssertion_canBe::get_obj()
{
	return obj;
}

void CBlockAssertion_canBe::dump(std::string ident)
{
	cout << ident << "Can Be " << endl;
	{
		this->get_obj()->dump(ident + "       ");
		cout << ident << "Values: " << endl;
		this->definition->dump(ident + "       ");

	}
}

 

CBlockAssertion_canBe::CBlockAssertion_canBe(UBlock _obj, CBlockEnums* _definition) :   definition(_definition) , obj(_obj)
{
}

CBlock* CBlockAssertion_isKindOf::get_obj()
{
	return noum;
}

NoumDefinitions CBlockAssertion_isKindOf::noumDefinitions()
{
	return  single_definitions(this->noum->named, this->get_definition() );
}

void CBlockAssertion_isKindOf::dump(std::string ident)
{
	cout << ident << "is Kind Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

CBlock* CBlockAssertion_isKindOf::get_definition()
{ return baseKind ; }

CBlock* CBlockAssertion_isInstanceOf::get_obj()
{
	return noum;
}

CBlock* CBlockAssertion_isInstanceOf::get_definition()
{
	return baseKind;
}

void CBlockAssertion_isInstanceOf::dump(std::string ident)
{
	cout << ident << "is Instance Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

UBlock CBlockAssertion_isNamedValueOf::get_obj()
{
	return this->noum;
}

UBlock CBlockAssertion_isNamedValueOf::get_definition()
{
	return this->baseKind ;
}

void CBlockAssertion_isNamedValueOf::dump(std::string ident)
{
	cout << ident << "is Named Value Of " << endl;
	this->noum->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

UBlock CBlockAssertion_isVariable::get_obj()
{
	return variable;
}

UBlock CBlockAssertion_isVariable::get_definition()
{
	return baseKind;
}

void CBlockAssertion_isVariable::dump(std::string ident)
{
	cout << ident << "is Variable Of  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Kind " << endl;
	this->baseKind->dump(ident + "       ");
}

CBlock* CBlockAssertion_isDefaultAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isDefaultAssign::get_definition()
{
	return value;
}

void CBlockAssertion_isDefaultAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Usually " << endl;
	this->value->dump(ident + "       ");
}

CBlock* CBlockAssertion_isConstantAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isConstantAssign::get_definition()
{
	return value;
}

void CBlockAssertion_isConstantAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Always " << endl;
	this->value->dump(ident + "       ");
}

CBlock* CBlockAssertion_isForbiddenAssign::get_obj()
{
	return value;
}

CBlock* CBlockAssertion_isForbiddenAssign::get_definition()
{
	return variable;
}

void CBlockAssertion_isForbiddenAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is Never " << endl;
	this->value->dump(ident + "       ");
}

UBlock CBlockAssertion_isDirectAssign::get_obj()
{
	return variable;
}

UBlock CBlockAssertion_isDirectAssign::get_definition()
{
	return value;
}

void CBlockAssertion_isDirectAssign::dump(std::string ident)
{
	cout << ident << "Assign  " << endl;
	this->variable->dump(ident + "       ");
	cout << ident << "Is " << endl;
	this->value->dump(ident + "       ");
}

CBlock* CBlockAssertion_isNotDirectAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isNotDirectAssign::get_definition()
{
	return value;
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

void CBlockUnderstandStatic::dump(std::string ident)
{
	cout << ident << "Understand Static " << endl;
	this->argument_match->dump(ident + "       ");
	cout << ident << "As " << endl;
	this->output_n->dump(ident + "       ");
}
