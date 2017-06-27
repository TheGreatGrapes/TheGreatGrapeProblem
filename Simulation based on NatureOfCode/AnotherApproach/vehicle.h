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
    Pvector *mySteerForce;
    JunctionPoint *goal;

    float maxspeed;
    float maxforce;
    float priority;

    int counter;
    int onlyOnce;
    int myCurrentGoal;

    bool followSomeone;

    unsigned long tempGoal;
    unsigned long tempVar;
    unsigned long whoIfollowed;

    std::vector<JunctionPoint> possibleDest;
    std::vector<Pvector*> goals;

    ////////////// Behaviors /////////////

    virtual void move(std::vector<Vehicle *> ) = 0;           // Pure virtual function (Necessary to be overwritten)

    virtual void arrive(std::vector<Vehicle *> );             // Normal virtual function (Not necessary to be overwritten)
    virtual void follow();                                    // Normal virtual function (Not necessary to be overwritten)
    virtual void findSomeoneInFront(std::vector<Vehicle *> ); // Normal virtual function (Not necessary to be overwritten)
    virtual void separate(std::vector<Vehicle *> );           // Normal virtual function (Not necessary to be overwritten)
    virtual void goToJunction();                              // Normal virtual function (Not necessary to be overwritten)

    void chooseJunction(Path*);                               // Don't have to be virtual. Because all drivers share this common behavior/function
    void makeTurn(Path*);                                     // Don't have to be virtual. Because all drivers share this common behavior/function
    void seek(Pvector*);                                      // Don't have to be virtual. Because all drivers share this common behavior/function
    void applyForce(Pvector*);                                // Don't have to be virtual. Because all drivers share this common behavior/function
    void update();                                            // Don't have to be virtual. Because all drivers share this common behavior/function

    ////////////// Sub Functions /////////////

    void stopIfCloseEnough();

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

};

#endif // VEHICLE_H
