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

    Vehicle(float, float, int, float);

    ////////////////// Variables ////////////////

    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;
    JunctionPoint *goal;

    float maxspeed;
    float maxforce;
    int counter;

    unsigned long tempGoal;
    unsigned long tempVar;

    std::vector<JunctionPoint> possibleDest;

    ////////////// Main Functions /////////////

    void chooseJunction(Path*);
    void makeTurn(Path*);
    void arrive();
    void seek(Pvector*);
    void applyForce(Pvector*);
    void update();
    void separate(std::vector<Vehicle*>);

    ////////////// Sub Functions /////////////

    void stopIfCloseEnough();
    void limit(Pvector *vec, float);

    float map(float, float, float, float, float);

    bool setGoal();
    bool isArrived();
    bool aboutToGo();
    bool isAccessible(Path* , unsigned long, unsigned long);
    bool isInOrOut(Path*, unsigned long, unsigned long, bool);

    ////////////// Unused Stuff /////////////
    int id;
    float mass;
    float lifespan;
    bool direction;

    //void follow(Path* p);

};

#endif // VEHICLE_H
