#ifndef PARTICLE_H
#define PARTICLE_H
#include "pvector.h"

class Particle
{
public:
    Particle();
    Particle(float, float, int);

    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;
    int id;

    float mass;
    float lifespan;

    void update();
    void applyForce(Pvector*);
    void checkEdge();
    bool isDead();

};

#endif // PARTICLE_H
