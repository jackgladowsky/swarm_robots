// Graph.cpp
#include <iostream>
#include "Graph.h"

Graph::Graph(int numNodes) : numNodes(numNodes) {
    for (int i = 0; i < numNodes; i++) {
        // generate random number between 1 and 10
        int random = rand() % 100 + 1;
        // std::cout << "Random num: " << random << std::endl;
        if (random <= 10) {
            // std::cout << "OBSTACLE" << std::endl;
            nodes.push_back(new GraphNode(i, OBSTACLE)); // 10% chance of being an obstacle 
            this->obsCount++;
        }
        else if(random > 10 && random <= 90) { // 80% chance of being clear
            // std::cout << "CLEAR" << std::endl;
            nodes.push_back(new GraphNode(i, CLEAR));
            this->clrCount++;
        }
        else {
            // std::cout << "OBJECT" << std::endl;
            nodes.push_back(new GraphNode(i, OBJECT)); // 1% chance of being an object
            this->objCount++;
        }
    }

    // set control point
    int controlPoint = rand() % numNodes;
    nodes[controlPoint]->state = CONTROL;

    // set neighbors randomly, each node can have up to 4 neighbors
    // neighbors are not necesarrily adjacent values in the list 
    // but just two nodes that have a connection.
    // connections between nodes must be bidirectional
    // each node must have at least one neighbor
    // the graph must be connected
    // it cannot have more than one connection per neighbor
    for (int i = 0; i < numNodes; i++) {
        int numNeighbors = rand() % 4 + 1;
        for (int j = 0; j < numNeighbors; j++) {
            int neighbor = rand() % numNodes;
            if (neighbor != i) {
                // check if neighbor already exists
                bool exists = false;
                for (int k = 0; k < nodes[i]->neighbors.size(); k++) {
                    if (nodes[i]->neighbors[k]->NodeID == neighbor) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    nodes[i]->neighbors.push_back(nodes[neighbor]);
                    nodes[neighbor]->neighbors.push_back(nodes[i]);
                }
            }
        }
    }

}

// print the entire graph node by node, display each nodes data clearly
// print the neighbors of each node
void Graph::printGraph() {
    for (int i = 0; i < numNodes; i++) {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Node ID: " << nodes[i]->NodeID << std::endl;
        std::cout << "Node State: ";
        switch (nodes[i]->state) {
            case CLEAR:
                std::cout << "CLEAR" << std::endl;
                break;
            case OBSTACLE:
                std::cout << "OBSTACLE" << std::endl;
                break;
            case OBJECT:
                std::cout << "OBJECT" << std::endl;
                break;
            case CONTROL:
                std::cout << "CONTROL" << std::endl;
                break;
        }
        std::cout << "Neighbors: ";
        for (int j = 0; j < nodes[i]->neighbors.size(); j++) {
            std::cout << nodes[i]->neighbors[j]->NodeID << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Object Count: " << this->objCount << std::endl;
    std::cout << "Obstacle Count: " << this->obsCount << std::endl;
    std::cout << "Clear Count: " << this->clrCount << std::endl;
    std::cout << "--------------------------------------" << std::endl;

}

