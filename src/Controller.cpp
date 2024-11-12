#include "Controller.h"

void Controller::createRobots(int numRobs) {
    for (int i = 0; i < numRobs; i++) {
        Robot* robot = new Robot(i);
        robot->currNode = graphMap->controlPoint;
        robot->prevNode = nullptr;
        robots.push_back(robot);
    }
}

void Controller::map() {
    createRobots(numRobots);
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Start Mapping..." << std::endl;
    mapping = true;
    std::cout << "Control Node neighbors: ";
    for (size_t j = 0; j < graphMap->controlPoint->neighbors.size(); j++) {
        std::cout << graphMap->controlPoint->neighbors[j]->NodeID << " ";
    }
    std::cout << std::endl;
    exploredMap->controlPoint = graphMap->controlPoint;
    exploredMap->nodes.push_back(graphMap->controlPoint);
    int count = 0;

    while (mapping) {
        if (count == 3) return;
        for (size_t i=0; i < robots.size(); i++) {
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Current Robot: " << i << "\n";

            updateExploredMap(robots[i]);
            robots[i]->move(graphMap, &visitedNodes); 

            

            // if (visitedNodes.size() == exploredMap->nodes.size())
            // {
            //     return;
            // }
        }
        count++;

    }
}

// Robot 0 start on CP
// UEM: CP has not been visited yet, so mark it as visited
// UEM: creates a copy of CP
// UEM: loop through CP neighbors
// UEM: check if CP currentNeighbor has been explored
// UEM: push newNeigbor to explored
// UEM: push newNeigbor to currNode neighbors
// UEM: push currNode to newNeigbor neighbors



void Controller::printExploredMap() {
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Printing Explored Graph...\n";
    exploredMap->printGraph();
}


void Controller::updateExploredMap(Robot* currRobot){
    GraphNode* currNode = currRobot->currNode;
    

    // loop through visited nodes
    bool hasVisited = isVisited(currNode);
        
    if (hasVisited) { // if the currNode has been visited
        return;
    }
    else { // if the current node has NOT been visited
        std::cout << "start\n";
        visitedNodes.push_back(currNode); // add the currNode to visited list

        GraphNode* newNode = new GraphNode(currNode->NodeID, currNode->state); // create the copy of the currNode

        bool hasExploredNode = isExplored(currNode);

        if (!hasExploredNode) {
            exploredMap->nodes.push_back(newNode);
        }
        else {
            free(newNode);
            std::cout <<"return\n";
            return;
        }

        for (int i=0; i<currNode->neighbors.size(); i++) { // loop through the currNodes neighbors

            GraphNode* currNeighbor = currNode->neighbors[i]; // get the current neighbor
            bool hasExplored = isExplored(currNeighbor);

            if (hasExplored) { // if the currNeighbor has been explored already
                GraphNode* exploredNode = findExploredNode(currNeighbor->NodeID);
                exploredNode->neighbors.push_back(newNode);
                newNode->neighbors.push_back(exploredNode);
            }
            else { // if the current neighbor has not been explored yet
                GraphNode* newNeighbor = new GraphNode(currNeighbor->NodeID, currNeighbor->state); // create neighbor copy
                exploredMap->nodes.push_back(newNeighbor); // set the newNeighbor as explored
                newNode->neighbors.push_back(newNeighbor); // set the newNeighbor as newNode neighbor
                newNeighbor->neighbors.push_back(newNode); // set the newNode as newNeighbor neighbor
            }
        }

    }
}


GraphNode* Controller::findExploredNode(int nodeID) {
    for (int i=0; i > exploredMap->nodes.size(); i++) {
        if (nodeID == exploredMap->nodes[i]->NodeID) {
            return exploredMap->nodes[i];
        }
    std::cout << "Node has not been explored yet.\n";
    return nullptr;
    }
}


bool Controller::isVisited(GraphNode* node) {
    for (int i=0; i > visitedNodes.size(); i++) {
        // if the current node has been visited
        if (node->NodeID == visitedNodes[i]->NodeID) {
            return true;
        }
    return false;
    }
}

bool Controller::isExplored(GraphNode* node) {
    for (int i=0; i > exploredMap->nodes.size(); i++) {
        // if the current node has been visited
        if (node->NodeID == exploredMap->nodes[i]->NodeID) {
            return true;
        }
    return false;
    }
}
