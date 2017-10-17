//
// Created by eraldo.rangel on 17/10/2017.
//

#ifndef APPMATCH_CBLOCKKINDCOMPOSITION_H
#define APPMATCH_CBLOCKKINDCOMPOSITION_H

#include "BlockInterpreter.hpp"

namespace CBlocking {
    class CBlockKindComposition : public CBlockKind {

    public:
        void dump(string ident) override;
        virtual bool isValue() override { return true; }
        CBlockKindComposition(string named ) : CBlockKind(named) { }
        virtual BlockType type() override { return BlockType::BlockKindComposition; }
    };
    using HBlockKindComposition = std::shared_ptr<CBlockKindComposition>;



    class CBlockKindCompositionList : public CBlockKindComposition {

    public:
        HBlockKind itemKind;
        CBlockKindCompositionList( HBlockKind _itemKind ) : CBlockKindComposition("list of "+_itemKind->named), itemKind(_itemKind)
        {

        }
        void dump(string ident) override;
          BlockType type() override { return BlockType::BlockKindCompositionList; }
    };
    using HBlockKindCompositionList = std::shared_ptr<CBlockKindCompositionList>;



    // relation of K to L
    class CBlockKindCompositionRelation : public CBlockKindComposition
    {
    public:
        HBlockKind fromKind;
        HBlockKind toKind;
        CBlockKindCompositionRelation( HBlockKind _fromKind , HBlockKind _toKind  ) :CBlockKindComposition("relation of "+_fromKind->named+" to "+_toKind->named),
                toKind(_toKind) , fromKind(_fromKind)
                {

                }

        void dump(string ident) override;
          BlockType type() override { return BlockType::BlockKindCompositionRelation; }
    };
    using HBlockKindCompositionRelation = std::shared_ptr<CBlockKindCompositionRelation>;




    // phrase K -> L
    class CBlockKindCompositionPhrase : public CBlockKindComposition {

    public:
        HBlockKind fromKind;
        HBlockKind toKind;
        CBlockKindCompositionPhrase( HBlockKind _fromKind , HBlockKind _toKind  ) : CBlockKindComposition("phrase "+_fromKind->named+" -> "+_toKind->named) ,toKind(_toKind) , fromKind(_fromKind)
        {

        }

       virtual void dump(string ident) override;
          BlockType type() override { return BlockType::BlockKindCompositionPhrase; }
    };
    using HBlockKindCompositionPhrase = std::shared_ptr<CBlockKindCompositionPhrase>;
}
#endif //APPMATCH_CBLOCKKINDCOMPOSITION_H
