#include <iostream>
#include "Node.h"

void GraphNode::printNode() {
    std::cout << "------------------------------------" << this->NodeID << std::endl;

    std::cout << "Node ID: " << this->NodeID << std::endl;
    std::cout << "Node State: ";
    switch (this->state) {
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
        for (int j = 0; j < this->neighbors.size(); j++) {
            std::cout << this->neighbors[j]->NodeID << " ";
        }
        std::cout << std::endl;

    std::cout << "------------------------------------" << this->NodeID << std::endl;

}