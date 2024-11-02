#include <iostream>
#include "Graph.h"
#include "Robot.h"
#include "Controller.h"

int main() {
    std::cout << "Hello Swarm Robots!" << std::endl;

    Robot robot1;

    Graph graph(10);
    //graph.printGraph();

    Controller controller;

    return 0;
}