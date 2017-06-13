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
	
	int roadLength = drivingRoad->getRoadLength();
	vehPose = vehPos*roadLength;
	
	drivingRoad->addVehicle(this); 
	cout << "the road length is " << vehPose << endl;
	}

void cVehicle::drive(){
	//DRIVING
	cout << "The position of the car - " << vehId <<" is " << vehPose << endl;
	//calculating the distance from the node using the position
	int rLength = drivingRoad->getRoadLength();
	//updating the distance
	vehPose = vehPose+vehVel;
	//updating the position in percentage
	vehPos=vehPose/rLength;
	}

float cVehicle::getPose(){
	return vehPose;
	}

float cVehicle::getVel(){
	return vehVel;
	}