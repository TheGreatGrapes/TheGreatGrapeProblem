#ifndef PATH_H
#define PATH_H
#include "pvector.h"
#include "junction.h"
#include <vector>

class Path
{
public:
    Path();
    Path(float,float,float,float);

    std::vector<Junction*> mainJunctions;


////////////// Unused Stuff ////////////////
    float radius;

    Pvector *start;
    Pvector *end;

    void addPoints(float, float);

    std::vector<Pvector*> points;
};

#endif // PATH_H
