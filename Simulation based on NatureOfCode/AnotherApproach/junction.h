#ifndef JUNCTION_H
#define JUNCTION_H
#include "junctionpoint.h"
#include <vector>

class Junction
{
public:
    Junction(float, float);

    std::vector<JunctionPoint*> subJunctions; // A collection (vector) of 8 junction points at one crossroad, including 4 in/ 4 out.

    Pvector* junLocation;                     // Where the center of junction is located.

    void addPoints(float, float);             // Add points to the junction ( 8 junction points will be added by calling it once )

    void setStatus();                         // Filter out the points where no further connection is possible, and set up in/out points.

};

#endif // JUNCTION_H
