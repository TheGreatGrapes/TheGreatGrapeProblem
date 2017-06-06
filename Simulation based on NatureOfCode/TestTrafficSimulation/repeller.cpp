#include "repeller.h"

Repeller::Repeller(float x, float y)
{
    location = new Pvector(x, y);
    mass = 20;
    G = 0.4;
}

Pvector* Repeller::repel(Particle *p){
    Pvector* force = Pvector::sub(location, p->location);
    float distance = force->mag();
    distance = constrain(distance, 10, 50);
    force->normalize();
    float strength = (-1 * G * mass * p->mass ) / (distance * distance);
    force->mult(strength);

    return force;
}

float Repeller::constrain(float dis, float lowerBound, float upperBound){
    if(dis < lowerBound){
        dis = lowerBound;
    }else if (dis > upperBound){
        dis = upperBound;
    }
    return dis;
}
