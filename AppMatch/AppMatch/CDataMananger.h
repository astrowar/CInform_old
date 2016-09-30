//
// Created by eraldo.rangel on 30/09/2016.
//

#ifndef APPMATCH_CDATAMANANGER_H
#define APPMATCH_CDATAMANANGER_H


#include "BlockInterpreter.h"
#include <map>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>


class CDataMananger {


std::vector<HBlock> blocks;


    template <class Archive>
    void save( Archive & ar ) const;

    template <class Archive>
    void load( Archive & ar );
};






#endif //APPMATCH_CDATAMANANGER_H
