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
	}

	 
	std::string name;
	HInstance inst;
	HValueKind vkind;

};


class CValue
{
public:
	CValue(HValueKind vkind)
		: vkind(vkind)
	{
	}
	virtual ~CValue() {};
	HValueKind vkind;


};
using HValue  = std::shared_ptr<CValue>;
 




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

 
extern HValueKind  HValueKindString;
extern HValueKind  HValueKindText;
extern HValueKind  HValueKindList;





class CValueText : public CValue
{
public:
	CValueText(  const std::string& cs)
		: CValue(HValueKindText),
		_text(cs)
	{
	}

	std::string _text;

};

class CValueString : public CValue
{
public :
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
	CValueList(  const std::list<CValue*>& c_values)
		: CValue(HValueKindList),
		values(c_values)
	{
	}

	std::list<CValue*> values;
};


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
		value(value)
	{
	}

	CKindProperty property;
	HValueAssert value;

};

class CInstancePropertyAssert
{
public:
	CInstancePropertyAssert(CInstanceProperty* property, HValue  value)
		: property(property),
		value(value)
	{
	}

	CInstanceProperty *property;
	HValue value;

};




//No env , tudo eh HANDLE 

class FEnviroment
{
public:
	FEnviroment();
	FEnviroment* copy() const;
	virtual ~FEnviroment();
	void addKind(HKind _k);
	void addInstance(HInstance _k); 

	//Listas 
	std::list<HInstance> instances;
	std::list<HKind> kinds;

	std::list<CInstanceProperty> instance_properties;
	std::list<CInstancePropertyAssert > instance_properties_asserts;
	std::list<CKindPropertyAssert> kind_properties_asserts; 

};


HKind make_kind(FEnviroment *env, std::string name);
HInstance make_instance(FEnviroment *env, std::string name, HKind k);
HKind make_derivade_kind(FEnviroment* env, std::string name, HKind base);


HKind get_kind(FEnviroment* env, std::string name);
HInstance get_instance(FEnviroment* env, std::string name);

void  set_property(FEnviroment* env, CInstanceProperty&  prop);
void  set_property(FEnviroment* env, CKindPropertyAssert&  prop);

CInstanceProperty*  get_property(FEnviroment* env, HInstance obj , std::string name);


HValue  get_property_value(FEnviroment* env, CInstanceProperty* c_instance_property);
void  set_property_value(FEnviroment* env, CInstanceProperty* c_instance_property , HValue val);


HValue make_string_value(std::string v);
HValue make_text_value(std::string v);


std::string  toString(HValue val);
std::string  toString(CValue* val);



HValueKind  makeValueKindEnum(FEnviroment* env, const std::string& _name, HValueKind _valuesKind, const std::list<HValue>& posiblesValues);

#endif;
