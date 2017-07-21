#include "roamingdriver.h"

RoamingDriver::RoamingDriver(float posX, float posY, int _id, float maxV, Path* p)
    : Vehicle(posX, posY, _id, maxV, p)
{

}

void RoamingDriver::move(std::vector<Vehicle *> vehicles){

    applyBehaviour(vehicles);
}

void RoamingDriver::applyBehaviour(std::vector<Vehicle*> vehicles)   //overwritten with introduced weights for seperate and follow
{
    //Pvector* sep = separate(vehicles);
    Pvector* arr = arrive(vehicles);
    Pvector* foll = follow();

    foll->mult(0.2);
    //sep->mult(1);       //weight for seperate behaviour (high value will mean high consideration for *seperation*)
    arr->mult(1);

    //applyForce(sep);
    applyForce(foll);
    applyForce(arr);

}
