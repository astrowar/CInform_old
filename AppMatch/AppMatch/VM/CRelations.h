#pragma once
#ifndef _CDEFRELATIONS_H
#define _CDEFRELATIONS_H

#include <string>
#include "ConstDefinitions.h"

namespace VM {

    //Complex thing RELATIONS
    class CRelationDescriptionNode {
    public:
        CRelationDescriptionNode(std::string _named, HGenericKind _kind);

        virtual ~CRelationDescriptionNode() {}

        virtual bool isMany() { return false; };

        virtual bool isGroup() { return false; };
        std::string named;
        HGenericKind vkind;
    };

    using HRelationDescriptionNode = std::shared_ptr<CRelationDescriptionNode>;

    class CRelationDescriptionNodeGroup : public CRelationDescriptionNode {
    public:
        CRelationDescriptionNodeGroup(std::string _named, HGenericKind _kind);

        virtual bool isMany() override { return false; };

        virtual bool isGroup() override { return true; }
    };

    class CRelationDescriptionNodeMany : public CRelationDescriptionNode {
    public:
        CRelationDescriptionNodeMany(std::string _named, HGenericKind _kind);

        virtual bool isMany() override { return true; };

        virtual bool isGroup() override { return false; }
    };


    // Relations per Se

    class CRelationDescription {
    public:
        CRelationDescription(std::string _named, HRelationDescriptionNode _node1, HRelationDescriptionNode _node2,
                             bool _symmetric = false);

        HRelationDescriptionNode node1, node2;
        std::string named;
        bool symmetric;
    };

    class CRelationInstance {
    public:
        CRelationInstance(CRelationDescription *_relDesc, HGenericValue val, HGenericValue val2);

        CRelationDescription *relDesc;
        HGenericValue item1;
        HGenericValue item2;
    };


}

#endif
