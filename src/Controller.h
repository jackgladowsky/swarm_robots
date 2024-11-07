#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "Robot.h"

class Controller {
public:
    std::vector<Robot*> robots;
    std::vector<GraphNode*> visitedNodes;
    Graph* graphMap;
    bool mapping;
    int numRobots = 3;

    void createRobots(int numRobs);
    void map();

private:
    bool visited(GraphNode* node, std::vector<GraphNode*> visited);
};

#endif