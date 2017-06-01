#include "particle.h"

Particle::Particle(){
    location = new Pvector(0,0);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);
    lifespan = 250;
    id = 1;
    mass = 1;
}

Particle::Particle(float l, float v, int _id)
{
    location = new Pvector(l,v);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);
    lifespan = 250;
    id = _id;
    mass = 1;
}

void Particle::update(){
    velocity->add(acceleration);
    location->add(velocity);
    acceleration->mult(0);
    checkEdge();
    lifespan -= 2;
}

void Particle::checkEdge(){
    if(location->x < -250){
        location->x = -250;
        velocity->x *= -1;
    }else if (location->x > 250){
        velocity->x *= -1;
        location->x = 250;
    }

    if(location->y < -250){
        location->y = -250;
        velocity->y *= -1;
    }else if (location->y > 250){
        velocity->y *= -1;
        location->y = 250;
    }
}

bool Particle::isDead(){
    if(lifespan <= 0){
        return true;
    }else
        return false;
}

void Particle::applyForce(Pvector* force){
    Pvector *f = new Pvector(0,0);
    *f = force->get();
    f->div(mass);
    this->acceleration->add(f);
}
