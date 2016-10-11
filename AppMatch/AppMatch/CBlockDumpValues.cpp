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
#include "sharedCast.hpp"


using namespace std;

void CUnresolved::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "UNRESOLVED: ", this->contents.c_str());
}

void CBlockNoum::dump(string ident) {
	printf("%s %s\n", ident.c_str(), this->named.c_str());
}



void CBlockEnums::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Enum:");
		for (auto e = values.begin(); e != values.end(); ++e) {
			(*e)->dump(ident + "   ");
		}
}

void CBlockKindOfName::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Named :  ", baseClasseName.c_str());
}

void CBlockKindOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Kind Of:  ");
		baseClasse->dump(ident + "   ");
}



void CBlockArgumentInput::dump(string ident)
{
	printf("%s  Argument Named : %s\n",ident.c_str() ,   named.c_str());
		kind->dump(ident + "   ");
}

void CBlockSimetricRelation::dump(string ident)
{
	printf("%s S Relation  : %s\n",ident.c_str() ,   named.c_str());
		input_A->dump(ident + "   ");
		printf("%s %s\n", ident.c_str() , "To    "  );
	input_B->dump(ident + "   ");

}

void CBlockASimetricRelation::dump(string ident)
{
	printf("%s A Relation  : %s\n",ident.c_str() ,    named.c_str());
		input_A->dump(ident + "   ");
		printf("%s %s\n", ident.c_str(), "To    ");
		input_B->dump(ident + "   ");
}

void CBlockKindAction::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Action applying to:  ", baseClasseName.c_str());
		this->applyTo->dump(ident + "   ");
}



void CBlockKindValue::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Value: ", named.c_str());
}

void CBlockKindThing::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Kind Thing : ", named.c_str());
}

void CBlockListOfKind::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "List Of:  ");
		itemKind->dump(ident + "   ");
}



void CBlockNamedValue::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Named Value: ", named.c_str());
}

void CBlockVariable::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Variable: ", named.c_str());
}

void CBlockProperty::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Property:");
		prop->dump(ident + "          ");
		printf("%s %s\n", ident.c_str(), "      of:");
		obj->dump(ident + "          ");
}

void CBlockInstanceVariable::dump(string ident) {

	printf("%s %s\n", ident.c_str(), "Property:");
		kind_name->dump(ident + "          ");
		printf("%s %s\n", ident.c_str(), "   called:");
		property_name->dump(ident + "          ");
}

void CBlockKind_InstanceVariable::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Kind Named Variable: ");
		kind->dump(ident + "          ");
		printf("%s %s\n",ident.c_str() , "   has  an:");
		variableNamed->dump(ident + "          ");
}

 

void CBlockList::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "List: ");
		for (auto e = lista.begin(); e != lista.end(); ++e) {
			(*e)->dump(ident + "   ");
		}
}

void CBlockList_OR::dump(string ident) {
	printf("%s %s\n",ident.c_str() , "List OR: ");
		for (auto e = lista.begin(); e != lista.end(); ++e) {
			(*e)->dump(ident + "   ");
		}
}

void CBlockAssertion_is::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assert: ");

		this->get_obj()->dump(ident + "     ");
		printf("%s %s\n", ident.c_str(), "is_____ ");
		this->get_definition()->dump(ident + "     ");
}



void CBlockMatchAny::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match Any ");

}

void CBlockMatchNamed::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Match As ", named.c_str());
	{
		this->matchInner->dump(ident + "       ");
	}
}

void CBlockMatchNoum::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Noum ");
	{
		this->inner->dump(ident + "       ");
	}
}

void CBlockMatchKind::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match Kind: ");
	{
		this->kind->dump(ident + "       ");
	}
}

void CBlockMatchList::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Match List [");
	{
		for (auto i : matchList) {
			i->dump(ident + "       ");
		}
	}
	printf("%s %s\n", ident.c_str(), "          ]");
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
}

void CBlockMatchBlock::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Block: ");
	{
		this->inner->dump(ident + "       ");
	}
}


void CBlockMatchDirectIs::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Is: ");
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
}

void CBlockMatchDirectIsNot::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Match Is Not: ");
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
}

void CBlockMatchIsVerb::dump(string ident)
{
	printf("%s Match verb: %s\n",ident.c_str() ,  verb.c_str() );
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
}

void CBlockMatchIsNotVerb::dump(string ident)
{
	printf("%s Match Not verb: %s\n", ident.c_str(),  verb.c_str());
	{
		this->obj->dump(ident + "       ");
		this->value->dump(ident + "       ");
	}
}

void CBlockMatchProperty::dump(string ident)
{
	printf("%s %s\n" , ident.c_str() , "Match property: "   );
	{
		this->prop->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "OF ");
			this->obj->dump(ident + "       ");

	}

}

void CBlockActionApply::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Action applyTo ");
	{
		this->noum1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "With ");
			this->noum2->dump(ident + "       ");

	}
}

void CBlockAction::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Action ", this->named.c_str());


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
}

void CBlockToDecideIf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Define ");
	{

		this->queryToMatch->dump(ident + "       ");

		printf("%s %s\n", ident.c_str(), "IF ");
			this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideWhat::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "To   What ");
	{
		this->queryToMatch->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "Decide for ");
			this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideWhat_FirstNoum::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "To  What N1 ");
	{
		this->queryToMatch->dump(ident + "       ");
		printf("%s %s\n",ident.c_str() , "Decide for ");
			this->decideBody->dump(ident + "       ");
	}
}

void CBlockToDecideOn::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "DecideOn ");
	{
		this->decideBody->dump(ident + "       ");
	}
}

void CBlockBooleanAND::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Boolean ");
	{
		this->input_A->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "AND ");
			this->input_B->dump(ident + "       ");
	}

}

void CBlockBooleanOR::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Boolean NOT");
	{
		this->input_A->dump(ident + "       ");
	}
}

void CBlockBooleanNOT::dump(string ident) {
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
}

void CBlockAssertion_isActionOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Action ");
}

void CBlockDinamicDispatch::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "DinamicDispatch ");
	{
		this->commandList->dump(ident + "       ");
	}
}

void CBlockStaticDispatch::dump(string ident) {
	printf("%s %s %i \n", ident.c_str(), "StaticDispatch Entry:  ", this->staticEntryTable  );
	{

		printf("%s %s\n", ident.c_str(), "Args: ");
			this->noum1->dump(ident + "       ");
		this->noum2->dump(ident + "       ");

	}
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

void CBlockAction::set_property(string pnamed, HBlock value)
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
}

void CBlockAssertion_isKindOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Kind Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isInstanceOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Instance Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isNamedValueOf::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Named Value Of ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isVariable::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "is Variable Of  ");
		this->variable->dump(ident + "       ");
	printf("%s %s\n", ident.c_str(), "Kind ");
		this->baseKind->dump(ident + "       ");
}

void CBlockAssertion_isDefaultAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Usually ");
		this->value->dump(ident + "       ");
}

void CBlockAssertion_isConstantAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Always ");
		this->value->dump(ident + "       ");
}

void CBlockAssertion_isForbiddenAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is Never ");
		this->value->dump(ident + "       ");
}

void CBlockAssertion_isDirectAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is ");
		this->value->dump(ident + "       ");
}

void CBlockAssertion_isNotDirectAssign::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Assign  ");
		this->variable->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Is NOT");
		this->value->dump(ident + "       ");
}

void CBlockAssertion_InstanceVariable::dump(string ident) {
	printf("%s %s\n", ident.c_str(), "Instance  ");
		this->noum->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "Has ");
		this->instance_variable->dump(ident + "       ");

}

void CBlockIsVerb::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Is     ", verb.c_str());
		this->n1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "related ");
		this->n2->dump(ident + "       ");
}

void CBlockIsNotVerb::dump(string ident) {
	printf("%s %s %s\n", ident.c_str(), "Is  NOT ", verb.c_str());
		this->n1->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "related ");
		this->n2->dump(ident + "       ");
}

void CBlockVerbRelation::dump(string ident) {
	printf("%s %s\n",ident.c_str() , "Verb  ");
		this->verbNoum->dump(ident + "       ");
	printf("%s %s\n",ident.c_str() , "Implies ");
		this->relationNoum->dump(ident + "       ");
}

void CVariableNamed::dump(string ident)
{
	printf("%s VAriable Named  %s\n",ident.c_str() ,   name->named.c_str());
		this->kind->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "values ");
		this->value->dump(ident + "       ");
}

string HtoString(HBlockList lst)
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

string HtoString(HBlock value)
{
	if (HBlockNoum verbNoum = asHBlockNoum(value)) {
		return verbNoum->named;
	}
	else if (HBlockList verbNoumList = asHBlockList(value))
	{
		return HtoString(verbNoumList);
	}
	else if (HBlockProperty pNoumList = asHBlockProperty(value))
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

}

void CBlockUnderstandStatic::dump(string ident) {
	printf("%s %s %i \n", ident.c_str(), "Understand Static ", entryID);
		this->argument_match->dump(ident + "       ");
		printf("%s %s\n", ident.c_str(), "As ");
		this->output_n->dump(ident + "       ");
}

void CBlockUnderstandDynamic::dump(string ident)
{
	printf("%s %s\n" , ident.c_str(), "Understand Dynamic "  );
	this->input_n->dump(ident + "       ");
	this->argument_n->dump(ident + "       ");
	printf("%s %s\n",ident.c_str() , "As ");
		this->output_n->dump(ident + "       ");
}

void CBlockVerb::dump(string ident)
{
	printf("%s verb %s\n",ident.c_str() ,   named.c_str());
}


void CBlockSelector_All::dump(string ident)
{
	printf("%s %s\n" , ident.c_str(), "Select All "   );
	this->what->dump(ident + "       ");
}


void CBlockSelector_Any::dump(string ident)
{
	printf("%s %s\n", ident.c_str(), "Select Any ");
		this->what->dump(ident + "       ");
}

 

void CRunLocalScope::dump(string ident)
{
	printf("%s %s\n",ident.c_str() , "Local Scope ");
		for (auto &kv : locals)
		{
			printf("%s    %s\n",ident.c_str() ,  kv.first.c_str());
				kv.second->dump(ident + "       ");
		}
}

std::shared_ptr<CRunLocalScope> CRunLocalScope::Union(std::shared_ptr<CRunLocalScope> other)
{
	auto localsNext = std::make_shared< CRunLocalScope >();
	for (auto &e : this->locals)
	{
		localsNext->locals.push_back(e);
	}

	for (auto &e : other->locals)
	{
		localsNext->locals.push_back(e);
	}

	return localsNext;
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
}


void CBlockRelationInstance::dump(string ident)
{
	printf("%s %s %s\n", ident.c_str(), "Relation Instance of ", this->relation->named.c_str());
	{
		this->value1->dump(ident + "       ");
		this->value2->dump(ident + "       ");
	}
}

void CBlockNow::dump(string ident) {
	printf("%s %s\n" , ident.c_str(), "Now "  );
	{
		this->assertation->dump(ident + "       ");
	}

}