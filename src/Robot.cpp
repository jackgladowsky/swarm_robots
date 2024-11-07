# include <iostream>
#include "Robot.h"

Robot::Robot(int id) {
    robotID = id;
    isMapping = false;
    isRetrieving = false;
    hasObject = false;
    std::cout << "ROBOT " << robotID << " CREATED." << std::endl;
}

void Robot::move(Graph* graph, std::vector<GraphNode*> visited) {
    
}

void Robot::mapGraph(Graph* graph, std::vector<GraphNode*> visited) {
    if (isMapping || isRetrieving) {
        std::cout << "Already performing task." << std::endl;
    }

    std::cout << "ROBOT " << robotID << " STARTING MAPPING" << std::endl;
    isMapping = true;
    // enter graph at control point
    currNode = graph->controlPoint;
    visited.push_back(currNode);
}

