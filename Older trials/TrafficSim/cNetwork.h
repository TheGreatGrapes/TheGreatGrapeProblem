#ifndef CNETWORK_H
#define CNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include <vector>
#include <memory>

#include <cmath>

#include "cNodes.h"
#include "cVehicle.h"


using namespace std;


class cNetwork
{
    public:
        /** Default constructor */
        cNetwork(int _netId, cNodes *_beginNode, cNodes *_endNode, int _numOfLanes);
        void addVehicle(cVehicle *_newVehicle);
		void update();
        bool collisionCheck(int _i);
		int getRoadLength();
		float getRelativVel(int _i);
		float getDist(int _i);


    private:
        int netId;
        cNodes *beginNode;
        cNodes *endNode;
		int roadLength;
        int numOfLanes;
        vector<cVehicle*> vehiclesOnRoad;
};

#endif // CNETWORK_H
