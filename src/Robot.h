#ifndef ROBOT_H
#define ROBOT_H

#include "Node.h"
#include "Graph.h"

// TODO
// assign robotID

class Robot {
public:
    GraphNode* currNode;
    GraphNode* prevNode;
    //std::vector<GraphNode*> prevNodes;
    bool hasObject;
    bool isMapping;
    bool isRetrieving;
    int robotID;

    Robot(int id);
    // void mapGraph(Graph* graph, std::vector<GraphNode*> visited);
    void move(std::vector<GraphNode*> *visited);
private:
    bool visitedNode(int nodeID, std::vector<GraphNode*> visited);
    int chooseRandNeighborNode(std::vector<GraphNode*> visited);
};

#endif