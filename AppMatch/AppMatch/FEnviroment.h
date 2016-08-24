#pragma once
#ifndef _CFENV_H
#define _CFENV_H

#include <string>
#include <list>
#include <memory>
#include "EqualsResult.h"
#include "ConstDefinitions.h"
#include "CObjectDefinitions.h"
#include "CValueDefinitions.h"
#include "CProperties.h"
#include "CRelations.h"
#include "CVariableDefinition.h"
#include "CAssertionDefinition.h"

namespace VM {
    extern HValueKind HValueKindBoolean;
    extern HValueKind HValueKindString;
    extern HValueKind HValueKindText;
    extern HValueKind HValueKindList;
    extern HValueKind HValueKindNumber;

    extern HValueKind HValueKindObjectInstance;
    extern HValueKind HValueKindObjectKind;

#ifdef oldCode
    class CValueObjectInstance : public CValue //um  HInstancia
    {
    public:
        HValue clone() override;

        CValueObjectInstance(HInstance c_value)
            : CValue(HValueKindObjectInstance),
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
            : CValue(HValueKindObjectKind),
            value(c_value)
        {
        }

        HObjectKind value;
    };

    using HValueObjectKind = std::shared_ptr<CValueObjectKind>;
#endif






    //========================================


    //=====================================
    //No env , tudo eh HANDLE
    class FEnviromentBase;

    class FEnviroment {
    public:
        FEnviroment();

        virtual FEnviroment *copy() = 0;

        virtual ~FEnviroment();

        virtual void addKind(HObjectKind _k) = 0;

        virtual void addInstance(HInstance _k) = 0;

        virtual void addVariable(HVariable _k) = 0;

        virtual FEnviromentBase *getBase() = 0;

        virtual void dump_relations();
    };

    class FEnviromentBase : public FEnviroment {
    public:
        void addKind(HObjectKind _k) override;

        void addInstance(HInstance _k) override;

        void addVariable(HVariable _k) override;

        FEnviromentBase();

        virtual FEnviroment *copy() override;

        virtual FEnviromentBase *getBase() override;

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
    class SubFEnviroment : public FEnviroment {
    public:
        FEnviroment *copy() override;

        void addKind(HObjectKind _k) override;

        void addInstance(HInstance _k) override;

        void addVariable(HVariable _k) override;

        virtual FEnviromentBase *getBase() override;

    private:
        SubFEnviroment(FEnviroment *parent)
                : parent(parent) {
        }

        FEnviroment *parent;
        std::list<HVariable> variables;
    };


    bool isInstanceOf(CGenericValue *val, CGenericKind *kind);

    EqualsResul isEqual(HValue c1, HValue c2);

    HObjectKind make_kind(FEnviroment *env, std::string name);

    HInstance make_instance(FEnviroment *env, std::string name, HObjectKind k);

    HObjectKind make_derivade_kind(FEnviroment *env, std::string name, HObjectKind base);

    HVariable make_variable(FEnviroment *env, std::string name, HValueKind vkind);

    HObjectKind get_kind(FEnviroment *env, std::string name);

    HInstance get_instance(FEnviroment *env, std::string name);

    void assign_property(FEnviroment *env, CInstanceProperty &prop);

    void assign_property(FEnviroment *env, CKindPropertyAssert &prop);

    CInstanceProperty *get_property(FEnviroment *env, HInstance obj, std::string name);

    HValue get_property_value(FEnviroment *env, CInstanceProperty *c_instance_property);

    void set_property_value(FEnviroment *env, CInstanceProperty *c_instance_property, HValue val);

    void set_variable_value(FEnviroment *env, HVariable var, HGenericValue c_value);

    HGenericValue get_variable_value(FEnviroment *env, HVariable var);

    HValue make_string_value(std::string v);

    HValue make_text_value(std::string v);

    HValue make_bool_value(bool v);

    HValue make_number_value(int v);

    HValue make_list_value(std::list<HGenericValue> glist);

    HGenericValue make_obj_instance_value(HInstance v);

    HGenericKind make_obj_kind_value(HObjectKind v);

    HValue makeValueInstance(FEnviroment *env, const std::string &_name, HValueKind vkind);

    std::string toString(HGenericValue val);

    std::string toString(HValue val);

    HValueKind
    makeValueKindEnum(FEnviroment *env, std::string _name, HValueKind _valuesKind, std::list<HValue> posiblesValues);

    HValueKind makeValueKind(FEnviroment *env, const std::string &_name);


    HRelationDescriptionNode make_relation_node(std::string _name, HObjectKind _vkind);

    HRelationDescriptionNode make_relation_node_various(std::string _name, HObjectKind _vkind);

    HRelationDescriptionNode make_relation_node(std::string _name, HValueKind _vkind);

    HRelationDescriptionNode make_relation_node_various(std::string _name, HValueKind _vkind);


    CRelationDescription *get_relation_description(FEnviroment *env, std::string named);

    void add_relation_description(FEnviroment *envb, CRelationDescription rel_description);


    void
    set_relation(FEnviroment *env, CRelationDescription *relation_description, HGenericValue val1, HGenericValue val2);

    void unset_relation(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1,
                        HGenericValue val2);

    HGenericValue
    get_relation_to(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue from_val);

    HGenericValue
    get_relation_from(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue to_val);
}

#endif



