//
//  queryPtrComp.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/27/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"


bool queryPrtComp::operator()(Query*& lhs, Query*& rhs) const {
      if (lhs->getQueryPosition() == rhs->getQueryPosition()) {
          return lhs->getReferencePosition() > rhs->getReferencePosition();
      }
      else {
          return lhs->getQueryPosition() > rhs->getQueryPosition();
      }
}


priority_queue<Query*, vector<Query*>,queryPrtComp>
    remove(Query* removedElement,
           priority_queue<Query*, vector<Query*>,queryPrtComp> pq) {
    
    priority_queue<Query*, vector<Query*>,queryPrtComp> copy = pq;
    priority_queue<Query*, vector<Query*>,queryPrtComp> paste;
    
    while (copy.size() != 0) {
        Query *curr = copy.top();
        if (curr->getQueryPosition() != removedElement->getQueryPosition()
            || curr->getReferencePosition() != removedElement->getReferencePosition()) {
            paste.push(curr);
        }
        copy.pop();
    }
    return paste;
}
