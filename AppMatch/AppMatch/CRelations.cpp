
#include "CRelations.h"
#include "CObjectDefinitions.h"
#include "CValueDefinitions.h"

#include <iostream>
#include "FEnviroment.h"

namespace VM {
    std::string toString(CRelationInstance *val);

    EqualsResul isEqual_val(CValue *c1, CValue *c2);

    EqualsResul isEqual(CGenericValue *c1, CGenericValue *c2);

    EqualsResul isEqual(CGenericKind *c1, CGenericKind *c2);

    EqualsResul isEqual(CRelationInstance *c1, CRelationInstance *c2);


    HRelationDescriptionNode make_relation_node(std::string _name, HObjectKind _kind) {
        HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNode>(_name,
                                                                                  std::static_pointer_cast<CGenericKind>(
                                                                                          _kind));
        return val;
    }

    HRelationDescriptionNode make_relation_node_various(std::string _name, HObjectKind _kind) {
        HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNodeMany>(_name,
                                                                                      std::static_pointer_cast<CGenericKind>(
                                                                                              _kind));
        return val;
    }

    HRelationDescriptionNode make_relation_node(std::string _name, HValueKind _kind) {
        HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNode>(_name,
                                                                                  std::static_pointer_cast<CGenericKind>(
                                                                                          _kind));
        return val;
    }

    HRelationDescriptionNode make_relation_node_various(std::string _name, HValueKind _kind) {
        HRelationDescriptionNode val = std::make_shared<CRelationDescriptionNodeMany>(_name,
                                                                                      std::static_pointer_cast<CGenericKind>(
                                                                                              _kind));
        return val;
    }


    void add_relation_description(FEnviroment *envb, CRelationDescription rel_description) {
        FEnviromentBase *env = envb->getBase();
        {
            env->relations_description.push_back(rel_description);
        }
    }

    CRelationDescription *get_relation_description(FEnviroment *envb, std::string named) {
        FEnviromentBase *env = envb->getBase();
        {
            for (auto it = env->relations_description.begin(); it != env->relations_description.end(); ++it) {
                if (it->named == named) {
                    return &(*it);
                }
            }
        }
        return nullptr;
    }

    bool isAlowedToNode(FEnviroment *envb, HRelationDescriptionNode node, HGenericValue val) {
        CRelationDescriptionNodeMany *nodeMany = dynamic_cast<CRelationDescriptionNodeMany *>(node.get());
        if (nodeMany) {
            // TODO
        }

        return isInstanceOf(val.get(), node->vkind.get());
    }


    CRelationInstance *
    find_relation_i_1(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1) {
        FEnviromentBase *env = envb->getBase();
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (it->relDesc->named == relation_description->named) {
                if (isEqual(it->item1.get(), val1.get()) == Equals) {

                    return &(*it);
                }
            }
        }
        return nullptr;
    }


    std::list<HGenericValue>
    find_relation_list_1(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1) {
        FEnviromentBase *env = envb->getBase();
        std::list<HGenericValue> values;
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (it->relDesc->named == relation_description->named) {

                if (isEqual(it->item1.get(), val1.get()) == Equals) {
                    values.push_back(it->item2);
                }

            }
        }
        return values;
    }


    std::list<HGenericValue>
    find_relation_list_2(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val2) {
        FEnviromentBase *env = envb->getBase();
        std::list<HGenericValue> values;
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (it->relDesc->named == relation_description->named) {
                if (isEqual(it->item2.get(), val2.get()) == Equals) {
                    values.push_back(it->item1);
                }
            }
        }
        return values;
    }


    CRelationInstance *
    find_relation_i_2(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val2) {
        FEnviromentBase *env = envb->getBase();
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (it->relDesc->named == relation_description->named) {
                if (isEqual(it->item2.get(), val2.get()) == Equals) {
                    //   std::cout << "Equals? " << toString(it->item2) << " == " << toString(val2) << std::endl;
                    return &(*it);
                }
            }
        }
        return nullptr;
    }


    CRelationInstance *
    find_relation_i_any(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val) {
        CRelationInstance *p = find_relation_i_1(envb, relation_description, val);
        if (p != nullptr) return p;
        p = find_relation_i_2(envb, relation_description, val);
        if (p != nullptr) return p;
        return nullptr;
    }

    CRelationInstance *
    find_relation_i(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1,
                    HGenericValue val2) {
        FEnviromentBase *env = envb->getBase();
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (it->relDesc->named == relation_description->named) {
                if (isEqual(it->item1.get(), val1.get()) == Equals)
                    if (isEqual(it->item2.get(), val2.get()) == Equals) {
                        return &(*it);
                    }
            }
        }
        return nullptr;
    }


    void delete_relation(FEnviroment *envb, CRelationInstance *inst) {
        if (inst == nullptr) return;
        FEnviromentBase *env = envb->getBase();
        for (auto it = env->relation_instances.begin(); it != env->relation_instances.end(); ++it) {
            if (isEqual(&(*it), inst) == Equals) {
                it = env->relation_instances.erase(it);
                if (it == env->relation_instances.end()) break;
            }
        }
    }


    void unset_relation(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1,
                        HGenericValue val2) {
        FEnviromentBase *env = envb->getBase();
        //Acha a relacao corrent
        auto p = find_relation_i(envb, relation_description, val1, val2);
        delete_relation(env, p);
    }


    HValue make_joined_list(std::list<HGenericValue> &list1, std::list<HGenericValue> &list2);

    HGenericValue
    get_relation_to(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue from_val) {
        if (relation_description->node1->isMany()) {
            auto plist = find_relation_list_1(envb, relation_description, from_val);
            if (relation_description->symmetric) {
                auto plist_2 = find_relation_list_2(envb, relation_description, from_val);
                return make_joined_list(plist, plist_2);
            }
            return make_list_value(plist);
        }

        auto p = find_relation_i_1(envb, relation_description, from_val);
        if (p != nullptr) return p->item2;

        if (relation_description->symmetric) {
            p = find_relation_i_2(envb, relation_description, from_val);
            if (p != nullptr) return p->item1;
        }
        return nullptr;


    }


    HGenericValue
    get_relation_from(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue to_val) {


        //FEnviromentBase* env = envb->getBase();

        if (relation_description->node1->isMany()) {
            auto plist = find_relation_list_2(envb, relation_description, to_val);
            return make_list_value(plist);
        }
        //Acha a relacao corrent
        auto p = find_relation_i_2(envb, relation_description, to_val);
        if (p != nullptr) return p->item1;
        if (relation_description->symmetric) {
            p = find_relation_i_2(envb, relation_description, to_val);
            if (p != nullptr) return p->item2;
        }
        return nullptr;

    }


    void set_relation(FEnviroment *envb, CRelationDescription *relation_description, HGenericValue val1,
                      HGenericValue val2) {
        FEnviromentBase *env = envb->getBase();
        if (isAlowedToNode(env, relation_description->node1, val1))
            if (isAlowedToNode(env, relation_description->node2, val2)) {

                if (relation_description->node1->isMany() == false) {
                    auto p = find_relation_i_1(envb, relation_description, val1);
                    delete_relation(env, p);
                }

                if (relation_description->node2->isMany() == false) {
                    auto p = find_relation_i_2(envb, relation_description, val2);
                    delete_relation(env, p);
                }

                env->relation_instances.push_back(CRelationInstance(relation_description, val1, val2));
                return;
            }
        throw "unable to create relation instance";
    }


}