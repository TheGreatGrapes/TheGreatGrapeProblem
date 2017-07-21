#ifndef ROAMINGDRIVER_H
#define ROAMINGDRIVER_H
#include "vehicle.h"

class RoamingDriver:public Vehicle
{
public:
    RoamingDriver(float, float, int, float, Path*);

    void move(std::vector<Vehicle *> );              // A function that describes the behavior of a normal driver
                                                     // The behavior is made of onle one simple function: arrive
    void applyBehaviour(std::vector<Vehicle*> vehicles);
};

#endif // ROAMINGDRIVER_H
