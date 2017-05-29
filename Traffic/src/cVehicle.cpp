#include "cVehicle.h"
#include "cNetwork.h"

cVehicle::cVehicle(int _vehId, float _vehPos, float _vehVel, float _vehAcc, cNetwork *_drivingRoad, int _activeLane)
{
    vehId = _vehId;
    vehPos = _vehPos;
    vehVel = _vehVel;
    vehAcc = _vehAcc;
    drivingRoad = _drivingRoad;
    activeLane = _activeLane;

    drivingRoad->AddVehicle(this);

     printf("this ");
}

void cVehicle::drive(){
}
