//
//  Query.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/27/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"

unsigned int queryThreshold = 20;

Query::Query(unsigned int q, unsigned int r, unsigned int length) {
    this->queryPosition = q;
    this->referencePosition = r;
    this->length = length;
}

unsigned int Query::getQueryPosition() {
    return this->queryPosition;
}

unsigned int Query::getReferencePosition() {
    return this->referencePosition;
}

bool Query::checkSameGroup(Query* rhs) {
    // r1 - q1
    int lhsDifference = this->referencePosition - this->queryPosition;
    // r2 - q2
    int rhsDifference
        = rhs->referencePosition - rhs->queryPosition;
    
    // Check threashold
    if (abs((int)lhsDifference - (int)rhsDifference) <= queryThreshold
            && abs((int)lhsDifference - (int)rhsDifference) >= 0) {
        return true;
    }
    else {
        return false;
    }
}




