#include "cNodes.h"

cNodes::cNodes(int _nodeId, int _nodePosX, int _nodePosY)
{
    nodeId = _nodeId;
    nodePosX = _nodePosX;
    nodePosY = _nodePosY;
}

vector<int> cNodes::getNodePose(){
	vector<int> pose;
	pose.push_back(nodePosX);
	pose.push_back(nodePosY);
	return pose;
	}
