//
//  HashFirst.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/24/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"

using namespace std;

HashFirst::HashFirst(unsigned int b) {
    this->tableBUCKET = b;
    table = new list<positionPlusSixKmer*>[tableBUCKET];
}

HashFirst::~HashFirst() {
    for (unsigned int i = 0; i < this->tableBUCKET; i += 1) {
        for (auto content : this->table[i]) {
            delete content;
        }
    }
}
      
void HashFirst::insertItem(std::string insertedElement, positionPlusSixKmer *obj) {
    //cout << insertedElement << endl;
    unsigned int index = hashFunction(insertedElement);
    table[index].push_back(obj);
    this->firstSize += 1;
}

unsigned int HashFirst::getTableSize() {
    return this->firstSize;
}

