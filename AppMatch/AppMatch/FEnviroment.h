#pragma once

#ifndef _CFENV_H
#define _CFENV_H
#include <string>
#include <list>
#include <memory>


class CKind;
using HKind = std::shared_ptr<CKind>;
class CKind
{
public:
	HKind  previous;
	std::string name;
	CKind(std::string named, HKind prev);

};
using HKind = std::shared_ptr<CKind>;

class CInstance
{

public:
	CInstance(HKind kind, const std::string& name)
		: kind(kind),
		name(name)
	{
	}

	HKind kind;
	std::string name;
};

using HInstance = std::shared_ptr<CInstance>;




class CValueKind
{
public:
	std::string name;
	CValueKind(std::string _name);
	virtual ~CValueKind() {}

	 
};

using HValueKind = std::shared_ptr<CValueKind>;
 



 



class CKindProperty
{
public:
	CKindProperty(const std::string& name, HKind _kind, HValueKind _vkind)
		: name(name),
		kind(_kind),
		vkind(_vkind)
	{
	}

	std::string name;
	HKind kind;
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
		if(_vkind == nullptr)
		{
			throw "unable";
		}
	} 
	std::string name;
	HInstance inst;
	HValueKind vkind;

};
using HInstanceProperty = std::shared_ptr<CInstanceProperty>;
 



class CValue
{
public:
	CValue(HValueKind vkind)
		: vkind(vkind)
	{
	}
	virtual ~CValue() {};
	HValueKind vkind;


	virtual CValue* clone() =0  ;
};
using HValue  = std::shared_ptr<CValue>;
 



class CVariable
{

public:
	CVariable(const std::string& name, HValueKind _vkind);

	HValueKind vkind;
	HValue  value;
	std::string name;
};

using HVariable = std::shared_ptr<CVariable>;



class CValueKindEnum : public CValueKind
{

public:
	CValueKindEnum(const std::string& _name, HValueKind _valuesKind,  const std::list<HValue>& posiblesValues)
		: CValueKind(_name),		 
		values(posiblesValues),
		valuesKind(_valuesKind)
	{
	}
	
	std::list<HValue> values;
	HValueKind valuesKind; 
};

 

extern HValueKind  HValueKindBoolean; 
extern HValueKind  HValueKindString;
extern HValueKind  HValueKindText;
extern HValueKind  HValueKindList;
extern HValueKind  HValueKindNumber;





class CValueBoolean : public CValue
{
public:
	CValue* clone() override;

	CValueBoolean(bool v )
		: CValue(HValueKindBoolean),
		val(v)
	{
	}

	bool  val;

};


class CValueText : public CValue
{
public:
	CValue* clone() override;

	CValueText(  const std::string& cs)
		: CValue(HValueKindText),
		_text(cs)
	{
	}

	std::string _text;

};

class CValueString : public CValue
{
public:
	CValue* clone() override;

	CValueString(  const std::string& cs)
		: CValue(HValueKindString),
		_text(cs)
	{
	}

	std::string _text;

};


class CValueList : public CValue
{
public:
	CValue* clone() override;

	CValueList(  const std::list<CValue*>& c_values)
		: CValue(HValueKindList),
		values(c_values)
	{
	}

	std::list<CValue*> values;
};



class CValueNumber : public CValue
{
public:

	CValue* clone() override;

	CValueNumber(int  c_value)
		: CValue(HValueKindNumber),
		value(c_value)
	{
	}

	int value;
};
 



class CValueInstance : public CValue   // Value instance eh o valor dos HValueKind customizados
{
public:
	CValue* clone() override;
	CValueInstance(const std::string& _named, HValueKind vkind);

	std::string  named;
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



bool can_set_value(HValueKind vkind,  HValue val);

class CKindPropertyAssert
{
	public:
	CKindPropertyAssert(CKindProperty property, HValueAssert  value)
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
	CInstancePropertyAssert(CInstanceProperty property, HValue  value)
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
	CRelationDescriptionNode(std::string _named, HKind _kind);
	std::string named;
	HKind kind;
};

using HRelationDescriptionNode = std::shared_ptr<CRelationDescriptionNode>;

class CRelationDescriptionNodeGroup : public CRelationDescriptionNode
{
public:
	CRelationDescriptionNodeGroup(std::string _named, HKind _kind);
 

};


class CRelationDescriptionNodeMany : public CRelationDescriptionNode
{
public:
	CRelationDescriptionNodeMany(std::string _named,  HKind _kind);


};


 



class CRelationDescription
{
public:
	CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode  _node2 , bool _symmetric = false  );

	HRelationDescriptionNode node1, node2;
	std::string named;
	bool symmetric; 
	 

		
};
 
 


class CRelationInstance
{
public:
	CRelationInstance(CRelationDescription* _relDesc, HInstance val, HInstance val2);
	CRelationDescription* relDesc;
	HInstance item1;
	HInstance item2;
};
 


//=====================================


//No env , tudo eh HANDLE 
class FEnviromentBase;

class FEnviroment
{
public:
	FEnviroment();
	virtual FEnviroment* copy()  = 0;
	virtual ~FEnviroment();
	virtual void addKind(HKind _k) = 0;
	virtual void addInstance(HInstance _k) = 0;
	virtual void addVariable(HVariable _k) = 0;  
	virtual FEnviromentBase* getBase() = 0;
	 
};



class FEnviromentBase :public FEnviroment
{
public:
	void addKind(HKind _k) override;
	void addInstance(HInstance _k) override;
	void addVariable(HVariable _k) override;
	FEnviromentBase();
	virtual FEnviroment* copy()   override;
	virtual FEnviromentBase* getBase() override; 

	//Listas 
	std::list<HInstance> instances;
	std::list<HKind> kinds;


	std::list<HValueInstance> value_instances;
	std::list<HVariable> variables;


	std::list<CInstanceProperty> instance_properties;
	std::list<CInstancePropertyAssert > instance_properties_values;
	std::list<CKindPropertyAssert> kind_properties_asserts;
	std::list<CRelationDescription> relations_description;
	std::list<CRelationInstance> relation_instances;
};

// um env para as variaveis locais LET
class SubFEnviroment :public FEnviroment
{
public:
	FEnviroment* copy() override;

	void addKind(HKind _k) override;

	void addInstance(HInstance _k) override;

	void addVariable(HVariable _k) override;

	virtual FEnviromentBase* getBase() override;

private:
	SubFEnviroment(FEnviroment* parent  )
		: parent(parent)		  
	{
	}


	FEnviroment *parent;
	std::list<HVariable> variables;
};




HKind make_kind(FEnviroment *env, std::string name);
HInstance make_instance(FEnviroment *env, std::string name, HKind k);
HKind make_derivade_kind(FEnviroment* env, std::string name, HKind base);
HVariable  make_variable(FEnviroment *env, std::string name, HValueKind vkind);

HKind get_kind(FEnviroment* env, std::string name);
HInstance get_instance(FEnviroment* env, std::string name);

void  assign_property(FEnviroment* env, CInstanceProperty&  prop);
void  assign_property(FEnviroment* env, CKindPropertyAssert&  prop);

CInstanceProperty*  get_property(FEnviroment* env, HInstance obj , std::string name);


HValue  get_property_value(FEnviroment* env, CInstanceProperty* c_instance_property);
void  set_property_value(FEnviroment* env, CInstanceProperty* c_instance_property , HValue val);


void set_variable_value(FEnviroment* env, HVariable var, HValue c_value);
HValue get_variable_value(FEnviroment* env, HVariable var);

HValue make_string_value(std::string v);
HValue make_text_value(std::string v);
HValue make_bool_value(bool  v);
HValue make_number_value(int  v);

HValue  makeValueInstance(FEnviroment* env, const std::string& _name, HValueKind vkind);


std::string  toString(HValue val);
std::string  toString(CValue* val);

HValueKind  makeValueKindEnum(FEnviroment* env,   std::string  _name, HValueKind _valuesKind,   std::list<HValue>  posiblesValues);
HValueKind makeValueKind(FEnviroment* env, const std::string& _name  );

 

HRelationDescriptionNode make_relation_node(  std::string  _name, HKind _kind);
HRelationDescriptionNode make_relation_node_various(std::string  _name, HKind _kind);




CRelationDescription* get_relation_description(FEnviroment* env, std::string named);


void add_relation_description(FEnviroment* envb, CRelationDescription rel_description);
void add_relation(FEnviroment* env, CRelationDescription* relation_description , HInstance val1, HInstance val2 );


#endif;
