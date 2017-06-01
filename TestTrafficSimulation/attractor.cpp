#include "attractor.h"

Attractor::Attractor(float x, float y)
{
    location = new Pvector(x, y);
    mass = 20;
    G = 0.4;

}

Pvector* Attractor::attract(Mover m){
    Pvector* force = Pvector::sub(location, m.location);
    float distance = force->mag();
    distance = constrain(distance, 5, 25);
    force->normalize();
    float strength = (-1 * G * mass * m.mass ) / (distance * distance);
    force->mult(strength);

    return force;
}

float Attractor::constrain(float dis, float lowerBound, float upperBound){
    if(dis < lowerBound){
        dis = lowerBound;
    }else if (dis > upperBound){
        dis = upperBound;
    }
    return dis;
}
