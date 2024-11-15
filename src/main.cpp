#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Graph.h"
#include "Robot.h"
#include "Controller.h"

int main() {
    std::cout << "Hello Swarm Robots!" << std::endl;
    srand(time(NULL));

    Graph graph(25);
    graph.printGraph();

    Controller controller(&graph);
    controller.map();
    controller.printExploredMap();

    return 0;
}