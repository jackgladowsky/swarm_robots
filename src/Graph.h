// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph {
public:
    int numNodes; // Number of nodes in graph
    std::vector<GraphNode*> nodes; // Vector of nodes in graph
    GraphNode* controlPoint; // Control point node
    
    Graph(int numNodes); // constructor with default argument
    Graph(int numNodes, bool empty, GraphNode* cp); // constructor with default argument

    Graph init_empty(int numNodes = 5);
    void printGraph(); // print the graph
private:
    int obsCount = 0;
    int objCount = 0;
    int clrCount = 0; 
};

#endif // GRAPH_H