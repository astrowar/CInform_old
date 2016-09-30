//
// Created by eraldo.rangel on 30/09/2016.
//

#include "CDataMananger.h"





template<class Archive>
void CDataMananger::save(Archive &ar) const {
    ar( blocks );
}

template<class Archive>
void CDataMananger::load(Archive &ar) {
    blocks.clear();
    ar( blocks );
}


