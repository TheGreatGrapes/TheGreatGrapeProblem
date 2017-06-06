#ifndef VEHICLE_H
#define VEHICLE_H
#include "pvector.h"
#include "path.h"

class Vehicle
{
public:
    Vehicle();
    Vehicle(float, float, int, float);

    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;

    int id;
    float mass;
    float lifespan;
    float maxspeed;
    float maxforce;

    void applyForce(Pvector*);
    void seek(Pvector*);
    void limit(Pvector *vec, float);
    void update();
    void arrive(Pvector*);
    float map(float, float, float, float, float);
    void follow(Path*, int);
    void checkEdge();
    void borders(Path*);
    void separate(std::vector<Vehicle*>);


};

#endif // VEHICLE_H
