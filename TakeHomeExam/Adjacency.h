//
// Created by sbk on 21.12.2017.
//

#ifndef CENG315_ADJACENCY_H
#define CENG315_ADJACENCY_H

#include <iostream>
#include <vector>
#include "AdjacencyNode.h"
using namespace std;

class Adjacency {
public:
    int size;

    vector<AdjacencyNode> adjacencyNodes;

    Adjacency();
};


#endif //CENG315_ADJACENCY_H
