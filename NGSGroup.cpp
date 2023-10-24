//
//  NGSGroup.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/28/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"

const unsigned int NGS_KMER_LENGTH = 20;
unsigned int NGS_FIRST_FOURTEEN = 14;
unsigned int NGS_REST = 6;


NGSGroup::NGSGroup(string NGSFile, TwoChainTable *indexTable) {
    ifstream NGSinput(NGSFile);

    string ngsList_1;
    while (getline(NGSinput, ngsList_1)) {

        for (unsigned int i = 0; i < ngsList_1.size(); i += 1) {
            if (ngsList_1[i] == 'N') {
                int randomizedNumber = chooseRandom(4);
                char correspondingLetter = digitToLetter(randomizedNumber);
                ngsList_1[i] = correspondingLetter;
            }
        }

        for (unsigned int NGSIndex = 0;
             NGSIndex + NGS_KMER_LENGTH - 1 < ngsList_1.size(); NGSIndex += 1) {
            std::string firstNGSKmerPart = ngsList_1
                .substr(NGSIndex, NGS_FIRST_FOURTEEN);
            std::string secondNGSKmerPart = ngsList_1
                .substr(NGSIndex + NGS_FIRST_FOURTEEN, NGS_REST);

            std::string firstNGSDigitalString = "";
            std::string secondNGSDigitalString = "";
            for (int i = 0; i < firstNGSKmerPart.size(); i += 1) {
                firstNGSDigitalString += decideDigit(firstNGSKmerPart.at(i));
            }
            for (int i = 0; i < secondNGSKmerPart.size(); i += 1) {
                secondNGSDigitalString += decideDigit(secondNGSKmerPart.at(i));
            }

            // Check exist in the first table
            if (indexTable->fourtheenKmerLengthTable
                ->getListAtIndex(binaryToDecimal(firstNGSDigitalString))
                    .size() != 0) {

                std::list<positionPlusSixKmer*> currentList
                    = indexTable->fourtheenKmerLengthTable
                    ->getListAtIndex(binaryToDecimal(firstNGSDigitalString));
                
                for (auto content: currentList) {
                    if (content->getSixKmer() == secondNGSDigitalString) {
                        
                        // Create query
                        Query *currentQuery
                            = new Query(NGSIndex,content->getPosition(),
                                NGS_KMER_LENGTH);
                        this->queryGroup.push(currentQuery);
                    }
                }
            }
        }
    }
    NGSinput.close();
}


NGSGroup::~NGSGroup() {
    unsigned long size = this->queryGroup.size();
    for (unsigned long i = 0; i < size; i += 1) {
        Query *curr = this->queryGroup.top();
        delete curr;
        queryGroup.pop();
    }
}


priority_queue<Query*, vector<Query*>, queryPrtComp> NGSGroup::getQueue() {
    return this->queryGroup;
}
