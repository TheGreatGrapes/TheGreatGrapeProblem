#include "cNetwork.h"

cNetwork::cNetwork(int _netId, cNodes *_beginNode, cNodes *_endNode, int _numOfLanes)
{
    netId = _netId;
    beginNode = _beginNode;
    endNode = _endNode;
    numOfLanes = _numOfLanes;
	
	//calculation of road length a.k.a length of a vector
	roadLength = sqrt(pow(beginNode->getNodePose()[0]-endNode->getNodePose()[0],2)-pow(beginNode->getNodePose()[1]-endNode->getNodePose()[1],2));
}

void cNetwork::addVehicle(cVehicle *_newVehicle){
	vehiclesOnRoad.push_back(_newVehicle);
	
	cout << vehiclesOnRoad.size() << endl;
}

void cNetwork::update(){
	
	int limit = vehiclesOnRoad.size();
	vector<bool> collisionStatus(limit);
	for(int i=1; i<limit;i++){

		collisionStatus.push_back(collisionCheck(i));
		}
	for(int i=0; i<(limit-1);i++){
		if(collisionStatus[i]==true){
			
			}else{
				vehiclesOnRoad[i]->drive();
				vehiclesOnRoad[i+1]->drive();
				cout << "array: " << vehiclesOnRoad[i]->getPose() << " and " << vehiclesOnRoad[i+1]->getPose() << endl;
				}
		}
	}

bool cNetwork::collisionCheck(int _i){
	bool collisionResult = true;

	float relVel = getRelativVel(_i);
	float Dist = getDist(_i);
	
	if(Dist <= relVel){
		collisionResult= true;
		}else{
			collisionResult = false;
			}
	return collisionResult;
	}

int cNetwork::getRoadLength(){
	return roadLength;
	}

float cNetwork::getRelativVel(int _i){
	float relVel = vehiclesOnRoad[_i]->getVel() - vehiclesOnRoad[_i-1]->getVel();
	return relVel;
	}

float cNetwork::getDist(int _i){
	float Dist = vehiclesOnRoad[_i-1]->getPose() - vehiclesOnRoad[_i]->getPose();
	return Dist;
	}