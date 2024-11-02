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
    bool hasObject;
    bool isMapping;
    bool isRetrieving;
    int robotID;

    Robot();
    void mapGraph(Graph* graph, std::vector<GraphNode*> visited);
private:
    void dfsRecursive();
};

#endif