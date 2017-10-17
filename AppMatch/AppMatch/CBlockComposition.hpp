//
// Created by eraldo.rangel on 17/10/2017.
//

#ifndef APPMATCH_CBLOCKKINDCOMPOSITION_H
#define APPMATCH_CBLOCKKINDCOMPOSITION_H

#include "BlockInterpreter.hpp"

namespace CBlocking {
    class CBlockComposition : public CBlockKind {

    public:
        //void dump(string ident) override;
        virtual bool isValue() override { return true; }
        CBlockComposition(string named ) : CBlockKind(named) { }
        virtual BlockType type() override { return BlockType::BlockComposition; }
    };
    using HBlockComposition = std::shared_ptr<CBlockComposition>;



    class CBlockCompositionList : public CBlockComposition {

    public:
        HBlockKind itemKind;
        CBlockCompositionList( HBlockKind _itemKind ) : CBlockComposition("list of "+_itemKind->named), itemKind(_itemKind)
        {

        }
        void dump(string ident) override;
        BlockType type() override { return BlockType::BlockCompositionList; }
    };
    using HBlockCompositionList = std::shared_ptr<CBlockCompositionList>;



    // relation of K to L
    class CBlockCompositionRelation : public CBlockComposition
    {
    public:
        HBlockKind fromKind;
        HBlockKind toKind;
        CBlockCompositionRelation( HBlockKind _fromKind , HBlockKind _toKind  ) :CBlockComposition("relation of "+_fromKind->named+" to "+_toKind->named),
                toKind(_toKind) , fromKind(_fromKind)
                {

                }

        void dump(string ident) override;
          BlockType type() override { return BlockType::BlockCompositionRelation; }
    };
    using HBlockCompositionRelation = std::shared_ptr<CBlockCompositionRelation>;




    // phrase K -> L
    class CBlockCompositionPhrase : public CBlockComposition {

    public:
        HBlockKind fromKind;
        HBlockKind toKind;
        CBlockCompositionPhrase( HBlockKind _fromKind , HBlockKind _toKind  ) : CBlockComposition("phrase "+_fromKind->named+" -> "+_toKind->named) ,toKind(_toKind) , fromKind(_fromKind)
        {

        }
       virtual void dump(string ident) override;
          BlockType type() override { return BlockType::BlockCompositionPhrase; }
    };
    using HBlockCompositionPhrase = std::shared_ptr<CBlockCompositionPhrase>;
}
#endif //APPMATCH_CBLOCKKINDCOMPOSITION_H
