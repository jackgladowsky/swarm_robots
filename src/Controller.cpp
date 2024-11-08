#include "Controller.h"

void Controller::createRobots(int numRobs) {
    for (int i = 0; i < numRobs; i++) {
        Robot* robot = new Robot(i);
        std::cout << graphMap->controlPoint->NodeID;
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
    while (mapping) {
        for (size_t i=0; i < robots.size(); i++) {
            std::cout << "current Robot: " << i << "\n";
            // call updateExploredMap
            robots[i]->move(graphMap, &visitedNodes);
        }
        if (visitedNodes.size() == graphMap->numNodes)
        {
            return;
        }
    }
}

void Controller::updateExploredMap(Robot* currRobot){
    
    // create new node
    GraphNode* newNode = new GraphNode(currRobot->currNode->NodeID, currRobot->currNode->state);
    // for curr
    for (size_t i = 0; i < currRobot->currNode->neighbors.size(); i++){
        GraphNode* newNeighbor = new GraphNode(currRobot->currNode->neighbors[i]->NodeID, currRobot->currNode->neighbors[i]->state);
        newNode->neighbors.push_back(newNeighbor);
        newNeighbor->neighbors.push_back(newNode);
    }
    exploredMap->nodes.push_back(newNode);
}

// updateExploredMap

// if currNode has not been visited
//      create a new Node, set ID and STATE as currNode
//      loop through currNode neighbors
//          if currNeighbor is not in exploredMap
//              create newNieghbor, set ID and STATE as currNeighbor
//              push newNeighbor to exploredMap & push newNeighbor to newNode's neighbors
//              push newNode to newNeighbor's neighbors
//          if currNeighbor IS in exploredMap
//              push newNode to exploredMap version of currNeighbor's neighbors
//              push exploredMap's currNeighbor to currNode's neighbors

// if currNode has been visited
//      