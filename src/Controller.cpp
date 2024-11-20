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
    // update explored map w/ control point + neighbors before mapping starts
    GraphNode* controlPoint = new GraphNode(graphMap->controlPoint->NodeID, graphMap->controlPoint->state);
    // add control point neighbors
    // for (int i = 0; i < graphMap->controlPoint->neighbors.size(); i++) {
    //     controlPoint->neighbors.push_back(graphMap->controlPoint->neighbors[i]);
    // }
    exploredMap->controlPoint = controlPoint;
    exploredMap->nodes.push_back(controlPoint);
    visitedNodes.push_back(controlPoint);
    std::cout << "Pushing node" << exploredMap->controlPoint->NodeID << " to explored map\n";
    for (int i = 0; i < graphMap->controlPoint->neighbors.size(); i++) {
        GraphNode* currNeighborCopy = new GraphNode(graphMap->controlPoint->neighbors[i]->NodeID, graphMap->controlPoint->neighbors[i]->state); // create neighbor copy
        controlPoint->neighbors.push_back(currNeighborCopy);
        exploredMap->nodes.push_back(currNeighborCopy);
        currNeighborCopy->neighbors.push_back(exploredMap->controlPoint);
        std::cout << "Pushing node " << currNeighborCopy->NodeID << " to explored map\n";
    }

    /*
    To implement obstacle stuff
    - when a robot is on an obstacle node, don't add the other neighbors 
    - can't move through that node
    - in backtracking/BFS
        - make it so that we don't consider a path through that node
    */



    int count = 0;

    while (mapping) {
        if (count == 10) return;
        for (size_t i=0; i < robots.size(); i++) {
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Current Robot: " << i << "\n";

            // updateExploredMap(robots[i]);
            robots[i]->move(&visitedNodes); 
            updateExploredMap(robots[i]);

            // print sizes of explored and visited node lists
            std::cout << "Size of explored: " << exploredMap->nodes.size() << "\n";
            std::cout << "Size of visited: " << visitedNodes.size() << "\n";

            if (visitedNodes.size() == exploredMap->nodes.size())
            {
                std::cout << "all nodes have been visited\n";
                return;
            }
        }
        count++;

    }

    std::cout << "End of graph has been reached... sending robots back" << std::endl;
    robots[i]->moveBack();
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
    bool hasVisitedNode = isVisited(currRealNode);
    
    // if the currRealNode has been visited
    if (hasVisitedNode) { 
        return;
    }
    else { // if the current real node has NOT been visited
        // std::cout << "start\n";
        visitedNodes.push_back(currRealNode); // set currRealNode to visited

        // GraphNode* currNodeCopy = new GraphNode(currRealNode->NodeID, currRealNode->state); // create the copy of the currNode
        GraphNode* currNodeCopy = findExploredNode(currRealNode->NodeID);

        // updating state when we visit a node (you don't know state until visiting a node)
        currNodeCopy->state = currRealNode->state;

        for (size_t i=0; i<currRealNode->neighbors.size(); i++) { // loop through the currNodes neighbors

            GraphNode* currRealNeighbor = currRealNode->neighbors[i]; // get the current neighbor
            bool hasExploredNeighbor = isExplored(currRealNeighbor);
            bool hasVisitedNeighbor = isVisited(currRealNeighbor);
            // std::cout << "hasExplored = " << hasExplored << "\n";
            if (hasVisitedNeighbor) {
                continue;
            }
            if (hasExploredNeighbor) { // if the currNeighbor has been explored already
                if (exploredMap->controlPoint->NodeID == currRealNeighbor->NodeID) continue;
                GraphNode* currNeighborCopy = findExploredNode(currRealNeighbor->NodeID);
                currNeighborCopy->neighbors.push_back(currNodeCopy);
                currNodeCopy->neighbors.push_back(currNeighborCopy);
                std::cout << "added " << currNodeCopy->NodeID << " <-> " << currNeighborCopy->NodeID << "\n";
            }
            else { // if the current neighbor has not been explored yet
                GraphNode* currNeighborCopy = new GraphNode(currRealNeighbor->NodeID, CLEAR); // create neighbor copy
                exploredMap->nodes.push_back(currNeighborCopy); // set the newNeighbor as explored
                std::cout << "Pushing node " << currNeighborCopy->NodeID << " to explored map\n";
                currNodeCopy->neighbors.push_back(currNeighborCopy); // set the newNeighbor as newNode neighbor
                currNeighborCopy->neighbors.push_back(currNodeCopy); // set the newNode as newNeighbor neighbor
                std::cout << "added " << currNodeCopy->NodeID << " <-> " << currNeighborCopy->NodeID << "\n";
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
