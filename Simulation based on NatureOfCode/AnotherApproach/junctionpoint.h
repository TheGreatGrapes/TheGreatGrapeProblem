#ifndef JUNCTIONPOINT_H
#define JUNCTIONPOINT_H
#include "pvector.h"



class JunctionPoint: public Pvector     // The most basic components that make a junction, 4 to drive in / 4 out of the junction.
{
public:

    JunctionPoint(float,float,int);     // Inheriting everything from Pvector but with additional info like accessibility,
                                        // in/out junction, and index when being created.
    bool accessible;
    bool inOrOut;
    int index;

    JunctionPoint get();                // return a junctionPoint
};

#endif // JUNCTIONPOINT_H
