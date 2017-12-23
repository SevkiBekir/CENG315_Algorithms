//
// Created by sbk on 21.12.2017.
//

#include "AdjacencyNode.h"

AdjacencyNode::AdjacencyNode() {
    weight = 0;
    destination = 0;

}

AdjacencyNode::AdjacencyNode(int destination, int weight) {
    this->weight = weight;
    this->destination = destination;

}
