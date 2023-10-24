//
//  BaiscDigitalTransfer.hpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/21/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#ifndef BaiscDigitalTransfer_hpp
#define BaiscDigitalTransfer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>


/*
 * decide the input to corresponding binary number
 */
std::string decideDigit(char character);

/*
 * choosed randomized digit when character is N, and convert
 * into corresponding binary number
 */
int chooseRandom(int ceil);

/*
 * transfer a binary to a decimal
 */
unsigned int binaryToDecimal(std::string n);

/*
 * Transfer a number to corresponding char 
 */
char digitToLetter(int chosedResult);
 


#endif /* BaiscDigitalTransfer_hpp */
