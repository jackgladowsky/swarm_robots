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
    int controlPointIndex = rand() % numNodes;
    nodes[controlPointIndex]->state = CONTROL;
    controlPoint = nodes[controlPointIndex];

    // loop through all nodes in graph
    for (int i = 0; i < numNodes; i++) {
        // choose random number 1-4
        int numNeighbors = rand() % 4 + 1;\

        // loop through from 0 to numNeighbors
        for (int j = 0; j < numNeighbors; j++) {
            // choose a random node
            int neighbor = rand() % numNodes;

            // if neighbor is not itself
            if (neighbor != i) {
                bool exists = false;

                // loop through current nodes neighbors
                for (size_t k = 0; k < nodes[i]->neighbors.size(); k++) {
                    // check if current node and current nodes neighbors has 4 already
                    // if (nodes[i]->neighbors.size() == 4 || nodes[i]->neighbors[k]->neighbors.size() == 4){
                    //     break;
                    // }

                    // if the neighbor already exists
                    if (nodes[i]->neighbors[k]->NodeID == neighbor) {
                        exists = true;
                        break;
                    }
                }
                // create then neighbor by pushing each node to each nodes neighbor list
                if (!exists) {
                    nodes[i]->neighbors.push_back(nodes[neighbor]);
                    nodes[neighbor]->neighbors.push_back(nodes[i]);
                }
            }
        }
    }
}

Graph::Graph(int numNodes, bool empty, GraphNode* cp) : numNodes(numNodes) {
    GraphNode* node = new GraphNode(0, CLEAR);
    // nodes.push_back(cp);
    controlPoint = cp;
}

// print the entire graph
void Graph::printGraph() {
    for (int i = 0; i < nodes.size(); i++) {
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
        for (size_t j = 0; j < nodes[i]->neighbors.size(); j++) {
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

