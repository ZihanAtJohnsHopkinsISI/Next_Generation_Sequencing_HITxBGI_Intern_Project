//
//  TwoChainTable.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/24/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include "Set.hpp"


// Macro public static constant
// 4294967294 2^32
// 288435456 2^28
// 1073741824 2^30
unsigned int TABLE_LENGTH = 288435456;
unsigned int SECONDARY_TABLE_LENGTH = 1073741824;
const unsigned int KMER_LENGTH = 20;
unsigned int FIRST_FOURTEEN = 14;
unsigned int REST = 6;

using namespace std;



TwoChainTable::TwoChainTable(FILE *fileName) {
    
    this->fourtheenKmerLengthTable = new HashFirst(TABLE_LENGTH);
    this->sixKmerLenthTable = new HashSecond(SECONDARY_TABLE_LENGTH);
 
    int c;
    std::string referenceList = "";
    while ((c = fgetc(fileName)) != EOF) {
        referenceList += c;
    }

    for (unsigned int index = 0;
         index + KMER_LENGTH - 1 < referenceList.size(); index += 1) {
        
        // Seperate each kmer into 14+6
        std::string firstKmerPart = referenceList.substr(index, FIRST_FOURTEEN);
        std::string secondKmerPart = referenceList
            .substr(index + FIRST_FOURTEEN, REST);

        // Get seperate string for certain sequence
        std::string firstDigitalString = "";
        std::string secondDigitalString = "";
        for (int i = 0; i < firstKmerPart.size(); i += 1) {
            firstDigitalString += decideDigit(firstKmerPart.at(i));
        }
        for (int i = 0; i < secondKmerPart.size(); i += 1) {
            secondDigitalString += decideDigit(secondKmerPart.at(i));
        }

        // index is the position, starting position on reference
        positionPlusSixKmer *currentPositionPlusSixBP
            = new positionPlusSixKmer(index, secondDigitalString);
        
        // established the first table with <key14, pos+6bp>
        fourtheenKmerLengthTable
            ->insertItem(firstDigitalString, currentPositionPlusSixBP);
    }
    
    // Get each positionPlusSixKmer stores in the first table
    for (unsigned int i = 0; i < TABLE_LENGTH; i += 1) {
        std::priority_queue<positionPlusSixKmer*,
            std::vector<positionPlusSixKmer*>, keyPrtComp> pq;
        
        if (fourtheenKmerLengthTable->getListAtIndex(i).size() != 0) {
            
            std::list<positionPlusSixKmer*> currentList = fourtheenKmerLengthTable->getListAtIndex(i);
            for (auto content: currentList) {
                if (content != nullptr) {
                    pq.push(content);
                }
            }
        }
        
        while (pq.size() > 0) {
            positionPlusSixKmer *currentSixKmer = pq.top();
            pq.pop();
            sixKmerLenthTable->insertItem(currentSixKmer);
        }
    }
    
}

TwoChainTable::~TwoChainTable() {
    
}


