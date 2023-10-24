//
//  postionPlusSixKmer.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/24/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include "Set.hpp"



positionPlusSixKmer::positionPlusSixKmer(unsigned int position, std::string sixKmer) {
    this->position = position;
    this->sixKmer = sixKmer;
}

unsigned int positionPlusSixKmer::getPosition() const {
    return this->position;
}

std::string positionPlusSixKmer::getSixKmer() {
    return this->sixKmer;
}

bool positionPlusSixKmer::operator<(const positionPlusSixKmer& other) {
    return this->sixKmer < other.sixKmer;
}
