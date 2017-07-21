#ifndef PATH_H
#define PATH_H
#include "pvector.h"
#include "junction.h"
#include <vector>

class Path
{
public:
    Path();

    std::vector<Pvector*> Destinations;

    std::vector<Junction*> mainJunctions;

    void addMainJunctions(float, float);

};

#endif // PATH_H
