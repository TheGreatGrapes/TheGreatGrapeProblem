#include "mover.h"

extern int windowSize;

Mover::Mover()
{
    location = new Pvector(0, 0);
    //velocity = new Pvector(rand() % 6 - 3, rand() % 6 - 3);
    velocity = new Pvector(0, 0);
    acceleration = new Pvector(0, 0);
    mass = 1.0;
    G = 0.4;
}

Mover::Mover(float m, float x, float y)
{
    location = new Pvector(x, y);
    velocity = new Pvector(0, 0);
    acceleration = new Pvector(0, 0);
    mass = m;
    G = 0.4;
}

void Mover::update(){
    velocity->add(acceleration);
    location->add(velocity);
    checkEdge();
    acceleration->mult(0);
}

void Mover::checkEdge(){
    if(location->x < -windowSize){
        location->x = -windowSize;
        velocity->x *= -1;
    }else if (location->x > windowSize){
        velocity->x *= -1;
        location->x = windowSize;
    }

    if(location->y < -windowSize){
        location->y = -windowSize;
        velocity->y *= -1;
    }else if (location->y > windowSize){
        velocity->y *= -1;
        location->y = windowSize;
    }
}

void Mover::applyForce(Pvector* force){
    Pvector *f = Pvector::div(force,this->mass);
    acceleration->add(f);
}


Pvector* Mover::attract(Mover m){
    Pvector* force = Pvector::sub(location, m.location);
    float distance = force->mag();
    distance = constrain(distance, 10, 25);
    force->normalize();
    float strength = (G * mass * m.mass ) / (distance * distance);
    force->mult(strength);

    return force;
}

Pvector* Mover::repell(Mover m){
    Pvector* force = Pvector::sub(location, m.location);
    float distance = force->mag();
    distance = constrain(distance, 10, 25);
    force->normalize();
    float strength = (G * mass * m.mass ) / (distance * distance);
    force->mult(strength);

    return force;
}

float Mover::constrain(float dis, float lowerBound, float upperBound){
    if(dis < lowerBound){
        dis = lowerBound;
    }else if (dis > upperBound){
        dis = upperBound;
    }
    return dis;
}
