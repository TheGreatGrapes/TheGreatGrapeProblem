#include "path.h"

Path::Path()
{
    radius = 5;
    //start = new Pvector(-200,100);
    //end = new Pvector(200,50);
}

void Path::addPoints(float x, float y){
    Pvector *point = new Pvector(x, y);
    points.push_back(point);   //try *point instead
}

Pvector* Path::getStart()
{
    return points[0];
}


Pvector* Path::getEnd()
{
    return points[points.size() -1];
}

int Path::getSize()
{
    return (int)points.size();
}

Pvector* Path::getPoint(int i)
{
    return points[i];
}
