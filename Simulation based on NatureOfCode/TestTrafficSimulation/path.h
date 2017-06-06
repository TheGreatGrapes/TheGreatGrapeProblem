#ifndef PATH_H
#define PATH_H
#include "pvector.h"
#include <vector>

class Path
{
public:
    Path();
    //Pvector *start;
    //Pvector *end;
    std::vector<Pvector*> points;

    float radius;

    void addPoints(float, float);

    Pvector* getStart();
    Pvector* getEnd();
    int getSize();
    Pvector* getPoint(int);

};

#endif // PATH_H
