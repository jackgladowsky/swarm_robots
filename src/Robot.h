#ifndef ROBOT_H
#define ROBOT_H

#include <stack>
#include "Node.h"
#include "Graph.h"

// TODO
// assign robotID

class Robot {
public:
    GraphNode* currNode;
    GraphNode* prevNode;
    std::stack<GraphNode*> prevNodeStack;
    bool hasObject;
    bool isMapping;
    bool isRetrieving;
    int robotID;

    Robot(int id);
    // void mapGraph(Graph* graph, std::vector<GraphNode*> visited);
    void move(std::vector<GraphNode*>* visited);
    void moveBack();
private:
    bool visitedNode(GraphNode* node, std::vector<GraphNode*> visited);
};

#endif