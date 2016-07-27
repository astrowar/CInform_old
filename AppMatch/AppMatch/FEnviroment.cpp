#include "FEnviroment.h"
#include "EqualsResult.h"
#include <iostream>


CKind::CKind(std::string named, HKind prev):previous(prev), name(named)
{

}

CValueKind::CValueKind(std::string _name): name(_name)
{}


 

CVariable::CVariable(const std::string& name, HValueKind _vkind): vkind(_vkind), value( nullptr) , name(name)
{
 
}

EqualsResul isEqual(CValue *c1, CValue *c2);


EqualsResul isEqual(CValueString *c1, CValueString *c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueText *c1, CValueText *c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueList *c1, CValueList *c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->values .size() != c2->values.size()) return NotEquals;
	if (c1->values.empty()) return Equals;

	auto it1 = c1->values.begin();
	auto it2 = c2->values.begin();

	while (it1 != c1->values.end())
	{
		EqualsResul q = isEqual((*it1) , (*it2) );
		if (q != Equals) return NotEquals;
		++it1;
		++it2;
	}

	return Equals;
}

EqualsResul isEqual(CValue *c1, CValue *c2)
{
	EqualsResul q;
	{
		 
		q = isEqual(dynamic_cast<CValueString*>(c1), dynamic_cast<CValueString*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueText  *>(c1), dynamic_cast<CValueText*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueList*>(c1), dynamic_cast<CValueList*>(c2));
		if (q != Undefined) return q;

		return Undefined;
	}

}

bool can_set_value_enum(CValueKindEnum* kenum, CValue *val)
{
	//o val eh algum desses valores porriveis ?
	for (auto it = kenum->values.begin(); it != kenum->values.end(); ++it)
	{
		if (isEqual((*it).get(), val ) == Equals) return true;
	}
	return false;

}

CValue* CValueBoolean::clone()
{
	return new CValueBoolean(this->val);
}

CValue* CValueText::clone()
{
	return new CValueText(this->_text );
}

CValue* CValueString::clone()
{
	return new CValueString(this->_text );
}

CValue* CValueList::clone()
{

	auto nlist = new CValueList({});
	for (auto it = this->values.begin(); it != this->values.end(); it)
	{
		nlist->values.push_back((*it)->clone());
	}
	nlist->vkind = this->vkind;
	return nlist;
}

CValue* CValueNumber::clone()
{
	return new CValueNumber(this->value );
}

CValue* CValueInstance::clone()
{
	return new CValueInstance(this->named, this->vkind);
}

CValueInstance::CValueInstance(const std::string& _named, HValueKind vkind): CValue(vkind), named(_named)
{

}

HValueAssert::HValueAssert(const HValue& c_value, float constraint): value(c_value),
                                                                     constraint(constraint)
{
}

HValueAssert Usually_Value(const HValue& c_value)
{
	return HValueAssert(c_value, 0.3f);
}

HValueAssert Always_Value(const HValue& c_value)
{
	return HValueAssert(c_value, 1.0f);
}

bool can_set_value_ptr(HValueKind vkind, CValue *val)
{

	CValueKindEnum* kenum = dynamic_cast<CValueKindEnum*>(vkind.get());
	if (kenum != nullptr)
	{
		bool cans = can_set_value_enum(kenum, val);

		return cans;

	}

	if (val->vkind == vkind)
	{
		return true;
	}
	return false;

}


bool can_set_value(HValueKind vkind, HValue val)
{
	return can_set_value_ptr(vkind, val.get());

}


 



HValueKind  HValueKindBoolean;
HValueKind  HValueKindString;
HValueKind  HValueKindText;
HValueKind  HValueKindList;
HValueKind  HValueKindNumber;

CRelationDescriptionNode::CRelationDescriptionNode(std::string _named, HKind _kind): named(_named), kind(_kind)
{
}

CRelationDescriptionNodeGroup::CRelationDescriptionNodeGroup(std::string _named, HKind _kind): CRelationDescriptionNode(_named,_kind)
{
}

CRelationDescriptionNodeMany::CRelationDescriptionNodeMany(std::string _named, HKind _kind): CRelationDescriptionNode(_named,_kind)
{
}

CRelationDescription::CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode _node2, bool _symmetric   ):node1(_node1), node2(_node2), named(_named),symmetric(_symmetric)
{

}

 

CRelationInstance::CRelationInstance(CRelationDescription* _relDesc, HInstance val, HInstance val2): relDesc(_relDesc), item1(val), item2(val2)
{
}

FEnviroment::FEnviroment()
{
	 

}

 

 

FEnviroment::~FEnviroment()
{
	 

}

void FEnviromentBase::addKind(HKind _k)
{
	this->kinds.push_back(_k);
}

void FEnviromentBase::addInstance(HInstance _k)
{
	this->instances.push_back(_k);
}

void FEnviromentBase::addVariable(HVariable _k)
{
	this->variables.push_back(_k);
}

 

FEnviromentBase::FEnviromentBase()
{

	HValueKindBoolean = std::make_shared<CValueKind>("bool");
	HValueKindString = std::make_shared<CValueKind>("string");
	HValueKindText = std::make_shared<CValueKind>("text");
	HValueKindList = std::make_shared<CValueKind>("list");
	HValueKindNumber = std::make_shared<CValueKind>("number");
}

 
FEnviroment* FEnviromentBase::copy()  
{
	auto  c = new FEnviromentBase();

	c->kinds = std::list<HKind>(this->kinds.begin(), this->kinds.end());
	c->instances = std::list<HInstance>(this->instances.begin(), this->instances.end());


	return static_cast<FEnviroment*>(c)  ;
}

FEnviromentBase* FEnviromentBase::getBase()
{
	return  (this);
}

 

FEnviroment* SubFEnviroment::copy()
{
	throw "unable to copy";
}

void SubFEnviroment::addKind(HKind _k)
{
	throw "unable to add";
}

void SubFEnviroment::addInstance(HInstance _k)
{
	throw "unable to add";
}

void SubFEnviroment::addVariable(HVariable _k)
{
	this->variables.push_back(_k);
}

FEnviromentBase* SubFEnviroment::getBase()
{
	return this->parent->getBase();
}



HKind make_kind(FEnviroment *env,  std::string name)
{
	auto c = std::make_shared<CKind>(name, nullptr);
	env->addKind(c);
	return c;
}

HKind make_derivade_kind(FEnviroment* env, std::string name , HKind base)
{
	auto c = std::make_shared<CKind>(name, base );
	env->addKind(c);
	return c;
}

HVariable make_variable(FEnviroment* env, std::string name, HValueKind vkind)
{
	auto c = std::make_shared<CVariable >(name, vkind);
	env->addVariable(c);
	return c;
}

HKind get_kind(FEnviroment* envb, std::string name)
{	
	FEnviromentBase* env  = dynamic_cast<FEnviromentBase*>(envb);
	 
	{

		for (auto it = env->kinds.begin(); it != env->kinds.end(); ++it)
		{
			if ((*it)->name == name) return *it;
		}
		return nullptr;
	}
}


HInstance get_instance(FEnviroment* envb, std::string name)
{
	FEnviromentBase* env = envb->getBase();
	 
	{
		for (auto it = env->instances.begin(); it != env->instances.end(); ++it)
		{
			if ((*it)->name == name) return *it;
		}
		return nullptr;
	}
	 
}

void assign_property(FEnviroment* envb, CInstanceProperty& prop)
{
	FEnviromentBase* env = envb->getBase();
	 
	{
		env->instance_properties.push_back(prop);
	}
}

void assign_property(FEnviroment* envb, CKindPropertyAssert& prop)
{
	FEnviromentBase* env = envb->getBase();
	 
	{
		env->kind_properties_asserts.push_back(prop);
	}
	 
}

CInstanceProperty   instanceProperty(CKindProperty  kprop , HInstance _inst)
{
	CInstanceProperty   c =    CInstanceProperty(kprop.name, _inst, kprop.vkind);
	return c;

}

HInstanceProperty  get_property_default_from_kind(FEnviroment* envb, HInstance obj,  HKind c_kind, std::string propName)
{
	FEnviromentBase* env = envb->getBase();
	 
	{
		for (auto it = env->kind_properties_asserts.begin(); it != env->kind_properties_asserts.end(); ++it)
		{
			if ((*it).property.kind == c_kind)
				if ((*it).property.name == propName)
				{
					CInstanceProperty *cprop = new  CInstanceProperty((*it).property.name, obj, (*it).property.vkind);
					return HInstanceProperty(cprop);
				}
		}
		if (c_kind->previous != nullptr)
		{
			return get_property_default_from_kind(env, obj, c_kind->previous, propName);
		}
		return nullptr;
	}
}

CInstanceProperty* get_property(FEnviroment* envb, HInstance obj, std::string name)
{
	FEnviromentBase* env = envb->getBase();
	 
	{
		for (auto it = env->instance_properties.begin(); it != env->instance_properties.end(); ++it)
		{
			if ((*it).name == name)
			{
				if ((*it).inst == obj)
				{
					return &(*it);
				}
			}
		}
		{
			//nao tem na instancia .. verifica se tem alguma herdada do seu Kind
			HInstanceProperty  pKind = get_property_default_from_kind(env, obj, obj->kind, name);
			// Ok .. agora associa esse valor na instancia
			if (pKind != nullptr)
			{
				env->instance_properties.push_back(*pKind);
				return &(env->instance_properties.back());
			}
		}
		return nullptr;
	}
}


HValue get_property_value(FEnviroment* envb, HKind c_kind , std::string  propName)
{
	FEnviromentBase* env = envb->getBase();
	 
	 
		for (auto it = env->kind_properties_asserts.begin(); it != env->kind_properties_asserts.end(); ++it)
		{
			if ((*it).property.kind == c_kind)
				if ((*it).property.name == propName)
				{
					return (*it).valueAssertion.value;
				}
		}
		if (c_kind->previous != nullptr)
		{
			return get_property_value(env, c_kind->previous, propName);
		}
		return nullptr;
	 
}


HValue get_property_value(FEnviroment* envb, HInstance c_instance, std::string  propName)
{
	FEnviromentBase* env = envb->getBase();
	{
		for (auto it = env->instance_properties_values.begin(); it != env->instance_properties_values.end(); ++it)
		{
			if ((*it).property.inst == c_instance)
				if ((*it).property.name == propName)
				{
					return (*it).value;
				}
		}
		return nullptr;
	}
}


void  set_property_value(FEnviroment* envb, CInstanceProperty* c_instance_property, HValue val)
{
	FEnviromentBase* env = envb->getBase();
	{
		//std::cout << "Try set " << val->vkind->name << " to " << c_instance_property->vkind->name << std::endl;
		if (can_set_value(c_instance_property->vkind, val))
		{
			for (auto it = env->instance_properties_values.begin(); it != env->instance_properties_values.end(); ++it)
			{
				if ((*it).property.inst == c_instance_property->inst)
					if ((*it).property.name == c_instance_property->name)
					{
						(*it).value = val;
						return;
					}
			}
			CInstancePropertyAssert cval = CInstancePropertyAssert(*c_instance_property, val);
			env->instance_properties_values.push_back(cval);
		}
		else
		{
			throw "unable to set value";
		}
	}
}

HValue get_property_value(FEnviroment* env, CInstanceProperty* c_instance_property)
{
	// to_decide entra aqui 

	HValue v = get_property_value(env, c_instance_property->inst, c_instance_property->name);
	// nao tem na instancia ..obtem do tipo
	if (v != nullptr) return v;

	return  get_property_value(env, c_instance_property->inst->kind , c_instance_property->name);
}

HValue make_string_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueString>(v));
}

HValue make_text_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueText>(v));
}


HValue make_bool_value(bool  v) 
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueBoolean>(v));
}


HValue make_number_value(int  v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueNumber>(v));
}


std::string toString(CValue *val)
{
	if (val == nullptr) return "NIL??";

	{
		CValueString* v = dynamic_cast<CValueString*>(val );
		if (v != nullptr) return v->_text;
	}
	{
		CValueText* txt = dynamic_cast<CValueText*>(val );
		if (txt != nullptr) return txt->_text;
	}

	{
		CValueList* lst = dynamic_cast<CValueList*>(val );
		if (lst != nullptr)
		{
			std::string s;
			for(auto it = lst->values.begin() ; it != lst->values.end(); it)
			{
				//CValue* hit = (*it);
				s += toString(*it) + " ";
			}
			return s;
		}
	}

	{
		CValueBoolean* v = dynamic_cast<CValueBoolean*>(val);
		if (v != nullptr)
		{
			if (v->val) { return "true"; }
			else { return "false";  }
		}
	}

	{
		CValueNumber* v = dynamic_cast<CValueNumber*>(val);
		if (v != nullptr)
		{
			return  std::to_string(v->value);
		}
	}

	 

	return "ERROR";
}

HValueKind makeValueKindEnum(FEnviroment* env, std::string  _name, HValueKind _valuesKind, std::list<HValue>  posiblesValues)
{
	if (_valuesKind == nullptr)
	{
		throw "unable to set value kind";
	}

	std::shared_ptr<CValueKindEnum> cc = std::make_shared<CValueKindEnum>(_name, _valuesKind, posiblesValues);
	 
	return cc;


}

HValueKind makeValueKind(FEnviroment* env, const std::string& _name)
{
	std::shared_ptr<CValueKind> cc = std::make_shared<CValueKind>(_name);
	return cc;
}

HRelationDescriptionNode make_relation_node(  std::string _name, HKind _kind)
{ 
		HRelationDescriptionNode  val = std::make_shared<CRelationDescriptionNode>(_name, _kind);	 
		return val; 
}

HRelationDescriptionNode make_relation_node_various(std::string _name,  HKind _kind)
{
	HRelationDescriptionNode  val = std::make_shared<CRelationDescriptionNodeMany>(_name,  _kind);
	return val;

}

void add_relation_description(FEnviroment* envb, CRelationDescription rel_description)
{
	FEnviromentBase* env = envb->getBase();
	{ 
		env->relations_description.push_back(rel_description); 
	}
}

CRelationDescription*   get_relation_description(FEnviroment* envb, std::string named)
{
	FEnviromentBase* env = envb->getBase();
	{
		for (auto it = env->relations_description.begin(); it != env->relations_description.end(); ++it)
		{
			if (it->named == named)
			{
				  return &(*it);
			}
		}
	}
	return nullptr;
}


 

void add_relation(FEnviroment* envb, CRelationDescription* relation_description, HInstance val1, HInstance val2)
{
	FEnviromentBase* env = envb->getBase();
	 if (relation_description->node1->kind == val1->kind )
		 if (relation_description->node2->kind == val2->kind)
		 {
			 env->relation_instances.push_back(CRelationInstance( relation_description, val1,val2 ) );
			 return;

		 }

	 throw "unable to create relation instance";

}


HValue   makeValueInstance(FEnviroment* envb, const std::string& _name , HValueKind vkind )
{
	FEnviromentBase* env = envb->getBase();
	{
		HValueInstance  val = std::make_shared<CValueInstance>(_name, vkind);
		env->value_instances.push_back(val);
		return val;
	}
	 
}



std::string toString(HValue val)
{
	return toString(val.get());
}

HInstance make_instance(FEnviroment* env, std::string name, HKind k)
{
	auto c = std::make_shared<CInstance>(k , name);
	env->addInstance(c);
	return c;
}





void set_variable_value(FEnviroment* env, HVariable var, HValue  c_value)
{
	if (c_value == nullptr)
	{
		throw "nill ??? ";
		 
	}
	if (can_set_value (var->vkind, c_value))
	{
		var->value = std::shared_ptr<CValue>( c_value->clone() );
	}
	else
	{
		throw "types not match";
	}
}

HValue get_variable_value(FEnviroment* env, HVariable var)
{
	return std::shared_ptr<CValue>(var->value->clone());
}