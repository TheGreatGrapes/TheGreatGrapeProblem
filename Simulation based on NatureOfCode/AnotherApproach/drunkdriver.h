#ifndef DRUNKDRIVER_H
#define DRUNKDRIVER_H
#include "vehicle.h"

class DrunkDriver : public Vehicle
{
public:
    DrunkDriver(float, float, int, float);

    void move(std::vector<Vehicle *> ); // A function that describes the behavior of a drunk driver
                                        // The behavior is made of two simple functions: follow and separate.

    void follow();
    void separate(std::vector<Vehicle *> );

};

#endif // DRUNKDRIVER_H
