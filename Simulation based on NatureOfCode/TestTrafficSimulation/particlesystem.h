#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include <vector>
#include <pvector.h>
#include <repeller.h>
#include "stdlib.h"
#include "time.h"

class ParticleSystem
{
public:
    ParticleSystem();

    std::vector<Particle*> particles;
    //Pvector* origin;

    void addParticle();
    void applyForce(Pvector*);
    void applyRepeller(Repeller*);
    void run();
};

#endif // PARTICLESYSTEM_H
