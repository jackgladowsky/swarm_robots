#include "Controller.h"

void Controller::map() {
    mapping = true;
    while (mapping) {
        for (int i=0; i < robots.size(); i++) {
            robots[i]->mapGraph(graphMap, visitedNodes);
        }
    }
    
}

bool Controller::visited(GraphNode* node, std::vector<GraphNode*> visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i]->NodeID == node->NodeID) {
            return true;
        }
    }
    return false;
}