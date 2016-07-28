#include "FEnviroment.h"
#include "EqualsResult.h"
#include <iostream>




bool isInstanceOf(CGenericValue *val, CGenericKind *kind)
{
	{
		CObjectKind* okind = dynamic_cast<CObjectKind*>(kind);
		if (okind != nullptr)
		{
			CObjectInstance* oval = dynamic_cast<CObjectInstance*>(val);
			if (oval != nullptr)
			{
				return  (oval->kind->name == okind->name);
			}
			return true; // null is always setabble 
		}
	}

	{
		CValueKind  * vkind = dynamic_cast<CValueKind*>(kind);
		if (vkind != nullptr)
		{
			CValue * vval = dynamic_cast<CValue*>(val);
			return  (vval->vkind->name == vkind->name);
		}
		return true ; // nil is always settable 

	}

}


CObjectKind::CObjectKind(std::string named, HObjectKind prev): previous(prev), name(named)
{
}

CValueKind::CValueKind(std::string _name): name(_name)
{
}

CVariable::CVariable(const std::string& name, HGenericKind _vkind): vkind(_vkind), value(nullptr) , name(name)
{
}

EqualsResul isEqual_val(CValue* c1, CValue* c2);
EqualsResul isEqual(CGenericValue* c1, CGenericValue* c2);

EqualsResul isEqual(CValueString* c1, CValueString* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueInstance * c1, CValueInstance* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->vkind->name != c2->vkind->name) return NotEquals;
	if (c1->named  == c2->named ) return Equals;
	return NotEquals;
}


 

EqualsResul isEqual(CValueBoolean* c1, CValueBoolean* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->val == c2->val) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CRelationInstance * c1, CRelationInstance* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if ((c1->relDesc->named == c2->relDesc->named))
	{
		if (isEqual(c1->item1.get(), c2->item1.get()) == Equals)
			if (isEqual(c1->item2.get(), c2->item2.get()) == Equals)
			{
				return Equals;
			}
	}
	return NotEquals;
}


EqualsResul isEqual(CValueText* c1, CValueText* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->_text == c2->_text) return Equals;
	return NotEquals;
}

EqualsResul isEqual(CValueList* c1, CValueList* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	if (c1->values.size() != c2->values.size()) return NotEquals;
	if (c1->values.empty()) return Equals;
	auto it1 = c1->values.begin();
	auto it2 = c2->values.begin();
	while (it1 != c1->values.end())
	{
		EqualsResul q = isEqual((*it1).get(), (*it2).get());
		if (q != Equals) return NotEquals;
		++it1;
		++it2;
	}
	return Equals;
}




 




EqualsResul isEqual_val(CValue* c1, CValue* c2)
{
	if (c1 == c2) return Equals; //obvious
	EqualsResul q;
	{
		q = isEqual(dynamic_cast<CValueString*>(c1), dynamic_cast<CValueString*>(c2));
		if (q != Undefined) return q;
		q = isEqual(dynamic_cast<CValueText *>(c1), dynamic_cast<CValueText*>(c2));
		if (q != Undefined) return q;
		q = isEqual(dynamic_cast<CValueList*>(c1), dynamic_cast<CValueList*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueList*>(c1), dynamic_cast<CValueList*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueInstance*>(c1), dynamic_cast<CValueInstance*>(c2));
		if (q != Undefined) return q;

		q = isEqual(dynamic_cast<CValueBoolean *>(c1), dynamic_cast<CValueBoolean*>(c2));
		if (q != Undefined) return q;

		 

		return Undefined;
	}
}

EqualsResul isEqual_inst(CObjectInstance * c1, CObjectInstance* c2)
{	
	if( c1->kind->name == c2->kind->name)
	{
		if (c1->name == c2->name) return Equals;
	}
	return NotEquals;
}


EqualsResul isEqual_valkind(CValueKind * c1, CValueKind* c2)
{
	 
 if (c1->name == c2->name) return Equals;
	 
	return NotEquals;
}

EqualsResul isEqual_instkind(CObjectKind * c1, CObjectKind * c2)
{
 if (c1->name == c2->name) return Equals;
	 
	return NotEquals;
}

EqualsResul isEqual(CGenericValue * c1, CGenericValue* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	{
		CValue * v1 = dynamic_cast<CValue*>(c1);
		if (v1 != nullptr)
		{
			CValue * v2 = dynamic_cast<CValue*>(c2);
			if (v2 != nullptr)
				return isEqual_val(v1, v2);
			return NotEquals;
		}
	}
	{
		CObjectInstance * h1 = dynamic_cast<CObjectInstance*>(c1);
		if (h1 != nullptr)
		{
			CObjectInstance * h2 = dynamic_cast<CObjectInstance*>(c2);
			if (h2 != nullptr)
				return isEqual_inst(h1, h2);
			return NotEquals;
		}
	} 
	return Undefined;
}



EqualsResul isEqual(CGenericKind * c1, CGenericKind* c2)
{
	if (c1 == nullptr || c2 == nullptr) return Undefined;
	{
		CValueKind * v1 = dynamic_cast<CValueKind*>(c1);
		if (v1 != nullptr)
		{
			CValueKind * v2 = dynamic_cast<CValueKind*>(c2);
			if (v2 != nullptr)
				return isEqual_valkind(v1, v2);
			return NotEquals;
		}
	}
	{
		CObjectKind  * h1 = dynamic_cast<CObjectKind*>(c1);
		if (h1 != nullptr)
		{
			CObjectKind * h2 = dynamic_cast<CObjectKind*>(c2);
			if (h2 != nullptr)
				return isEqual_instkind(h1, h2);
			return NotEquals;
		}
	}
	return Undefined;
}




bool can_set_value_enum(CValueKindEnum* kenum, CValue* val)
{
	//o val eh algum desses valores porriveis ?
	for (auto it = kenum->values.begin(); it != kenum->values.end(); ++it)
	{
		if (isEqual((*it).get(), val) == Equals) return true;
	}
	return false;
}

HValue CValueBoolean::clone()
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueBoolean>(this->val));
}

HValue CValueText::clone()
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueText>(this->_text));
}

HValue CValueString::clone()
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueString>(this->_text));
}


HGenericValue copyValue(HGenericValue val)
{
	CValue * aValue = dynamic_cast<CValue*>(val.get());
	if (aValue != nullptr) return aValue->clone();
	//CObjectInstance * aInstance = dynamic_cast<CObjectInstance*>(val.get());	
	return val; //pass the reference

}


HValue CValueList::clone()
{
	auto nlist = new CValueList({});
	for (auto it = this->values.begin(); it != this->values.end(); ++it)
	{
		//CValue * aValue = dynamic_cast<CValue*>( (*it).get() );
		//if (aValue != nullptr)
		//{
		//	nlist->values.push_back( aValue->clone()  ); // clone the value
		//}
		//else
		
			nlist->values.push_back(copyValue( *it)) ; // just copy the pointer 
		
	}
	nlist->vkind = this->vkind;
	return std::shared_ptr<CValue>(nlist);
}

HValue CValueNumber::clone()
{
	return std::make_shared<  CValueNumber>(this->value);
}

 


HValue CValueInstance::clone()
{
	return  std::make_shared<CValueInstance>(this->named, this->vkind);
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

bool can_set_value_ptr(HValueKind vkind, CValue* val)
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

HValueKind HValueKindBoolean;
HValueKind HValueKindString;
HValueKind HValueKindText;
HValueKind HValueKindList;
HValueKind HValueKindNumber;
HValueKind HValueKindObjectInstance;
HValueKind HValueKindObjectKind;

CRelationDescriptionNode::CRelationDescriptionNode(std::string _named, HGenericKind _vkind): named(_named), vkind(_vkind)
{
}

CRelationDescriptionNodeGroup::CRelationDescriptionNodeGroup(std::string _named, HGenericKind _vkind): CRelationDescriptionNode(_named, _vkind)
{
}

CRelationDescriptionNodeMany::CRelationDescriptionNodeMany(std::string _named, HGenericKind _vkind): CRelationDescriptionNode(_named, _vkind)
{
}

CRelationDescription::CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode _node2, bool _symmetric): node1(_node1), node2(_node2), named(_named), symmetric(_symmetric)
{
	if (_symmetric)
	{
		if ((_node1->isMany() !=  _node2->isMany()) || ( isEqual(_node1->vkind.get()  , _node2->vkind.get() ) != Equals ))
		{
			std::cout << "unable to make assimetric relations Symetric" << std::endl;
			throw "Symetric Error ";
		}		
	}
}

CRelationInstance::CRelationInstance(CRelationDescription* _relDesc, HGenericValue val, HGenericValue val2): relDesc(_relDesc), item1(val), item2(val2)
{
}

FEnviroment::FEnviroment()
{
}

FEnviroment::~FEnviroment()
{
}

void FEnviromentBase::addKind(HObjectKind _k)
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
	HValueKindObjectInstance = std::make_shared<CValueKind>("instance");
    HValueKindObjectKind =std::make_shared<CValueKind>("kind");
}

FEnviroment* FEnviromentBase::copy()
{
	auto c = new FEnviromentBase();
	c->kinds = std::list<HObjectKind>(this->kinds.begin(), this->kinds.end());
	c->instances = std::list<HInstance>(this->instances.begin(), this->instances.end());
	return static_cast<FEnviroment*>(c) ;
}

FEnviromentBase* FEnviromentBase::getBase()
{
	return (this);
}

FEnviroment* SubFEnviroment::copy()
{
	throw "unable to copy";
}

void SubFEnviroment::addKind(HObjectKind _k)
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

 

HObjectKind make_kind(FEnviroment* env, std::string name)
{
	auto c = std::make_shared<CObjectKind>(name, nullptr);
	env->addKind(c);
	return c;
}

HObjectKind make_derivade_kind(FEnviroment* env, std::string name, HObjectKind base)
{
	auto c = std::make_shared<CObjectKind>(name, base);
	env->addKind(c);
	return c;
}

HVariable make_variable(FEnviroment* env, std::string name, HValueKind vkind)
{
	auto c = std::make_shared<CVariable>(name, vkind);
	env->addVariable(c);
	return c;
}

HObjectKind get_kind(FEnviroment* envb, std::string name)
{
	FEnviromentBase* env = dynamic_cast<FEnviromentBase*>(envb);
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

CInstanceProperty instanceProperty(CKindProperty kprop, HInstance _inst)
{
	CInstanceProperty c = CInstanceProperty(kprop.name, _inst, kprop.vkind);
	return c;
}

HInstanceProperty get_property_default_from_kind(FEnviroment* envb, HInstance obj, HObjectKind c_kind, std::string propName)
{
	FEnviromentBase* env = envb->getBase();
	{
		for (auto it = env->kind_properties_asserts.begin(); it != env->kind_properties_asserts.end(); ++it)
		{
			if ((*it).property.kind == c_kind)
				if ((*it).property.name == propName)
				{
					CInstanceProperty* cprop = new CInstanceProperty((*it).property.name, obj, (*it).property.vkind);
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
			HInstanceProperty pKind = get_property_default_from_kind(env, obj, obj->kind, name);
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

HValue get_property_value(FEnviroment* envb, HObjectKind c_kind, std::string propName)
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

HValue get_property_value(FEnviroment* envb, HInstance c_instance, std::string propName)
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

void set_property_value(FEnviroment* envb, CInstanceProperty* c_instance_property, HValue val)
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
	return get_property_value(env, c_instance_property->inst->kind, c_instance_property->name);
}

HValue make_string_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueString>(v));
}

HValue make_text_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueText>(v));
}

HValue make_bool_value(bool v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueBoolean>(v));
}

HValue make_number_value(int v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueNumber>(v));
}

HValue make_list_value(std::list<HGenericValue > glist)
{
	 return  std::static_pointer_cast<CValue>(std::make_shared<CValueList>(glist));
}

HValue make_joined_list(std::list<HGenericValue >& list1 , std::list<HGenericValue >& list2)
{
	 
	std::list<HGenericValue > values(list1 .begin(), list1 .end());
	values.insert(values.end(), list2 .begin(), list2 .end());
	
	return  std::static_pointer_cast<CValue>(std::make_shared<CValueList>(values));
}

 

HGenericValue make_obj_instance_value(HInstance v)
{
	return std::static_pointer_cast<CGenericValue>(v);
   // return std::static_pointer_cast<CValue>(std::make_shared<CValueObjectInstance>(v));
}
HGenericKind make_obj_kind_value(HObjectKind v)
{
	return std::static_pointer_cast<CGenericKind>( v );
    //return std::static_pointer_cast<CValue>(std::make_shared<CValueObjectKind>(v));
}


std::string toString(CGenericValue* val);


std::string toString_val(CValue* val)
{
	if (val == nullptr) return "NIL??";
	{
		CValueString* v = dynamic_cast<CValueString*>(val);
		if (v != nullptr) return v->_text;
	}
	{
		CValueText* txt = dynamic_cast<CValueText*>(val);
		if (txt != nullptr) return txt->_text;
	}
	{
		CValueList* lst = dynamic_cast<CValueList*>(val);
		if (lst != nullptr)
		{
			std::string s;
			for (auto it = lst->values.begin(); it != lst->values.end(); ++it)
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
			if (v->val)
			{
				return "true";
			}
			else
			{
				return "false";
			}
		}
	}
	{
		CValueNumber* v = dynamic_cast<CValueNumber*>(val);
		if (v != nullptr)
		{
			return std::to_string(v->value);
		}
	}

	 
	return "ERROR";
}
 



std::string toString_inst(CObjectInstance* val)
{
	return val->name;
}

std::string toString(CGenericValue* val)
{
	{
		CValue* v = dynamic_cast<CValue*>(val);
		if (v != nullptr) return toString_val(v);
	}
	{
		CObjectInstance* h = dynamic_cast<CObjectInstance*>(val);
		if (h != nullptr) return toString_inst(h);
	}
	return "Nil";
}

std::string toString(HGenericValue val)
{
	return toString(val.get());
}

std::string toString (CRelationInstance* val)
{
	return toString( val->item1.get()) + "->" + val->relDesc->named + " ->" + toString(val->item2.get())  ;

}



HValueKind makeValueKindEnum(FEnviroment* env, std::string _name, HValueKind _valuesKind, std::list<HValue> posiblesValues)
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

HRelationDescriptionNode make_relation_node(std::string _name, HObjectKind  _kind)
{
    HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNode>(_name, std::static_pointer_cast<CGenericKind >(_kind) );
	return val;
}

HRelationDescriptionNode make_relation_node_various(std::string _name, HObjectKind  _kind)
{
	HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNodeMany>(_name, std::static_pointer_cast<CGenericKind >(_kind) );
	return val;
}

HRelationDescriptionNode make_relation_node(std::string _name, HValueKind  _kind)
{
    HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNode>(_name, std::static_pointer_cast<CGenericKind >(_kind) );
    return val;
}

HRelationDescriptionNode make_relation_node_various(std::string _name, HValueKind  _kind)
{
    HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNodeMany>(_name, std::static_pointer_cast<CGenericKind >(_kind) );
    return val;
}





void add_relation_description(FEnviroment* envb, CRelationDescription rel_description)
{
	FEnviromentBase* env = envb->getBase();
	{
		env->relations_description.push_back(rel_description);
	}
}

CRelationDescription* get_relation_description(FEnviroment* envb, std::string named)
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

bool isAlowedToNode(FEnviroment* envb, HRelationDescriptionNode node, HGenericValue val )
{
	CRelationDescriptionNodeMany* nodeMany =  dynamic_cast<CRelationDescriptionNodeMany*>(node.get());
	if (nodeMany)
	{
		// TODO 
	} 

	 return isInstanceOf(  val.get(), node->vkind.get() ); 
}


CRelationInstance* find_relation_i_1(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val1)
{
	FEnviromentBase* env = envb->getBase();
	for (auto it = env->relation_instances .begin(); it != env->relation_instances.end(); ++it)
	{
		if (it->relDesc->named  == relation_description->named)
		{
			if( isEqual( it->item1.get()  , val1.get()) == Equals )
			{
				 
				return &(*it);
			}				 
		}
	}
	return nullptr;
}


std::list<HGenericValue> find_relation_list_1(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val1)
{
	FEnviromentBase* env = envb->getBase();
	std::list<HGenericValue> values;
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{
		if (it->relDesc->named == relation_description->named)
		{

			if (isEqual(it->item1.get(), val1.get()) == Equals)
			{
				values.push_back(it->item2); 
			}
			 
		}
	}
	return values;
}


std::list<HGenericValue> find_relation_list_2(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val2)
{
	FEnviromentBase* env = envb->getBase();
	std::list<HGenericValue> values;
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{
		if (it->relDesc->named == relation_description->named)
		{
			if (isEqual(it->item2.get(), val2.get()) == Equals)
			{
				values.push_back(it->item1);
			}
		}
	}
	return values;
}



CRelationInstance* find_relation_i_2(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val2)
{
	FEnviromentBase* env = envb->getBase();
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{
		if (it->relDesc->named == relation_description->named)
		{
			if (isEqual(it->item2.get(), val2.get()) == Equals)
			{ 
				//   std::cout << "Equals? " << toString(it->item2) << " == " << toString(val2) << std::endl;
				return &(*it);
			}
		}
	}
	return nullptr;
}


CRelationInstance* find_relation_i_any(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val)
{
	CRelationInstance* p = find_relation_i_1(envb, relation_description, val);
	if (p != nullptr) return p;
	p = find_relation_i_2(envb, relation_description, val);
	if (p != nullptr) return p;
	return nullptr;
}

CRelationInstance* find_relation_i (FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val1, HGenericValue val2)
{
	FEnviromentBase* env = envb->getBase();
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{
		if (it->relDesc->named == relation_description->named)
		{
			if (isEqual(it->item1.get(), val1.get()) == Equals)
				if (isEqual(it->item2.get(), val2.get()) == Equals)
			{
				return &(*it);
			}
		}
	}
	return nullptr;
}




void delete_relation(FEnviroment* envb, CRelationInstance* inst)
{
	if (inst == nullptr) return;
	FEnviromentBase* env = envb->getBase();
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{ 
			if ( isEqual(&(*it) , inst) == Equals)
			{
				it = env->relation_instances.erase(it);
				if(it == env->relation_instances.end() ) break;
			}		 
	}
}

 

void unset_relation(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue val1, HGenericValue val2)
{
	FEnviromentBase* env = envb->getBase();
	//Acha a relacao corrent
	auto p = find_relation_i(envb, relation_description, val1, val2);
	delete_relation(env, p); 
}

HGenericValue get_relation_to(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue from_val)
{
	if (relation_description->node1->isMany())
	{
		auto plist = find_relation_list_1(envb, relation_description, from_val);
		if (relation_description->symmetric)
		{
			auto plist_2 = find_relation_list_2(envb, relation_description, from_val);
			return make_joined_list(plist, plist_2);
		}
		return make_list_value(plist);
	}
 
	 
	auto p = find_relation_i_1(envb, relation_description, from_val);
	if (p != nullptr) return p->item2;

	if( relation_description->symmetric )
	{
		p = find_relation_i_2(envb, relation_description, from_val);
		if (p != nullptr) return p->item1;
	}
	return nullptr;
	

}


HGenericValue get_relation_from(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue  to_val)
{

    
	//FEnviromentBase* env = envb->getBase();
	
    if (relation_description->node1->isMany() )
    {
		auto plist = find_relation_list_2(envb, relation_description, to_val);
		return make_list_value(plist);
    }
    //Acha a relacao corrent
	auto p = find_relation_i_2(envb, relation_description, to_val);
	if (p != nullptr) return p->item1 ;	 
	if (relation_description->symmetric)
	{
		p = find_relation_i_2(envb, relation_description, to_val);
		if (p != nullptr) return p->item2;
	}
	return nullptr;
    
}


void set_relation(FEnviroment* envb, CRelationDescription* relation_description, HGenericValue   val1, HGenericValue val2)
{
	FEnviromentBase* env = envb->getBase();
	if (isAlowedToNode(env, relation_description->node1  , val1 ))
		if (isAlowedToNode(env, relation_description->node2, val2))
		{

			if ( relation_description->node1->isMany() == false  )
			{
				auto p = find_relation_i_1(envb, relation_description, val1 );
				delete_relation(env, p);
			}

			if (relation_description->node2->isMany() == false)
			{
				auto p = find_relation_i_2(envb, relation_description, val2);
				delete_relation(env, p);
			}

			env->relation_instances.push_back(CRelationInstance(relation_description, val1, val2));
			return;
		}
	throw "unable to create relation instance";
}





HValue makeValueInstance(FEnviroment* envb, const std::string& _name, HValueKind vkind)
{
	FEnviromentBase* env = envb->getBase();
	{
		HValueInstance val = std::make_shared<CValueInstance>(_name, vkind);
		env->value_instances.push_back(val);
		return val;
	}
}

std::string toString(HValue val)
{
	return toString(val.get());
}

HInstance make_instance(FEnviroment* env, std::string name, HObjectKind k)
{
	auto c = std::make_shared<CObjectInstance>(k, name);
	env->addInstance(c);
	return c;
}


 

void set_variable_value(FEnviroment* env, HVariable var, HGenericValue  c_value)
{
	if (c_value == nullptr)
	{
		throw "nill ??? ";
	}
	if (isInstanceOf ( c_value.get() , var->vkind.get() ))
	{
		var->value =  copyValue( c_value );
	}
	else
	{
		throw "types not match";
	}
}

HGenericValue get_variable_value(FEnviroment* env, HVariable var)
{
	return  copyValue(var->value );
}

EqualsResul isEqual(HValue c1, HValue  c2)
{
	return isEqual(c1.get(), c2.get());
}




void FEnviroment::dump_relations()
{
	FEnviromentBase *env = this->getBase();

	std::cout << "Begin Relations" << std::endl;
	for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
	{

          std::cout << toString(&(*it)) <<   std::endl;
		 
	}
	std::cout << "End Relations " << std::endl;


}