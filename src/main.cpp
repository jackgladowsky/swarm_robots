#include <iostream>
#include "Graph.h"
#include "Robot.h"
#include "Controller.h"
#include <time.h>

int main() {
    std::cout << "Hello Swarm Robots!" << std::endl;

    srand(time(NULL));

    Graph graph(10);
    // graph.printGraph();

    Controller controller(&graph);
    controller.map();
    controller.printExploredMap();

    return 0;
}

// stop condition should be:

// when all explored nodes have been visited
// visitednodes.size == exploredmap.nodes.size