//
//  Set.hpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 6/21/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

/*
 * This file includes all fuction declarations and objective classes
 * that being used in the DNA Index.
 */

#ifndef SET_H
#define SET_H
#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "BaiscDigitalTransfer.hpp"
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <cstdlib>


using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::fstream; using std::priority_queue;
using std::list; using std::ofstream;


class positionPlusSixKmer {
  
public:
    /*
     * position is the kmer starting position on the reference sequence
     * sixKmer is the string of the last six length kmer
     */
    unsigned int position;
    
    std::string sixKmer;
    
    positionPlusSixKmer(unsigned int position, std::string sixKmer);
    
    
    unsigned int getPosition() const;
    
    std::string getSixKmer();
    
    /*
     * Overload the comparator < which decide the if one obj is smaller
     * than another
     */
    bool operator<(const positionPlusSixKmer& other);

};

/*
 * Secondary hashtable
 */
class HashSecond {
    unsigned int tableBUCKET;    // No. of buckets
  
    // Pointer to an array containing buckets
    std::list<positionPlusSixKmer*> *table;
    
    unsigned int index;
    
    public:
        HashSecond(unsigned int V);  // Constructor
    
        ~HashSecond();
  
        /*
         * Insert an element with starting point
         */
        void insertItem(positionPlusSixKmer *secondPart);
  
        /*
         * binary to decimal is the hash key
         */
        int hashFunction(string kmer) {
            return binaryToDecimal(kmer);
        }
  
        void displayHash();
    
        /*
        * Get the list at certain index
        */
        std::list<positionPlusSixKmer*> getListAtIndex(unsigned int index) {
            return this->table[index];
        }
    
};


/*
 * First half hashtable
 */
class HashFirst {
    
    unsigned int tableBUCKET;    // No. of buckets 2^30
    
    // Pointer to an array containing buckets
    std::list<positionPlusSixKmer*> *table;
      
    unsigned int firstSize;
    
      public:
        HashFirst(unsigned int V);  // Constructor 2^30
    
    
        ~HashFirst();
        /*
        * Insert an element with starting point
        */
        void insertItem(string insertedElement, positionPlusSixKmer *obj);
    
        /*
        * binary to decimal is the hash key
        */
        int hashFunction(string kmer) {
            return binaryToDecimal(kmer);
        }
    
        /*
         * Get the list at certain index
         */
        std::list<positionPlusSixKmer*> getListAtIndex(unsigned int index) {
            return this->table[index];
        }
    
        unsigned int getTableSize();
            
};


/*
 * Create a table with first and secondary table for reference
 * DNA sequence
 */
class TwoChainTable {
  
public:
    
    /*
     * 14 and 6 Kmer partial table
     */
    HashFirst *fourtheenKmerLengthTable;
    HashSecond *sixKmerLenthTable;

    TwoChainTable(FILE *fileName);
    
    ~TwoChainTable();
    
    //unsigned int findPostion();
    
};


/*
 * Overload the compare rule of priority queue
 * Compare the decimal value from the positionPlusSixKmer for last
 * six kmer length
 */
class keyPrtComp {
    public:

        bool operator()(positionPlusSixKmer*& lhs, positionPlusSixKmer*& rhs) const;
};


/*
 * This class is to initialize all file with invalid character
 */
class FileIO {
   
    string inputFile;
    string outputFile;
    
    public:
    
        /*
         * inputFile is the file wait to be read
         * outputFile is the file wait to be write
         * target is the rules to decide the way to construct the object
         */
        FileIO(string inputFile, string outputFile, int target);
    
        ~FileIO();
    
        string getOutputFile();
};


/*
 * Query stores the reference position and query position with a
 * default query length 20.
 */
class Query {
    
    unsigned int queryPosition;
    unsigned int referencePosition;
    unsigned int length;  // Usually length set to be 20
    
    public:
        Query(unsigned int q, unsigned int r, unsigned int length);
    
        unsigned int getQueryPosition();
    
        unsigned int getReferencePosition();
    
        bool checkSameGroup(Query* rhs);
    
};


/*
 * Overload the compare rule of priority queue
 * Compare the decimal value from the positionPlusSixKmer for last
 * six kmer length
 */
class queryPrtComp {

    public:
       
    bool operator()(Query*& lhs, Query*& rhs) const;
    
};


/*
 * Remove function that used in the priority_queue, which should be used
 * under same type.
 */
priority_queue<Query*, vector<Query*>,queryPrtComp>
    remove(Query* removedElement,priority_queue<Query*,
           vector<Query*>,queryPrtComp> pq);


/*
 * Gather all valid NGS groups that can find in the reference sequence
 * The instance variable will be furtherly verrified if its element can be
 * integrated into a graph.
 *
 * This step will be implemeted in seperate files
 */
class NGSGroup {
    
    priority_queue<Query*, std::vector<Query*>, queryPrtComp> queryGroup;
    
    public:
    
        NGSGroup(string NGSFile, TwoChainTable *indexTable);
    
        ~NGSGroup();
    
        priority_queue<Query*, vector<Query*>, queryPrtComp> getQueue();
    
};


/*
 * The queryPqPtrCompHelper associalte with queryPqPtrComp which helps to
 * practicize the function such that the priority_queue<priority_queue>
 * It overload the priority_queue which stores the graph node in certain
 * sequence.
 *
 * Type with priority_queue<Query*, vector<Query*>,queryPrtComp>
 * Instance variable is a priority_queue with above type. 
 */
class queryPqPtrCompHelper {
    
    priority_queue<Query*, vector<Query*>,queryPrtComp> pq;
    
    public:
    
    queryPqPtrCompHelper(priority_queue<Query*, vector<Query*>,queryPrtComp> pq);
    
    priority_queue<Query*, vector<Query*>,queryPrtComp> getPq();
};


class queryPqPtrComp {
  
    public:
    
    bool operator() (queryPqPtrCompHelper*& lhs,
        queryPqPtrCompHelper*& rhs) const;
    
};


/*
 * Craft a graph with instance variable list<list<Query*>> mappingList
 * list<Query*> source, list<Query*> sink.
 *
 */
class referencialPositionGraph {
    list<list<Query*>> mappingList;
    list<Query*> source;
    list<Query*> sink;
    
public:
    
    referencialPositionGraph(
        priority_queue<Query*, vector<Query*>, queryPrtComp> queryGroups);
        
    ~referencialPositionGraph();
    
    list<list<Query*>> getMappingList();
    
    list<Query*> getSource();
    
    list<Query*> getSink();
    
    unsigned int getSourceStartPostion();
    
    unsigned int getSinkEndPosition();
};

#endif
