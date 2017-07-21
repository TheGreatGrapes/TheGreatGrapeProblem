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

    Vehicle(float, float, int, float, Path*);
    ~Vehicle();

    ////////////////// Variables ////////////////

    Pvector *location;
    Pvector *velocity;
    Pvector *acceleration;
    Pvector *mySteerForce;
    JunctionPoint *goal;
    Pvector* longTermDest;

    float maxspeed;
    float maxforce;

    float sepWeight;
    float folWeight;
    float arrWeight;

    int counter;
    int onlyOnce;
    int myCurrentGoal;
    int timesReached;

    bool followSomeone;
    bool reachedDest;

    unsigned long timesTaken;

    unsigned long tempGoal;
    unsigned long tempVar;
    unsigned long whoIfollowed;

    std::vector<JunctionPoint> possibleDest;
    std::vector<Vehicle*> possibleCars;
    std::vector<Pvector*> goals;

    ////////////// Behaviors /////////////

    virtual void move(std::vector<Vehicle *> ) = 0;           // Pure virtual function (Necessary to be overwritten)
    virtual void applyBehaviour(std::vector<Vehicle*>) = 0;   // Pure virtual function (Necessary to be overwritten)

    virtual Pvector *arrive(std::vector<Vehicle *> );             // Normal virtual function (Not necessary to be overwritten)
    virtual Pvector *follow();                                    // Normal virtual function (Not necessary to be overwritten)
    virtual void findSomeoneInFront(std::vector<Vehicle *> ); // Normal virtual function (Not necessary to be overwritten)
    virtual Pvector *separate(std::vector<Vehicle *> );           // Normal virtual function (Not necessary to be overwritten)    
    virtual Pvector *seek(Pvector*);
    virtual Pvector *goToJunction();                              // Normal virtual function (Not necessary to be overwritten)

    void chooseJunction(Path*);                               // Don't have to be virtual. Because all drivers share this common behavior/function
    virtual void makeTurn(Path*);                                     // Don't have to be virtual. Because all drivers share this common behavior/function
                                     // Don't have to be virtual. Because all drivers share this common behavior/function
    void applyForce(Pvector*);                                // Don't have to be virtual. Because all drivers share this common behavior/function
    void update();                                            // Don't have to be virtual. Because all drivers share this common behavior/function
    //void makeNewDest(Path*);

    ////////////// Sub Functions /////////////

    void stopIfCloseEnough();
    void setInitDest(Path*);

    float map(float, float, float, float, float);

    bool setGoal();
    bool isArrived();
    bool aboutToGo();
    bool isAccessible(Path* , unsigned long, unsigned long);
    bool isInOrOut(Path*, unsigned long, unsigned long, bool);

    ////////////// Unused Stuff /////////////
    int id;
    float mass;

};

#endif // VEHICLE_H
