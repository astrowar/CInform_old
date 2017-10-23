#include "CBlockMatch.hpp"
#include "CBlockMatch.hpp"
// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Eraldo Rangel on 18/08/16.
//



#include "BlockInterpreter.hpp"
#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"

#include "CBlockDumpValues.hpp"
#include "CBlockUndestand.hpp"


 
#include "CBlockRelation.hpp"
#include "CBlockScope.hpp"
#include "CBlockCommand.hpp"
#include "CBlockControlFlux.hpp"

#include "sharedCast.hpp"
#include "CBlockNumber.hpp"
#include "CBlockCompostion.hpp"

#include <cassert>

using namespace std;
using namespace CBlocking;


void  CBlockInstance::dump_contents(string ident) 
{
	printf("%s %s %s\n", ident.c_str(), "Instance: ", named.c_str());
	auto nn = this;
	{
		for (auto &va : nn->anomimousSlots) {

			if (HVariableSlotEnum venum = DynamicCasting::asHVariableSlotEnum(va)) {

				venum->valueDefinition->dump(ident + "    ");
				venum->value->dump(ident + "    ");

			}
			if (HVariableSlotBool vbool = DynamicCasting::asHVariableSlotBool(va)) {

				vbool->valueDefinition->dump(ident + "    ");				
				printf("%s         bool: %i\n", ident.c_str(), vbool->value);
				
			}
		}
	}
	CBlock::dump(ident);

}


void  CBlockInstance::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Instance: ", named.c_str()); 
	CBlock::dump(ident);
}


void CUnresolved::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "UNRESOLVED: ", this->contents.c_str());
	CBlock::dump(ident);
}

void CBlockNoum::dump(string ident) {
	printf("%s %s\n", ident.c_str(), this->named.c_str());
	CBlock::dump(ident);
}



void CBlockEnums::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Enum:");
		for (auto e = values.begin(); e != values.end(); ++e) {
			(*e)->dump(ident + "   ");
		}
		CBlock::dump(ident);
}


 
void CBlockNothing::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Nothing"); 
	CBlock::dump(ident);
}


void CBlockKindOfName::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Named :  ", baseClasseName.c_str());
	CBlock::dump(ident);
}

void CBlockKindOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Kind Of:  ");
		baseClasse->dump(ident + "   ");
		CBlock::dump(ident);
}



void CBlockArgumentInput::dump(string ident)
{
	printf("%s  Argument Named : %s\n",ident.c_str() ,   named.c_str());
		kind->dump(ident + "   ");
		CBlock::dump(ident);
}

void CBlockSimetricRelation::dump(string ident)
{
	printf("%s S Relation  : %s\n",ident.c_str() ,   named.c_str());
		input_A->dump(ident + "   ");
		printf("%s %s\n", ident.c_str() , "To    "  );
	input_B->dump(ident + "   ");
	CBlock::dump(ident);

}

void CBlockASimetricRelation::dump(string ident)
{
	printf("%s A Relation  : %s\n",ident.c_str() ,    named.c_str());
		input_A->dump(ident + "   ");
		printf("%s %s\n", ident.c_str(), "To    ");
		input_B->dump(ident + "   ");
		CBlock::dump(ident);
}

void CBlockKindAction::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Action applying to:  ", baseClasseName.c_str());
		this->applyTo->dump(ident + "   ");
		CBlock::dump(ident);
}



void CBlockKindValue::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Value: ", named.c_str());
	CBlock::dump(ident);
}

void CBlockKindThing::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Thing : ", named.c_str());
	CBlock::dump(ident);
}

void CBlockListOfKind::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "List Of:  ");
		itemKind->dump(ident + "   ");
		CBlock::dump(ident);
}



void CBlockNamedValue::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Named Value: ", named.c_str());
	CBlock::dump(ident);
}

void CBlockVariable::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Variable: ", named.c_str());
	CBlock::dump(ident);
}

void CBlockProperty::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Property:");
		prop->dump(ident + "          ");
		printf("%s %s\n", ident.c_str(), "      of:");
		obj->dump(ident + "          ");
		CBlock::dump(ident);
}

void CBlockInstanceVariable::dump(string ident) {

	printf("%s %s\n", ident.c_str(), "Property:");
		kind_name->dump(ident + "          ");
		printf("%s %s\n", ident.c_str(), "   called:");
		property_name->dump(ident + "          ");
		CBlock::dump(ident);
}

void CBlockKind_InstanceVariable::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Kind Named Variable: ");
		kind->dump(ident + "          ");
		printf("%s %s\n",ident.c_str() , "   has  an:");
		variableNamed->dump(ident + "          ");
		CBlock::dump(ident);
}

 

void CBlockList::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "List: ");
		for (auto e = lista.begin(); e != lista.end(); ++e)
        {   if ((*e) == nullptr) printf("%s NULL\n",ident.c_str()  );
            else {
                (*e)->dump(ident + "   ");
            }
		}
		CBlock::dump(ident);
}

void CBlockList_OR::dump(string ident) {
	printf("%s %s\n",ident.c_str() , "List OR: ");
		for (auto e = lista.begin(); e != lista.end(); ++e) {
			(*e)->dump(ident + "   ");
		}
		CBlock::dump(ident);
}

void CBlockList_AND::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "List AND: ");
	for (auto e = lista.begin(); e != lista.end(); ++e) {
		(*e)->dump(ident + "   ");
	}
	CBlock::dump(ident);
}

void CBlockAssertion_is::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assert: ");

		this->get_obj()->dump(ident + "     ");
		printf("%s %s\n", ident.c_str(), "is_____ ");
		this->get_definition()->dump(ident + "     ");
		CBlock::dump(ident);
}



void CBlockMatchAny::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match Any ");
	CBlock::dump(ident);
}

void CBlockMatchNamed::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Match As ", named.c_str());
	{
		this->matchInner->dump(ident + "       ");
	}
	CBlock::dump(ident);
}
 

CBlockMatchNamed::CBlockMatchNamed(string _named, HBlockMatch _matchInner) : CBlockMatch(), named(_named),
matchInner(_matchInner)
{
	assert(_named != "not");
	assert(_named != "the");
	assert(strncmp(_named.c_str(), "the", 3) != 0);
	assert(_named[0] != '[');
	assert(_named[0] != '(');

}



void CBlockMatchNoum::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Noum ");
	{
		this->inner->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchKind::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match Kind: ");
	{
		this->kind->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchList::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match List [");
	{
		for (auto i : matchList) {
			i->dump(ident + "       ");
		}
	}
	printf("%s %s\n", ident.c_str(), "          ]");
	CBlock::dump(ident);
}

void CBlockMatchAND::dump(string ident)
{
	printf("%s %s\n",ident.c_str(), "Match AND [");
	{
		for (auto i : matchList) {
			i->dump(ident + "       ");
		}
	}
	printf("%s %s\n",ident.c_str() , "          ]");
	CBlock::dump(ident);
}

void CBlockMatchNOT::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Match NOT [");
	this->input->dump(ident + "       ");
	CBlock::dump(ident);
}

void CBlockMatchOR::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match OR [");
	{
		for (auto i : matchList) {
			i->dump(ident + "       ");
		}
	}
	printf("%s %s\n",ident.c_str() , "          ]");
	CBlock::dump(ident);

}


 

void CBlockMatchActionCall::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Match Action Call : ");
	{
		this->action->dump(ident + "       ");
		if(this->argument1!=nullptr) this->argument1->dump(ident + "       ");
		if (this->argument2 != nullptr) this->argument2->dump(ident + "       ");
	}
	CBlock::dump(ident);
}


void CBlockMatchBlock::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Block: ");
	{
		this->inner->dump(ident + "       ");
	}
	CBlock::dump(ident);
}


void CBlockMatchDirectIs::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Is: ");
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchDirectIsNot::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Is Not: ");
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchIsVerb::dump(string ident)
{
	printf("%s Match verb: %s\n",ident.c_str() ,  verb.c_str() );
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchIsNotVerb::dump(string ident)
{
	printf("%s Match Not verb: %s\n", ident.c_str(),  verb.c_str());
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchProperty::dump(string ident)
{
	printf("%s %s\n" , ident.c_str() , "Match property: "   );
	{
		this->prop->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "OF ");
			this->obj->dump(ident + "       ");

	}

	CBlock::dump(ident);
}

void CBlockMatchWhich::dump(string ident)
{
	this->obj->dump(ident );
	printf("       %s Which: %s\n", ident.c_str(), verb.c_str());
	{		
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockMatchWhichNot::dump(string ident)
{
	this->obj->dump(ident + "       ");
	printf("%s Which Not: %s\n", ident.c_str(), verb.c_str());
	{
		this->value->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockActionApply::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Action applyTo ");
	{
		if (noum1 != nullptr)
		{
			this->noum1->dump(ident + "       ");
			if (this->noum2 != nullptr)
			{
				printf("%s %s\n", ident.c_str(), "With ");
				this->noum2->dump(ident + "       ");
			}
		}

	}
	CBlock::dump(ident);
}

void CBlockAction::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Action ", this->named.c_str());
	for(auto nn: this->namedSlots) nn->dump(ident + "       ");
	CBlock::dump(ident);

}

void CBlockAction::newNamedVariable(HBlockNoum called, HBlockKind kind)
{
	this->namedSlots.push_back(std::make_shared< CVariableNamed>(called, kind, nullptr));
 
}



void CBlockToDecideWhether::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "To Decide Whether (bool)");
	{
		this->queryToMatch->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Decide for ");
			this->decideBody->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockToDecideIf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Define ");
	{

		this->queryToMatch->dump(ident + "       ");

		printf("%s %s\n", ident.c_str(), "IF ");
			this->decideBody->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockToDecideWhat::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "To   What ");
	{
		this->queryToMatch->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "Decide for ");
			this->decideBody->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockToDecideWhat_FirstNoum::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "To  What N1 ");
	{
		this->queryToMatch->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "Decide for ");
			this->decideBody->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockToDecideOn::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "DecideOn ");
	{
		this->decideBody->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockBooleanValue::dump(string ident)
{
	if (state) { printf("%s %s\n", ident.c_str(), "Boolean TRUE"); }
	else { printf("%s %s\n", ident.c_str(), "Boolean FALSE"); }	
	CBlock::dump(ident);
}

void CBlockBooleanAND::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Boolean ");
	{
		this->input_A->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "AND ");
			this->input_B->dump(ident + "       ");
	}

	CBlock::dump(ident);
}

void CBlockBooleanOR::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Boolean OR");
	{
		this->input_A->dump(ident + "       ");
		this->input_B->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockBooleanNOT::dump(string ident) 
{
	printf("%s %s\n", ident.c_str(), "Boolean NOT");
	{
		this->input_A->dump(ident + "       ");
	}
	CBlock::dump(ident);
}


 
void CBlockSelectorAND::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Selector  ");
	{
		this->value1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "AND ");
		this->value2->dump(ident + "       ");
	}

	CBlock::dump(ident);
}


void CBlockActionCall::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Call ");
	{
		this->action->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Args: ");

			if (this->noum1 == nullptr)
			{
				printf("%s %s\n",ident.c_str() , "       Nothing");
			}
			else
			{
				this->noum1->dump(ident + "       ");
			}


		if (this->noum2 == nullptr)
		{
			printf("%s %s\n",ident.c_str() , "       Nothing");
		}
		else
		{
			this->noum2->dump(ident + "       ");
		}

	}
	CBlock::dump(ident);
}

void CBlockAssertion_isActionOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Action ");
	CBlock::dump(ident);
}

void CBlockDinamicDispatch::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "DinamicDispatch ");
	{
		this->commandList->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockStaticDispatch::dump(string ident) {
	printf("%s %s %i \n", ident.c_str(), "StaticDispatch Entry:  ", this->staticEntryTable  );
	{

		printf("%s %s\n", ident.c_str(), "Args: ");
			this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
	CBlock::dump(ident);
}

HVariableNamed CBlockAction::get_property(string pnamed)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{

			return va;
		}
	}
	return nullptr;
 
}

void CBlockAction::set_property(string pnamed, CBlocking::HBlock value)
{
	for (auto &va : this->namedSlots)
	{

		if (va->name->named == pnamed)
		{

			va->value = value;
		}
	}
	return;
	 
}

void CBlockAssertion_canBe::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Can Be ");
	{
		this->get_obj()->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Values: ");
			this->definition->dump(ident + "       ");

	}
	CBlock::dump(ident);
}

void CBlockAssertion_isKindOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Kind Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isInstanceOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Instance Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isNamedValueOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Named Value Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isVariable::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Variable Of  ");
		this->variable->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlocking::CBlockAssertion_isLocalVariable::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "let Variable   ");
	this->variableName->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "Be ");
	this->valueExpression->dump(ident + "       ");
	CBlock::dump(ident);
}


void CBlockAssertion_isDefaultAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Usually ");
		this->value->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isConstantAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Always ");
		this->value->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isForbiddenAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Never ");
		this->value->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isDirectAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is ");
		this->value->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_isNotDirectAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is NOT");
		this->value->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockAssertion_InstanceVariable::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Instance  ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Has ");
		this->instance_variable->dump(ident + "       ");

		CBlock::dump(ident);
}

void CBlockIsVerb::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Is     ", verb.c_str());
		this->n1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "related ");
		this->n2->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockIsNotVerb::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Is  NOT ", verb.c_str());
		this->n1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "related ");
		this->n2->dump(ident + "       ");
		CBlock::dump(ident);
}



 
void CBlockAssert::dump(string ident) {
	printf("%s %s \n", ident.c_str(), "Assert ");
	this->expression->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "Equals ");
	this->result->dump(ident + "       ");
	CBlock::dump(ident);
}



void CBlockVerbDirectRelation::dump(string ident) {
	printf("%s %s\n",ident.c_str() , "Verb  ");
		this->verbNoum->dump(ident + "       ");
	printf("%s %s\n",ident.c_str() , "Implies Direct");
		this->relationNoum->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockVerbReverseRelation::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Verb  ");
	this->verbNoum->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "Implies Reverse");
	this->relationNoum->dump(ident + "       ");
	CBlock::dump(ident);
}

void CVariableNamed::dump(string ident)
{
	printf("%s VAriable Named  %s\n",ident.c_str() ,   name->named.c_str());
		this->kind->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "values ");
		if (this->value != nullptr) { this->value->dump(ident + "       "); }
		else { printf("%s        nullptr\n", ident.c_str()); }
		CBlock::dump(ident);
}

string  CBlocking::HtoStringList(HBlockList lst)
{

	if (lst->lista.empty()) return "";
	if (lst->lista.size() == 1) return HtoString(lst->lista.front());
	std::string vstr = "";
	bool fronti = true;
	for (auto &v : lst->lista)
	{
		if (!fronti) vstr += " ";
		vstr += HtoString(v);
		fronti = false;
	}
	return vstr;
	 
}

string CBlocking::HtoString( HBlock value)
{
	if (HBlockNoum verbNoum = DynamicCasting::asHBlockNoum(value)) {
		return verbNoum->named;
	}
	else if (HBlockList verbNoumList = DynamicCasting::asHBlockList(value))
	{
		return HtoStringList(verbNoumList);
	}
	else if (HBlockProperty pNoumList = DynamicCasting::asHBlockProperty(value))
	{
		return HtoString(pNoumList->prop) + " of " + HtoString(pNoumList->obj);
	}
	return "";
	 
}

void CBlockUnderstand::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Understand  ");
		this->input_n->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "As ");
		this->output_n->dump(ident + "       ");
	CBlock::dump(ident);
}

void CBlockUnderstandStatic::dump(string ident) {
	printf("%s %s %i \n", ident.c_str(), "Understand Static ", entryID);
		this->argument_match->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "As ");
		this->output_n->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockUnderstandDynamic::dump(string ident)
{
	printf("%s %s\n" , ident.c_str(), "Understand Dynamic "  );
	this->input_n->dump(ident + "       ");
	this->argument_n->dump(ident + "       ");
	printf("%s %s\n",ident.c_str() , "As ");
		this->output_n->dump(ident + "       ");
		CBlock::dump(ident);
}

void CBlockVerb::dump(string ident)
{
	printf("%s verb %s\n",ident.c_str() ,   named.c_str());
	for (auto &c : conjugations)
		c->dump(ident + "       ");
	CBlock::dump(ident);
}
void CBlockVerbAdapt::dump(string ident)
{
	printf("%s verb adapt for (%s)  in (%s) to (%s)\n", ident.c_str(), verb.c_str() , tense.c_str() , viewPoint.c_str());
	CBlock::dump(ident);
}


void CBlockVerbConjugation::dump(string ident)
{
	printf("%s vb conjg ( %6s )  :  %s \n", ident.c_str(), tense.c_str(),    word.c_str()  );
	CBlock::dump(ident);
}

void CBlockSelector_All::dump(string ident)
{
	printf("%s %s\n" , ident.c_str(), "Select All "   );
	this->what->dump(ident + "       ");
	CBlock::dump(ident);
}


void CBlockSelector_Any::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Select Any ");
		this->what->dump(ident + "       ");
		CBlock::dump(ident);
}

 

void CRunLocalScope::dump(string ident)
{
	if (this->previous != nullptr) this->previous->dump("");
	printf("%s %s\n",ident.c_str() , "Local Scope ");
		for (auto &kv : locals)
		{
			printf("%s    %s\n",ident.c_str() ,  kv.first.c_str());
				kv.second->dump(ident + "       ");
		}
		 
}

//std::shared_ptr<CRunLocalScope> CRunLocalScope::Union(std::shared_ptr<CRunLocalScope> other)
//{
//	auto localsNext = std::make_shared< CRunLocalScope >();
//	for (auto &e : this->locals)
//	{
//		localsNext->locals.push_back(e);
//	}
//
//	for (auto &e : other->locals)
//	{
//		localsNext->locals.push_back(e);
//	}
//
//	return localsNext;
//}

HRunLocalScope copy_CRunLocalScope(HRunLocalScope _inn)
{
	HRunLocalScope ret = std::make_shared< CRunLocalScope > (nullptr);

	ret->previous = _inn->previous;
	for(auto it : _inn->locals )
	{
		ret->locals.push_back(it);
	}
	return ret;

}

void CExecutionBlock::dump(string ident) const
{
	printf("%s %s\n", ident.c_str(), "ExecutionBlock "); 
	{

		locals->dump(ident + "       ");
		block->dump(ident + "       ");

	}
 
}


void CBlockText::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Text:  ", contents.c_str());
	CBlock::dump(ident);
}


void CBlockRelationInstance::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Relation Instance of ", this->relation->named.c_str());
	{
		this->value1->dump(ident + "       ");
		this->value2->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockConditionalRelation::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Relation Coditional ", this->relation->named.c_str());	
		this->relation->dump(ident + "       ");
	printf("%s When \n", ident.c_str());
		this->coditional->dump(ident + "       ");
	
		CBlock::dump(ident);
}

void CBlockRelationLookup::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Relation LookUp  By", this->relation.c_str() );
	{
		this->value1->dump(ident + "       ");
		this->value2->dump(ident + "       ");

	}
	CBlock::dump(ident);
}

void CBlockVerbLookup::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Verb LookUp  By", this->verb.c_str());
	{
		this->value1->dump(ident + "       ");
		this->value2->dump(ident + "       ");

	}
	CBlock::dump(ident);
}

 
void CBlockRelationArguments::dump(string ident)
{
	printf("%s %s \n", ident.c_str(), "Relation Argument");
	{
		this->value1->dump(ident + "       ");
	printf("%s To \n", ident.c_str());
		this->value2->dump(ident + "       ");

	}
	CBlock::dump(ident);
}
 

void CBlockNow::dump(string ident) {
	printf("%s %s\n" , ident.c_str(), "Now "  );
	{
		this->assertation->dump(ident + "       ");
	}
	CBlock::dump(ident);
}
 
void CBlockEvery::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Every ");
	{
		this->assertation->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

void CBlockControlToken::dump(string ident)
{
	printf("%s %s  %s\n", ident.c_str(), "Token " , this->token.c_str());
	{
		if (contents != nullptr)
		   this->contents->dump(ident + "       ");
	}
	CBlock::dump(ident);
}



void CBlockCompostionPhrase::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Phrase Kind  ");
	
	CBlock::dump(ident);
}


void CBlockControlIF::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "IF  " );
	{
		  this->block_if->dump(ident + "       ");
		  printf("%s %s\n", ident.c_str(), "THEN  ");
		  this->block_then->dump(ident + "       ");

		  if (this->block_else != nullptr)
		  {
			  printf("%s %s\n", ident.c_str(), "ELSE  ");
			  this->block_else->dump(ident + "       ");
		  }
		
	}
	CBlock::dump(ident);
}


void CBlockControlUnless::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "UNLESS  ");
	{
		this->block_if->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "THEN  ");
		this->block_then->dump(ident + "       ");

		if (this->block_else != nullptr)
		{
			printf("%s %s\n", ident.c_str(), "ELSE  ");
			this->block_else->dump(ident + "       ");
		}

	}
	CBlock::dump(ident);
}

void CBlockControlSelect::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "SELECT  ");
	{
		this->block_seletor->dump(ident + "       ");
		for (auto &e : this->block_selectList)
		{
			e->dump(ident + "       ");
		}

		if (this->block_else != nullptr)
		{
			printf("%s %s\n", ident.c_str(), "ELSE  ");
			this->block_else->dump(ident + "       ");
		}
	}
	CBlock::dump(ident);
}

void CBlockControlForEach::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "FOR EACH  ");
	this->block_variable->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "LOOP  ");
	this->block_body->dump(ident + "       ");
	CBlock::dump(ident);
}


void CBlockExecutionResultFlag::dump(string ident)
{

	if (this->flag == actionContinue) printf("%s %s\n", ident.c_str(), "ResultFlag Action Continue");
	if (this->flag == actionStop) printf("%s %s\n", ident.c_str(), "ResultFlag Action Stop");
	if (this->flag == ruleSucess) printf("%s %s\n", ident.c_str(), "ResultFlag Rule Sucess");
	if (this->flag == ruleFail) printf("%s %s\n", ident.c_str(), "ResultFlag Rule Fail");
  
	if (this->contents)
	{
		this->contents->dump(ident + "       ");
	}
	CBlock::dump(ident);
}

 
void CBlockControlSelectItem::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "SELECT ITEM  ");
	{
		this->block_seletor->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "BODY  ");
		this->block_execute->dump(ident + "       "); 
	}
	CBlock::dump(ident);
}



void CBlockComandList::dump(string ident)
{
	if (lista.size() ==1 )
	{
		lista.front()->dump(ident);
	}
	else
	{
		printf("%s %s\n", ident.c_str(), "CommandList  ");
		for (auto &kv : lista)
		{
			kv->dump(ident + "       ");
			printf("\n");
		}
	}
	CBlock::dump(ident);
}

 
void CBlockEventHandle::dump(string ident)
{
	if (this->stage == StageInstead) printf("%s %s\n", ident.c_str(), "Event Instead Handle ");
	if (this->stage == StageCheck) printf("%s %s\n", ident.c_str(), "Event Check  Handle ");
	if (this->stage == StageBefore) printf("%s %s\n", ident.c_str(), "Event Before Handle ");	
	if (this->stage == StageCarryOut ) printf("%s %s\n", ident.c_str(), "Event Carry Out  Handle ");
	if (this->stage == StageAfter) printf("%s %s\n", ident.c_str(), "Event After  Handle ");
	if (this->stage == StageReport) printf("%s %s\n", ident.c_str(), "Event Report Handle ");


	
	this->eventToObserve->dump(ident + "       ");
	this->body->dump(ident + "       ");
	CBlock::dump(ident);
}

void CBlockSelector_Where::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Seletor WHERE  ");
	{
		this->what->dump(ident + "       ");		
	}
	CBlock::dump(ident);
}


void   CBlockIntegerNumber::dump(string ident)
{
	printf("%s %s %i\n", ident.c_str(), "Number " , value );
	CBlock::dump(ident);
}

void   CBlockFactionalNumber::dump(string ident)
{
	printf("%s %s %8.3f\n", ident.c_str(), "Number ", value);
	CBlock::dump(ident);
}