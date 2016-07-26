#pragma once

#ifndef _CFENV_H
#define _CFENV_H
#include <string>
#include <list>
#include <memory>


class CKind
{
public:
	CKind* previous;
	std::string name;
	CKind(std::string named, CKind *prev);

};
using HKind = std::shared_ptr<CKind>;

class CInstance
{

public:
	CInstance(CKind* kind, const std::string& name)
		: kind(kind),
		name(name)
	{
	}

	CKind* kind;
	std::string name;
};

using HInstance = std::shared_ptr<CInstance>;





class CKindProperty
{
	CKindProperty(const std::string& name, CKind* inst)
		: name(name),
		inst(inst)
	{
	}

	std::string name;
	CKind* inst;

};


class CValueKind
{
public:
	std::string name;
	CValueKind(std::string _name);
	virtual ~CValueKind() {};
};

using HValueKind = std::shared_ptr<CValueKind>;
 


class CInstanceProperty
{
public:
	CInstanceProperty(const std::string& name, HInstance inst, HValueKind vkind)
		: name(name),
		inst(inst),
		vkind(vkind)
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



class CValueKindEnum : public CValueKind
{

public:
	CValueKindEnum(const std::string& _name, const std::string& name, const std::list<CValue*>& c_values)
		: CValueKind(_name),
		name(name),
		values(c_values)
	{
	}

	std::string name;
	std::list<CValue*> values;



};





class CValueText : public CValue
{
	CValueText(HValueKind vkind, const std::string& cs)
		: CValue(vkind),
		_text(cs)
	{
	}

	std::string _text;

};


class CValueList : public CValue
{
	CValueList(HValueKind vkind, const std::list<CValue*>& c_values)
		: CValue(vkind),
		values(c_values)
	{
	}

	std::list<CValue*> values;
};





class CKindPropertyAssert
{
	CKindPropertyAssert(CKindProperty* property, CValue*  value)
		: property(property),
		value(value)
	{
	}

	CKindProperty *property;
	CValue *value;

};

class CInstancePropertyAssert
{
	CInstancePropertyAssert(CInstanceProperty* property, CValue* value)
		: property(property),
		value(value)
	{
	}

	CInstanceProperty *property;
	CValue* value;

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

};


HKind make_kind(FEnviroment *env, std::string name);
HInstance make_instance(FEnviroment *env, std::string name, HKind k);
HKind make_derivade_kind(FEnviroment* env, std::string name, HKind base);


#endif;