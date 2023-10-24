//
//  KeyPtrComp.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/24/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"


bool keyPrtComp::operator()(positionPlusSixKmer*& lhs, positionPlusSixKmer*& rhs) const {
    unsigned int lhsSixBPDigit = binaryToDecimal(lhs->getSixKmer());
    unsigned int rhsSixBPDigit = binaryToDecimal(rhs->getSixKmer());
    return lhsSixBPDigit > rhsSixBPDigit;
}
