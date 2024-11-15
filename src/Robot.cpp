# include <iostream>
#include "Robot.h"

Robot::Robot(int id) {
    robotID = id;
    isMapping = false;
    isRetrieving = false;
    hasObject = false;
    std::cout << "ROBOT " << robotID << " CREATED." << std::endl;
}

void Robot::move(std::vector<GraphNode*>* visited) {
    // get neighbors
    // make sublist of nonvisited neighbors
    std::vector<GraphNode*> unvisitedNeighbors = {};
    for (size_t i = 0; i < currNode->neighbors.size(); i++) {
        if (!visitedNode(currNode->neighbors[i], *visited)) {
            unvisitedNeighbors.push_back(currNode->neighbors[i]);
        }
    }    
    if (unvisitedNeighbors.size() != 0)
    {
        int randNeighborNum = rand() % unvisitedNeighbors.size();
        GraphNode* randNeighbor = unvisitedNeighbors[randNeighborNum];
        

        // if not checked, set currNode to new node & add node to visited
        prevNode = currNode;
        currNode = randNeighbor;
        std::cout << "rand neighbor selected: " << randNeighbor->NodeID << "\n";

        // visited->push_back(currNode); // robots send current node data to controller
        std::cout << "Node ID: " << currNode->NodeID << std::endl;
        std::cout << "Node State: ";
        switch (currNode->state) {
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
        for (size_t j = 0; j < currNode->neighbors.size(); j++) {
            std::cout << currNode->neighbors[j]->NodeID << " ";
        }
        std::cout << std::endl;
        return;
    }
    // remove from that list each time a neighbor is visited
    // for (size_t i = 0; i < currNode->neighbors.size(); i++) {
    //     // choose random neighbor
    //     int randNeighbor = rand() % currNode->neighbors.size();
    //     // check if random neighbor has veen visited
    //     if (visitedNode(currNode->neighbors[randNeighbor], *visited)){
    //         // if visisted, choose new neighbor node
    //         continue;
    //     }
    //     else{
    //         // if not checked, set currNode to new node & add node to visited
    //         prevNode = currNode;
    //         currNode = currNode->neighbors[randNeighbor];
    //         // visited->push_back(currNode); // robots send current node data to controller
    //         std::cout << "Node ID: " << currNode->NodeID << std::endl;
    //         std::cout << "Node State: ";
    //         switch (currNode->state) {
    //             case CLEAR:
    //                 std::cout << "CLEAR" << std::endl;
    //                 break;
    //             case OBSTACLE:
    //                 std::cout << "OBSTACLE" << std::endl;
    //                 break;
    //             case OBJECT:
    //                 std::cout << "OBJECT" << std::endl;
    //                 break;
    //             case CONTROL:
    //                 std::cout << "CONTROL" << std::endl;
    //                 break;
    //         }
    //         std::cout << "Neighbors: ";
    //         for (size_t j = 0; j < currNode->neighbors.size(); j++) {
    //             std::cout << currNode->neighbors[j]->NodeID << " ";
    //         }
    //         std::cout << std::endl;
    //         return;
    //     }
    // }
    std::cout << "All possible neighbor nodes have been visited." << std::endl;
    std::cout << "------------------------------------" << std::endl;
    return;
}


bool Robot::visitedNode(GraphNode* node, std::vector<GraphNode*> visited) {
    for (size_t i = 0; i < visited.size(); i++) {
        if (visited[i]->NodeID == node->NodeID) {
            return true;
        }
    }
    return false;
}