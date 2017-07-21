#ifndef DRUNKDRIVER_H
#define DRUNKDRIVER_H
#include "vehicle.h"

class DrunkDriver : public Vehicle
{
public:
    DrunkDriver(float, float, int, float, Path*);

    void move(std::vector<Vehicle *> ); // A function that describes the behavior of a drunk driver
                                        // The behavior is made of two simple functions: follow and separate.
    void makeTurn(Path*);
    void applyBehaviour(std::vector<Vehicle*> vehicles);

    Pvector* follow();
    Pvector* separate(std::vector<Vehicle *> );

    void calulateDist();

};

#endif // DRUNKDRIVER_H
