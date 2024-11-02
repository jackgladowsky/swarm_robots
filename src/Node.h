#ifndef NODE_H
#define NODE_H

#include <vector>

enum NodeState {
    CLEAR = 0, // node is clear to travel on
    OBSTACLE = 1, // node is not clear to travel on
    OBJECT = 2, // node contains an object
    CONTROL = 3 // node contains control point/home
};

class GraphNode {
public:
    int NodeID;
    NodeState state;
    std::vector<GraphNode*> neighbors;

    GraphNode(int id, NodeState state) : NodeID(id), state(state) {};
    void printNode();
private:

};

#endif