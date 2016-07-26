#include "FEnviroment.h"
#include "EqualsResult.h"


CKind::CKind(std::string named, HKind prev):previous(prev), name(named)
{

}

CValueKind::CValueKind(std::string _name): name(_name)
{}

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
	EqualsResul q = Undefined;
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

bool can_set_value(CValueKindEnum* kenum, HValue val)
{
	//o val eh algum desses valores porriveis ?
	for (auto it = kenum->values.begin(); it != kenum->values.end(); ++it)
	{
		if (isEqual((*it).get(), val.get()) == Equals) return true;
	}
	return false;

}

bool can_set_value(HValueKind vkind, HValue val)
{
	
	CValueKindEnum* kenum  = dynamic_cast<CValueKindEnum*>(vkind.get());
	if (kenum != nullptr )
	{
		return can_set_value(kenum, val);
		
	}

	if (val->vkind == vkind) return true;
	return false;

}

FEnviroment::FEnviroment()
{
}

FEnviroment* FEnviroment::copy() const
{
	auto  c =  new FEnviroment();
	
	c->kinds = std::list<HKind>(this->kinds.begin(), this->kinds.end());
	c->instances = std::list<HInstance>(this->instances.begin(), this->instances.end());


	return c;
}


  HValueKind  HValueKindString;
  HValueKind  HValueKindText;
  HValueKind  HValueKindList;

FEnviroment::~FEnviroment()
{
	   HValueKindString = std::make_shared<CValueKind>("string");
	   HValueKindText = std::make_shared<CValueKind>("text");
	   HValueKindList = std::make_shared<CValueKind>("list");

}

void FEnviroment::addKind(HKind _k)
{
	this->kinds.push_back(_k);
}

void FEnviroment::addInstance(HInstance _k)
{
	this->instances.push_back(_k);
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

HKind get_kind(FEnviroment* env, std::string name)
{
	for(auto it = env->kinds.begin() ; it != env->kinds.end();++it )
	{
		if ((*it)->name == name) return *it;
	}
	return nullptr;
}


HInstance get_instance(FEnviroment* env, std::string name)
{
	for (auto it = env->instances.begin(); it != env->instances.end(); ++it)
	{
		if ((*it)->name == name) return *it;
	}
	return nullptr;
}

void set_property(FEnviroment* env,   CInstanceProperty& prop)
{
	env->instance_properties.push_back(prop);
}

CInstanceProperty* get_property(FEnviroment* env, HInstance obj, std::string name)
{
	for (auto it = env->instance_properties.begin(); it != env->instance_properties.end(); ++it)
	{
		if ((*it).inst == obj)
		{
			return &(*it);
		}
	}
	return nullptr;
}


HValue get_property_value(FEnviroment* env, HKind c_kind , std::string  propName)
{
	for (auto it = env->kind_properties_asserts.begin(); it != env->kind_properties_asserts.end(); ++it)
	{
		if ((*it).property->kind   == c_kind)
			if ((*it).property->name  == propName)
			{
				return (*it).value;
			}
	}
	if( c_kind->previous != nullptr )
	{
		return get_property_value(env, c_kind->previous, propName);
	}
	return nullptr;
}


HValue get_property_value(FEnviroment* env, HInstance c_instance, std::string  propName)
{

	for (auto it = env->instance_properties_asserts.begin(); it != env->instance_properties_asserts.end(); ++it)
	{
		if ((*it).property->inst == c_instance)
			if ((*it).property->name == propName)
			{
				return (*it).value;
			}
	}
	return nullptr;
}


void  set_property_value(FEnviroment* env, CInstanceProperty* c_instance_property, HValue val)
{
	if ( can_set_value(c_instance_property->vkind , val))
	{
		for (auto it = env->instance_properties_asserts.begin(); it != env->instance_properties_asserts.end(); ++it)
		{
			if ((*it).property->inst == c_instance_property->inst)
				if ((*it).property->name == c_instance_property->name)
				{
					(*it).value = val;
					return;
				}
		}
		CInstancePropertyAssert cval = CInstancePropertyAssert(c_instance_property, val);
		env->instance_properties_asserts.push_back(cval);
	}
}

HValue get_property_value(FEnviroment* env, CInstanceProperty* c_instance_property)
{
	// to_decide entra aqui 

	HValue v = get_property_value(env, c_instance_property->inst, c_instance_property->name);
	// nao tem na instancia ..obtem do tipo
	if (v != nullptr) return v;

	return  get_property_value(env, c_instance_property->inst->kind , c_instance_property->name);

	return nullptr;
}

HValue make_string_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueString>(v));
}

HValue make_text_value(std::string v)
{
	return std::static_pointer_cast<CValue>(std::make_shared<CValueText>(v));
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
				CValue* hit = (*it);
				s += toString(*it) + " ";
			}
			return s;
		}
	}

	return "ERROR";
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
