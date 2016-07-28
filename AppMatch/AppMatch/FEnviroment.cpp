#include "FEnviroment.h"
#include "EqualsResult.h"
#include <iostream>

namespace VM
{
	EqualsResul isEqual_val(CValue* c1, CValue* c2);
	EqualsResul isEqual(CGenericValue* c1, CGenericValue* c2);
	EqualsResul isEqual(CGenericKind * c1, CGenericKind* c2);
	EqualsResul isEqual(CRelationInstance * c1, CRelationInstance* c2);




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
			return true; // nil is always settable 

		}

	}


	CObjectKind::CObjectKind(std::string named, HObjectKind prev) : previous(prev), name(named)
	{
	}

	CValueKind::CValueKind(std::string _name) : name(_name)
	{
	}

	CVariable::CVariable(const std::string& name, HGenericKind _vkind) : vkind(_vkind), value(nullptr), name(name)
	{
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

			nlist->values.push_back(copyValue(*it)); // just copy the pointer 

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

	CValueInstance::CValueInstance(const std::string& _named, HValueKind vkind) : CValue(vkind), named(_named)
	{
	}

	HValueAssert::HValueAssert(const HValue& c_value, float constraint) : value(c_value),
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

	CRelationDescriptionNode::CRelationDescriptionNode(std::string _named, HGenericKind _vkind) : named(_named), vkind(_vkind)
	{
	}

	CRelationDescriptionNodeGroup::CRelationDescriptionNodeGroup(std::string _named, HGenericKind _vkind) : CRelationDescriptionNode(_named, _vkind)
	{
	}

	CRelationDescriptionNodeMany::CRelationDescriptionNodeMany(std::string _named, HGenericKind _vkind) : CRelationDescriptionNode(_named, _vkind)
	{
	}

	CRelationDescription::CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode _node2, bool _symmetric) : node1(_node1), node2(_node2), named(_named), symmetric(_symmetric)
	{
		if (_symmetric)
		{
			if ((_node1->isMany() != _node2->isMany()) || (isEqual(_node1->vkind.get(), _node2->vkind.get()) != Equals))
			{
				std::cout << "unable to make assimetric relations Symetric" << std::endl;
				throw "Symetric Error ";
			}
		}
	}

	CRelationInstance::CRelationInstance(CRelationDescription* _relDesc, HGenericValue val, HGenericValue val2) : relDesc(_relDesc), item1(val), item2(val2)
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
		HValueKindObjectKind = std::make_shared<CValueKind>("kind");
	}

	FEnviroment* FEnviromentBase::copy()
	{
		auto c = new FEnviromentBase();
		c->kinds = std::list<HObjectKind>(this->kinds.begin(), this->kinds.end());
		c->instances = std::list<HInstance>(this->instances.begin(), this->instances.end());
		return static_cast<FEnviroment*>(c);
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

	HValue make_joined_list(std::list<HGenericValue >& list1, std::list<HGenericValue >& list2)
	{

		std::list<HGenericValue > values(list1.begin(), list1.end());
		values.insert(values.end(), list2.begin(), list2.end());

		return  std::static_pointer_cast<CValue>(std::make_shared<CValueList>(values));
	}



	HGenericValue make_obj_instance_value(HInstance v)
	{
		return std::static_pointer_cast<CGenericValue>(v);
		// return std::static_pointer_cast<CValue>(std::make_shared<CValueObjectInstance>(v));
	}
	HGenericKind make_obj_kind_value(HObjectKind v)
	{
		return std::static_pointer_cast<CGenericKind>(v);
		//return std::static_pointer_cast<CValue>(std::make_shared<CValueObjectKind>(v));
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


	HValue makeValueInstance(FEnviroment* envb, const std::string& _name, HValueKind vkind)
	{
		FEnviromentBase* env = envb->getBase();
		{
			HValueInstance val = std::make_shared<CValueInstance>(_name, vkind);
			env->value_instances.push_back(val);
			return val;
		}
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
		if (isInstanceOf(c_value.get(), var->vkind.get()))
		{
			var->value = copyValue(c_value);
		}
		else
		{
			throw "types not match";
		}
	}

	HGenericValue get_variable_value(FEnviroment* env, HVariable var)
	{
		return  copyValue(var->value);
	}





	std::string toString(CRelationInstance* val);
	void FEnviroment::dump_relations()
	{
		FEnviromentBase *env = this->getBase();

		std::cout << "Begin Relations" << std::endl;
		for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it)
		{

			std::cout << toString(&(*it)) << std::endl;

		}
		std::cout << "End Relations " << std::endl;

	}

}