#ifndef OBJECT_H
#define OBJECT_H

#include <Node.h>

enum objStatus{
NOT_COLLECTED,
COLLECTED
};

class Object {
private:

public:
    GraphNode location;
    objStatus status;
    Object(GraphNode location, objStatus status) : location(location), status(status) {};
};


#endif OBJECT_H