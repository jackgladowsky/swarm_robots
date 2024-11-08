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
    Graph* exploredMap;     // controller's version of the map
    bool mapping;
    int numRobots = 3;

    Controller(Graph* graph) : graphMap(graph){};

    void createRobots(int numRobs);
    void map();

private:
    bool visited(GraphNode* node, std::vector<GraphNode*> visited);
    void updateExploredMap(Robot* currRobot);
};

#endif