#pragma once
#ifndef _CFENV_H
#define _CFENV_H
#include <string>
#include <list>
#include <memory>
#include "EqualsResult.h"


 // Classes  abstradas .. que servem como protocolos
class CGenericKind abstract
{
public:
	virtual ~CGenericKind()
	{
	}

	virtual void some() {};

 };

using HGenericKind = std::shared_ptr<CGenericKind>;

class CGenericValue abstract
{
public:
	virtual ~CGenericValue()
	{
	}

	virtual void some() {};
}; 
using HGenericValue = std::shared_ptr<CGenericValue>;



//Classes concretas

class CObjectKind;
using HObjectKind = std::shared_ptr<CObjectKind>;


class CObjectKind: public  CGenericKind
{	 
public:
	HObjectKind previous;
	std::string name;
	CObjectKind(std::string named, HObjectKind prev);
};

using HObjectKind = std::shared_ptr<CObjectKind>;

class CObjectInstance: public  CGenericValue
{
public:
	CObjectInstance(HObjectKind kind, const std::string& name)
		: kind(kind),
		  name(name)
	{
	}

	HObjectKind kind;
	std::string name;
};

using HInstance = std::shared_ptr<CObjectInstance>;

class CValueKind :public CGenericKind
{
public:
	std::string name;
	CValueKind(std::string _name);

	 
};

using HValueKind = std::shared_ptr<CValueKind>;

class CKindProperty
{
public:
	CKindProperty(const std::string& name, HObjectKind _kind, HValueKind _vkind)
		: name(name),
		  kind(_kind),
		  vkind(_vkind)
	{
	}

	std::string name;
	HObjectKind kind;
	HValueKind vkind;
};

class CInstanceProperty
{
public:
	CInstanceProperty(const std::string& _name, HInstance _inst, HValueKind _vkind)
		: name(_name),
		  inst(_inst),
		  vkind(_vkind)
	{
		if (_vkind == nullptr)
		{
			throw "unable";
		}
	}

	std::string name;
	HInstance inst;
	HValueKind vkind;
};

using HInstanceProperty = std::shared_ptr<CInstanceProperty>;


class CValue;
using  HValue = std::shared_ptr<CValue>;
class CValue : public CGenericValue
{
public:
	CValue(HValueKind vkind)
		: vkind(vkind)
	{
	} 
	HValueKind vkind;
	virtual HValue  clone() =0;
};

 

class CVariable
{
public:
	CVariable(const std::string& name, HGenericKind  _vkind);
	HGenericKind vkind;
	HGenericValue value;
	std::string name;
};

using HVariable = std::shared_ptr<CVariable>;

class CValueKindEnum : public CValueKind
{
public:
	CValueKindEnum(const std::string& _name, HValueKind _valuesKind, const std::list<HValue>& posiblesValues)
		: CValueKind(_name),
		  values(posiblesValues),
		  valuesKind(_valuesKind)
	{
	}

	std::list<HValue> values;
	HValueKind valuesKind;
};

extern HValueKind HValueKindBoolean;
extern HValueKind HValueKindString;
extern HValueKind HValueKindText;
extern HValueKind HValueKindList;
extern HValueKind HValueKindNumber;

extern HValueKind HValueKindObjectInstance;
extern HValueKind HValueKindObjectKind;


class CValueBoolean : public CValue
{
public:
	HValue clone() override;

	CValueBoolean(bool v)
		: CValue(HValueKindBoolean),
		  val(v)
	{
	}

	bool val;
};

class CValueText : public CValue
{
public:
	HValue clone() override;

	CValueText(const std::string& cs)
		: CValue(HValueKindText),
		  _text(cs)
	{
	}

	std::string _text;
};

class CValueString : public CValue
{
public:
	HValue clone() override;

	CValueString(const std::string& cs)
		: CValue(HValueKindString),
		  _text(cs)
	{
	}

	std::string _text;
};

class CValueList : public CValue
{
public:
	HValue clone() override;

	CValueList(  std::list<HGenericValue>  c_values)
		: CValue(HValueKindList),
		  values(c_values)
	{
	}

	std::list<HGenericValue> values;
};


 



class CValueNumber : public CValue
{
public:
	HValue clone() override;

	CValueNumber(int c_value)
		: CValue(HValueKindNumber),
		  value(c_value)
	{
	}

	int value;
};


#ifdef oldCode 
class CValueObjectInstance : public CValue //um  HInstancia 
{
public:
	HValue clone() override;

	CValueObjectInstance(HInstance c_value)
		: CValue(HValueKindObjectInstance ),
		value(c_value)
	{
	}

	HInstance value;
};

using HValueObjectInstance = std::shared_ptr<CValueObjectInstance>;

class CValueObjectKind : public CValue //um  HObjectKind
{
public:
	HValue clone() override;
    
    CValueObjectKind(HObjectKind c_value)
    : CValue(HValueKindObjectKind ),
    value(c_value)
    {
    }
    
    HObjectKind value;
};

using HValueObjectKind = std::shared_ptr<CValueObjectKind>;
#endif


class CValueInstance : public CValue // Value instance eh o valor dos HValueKind customizados
{
public:
	HValue clone() override;
	CValueInstance(const std::string& _named, HValueKind vkind);
	std::string named;
};

using HValueInstance = std::shared_ptr<CValueInstance>;

//========================================
class AssertConstraint
{
public:
	AssertConstraint(float lk)
		: LK(lk)
	{
	}

	float LK;
};

class HValueAssert //class que define os parametros de contorno de um dado valor em um Kind
{
public:
	HValueAssert(const HValue& c_value, float constraint);
	HValue value;
	AssertConstraint constraint;
};

HValueAssert Usually_Value(const HValue& c_value);
HValueAssert Always_Value(const HValue& c_value);
bool can_set_value(HValueKind vkind, HValue val);

class CKindPropertyAssert
{
public:
	CKindPropertyAssert(CKindProperty property, HValueAssert value)
		: property(property),
		  valueAssertion(value)
	{
	}

	CKindProperty property;
	HValueAssert valueAssertion;
};

class CInstancePropertyAssert
{
public:
	CInstancePropertyAssert(CInstanceProperty property, HValue value)
		: property(property),
		  value(value)
	{
	}

	CInstanceProperty property;
	HValue value;
};

//Complex thing RELATIONS
class CRelationDescriptionNode
{
public:
	CRelationDescriptionNode(std::string _named, HGenericKind _kind);
	virtual ~CRelationDescriptionNode(){}
	virtual bool isMany() { return false; };
	virtual bool isGroup() { return false; };
	std::string named;
	HGenericKind vkind;
};

using HRelationDescriptionNode = std::shared_ptr<CRelationDescriptionNode>;

class CRelationDescriptionNodeGroup : public CRelationDescriptionNode
{
public:
	CRelationDescriptionNodeGroup(std::string _named, HGenericKind _kind);
	virtual bool isMany() override { return false; };
	virtual bool isGroup() override { return true ; }
};

class CRelationDescriptionNodeMany : public CRelationDescriptionNode
{
public:
	CRelationDescriptionNodeMany(std::string _named, HGenericKind _kind);
	virtual bool isMany() override  { return true ; } ;
    virtual bool isGroup() override  {	return false;}
};


// Relations per Se

class CRelationDescription
{
public:
	CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode _node2, bool _symmetric = false);
	HRelationDescriptionNode node1, node2;
	std::string named;
	bool symmetric;
};

class CRelationInstance
{
public:
	CRelationInstance(CRelationDescription* _relDesc, HGenericValue  val, HGenericValue val2);
	CRelationDescription* relDesc;
	HGenericValue item1;
	HGenericValue item2;
};

//=====================================
//No env , tudo eh HANDLE 
class FEnviromentBase;

class FEnviroment
{
public:
	FEnviroment();
	virtual FEnviroment* copy() = 0;
	virtual ~FEnviroment();
	virtual void addKind(HObjectKind _k) = 0;
	virtual void addInstance(HInstance _k) = 0;
	virtual void addVariable(HVariable _k) = 0;
	virtual FEnviromentBase* getBase() = 0;

	virtual void dump_relations()   ;
};

class FEnviromentBase :public FEnviroment
{
public:
	void addKind(HObjectKind _k) override;
	void addInstance(HInstance _k) override;
	void addVariable(HVariable _k) override;
	FEnviromentBase();
	virtual FEnviroment* copy() override;
	virtual FEnviromentBase* getBase() override;
	//Listas 
	std::list<HInstance> instances;
	std::list<HObjectKind> kinds;
	std::list<HValueInstance> value_instances;
	std::list<HVariable> variables;
	std::list<CInstanceProperty> instance_properties;
	std::list<CInstancePropertyAssert> instance_properties_values;
	std::list<CKindPropertyAssert> kind_properties_asserts;
	std::list<CRelationDescription> relations_description;
	std::list<CRelationInstance> relation_instances;

	 
};

// um env para as variaveis locais LET
class SubFEnviroment :public FEnviroment
{
public:
	FEnviroment* copy() override;
	void addKind(HObjectKind _k) override;
	void addInstance(HInstance _k) override;
	void addVariable(HVariable _k) override;
	virtual FEnviromentBase* getBase() override;

	 

private:
	SubFEnviroment(FEnviroment* parent)
		: parent(parent)
	{
	}

	FEnviroment* parent;
	std::list<HVariable> variables;
};


bool isInstanceOf(CGenericValue *val, CGenericKind *kind);

EqualsResul isEqual(HValue c1, HValue  c2);

HObjectKind make_kind(FEnviroment* env, std::string name);
HInstance make_instance(FEnviroment* env, std::string name, HObjectKind k);
HObjectKind make_derivade_kind(FEnviroment* env, std::string name, HObjectKind base);
HVariable make_variable(FEnviroment* env, std::string name, HValueKind vkind);
HObjectKind get_kind(FEnviroment* env, std::string name);
HInstance get_instance(FEnviroment* env, std::string name);
void assign_property(FEnviroment* env, CInstanceProperty& prop);
void assign_property(FEnviroment* env, CKindPropertyAssert& prop);
CInstanceProperty* get_property(FEnviroment* env, HInstance obj, std::string name);
HValue get_property_value(FEnviroment* env, CInstanceProperty* c_instance_property);
void set_property_value(FEnviroment* env, CInstanceProperty* c_instance_property, HValue val);
void set_variable_value(FEnviroment* env, HVariable var, HGenericValue c_value);
HGenericValue get_variable_value(FEnviroment* env, HVariable var);
HValue make_string_value(std::string v);
HValue make_text_value(std::string v);
HValue make_bool_value(bool v);
HValue make_number_value(int v);
HValue make_list_value( std::list<HGenericValue> glist);

HGenericValue make_obj_instance_value(HInstance v);
HGenericKind make_obj_kind_value(HObjectKind v);

HValue makeValueInstance(FEnviroment* env, const std::string& _name, HValueKind vkind);
std::string toString(HGenericValue val);
std::string toString(HValue val);
 
HValueKind makeValueKindEnum(FEnviroment* env, std::string _name, HValueKind _valuesKind, std::list<HValue> posiblesValues);
HValueKind makeValueKind(FEnviroment* env, const std::string& _name);


HRelationDescriptionNode make_relation_node(std::string _name, HObjectKind  _vkind);
HRelationDescriptionNode make_relation_node_various(std::string _name, HObjectKind  _vkind);
HRelationDescriptionNode make_relation_node(std::string _name, HValueKind _vkind);
HRelationDescriptionNode make_relation_node_various(std::string _name, HValueKind _vkind);


CRelationDescription* get_relation_description(FEnviroment* env, std::string named);
void add_relation_description(FEnviroment* envb, CRelationDescription rel_description);


void set_relation(FEnviroment* env, CRelationDescription* relation_description, HGenericValue val1, HGenericValue val2);
void unset_relation(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val1, HGenericValue val2);

HGenericValue get_relation_to(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue from_val);
HGenericValue get_relation_from(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue to_val);

 
#endif



