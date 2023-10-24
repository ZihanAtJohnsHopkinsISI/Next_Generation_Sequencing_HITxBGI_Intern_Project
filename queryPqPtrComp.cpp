//
//  queryPqPtrComp.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 7/4/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"


/*
 * Reload the priority_queue
 * Need to pay attention to the
 */
bool queryPqPtrComp::operator()(queryPqPtrCompHelper*& lhs,
        queryPqPtrCompHelper*& rhs) const {
    
    priority_queue<Query*, vector<Query*>, queryPrtComp> currLhs = lhs->getPq();
    priority_queue<Query*, vector<Query*>, queryPrtComp> currRhs = rhs->getPq();

    Query *lastLhs = (&currLhs)->top();
    Query *lastRhs = (&currRhs)->top();


    return lastLhs->getReferencePosition() > lastRhs->getReferencePosition();
}


queryPqPtrCompHelper::queryPqPtrCompHelper(priority_queue<Query*, vector<Query*>,queryPrtComp> pq) {
    this->pq = pq;
}

priority_queue<Query*, vector<Query*>,queryPrtComp> queryPqPtrCompHelper::
    getPq() {
    return this->pq;
}



