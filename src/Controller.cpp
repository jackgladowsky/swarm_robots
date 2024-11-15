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
    std::cout << "On node: " << graphMap->controlPoint->NodeID << "\n";
    std::cout << "Control Node neighbors: ";
    for (size_t j = 0; j < graphMap->controlPoint->neighbors.size(); j++) {
        std::cout << graphMap->controlPoint->neighbors[j]->NodeID << " ";
    }
    std::cout << std::endl;
    //exploredMap->controlPoint = graphMap->controlPoint;
    //exploredMap->nodes.push_back(graphMap->controlPoint);
    int count = 0;

    while (mapping) {
        if (count == 10) return;
        for (size_t i=0; i < robots.size(); i++) {
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Current Robot: " << i << "\n";

            updateExploredMap(robots[i]);
            robots[i]->move(&visitedNodes); 
            updateExploredMap(robots[i]);

            

            if (visitedNodes.size() == exploredMap->nodes.size())
            {
                std::cout << "all nodes have been visited\n";
                return;
            }
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


// VISITED: A node is visited when a robot lands on that Node
// EXPLORED: A node is explored when a robot lands on a neighbor of that node

void Controller::updateExploredMap(Robot* currRobot){
    GraphNode* currRealNode = currRobot->currNode; // actual Node from graphMap

    // check to see if currentRealNode has been visited
    bool hasVisited = isVisited(currRealNode);
    
    // if the currRealNode has been visited
    if (hasVisited) { 
        return;
    }
    else { // if the current real node has NOT been visited
        // std::cout << "start\n";
        visitedNodes.push_back(currRealNode); // set currRealNode to visited

        GraphNode* currNodeCopy = new GraphNode(currRealNode->NodeID, currRealNode->state); // create the copy of the currNode

        bool hasExploredNode = isExplored(currRealNode);

        if (!hasExploredNode) {
            exploredMap->nodes.push_back(currNodeCopy);
        }
        else {
            free(currNodeCopy);
            std::cout <<"return\n";
            return;
        }

        for (size_t i=0; i<currRealNode->neighbors.size(); i++) { // loop through the currNodes neighbors

            GraphNode* currRealNeighbor = currRealNode->neighbors[i]; // get the current neighbor
            bool hasExplored = isExplored(currRealNeighbor);
            // std::cout << "hasExplored = " << hasExplored << "\n";

            if (hasExplored) { // if the currNeighbor has been explored already
                GraphNode* currNeighborCopy = findExploredNode(currRealNeighbor->NodeID);
                currNeighborCopy->neighbors.push_back(currNodeCopy);
                currNodeCopy->neighbors.push_back(currNeighborCopy);
            }
            else { // if the current neighbor has not been explored yet
                GraphNode* currNeighborCopy = new GraphNode(currRealNeighbor->NodeID, currRealNeighbor->state); // create neighbor copy
                exploredMap->nodes.push_back(currNeighborCopy); // set the newNeighbor as explored
                currNodeCopy->neighbors.push_back(currNeighborCopy); // set the newNeighbor as newNode neighbor
                currNeighborCopy->neighbors.push_back(currNodeCopy); // set the newNode as newNeighbor neighbor
            }
        }

    }
}


GraphNode* Controller::findExploredNode(int nodeID) {
    for (size_t i=0; i < exploredMap->nodes.size(); i++) {
        if (nodeID == exploredMap->nodes[i]->NodeID) {
            return exploredMap->nodes[i];
        }
    }
    std::cout << "Node has not been explored yet.\n";
    return nullptr;
}


bool Controller::isVisited(GraphNode* node) {
    for (size_t i=0; i < visitedNodes.size(); i++) {
        // if the current node has been visited
        if (node->NodeID == visitedNodes[i]->NodeID) {
            return true;
        }    
    }
    return false;
}

bool Controller::isExplored(GraphNode* node) {
    // std::cout << "explored map size: " << exploredMap->nodes.size() << "\n";
    for (size_t i=0; i < exploredMap->nodes.size(); i++) {
        // if the current node has been visited
        // std::cout << "NodeID: " << node->NodeID << "\n";
        // std::cout << "exploredMap node ID: " << exploredMap->nodes[i]->NodeID << "\n";
        if (node->NodeID == exploredMap->nodes[i]->NodeID) {
            return true;
        }
    }
    return false;
}
