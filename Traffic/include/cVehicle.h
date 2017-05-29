#ifndef CVEHICLE_H
#define CVEHICLE_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


class cNetwork;

class cVehicle
{
    public:
        /** Default constructor */
        cVehicle(int _vehId, float _vehPos, float _vehVel, float _vehAcc, cNetwork *_drivingRoad, int _activeLane);
        void drive();

    private:
        int vehId;
        float vehPos;
        float vehVel;
        float vehAcc;
        cNetwork *drivingRoad;
        int activeLane;
};

#endif // CVEHICLE_H
