
#include "CValueDefinitions.h"
#include "FEnviroment.h"

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

CInstanceProperty instanceProperty(CObjectKindProperty kprop, HInstance _inst)
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



CKindPropertyAssert::CKindPropertyAssert(CObjectKindProperty _property, HValueAssert value): property(_property),
                                                                                      valueAssertion(value)
{
	
	if ( can_set_value (property.vkind ,  valueAssertion.value ) ==false )
	{
		throw "unable to set value";
	}

}