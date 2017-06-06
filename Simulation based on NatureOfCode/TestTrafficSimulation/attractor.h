#ifndef ATTRACTOR_H
#define ATTRACTOR_H
#include "pvector.h"
#include "mover.h"

class Mover;

class Attractor
{
public:
    Attractor(float, float);

    Pvector* location;
    float mass;
    float G;

    Pvector* attract(Mover);
    float constrain(float, float, float);
};

#endif // ATTRACTOR_H
