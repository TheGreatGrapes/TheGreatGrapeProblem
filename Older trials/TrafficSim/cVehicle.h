#ifndef CVEHICLE_H
#define CVEHICLE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class cNetwork;

class cVehicle
{
    public:
        /** Default constructor */
        cVehicle(int _vehId, float _vehPos, float _vehVel, float _vehAcc, cNetwork *_drivingRoad, int _activeLane);
        void drive();
		float getPose();
		float getVel();

    private:
        int vehId;
        float vehPos;
		float vehPose;
        float vehVel;
        float vehAcc;
        cNetwork *drivingRoad;
        int activeLane;
};

#endif // CVEHICLE_H
