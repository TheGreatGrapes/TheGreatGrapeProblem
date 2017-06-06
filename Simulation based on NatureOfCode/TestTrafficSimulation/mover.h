#ifndef MOVER_H
#define MOVER_H
#include "pvector.h"
#include "stdlib.h"
#include "time.h"

class Mover
{
public:
    Mover();
    Mover(float, float, float);

    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;
    float mass;
    float G;


    void update();
    void checkEdge();
    void applyForce(Pvector*);
    Pvector* attract(Mover);
    Pvector* repell(Mover);
    float constrain(float, float, float);
};

#endif // MOVER_H
