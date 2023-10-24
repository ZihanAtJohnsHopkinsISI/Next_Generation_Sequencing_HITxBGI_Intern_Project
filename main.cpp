//
//  main.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/15/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//


#include <vector>
#include "BaiscDigitalTransfer.hpp"
#include "Set.hpp"

unsigned int COMPLETE_LENGTH = 20;


int main(int argc, const char * argv[]) {
    
    string originFile = "/Users/starkzihanqu/desktop/Programing/DNASequenceAlignment/DNASequenceAlignment/DNASequenceAlignment/hs37d5_22.fa";
    string output = "/Users/starkzihanqu/desktop/Programing/DNASequenceAlignment/DNASequenceAlignment/DNASequenceAlignment/output.txt";
    FileIO *input = new FileIO(originFile, output, 1);

    string in(input->getOutputFile());
    ofstream out("/Users/starkzihanqu/desktop/output.txt");
    FILE* inf = fopen(in.c_str(), "r");
    TwoChainTable *t = nullptr;
    if (inf != nullptr) {
      t = new TwoChainTable(inf);
    }

    /*
     * Now we are going to dispose the query which find the reletaive
     * position on both reference list and NGS list
     */

    // Here Below is the NGS sequence
    // Also we suppose that the NGS file is exist
    string NGS_1("/Users/starkzihanqu/desktop/Programing/DNASequenceAlignment/DNASequenceAlignment/DNASequenceAlignment/NGS1.txt");
    NGSGroup *ngs = new NGSGroup(NGS_1, t);

//    /* Test code start here */
    unsigned int size = ngs->getQueue().size();
    priority_queue<Query*, vector<Query*>, queryPrtComp> test = ngs->getQueue();
    
    referencialPositionGraph *p = new referencialPositionGraph(test);
//    ifstream NGSinput(NGS_1);
//    string ngsList_1;
//    getline(NGSinput, ngsList_1);
//    ifstream RefInput(output);
//    string refString;
//    getline(RefInput, refString);
    
    cout << "start get result" << endl;
    
    int index = 0;
    // Display the graph
    list<list<Query*>> mapping = p->getMappingList();
    while (mapping.size() != 0) {
        list<Query*> currGroup = mapping.front();
        ifstream NGSinput(NGS_1);
        string ngsList_1;
        getline(NGSinput, ngsList_1);
        ifstream RefInput(output);
        string refString;
        getline(RefInput, refString);
        
        // Get first last
        unsigned int startQueryPosition = currGroup.back()->getQueryPosition();
        unsigned int startReferencePostion = currGroup.back()->getReferencePosition();
        mapping.pop_front();

        if (mapping.size() != 0) {

            // Get second first;
            list<Query*> nextGroup = mapping.front();
//            mapping.pop_front();
            unsigned int endQueryPosition = nextGroup.front()->getQueryPosition();
            unsigned int endReferencePosition = nextGroup.front()->getReferencePosition();
            if (abs((int)startReferencePostion - (int)endReferencePosition) <= 100000) {
                if (startQueryPosition > endQueryPosition) {
                    out << "start: ";
                    out << endQueryPosition;
                    out << "end: ";
                    out << startQueryPosition << endl;
                    out << ngsList_1
                    .substr(endQueryPosition,
                            startQueryPosition
                            - endQueryPosition + COMPLETE_LENGTH) << endl;
                    out << "Compare to: " << endl;
                    if (startReferencePostion > endReferencePosition) {
                        out << refString
                        .substr(endReferencePosition, startReferencePostion
                                - endReferencePosition + COMPLETE_LENGTH) << endl;
                    }
                    else if (startReferencePostion <= endReferencePosition) {
                        out << refString
                        .substr(startReferencePostion, endReferencePosition
                                - startReferencePostion + COMPLETE_LENGTH) << endl;
                    }

                }
                else {
                    out << "start: ";
                    out << startQueryPosition;
                    out << "end: ";
                    out << endQueryPosition << endl;
                    out << ngsList_1
                    .substr(startQueryPosition, endQueryPosition
                            - startQueryPosition + COMPLETE_LENGTH) << endl;
                    out << "Compare to: " << endl;
                    if (startReferencePostion > endReferencePosition) {
                        out << refString
                        .substr(endReferencePosition, startReferencePostion
                                - endReferencePosition + COMPLETE_LENGTH) << endl;
                    }
                    else if (startReferencePostion <= endReferencePosition) {
                        out << refString
                        .substr(startReferencePostion, endReferencePosition
                                - startReferencePostion + COMPLETE_LENGTH) << endl;
                    }
                }
            }
            
        }
//        index += 1;
//        if (index == 3) {
//            break;
//        }
        // get 1 pair;
    }

    fclose(inf);


}
