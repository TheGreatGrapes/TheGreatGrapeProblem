#ifndef CNODES_H
#define CNODES_H

#include <vector>

using namespace std;

class cNodes
{
    public:
        /** Default constructor */
        cNodes(int _nodeId, int _nodePosX, int _nodePosY);
		vector<int> getNodePose();

    private:
        int nodeId;
        int nodePosX;
        int nodePosY;
};

#endif // CNODES_H
