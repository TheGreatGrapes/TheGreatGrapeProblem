#ifndef REPELLER_H
#define REPELLER_H
#include "pvector.h"
#include "particle.h"

class Repeller
{
public:
    Repeller(float, float);
    Pvector* location;
    float mass;
    float G;

    Pvector* repel(Particle*);
    float constrain(float, float, float);
};

#endif // REPELLER_H

