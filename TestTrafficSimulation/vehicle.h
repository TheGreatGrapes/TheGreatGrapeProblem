#ifndef VEHICLE_H
#define VEHICLE_H
#include "pvector.h"
#include "path.h"
#include "stdlib.h"
#include "time.h"
#include <vector>

class Vehicle
{
public:
    ///////////////// Constructor ///////////////
    Vehicle();
    Vehicle(float, float, int, float);

    ////////////////// Variables ////////////////
    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;
    Pvector *goal;

    std::vector<Pvector> possibleDest;
    std::vector<Vehicle*> cars;

    int decision;

    float maxspeed;
    float maxforce;

    ////////////// Main Functions /////////////
    void arrive();
    void seek(Pvector*);
    void applyForce(Pvector*);

    ////////////// Sub Functions /////////////
    void update();
    void stopAtJunction();
    void chooseJunction(Path*);
    void limit(Pvector *vec, float);
    void addCars(float , float , int, float);

    float map(float, float, float, float, float);

    bool ifAtJunction(Path*);

    ////////////// Unused Variables /////////////
    int id;
    float mass;
    float lifespan;
    bool direction;

    //////////// Unused Functions /////////////
    void follow(Path* p);

};

#endif // VEHICLE_H
