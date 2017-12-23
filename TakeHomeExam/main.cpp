//
// Created by sbk on 20.12.2017.
//

#include <fstream>
#include <iostream>
#include "Adjacency.h"
#include "Deliver.h"
#include <queue>

# define INFINITY 0x3f3f3f3f
using namespace std;

struct myGreater {
    bool operator()(const AdjacencyNode &a, const AdjacencyNode &b) {

        return a.weight > b.weight;
    }
};

void djikstraShortestPath(const int wareHouse, const vector<Adjacency> &adjacencyList,
                          vector<int> &distance) {
    int w, i, visW, visV, size;
    priority_queue<AdjacencyNode, vector<AdjacencyNode>, myGreater> priorityQueue;


    AdjacencyNode adjacencyNode;
    adjacencyNode.destination = wareHouse;
    adjacencyNode.weight = 0;
    priorityQueue.push(adjacencyNode);

    distance[wareHouse] = 0;
    while (!priorityQueue.empty()) {
        w = priorityQueue.top().destination;
        priorityQueue.pop();

        size = adjacencyList[w].size;

        for (i = 0; i < size; ++i) {
            visW = adjacencyList[w].adjacencyNodes[i].weight;
            visV = adjacencyList[w].adjacencyNodes[i].destination;

            if (distance[visV] > distance[w] + visW) {
                distance[visV] = distance[w] + visW;

                adjacencyNode.destination = visV;
                adjacencyNode.weight = distance[visV];
                priorityQueue.push(adjacencyNode);
            }
        }

    }
}

int main(int argc, char *argv[]) {

    vector<Adjacency> adjacencyList;
    Adjacency adjacency;
    AdjacencyNode adjacencyNode;
    vector<int> wareHouse;
    vector<Deliver> destination;
    int cityCounter = 0;
    int destinationCounter = 0;
    int i = 0, k, j, h, l, difference, min, minIndex, sum;
    int index = 0;
    string filename = argv[1];
    ifstream file;
    file.open(filename);


    while (!file.eof()) {
        if (i == 0) {
            // first line
            file >> index;
            cityCounter = index;
            for (j = 0; j < index; ++j) {
                adjacencyList.push_back(adjacency);
            }

            i++;
            continue;
        } else if (i == 1) {
            //second line

            file >> index;
            destinationCounter = index;

            i++;
            continue;
        } else if (i == 2) {
            for (j = 0; j < 2; ++j) {
                file >> index;
                wareHouse.push_back(index);
            }

            i++;
            continue;
        } else if (i == 3) {
            for (j = 0; j < destinationCounter; ++j) {
                file >> index;
                Deliver deliver;
                deliver.destionationNo = index;
                destination.push_back(deliver);
            }

            i++;
            continue;
        } else {
            for (h = 0; h < cityCounter; ++h) {
                for (j = 0; j < cityCounter; ++j) {
                    file >> index;
                    if (index == 0) {
                        continue;
                    } else {

                        adjacencyList[h].size++;
                        adjacencyNode.weight = index;
                        adjacencyNode.destination = j;
                        adjacencyList[h].adjacencyNodes.push_back(adjacencyNode);

                    }
                }
            }

            break;
        }

    }

    vector<int> distance1(cityCounter, INFINITY);
    vector<int> distance2(cityCounter, INFINITY);
    djikstraShortestPath(wareHouse[0], adjacencyList, distance1);
    djikstraShortestPath(wareHouse[1], adjacencyList, distance2);


    int countWareHouse1 = 0;
    for (int k = 0; k < destinationCounter; ++k) {
        if (distance1[destination[k].destionationNo] > distance2[destination[k].destionationNo]) {
            destination[k].wareHouseNo = wareHouse[1];
            destination[k].diff = distance1[destination[k].destionationNo] - distance2[destination[k].destionationNo];
        } else {
            countWareHouse1++;
            destination[k].wareHouseNo = wareHouse[0];
            destination[k].diff = distance2[destination[k].destionationNo] - distance1[destination[k].destionationNo];

        }
    }

    if (countWareHouse1 > (destinationCounter / 2)) {
        //warehouse 1 daha fazla
        difference = countWareHouse1 - (destinationCounter / 2);
        for (j = 0; j < difference; ++j) {
            min = INFINITY;
            minIndex = 0;
            for (k = 0; k < destinationCounter; ++k) {
                if ((destination[k].wareHouseNo == wareHouse[0]) && (destination[k].diff < min)) {
                    min = destination[k].diff;
                    minIndex = k;
                }
            }

            destination[minIndex].wareHouseNo = wareHouse[1];

        }
    } else if (countWareHouse1 < (destinationCounter / 2)) {
        //warehouse 2 daha fazla
        difference = (destinationCounter - countWareHouse1) - (destinationCounter / 2);
        for (j = 0; j < difference; ++j) {
            min = INFINITY;
            minIndex = 0;
            for (k = 0; k < destinationCounter; ++k) {
                if ((destination[k].wareHouseNo == wareHouse[1]) && (destination[k].diff < min)) {
                    min = destination[k].diff;
                    minIndex = k;
                }
            }

            destination[minIndex].wareHouseNo = wareHouse[0];
        }
    }

    sum = 0;
    for (l = 0; l < destinationCounter; ++l) {
        if (destination[l].wareHouseNo == wareHouse[0]) {
            sum += distance1[destination[l].destionationNo];
        } else {
            sum += distance2[destination[l].destionationNo];
        }
    }


    cout << sum << endl;
    for (l = 0; l < destinationCounter; ++l) {
        cout << destination[l].destionationNo << " " << destination[l].wareHouseNo << endl;
    }

    return 0;
}
