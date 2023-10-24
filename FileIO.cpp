//
//  FileIO.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/27/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"
   

FileIO::FileIO(string inputFile, string outputFile, int target) {
    this->inputFile = inputFile;
    this->outputFile = outputFile;
    switch (target) {
        case 1: {
            FILE *input = fopen(this->inputFile.c_str(), "r");
            fstream output;
            output.open(this->outputFile, std::ios::out);
            if (input == nullptr) {
                cerr << "Invalid input" << endl;
            }
            else {
                int c;
                string letterList = "";
                while ((c = fgetc(input)) != EOF) {
                    char transferedLetter = 's';
                    // Check new line character;
                    if (c == '\n') {
                        int checkEnd = fgetc(input);
                        if (checkEnd != EOF) {
                            c = checkEnd;
                        }
                        else {
                            break;
                        }
                    }
                    
                    // Randomized choose digit from letter
                    if (c == 'N') {
                        c = chooseRandom(4);
                        transferedLetter = digitToLetter(c);
                        c = transferedLetter;
                    }
                    else {
                        transferedLetter = c;
                    }
                    output.put(c);
                }
                output.close();
            }
            break;
        }
    }
    
}
    
FileIO::~FileIO() {
    
}
    
string FileIO::getOutputFile() {
    return this->outputFile;
}

