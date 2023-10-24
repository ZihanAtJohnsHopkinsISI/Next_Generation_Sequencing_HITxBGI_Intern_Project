//
//  referencialPositionGraph.cpp
//  DNASequenceAlignment
//
//  Created by Zihan Qu on 7/7/21.
//  Copyright © 2021 Zihan Qu. All rights reserved.
//

#include <stdio.h>
#include "Set.hpp"
using namespace std;


referencialPositionGraph::referencialPositionGraph(priority_queue<Query*, vector<Query*>, queryPrtComp> queryGroups) {
    
    priority_queue<queryPqPtrCompHelper*, vector<queryPqPtrCompHelper*>, queryPqPtrComp> totalQueryGroupPq;

    while (queryGroups.size() != 0) {
        // Created a check matched pq with type Query*
        priority_queue<Query*, vector<Query*>, queryPrtComp> findMatchPq = queryGroups;
        findMatchPq.pop();

        priority_queue<Query*, vector<Query*>, queryPrtComp> currQueryGroup;
        Query *currFirstQuery = queryGroups.top();
        while (findMatchPq.size() != 0) {
            Query *find = findMatchPq.top();
            
            // If find matched, then removed the corresponding query in the orginal
            // priority queue
            if (currFirstQuery->checkSameGroup(find) == true) {
                
                // pushed the rest of query, such that A~bs, which is Bs
                currQueryGroup.push(find);
                queryGroups = remove(find, queryGroups);
            }
            findMatchPq.pop();
        }
        
        // push the first relative query, such that A~Bs, which is A
        if (findMatchPq.size() == 0) {
            currQueryGroup.push(currFirstQuery);
        }

        queryPqPtrCompHelper* currPushGroup = new queryPqPtrCompHelper(currQueryGroup);
        totalQueryGroupPq.push(currPushGroup);
        queryGroups.pop();
    }
    
    // Craft the graph
    if (totalQueryGroupPq.size() != 0) {
        priority_queue<Query*, vector<Query*>,queryPrtComp> topGroup
            = totalQueryGroupPq.top()->getPq();
        list<Query*> firstGroup;
        
        // Dispose source
        while (topGroup.size() != 0) {
            firstGroup.push_back(topGroup.top());
            topGroup.pop();
        }
        this->source = firstGroup;
        this->mappingList.push_back(firstGroup);
        totalQueryGroupPq.pop();
        
        // Dispose middle rest
        while (totalQueryGroupPq.size() > 1) {
            priority_queue<Query*, vector<Query*>,queryPrtComp> currGroup
                = totalQueryGroupPq.top()->getPq();
            list<Query*> currList;
            while (currGroup.size() != 0) {
                currList.push_back(currGroup.top());
                currGroup.pop();
            }
            this->mappingList.push_back(currList);
            totalQueryGroupPq.pop();
        }
        
        // Dispose sink
        priority_queue<Query*, vector<Query*>,queryPrtComp> bottomGroup
            = totalQueryGroupPq.top()->getPq();
        list<Query*> lastGroup;
        while (bottomGroup.size() != 0) {
            lastGroup.push_back(bottomGroup.top());
            bottomGroup.pop();
        }
        this->sink = lastGroup;
        this->mappingList.push_back(lastGroup);
        totalQueryGroupPq.pop();
        
        if (totalQueryGroupPq.size() == 0) {
            cout << "Valid" << endl;
        }
        else {
            cout << "Error" << ends;
        }
    }
    
}


referencialPositionGraph::~referencialPositionGraph() {
    while (mappingList.size() != 0) {
        while (mappingList.front().size() != 0) {
            delete mappingList.front().front();
            mappingList.front().pop_front();
        }
    }
}

list<list<Query*>> referencialPositionGraph::getMappingList() {
    return this->mappingList;
}

list<Query*> referencialPositionGraph::getSource() {
    return this->source;
}

list<Query*> referencialPositionGraph::getSink() {
    return this->sink;
}

unsigned int referencialPositionGraph::getSourceStartPostion() {
    if (this->source.size() != 0) {
       return this->source.front()->getReferencePosition();
    }
    else {
        return -1;
    }
    
}

unsigned int referencialPositionGraph::getSinkEndPosition() {
    if (this->sink.size() != 0) {
        return this->sink.back()->getReferencePosition();
    }
    else {
        return -1;
    }
    
}
