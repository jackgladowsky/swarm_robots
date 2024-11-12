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
    Graph* graphMap; // this is actual graph
    Graph* exploredMap = new Graph(10, true, graphMap->controlPoint); // controller's version of the map
    bool mapping;
    int numRobots = 1;

    Controller(Graph* graph) : graphMap(graph){};

    void createRobots(int numRobs);
    void map();
    void printExploredMap();

private:
    bool isVisited(GraphNode* node);
    bool isExplored(GraphNode* node);
    GraphNode* findExploredNode(int nodeID); 
    void updateExploredMap(Robot* currRobot);
};

#endif