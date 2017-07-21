#ifndef NORMALDRIVER_H
#define NORMALDRIVER_H
#include "vehicle.h"

class NormalDriver : public Vehicle
{
public:
    NormalDriver(float, float, int, float, Path*);

    void move(std::vector<Vehicle *> );              // A function that describes the behavior of a normal driver
                                                     // The behavior is made of onle one simple function: arrive
    Pvector* arrive(std::vector<Vehicle *> );
    Pvector* separate(std::vector<Vehicle*> );
    Pvector* goToJunction();                             // with our own version of behavior here in this NormalDriver class

    void makeTurn(Path* p);
    void findSomeoneInFront(std::vector<Vehicle *> );// This two functions are made virtual in Vehicle class so that we can easily overwrite it

    void applyBehaviour(std::vector<Vehicle*> vehicles);

};

#endif // NORMALDRIVER_H
