#ifndef CNETWORK_H
#define CNETWORK_H

#include <vector>

#include "cNodes.h"
#include "cVehicle.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


class cNetwork
{
    public:
        /** Default constructor */
        cNetwork(int _netId, cNodes *_beginNode, cNodes *_endNode, int _numOfLanes);
        void AddVehicle(cVehicle *_newVehicle);
        void Update();
        void CollisionAvoidance();


    private:
        int netId;
        cNodes *beginNode;
        cNodes *endNode;
        int numOfLanes;
        vector<cVehicle*> *vehiclesOnRoad;
};

#endif // CNETWORK_H
