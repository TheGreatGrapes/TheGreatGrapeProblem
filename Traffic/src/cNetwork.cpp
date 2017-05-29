#include "cNetwork.h"

cNetwork::cNetwork(int _netId, cNodes *_beginNode, cNodes *_endNode, int _numOfLanes)
{
    netId = _netId;
    beginNode = _beginNode;
    endNode = _endNode;
    numOfLanes = _numOfLanes;
}

void cNetwork::AddVehicle(cVehicle *_newVehicle){
    vehiclesOnRoad->push_back(_newVehicle);
   // cout << vehiclesOnRoad->size();
   printf("this %d", vehiclesOnRoad->size());
}

void cNetwork::Update(){
    CollisionAvoidance();
}

void cNetwork::CollisionAvoidance(){
}

