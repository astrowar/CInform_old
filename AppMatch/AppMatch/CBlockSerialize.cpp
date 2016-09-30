#include "BlockInterpreter.h"
#include "CBlockUndestand.h"
#include "CDataMananger.h"
#include "CBlockDumpValues.h"

void CBlockKind_InstanceVariable::store(CDataManangerSave* mng)
{
	
	mng->type(this->type() , this->kind, this->variableNamed);
}

void CUnresolved::store(CDataManangerSave* m)
{
	m->type(this->type(), this->contents); 
}
void CBlockKind::store(CDataManangerSave* m)
{
	m->type(this->type(), this->named);
}

void CBlockNoum::store(CDataManangerSave* m)
{
	m->type(this->type(),named);
	

}

void CBlockKindOf::store(CDataManangerSave* m)
{
	m->type(this->type(), baseClasse);
	

}

void CBlockKindAction::store(CDataManangerSave* m)
{
	m->type(this->type(), baseClasseName, applyTo);
 
	
}

void CBlockKindValue::store(CDataManangerSave* m)
{
	m->type(this->type(),named);
 
}


void CBlockKindThing::store(CDataManangerSave* m)
{
	m->type(this->type(),named);
	
}
 

void CBlockListOfKind::store(CDataManangerSave* m)
{
	m->type(this->type(), itemKind);	
}



void CBlockNamedValue::store(CDataManangerSave* m)
{
	m->type(this->type(), named );
	
}

void CBlockVariable::store(CDataManangerSave* m)
{
	m->type(this->type(),named);
	
}

void CBlockProperty::store(CDataManangerSave* m)
{
	m->type(this->type(), prop, obj);
	
}

void CBlockInstanceVariable::store(CDataManangerSave* m)
{
	m->type(this->type(),property_name , kind_name);

	 
}

void CBlockList::store(CDataManangerSave* m)
{
	m->type(this->type() , lista); 
}


void CBlockEnums::store(CDataManangerSave* m)
{
	m->type(this->type(), std::vector<HBlock>(values.begin(), values.end()));
}




void CBlockAssertion_InstanceVariable::store(CDataManangerSave* m)
{
	m->type(this->type(), this->noum, this->instance_variable);
}


void CBlockVerbRelation::store(CDataManangerSave* m)
{
	m->type(this->type(), verbNoum, this->relationNoum );
}


void CBlockDinamicDispatch::store(CDataManangerSave* m)
{
	m->type(this->type(), this->commandList );
}

void CBlockActionApply::store(CDataManangerSave* m)
{
	m->type(this->type(), this->noum1, this->noum2);
}



void CBlockVerb::store(CDataManangerSave* m)
{
	m->type(this->type(), this->named);
}

void CBlockSelector_All::store(CDataManangerSave* m)
{
	m->type(this->type(), this->what);
}


void CBlockSelector_Any::store(CDataManangerSave* m)
{
	m->type(this->type(), this->what);
}


//=======================================


void CBlockAssertion_isDirectAssign::store(CDataManangerSave* m)
{
	m->type(this->type(), this->variable  , this->value);
}

void CBlockIsVerb::store(CDataManangerSave* m)
{
	m->type(this->type(), this->verb, this->n1 , this->n2);
}

