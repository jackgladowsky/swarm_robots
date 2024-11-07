# include <iostream>
#include "Robot.h"

Robot::Robot() {
    std::cout << "ROBOT CREATED" << std::endl;
    isMapping = false;
    isRetrieving = false;
    hasObject = false;
}

void Robot::mapGraph(Graph* graph, std::vector<GraphNode*> visited) {
    if (isMapping || isRetrieving) {
        std::cout << "Already performing task." << std::endl;
    }

    std::cout << "ROBOT STARTING MAPPING" << std::endl;
    isMapping = true;
    // enter graph at control point
    currNode = graph->controlPoint;
    visited.push_back(currNode);

    // DFS
    // loop through current nodes neighbors
    for (size_t i = 0; i < currNode->neighbors.size(); i++) {
        // check if current neighbor has been visited
        for (size_t j = 0; j < visited.size(); j++){
            if (currNode->NodeID == visited[j]->NodeID) {
                return;
            }
        }

    }
}

