#include "Controller.h"

void Controller::createRobots(int numRobs) {
    for (int i = 0; i < numRobs; i++) {
        Robot* robot = new Robot(i);
        robots.push_back(robot);
    }
}

void Controller::map() {
    createRobots(numRobots);
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Start Mapping..." << std::endl;
    mapping = true;
    while (mapping) {
        for (size_t i=0; i < robots.size(); i++) {
            // robots[i]->mapGraph(graphMap, visitedNodes);
        }
    }
}

bool Controller::visited(GraphNode* node, std::vector<GraphNode*> visited) {
    for (size_t i = 0; i < visited.size(); i++) {
        if (visited[i]->NodeID == node->NodeID) {
            return true;
        }
    }
    return false;
}