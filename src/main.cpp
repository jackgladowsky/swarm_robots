#include <iostream>
#include "Graph.h"
#include "Robot.h"
#include "Controller.h"

int main() {
    std::cout << "Hello Swarm Robots!" << std::endl;

    Graph graph(10);
    // graph.printGraph();

    Controller controller(&graph);
    controller.map();
    controller.printExploredMap();

    return 0;
}