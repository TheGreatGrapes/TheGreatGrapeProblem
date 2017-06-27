#ifndef NORMALDRIVER_H
#define NORMALDRIVER_H
#include "vehicle.h"

class NormalDriver : public Vehicle
{
public:
    NormalDriver(float, float, int, float);

    void move(std::vector<Vehicle *> );              // A function that describes the behavior of a normal driver
                                                     // The behavior is made of onle one simple function: arrive

    void arrive(std::vector<Vehicle *> );

    void findSomeoneInFront(std::vector<Vehicle *> );// This two functions are made virtual in Vehicle class so that we can easily overwrite it
    void goToJunction();                             // with our own version of behavior here in this NormalDriver class
};

#endif // NORMALDRIVER_H
