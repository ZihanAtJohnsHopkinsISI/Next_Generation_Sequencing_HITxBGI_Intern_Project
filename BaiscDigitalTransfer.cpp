//
//  BaiscDigitalTransfer.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/21/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include "BaiscDigitalTransfer.hpp"
#include <string>
#include <stdlib.h>
using namespace std;


unsigned int binaryToDecimal(std::string n) {
    std::string num = n;
    unsigned int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    unsigned int base = 1;
 
    unsigned int len = num.size(); // usually set to be 40
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}


std::string decideDigit(char character) {
    if (character == 'A') {
        return "00";
    }
    else if (character == 'C') {
        return "01";
    }
    else if (character == 'G') {
        return "10";
    }
    else {
        return "11";
    }
}

int chooseRandom(int ceil) { // ceil must be 4;
    //srand (time(NULL));
    int randomizedNumber = rand();
    int chosedResult = randomizedNumber % ceil + 1;
    return chosedResult;
}


char digitToLetter(int chosedResult) {
    if (chosedResult == 1) {
        return 'A';
    }
    else if (chosedResult == 2) {
        return 'C';
    }
    else if (chosedResult == 3) {
        return 'G';
    }
    else {
        return 'T';
    }
}



