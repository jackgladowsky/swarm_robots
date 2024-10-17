// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph {
public:
    int numNodes; // Number of nodes in graph
    std::vector<GraphNode*> nodes; // Vector of nodes in graph
    
    Graph(int numNodes = 5); // constructor with default argument
    void printGraph(); // print the graph
private:
    int obsCount = 0;
    int objCount = 0;
    int clrCount = 0; 
};

#endif // GRAPH_H