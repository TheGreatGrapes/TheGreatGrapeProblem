#ifndef CNODES_H
#define CNODES_H

class cNodes
{
    public:
        /** Default constructor */
        cNodes(int _nodeId, int _nodePosX, int _nodePosY);

    private:
        int nodeId;
        int nodePosX;
        int nodePosY;
};

#endif // CNODES_H
